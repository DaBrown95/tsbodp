# Scrolling scene setup

Three connected functions add 940 bytes of matching C: the 252-byte setup at
`0x0800EB90`, its 16-byte fill wrapper at `0x0800D6B8`, and the 672-byte input
selector at `0x0800EC8C`. All complete linked extents match, including the
setup's final eleven-word literal pool through `0x0800EC8C`. Actually compiled
changed-source controls reject for all three functions. The names describe observed display operations; the scene's
gameplay role and original names remain unknown.

The setup selects display mode zero, enables OBJ, configures backgrounds
three, one and zero, fills backgrounds one and zero, then loads two background
resources through the accepted loader at `0x0800DA20`. It loads a resource
palette and sixteen alternate palette entries, then sets background three's
x/y velocity to `0x10000` through `display_set_background_velocity`. This
connects the setup to the accepted background state/update/VBlank path.
It also clears selector state, calls four unconverted preparation routines,
clears one owner's flag bit and initializes a counter to four. The inferred
scrolling-scene name does not identify the assets or assert visible behavior
under every display or commit state.

The fill wrapper forwards its background index and halfword tile argument to
`display_fill_background_map`, using zero for its palette/color argument.
That accepted map fill still calls the explicitly unconverted tile-fill
function at `0x0800D730`; the wrapper does not convert that dependency.

## Partial views and boundaries

The request view at `0x03004350` overlaps the existing scene request. It
retains mode, scene and parameter at offsets `4/8/12` and exposes observed
word accesses at `0x10/0x14`. The reconstructed input selector at `0x0800EC8C`
reads those last two words as a state and a decrementing timer; this is static
evidence, and their public field names remain explicitly unknown. The view
does not establish an array stride or allocation ownership.

The two owner pointers at `0x030043B0` address objects with an ID halfword at
`8` and flags at `0x0C`, agreeing with the reconstructed frame command view.
The setup uses the second pointer. It clears three bytes at
`0x030018B8/9/A`; the selector and unconverted redraw routines provide provisional
count/selection/page interpretations.
The three adjacent ROM control words at `0x0804F834/8/C` have separate
symbols because independent global member loads match the observed literal
addresses. The resource and palette symbols refer to original unconverted
ROM data; no asset data is included in source.

The setup's unconverted calls keep address-based names for `0x0801AE2C`,
`0x0800EF2C`, `0x0800F034`, `0x0800F168` and `0x0800F478`. No implementation
or runtime claim is implied for them. The connected selector's old mapped
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

## Preserved comparisons

`reports/agents/display_audio/background_motion/scene/ready.json` is the
ignored local receipt index. The public source/header closure was compiled
again after promotion. Changing the x velocity from `0x10000` to `0x20000`
rejects with a 256-byte output and 104 differing/missing/extra bytes; changing
the wrapper's zero palette argument to one rejects by one byte. The selector's
changed item-increment threshold from two to one also rejects by one byte.
All exact positives, raw outputs, commands, source/header snapshots and earlier failed
array-control, shared-zero and selector variants remain local. All source is semantic
C without embedded instruction bodies. Compiler
equality, full-ROM equality and runtime behavior remain separate claims.
