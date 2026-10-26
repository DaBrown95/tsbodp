# Search-cost queue and daily clock handoff

Three connected matching functions add 360 complete C extent bytes:

| Function | ROM address | Extent |
| --- | --- | ---: |
| `frame_search_take_lowest_cost` | `0x0803C42C` | 108 bytes |
| `display_time_reset_hour_interval` | `0x0803C538` | 84 bytes |
| `display_time_day_event` | `0x0803CA6C` | 168 bytes |

The first function is another operation on the established search queue. It
uses the same two queue roots at `0x03007310`, two free-list roots at
`0x03007320`, 24-byte intrusive nodes and 16-byte copied payload as the
accepted priority-based pop. This function compares the unsigned cost byte at
node `+0x10`; the other compares priority at `+0x14`. It copies the selected
payload, updates the selected payload's queue tail and releases the node through
the accepted pool helper. The distinction follows the actual byte loads, not
the adjacency to clock functions. The first node's next pointer is read before
the later null check, preserving the original behavior. Empty-list safety,
arbitrary queue indices and runtime use are unproved.

The accepted world-clock updater at `0x0803C498` calls the new day event after
a day carry. The day event reads the clock's signed day at world root
`0x03003950 + 8`, matching the existing clock alias `0x03003958`. A separate
same-address access view observes stage `+0x440`, counters `+0x741/+0x742`,
cycle value `+0x744`, signed cycle byte `+0x746` and flag `+0x747`. These names
describe this path's operations; they do not establish a complete world layout
or the value's gameplay meaning. Above stage one the two byte counters advance.
A cycle other than the signed sentinel -1 decrements, calls the original
cycle-value provider on reaching zero and resets to seven. Explicit byte and
signed-byte reads retain the original differing widths.

The second phase clears flag `+0x747`, invokes the original four-word flag
reset, resets accepted actor-entry values rooted at world `+0xDC`, invokes the
original relation-value adjustment at world `+0x30`, clears byte `+0x73D`, and
resets the hour interval. On a signed day divisible by seven it calls the
matching weekly actor-entry operation. The signed remainder helper is the
established `__modsi3` at `0x0804CE08`; the explicit signed-short result test
preserves the observed narrowing. The weekly operation now has the matching owner below. The three other
direct daily providers are reconstructed below; their historical private
receipts retain their previous aliases and extent evidence.

The interval reset clears two eight-byte clock records rooted at `0x03004074`.
A primary-generator draw from zero through 99 at most 29 enables the interval.
It draws a first hour from zero through 22, then calls the same generator with
first-plus-one and 22, and writes both signed hour bytes after those calls.
Otherwise it clears the enabled byte. First hour 22 therefore causes a call
with bounds 23 and 22; the reconstruction preserves it and adds no ordering
guard. The observed interval prefix is seventeen bytes. Structure tail padding
does not establish its allocation, and its scheduling or gameplay role is
unknown.

All three sources use ordinary C without register bindings. The two clock
functions explicitly request the original zero tail alignment; this contains
no instruction body. Full literal pools and alignment match, and genuine
changed-source comparison, threshold and cycle-reset controls each reject with
one differing byte.
Raw source failures, full comparison bytes and native object/link receipts stay
in ignored reports. These static and compiler results are separate from
whole-ROM equality and runtime behavior.

## Direct daily providers

Three further directly called providers add 168 complete matching C bytes:

| Function | ROM address | Extent |
| --- | --- | ---: |
| `display_time_add_cycle_value` | `0x0801BCD0` | 28 bytes |
| `display_time_reset_daily_counters` | `0x08010A80` | 44 bytes |
| `display_menu_relax_relation_values` | `0x08035E9C` | 96 bytes |

The first adds 500 to the unsigned halfword at world `+0x744`, retaining the
observed narrowing on its store. Its cycle-reset caller motivates `cycle_value`;
the value's gameplay role is unresolved. The second clears four saved flag words
at `+0x714`, `+0x718`, `+0x71C` and `+0x720`. These offsets refine unknown
bytes in the same access view without moving any previously observed field.
Neither function receives an argument. The old unnamed child aliases remain
in historical private receipts; their execution addresses are unchanged.

The relation provider reuses the published 104-byte relation-values view,
whose 24 four-byte records begin at `+8`. It reads each signed value at
`+9 + 4 * index`, skips zero and the -128 initialization sentinel, and draws
zero through two with the established primary generator. Positive values
decrease; negative values increase; a sign crossing clamps to zero. The cursor
advances within the actual relation-values storage, and the signed character
accesses preserve the byte widths without a fabricated scalar representation.
A named loop sentinel declared before the character cursor recovers the
original constant initialization order in ordinary C, with no register binding.
Natural typed-record and other declaration-order attempts remain preserved as
failed full comparisons. These operations justify the provisional relaxation
name, not a tested daily relationship or probability model.

