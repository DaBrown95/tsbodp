# Actor-palette menu scene lifecycle

The audited phase table's row nineteen connects initialization `0x08013F3D`,
state dispatch `0x08015F69` and shutdown `0x0801405D`. These three ordinary-C
functions add 564 original extent bytes and connect the previously reconstructed
[actor/palette menu](ACTOR_GROUP_BINDING.md) and its transition path. Nine state
handlers remain explicit original dependencies; matching these scene callbacks
does not establish complete reconstruction or runtime behavior of this menu.

| ROM extent | Function | Bytes |
| --- | --- | ---: |
| `0x13F3C` | `scene_palette_menu_initialize` | 288 |
| `0x1405C` | `scene_palette_menu_shutdown` | 112 |
| `0x15F68` | `scene_palette_menu_step` | 164 |

## Initialization and shared state

Initialization allocates 308 zeroed bytes and stores the pointer at
`0x03001954`. The observed word at allocation offset zero receives 25; its
meaning is unknown. The pointer at `+0x130` receives existing game-state
storage at `0x03003978`, or game-state `+0x28`. The new partial structure
records these accesses and the observed allocation size without assigning
roles to the intervening fields or interpreting the pointed-to storage.
Allocation failure is unchecked, as in the original.

The shared request receives scene zero, transition/state word `+0x10` zero
and timer `+0x14` thirty. All fifteen words beginning at `0x03001918` are
cleared; the existing menu-choice declaration and its accepted consumers are
reused. Four background controls at `0x08051F60..0x08051F6C` configure layers
zero, three, two and one. Layers zero, two and one are filled with zero. The
layer-zero control also selects the text background. An original palette is
loaded through the canonical word-argument palette interface; no palette bytes
are embedded in the reconstructed source.

The existing exit-object array at `0x03001958` is cleared for 32 bytes. Its
count byte at `0x03001978` and the following control byte at `0x03001979` are
cleared separately. These are the same views used by the accepted transition
routine; their complete ownership and valid count domain remain unproven.
The timer is then set to thirty-one. The intervening provider calls can observe
the earlier thirty, so both stores are retained. Initialization loads layer
three's background, sets both velocity coordinates to 65,536, selects sequence
one and runs the first transition with `(63, 0)`.

## State dispatch and shutdown

The state dispatcher reads the shared request word at `+0x10`. Its complete
switch owns the fifteen-word jump table at `0x08015F84` and the following call
blocks through `0x1600A`, plus two zero alignment bytes. Explicit empty cases
seven, thirteen and fourteen reproduce the original table and upper bound;
values above fourteen return without calling a handler. An initial implicit-
default model omitted the two high empty cases, emitted 156 bytes and failed
comparison. The accepted switch needs no manufactured work or register binding.

| State | Observed target | Current source status |
| ---: | --- | --- |
| 0 | `scene_palette_menu_phase_0` | Matching C |
| 1 | `0x080157D0` | Original |
| 2 | `frame_step_palette_menu_transition` | Matching C |
| 3 | `frame_step_palette_menu` | Matching C |
| 4 | `0x08014B40` | Original |
| 5 | `0x08015270` | Original |
| 6 | `0x08014584` | Original |
| 7 | Empty case | Part of this dispatcher |
| 8 | `0x080146E4` | Original |
| 9 | `0x08014CB0` | Original |
| 10 | `0x08014F08` | Original |
| 11 | `0x080152D0` | Original |
| 12 | `0x080153EC` | Original |
| 13, 14 | Empty cases | Part of this dispatcher |

The original-target declarations use state-number names until their bodies
provide semantic evidence. They are address handoffs and receive no C credit.
The two accepted handlers connect row choice, text drawing, actor resources,
input and transitions to this lifecycle.

Shutdown copies the low bytes of the first seven choice words into the existing
game-state selectors at `+0x20..+0x26`. The eighth selector is left untouched.
It then runs the second transition, releases the primary object list, resets
display and palette jobs, clears scene-object slots and frees the allocation.
The global allocation pointer is not cleared. This matches the existing actor
updater's selector widths and storage while preserving the observed operations.

## Verification and connected declaration correction

All three functions match without register bindings or added traffic. Their
complete extents include literal pools, the switch table and zero alignment.
The shutdown ends at the independently accepted constructor `0x140CC`;
the dispatcher ends at the next prologue `0x1600C`. Controls change allocation
size, the final selector's source choice and the dispatch word; all must reject.
Current accepted constructor, updater, row-choice/draw, outer input and
transition callers/providers are rechecked without duplicate coverage.

