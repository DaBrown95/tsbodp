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

The second phase clears flag `+0x747`, invokes the original daily counter
reset, resets accepted actor-entry values rooted at world `+0xDC`, invokes the
original relation-value adjustment at world `+0x30`, clears byte `+0x73D`, and
resets the hour interval. On a signed day divisible by seven it calls the
original weekly actor-entry operation. The signed remainder helper is the
established `__modsi3` at `0x0804CE08`; the explicit signed-short result test
preserves the observed narrowing. The weekly operation, counter reset,
cycle-value provider and relation adjustment remain explicit original regions.
Useful private child candidates receive no source-coverage credit in this batch.

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
