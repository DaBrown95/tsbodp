# Sequential scrolling-text scene

The scene phase table's row thirteen points to initialization at `0x08013B0D`,
input at `0x08013C45` and shutdown at `0x08013E09`. Twelve connected C functions
cover 1,072 original extent bytes, including their pools and zero alignment.
The names describe sequential resource-text creation and upward object motion;
they do not identify the displayed content or establish gameplay behavior.

| ROM extent | Function | Bytes |
| --- | --- | ---: |
| `0x13B0C` | `scene_scroll_text_initialize` | 312 |
| `0x13C44` | `scene_scroll_text_step` | 88 |
| `0x13C9C` | `scene_scroll_text_append` | 200 |
| `0x13D64` | `scene_scroll_text_end_step` | 164 |
| `0x13E08` | `scene_scroll_text_shutdown` | 32 |
| `0x13E28` | `scene_scroll_text_confirm` | 4 |
| `0x13E2C` | `scene_scroll_text_cancel` | 44 |
| `0x13E58` | `scene_scroll_text_vertical` | 4 |
| `0x13E5C` | `scene_scroll_text_horizontal` | 4 |
| `0x13E60` | `scene_scroll_text_update` | 56 |
| `0x13E98` | `scene_scroll_text_regular_step` | 60 |
| `0x13ED4` | `scene_scroll_text_hold_step` | 104 |

## State, initialization and input

The sixteen-byte view at `0x03001908` contains the latest object pointer at
`+0`, a retained object pointer at `+4`, signed halfword coordinates at `+8`
and `+0x0A`, and a stop byte at `+0x0C`. The remaining bytes and full allocation
ownership are unknown. Initialization selects sequence nine and clears eight
halfwords with the existing explicit BIOS copy/fill wrapper. It initializes
coordinates to 162 and 160 and request parameter to resource-text index 6292.
The BIOS wrapper adds no C credit in this batch.

The setup configures backgrounds three and two, uses the selected text bank's
background table, loads two palettes, configures alpha transitions and creates
two scene objects. The second object receives text resource 23, transition
state fourteen and variant 58. The transition-object cast refers to the
existing alternate access view of the same frame object. Its provider takes
a byte state; the two alpha providers take halfwords. Serialized backgrounds,
palettes and resource strings remain original private data.

Input reads the local player's pressed halfword and checks bit zero, bit one,
`0xC0` and `0x30` in that order, then runs the scrolling update. Confirm,
vertical and horizontal handlers are observed empty C callbacks, each owning
its two-byte return and two-byte zero alignment. The cancel handler returns
to kind six with the current scene when the previous request was kind six;
otherwise it submits default kind five. These names follow the button edges
and do not imply functionality in the empty handlers. Shutdown runs the second
transition, releases the primary list, resets display state and clears scene
object slots. The audio-options chooser and serialized scene command are
existing callers that can request this scene.

## Text creation and object callbacks

The append function obtains the text indexed by the request parameter. A
leading caret is consumed; a following digit zero through nine is also consumed
and used as a control kind. Kind one selects font three, while other kinds use
font one, with the same remaining font parameters. A nonempty remainder creates
a text object, centers it at the signed halfword coordinates and sets its
vertical velocity to negative one pixel in 16.16 fixed-point units. Kind zero
sets the stop byte and installs the ending callback. Kind one installs the
retained-object callback; other kinds install the regular callback. The latest
pointer is saved. Empty strings still advance the halfword cursor by twelve
and the word text index by one. The string capacities and termination domain
remain unproven.

The frame update appends while the stop byte is clear and either the latest
pointer is null or its signed fixed-point y position is below `0xA00000`.
It then decrements the cursor's low halfword modulo 65,536. Signed cursor reads
for positioning and unsigned low-halfword arithmetic are separate observed
accesses to the same storage.

The ending callback sets object flag bit one and returns to the previous/default
scene after y becomes negative. Below `0x240000`, its next branch clears object
flag bit zero and retires any retained object, clearing the retained pointer.
The regular callback sets flag bit one below the same threshold. The retained
callback stops an object at y no greater than `0x120000` and saves it at `+4`;
its next branch retires that saved object below `0x240000`.

The native callbacks also contain lower-threshold branches after those
`0x240000` tests. Their comparisons are preserved even though the captured
signed y conditions make those subsequent branches unreachable. They manipulate
bits two and three of the existing object byte at `+0xD1`. The new two-bit view
records that exact access while preserving all other bits; the complete meaning
of those bits and the original rationale for the threshold ordering are unknown.
The held-object variant has an inclusive `0x200000` comparison, while the other
two use exclusive comparisons. These differences remain explicit.

## Matching and limits

Initialization uses the real fill pointer before assigning zero, and the append
function creates its font selector only after parsing the prefix. Those genuine
lifetimes recover the original ordering without extra operations or bindings.
Scoped real button masks reproduce the separate input tests. Eleven functions
match without register bindings. The update has one scoped unsigned-halfword
binding to `R0` for the actual minus-one increment. It is converted into the
word sum and expires before the fresh cursor load; it crosses no call. The
state pointer is unbound. Removing the increment constraint changes native
allocation; no unused initializer or synthetic traffic is present.

All twelve functions have changed-source negative controls. The empty callback
controls add an actual write to the observed stop byte; they do not claim the
write belongs in the original. The three empty extents and cancel path use
explicit zero-filled alignment, separate from the C instruction bodies.
Interspersed pools in the append and ending callbacks remain inside their full
original extents. The next independent prologue at `0x13F3C` bounds the final
callback. Current accepted provider/caller bodies are rechecked without duplicate
coverage, and the existing BIOS wrapper remains separate assembly glue.
Useful failed width, lifetime, byte-mask and padding trials remain in ignored
local reports. This establishes compiler and byte matches plus static scene
connections; it does not establish hardware timing or runtime/gameplay behavior.

The palette-provider declarations are now explicit and use their accepted
word-argument, void-return interfaces. The earlier initializer used C89
implicit declarations; refreshing all twelve sources and controls with the
corrected header adds no coverage. See the connected
[palette-menu lifecycle](SCENE_PALETTE_MENU.md) for this declaration correction.
