> Internal AI scratch notes. Names and types below are reconstructed descriptions.

# VBlank wrapper evidence

The USA/Europe revision 0 function beginning at ROM `0x1F680` ends at
`0x1F854`, including its literal pools and alignment. The accepted C candidate
owns all **468 bytes**. It was compiled with the pinned agbcc backend at `-O2
-mthumb-interwork` and linked at `0x0801F680`; the full extent is identical.
This compiler match is separate from runtime or gameplay evidence.

The increment and reload of `0x03001DA4` establish a volatile nesting-depth
word. Only depth one executes the body; every path decrements it. The word at
`0x03001DA8` is toggled with one and selects a 1024-byte OAM image within a
buffer. `0x03004520` and `0x03004D60` are the two buffer bases used here. DMA0
at `0x040000B0` transfers 256 words to OAM at `0x07000000`, with control
`0x84000100` and a following control-register read. This is DMA0, while the
interrupt installation function independently uses DMA3.

The context halfword at offset `0x38` selects the transfer/handoff path. When
set, the wrapper chooses the opposite source from the pointer at
`0x03004510`, copies a pending byte from `0x03004400` to `0x03004D50`, clears
the pending byte and calls `0x08011834`. It then copies the pointer at
`0x03004D20` to `0x03004510` and toggles `0x03004D20` between the two buffer
bases. When the halfword is clear, DMA uses the buffer selected by
`0x03004510` without that pointer handoff. The pointer-role names remain
provisional; they should be refined with the buffer writers.

The wrapper calls, in order, `0x0800A788`, `0x08046F84`, the context's VBlank
callback through the compiler's `_call_via_r0`, `0x0800D3B0`, `0x080486B8`
and `0x080117E4`. These calls connect background animation, queued transfers,
frame updates, background register changes, window registers and palette
jobs; detailed names depend on each reconstructed callee. The context's
`vblank_count` at `0x1C` increments. Its `0x2C` counter increments and resets
after 59; `0x30` is sampled into `0x34` and cleared at that rollover. The
`frame_work_count` name describes this sampling only; the writers need
further evidence. The `0x38` transfer-ready halfword is then cleared if set.

The function acknowledges VBlank in `REG_IF` and software flags at
`0x03001DA0`. The byte at `0x03007366` has bit 7 tested and bit 6 cleared or
set. With bit 7 clear, it clears bit 6 and calls ROM `0x0804C874`, a veneer
to the copied audio ARM entry at `0x03001080`. With bit 7 set, it sets bit 6
and skips that call. Busy/pending names are inferred from this coordination
pattern. An eight-bit volatile bitfield accurately expresses the preserved
read/modify/store accesses; no embedded original instructions are used.

Every exit disables `REG_IME`, sets bit zero of the BIOS interrupt flags at
`0x03007FF8`, and reenables `REG_IME`. These BIOS flags are distinct from the
game's software flags. The ordering and unconditional reenable are retained
as observed rather than generalized to a different interrupt API.

Local reports under `reports/agents/vblank-wrapper/` preserve the complete
reference and compiled extents, compiler/link commands, source snapshots and
failed candidates. Changing the buffer-index shift from 10 to 9 produces a
same-size 468-byte candidate with four differing bytes and is rejected.
