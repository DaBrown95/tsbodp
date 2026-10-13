# Connected clock arithmetic and selection

The initial arithmetic/selection batch added eight Thumb functions and 760
matching C bytes. The previously accepted
20-byte day-remainder helper is renamed with no coverage gain, making this a
nine-function, 780-byte connected clock path. The menu choice initializer,
scene initializer, actor eligibility and script interval command establish its
connections; whole-ROM matching and static access do not establish runtime
chronology, save compatibility or gameplay behavior.

| Function | ROM entry | Complete extent | Coverage |
| --- | --- | ---: | --- |
| `display_time_add` | `0x080102D8` | 344 | New |
| `display_time_compare` | `0x080106C0` | 112 | New |
| `display_time_clear` | `0x08010730` | 16 | New |
| `display_time_copy` | `0x08010740` | 12 | New |
| `display_time_copy_add` | `0x0801074C` | 24 | New |
| `display_time_equal` | `0x08010764` | 128 | New |
| `display_time_period` | `0x080107E4` | 36 | New |
| `display_time_weekday` | `0x08010808` | 20 | Existing, renamed |
| `display_time_in_range` | `0x0801081C` | 88 | New |

Returns and following function prologues bound these extents. Each is linked at
its original ROM address and includes its alignment. No copied-RAM address or
ARM instruction body is part of this batch.

## Record and arithmetic evidence

The eight-byte access view contains signed day halfword at `+0`, signed hour,
minute, second and tick bytes at `+2/+3/+4/+5`, and an uninterpreted halfword at
`+6`. Both typed copies transfer two complete words; the final halfword is
copied and cleared but not interpreted by this family. The observed menu and
shared-state addresses are word aligned. This view does not inventory all
clock storage or prove alignment and bounds for every unconverted caller.

The add routine processes the lower components with radices 30 ticks, 60
seconds, 60 minutes and 24 hours. Negative values borrow and excessive positive
values carry into the next component. Each stored byte is narrowed before its
signed comparison, preserving the original compiler's wrapping behavior.
Flags 1/2/4/8 report the carry or borrow into second/minute/hour/day. The delta's
day and final halfword are ignored; this is not a general addition of all
record fields. Large offsets, overflow and runtime valid ranges have not been
validated beyond the matching code's actual accesses and conversions.

Higher delta bytes are captured after a negative tick borrow loop, or before a
positive tick carry loop, preserving the observed order even if records alias.
Ordinary C closes the algorithm except for a short-scoped `r1` binding on the
current-hour sum. That value exists only within the addition/store block, has
no overlapping constrained value and crosses no call. The code contains no
instruction-body transcription or output manipulation. A natural unbound
version of the full routine has the correct 344-byte size but eight register
bytes differ; both that attempt and the earlier 348-byte attempt are retained.

The menu initializer at `0x080180D4` passes current clock `0x03003958`, constant
`0x08D70D48`, and selection record `0x03003D68 + 4` to copy/add. The constant has
hour 24 and all other components zero. This supersedes the former resource-
effect name: the operation copies the current clock and sets a next-day
deadline. Copy/add writes through selection offset `+11`; the menu header now
captures this twelve-byte observed view without claiming complete storage bounds.
The first four clock bytes correspond
to the menu persistence/comparator's previous `major/minor/part` ordering names.
The initializer still differs by six scheduling bytes and receives no coverage.

## Comparisons, periods and affected callers

Compare returns 0 for equal selected fields, 1 for earlier and 2 for later.
Masks 8/4/2/1 select day/hour/minute/second in that order. Equality additionally
checks tick for mask 16 and keeps examining selected components after a
difference. The range helper includes both ends; descending endpoints describe
a wrapping interval. Equal endpoints return true for every compared clock,
as the original control flow does, rather than defining a single-point range.

