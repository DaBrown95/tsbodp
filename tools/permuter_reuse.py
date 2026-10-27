"""Conservative checks for one deterministic comparison-to-scalar extraction.

This is independent of upstream find_var_reads and source_contract. It does not
certify arbitrary C equivalence or qualify random permuter output. The accepted
subset is a pure integer comparison used as the whole condition of an If,
assigned to an unescaped automatic integer immediately before that If or across
simple scalar assignments in its same Compound. Requalify after any AST change.
No upstream files, compiler settings, or search weights are changed here.
"""
from dataclasses import dataclass

from project import ROOT


@dataclass(frozen=True)
class ReuseCheck:
    allowed: bool
    reason: str
    reads: tuple
    writes: tuple
    insertion_index: int | None
    expression_index: int | None
    blocking_read: int | None = None


def _walk(node):
    if node is not None:
        yield node
        for _, child in node.children():
            yield from _walk(child)


def _accesses(node, ca):
    """Value reads and scalar writes; scalar '=' still visits its entire RHS."""
    reads, writes = [], []

    def visit(n):
        if n is None:
            return
        if isinstance(n, ca.ID):
            reads.append(n)
        elif isinstance(n, ca.Decl):
            visit(n.init)
            if n.init is not None:
                writes.append((n.name, n))
        elif isinstance(n, ca.StructRef):
            visit(n.name)  # The field identifier is not a local variable read.
        elif isinstance(n, ca.Assignment):
            if isinstance(n.lvalue, ca.ID):
                if n.op != '=':
                    visit(n.lvalue)
                writes.append((n.lvalue.name, n.lvalue))
            else:
                visit(n.lvalue)
            visit(n.rvalue)
        elif isinstance(n, ca.UnaryOp):
            if n.op == '&' and isinstance(n.expr, ca.ID):
                return  # Address-taking is rejected independently.
            if n.op in ('sizeof', '_Alignof', '__alignof__'):
                return
            visit(n.expr)
            if n.op in ('p++', 'p--', '++', '--') and isinstance(n.expr, ca.ID):
                writes.append((n.expr.name, n.expr))
        else:
            for _, child in n.children():
                visit(child)

    visit(node)
    return reads, writes


class _Unsupported(ValueError):
    pass


class _Flow:
    """Structured flow for read-before-def, not expression equivalence."""
    def __init__(self, fn, variable, ca):
        self.ca, self.variable = ca, variable
        self.nodes, self.entries = [], {}
        self.entry = self.statement(fn.body, None, None, None)

    def atom(self, owner, expression, successors=()):
        reads, _ = _accesses(expression, self.ca)
        ca = self.ca
        # Nested/conditional writes are not definite definitions. Counting all
        # reads first also conservatively rejects x = x + 1 and compound LHSs.
        defines = (isinstance(expression, ca.Assignment)
                   and expression.op == '='
                   and isinstance(expression.lvalue, ca.ID)
                   and expression.lvalue.name == self.variable)
        defines |= (isinstance(expression, ca.Decl)
                    and expression.name == self.variable
                    and expression.init is not None)
        index = len(self.nodes)
        self.nodes.append(([r for r in reads if r.name == self.variable],
                           defines, [s for s in successors if s is not None]))
        if owner is not None:
            self.entries[owner] = index
        return index

    def statement(self, n, following, breaking, continuing):
        ca = self.ca
        if n is None:
            return following
        if isinstance(n, ca.Compound):
            head = following
            for item in reversed(n.block_items or []):
                head = self.statement(item, head, breaking, continuing)
            return self.atom(n, None, (head,))
        if isinstance(n, ca.If):
            yes = self.statement(n.iftrue, following, breaking, continuing)
            no = self.statement(n.iffalse, following, breaking, continuing)
            return self.atom(n, n.cond, (yes, no))
        if isinstance(n, (ca.While, ca.DoWhile)):
            condition = self.atom(n, n.cond)
            body = self.statement(n.stmt, condition, following, condition)
            self.nodes[condition][2].extend(s for s in (body, following) if s is not None)
            if isinstance(n, ca.DoWhile):
                return self.atom(n, None, (body,))
            return condition
        if isinstance(n, ca.For):
            condition = self.atom(None, n.cond)
            step = self.atom(None, n.next, (condition,))
            body = self.statement(n.stmt, step, following, step)
            self.nodes[condition][2].extend(s for s in (body, following) if s is not None)
            return self.atom(n, n.init, (condition,))
        if isinstance(n, ca.Break):
            return self.atom(n, None, (breaking,))
        if isinstance(n, ca.Continue):
            return self.atom(n, None, (continuing,))
        if isinstance(n, ca.Return):
            return self.atom(n, n.expr)
        if isinstance(n, (ca.Decl, ca.Assignment, ca.FuncCall, ca.UnaryOp,
                          ca.BinaryOp, ca.Cast, ca.ExprList, ca.EmptyStatement)):
            return self.atom(n, n, (following,))
        raise _Unsupported('unsupported control or statement: ' + type(n).__name__)

    def first_read_before_def(self, statement, consumer, consumed_reads=()):
        if statement not in self.entries:
            raise _Unsupported('insertion is not an executable statement')
        consumer_index = self.entries[consumer]
        pending, seen = [(self.entries[statement], False)], set()
        while pending:
            index, consumed = pending.pop()
            state = index, consumed
            if state in seen:
                continue
            seen.add(state)
            reads, defines, successors = self.nodes[index]
            # Only the first dynamic evaluation retains these reads before
            # the new store. A backedge reads the overwritten value and must
            # be rejected unless an original definite assignment killed it.
            first_consumer = index == consumer_index and not consumed
            old_reads = [n for n in reads if not first_consumer or n not in consumed_reads]
            if old_reads:
                return old_reads[0]
            if not defines:
                pending.extend((successor, consumed or first_consumer) for successor in successors)
        return None