The three children plus the earlier queue/clock batch comprise six functions
and 528 distinct C bytes. The new child controls change the increment, final
flag-word store and record loop bound, rejecting by 18, 16 and one byte
respectively. Both previous daily-header consumers remain exact and each
rejects its real control by one byte after the final header refinement.
The weekly actor-entry reconciliation at `0x0802005C` now has a matching
source owner, qualified below. Its scan reconciles flag bits with kind-125
secondary records and clears at most one bit per invocation. Runtime invocation,
list consistency and complete table/index domains remain unproved.

## Daily flag object handoff

Two further connected functions add 320 complete matching C bytes:

| Function | ROM address | Extent |
| --- | --- | ---: |
| `frame_step_daily_flag_object` | `0x08010974` | 268 bytes |
| `frame_test_daily_flag` | `0x08010B14` | 52 bytes |

The original factory at `0x08010874` installs the first function at object
`+0x88`, and calls the second with the payload-derived index stored at object
`+0x68`. The factory is reconstructed in the connected closure below. The query returns the
actual masked word from world `+0x714` for indices up to 31 and `+0x718` after
subtracting 32 otherwise, without normalizing to a Boolean. The update clears
a bit in the corresponding second pair at `+0x71C/+0x720`. Existing save
read/write functions serialize these same four words through the alias
`g_save_flag_words` at `0x03004064`. This evidence corrects the shared field
label to `daily_flag_words`; the previously published reset function retains
its historical `display_time_reset_daily_counters` name and clears those flags.
No gameplay counter interpretation is asserted.

The callback's state one delegates to the matching actor dispatcher. In state
18, variant zero stops its owner, sets the owner's state to zero, faces the
owner toward this object, requests animation 32 and enters variant 14 with an
eight-count timer. Variant 14 decrements the timer until -1, adjusts the entry
counter rooted at world `+0xDC` for this object's halfword subtype, clears
object flag one, emits cue 48 and enters variant 15. Variant 15 waits for the
owner's observed animation-completion flag `0x00400000`, clears the indexed bit
in the second flag pair, then restores this object's state one and flag two,
and the owner's state 16 and animation one. Other observed states and variants
perform no action. The owner field at `+0x64` and index at `+0x68` are a
selector-specific view and do not replace the differently used fields in the
shared actor view.

The query uses ordinary C with no register constraints. The callback has two
branch-local semantic R2 constraints for the actual world base address; these
lifetimes end before any ABI call. Integer address construction retains the
observed separate base and field-offset calculations. No instruction body,
output edits, artificial volatility or fabricated data are used. The full
extents include original literal pools and explicit zero alignment. Real source
controls change the timer initialization and query's bank boundary. All five
previous importers of the refined daily header are recompiled with their real
controls; their bytes remain unchanged.

This path adds static creator/callback evidence, not gameplay observation.
Owner validity, subtype table bounds and an overall index domain of zero
through 63 remain unproved; no new guards are invented. The unsigned source
shift describes the bank operation within that domain, while the complete
pinned-compiler comparison preserves the original machine bytes. The flag
setters, factory and interaction callback are reconstructed below; the weekly
reconciliation is reconstructed below.

## Daily flag factory and interaction closure

Five directly connected producers add 480 complete matching C extent bytes:

| Function | ROM address | Extent |
| --- | --- | ---: |
| `frame_create_daily_flag_object` | `0x08010874` | 256 bytes |
| `frame_test_daily_pending_flag` | `0x08010B48` | 52 bytes |
| `frame_mark_daily_flag` | `0x08010B7C` | 52 bytes |
| `frame_mark_daily_pending_flag` | `0x08010BB0` | 52 bytes |
| `frame_daily_flag_interact` | `0x08011414` | 68 bytes |

The factory pointer word at `0x0804F2B8` is slot 16 relative to the established
factory-table root `0x0804F278`. This identifies one table entry; it does not
establish the full table's length. The factory obtains a 320-byte scene object
through the matching allocator and reads a serialized payload prefix: word ID,
signed halfword positions at `+4/+6`, byte subtype at `+8` and flag index at
`+9`. It stores the narrowed ID and subtype and keeps the index at object `+0x68`.

The factory uses the first flag pair at world `+0x714/+0x718` to choose between
reusing a stored result and drawing another chance value. If present, it normalizes the masked result from the second
pair at `+0x71C/+0x720` into an actual byte Boolean. Otherwise a primary chance call
using the subtype's byte threshold may set the second pair, and the first pair
is marked regardless of the draw result. Both queries return masked words,
not normalized Boolean values. Both setters use unsigned word OR operations
and retain the original bank-selection and index subtraction.

An active result places and configures the object, sets flags `0x000E0415`,
installs the matching daily callback at `+0x88`, starts state zero/variant one,
clears its owner pointer, selects an animation and palette from subtype tables,
sets OAM byte `+0xD5` bits two and three, and installs the new interaction at
`+0xC8`. The inactive branch removes the allocated object and returns null.
The factory has no original null-allocation check, and none is added. Position
shifts explicitly use unsigned values before their existing signed word ABI,
retaining the original bit representation without a negative signed shift.