This batch also corrects the scrolling-text header to explicitly declare
`display_load_palette` and `display_load_palette_alternate` with their accepted
`void(const void *, unsigned int, unsigned int)` interfaces. Its previous
initializer relied on C89 implicit declarations. All twelve scrolling-text
sources and their controls are refreshed with the explicit types, with zero
additional C credit. Useful failed declaration, lifetime and switch models
remain local. Static connections and source/byte matching remain separate from
runtime, hardware-timing and gameplay claims.

## State-zero entry and preparation

Two ordinary C providers add 660 matching extent bytes: state zero at
`0x0801553C..0x08015728` owns 492 bytes, followed by the 168-byte preparation
helper through `0x080157D0`. State one remains an independent original entry.
The complete pools and alignment belong to these two extents. No register
bindings, new guards, volatile accesses or extra calls and stores are required.
The lifecycle above and the previously reconstructed transition/update handlers
remain distinct connected sources with no duplicate credit.

State zero snapshots the request's full phase word and returns immediately when
it is nonzero. Only the zero-phase path captures the timer word. At timer 31 it
prepares the entry and plays cue 12. Timer 30 sets window one, configures its
control, starts scroll and window moves, enables backgrounds one and zero and
prepares the object slots. Slots 13 and 14 receive IDs 129 and 128; the fresh
request scene decides which receives flag one, need timer 16 and variant 56,
while the other clears flag one and receives variant 58. Scene three reverses
those roles. Slots 8, 12, 15, 16 and 10 receive IDs 131, 130, 135, 136 and 132,
need timers 14, 16, 15, 15 and 15, and variant 56. Object pointers and indices
remain unchecked.

At timer 15, the helper reconfigures window one, enables background two, starts
its scroll and the second window-move view, writes the captured zero phase to the
request parameter and prepares slot 11 with ID 133, need timer 15 and variant 56.
Timer one disables window one; timer zero sets the phase word to one. Other
timers perform none of these branches. Every zero-phase path then decrements
fresh global timer storage, including after provider calls, rather than storing
an arithmetic result from the earlier snapshot. This preserves possible provider
changes to that storage without claiming a runtime trace.

The first of the three 15-valued halfword stores uses an ordinary one-member
`PaletteTimerCell` access view of the existing `need_timer` field at actor
`+0x5E`. Explicit packed, two-byte alignment gives the view size and alignment
two under the pinned compiler, preserving the original halfword store. The
compiler's plain aggregate would have size and alignment four, exceeding this
field's observed alignment. This is no new allocation or complete actor layout.
The word timer assigned during that actual
store supplies the two following stores. A plain halfword-pointer predecessor
kept the object base and omitted a subsequent native table reload, failing by
eight bytes. The cell view preserves the original destructive field-address
calculation, timer value and table reload with no additional traffic. The exact
compiler alias/lifetime mechanism is inferred from the output, while the field
width, address and full byte match are directly checked. Failed forms and raw
comparisons remain private.

Preparation clears backgrounds zero, one and two, selects font one with fill
minus one, loads the two original backgrounds and the established entry palette,
and invokes the original template walker with tile one and word argument 37.
It sets all three background scroll targets with word duration one before calling
the original entry-object builder. The template declaration returns a word and
accepts word arguments plus a pointer to eight-byte records containing signed
halfword x/y, byte width/style and halfword text. The pinned compiler gives this
eight-byte record four-byte alignment; the template root at `0x08052444` and its
eight-byte stride satisfy it. Static layout checks independently establish offsets
zero, two, four, five and six. A private width-byte-to-word control fails the
layout checks while this pointer-passing helper still matches, distinguishing
layout evidence from caller-byte equality. The ignored word result and
proper record-pointer type retain the original 168-byte helper. The former
private void/untyped declaration is excluded from canonical interface evidence.

The template walker at `0x08044F00..0x08044FA0` and the 336-byte object builder
at `0x08015B68` remain explicit original dependencies with zero new C credit.
The typed template header ships with this batch; it does not represent recovered
source for that provider. Its accepted text decoder/drawing/font/buffer context,
the actual background, window, variant and audio providers, the lifecycle caller
and incoming background-enable wrapper are verified separately.

Fresh canonical positives and changed-source controls cover both complete
extents and the current connected providers/callers. Controls change the timer
value in the actual halfword store and the template word argument. Source,
literal current-header dependencies, allocated native sections, symbols, original
addresses and pools are pinned; stricter implicit-declaration warning-as-error
builds run outside the unchanged acceptance profile. These are static and
compiler/link claims, not gameplay, object-capacity, template-content or complete
menu reconstruction claims. Nine state targets remain original.
