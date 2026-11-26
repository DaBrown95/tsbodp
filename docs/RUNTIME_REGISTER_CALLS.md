# Compiler assembly runtime

Two groups of routines in the code area are compiler runtime assembly rather
than C: the register-call veneers and the integer division and remainder
routines. Both are written as assembly sources under `src/`, because the
upstream compiler library writes them that way.

## Register-call veneers

The family at `0x0804CCF0..0x0804CD2C` is fifteen four-byte veneers, one each
for `r0` to `r9`, `sl`, `fp`, `ip`, `sp` and `lr`. Each branches through its
named register and is followed by a NOP. The family is 60 bytes: 30 branch
bytes and 30 NOP bytes.

The fifteen entries appear in the same order, with the same bodies, as
[`libgcc/lib1thumb.asm`, `L_call_via_rX`](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc/lib1thumb.asm#L595-L633)
at the pinned agbcc revision. That source describes the BL/BX interworking
contract: BL sets an odd Thumb return address, and BX then picks the target
state from the register's low bit. The veneers keep the caller's return
address and have no ordinary C argument or return interface. The match shows
the origin is compiler runtime assembly. It does not identify which compiler
revision the game used.

The upstream copyright, GPL and linking-exception notices stay in every source
file, and the full [GPL text](../licenses/GCC-GPL-2.0.txt) is kept in the
repository. The only changes are to split the upstream macro into standalone
sources and to write the GNU assembler directives out explicitly; the branch
and NOP are unchanged.

Each four-byte extent matches the reference. The negative controls change the
target register or the NOP halfword to a different value of the same size, and
the build rejects each.

The inventory census records the fifteen NOPs (30 bytes) as assembly
instructions that no control flow reaches. Which registers reach these
veneers, and which callers use them, is not known.

## Integer division and remainder

Five routines from the same upstream `libgcc/lib1thumb.asm` are assembly,
totalling 672 bytes. The upstream Makefile builds these handwritten routines
separately from its C `libgcc2` and floating-point sources. The algorithm, the
unrolled subtract-and-shift order, the scratch-register use and the
`MOV PC, LR` returns all match the ROM.

| Entry | ROM offset | Full extent | Instructions | Zero alignment |
| --- | --- | ---: | ---: | ---: |
| `__divsi3` | `0x4CD2C` | 148 | 146 | 2 |
| `__div0` | `0x4CDC0` | 4 | 2 | 2 |
| `__modsi3` | `0x4CE08` | 208 | 206 | 2 |
| `__udivsi3` | `0x4CED8` | 120 | 120 | 0 |
| `__umodsi3` | `0x4CF50` | 192 | 192 | 0 |

The instructions total 666 bytes and the alignment padding six. The C
`__fixunsdfsi` at `0x4CDC4..0x4CE08` sits between `__div0` and `__modsi3` and
is separate from these. The division routines call `__div0` when the divisor
is zero.

Only the preprocessor wrappers for symbol, type, size and return were
expanded, and Thumb mode and alignment were made explicit. The upstream
licence and linking exceptions stay in every source file. Each extent matches
with no output patches, extra sections or unresolved relocations. The
negative controls change the division's starting bit or the zero handler's
return instruction, and each is rejected.
