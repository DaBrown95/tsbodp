# Text-bank scene and text slots

This connected path reconstructs thirteen C functions, 1,012 bytes, at their original
USA/Europe revision-0 ROM addresses. The nine scene functions cover the contiguous
808-byte region `0x08023F34..0x0802425C`; three shared text-slot helpers and the
save-header commit provider add 204 bytes. These are compile/link byte matches, including each function's literal
pools and alignment. They do not establish gameplay or a complete game inventory.

| Function | ROM address | Extent bytes |
| --- | --- | ---: |
| `scene_text_bank_initialize` | `0x08023F34` | 232 |
| `scene_text_bank_step` | `0x0802401C` | 88 |
| `scene_text_bank_shutdown` | `0x08024074` | 56 |
| `scene_text_bank_load_preview` | `0x080240AC` | 40 |
| `scene_text_bank_apply_selection` | `0x080240D4` | 64 |
| `scene_text_bank_return_previous` | `0x08024114` | 36 |
| `scene_text_bank_change_selection` | `0x08024138` | 88 |
| `scene_text_bank_create_row` | `0x08024190` | 92 |
| `scene_text_bank_redraw_row` | `0x080241EC` | 112 |
| `display_create_text_slot` | `0x080452D8` | 28 |
| `display_create_text_slots` | `0x080452F4` | 52 |
| `display_clear_text_slots` | `0x080453F0` | 32 |
| `save_stream_commit_header` | `0x08037ED4` | 92 |

The flat scene-phase table at `0x0805797C` supplies row 12's three Thumb entry
pointers: `0x08023F35`, `0x0802401D` and `0x08024075`. The reconstructed audio-options
scene submits kind 12 for its corresponding selected row. This is static incoming
handoff evidence; the table alone is not a runtime execution trace. The contiguous
region ends at the independent prologue at `0x0802425C`, while the slot helpers end
at independent prologues `0x080452F4`, `0x08045328` and `0x08045410`.

## Connected behavior and data evidence

Initialization copies save-header byte 10 into the active scene request's
`parameter` word, configures background 3 and four 9-by-7 map rectangles, sets its
velocity to `(-65536, -65536)`, loads the selected preview and palette, and builds
six text rows. The existing bank selector at `0x08044FC0` selects the indexed text
resource; the existing save-header option updater at `0x08037C5C` copies the
selected bank back into header byte 10 and writes byte 11 to one. This connects
the provisional text-bank naming to actual resource selection and persistence
fields without assigning a language to any bank.

The input path reads the local player's pressed halfword. Bit 0 applies the
selection and plays cue 1; bits 1 and 2 independently take the return path; bits
6 or 7 update the selected row and play cue 0. Scoped mask results preserve the
original short-circuit tests. A combined bit-1/bit-2 predicate compiled to a
shorter function and remains a failed private attempt. The selection helper
passes the actual parameter address to the existing vertical input provider,
with bounds 0 through 5, and redraws both the old and new selected rows before
loading the new background preview.

Rows use text IDs `row + 6`, font 3, color 3 for the selected row and color 0 for
other rows. The unselected row's offset is the word value 65535, then the computed
Y coordinate is explicitly narrowed to a signed halfword before the existing
centered-position provider. In the observed six-row construction domain this is
a one-pixel upward offset; arbitrary row arguments and resource indices remain
unchecked. The word offset local is an actual coordinate value, with no register
constraints or synthetic initialization.

`display_create_text_slot` invokes the reconstructed text-object allocator,
stores its returned pointer in the indexed table and narrows the slot into the
object's ID halfword at offset 8. The pointer table at `0x03007370` is named
`g_display_text_slots`; the clear loop visits six entries using an unsigned byte
counter. This proves the six-entry access span, not the allocation's complete
ownership or an arbitrary index bound. The separately reconstructed audio-control
view at `0x03007360` describes its own observed fields and does not own this table.

The plural slot creator repeatedly invokes the same allocator, which updates the
pointed string cursor. It creates at least one object, even if the initial string
is empty. It stores sequential table pointers and narrows each word slot index to
the object's ID halfword. The unsigned byte count wraps before its word return;
the slot index and table access stay unchecked. Four finite native-body fixtures
exercise empty input, one final slot, two middle slots and all six observed slots,
with an abstract allocator contract and caller-clobbered registers poisoned after
each call. They do not establish string validity, table capacity or real allocator
execution. The changed count control is rejected in all four cases.

Redraw first sets bit 1 of the old object's flags, then allocates and stores its
replacement. The reconstructed `frame_step_object` consumes that flag by calling
`frame_remove_object`, supporting the inferred deferred retirement role. Shutdown
runs the corresponding transition, releases the primary object list, clears the
six pointers and resets the display. It does not make the clear helper itself an
object destructor.

The active scene request at `0x03004350` and previous request view at
`0x03004370` retain the existing six-word layout. When applying a choice, previous
kind zero submits the default kind 3 request; other kinds submit the previous
kind and scene in mode 1. Cancellation submits kind 6 in mode 0 only when the
previous kind was 6. The other cancellation cases have no submission in this
body. These names and content roles remain inferred from calls and field accesses.

Read-only control, background and palette views remain explicit fixed-address
symbols. The palette address `0x08EDE3BA` is an access view two bytes after an
existing menu palette-resource root, rather than a new independent asset. No ROM
assets or extracted contents are published.

## Verification and remaining boundary

All thirteen ordinary C sources compile without register bindings or added volatile
accesses. Each real changed-source control alters a row bound, input mask, scene
kind, preview parameter, font, flag or stored slot ID and is rejected by complete
byte comparison. The connected existing providers and retirement consumers are
also recompiled with their actual controls against current headers. Native object
and linked ELF sections, symbol addresses, complete byte extents, source snapshots
and header dependencies are audited separately from the whole-ROM gate.
The alternate-palette declaration uses the existing provider's word-sized first
and count parameters. Correcting the earlier inferred halfword declaration changes
no palette source credit; all nine scene importers and that provider are verified
again with their actual controls.

The `save_stream_commit_header` provider's true extent is 92 bytes, ending at the
reconstructed checksum function's independent prologue at `0x08037F30`. It reads
16 stored header bytes, clears the current checksum halfword, then replaces it
with the negative halfword sum. The observed four-count loop compares only the
cached first word, with no address advance. A first-word mismatch returns zero
without writing; equality returns one after writing the 16-byte header. Other
header bytes can differ without blocking this write. The reason for the repeated
same-word comparison remains uncertain. The union's `dwords[4]` view permits the
observed aligned word access while retaining the 16-byte header and all state
offsets. Adding it raises the header union's alignment from two to four bytes;
the containing 204-byte state keeps its existing four-byte alignment, size and
field offsets.

Twenty-one finite original-body, linked-body and semantic fixtures cover equal
first words with differing tails, a first-word mismatch, checksum carry and an
ignored old checksum. All genuine comparison-inversion controls are rejected.
The fixtures abstract read, write and checksum providers; they do not establish
EEPROM hardware behavior or a successful save at runtime. Three interpreter
failure controls reject an unsupported instruction, a missing literal pool and
a zero instruction budget.

The existing `save_stream_build_buffer` alias identifies the
separate original provider at `0x080379A0`; it is not reused for this address.
A stale private scene alias incorrectly reused that name and was caught by the
global symbol audit before integration. An
earlier 128-byte trial range incorrectly included the adjacent checksum function;
that failed range and the intermediate semantic models are preserved privately.
The wrong range and positive-only private attempts receive no source-coverage
credit; the complete 92-byte provider and real control are verified independently.
