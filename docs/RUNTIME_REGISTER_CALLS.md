# Compiler assembly runtime

## Register-call veneers

The complete family at `0x0804CCF0..0x0804CD2C` now has explicit source
ownership: fifteen four-byte veneers for `r0` through `r9`, `sl`, `fp`, `ip`,
`sp` and `lr`. Each branches through its named register and retains the native
following NOP. The family totals 60 separate assembly extent bytes: 30 branch
bytes and 30 NOP bytes. The previously owned `r1` and `r3` entries account for
eight of those bytes; this intake adds thirteen entries and 52 bytes, with no
recovered-C credit.

Assembly origin is supported by the identical fifteen-entry order and bodies
in [`libgcc/lib1thumb.asm`, `L_call_via_rX`](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc/lib1thumb.asm#L595-L633)
at the pinned compiler source revision. That source explicitly describes the
BL/BX interworking contract: BL establishes an odd Thumb return address, then
BX selects the target state from the register's low bit. The veneers preserve
that caller-supplied return and have no ordinary C argument/return interface.
This is compiler runtime assembly, rather than an exception for a difficult C
match. It does not uniquely identify the historical compiler revision.

The upstream copyright, GPL and linking-exception notices remain in every
selected source; the full [GPL text](../licenses/GCC-GPL-2.0.txt) is retained.
Changes split the upstream macro into standalone sources and make the GNU
assembler directives explicit; the branch and NOP are unchanged. Every full
four-byte extent matches and rejects a same-size change to the target
register. Fresh local comparisons and controls are retained under ignored
`analysis/compiler-call-veneers/`.

This source ownership does not close the incoming register values, complete
caller set or writable callback populations. In particular, no caller or
runtime execution is inferred for previously unindexed family members.

## Integer division and remainder

Five selected routines from the same pinned `libgcc/lib1thumb.asm` now own
672 assembly extent bytes. The upstream Makefile builds these handwritten
assembly definitions separately from its C `libgcc2` and floating-point sources.
The algorithm, unrolled subtraction/shift order, scratch-register protocol and
`MOV PC, LR` returns all match the native bodies; these are supported assembly
origin exceptions, not C functions translated to assembly to obtain a match.

| Entry | ROM offset | Full extent | Instructions | Zero alignment |
| --- | --- | ---: | ---: | ---: |
| `__divsi3` | `0x4CD2C` | 148 | 146 | 2 |
| `__div0` | `0x4CDC0` | 4 | 2 | 2 |
| `__modsi3` | `0x4CE08` | 208 | 206 | 2 |
| `__udivsi3` | `0x4CED8` | 120 | 120 | 0 |
| `__umodsi3` | `0x4CF50` | 192 | 192 | 0 |

The existing C `__fixunsdfsi` occupies `0x4CDC4..0x4CE08`; it is separate from
these assembly owners. The division routines call the independent original
`__div0` entry on a zero divisor. No new exception replaces that C conversion,
and the reference's arithmetic and zero-divisor behavior are preserved.

Selection expands only preprocessor symbol/type/size/return wrappers and makes
standalone Thumb mode/alignment explicit. Full upstream licence and linking
exceptions remain in every selected source. Every whole extent matches, with
no output patches, instruction payloads, extra sections or unresolved
relocations. Controls change the division bit seed, or the zero handler's
return instruction, and all reject at the same sizes. The 666 instruction
bytes and six alignment bytes remain distinct from C credit. Local source,
linked bytes, controls and the independent boundary/provenance review are
under ignored `analysis/compiler-integer-division/`.
