# Actor group resources and palette composition

Four connected C functions reconstruct 372 bytes, including literal pools and
alignment. They close the resource and palette dependencies of the accepted
actor factory, actor-part updater and scene-player factory. Names describe the
observed part indices and transfers; this is static/compiler evidence, without
a runtime or gameplay experiment.

| Entry | Function | Complete extent |
| --- | --- | ---: |
| `0x08001400` | `frame_clear_part_variants` | 24 |
| `0x08001450` | `frame_set_part_variants` | 40 |
| `0x0803AD64` | `frame_bind_actor_group` | 164 |
| `0x0803AEC8` | `frame_load_actor_group_palette` | 144 |

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
