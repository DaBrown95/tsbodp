# Text-bank scene and text slots

This connected path reconstructs seventeen C functions, 1,388 bytes, at their original
USA/Europe revision-0 ROM addresses. The nine scene functions cover the contiguous
808-byte region `0x08023F34..0x0802425C`; six shared text helpers and two
save-stream providers add 580 bytes. These are compile/link byte matches, including each function's literal
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
| `display_append_text_resource` | `0x0804502C` | 52 |
| `display_format_hex_text` | `0x08045060` | 64 |
| `display_create_text_slot` | `0x080452D8` | 28 |
| `display_create_text_slots` | `0x080452F4` | 52 |
| `display_position_text_object` | `0x08045358` | 152 |
| `display_clear_text_slots` | `0x080453F0` | 32 |
| `save_stream_build_buffer` | `0x080379A0` | 108 |
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

Those cursor bounds do not validate the saved initial selection: initialization
loads its preview before movement, and confirmation can apply the unchanged
parameter. [Header validation](SAVE_STREAM.md#transfer-and-checksum-boundary)
does not restrict byte ten to zero through five, so that initial range remains
a precondition.

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

The separate `save_stream_build_buffer` provider at `0x080379A0` now has its own
complete 108-byte C replacement; its name is not reused for the header commit.
A stale private scene alias incorrectly reused that name and was caught by the
global symbol audit before integration. An
earlier 128-byte trial range incorrectly included the adjacent checksum function;
that failed range and the intermediate semantic models are preserved privately.
The wrong range and positive-only private attempts receive no source-coverage
credit; the complete 92-byte provider and real control are verified independently.


## Adjacent text assembly and positioning

The three adjacent text helpers add 268 complete matching C bytes. Resource append
walks the caller's existing string, invokes the reconstructed text decoder with a
1024-byte limit at its terminator, then returns the new terminator on success or a
null pointer on a nonzero decoder result. The decoder can partially overwrite the
buffer before reporting a capacity failure; the append helper does not know the
allocation's remaining capacity. Its mapped incoming callers at `0x080157D0` and
`0x08042408` remain explicit original regions. These are static connections, not
runtime traces or reconstructed callers.

Text positioning receives word coordinates and narrows each to a signed halfword.
Four independent flag bits apply half or full measured width and height offsets
in sequence, before the existing position provider stores fixed-point coordinates.
The half-size expression rounds by `(measurement + 1) / 2` with signed division;
negative odd measurements therefore follow truncation toward zero. The pinned
32-bit conversion and shifts preserve the native result. Measurements and
intermediate signed subtraction must fit an `int`; no arbitrary geometry or
valid-string domain is established.

The hexadecimal formatter emits uppercase digits and a terminating zero, then
returns the original output pointer. Its normalized C model supports digit counts
from zero through eight, including negative input values through the pinned signed
right shift and unsigned subtraction conversion. Arbitrary counts can produce
invalid C shift counts and remain outside that model. The sole register binding
holds the actual output cursor in R2 throughout the call-free loop; it introduces
no reads, writes or dummy value. Removing that binding produces a 68-byte mismatch,
which is retained privately. No mapped incoming caller for this helper or the
positioning helper has been identified in the current inventory.

All three true extents end at independent prologues: `0x08045060`, `0x080450A0`
and `0x080453F0`. Complete literal pools and alignment participate in the byte
comparison. Fresh changed-source controls alter an alignment flag, decoder limit
or hexadecimal letter and are rejected. Separate diagnostic builds use strict
implicit-function declaration warnings without changing the acceptance profile.

Forty-two finite original-body, linked-body and semantic fixtures cover twenty
position cases, six append cases and sixteen hexadecimal cases. They poison
caller-clobbered registers at abstract provider calls and check preserved registers
and the stack. Position fixtures use abstract font measurements; append fixtures
use an abstract decoder, including a partial capacity failure. The changed decoder
limit is observable in all six provider traces and changes the boundary case's
output and result; the letter control changes twelve of sixteen formatter outputs.
These finite fixtures do not establish actual font rendering, allocation capacity,
resource storage, gameplay or arbitrary input validity. Their interpreter failure
controls reject unsupported instructions and an exhausted instruction budget.


## Save-buffer construction

The matched 108-byte builder closes the reconstructed commit-slot, game-state
serializer and checksum path. It clears 2040 bytes at the current buffer pointer,
reloads that pointer after the clear, resets the cursor and bit offset, then calls
the existing 280-byte game-state serializer. It stores the cursor difference as
the unsigned used-byte count and computes `used * 100 / 2040`. Finally it clears
the last halfword at buffer offset 2038 and replaces it with the negative halfword
sum across all 2040 bytes. The serializer's unconverted descendants and unchecked
buffer capacity remain explicit; the builder does not itself verify capacity.

The state layout, interfaces and acceptance compiler profile are unchanged. Two
short register constraints hold the actual heap-clear fill value in R1 and byte
count in R2 until that call consumes them; both variables' scopes then end.
Capturing each value in its existing call operand prevents the old compiler from
retaining the first byte-count constant across later calls. All bindings for the
state pointer, stored zero and later span were removed while preserving the match.
There are no added reads, writes, unused initializations or instruction bodies.
The unsigned division provider at `0x0804CED8` remains original; its unsigned
comparisons and logical shifts distinguish it from the signed helper at
`0x0804CD2C`. No division-source coverage is claimed by this builder.

Fifteen finite original-body, linked-body and independent semantic cases cover
cursor differences from zero through 2040, checksum carry and overwriting a
serialized final halfword. The second fixture receipt also executes the original
unsigned division helper with denominator 2040. Heap clear, serialization and
checksum are abstract provider contracts; caller-clobbered registers are poisoned
after calls, while R4 through R11 and the stack are checked. Six cases observe the
changed percentage-numerator control. Three interpreter failure controls reject
an unsupported instruction, a missing literal pool and an exhausted budget.
These cases require a cursor within the same allocated buffer and do not establish
actual world serialization, arbitrary capacity, save hardware or gameplay.

The complete extent includes both literal words and ends at the independent
entry at `0x08037A0C`. The commit-slot caller, accepted serializer, checksum,
heap clear and both existing unsigned-divider callers are freshly compiled with
their genuine changed-source controls. Strict declaration diagnostics also match
without changing acceptance flags. Earlier candidates called the serializer by an
unconverted local alias; the current 280-byte canonical provider and its header
replace that stale private description. All failed ranges, lifetimes and byte
comparisons remain preserved locally.
