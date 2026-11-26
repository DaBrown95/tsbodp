These patches let old GNU tools build on a current host. `gcc302-host-compat.patch`
modifies GNU GCC 3.0.2 core source from
[the GNU release archive](https://ftp.gnu.org/gnu/gcc/gcc-3.0.2/gcc-core-3.0.2.tar.gz).
It applies only the following host compatibility changes:

- use `SET_DECL_RTL` instead of an obsolete conditional lvalue;
- use the native unprototyped fixed-argument callback ABI for generated instructions;
- check the border-block sentinel before indexing `dfs_order`.

The original files are `gcc/config/arm/arm.c` (Free Software Foundation,
1991, 1993–2001), `gcc/recog.h` (Free Software Foundation, 1987, 1996–2000),
and `gcc/dominance.c` (Free Software Foundation, 2000). They and this derived
patch are licensed under GNU GPL version 2 or later. The source contributors'
notices remain in the fetched source; the archive's unmodified license is
included as [GPL-2.0.txt](GPL-2.0.txt). The compatibility changes were prepared
for this project in October 2026.

The patch only makes the compiler build and run on a modern host. It does not
identify the compiler the game was built with, and the compiler's output is
still checked against the ROM by the normal matching build.

The separate `gcc302-hwi32-host-compat.patch` retains those three changes and
overrides `HOST_BITS_PER_WIDE_INT` to 32 and `HOST_WIDE_INT` to `int` in
`gcc/hwint.h` (Free Software Foundation, 1998). That file and this derived patch
also use GPL version 2 or later. This gives the compiler the integer arithmetic of a 32-bit host, while the
process itself keeps 64-bit pointers and `long`. ARM instruction selection is
not edited. The ordinary 64-bit-integer compiler is a separate pinned build.
Signed constants with the high bit set can make the two compilers emit
different Thumb instructions, so each source replacement is still accepted only
if the full extent matches and its changed-source controls are rejected.

The `binutils2101-host-compat.patch` file changes one host declaration in
[GNU binutils 2.10.1](https://ftp.gnu.org/gnu/binutils/binutils-2.10.1.tar.gz):
`libiberty/strerror.c` declares `sys_nerr` as `const`, matching current macOS
headers. That file identifies itself as public domain, written by Fred Fish
with a notice from Per Bothner. The assembler and its alignment code are
unmodified. GNU binutils' original GPL version 2 license is retained as
[binutils2101-GPL-2.0.txt](binutils2101-GPL-2.0.txt); its fetched source preserves
all original notices. This host change was prepared in October 2026.

Invocations of the modern assembler select the GNU object ABI and `softfpa`
explicitly. This matches the historical assembler's `-mno-fpu` convention and
lets mixed objects link with ABI checks enabled. A synthetic source test checks
that these flags leave the instruction bytes unchanged and that objects from
the historical compiler, the default compiler, assembly glue and explicit gaps
link together. Compiler assembly, object flags and output bytes are never
rewritten.
