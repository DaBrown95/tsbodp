# Factory slot 11 and scene kind 21

This connected path has eleven matching C extents, 3,088 bytes: resource factory
slot 11 creates a contact trigger, its paired collision callback submits scene
kind 21, and that scene initializes, processes input, refreshes selection, manages a
quantity editor, draws labels and a tile frame, and shuts down. The names describe observed catalog and selection accesses; they
are provisional. Compiler matching, static ownership and gameplay behavior are
separate claims. No gameplay run is claimed here.

| Function | ROM offset | Full extent |
|---|---:|---:|
| `frame_create_scene_trigger` | `0x3ACCC` | 148 |
| `frame_scene_trigger_contact` | `0x111F8` | 68 |
| `scene_catalog_initialize` | `0x41C4C` | 700 |
| `scene_catalog_step` | `0x41F08` | 876 |
| `scene_catalog_selection` | `0x42D38` | 200 |
| `scene_catalog_shutdown` | `0x42FE8` | 36 |
| `scene_catalog_update` | `0x42274` | 196 |
| `scene_catalog_begin_quantity` | `0x42E00` | 192 |
| `scene_catalog_quantity` | `0x42EC0` | 160 |
| `scene_catalog_build` | `0x430A4` | 80 |
| `scene_view_draw_frame` | `0x34480` | 432 |

Every extent includes its literal pools and original trailing alignment. The
constructor ends at the distinct original no-op entry `0x3AD60`; that four-byte
callee remains original and receives no C credit. The contact callback ends at
the distinct movement callback `0x1123C`. The initializer and step own the
adjacent ranges through `0x41F08` and `0x42274`. Selection owns its pools through
`0x42E00`; shutdown ends at the distinct `0x4300C` helper.

## Entry types and transfer evidence

The resource factory table at `0x4F278`, slot 11 at `0x4F2A4`, contains
`0x0803ACCD`. The existing `ResourceObjectFactory` uses two byte arguments.
The constructor has those compatible formals, then uses explicit low-byte
word locals for the payload provider. Its serialized payload is a 12-byte,
word-aligned partial record: ID word at zero, signed X/Y halfwords at 4/6,
width/height bytes at 8/9 and a selector byte at 10. Coordinates multiply signed
halfwords by 65,536. The selector is zero-extended into a halfword at object
`+0x64`; its field width is not inferred merely from the payload byte.

The full partial `SceneTriggerView` begins at the object base, size 204 and
alignment 4. Its player byte is at `+0x13`, state byte at `+0x4D`, selector at
`+0x64`, step callback at `+0x88`, bound count at `+0xAF`, four signed bounds at
`+0xB0..B3`, bound kind at `+0xB4` and paired callback at `+0xC8`. The constructor
sets flags `0x20404`, resets transition state, installs callback `0x080111F9`
and original no-op `0x0803AD61`, and records symmetric width/height bounds.

The callback's formals and role field use the existing two-pointer
`CollisionCallback` contract. The copied ARM collision dispatcher supplies both
objects in R0/R1, invokes the candidate's `+0xC8/+0xCC` slot, then handles the
reversed pair. The generic one-argument actor `on_interact` view remains a
separate provisional access view; this batch changes none of its declarations.
The new callback requires the other object's ID zero and state 16, reads
`g_input_pressed[other.player] & 1`, submits kind 21, mode zero and the owner's
halfword selector, then clears input. It does not test or write owner state.
This differs from the preceding contact-action callback at `0x111AC`.

The scene callback table at `0x5797C` uses 12-byte begin/step/end rows. Kind 21
contains `0x08041C4D`, `0x08041F09`, `0x08042FE9`. The accepted scene loaders call
these no-argument callbacks. Actual factory, collision and scene callback
assignments are checked with the pinned compiler; restored incompatible
factory word formals and `FrameObject *` collision formals are rejected.

## State, input and display behavior

