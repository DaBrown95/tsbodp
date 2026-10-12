# Resource condition reconstruction evidence

This connected continuation of resource commands 36 and 37 now contains 21
verified C functions covering 2,980 bytes. The latest entry-group refresh and
actor-entry lookup/removal add three functions and 260 bytes. Complete extents match at their original ROM
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
| `0802A3C8` | `condition_finish_group` | 212 |
| `0802A49C` | `condition_initialize_prior_rows` | 228 |
| `08029DA4` | `condition_update_actor_context` | 524 |
| `08029FB0` | `condition_finish_actor_context` | 188 |
| `0802A688` | `condition_refresh` | 132 |
| `08020A98` | `condition_query_actor` | 48 |
| `080209CC` | `condition_update_actor` | 80 |

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
game-state offset `F0`, finds entry ID `91` through `08020A98`, narrows the
returned index to a signed byte, reloads the list pointer after that call and
removes that entry with compaction enabled through `080209CC`. Those callees
are now reconstructed; the list's gameplay role and meaning of ID `91` remain
unresolved. The earlier property-query interpretation is superseded by their
actual four-byte entry accesses.

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
reconstructed refresh at `0802A688`. `condition_lookup_kind` accumulates
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

The group completer at `0802A3C8` writes the group-complete byte without an
active check. For row two, column zero it finds entry ID `7C`, narrows the
index to a signed byte and reloads the list pointer for the removal call.
It then checks the first five group-complete bytes in that row. When all are
truthy and the requested column is not five, other rows publish a non-`FF` word
kind from `08059AF0`, while row four activates entries zero through three in
column five. The word table remains unconverted data. The meaning of entry ID `7C` and
the broader purpose of this final-group handoff remain provisional; its lookup
and removal callees are now reconstructed.
Its exact 212-byte extent includes the three-word pool inside the function and
zero tail alignment. Changing the queried entry ID rejects by one byte.

The prior-row initializer at `0802A49C` sets group active/complete and entry
active/complete bytes to one for every definition in each row below the selected
row, then calls the accepted row selector. Its three loop indices are unsigned
bytes, while the selected-row argument is a full word. The source retains this
narrowing and the original absence of range checks. Definition counts are
reloaded after potentially aliasing byte stores. Shared scoped addresses, rather
than separate repeated accessor expressions, reproduce the compiler's lifetimes;
no fixed register variables are needed. Its complete 228-byte extent ends at
`0802A580`, including all six literal words and zero alignment. Changing one
group-complete write to zero rejects with a 224-byte output and 144 differing,
missing or extra bytes. The next function begins at `0802A580` and ends at
`0802A688`; its 264-byte semantic candidate remains unconverted. The earlier
492-byte envelope is not credited as one reconstructed initializer. Raw public
positive/control comparisons are under `reports/audio-root/condition-groups-canonical/`.

The refresh at `0802A688` scans the definition's byte count, requiring both
the complete byte at `449` and active byte at `448` for every four-byte entry.
It retains a false result after any failing entry and keeps scanning. A zero
count returns true. If all entries pass, including an empty group, it reloads
the definition and publishes its byte-two display kind unless it is `FF`.
It does not write the group-complete byte or validate the supplied row and column.
This closes the refresh dependency of activation and triple completion.

The source separates the initial count's lifetime from the entry walk and uses
four semantic register constraints for state and entry addresses and their
shared offset. The constraints emit no instruction bodies. Ordinary C retains
the result, count and loop index, avoiding the overlapping register lifetimes
seen in rejected earlier trials. The exact 132-byte extent includes all three
literal words. Moving the shared complete-byte offset from `449` to `44A`
produces a real 132-byte control with one differing byte, which is rejected.
Positive and control comparisons are retained under
`reports/audio-root/condition-refresh-canonical/`.

The two callees refine the partial list reached through game-state `F0`.
Its byte-zero count bounds the lookup; byte-one capacity bounds the removal
shift, and its pointer at four addresses four-byte records. Lookup compares
record byte zero with the full-word supplied ID, returns the first matching
index narrowed to a signed byte, and returns minus one if no entry matches.
The original caller names are retained as provisional aliases; this evidence
identifies list operations rather than a general actor property API.

With a nonzero low-byte compaction flag, removal copies each following whole
four-byte record through the capacity-bounded suffix. It then writes `FF` to
the vacated entry's byte zero, clears bytes one and two, retains byte three,
and decrements the byte-zero count. Without compaction it clears the supplied
entry directly and still decrements the count. Neither function validates an
index, count, capacity or failed lookup result. These are accessed layouts,
not a recovered complete allocation or a proof that every caller is valid.

Both extents use ordinary C with explicit zero tail alignment and no register
bindings. Saving the previous decrement value in the removal loop preserves
the original full-word test; a compact countdown expression produced different
bytes. The typed list argument reproduces the observed register order.
Changing lookup failure from minus one to minus two rejects by one byte;
changing the vacated-entry sentinel from `FF` to `FE` rejects by fourteen bytes.
Raw positive/control and useful failed comparisons remain under
`reports/audio-root/condition-actor-entries-canonical/`.

Useful failed candidates and raw comparisons remain in ignored local reports.
The selected-group initializer at `0802A580` remains unconverted. Close
candidates receive no C coverage credit. It is the next connected target before
assigning broader semantics to this system.
No output patch, difference mask or reference change was used.