Period returns 3 for hours at most 5 or above 19, 0 for 6 through 9, 1 for 10
through 16, and 2 for 17 through 19. The scene context word at `+4` is therefore
refined from the prior resource-pointer inference to an unsigned period
selector. Its unconverted audio getter at `0x08026A9C` explicitly switches on
selectors 0 through 3 before accessing scene audio data, and is now named
`scene_audio_for_period`. The scene initializer and need-effect audio restore
use that full-word selector without changing any address or layout.

The existing signed halfword remainder helper is now `display_time_weekday`;
its `% 7` and signed `short` return are unchanged. Actor eligibility uses the
signed hour as table row and the byte-narrowed weekday as column. No clamp or
validation has been introduced for negative components. The earlier world-
coordinate labels were provisional and are superseded by the connected clock
evidence.

The resource interval command fills hour/minute in two eight-byte default
clock records and calls the range helper with mask 6 and current clock
`0x03003958`. Its explicit unsigned-byte cast preserves the original caller's
return observation although the reconstructed callee returns a complete word.

## Clock text formatter

`display_time_format` at `0x08010430` adds a complete 656-byte Thumb extent,
including its 51-entry compiler-generated switch table, literal pools and
alignment. The original return at `0x080106B4`, final pool through `0x080106BF`
and following compare entry bound it. The source expresses format parsing and
decimal conversion in ordinary C, with no register constraints or embedded
instruction/table data. The arithmetic/selection core plus formatter therefore
contain ten matching functions and 1,436 bytes, including the existing renamed
20-byte weekday helper; these batches added nine functions and 1,416 bytes.

The input text ID selects a string through the published lookup API. Nonzero
game option byte `0x03005D9A` changes requested text ID 6225 to 6227. A dedicated
same-address options access view covers the eleven observed bytes; the audio
view at the same base only interprets its volume bytes at offsets 8 and 9. The
format option's wider storage and runtime meaning remain provisional.

A preliminary scan stops at the first `@a` or `@A`, selecting twelve-hour
output. Tokens `@D`, `@H`/`@h`, `@M`/`@m`, `@S`/`@s` and `@a`/`@A` select day,
hour, minute, second and AM/PM letters. Day emits up to three decimal positions
and consumes a following `D` if present. Hour/minute/second each consume one
additional format byte unconditionally; no syntax validation was added. AM/PM
hour zero emits 12, hours over 12 subtract 12, and the leading position is a
space below ten. Other characters are copied from the loop's cached current
byte. Unknown tokens normally emit nothing; option zero with text ID 6227 also
copies the current token byte after dispatch. These observations do not prove
all original strings follow the apparent doubled-token convention.

The signed division and remainder helpers at `0x0804C8C8` and `0x0804C8CC`
execute BIOS call 6; the latter moves the remainder from `r1` to the return
register. Both remain explicit unconverted low-level dependencies and receive
no C credit here. The formatter returns its original destination pointer,
terminates with zero and has no output-length argument. Its reads establish
signed component access but do not validate negative or oversized values,
string availability or runtime destination capacity.

Static mapped callers occur at `0x08005724`, `0x0801E798`, `0x08025570`,
`0x08026E6C`, `0x08028DFC` and `0x08029574`. The first and fifth combine countdown updates with text drawing and now match
as the connected producers described below. The other callers remain
unconverted; none of this static linkage establishes runtime execution. The compiler emits the bounded switch from
the C cases, rather than copying the original table into source.

## Countdown producers and map clearing

Three further matching functions close the formatter's immediate countdown
producers and their rectangle-clear dependency:

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `display_time_step_countdown` | `0x08005724` | 124 |
| `display_time_update_scene_countdown` | `0x08028DFC` | 192 |
| `display_clear_background_rectangle` | `0x0800D7E4` | 24 |

The shared countdown at `0x03003150` is distinct from the world clock at
`0x03003958`. The short producer adds a delta whose tick is -1, then chooses
palette 6 when minute is at most zero and second at most five, otherwise
palette zero. It formats text ID 6226 into a twenty-byte local array and draws
at (46,36) or (46,74), selected by shared frame flag 32. These are observed
updates and coordinates, not proof of callback frequency or real-time rate.

