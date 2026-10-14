# Menu choice restoration

`display_menu_restore_choice` replaces the complete `0x080403B8..0x080407EC`
extent: 1,076 bytes of semantic C, including its interspersed literal pools and
original alignment. It is reached by the accepted `display_menu_prepare_primary`
when the saved choice byte is not 255. Names remain provisional. This records
static connections and compiler matches; no gameplay behavior has been tested.

The selected descriptor comes from the existing pointer table at `0x08D715C8`,
indexed by the complete word at menu state `+8`. The choice byte at `+0x25`
selects a 24-byte row. The pointer-table entry is captured before that byte is
loaded. The existing text-row view and the new choice-row view have the same
stride; they describe different accesses, without establishing table bounds.

| Row offset | Observed use |
| --- | --- |
| `+4` | Value 255 clears the saved choice after restoration |
| `+8/+9` | Condition row and column; 255 selects the original sentinel paths |
| `+0xA..+0xE` | Five condition entry bytes |
| `+0xF..+0x13` | Five display-kind bytes |
| `+0x14` | Word of independent restoration flags |

The flag word is reread after calls. Its bit-one mask is normalized to the
completion word by unsigned subtraction and a logical shift: because the mask
is either zero or two, the result is exactly zero or one. This ordinary C
normalization preserves the original value domain and requires no register
bindings. The two five-entry loops use unsigned word counters, matching their
unsigned back edges.

The local world role is an explicit cast of the existing canonical world root
`g_save_world_init_state` at `0x03003950`. It observes the signed balance at `+4`,
an actor-entry-list pointer at `+0xF0`, and the condition-kind word at `+0x440`.
It is a partial access view, not a new allocation size. A separate actor-entry
list address at `0x03003AA8` is passed to the same accepted entry-add provider;
its ownership and complete storage extent remain unknown.

The flags can subtract balance, set resource triples, request signed relation
deltas, reset the first scene actor and its indicator, and add actor entries.
When the observed low byte of entry-add's word result is zero, restoration
sets `0x200000` in the current 56-byte transition row, clears completion and
submits the existing scene request. The scene request's third argument is a
word; the existing menu-owner access view is explicitly converted to that word.
The scene slots, transition rows and request state reuse canonical shared types.

On completion, the function may award 1,000 units, read the aligned menu word
at `+0x24` through a partial selection view, and finish one display kind. The
word is masked with `0x00FFFF00`; the original comparisons and fallback call
remain explicit. The final fallback observes the low byte of the earlier word
record-group selector. No complete selector domain has been inferred.

Each non-sentinel display-kind byte is published. Condition bytes either
activate five entry slots or select a row and store request state three. The
sentinel, failure and unchecked-index behavior are retained without additional
guards or fabricated initialization.

A real changed-source control changes the 200-unit subtraction to 201 and must
fail byte comparison. Twelve accepted direct providers and the accepted primary
preparation caller are freshly checked with their own source controls and
current header closures. The relation-delta coordinator at `0x08040AB4` and the
indicator-kind fallback at `0x0802C9C0` remain explicit unconverted dependencies.
Whole-ROM equality and source coverage are verified by the publication gates;
they do not establish runtime reachability for every descriptor flag.
