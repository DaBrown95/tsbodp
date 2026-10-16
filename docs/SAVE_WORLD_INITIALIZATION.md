# World defaults and selected-row display lifecycle

Nine connected C functions cover 628 bytes. The default-state initializer closes
its record, condition and selected-row reset calls, while the same selected-row
view connects window transition setup to the primary scene exit's object cleanup.
All complete extents, pools and alignment match independently; actual source
mutations reject. This is compiler/static evidence, not a runtime or gameplay test.

| Function | ROM offset | Bytes |
| --- | ---: | ---: |
| `save_world_initialize` | `0x1B630` | 212 |
| `save_world_initialize_record` | `0x31EC8` | 52 |
| `save_world_initialize_conditions` | `0x2A710` | 68 |
| `save_world_initialize_relations` | `0x35EFC` | 48 |
| `save_world_reset_transition_row` | `0x1EE08` | 24 |
| `save_world_begin_transition` | `0x1EE20` | 100 |
| `save_world_transition_ready` | `0x1EE84` | 36 |
| `save_world_clear_row_objects` | `0x1EEA8` | 64 |
| `save_world_release_row_object` | `0x1EFEC` | 24 |

The initializer uses the established world root at `0x03003950`. It copies the
complete eight-byte clock from an original ROM resource, initializes the child at
`+0x10`, resets the actor-entry context at `+0xDC`, and clears the 724-byte condition
region rooted at `+0x440`. The condition reset clears all display bits, sets kinds
0 through 22, and republishes the selected row. The relation initializer copies
only each seed's flag byte into 24 four-byte records, gives each value the existing
`-128` sentinel, then refreshes the signed average. Other relation bytes stay as
they were.

The child reset also calls `frame_reset_actor_needs` at `+0xA0`. Its accepted
provider copies a 44-byte need state and resets the selected field, establishing
child storage through `+0xCB`. The separately serialized needs child retains its
eight-word/32-byte boundary. The initializer uses an opaque record argument and
an explicit offset into the known `+0x10` world span, preserving that distinction
without changing the serializer's partial record declaration. Original no-op
hooks at `0x32000` and `0x3D170` remain explicit unconverted calls.

The default initializer clears two eight-byte regions at `+0x724` and `+0x72C`,
sets the observed byte defaults, and writes `-2` at `+0x74C`. This last word shares
the countdown address consumed by the clock updater. These partial views retain
neutral names for unestablished roles; they do not establish a complete world
allocation or the full valid domains of its state fields. The default clock's
resource bytes remain in the original unconverted ROM region.

The selected row comes from the published clock-selection byte at
`0x030040E0 + 0x31`, also the save-selection prefix's byte 42. Rows start at
`0x03004130` and have a 56-byte stride, matching the existing clock/save row views.
A reset sets the ready word to one and clears the halfword at `+8`. Transition
start writes 20 to that halfword, configures window one, sets its rectangle and
vertical movement, clears ready, and plays cue 12. The status function returns a
full word zero or one from `ready == 1`; the timer's broader lifecycle is still
unconverted.

Eight object-pointer slots occupy row `+0x10` through `+0x2F`. Cleanup reads the
selected-row byte again on each iteration, guards each nullable slot, and calls
the direct release helper. That helper sets the established frame-object flag
bit 1 and clears the slot. The frame scheduler consumes this flag during its
removal path; this helper itself does not unlink or recycle the object. Row index
arguments have no established bound. The direct helper narrows its slot argument
to a byte and assumes that the indexed object is non-null; cleanup supplies
indices zero through seven after a null check.

The cleanup C has one scoped register binding for the meaningful objects-array
address. It ends before the release call, preserving the observed base-plus-offset
calculation while preventing a different compiler reassociation. The other eight
functions use ordinary C. No output edits, hidden section removal, instruction
body transcription or comparison masks are used. Every positive and control
object and linked extent has `.text` as its sole nonempty allocated section.
Controls change the default marker, ready timer, relation sentinel, initializer
branch, condition-loop end, movement duration, status comparison, object flag and
cleanup-loop end, respectively.

Boundary corrections remain explicit: `0x2A710` owns 68 bytes and stops before
the separate no-op at `0x2A754`; the ready predicate's 34-byte CFG envelope omits
two alignment bytes, so its verified extent is 36. The larger game-state loader
at `0x1B704`, grouped actor-entry reader at `0x1FCF8`, paired condition modules and
row transition updater remain unconverted. Failed trials and raw comparisons are
retained locally; this connected reset/display path adds no runtime claim.

The separate default-reset path at `0x0801BB14` now also owns its original
no-op hook at `0x0802A70C`. An empty `void(void)` C definition rebuilds its two
instruction bytes and two zero alignment bytes, ending exactly at the condition
initializer. Normal and strict builds match both the hook and its existing
84-byte caller. A changed hook that calls the existing game-value setter with
zero produces 12 bytes and rejects; incompatible signatures and a missing
caller declaration also reject. The only direct Thumb-BL encoding found in the
ROM is the caller at `0x0801BB2A`; no exact even or Thumb pointer word was found.
These bounded static findings do not exclude dynamically formed references or
uniquely determine the original no-op's unused formal parameters.