The new scene header supplies partial, overlapping RAM views. State at
`0x030021C8` has page start, count, row, value and selector bytes at offsets
0..4; its compiler size/alignment is 8/4. The page-start name follows the
original page navigation helpers' four-entry increments and decrements. The
world view at `0x03003950` has an eight-byte clock at `+8`, quantity bytes at
`+0xE0`, value bytes at `+0xE9`, a catalog pointer at `+0xF0` and eight-byte
entry strides at `+0xF8`. The entry member contains the observed 14-entry
prefix for known selectors 0..13, giving this partial world view size/alignment
360/4; its complete capacity is unknown. These declared array lengths describe observed
accesses, not validated capacities. The catalog count is a one-byte,
`packed, aligned(1)` read view of the pointer target; the unreconstructed
drawing helper also reveals a word pointer at target `+4`, but this batch does
not claim a complete target record.

Initialization captures the requested selector, clears request selection,
quantity and phase, and derives count/value through those views. Signed clock
hour comparisons against the ROM records at `0x7FB48/0x7FB50` gate selectors
7/9. Selector 4 changes the first/action/last row limits and backgrounds;
selector 13 chooses another background. The phase-one branch draws a notice;
the other branch prepares objects, draws labels and calls the original panel,
item, heading and refresh helpers. Shutdown runs the second transition,
releases the object list and resets display, palette jobs and object slots.

The step callback keeps request phase zero's directional navigation and
confirmation, phase two's quantity edit and commit/cancel, phase one's notice
dismissal and phase three's local pressed-input mask. Shared and local pressed
arrays are distinct: phase zero gates direction with the shared array, reads
actual direction through the local array, then captures a fresh shared word for
confirmation. Phase two captures local words separately before and after the
quantity helper. It updates quantities, game value and flags on object slots
11/12 only on their original branches. Phase three masks the captured phase
word with local input; it does not turn that test into a new boolean condition.

Selection preserves the captured selector across an opaque item-refresh call:
selector 4 switches object zero's subtype 10/12, updates the selected row and
uses ID offsets 123 or 38. Other selectors use offset 39. Object pointers are
read again after refresh calls, and page/row bytes are read afresh for the fill
and draw calls. It then sets variant 58. A changed variant control differs at
all three actual call sites.

Two allocation hints express real value lifetimes. Initialization's R4 style
value is assigned after the first text lookup and stays live through the first
draw and second lookup to become the second draw's real argument. Step's R1
input value is assigned by each genuine input read; each captured word is dead
before any provider call, or is read on a path with no intervening call. The
next phase read starts a new lifetime. Removing these hints alone yields
700/79 and 876/10 byte differences. No instruction bodies, artificial reads,
volatile accesses or dummy dependencies are embedded.

## Explicit original helper boundary

Selection and the four text/quantity helpers are recovered. The bodies below
remain original. Their no-result call contracts use `void`
because these callers consume only effects; this is a scoped declaration, not
proof of the original source return type. The draw/fill entries retain full
word arguments: their native prologues preserve incoming words and use word
index arithmetic, while the reconstructed callers explicitly load bytes or
pass zero. The remaining original helpers consume no incoming arguments on
the observed paths.

| Original helper | ROM offset | Retained static extent |
|---|---:|---:|
| Draw items | `0x42338` | 208 including two-byte alignment |
| Fill panel | `0x42408` | 588 |
| Prepare objects | `0x42654` | 664 |
| Confirm | `0x42964` | 654 mapped estimate; alignment remains original |
| Option | `0x42BF4` | 324 |
| Finish | `0x4300C` | 104 |
| Previous page | `0x431B8` | 60 |
| Next page | `0x431F4` | 80 |

These are local static boundary estimates, not an exhaustive inventory. The
item-drawing source attempts are retained privately: first 220/197, followed
by genuine iterator/common-branch/slot-view trials 200/174, 200/177, 192/194.
They receive no C credit. The unconverted helpers may mutate scene state or
object pointers. Unchecked player, selector, object, array and resource inputs
remain unchecked; no runtime capacity or pointer-target validity is claimed.

