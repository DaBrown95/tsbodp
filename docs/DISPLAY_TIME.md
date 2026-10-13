# Connected clock arithmetic and selection

Eight new Thumb functions add 760 matching C bytes. The previously accepted
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
unconverted connected consumers. The adjacent clock-text formatter and the
producer that advances shared clock state are useful next targets. These
boundaries and clock names are evidence-led inferences, not claims of an
original source API or tested runtime scheduling.