def qualify_scalar_reuse(ast, function, assign_before, expression, reuse_name,
                         *, root=ROOT):
    """Check one current AST; return source-read evidence, without mutation.

    False negatives are intentional. Labels/goto/switch/asm, ambiguous names,
    escaped storage, unsupported types and effectful movement are rejected.
    Access indices are an independent preorder of this function, not upstream
    availability indices. A passing result is not a reusable certificate after
    another transformation, nor proof of general aliasing or C equivalence.
    """
    from permuter_setup import parser_modules
    _, ca = parser_modules(root)
    nodes = list(_walk(function))
    indices = {n: i for i, n in enumerate(nodes)}
    reads, writes = _accesses(function.body, ca)
    read_indices = tuple(indices[n] for n in reads if n.name == reuse_name)
    write_indices = tuple(indices[n] for name, n in writes if name == reuse_name)

    def result(allowed, reason, blocking=None):
        return ReuseCheck(allowed, reason, read_indices, write_indices,
                          indices.get(assign_before), indices.get(expression),
                          indices.get(blocking))

    if (not isinstance(function, ca.FuncDef) or function not in ast.ext
            or assign_before not in indices or expression not in indices):
        return result(False, 'function or selected nodes are outside the current AST')
    if len(indices) != len(nodes):
        return result(False, 'shared AST nodes are unsupported')
    parents = {child: node for node in nodes for _, child in node.children()}
    declarations = [n for n in _walk(function.body) if isinstance(n, ca.Decl)]
    args = function.decl.type.args
    parameters = [n for n in (args.params if args else []) if isinstance(n, ca.Decl)]
    locals_by_name = {}
    for decl in declarations + parameters:
        locals_by_name.setdefault(decl.name, []).append(decl)
    candidates = locals_by_name.get(reuse_name, [])
    if len(candidates) != 1 or candidates[0] in parameters:
        return result(False, 'reuse needs one unshadowed local declaration')
    if any(isinstance(n, ca.Typedef) for n in nodes):
        return result(False, 'function-local typedefs are outside the qualified subset')
    decl = candidates[0]
    typedefs = {n.name: n.type for n in ast.ext if isinstance(n, ca.Typedef)}

    def integer(declaration, destination=False):
        if declaration.asmlabel and destination:
            return False
        if declaration.gcc_attributes or set(declaration.storage) - {'auto', 'register'}:
            return False
        quals = set(declaration.quals)
        type_ = declaration.type
        seen = set()
        while isinstance(type_, ca.TypeDecl):
            quals.update(type_.quals)
            type_ = type_.type
            if isinstance(type_, ca.IdentifierType) and len(type_.names) == 1:
                name = type_.names[0]
                if name in typedefs and name not in seen:
                    seen.add(name)
                    type_ = typedefs[name]
        if not isinstance(type_, ca.IdentifierType):
            return False
        if not type_.names or not set(type_.names) <= {'int', 'char', 'short', 'long', 'signed', 'unsigned', '_Bool'}:
            return False
        return not (quals - ({'const'} if not destination else set()))

    if not integer(decl, destination=True):
        return result(False, 'reuse local is not an ordinary automatic integer (qualifier/storage/asm/type)')
    if any(isinstance(n, ca.Asm) for n in nodes):
        return result(False, 'inline asm is outside the qualified subset')
    if any(isinstance(n, ca.ArrayDecl) and n.dim is not None
           and not isinstance(n.dim, ca.Constant) for n in nodes):
        return result(False, 'variable-length array evaluation is outside the qualified subset')
    if any(isinstance(n, ca.UnaryOp) and n.op == '&'
           and any(isinstance(i, ca.ID) and i.name == reuse_name for i in _walk(n.expr))
           for n in nodes):
        return result(False, 'reuse local has escaped or address-taken storage')
    if any(isinstance(n, ca.FuncCall) and isinstance(n.name, ca.ID)
           and 'setjmp' in n.name.name for n in nodes):
        return result(False, 'nonlocal control is outside the qualified subset')

    def in_scope(declaration, point):
        if declaration in parameters:
            return True
        block = parents.get(declaration)
        if not isinstance(block, ca.Compound) or indices[declaration] >= indices[point]:
            return False
        while point is not None and point is not block:
            point = parents.get(point)
        return point is block

    if not in_scope(decl, assign_before):
        return result(False, 'reuse local is not declared at the insertion point')
    target = parents.get(expression)
    if not isinstance(target, ca.If) or target.cond is not expression:
        return result(False, 'expression must be the whole condition of an If')
    if not isinstance(expression, ca.BinaryOp) or expression.op not in ('<', '<=', '>', '>=', '==', '!='):
        return result(False, 'only a comparison result (0 or 1) may be extracted')
    # These old-value reads stay on the RHS and precede the extraction's store.
    # All other reads, including scalar assignment RHSs, remain blockers.
    consumed_reads = set(_walk(expression))
    try:
        blocking = _Flow(function, reuse_name, ca).first_read_before_def(assign_before, target, consumed_reads)
    except _Unsupported as exc:
        return result(False, str(exc))
    if blocking is not None:
        return result(False, 'old scalar value is read before its next definite assignment', blocking)

    block = parents.get(target)
    if not isinstance(block, ca.Compound) or parents.get(assign_before) is not block:
        return result(False, 'insertion and consumer must be direct siblings in one Compound')
    begin, end = block.block_items.index(assign_before), block.block_items.index(target)
    if begin > end:
        return result(False, 'insertion must precede the comparison')
    deps = set()

    def pure(expr, point):
        if isinstance(expr, ca.ID):
            found = locals_by_name.get(expr.name, [])
            if (len(found) != 1 or not integer(found[0])
                    or not in_scope(found[0], point)):
                return False
            deps.add(expr.name)
            return True
        if isinstance(expr, ca.Constant):
            return expr.type in ('int', 'char')
        if isinstance(expr, ca.UnaryOp) and expr.op in ('+', '-', '~', '!'):
            return pure(expr.expr, point)
        if isinstance(expr, ca.BinaryOp) and expr.op in ('+', '-', '*', '&', '|', '^', '<<', '>>', '<', '<=', '>', '>=', '==', '!='):
            return pure(expr.left, point) and pure(expr.right, point)
        return False

    if not pure(expression, assign_before):
        return result(False, 'comparison needs pure in-scope integer operands')
    comparison_deps = deps.copy()
    for stmt in block.block_items[begin:end]:
        if not (isinstance(stmt, ca.Assignment) and stmt.op == '='
                and isinstance(stmt.lvalue, ca.ID)):
            return result(False, 'movement crosses an effect or control boundary')
        name = stmt.lvalue.name
        found = locals_by_name.get(name, [])
        if (name in comparison_deps or name == reuse_name or len(found) != 1
                or not integer(found[0], destination=True)
                or not in_scope(found[0], stmt) or not pure(stmt.rvalue, stmt)):
            return result(False, 'movement crosses an unsafe scalar write or effect')
    return result(True, 'qualified comparison extraction; old scalar value is dead on structured paths')


def require_scalar_reuse(*args, **kwargs):
    """Reject before a caller attempts its deterministic transformation."""
    check = qualify_scalar_reuse(*args, **kwargs)
    if not check.allowed:
        raise ValueError(check.reason)
    return check


def extract_comparison_reuse(ast, function, assign_before, expression, reuse_name,
                             *, root=ROOT):
    """Qualify and perform exactly one extraction on these current AST nodes."""
    check = require_scalar_reuse(ast, function, assign_before, expression, reuse_name, root=root)
    from permuter_setup import parser_modules
    _, ca = parser_modules(root)
    parents = {child: node for node in _walk(function) for _, child in node.children()}
    target = parents[expression]
    block = parents[target]
    position = block.block_items.index(assign_before)
    target.cond = ca.ID(reuse_name)
    block.block_items.insert(position, ca.Assignment('=', ca.ID(reuse_name), expression))
    return check
