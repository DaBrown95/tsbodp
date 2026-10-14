# Definition row three: selection controller, moving event and row actors

This connected path has eighteen matching C functions covering 3,332 bytes,
including their original literal pools and alignment. It follows selection input
through object creators and the installed event and row updates, coordinate and
vector helpers, animation resets, palette requests and temporary-object removal.
The original initializer at `0x08018B28` (328 bytes), row preparation at
`0x08019640` (544), value refresh at `0x08019CF0` (144), event drawing at
`0x08019D80` (368), linked-row update at `0x0801994C` (332), and selection marker
at `0x08019A98` (96) remain explicit original dependencies and receive no C credit.
An exact source match does not recover those dependencies or establish gameplay.

The observed definition row at `0x080595B0` installs the original initializer
`0x08018B29` and the reconstructed no-argument controller `0x08018C71`.
The event creator installs `0x080190B1`; the row creator installs `0x0801925D`
at object offset 136. Both callbacks take one `FrameObject *`. The row creator
has an actual incoming word selector, stores its low halfword as the object ID,
and increments the scene's signed halfword active-row count. The callback and
creator declarations are checked against the actual reconstructed definitions.

The scene uses an observed 92-byte, four-aligned prefix within the existing
420-byte allocation: sound countdown at 10, signed active-row count 12,
sequence restore field 14, option 19, flags 21, primary/secondary/cursor pointers
24/28/32, observer slot 36, event slot 40, five eight-byte row-origin points 44,
sample handle 84 and three value bytes 88. The control root `0x03004350` has a
24-byte prefix, with refresh count 8, selection word/byte view 12, phase 16 and
timer 20. Temporary storage at `0x030038E0` has sixteen observed pointer slots
and a word count at 64 in a 104-byte prefix. Complete original capacities and
ownership remain unproved; no one-element array substitutes for these prefixes.

The activity's object view is 224 bytes, four-aligned, within the separately
verified 320-byte allocation. It names only observed positions, velocity,
acceleration and destination points; ID/subtype at 8/10, flags 12, direction 18,
speed 20, amount/phase/outcome/palette bytes 76..79, countdown word 88, step
callback 136, D1 and D3 bit fields, D5 palette/layer fields and animation fields
216..223. The native D1 operation clears bits 2..3, not the generic actor view's
provisional three-bit interpretation. Local typed views preserve this concrete
role without changing the shared actor layout or callback API.

The initializer stores an actual returned observer pointer into slot 36. Its
local union preserves that pointer's word representation. Reading the stored
word and converting it back to the observed object pointer restores the original
reload after writes to the automatic point. This is a causal compiler finding,
not proof that game objects alias those local points at runtime. Attachment
reads require the actual successful result 1 and initialized signed-byte X/Y
outputs. The coordinate consumers read each component only after its real
provider write; no uninitialized aggregate copy or invented incoming value is
used to preserve registers. The original attachment resource currently has an
observed attachment entry, but arbitrary incoming objects/resources are unproved.

The controller retains one real local binding. At `0x08018D2A` the old full
selection word is held in callee-saved R4 across the actual input call at
`0x08018D38`. After the new selection word is stored from R1, `0x08018D40/42`
narrow the same old word to its low byte in place. That call-free byte phase is
consumed as the first refresh argument at `0x08018D48` and is dead before the
refresh call at `0x08018D4A`. The second argument is the new low byte; the next
refresh receives new/new. Both calls, cursor movement and cue happen even when
the selected values are equal. Removing the binding keeps 576 bytes but differs
in 41 bytes. No other reconstructed body uses register bindings.

Five observed 56-byte row definitions begin at `0x08052B60`: speed 44 and four
byte thresholds at 48..51. Seven eight-byte phase records start at `0x08052C78`:
scale 0, threshold 4, probability 6 and frame delay 7. Three twelve-byte
background entries at `0x08052CB0` contain background pointer 0, palette pointer
4 and scale 8. Five four-byte option records at `0x08052B4C` provide three value
bytes. These are bounded local prefixes inferred from access strides and static
neighbor boundaries; they are not an inventory of all game data.

The direction helper takes four actual coordinate words in R0..R3. Unsigned
word subtraction defines the coordinate wrap before conversion to the signed
point passed to the existing angle provider. Four scalars and two grouped points
are both possible low-level source interpretations; the coherent C caller/callee
interface uses four scalars and a full unsigned return word. The existing angle
provider returns 0..31. The separate four-byte Thumb BIOS service-0A handoff at
`0x0804C8BC` is explicit assembly glue with zero C credit; the accepted service-0C
neighbor at `0x0804C8C0` is a different function. BIOS hardware behavior is not
established by matching or the finite memory model.

Normal positive/changed-source pairs cover all eighteen new functions and
22 accepted providers/dispatch contexts; strict diagnostics cover all new bodies.
Pinned compiler diagnostics check 74 layout facts and eighteen actual APIs,
physical bit masks and the pointer/word union; thirteen wrong headers reject.
A real omitted palette-queue declaration remains legacy-byte-identical but
rejects with strict declarations. The full current literal-header closure,
source/native function extents, pool relocations and natural zero tails are
separately audited. Whole-ROM acceptance and publication remain separate gates.

The finite packet executes 907 initialized cases: 903 bounded source-operation
cases and four angle-255 injections that test only the declared ABI. It records
345 real source-control divergences and seven deliberately rejected interpreter
or input cases. The actual input provider is separately executed in 24 zero,
directional and high-word cases; it supplies the word outcomes used by the
controller checks. A distinct wrong-old-selection source control diverges in
18 of 27 old/new cases. Predecessor fixtures incorrectly gated refresh calls on
unequal values; equal-selection checks exposed that model error, and the failed
model, raw bodies and corrected full replay are retained locally. The C source
and ROM were unchanged. Temporary pointers are unique initialized live objects;
the removal abstraction records the observed ID-FFFF tombstone. List, palette,
free-list and gameplay effects remain outside that abstraction. Direct children
use explicit provider hooks, with caller-saved poisoning and call effects; this
is bounded static/compiler evidence, not hardware execution or gameplay proof.
