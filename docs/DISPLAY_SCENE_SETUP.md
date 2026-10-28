# Scrolling scene setup

Nine connected functions add 1,812 bytes of matching C: the 252-byte setup at
`0x0800EB90`, its 16-byte fill wrapper at `0x0800D6B8`, and the 672-byte input
selector at `0x0800EC8C`, followed by the 112/108-byte previous/next group
operations at `0x0800F39C/0x0800F40C` and the 100-byte page control update at
`0x0800F478`, followed by the 40-byte bitset predicate at `0x0800EB68`,
308-byte object creation at `0x0800F168` and 204-byte label redraw at
`0x0800F29C`. All complete linked extents match, including the
setup's final eleven-word literal pool through `0x0800EC8C`. Actually compiled
changed-source controls reject for all nine functions. The names describe observed display operations; the scene's
gameplay role and original names remain unknown.

The setup selects display mode zero, enables OBJ, configures backgrounds
three, one and zero, fills backgrounds one and zero, then loads two background
resources through the accepted loader at `0x0800DA20`. It loads a resource
palette and sixteen alternate palette entries, then sets background three's
x/y velocity to `0x10000` through `display_set_background_velocity`. This
connects the setup to the accepted background state/update/VBlank path.
It also clears selector state, calls preparation routines
and the reconstructed list population, object creation and page control update,
clears one owner's flag bit and initializes a counter to four. The inferred
scrolling-scene name does not identify the assets or assert visible behavior
under every display or commit state.

The fill wrapper forwards its background index and halfword tile argument to
`display_fill_background_map`, using zero for its palette/color argument.
Its tile-fill dependency at `0x0800D730` now also has
[matching C](../src/display/background_character_fill.c), including the full
116-byte extent and real changed-source controls. This closes that source
dependency without establishing runtime VRAM bounds.

## Partial views and boundaries

The request view at `0x03004350` overlaps the existing scene request. It
retains mode, scene and parameter at offsets `4/8/12` and exposes observed
word accesses at `0x10/0x14`. The reconstructed input selector at `0x0800EC8C`
reads those last two words as a state and a decrementing timer; this is static
evidence, and their public field names remain explicitly unknown. The view
does not establish an array stride or allocation ownership.

The two setup owner pointers at `0x030043B0` address objects with an ID halfword at
`8` and flags at `0x0C`, agreeing with the reconstructed frame command view.
The setup uses the second pointer. The connected navigation operations also
access four more pointers at offsets `8/12/16/20`; the navigation header exposes
six observed slots. Object creation and label redraw extend those observed
accesses through pointer slot fourteen, at offset `0x38`. Both shared
declarations leave the array unsized: fifteen observed slots are not proof of
a complete allocation or an upper bound for other object-table users. The setup clears three bytes at
`0x030018B8/9/A`; the selector and unconverted redraw routines provide provisional
count/selection/page interpretations.
The three adjacent ROM control words at `0x0804F834/8/C` have separate
symbols because independent global member loads match the observed literal
addresses. The resource and palette symbols refer to original unconverted
ROM data; no asset data is included in source.

The setup's unconverted calls keep address-based names for `0x0801AE2C`,
`0x0800EF2C`. The address-based list-population alias at `0x0800F034` now
has a complete source owner, described below. The address-based
`display_scene_stage_0800f168`, `display_scene_stage_0800f29c` and
`display_scene_stage_0800f478` call aliases now resolve to the reconstructed
object creation, label redraw and page control update; the remaining aliases imply no
implementation or runtime claim. The connected selector's old mapped
626-byte envelope ended inside a literal pool at `0x0800EEFE`, producing a
false additional entry. Its branch targets continue through the return at
`0x0800EF24` and final literal at `0x0800EF28`; the candidate boundary is
`0x0800EC8C..0x0800EF2C`, 672 bytes. The source matches that complete extent;
the earlier split is not used to omit the shared tail or pool bytes.

## Input selection and handoff

The selector reads the accepted per-player pressed-key array at `0x03004228`
using the local-player byte at `0x03004111`. State zero decrements the word
at request offset `0x14` and, when it becomes unsigned `-1`, selects state one
and calls the accepted transition wrapper. State one invokes the previous/next
group operations for up/down, adjusts an owner's ID and frame variant when
needed, and redraws when the selected group changes. State two handles an
item index in request offset `0x0C` and a page byte at `0x030018BA`, redrawing
the selected item or page through explicit unconverted calls.

The group operations reject zero on decrement and five on increment, then
adjust request offset `8`. They update flag bit one on pointer slots two/three
at the observed edge cases, with an additional ID check (`0xB1/0xB2`) on slot
zero. Both redraw page zero, clear the page byte, update page controls, redraw
the selected item's details and issue audio cue zero. The checks do not reject
arbitrary out-of-range group values. The page control update clears or sets
flag bit one on slots four/five for the first and signed last page, using the
same count expression as the selector. These flag changes are static behavior;
they do not prove that the corresponding objects appear on screen.

Page navigation uses the signed last-page expression
`((count + 3) >> 2) - 1`, with count read as an unsigned byte from
`0x030018B8`. The source retains the signed comparison, including its
negative limit when count is zero. It does not add resource bounds or count
validation. The item increment path permits values up to three; the decrement
path hands off at zero. These observed comparisons do not establish the
valid range of every underlying data set.