Fresh canonical verification covers the six sources and all 37 connected
accepted providers/dispatchers: 43 positive/changed-source pairs, plus six
strict diagnostic pairs. Pinned layout controls reject a shifted player,
incorrect object packing, default count-view alignment, the former one-entry prefix and a byte selector;
the byte-selector factory also fails the actual ROM comparison. Removing an
actual audio prototype fails strict compilation. Native sections, pools,
alignment, current literal headers, source changes and global aliases are
audited separately. Whole-ROM integration remains a subsequent publication
gate, not a claim made by these local proofs.

## Quantity and text continuation

The second connected batch adds five extents, 1,060 bytes. The initializer and
step now call the four recovered helpers by their own names. These are only
identifier changes at the existing addresses: update `0x08042275`, headings
`0x080430A5`, quantity `0x08042EC1` and quantity setup `0x08042E01`. Both callers'
body constants, control logic, compiler profiles and extents are unchanged;
the complete affected literal importer closure is refreshed.

Quantity setup reads the selected quantity byte into a word. Zero plays cue 3
and returns. Otherwise it sets phase 2 and parameter 1, selects the font, loads
the fixed frame resource and measures text 439. Its unsigned width calculation
is `((width + 7) >> 3) + 2`; centering also uses an unsigned shift, preserving
the original word behavior if the measured width is out of range. It selects
the text layer, stages the captured available quantity, draws texts 438/439,
refreshes the quantity label and plays cue 1. The captured quantity stays live
through the opaque display calls.

The quantity label toggles object slots 12 and 11 from parameter==1 and
parameter==available quantity, clears its tile rectangle, formats the quantity
and draws it. The 20-byte native stack frame has eight outgoing argument bytes
and a 12-byte text region. This is not a general formatter capacity guarantee:
the accepted formatter can produce more than twelve bytes for wider word
inputs. The recovered setup initializes parameter 1 and the step edits it
against a byte quantity, but external writers, row validity and gameplay
coverage are not complete. No new guard or larger stack allocation is added.

The label updater handles the selected row versus the action row, request mode
and selector 13's object visibility. Its real zero color is assigned within the
actual rectangle-fill argument and then used as the later label's style. That
ordinary C lifetime change closes the initial 196/5 mismatch without new
traffic. The headings helper reads the signed value word at world `+4`, stages
it as a text substitution and draws text `0x184C`. The separate eight-byte,
word-aligned access view overlaps the existing world view; it does not claim an
independent object or complete world structure. The signed word type follows
the already accepted game-value update provider.

The frame drawer owns `0x34480..0x34630`, including its two-byte original zero
alignment and three literal words. The adjacent fixed-resource loader remains
a distinct accepted function. Full word X/Y/width/height arguments are retained;
only right and bottom endpoints wrap to bytes. It draws the three-by-three
frame pieces in the original order, with the center last:

| Row | Left | Middle | Right |
|---|---:|---:|---:|
| Top | tile+0 | tile+1 | tile+2 |
| Middle | tile+3 | tile+4 | tile+5 |
| Bottom | tile+6 | tile+7 | tile+8 |

Each draw reloads the background word, tile halfword and palette halfword from
`0x03001F04/1F08/1F0A`. Tile addition precedes palette OR and then wraps to a
halfword; the rectangle provider itself accepts a full word. Separate inner
width/height values and assignments in their actual draw arguments recover
the native lifetimes: 412/351 becomes 432/28, then 432/12, 432/10 and 432/0.
No register binding is needed. Dimensions below two, wrapped endpoints and
other unchecked geometry retain their original behavior.

The four original incoming frame-drawer sites besides quantity setup remain
unconverted at `0x21B9C`, `0x343EC`, `0x347EC` and `0x4311C`. Their existence is
static evidence, not reconstructed source or runtime coverage. The selected
and fixed frame-resource producers are included in the current proof context.
The five new functions have real changed-source and strict diagnostic controls;
layout/type checks distinguish byte equality from a correct word rectangle
prototype, signed value view and word geometry contract. Prior failed sources,
the former narrower private rectangle declaration and raw comparisons remain
local evidence. Whole-ROM equality is checked separately at publication.
