# Resource condition reconstruction evidence

This connected continuation of resource commands 36 and 37 now contains 16
verified C functions covering 2,280 bytes. The latest context updater adds one
function and 524 bytes. Complete extents match at their original ROM
addresses, including literal pools and zero tail alignment. Every replacement
has a compiled, linked changed-source control that is rejected. These are static
and compiler results; condition behaviour has not been tested during gameplay.

| Address | Provisional name | Bytes |
| --- | --- | ---: |
| `0802A1E8` | `resource_set_triple` | 480 |
| `0802A758` | `condition_complete_if_active` | 64 |
| `0802A798` | `condition_is_active` | 44 |
| `0802A7C4` | `condition_is_complete` | 44 |
| `0802A7F0` | `condition_group_active` | 36 |
| `0802A814` | `condition_group_complete` | 36 |
| `0802A838` | `condition_refresh_thresholds` | 44 |
| `0802A864` | `condition_select_row` | 152 |
| `0802C934` | `condition_clear_display_bits` | 28 |
| `0802C950` | `resource_set_display_kind` | 28 |
| `0802CA30` | `condition_lookup_kind` | 68 |
| `0802A06C` | `condition_activate_entry` | 380 |
| `0802A94C` | `condition_publish_row_displays` | 40 |
| `08020AC8` | `condition_record_actor_selection` | 124 |
| `08029DA4` | `condition_update_actor_context` | 524 |
| `08029FB0` | `condition_finish_actor_context` | 188 |

The serialized cells share the game-state base at `03003950` with the accepted
resource command predicates. Rows have stride 144 and columns stride 24.
Group active and complete bytes are at offsets `444` and `445`; five four-byte
entry records begin at `448`, with active and complete bytes at entry offsets
zero and one. The four getters return the stored byte without normalizing it.
These partial views establish accessed offsets, not the total state allocation
or valid row range.

Definitions at `08059A3C` have 32-byte row records. A row's count is at byte six
and its six pointer slots begin at eight. A pointed-to definition has display
kinds at bytes one and two, entry count at three and entry kinds beginning at
four. The header retains unknown bytes and a trailing partial array. The
definition and lookup tables remain explicit unconverted ROM data.

`resource_set_triple` returns immediately only when the complete byte equals
one. For row four, column four, entry two, it obtains the actor pointer at
game-state offset `F0`, queries property `91` through `08020A98`, narrows the
answer to a signed byte, reloads the actor pointer after that call and submits
the answer with flag one through `080209CC`. The original callees and the
meaning of property `91` remain unresolved.

The function writes the complete byte to one, then scans the definition's entry
count while requiring a truthy group-active byte and truthy completion bytes.
After its observed column and entry checks, an entirely completed group whose
kind has no active notification writes the selected row at state offset `751`,
ORs the column bit into byte `752`, and clears flag `00080000` in the current
view's flags. Otherwise an active entry sets that flag. The current view byte
is at `030040E0 + 31`; flag records begin at `03004130`, have observed stride
56, and contain their flags word at four. The existing eight-byte
`SceneModeFlags` declaration remains a partial view; the stride is explicit in
the access helper rather than represented as an inferred whole record size.

An entry kind other than `FF` sets a display bit, and the function calls the
still-unconverted refresh at `0802A688`. `condition_lookup_kind` accumulates
earlier row counts, selects an eight-byte record at `0805FAB4`, indexes the
word ID table at `0805F860`, and subtracts 18. Its result feeds the notification
predicate at `08040E08`. These call roles motivate the names but do not recover
the original terminology or prove display behaviour.

The display-bit clearer writes 15 bytes at `03001E00`. The setter selects byte
`kind >> 3` and bit `kind & 7`; it retains the original absence of a bounds
check. The clearer does not establish a valid range for every caller. The
threshold helper reads byte four of its input record: values above four invoke
the active-only completer for `(1, 4, 2)`, and values above 29 invoke it for
`(4, 0, 2)`. The input record's broader role remains provisional.

