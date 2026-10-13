# Actor group resources and palette composition

Eight connected C functions reconstruct 692 bytes, including literal pools and
alignment. They close the resource and palette dependencies of the accepted
actor factory, actor-part updater and scene-player factory. Names describe the
observed part indices and transfers; this is static/compiler evidence, without
a runtime or gameplay experiment.

| Entry | Function | Complete extent |
| --- | --- | ---: |
| `0x08001400` | `frame_clear_part_variants` | 24 |
| `0x08001450` | `frame_set_part_variants` | 40 |
| `0x080161AC` | `frame_load_actor_palette_pair` | 32 |
| `0x0803AD64` | `frame_bind_actor_group` | 164 |
| `0x0803AE08` | `frame_compose_actor_group_palette` | 116 |
| `0x0803AE7C` | `frame_compose_actor_group_alternate_palette` | 76 |
| `0x0803AEC8` | `frame_load_actor_group_palette` | 144 |
| `0x0803AF58` | `frame_load_actor_group_alternate_palette` | 96 |

The existing 12-byte animation-part record starts at object `+0x104`. The setter
writes its variants pointer at part `+8` and palette byte at `+1`; the clearer
only clears the pointer. Their incoming part index narrows to a byte. No part
count validation, flags update or tile allocation is added.

The binder reads definition byte zero to index the pointer tables rooted at
`0x08D72028`, `0x08D72038` and `0x08D72030`. The first supplies part zero's
variants, and the second additionally indexes by definition byte two for part
one. Both retain the object's OAM palette nibble. The third table supplies part
two's variants; its entry for the signed animation byte at object `+0x103`
controls whether the part is installed or its pointer cleared. The palette
lookup at `0x0806A250` uses that same signed index. A result of 254 selects the
game-state palette byte at `+0x42D`, otherwise the looked-up byte is used.
These table accesses do not establish valid mode, variant or negative-animation
domains. The source preserves the unchecked indexing and fallback.

The packed signed-eight-bit access view reproduces the observed byte load and
sign extension without changing the shared actor layout. Short register roles
retain the palette-table address and animation value during the lookup, then
reuse r0 for the variants offset. No value in a caller-clobbered register is
needed across an intervening call. Explicit 32-bit address arithmetic preserves
the observed add-operand order; pointer-first variants differed in one or two
bytes. These are compiler findings, not evidence for the original source spelling.

The palette composer builds 16 halfwords on the stack from the ROM root at
`0x080CCFFC`. First and last halfwords come from the common row. The intervening
ranges are selected independently from 32-byte rows:

| Definition byte | Destination/source byte offset | Bytes copied |
| ---: | ---: | ---: |
| 1 | 2 | 6 |
| 4 | 8 | 6 |
| 5 | 14 | 6 |
| 3 | 20 | 6 |
| 6 | 26 | 4 |

The existing `heap_copy` supplies each range, then the existing alternate
palette loader transfers all 16 halfwords beginning at slot shifted four.
The callee retains a full-word slot argument, without incoming byte narrowing;
the shared provisional prototype is corrected accordingly. The already accepted
callers continue to supply their observed palette nibble or zero. Palette-slot
bounds and visual meaning of individual color ranges remain unproven.

A view containing first/last halfwords around the 28-byte middle preserves the
observed stack-address lifetime. Its declaration after the row address closes
the remaining two-instruction scheduling difference naturally, without register
bindings in this body. Earlier plain-array, pointer-binding and compiler-profile
failures retain their complete raw comparisons under ignored actor-group reports.

Canonical sources, positive proofs and changed-source controls are
retained under `reports/audio-root/actor-group-canonical/`. The four new controls
change the fallback selector, transfer count, stored palette and cleared pointer.
The fresh current-header closure covers 232 existing functions; none is counted
again as new coverage. The ready manifest records their complete extents, source
and header snapshots, compiler/link commands and raw positive/control bytes.
Whole-ROM integration is verified separately at publication; the unconverted
renderer, sorter and other actor resource operations remain explicit.

The next four functions add 320 bytes to this resource path. The first composer
performs the same five range copies and common first/last-halfword writes into a
caller-supplied 32-byte palette. The alternate composer and transfer wrapper use
a second ROM row root at `0x080CD1FC`, also with 32-byte rows. They write the common
first halfword, then select these ranges:

| Definition byte | Destination/source byte offset | Bytes copied |
| ---: | ---: | ---: |
| 1 | 2 | 12 |
| 3 | 14 | 12 |
| 4 | 26 | 6 |

The final six-byte copy supplies the last halfword as part of its selected row.
The transfer wrapper composes into its own 32-byte stack buffer and calls the
same accepted palette loader with a full-word slot shifted four and count 16.
All three compile as ordinary C without register bindings; complete extents
include the observed literal word and two-byte zero alignment before it.

Fresh canonical proofs under `reports/audio-root/actor-palette-canonical/`
preserve four changed-source controls: change the final row selector in each
composer, the transfer count in the wrapper and the second palette-pair slot.
All reject, and the four earlier
direct consumers of the shared actor-group header are recompiled with their
controls after the declaration additions. Those rechecks add no coverage.

The incomplete static inventory records alternate-wrapper calls from
`0x080140CC`, `0x08014258`, `0x080161AC` and `0x080256A4`. The 32-byte caller at
`0x080161AC` is now reconstructed: it loads the common definition at
`0x03003970` through the ordinary wrapper into slot 1, then through the alternate
wrapper into slot 2. This base is the existing scene-player group and overlaps
game-state `+0x20`; the declaration is an access view, without establishing a new
allocation or definition-array bound. The other three callers remain unconverted.
The inventory records no calls to either standalone composer. These are shared
palette operations connected through the same row layouts and accepted copy and
display-transfer dependencies; the standalone composers' active uses, row-index
domains, output alignment and visual effects remain uncertain.