The interaction's original entry saves R1 as its owner. It accepts an owner
whose ID is zero and state is 16 when player-zero input mask 1 is pressed,
sets this selector to state 18/variant zero, records the owner and clears input.
This enters the previously reconstructed timer, cue and completion handoff.
Its role header therefore uses two `FrameObject *` callback arguments and a
local selector overlay. The matching copied collision pass also calls its
`+0xC8/+0xCC` callbacks with two objects. This static handoff supports this path's
contract; it does not prove every invocation or runtime collision. The generic
actor role's existing one-argument callback declaration remains provisional
and is not widened by this batch. The daily `+0x88` callback uses the shared
single-object declaration.

The chance, animation and palette roots are `0x08051B10`, `0x08051AAC` and
`0x08051AFC`. Their spacing is consistent with five 16-byte animation entries
and five palette words before the next roots, but the source leaves the arrays
unsized. The complete chance-table extent and the payload subtype/index domains
remain unresolved; no fabricated bounds or extra guards are introduced.
The C `1u << index` operation is defined only when the normalized count is below
32. For byte-derived factory indices 64 through 255, that count lies outside the
C domain whereas the original native variable LSL yields zero. The factory's
valid index domain remains unestablished; arbitrary full-word query inputs are
not covered by that native byte-domain observation. The
nearby second-pair clear helper is now reconstructed below. The current mapped
graph and a full-ROM Thumb call-pattern scan found no inbound caller; indirect
or runtime use remains unresolved.

The factory, pending query and interaction use ordinary C without register
constraints. Each setter has two branch-local R2 bindings for its actual world
base address. Those values end within the chosen bank calculation. Full extents,
literal pools and original zero tail alignment match; controls changing factory
flags, bank boundaries and the accepted owner state all reject. The seven-function
flag-object path totals 800 C extent bytes and joins the daily flag reset and
save-word accessors. Whole-ROM equality and gameplay behavior remain separate
claims. The weekly entry reconciliation is reconstructed below.


## Independently bounded pending-flag clearer

The [clear helper](../src/frame/frame_clear_daily_pending_flag_unrooted_10be4.c)
at `0x08010BE4` reproduces its complete 52-byte extent: 38 instruction, twelve
literal and two internal alignment bytes. Unsigned indices through 31 select
world word `+0x71C`; larger indices subtract 32 and select `+0x720`. It clears the
selected bit in the existing `DisplayDailyWorld.daily_flag_words[2..3]` owner.
The chosen one-word input and void result remain provisional without an incoming
caller. Index zero through 63 and live canonical-world backing are conditional;
no guard or universal full-word shift contract is added.

Both branch-local R2 constraints refer to the actual world-base value and end
at their address calculations without a call. They reuse the adjacent setter's
supported compiler constraint; they do not identify an original register
annotation. Normal and strict full comparisons and real clear-to-set controls
pass, alongside actual-definition and owner-layout checks. These results replace
one estimated source row and add no mapped extent, execution or gameplay claim.

## Weekly entry reconciliation

The [weekly worker](../src/display/time_weekly_entries.c) at `0x0802005C` owns
all 108 bytes from C: 108 instruction bytes, no literals or alignment. The
condition-one check gates a scan of the eight captured flag bits. For each set
bit, it samples the secondary-list pointer, searches the current capacity for
a kind-125 record with matching value, then observes capacity again. If the
index equals that final capacity, it rereads the flag byte, clears that bit and
stops. No additional guard or observation is introduced.

Actual byte-load results use QI register phases, so GCSE does not replace the
native repeated capacity and entry-pointer reads with cached pseudo values.
Only the existing secondary-pointer read is expressed through a volatile-
qualified compatible pointer-object lvalue. This preserves the R0 load and
R2 copy; a volatile local register failed to do so. Later list reads remain
ordinary accesses whose separate emitted loads are pinned compiler facts,
without a source-level guarantee of asynchronous freshness. No historical
qualifier or IRQ-writer population is inferred.

The record offset is computed in the target's 32-bit integer-address model;
the intermediate offset pointer is converted back before dereference. The
actual initializer installs list 14, and the maintained day-event caller passes
world plus `0xDC` on a day divisible by seven. Valid context/list/record backing,
aliases, later writers and complete incoming/runtime populations remain premises.
Every local is initialized on its use paths; no original-bug exception is needed.

Normal and strict-aliasing positives match the full native extent. Changing
kind 125 to 124 rejects both by one byte. The actual 168-byte day-event caller,
44-byte condition provider, 104-byte initializer and 48-byte capacity-search
control all match and reject their existing controls in both profiles, retaining
364 prior bytes. The full-ROM and progress gates verify source integration;
this adds no runtime execution evidence or complete code denominator.