After the state action, nonzero states handle a scene event and confirmation
inputs. Confirmation toggles states one/two, changes the active flag on the
two owners and resets/redraws the item/page state when entering state two.
The body uses separate confirmation tests with a shared C label. A combined
logical OR made the compiler combine masks and did not match. Indexed input
expressions retain the observed load reuse within each branch path. Two C
register constraints on the page-count byte and signed last-page limit
preserve the pinned compiler's allocation; they constrain semantic values
and insert no instruction body. Ordinary local/type/helper trials remain
preserved as failures.

## Object and label lifecycle

The object creation routine builds ten scene objects through the reconstructed
`frame_create_scene_object`, with IDs `0xB1/0xB3..0xBB`, then five label objects
through the explicitly unconverted factory at `0x080282D4`, with IDs
`0xBC..0xC0`. It clears flag bit one on pointer slot two. The four item objects
at slots six through nine are created in a signed-byte descending loop, with
subtype `0xE2`. The factory's four arguments retain the canonical full-word
types; the observed stored ID/subtype narrowing belongs to its implementation.
The five label objects each enter transition state eight. Creation assumes
successful returned pointers; no null checks have been added.

One label receives the address of a buffer at `0x03003960`. A partial text
state view starts at `0x03003950`, exposing a word at offset four and the
buffer address at offset sixteen. Its `buffer[1]` member represents that
observed address, not a buffer size or a string-length bound. The word's
`text_id` name is inferred from its handoff to the unconverted routine at
`0x0801B1CC`. Label resources use the adjacent ROM word table at `0x0804F81C`;
its six observed indices come from navigation, and its original data remains
unconverted. The text lookup at `0x08045008` retains inferred types and remains
an explicit unconverted dependency. The label factory and its text-object
allocator are reconstructed in the [connected lifecycle batch](DISPLAY_SCENE_LIFECYCLE.md).
That batch's table clear extends the observed pointer prefix to seventeen
slots, while retaining unsized declarations and no allocation-bound claim.

Label redraw changes nonnull old objects at slots thirteen/fourteen by clearing
flag bit one and setting bit two, then replaces both pointers and assigns state
eight to the new objects. It uses the local player's pressed up key to choose
neighbor indices, with special zero/five edge behavior. The source retains
unsigned-byte wrapping and supplies no general input validation. The two new
label pointers and their transition calls connect this routine to the accepted
frame and transition paths; object retirement and visible labels still need
runtime evidence.

The bitset predicate rejects indices above 148 and tests the selected bit of
the caller's word array, returning an unsigned byte normalized to zero/one.
Its redraw callers statically walk 149 catalog records
at `0x080616CC`, each 24 bytes, filtering category and an ID `0x13D` exclusion.
The list-population caller now has matching C; other inferred caller layouts
remain analysis evidence.
The predicate does not validate the supplied pointer or the underlying array
allocation. Object creation, label redraw and this predicate use ordinary C
without fixed register constraints.

## Catalog list population

The complete 308-byte source at `0x0800F034` adds one matching function to this
connected path: 280 instruction bytes and seven literal words, without padding.
It clears the active bit on four existing item objects, scans 149 24-byte catalog
records, excludes ID `0x13D` and filters the request category and enabled bitset.
It populates up to four eligible records after the page offset, refreshes their
objects, and fills any remaining slots with ID `0xE2` under the original count
comparison. The page still uses its low byte, and the source adds no pointer,
allocation or catalog-domain validation.

Two local word pairs hold only the actual clear-loop values: flags/object and
mask/next-slot pointer. After that loop, the low words change role to the
eligible-count and catalog addresses. Each active field is assigned before its
own read; the source never reads an uninitialized whole pair. Real scalar input
lifetimes preserve the native address materializations and partial-field
transfers. This representation reuses the successful lifetime findings from
catalog confirmation and window packing without adding game observations.
The initial related 312-byte experiment exposed PRE hoisting; composing the
actual full-word inputs with the surviving partial assignments restores the
complete 308-byte function. These declarations establish a matching source
representation, not the historical source's local types.

The existing canonical byte-return predicate, refresh and variant providers and
all shared headers remain unchanged. Changing the scan bound from 148 to 147
rejects by one byte. The normal pinned compilation, all changed-source controls
and the complete ROM pass. No new indirect-target population or runtime route
is established by this source gain.

## Preserved comparisons

`reports/agents/display_audio/background_motion/scene/ready.json` and
`navigation-ready.json` and `redraw/ready.json` in the same directory are the ignored local receipt
indices. The public source/header closure was compiled
again after promotion. Changing the x velocity from `0x10000` to `0x20000`
rejects with a 256-byte output and 104 differing/missing/extra bytes; changing
the wrapper's zero palette argument to one rejects by one byte. The selector's
changed item-increment threshold from two to one also rejects by one byte.
The navigation controls change the decrement's blocking group from zero to
one, the increment's blocking group from five to four, and the page rounding
constant from three to seven; all three reject by one byte. Page-control
allocation uses the same two semantic C register constraints on count and
signed limit as the selector. The group operations use ordinary C locals.
The next controls reduce the predicate's maximum index from 148 to 147 and
change the initial object ID from `0xB1` to `0xB2`, each rejecting by one byte.
Changing the label redraw's boundary group from five to four produces 200
bytes instead of 204 and rejects by 100 differing/missing/extra bytes. The
navigation sources were recompiled with real controls after the shared pointer
declaration became unsized; all three positive extents remained exact.
All exact positives, raw outputs, commands, source/header snapshots and earlier failed
array-control, shared-zero and selector variants remain local. All source is semantic
C without embedded instruction bodies. Compiler
equality, full-ROM equality and runtime behavior remain separate claims.