The scene producer reads scene byte `+18` and flags byte `+21` through the
pointer at `0x030043F4`. Bit 1 in a 28-byte ROM definition record enables the
path. Dirty bit 4 draws text ID 6227 into a twenty-byte local array after
clearing a background rectangle, chooses palette 6 when hour is at most zero
and minute at most ten, then clears that dirty bit. It next adds a delta whose
second is -1; any carry/borrow flag returned by the matching add routine sets
dirty bit 4 again. An eight-byte layout record supplies unsigned x/y halfwords
and left/top/width/height bytes. Table bounds, scene validity, shared-state
ownership and actual update cadence remain provisional.

The 24-byte clear wrapper passes the five rectangle arguments and tile zero
to the published background constant-fill function. It is a connected C
dependency, not low-level glue. All three routines use ordinary C and no
register constraints. Declaring the definition-table base before the scene
index preserves its observed lifetime and closes the scene producer's earlier
17-byte mismatch.

The short producer's original return at `0x0800579E` and next prologue at
`0x080057A0` bound all 124 bytes, including the intervening pool; the earlier
static inventory's 82-byte envelope had omitted the post-pool return path.
The scene producer returns at `0x08028EA2`, with its final pool ending before
`0x08028EBC`. The clear wrapper ends at the following fill function entry
`0x0800D7FC`. Extents, pools and alignment are verified independently of these
static boundary explanations.

This formatter/countdown batch adds four functions and 996 C bytes. Combined
with the prior arithmetic/selection core, the connected matching clock and
countdown path comprises thirteen functions and 1,776 bytes; 20 of those bytes
were previously accepted and merely renamed.

## Verification and remaining work

All eight new canonical sources match their complete extents and reject real
compiled controls. Changes to the tick borrow radix, day mask, clear width,
copy source, copy/add delta, initial equality value, period threshold and range
return reject with 1, 1, 1, 12, 17, 113, 1 and 38 differing bytes respectively.
The renamed weekday also rejects its divisor control with one differing byte.
All nine published menu consumers match and reject their controls after the
same-offset selection record refinement to twelve observed bytes.

The five modified published callers—scene initialization, the interval command,
actor eligibility, actor setup and need-effect audio restore—match and reject
their controls with current headers. A further 132 accepted consumers of the
changed scene, script and actor headers also match and reject their controls.
Ignored raw bytes, disassembly, exact source snapshots, commands and failures
are retained under `reports/agents/display_audio/catalog-presentation/`; the
ready metadata is `time-core-ready.json`. Historical receipts retain their old
names and bytes.

The 168-byte choice initializer and 1,112-byte secondary menu stage remain
unconverted connected consumers. The producers that advance shared clock state and render its formatted text
are useful next targets. These
boundaries and clock names are evidence-led inferences, not claims of an
original source API or tested runtime scheduling.

The formatter's canonical public source matches all 656 bytes and rejects an
actual compiled AM/PM threshold mutation (`hour <= 11` to `hour <= 10`) with one
differing byte. It has a new dedicated header and no accepted prior caller
requires a prototype change. The initial 668-byte attempt and final 656-byte,
one-byte cached-character attempt remain intact alongside the complete positive
and control evidence in `time-format-ready.json` and the ignored report tree.

Both countdown producers and the clear wrapper match their full canonical
extents and reject actual compiled mutations of the warning threshold, dirty
flag mask and cleared tile respectively, each with one differing byte. Their
proofs join the formatter in `time-format-ready.json`. The first short-producer
attempt (124 bytes, six differing scheduling bytes) and first scene-producer
attempt (192 bytes, seventeen differing bytes) remain intact. No pre-existing
accepted source requires a prototype or header change for this batch.
