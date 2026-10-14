# Primary menu row code

`display_menu_primary_row_code` owns the 380-byte revision-0 extent at
`0x0803F260..0x0803F3DC`, including its literal pools and original two-byte zero
alignment tail. The ELF function size is 378 bytes. The preceding reconstructed
`display_menu_populate_primary_rows` ends at this entry; the following
`display_menu_apply_primary_result` has an independent prologue at its end.
These are compile/link byte matches and static relationships, not gameplay or
a complete game inventory.

The row-population caller stores this helper's full-word result into one byte of
the five-code array, then calls the connected
[parameter selector](FRAME_MENU_ROW_PARAMETER.md). The helper takes a word row
argument and returns the complete `R4` value in `R0` without narrowing. Changing
its inferred return declaration from byte to word preserves the caller's
original byte store. No other declaration or shared layout changes.

The helper enables bit zero of the frame-object flags reached through the menu
object slot at `+4`. If the menu choice byte is present, a word record-group
selects the table base; the choice indexes a 24-byte record, and the row byte is
read at `+4` before checking `row <= 3`. The source retains that unchecked read.
An entry of 255 or row above three returns code 29. Otherwise, the entry selects
another record's word at `+20`.

The `0x7E00` entry guard covers six bits, 9 through 14. Once it succeeds, the
descending `0x200 << bit` loop for bits 6 through 0 also examines bit 15. Bit 15
alone therefore skips the threshold loop and takes the direct `row + 23` path.
For each enabled bit in the loop, a signed world word at `+4` is compared with a
signed threshold word; the result becomes `row + 23` or 29, and the selection is
marked ready. Traversal continues, so the lowest enabled bit determines the
final result. The world value's business meaning remains provisional. Its local
eight-byte access view does not assert a complete world layout.

When choice is 255, row three queries the actor-entry context pointer at world
`+0xF0` and tests the provider result's low byte. A nonempty list returns the
initial code zero; an empty list enters random selection. Row four returns 21.
Other rows also enter random selection. The existing bounded RNG receives 22
and supplies an unsigned-halfword result. Zero, 21 and duplicates in the five
code slots are retried. Definition 12, or world byte `+32` matching the actor
greeting byte at `+37`, additionally rejects 4, 5 and 14. Code 22 stays unchanged
when world byte `+0x740` is 42; otherwise a match with `definition + 18` converts
it to 28, and a mismatch retries. Input, table, context and retry termination
checks are not added.

The record address uses a 32-bit base-plus-offset representation followed by
ordinary byte-pointer arithmetic. This matches the target's table-address
calculation, not a copied instruction body. The existing record declaration
supplies stride 24; byte offset 4 and flags-word offset 20 follow the original
loads. The general catalog/context layout remains unchanged.

Five compiler bindings represent real value lifetimes. Row in `R5` and result
in `R4` survive calls through callee preservation. The entries base in `R0` dies
after computing the row address in `R1`; that address dies when the entry byte
replaces `R0`. The entry then supplies its test and record offset before mask
construction and any call. These three scratch values are sequential; no
caller-clobbered value crosses a call. Removing each binding changes native
bytes. Earlier record-offset, mask and world-pointer bindings were removed;
failed sources, removal trials and raw comparisons remain private. The final C
contains no volatile access, dummy initialization, extra call or memory traffic.

All current primary-header importers, the direct row-population caller and the
actor-list/RNG providers are verified with their actual changed-source controls.
The selector's control changes the reserved code 21 exclusion to 20 and differs
by one byte. Object sections, function boundaries, nine literal words, original
zero alignment and literal current-header dependencies are audited separately.
A strict diagnostic compile also rejects implicit function declarations without
changing the normal matching profile.

Sixteen finite original-body, linked-body and independent semantic fixtures
cover flag-mask boundaries, signed and descending thresholds, choice and row
branches, list state, duplicate/restricted codes and code-22 conversion or retry.
The fixtures abstract the existing RNG and list providers and poison
caller-clobbered registers. Three affected fixtures reject the genuine changed
source; unaffected paths are not labeled failed controls. Interpreter failure
controls reject unsupported instructions, missing literal pools, a repeating
all-zero RNG sequence and a zero instruction budget. These are bounded body
fixtures, not actual provider/gameplay execution or general termination evidence.
