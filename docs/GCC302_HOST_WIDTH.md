# Separate GCC 3.0.2 compiler integer widths

The sequencer envelope reconstruction exposed a host-width dependency in the
public GCC 3.0.2 Thumb backend. The ordinary native build selects 64-bit
`HOST_WIDE_INT` under its Alpha LP64 configure model. A negative 32-bit constant
is sign extended to 64 bits; `thumb_shiftable_const` then rejects it because its
shifted eight-bit masks cover only bits zero through thirty-one. A build using
32-bit compiler integers accepts that same target constant and synthesizes a
move and shift instead of a literal-pool load.

The separate `gcc302_hwi32` profile overrides the permitted macros in `hwint.h`
to `HOST_BITS_PER_WIDE_INT=32` and `HOST_WIDE_INT=int`. Native pointers and `long`
remain LP64. It reuses the ordinary host compatibility changes, with no new ARM
backend edits. Both profiles originate from the same pinned public archive;
the new complete patch, source-tree hash, configure/build instructions and
native executable fingerprint are separate. Setup enrolls a native fingerprint
only after a fresh build, and rejects an unknown existing executable, partial
build, stale source pin, changed archive/patch/source or changed preprocessor.
`make setup` provisions the profiles selected by the accepted manifest.

This is a reconstruction aid, not proof of the historical compiler. There is
no rewrite of compiler assembly, object flags, output or reference bytes. The
full 776-byte instrument function first compiled as 780 bytes with the LP64
profile; the HWI32 profile produces exactly the original 776 bytes from the
same semantic C. That private contrast and the failed original attempts remain
in `reports/audio-root/player-instruments*`. Public-source verification uses
the canonical freshly provisioned profile rather than the exploratory build.

The tools test suite covers explicit Thumb/ARM selection, independent profile
ownership, rejection of altered inputs and a real high-bit-constant source
control. A separate finite review compares 56 independently computed constants
in both instruction modes: signed/unsigned 32-bit edges; 64-bit shifts,
division and remainders; float/double constants and conversions; and target
integer/pointer sizes. Four actual source mutations are detected. Eight
variable-expression functions compile without diagnostics and preserve explicit
external helper references. The raw fixture initially assumed IEEE double
word ordering; GCC's ARM FPA layout stores the high word first, each word little
endian. That failed expectation and the independently corrected layout are
both retained. No compared bytes were patched or masked.

The canonical receipt is in
`reports/agents/vblank-wrapper/gcc302-host-width-edge-fixtures/`; compiler hashes
are checked before and after. These finite static checks do not prove arbitrary
compiler correctness, runtime behavior or gameplay. The ordinary LP64 profile
remains in use for its existing matches; functions opt into HWI32 explicitly.
