# Relation-grid scene

The inferred phase-17 lifecycle has eleven matching C functions totaling 2,084 bytes. Their complete original extents, including literal pools and alignment, match in normal and strict declaration profiles. Changed-source controls reject for every function. This is source and compiler evidence; it does not establish whole-scene gameplay or hardware behavior.

| Function | ROM offset | Bytes |
| --- | ---: | ---: |
| Initialize | `0x3615C` | 544 |
| Step | `0x3637C` | 440 |
| Create objects | `0x36534` | 216 |
| Draw detail | `0x3660C` | 312 |
| Sort relations | `0x367C8` | 124 |
| Shutdown | `0x36844` | 36 |
| Create indicator | `0x36868` | 108 |
| Read trait | `0x3203C` | 8 |
| Read descriptor | `0x32044` | 4 |
| Refresh entries | `0x36744` | 132 |
| Draw relation | `0x40D68` | 160 |

The lifecycle table at `0x5797C` has twelve-byte rows. Row 17 installs initialize, step and shutdown at `0x0803615D`, `0x0803637D` and `0x08036845`. Names and owner interpretations remain provisional.

The relation display at `0x40D68` uses a four-byte pair of signed halfwords in the third argument word and a full-word relation index in the fourth. The eight-byte `FramePoint` is a different interface. All direct dependencies of the observed grid lifecycle now have matching source; this does not close indirect populations or runtime preconditions.

The two getters read descriptor byte zero and trait byte `2 + index` through the actual input byte representation. The initializer supplies indices zero through four. Refresh examines six entries, reads the relation index before testing it against 23, writes the object subtype, refreshes the object and then reloads its flags. Invalid entries clear visibility. It preserves the two separate object-slot address lifetimes around the call.

The ordinary refresh predecessor was 132 bytes with two differing bytes: local allocation tied the short array-base value to the call-crossing slot pointer. A GNU R0 constraint now describes only the genuine immutable array address loaded at `0x08036792` and consumed by the addition at `0x08036794`. That value dies before R0 receives the call argument; the resulting slot stays in callee-saved R4. The source adds no memory access, artificial value use or instruction body. This is one matching source spelling, not historical-source proof. Normal and strict full-byte comparisons and actual source controls cover all three additions and both renamed callers. Separate actual definition checks use the pinned compiler ABI; modern Clang layout assertions were an unsuitable fixture and did not cause production header changes.

The new 144 extent bytes contain 122 instruction bytes, 20 referenced literal bytes and two alignment zeros. Resource backing, input populations and gameplay remain unproved.

Initialization sorts 24 relation indices by signed relation value, configures backgrounds and text, creates the visible object group, and draws trait and parameter indicators. The step function navigates two rows of three entries, pages within the observed range, redraws the detail panel and issues scene requests. It preserves repeated input and slot loads around opaque calls.

The fixed-address world access view reaches 160 bytes: trait inputs begin at `+0x18`, the relation-values view at `+0x20`, and six four-byte signed-parameter records at `+0x88`. The byte cursor advances only after the previous root-relative consumers finish. These are observed access views and bounded fixture contracts, not proof of a complete original C owner or effective type.

The grid itself accesses a twelve-pointer prefix of the scene object slots. The accepted shutdown helper clears seventeen slots, so a nested shutdown check needs seventeen mapped writable slots. Neither observation establishes the complete global capacity. Initialized selection `0..5` and page `0..9` keep the grid's index within the 24-entry index table; the original entry lookup occurs before its value guard. Allocation and resource availability remain caller or engine preconditions.

The actual indicator resource contains eleven frames. Nested animation checks therefore require frame indices `0..10`; byte-valued traits and signed-byte parameters alone do not prove that range. Text lookup may return null, and text drawing may fail to advance. Bounded checks require readable nonnull text, valid field/substitution buffers and successful bounded progress, with opaque engine effects stated separately.

The existing 240-byte scene-object constructor has a separate zero-credit source-domain repair: signed-halfword coordinates are multiplied by 65,536 rather than left-shifting a negative signed value. The complete signed-halfword products are representable in signed 32 bits and retain identical native bytes. This repair changes no metadata, profile, allocation, resource or callback contract, and does not establish scheduler or engine behavior.


## Relation display and percentage contract

The relation display owns 160 C extent bytes: 146 instruction bytes, twelve
referenced literal bytes and two alignment zeros. It reads the signed relation,
selects the ratio denominator 100 or -100, scales its low sixteen bits by ten,
sets the indicator frame, draws text 6222 at the supplied signed-halfword point
and copies the world-prefix text. Its parent keeps the same packed point call.

The 20-byte percentage provider now takes a full-word `int` percentage and
explicitly narrows it to `unsigned short` at multiplication. All three owning
declarations agree. The provider itself shifts incoming R1 to its low sixteen
bits; both the former narrow formal and the new explicit conversion can match
those bytes. The adopted contract preserves that low-halfword behavior for any
incoming word. This remains a supported source contract, without identifying
the historical prototype. All five existing source callers remain exact under
normal and strict compilation.

Each relation branch uses a genuine R1 conversion scratch between the ratio
return and the immediately following percentage call. Defined unsigned left
and right shifts implement the low-halfword conversion. The value dies at that
call and crosses no other call. Ordinary/narrow-formal attempts retained two
extra moves and emitted 164 bytes; the joint full-word provider contract and
explicit conversion reproduce all 160. No dummy value, extra read or instruction
body is supplied. Normal/strict genuine text-ID and provider-divisor controls
reject; the actual renamed parent and its source control remain exact.

The slot-six constructor selects known resource row eight, whose sequence has
21 frames (zero through twenty). Clamped relations from -100 through 100 stay
inside this range, but the raw signed-byte writer and initialized flag do not
prove that population. Values with magnitude 110 through 127 can select frames
21/22 or wrapped 254/255. These are invalid selections in an already known
resource, not evidence of additional executable code. Raw writer, backing,
text and runtime input domains remain open.
