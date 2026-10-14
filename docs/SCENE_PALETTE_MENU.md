# Actor-palette menu scene lifecycle

The audited phase table's row nineteen connects initialization `0x08013F3D`,
state dispatch `0x08015F69` and shutdown `0x0801405D`. These three ordinary-C
functions add 564 original extent bytes and connect the previously reconstructed
[actor/palette menu](ACTOR_GROUP_BINDING.md) and its transition path. Ten state
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
| 0 | `0x0801553C` | Original |
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
