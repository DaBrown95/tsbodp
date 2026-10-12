> Internal AI scratch notes. Function and field names are provisional.

# Frame-synchronised transitions and background animation

The connected transition batches reconstruct **28 functions, 2,696
bytes** at their original addresses, including pools and padding. The
VBlank-connected background animation path adds **seven functions, 500 bytes**,
comprising the tick, loader, four lifecycle routines and alpha defaults. Five
background visibility/reset routines add **188 bytes**. Nine scene/character
animation routines add **1,176 bytes**, and the two frame handoff wrappers add
**132 bytes**. The combined batch inventory is **51 functions, 4,592 bytes**.
The scene batch is described in [SCENE_RECONSTRUCTION.md](SCENE_RECONSTRUCTION.md).
Every candidate in this batch is compiled with the pinned agbcc backend at
`-O2 -mthumb-interwork`, linked at its original address and compared over the
complete extent. Every function has a changed-source negative control that
produces differing bytes. These are compiler matches; no runtime or gameplay
validation is implied.

## Connected paths

The callers of `irq_wait_vblank` expose a family of transitions from ROM
`0x38588` through `0x39B10`. The initial batch contains four connected window
sweeps/split-window routines, seven fades that also refresh frame stages,
three blocking alpha ramps, two indirect dispatch wrappers and seven alpha
configuration/update helpers. Additional window variants and refresh
controllers in that family remain unconverted; their source candidates are
not accepted coverage.

Window routines write `WININ`, `WINOUT`, the window rectangles, `DISPCNT`,
`BLDCNT` and `BLDY`. Their 16.16 intermediate arithmetic changes short pixel
coordinates by two pixels vertically or three pixels horizontally, once per
VBlank. Endpoint overshoot and the original comparison operators are kept.
The close/open words in candidate names describe inferred transition roles;
the concrete register operations are the stronger evidence.

The seven frame-refresh fade variants call the same four provisional stage
entries at `0x08001168`, `0x0800D17C`, `0x080117D4` and `0x0802D054`. Some
refresh once then wait twice, while others refresh on each of their two
waits. Their stage ordering differs in the original; the source retains it.
They choose brightness increase/decrease mode with `BLDCNT` and update
`BLDY` in one- or two-level steps. These stage names do not establish the
full responsibilities of their callees.

The two alpha-wave objects at `0x03001F98` and `0x03001FA0` each have four
signed halfwords: value, step, minimum and maximum. The setters and the
148-byte update at ROM `0x384F4` support that layout. The update adds the
step, clamps at a crossed endpoint and reverses the step, then derives
integer coefficients by shifting right eight. It writes the coefficients
back in 8.8 form and updates `BLDALPHA`; the quantization is retained. The
three blocking ramps also use these value fields and write `BLDALPHA`,
waiting the specified number of VBlanks per level or two VBlanks per level.

The indirect dispatchers at ROM `0x393FC` and `0x39434` set bit `0x4000` in
the word at `0x03004310`, call an indexed handler and clear that bit.
Their tables begin at ROM `0x6A1E0` and `0x6A218`. Each contiguous table has
14 Thumb handler pointers, and the second ends before non-pointer data at
`0x6A250`. Calls go through the compiler's `_call_via_r1` at `0x0804CCF4`.
The table entries are established statically, but these dispatchers do not
check the index. Caller bounds and the domain of the `kind` argument need
separate evidence before calling the indirect targets complete for arbitrary
inputs.

## Background animation

The VBlank call at `0x0800A788` updates the structure at `0x03002EC0`. Its
layout is a frame-pointer table at zero, a resource handle at four, signed
countdown at eight, flags at ten, delay and last-frame bytes at twelve and
thirteen, signed frame index at fourteen and transfer-enable byte at fifteen.
When the word at `0x03004310` has none of `0x70018` set and the animation's
flag one is set, it decrements the countdown. On expiry it advances or
reverses the signed frame index, wraps it, resets the countdown and, if
enabled, calls `0x0800CD4C` with background index three, the selected resource
pointer, `0xC0` and three. The display callee's accesses identify this as a
background resource animation, correcting the earlier palette hypothesis.
The cleanup at ROM `0xA890` tests the word at offset four with the resource
query at `0x0804146C`, conditionally releases it through `0x08041340`, and
hides background three through `0x0800D5DC`. This supports the provisional
resource-handle type. The 16-byte clear at `0xA87C`, forced reload at `0xA844`
and conditional stop at `0xA864` connect initialization and shutdown to the
VBlank state. Stop clears the low four flag bits; forced reload sets bit
eight when transfers are enabled. The complete flag meanings and the resource
handle lifetime remain unresolved. The 200-byte loader at `0xA6C0` now matches and closes that dependency. Its
twenty-byte descriptors and display calls are documented with the scene batch.

## Object handoff and recorded fades

The callback at ROM `0x1869C` uses the same frame-object prefix as the frame
subsystem, with transition state at `+0x4D`, pending flag at `+0x4F`, signed
countdown at `+0x58`, reset period at `+0x64`, endpoint at `+0x68` and alpha
bytes at `+0x72/+0x73`. The partial transition view leaves all unrelated fields
explicitly unknown. The helper at `0x1C04` changes state only when needed and
sets pending bit one. The callback advances or reverses alpha on countdown
expiry, applies coefficients unless game bit `0x100000` blocks them, and
restores the background animation when an endpoint is reached. The group
activation callee at `0xAD98` is still named provisionally; its two arguments
select resource object and command groups rather than proven hardware layers.

The paced fade controllers at `0x3946C/0x394F8` update link coordination, record
an event, run the frame stages and wait until the absolute VBlank-counter
difference reaches the configured period at `0x0300430C`. Their recorder at
`0x3A41C` has an eight-byte payload ABI and a twelve-byte record: kind and
sequence bytes, reserved halfword and an eight-byte data union. Its bounded
switch covers kinds one through thirteen. Kind three samples `KEYINPUT`;
other kinds consume a word, selected bytes, or one of three global vectors.
The callback increments the sequence, copies the record to `0x030072F0` and
sets game flag `0x40`. The fixed destination alone does not establish a queue.

Kind one ignores the payload, and these fade callers assign only its first
word; the original upper word remains unspecified. The source preserves that
representation rather than inventing an initialized argument. An aligned byte
view reproduces the by-value ABI; the exact original typedef remains unknown.
The code matches do not prove the event consumer or link protocol.

Alignment-only `asm(".align 2, 0")` directives explicitly retain original zero
tails where the assembler would otherwise emit Thumb NOP fill. They contain
no original instruction body. The instruction bodies remain semantic C.

## Retained comparison evidence

The ignored `reports/agents/vblank-wrapper/accepted-manifest.json` records the
accepted extents, external addresses, Thumb function declarations and source
mutations used by the negative controls. Each accepted trial retains its C
snapshot, compiler assembly/object, linker script/map-independent ELF,
reference bytes, candidate bytes and raw comparison. The `controls/` folder
retains independently compiled mutations and reports. Other directories
preserve rejected source shapes, including window-coordinate variants whose
instruction scheduling or literal ownership still differs.
