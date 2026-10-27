"""Independent lost-read and movement guards; synthetic C, no compiler/ROM."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from permuter_setup import ROOT, UPSTREAM, parser_modules
from permuter_reuse import (qualify_scalar_reuse, require_scalar_reuse,
                            extract_comparison_reuse)


@unittest.skipUnless((ROOT / UPSTREAM / 'perm_pycparser').exists(), 'optional local upstream parser')
class ReuseTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.util, cls.ca = parser_modules()

    def case(self, source, variable='sum'):
        ast = self.util.parse_c(source)
        fn = next(n for n in ast.ext if isinstance(n, self.ca.FuncDef))
        nodes = []

        def visit(n):
            nodes.append(n)
            for _, child in n.children():
                visit(child)

        visit(fn)
        targets = [n for n in nodes if isinstance(n, self.ca.If)
                   and isinstance(n.cond, self.ca.BinaryOp) and n.cond.op == '>=']
        self.assertEqual(len(targets), 1)
        target = targets[0]
        return ast, fn, target, target.cond, variable, nodes

    def check(self, source, allowed, reason=None, place=None):
        ast, fn, target, expr, var, nodes = self.case(source)
        statement = place(nodes) if place else target
        before = self.util.to_c_raw(ast)
        result = qualify_scalar_reuse(ast, fn, statement, expr, var)
        self.assertEqual(result.allowed, allowed, result)
        self.assertEqual(self.util.to_c_raw(ast), before)
        if reason:
            self.assertIn(reason, result.reason)
        return result

    def test_scalar_assignment_rhs_is_a_read_at_unsafe_early_insertion(self):
        source = 'void f(int a,int b){int sum=7; int key; key=sum-1; if(a>=b){} }'
        place = lambda ns: next(n for n in ns if isinstance(n, self.ca.Assignment))
        result = self.check(source, False, 'read before', place)
        self.assertIsNotNone(result.blocking_read)
        self.assertIn(result.blocking_read, result.reads)
        self.assertLess(result.insertion_index, result.blocking_read)
        self.assertLess(result.blocking_read, result.expression_index)

    def test_compound_lhs_and_increment_are_reads_before_their_write(self):
        for operation in ('sum += 1', 'sum++', '++sum'):
            with self.subTest(operation=operation):
                source = f'void f(int a,int b){{int sum=7; {operation}; if(a>=b){{}} }}'
                place = lambda ns: next(n for n in ns if isinstance(n, (self.ca.Assignment, self.ca.UnaryOp)))
                self.check(source, False, 'read before', place)

    def test_live_value_after_selected_condition_is_not_discarded(self):
        result = self.check('int f(int a,int b){int sum=7; if(a>=b){} return sum;}', False, 'read before')
        self.assertGreater(result.blocking_read, result.expression_index)

    def test_next_definite_assignment_kills_the_old_value(self):
        self.check('int f(int a,int b){int sum=7; if(a>=b){} sum=2; return sum;}', True)
        self.check('int f(int a,int b,int c){int sum=7; if(a>=b){} if(c)sum=2; return sum;}',
                   False, 'read before')

    def test_sorter_shaped_nested_loop_resets_before_the_next_old_read(self):
        self.check('''void f(int a,int b,int count) {
            int i;
            for(i=0;i<count;i++) {
                int key, sum;
                sum=a+1;
                { int y=1; key=sum-y; }
                while(i<count) {
                    int other=b;
                    if(key>=other) break;
                    i++;
                }
            }
        }''', True)

    def test_loop_backedge_old_read_rejects_reuse(self):
        self.check('''void f(int a,int b) {
            int key, sum=7;
            while(a) { key=sum; if(key>=b)break; a--; }
        }''', False, 'read before')

    def test_old_value_inside_the_selected_comparison_is_consumed_on_rhs(self):
        ast, fn, target, expr, var, _ = self.case('void f(int b){int sum=7; if(sum>=b){} }')
        result = extract_comparison_reuse(ast, fn, target, expr, var)
        self.assertTrue(result.allowed)
        assignment = fn.body.block_items[-2]
        self.assertIsInstance(assignment, self.ca.Assignment)
        self.assertIs(assignment.rvalue, expr)
        self.assertEqual(assignment.lvalue.name, 'sum')
        self.assertEqual(target.cond.name, 'sum')
        self.assertEqual(expr.left.name, 'sum')
        # Reusing a stale selection after mutation must fail.
        self.assertFalse(qualify_scalar_reuse(ast, fn, target, expr, var).allowed)

    def test_repeated_self_read_is_not_consumed_again_after_the_store(self):
        # b=5,n=2: the original condition succeeds twice; overwriting sum with
        # its first Boolean result makes the second condition false.
        self.check('''int f(int b,int n){int sum=7;int out=0;
            while(n--){if(sum>=b)out++;}return out;}''', False, 'read before')
        self.check('''int f(int b,int n,int c){int sum=7;int out=0;
            while(n--){if(sum>=b)out++;if(c)continue;sum=7;}return out;}''',
                   False, 'read before')
        self.check('''int f(int b,int n){int sum=7;int out=0;
            while(n--){if(sum>=b)out++;sum=7;}return out;}''', True)

    def test_vla_sizeof_cannot_hide_an_evaluated_read(self):
        self.check('''void f(int a,int b){int sum=7;int size;
            if(a>=b){}size=sizeof(int[sum]);}''', False, 'variable-length')
        self.check('''int f(int a,int b){int sum=7;if(a>=b){}
            int v[sum];return sizeof v;}''', False, 'variable-length')
        self.check('''int f(int a,int b){int sum=7;if(a>=b){}
            int v[3];return sizeof v;}''', True)

    def test_function_local_typedef_cannot_hide_volatile_storage(self):
        self.check('''typedef int U;void f(int a,int b){
            typedef volatile int U;U sum;if(a>=b){}}''', False, 'function-local typedef')

    def test_bound_operands_allowed_but_bound_destination_rejected(self):
        self.check('''void f(int x,int b) {
            int sum; register int a asm("r4")=x; if(a>=b){}
        }''', True)
        self.check('''void f(int a,int b) {
            register int sum asm("r4")=1; if(a>=b){}
        }''', False, 'asm/type')

    def test_shadowed_escaped_static_qualified_and_noninteger_storage_rejected(self):
        for declaration, tail, reason in [
            ('int sum;', '{int sum=1;}', 'unshadowed'),
            ('int sum;', 'int *p=&sum;', 'escaped'),
            ('static int sum;', '', 'storage'),
            ('volatile int sum;', '', 'qualifier'),
            ('const int sum=1;', '', 'qualifier'),
            ('int *sum;', '', 'type'),
            ('double sum;', '', 'type'),
        ]:
            with self.subTest(declaration=declaration, tail=tail):
                self.check(f'void f(int a,int b){{{declaration}{tail}if(a>=b){{}}}}', False, reason)
        self.check('void f(int a,int b,int sum){if(a>=b){}}', False, 'local declaration')
        self.check('typedef volatile int V; void f(int a,int b){V sum; if(a>=b){}}', False, 'qualifier')

    def test_unused_typedef_integer_destination_can_hold_boolean(self):
        self.check('typedef unsigned long U; void f(int a,int b){U sum; if(a>=b){}}', True)

    def test_immediate_extraction_does_not_hoist_memory_or_calls(self):
        for condition in ('*p>=b', 'g()>=b', '(a && b)>=b'):
            with self.subTest(condition=condition):
                self.check(f'int g(void); void f(int a,int b,int *p){{int sum;if({condition}){{}}}}',
                           False, 'pure in-scope')
        self.check('void f(int x,int b){int sum; volatile int a=x; if(a>=b){}}', False, 'pure in-scope')

    def test_same_block_pure_unrelated_assignment_can_be_crossed(self):
        source = 'void f(int a,int b){int sum; int t; t=1; if(a>=b){} }'
        place = lambda ns: next(n for n in ns if isinstance(n, self.ca.Assignment))
        self.check(source, True, place=place)

    def test_effect_control_dependency_and_indirect_write_boundaries_rejected(self):
        for statement in ('g();', '*p=1;', 'a=2;', 'if(a){}', 'a++;'):
            with self.subTest(statement=statement):
                source = f'void g(void); void f(int a,int b,int *p){{int sum;{statement}if(a>=b){{}}}}'
                ast, fn, target, expr, var, _ = self.case(source)
                start = fn.body.block_items[1]
                result = qualify_scalar_reuse(ast, fn, start, expr, var)
                self.assertFalse(result.allowed, result)
                self.assertTrue('boundary' in result.reason or 'unsafe scalar write' in result.reason, result)

    def test_case_switch_and_unstructured_control_explicitly_rejected(self):
        for body in ('switch(a){case 1: if(a>=b){} break;}',
                     'goto out; if(a>=b){} out: return;',
                     'asm("nop"); if(a>=b){}'):
            with self.subTest(body=body):
                self.check(f'void f(int a,int b){{int sum;{body}}}', False)

    def test_short_circuit_subexpression_is_not_unconditionally_hoisted(self):
        ast = self.util.parse_c('void f(int a,int b,int c){int sum;if(c && a>=b){} }')
        fn = ast.ext[0]
        target = fn.body.block_items[-1]
        result = qualify_scalar_reuse(ast, fn, target, target.cond.right, 'sum')
        self.assertFalse(result.allowed)
        self.assertIn('whole condition', result.reason)

    def test_rejected_wrapper_does_not_mutate_the_ast(self):
        ast, fn, target, expr, var, nodes = self.case('int f(int a,int b){int sum=7;if(a>=b){}return sum;}')
        before = self.util.to_c_raw(ast)
        with self.assertRaisesRegex(ValueError, 'read before'):
            extract_comparison_reuse(ast, fn, target, expr, var)
        self.assertEqual(self.util.to_c_raw(ast), before)
        with self.assertRaisesRegex(ValueError, 'read before'):
            require_scalar_reuse(ast, fn, target, expr, var)


if __name__ == '__main__':
    unittest.main()