The row selector connects this state to the shared scene request at
`03004350`. When request word zero equals eight, it submits `(1, 4, scene)` if
the current scene is five and `(1, 7, scene)` otherwise, then refreshes the
selected row's scene. In the other branch it selects an actor using context
`03003A2C`, writes the row's scene byte to request word `0C`, submits event
`1A` and refreshes. Both branches write the row's mode byte to `03004114`, save
the row word at game-state offset `440` and call the reconstructed row-display
publisher at `0802A94C`. The four-byte row scene/mode table at `08059ADC` remains
unconverted data. The shared `SceneRequest` now exposes the observed word at
`0C`; its name `parameter` remains deliberately general.

The 480-byte completion function uses sequential offset arithmetic, scoped
state and actor pointers, and explicit byte accesses to reproduce compiler
register lifetimes. It contains no register binding or instruction assembly.
The 68-byte lookup extent includes its three literal words and ends at
`0802CA74`; the 44-byte threshold extent includes two zero alignment bytes.
Full comparisons, not estimated scanner boundaries, determine coverage.

The activation path writes row one to the selected-row word for `(1, 0, *)`.
For an inactive entry within the observed definition bounds, it sets current-view
flag `00100000`. An inactive group within those bounds publishes its group display
kind unless the kind is `FF`. It then writes both active bytes unconditionally;
the display bounds checks do not guard these state writes. Adding validation
would change the original behavior. The function submits the narrowed selection
bytes to the context at game-state `DC`, updates and finishes the separate context
at `10`, checks the byte at `E0` against four and 29, and refreshes valid entries.
The 524-byte context updater at `08029DA4` is now reconstructed.

The selection recorder scans 13 groups, whose destination slots begin at context
`1C` with stride eight and a pointer at four. Definitions at `080535A4` have stride
eight, a byte count at one and a value-table pointer at four. Each eight-byte
value record holds a value at zero and row/column/entry bytes at four through six.
An equal triple copies the value byte to the corresponding four-byte destination
record. These accessed layouts motivate `ConditionActorSelectionContext`; they
do not identify this context with the shared frame-object layout.

The finishing helper reads six signed-byte counters in four-byte records beginning
at context `88`. Thresholds submit these condition triples: counter zero, above
zero and four, `(2,2,3)` and `(3,3,1)`; counter one, above zero and one, `(0,3,0)` and
`(2,0,1)`; counter two, above three, `(2,1,1)`, and above two with counter five above
one, `(3,2,2)`; counter three above one, `(2,1,0)`; counter four above three and six,
`(3,0,2)` and `(4,3,2)`. Values cached across calls remain cached in C. Their
gameplay meanings remain uncertain. Its inline accessor binds the record pointer
to R0 to preserve the pinned compiler's base-plus-three signed load; this is a
semantic pointer constraint, with no instruction body embedded.

The row-display publisher indexes five display kinds from the row definition.
The activation and selection-recorder matches use natural typed C without fixed
register variables. Array indexing rather than a pointer walk preserves the
publisher's loop allocation. Their compiled controls change the view flag, loop
limit, group count and counter threshold; each is rejected. Canonical raw
comparisons remain under `reports/audio-root/condition-continuation-canonical/`.

The context updater reads a signed halfword at context `22`, an unsigned count
at `24`, and value bytes at `29`, `31`, `39`, `3D`, `41`, `49`, `4D`, `59`, `79`
and `7D`. The four-byte record stride and byte-one value access support the partial
`ConditionMeter` view; names such as `total`, `count` and `meters` are provisional.
The count checks are nested at zero, three, seven and twelve; total checks are
nested at 24, 49 and 59. Meter values are explicitly narrowed to signed bytes.
Negative checks use minus 50 and reject the minus 128 sentinel. Four completion
and activation pairs select condition triples or display kinds 97, 101 and 104.
The updater reloads the values at `41` and `3D` after intervening calls while
retaining their pointers. Ordinary scoped C reproduces those lifetimes without
register bindings. The complete 524-byte comparison includes all five pool words
and two zero alignment bytes; its changed count threshold is rejected. Raw
positive, control and useful failed trials remain in ignored local reports.

Useful failed candidates and raw comparisons remain in ignored local reports.
The refresh at `0802A688`, group completion at `0802A3C8`, initialization at
`0802A49C` remain unconverted. Close candidates
receive no C coverage credit. They are
the next connected targets before assigning broader semantics to this system.
No output patch, difference mask or reference change was used.
