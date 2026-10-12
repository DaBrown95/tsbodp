# Resource condition reconstruction evidence

This connected continuation of resource commands 36 and 37 adds 11 verified C
functions covering 1,024 bytes. Complete extents match at their original ROM
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
the row word at game-state offset `440` and call the original row-display
publisher at `0802A94C`. The four-byte row scene/mode table at `08059ADC` remains
unconverted data. The shared `SceneRequest` now exposes the observed word at
`0C`; its name `parameter` remains deliberately general.

The 480-byte completion function uses sequential offset arithmetic, scoped
state and actor pointers, and explicit byte accesses to reproduce compiler
register lifetimes. It contains no register binding or instruction assembly.
The 68-byte lookup extent includes its three literal words and ends at
`0802CA74`; the 44-byte threshold extent includes two zero alignment bytes.
Full comparisons, not estimated scanner boundaries, determine coverage.

Useful failed candidates and raw comparisons remain in ignored local reports.
The activation path at `0802A06C`, refresh at `0802A688`, group completion at
`0802A3C8`, initialization at `0802A49C` and row-display publisher at `0802A94C`
remain unconverted. Close candidates receive no C coverage credit. They are
the next connected targets before assigning broader semantics to this system.
No output patch, difference mask or reference change was used.
