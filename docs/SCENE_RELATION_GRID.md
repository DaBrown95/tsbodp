# Relation-grid scene

The inferred phase-17 lifecycle has ten matching C functions totaling 1,924 bytes. Their complete original extents, including literal pools and alignment, match in normal and strict declaration profiles. Changed-source controls reject for every function. This is source and compiler evidence; it does not establish whole-scene gameplay or hardware behavior.

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

The lifecycle table at `0x5797C` has twelve-byte rows. Row 17 installs initialize, step and shutdown at `0x0803615D`, `0x0803637D` and `0x08036845`. Names and owner interpretations remain provisional.

The relation-detail service at `0x40D68` remains an explicit original boundary. It receives a four-byte pair of signed halfwords in the third argument word; the eight-byte `FramePoint` is a different interface.

The two getters read descriptor byte zero and trait byte `2 + index` through the actual input byte representation. The initializer supplies indices zero through four. Refresh examines six entries, reads the relation index before testing it against 23, writes the object subtype, refreshes the object and then reloads its flags. Invalid entries clear visibility. It preserves the two separate object-slot address lifetimes around the call.

The ordinary refresh predecessor was 132 bytes with two differing bytes: local allocation tied the short array-base value to the call-crossing slot pointer. A GNU R0 constraint now describes only the genuine immutable array address loaded at `0x08036792` and consumed by the addition at `0x08036794`. That value dies before R0 receives the call argument; the resulting slot stays in callee-saved R4. The source adds no memory access, artificial value use or instruction body. This is one matching source spelling, not historical-source proof. Normal and strict full-byte comparisons and actual source controls cover all three additions and both renamed callers. Separate actual definition checks use the pinned compiler ABI; modern Clang layout assertions were an unsuitable fixture and did not cause production header changes.

The new 144 extent bytes contain 122 instruction bytes, 20 referenced literal bytes and two alignment zeros. Resource backing, input populations and gameplay remain unproved.

Initialization sorts 24 relation indices by signed relation value, configures backgrounds and text, creates the visible object group, and draws trait and parameter indicators. The step function navigates two rows of three entries, pages within the observed range, redraws the detail panel and issues scene requests. It preserves repeated input and slot loads around opaque calls.

The fixed-address world access view reaches 160 bytes: trait inputs begin at `+0x18`, the relation-values view at `+0x20`, and six four-byte signed-parameter records at `+0x88`. The byte cursor advances only after the previous root-relative consumers finish. These are observed access views and bounded fixture contracts, not proof of a complete original C owner or effective type.

The grid itself accesses a twelve-pointer prefix of the scene object slots. The accepted shutdown helper clears seventeen slots, so a nested shutdown check needs seventeen mapped writable slots. Neither observation establishes the complete global capacity. Initialized selection `0..5` and page `0..9` keep the grid's index within the 24-entry index table; the original entry lookup occurs before its value guard. Allocation and resource availability remain caller or engine preconditions.

The actual indicator resource contains eleven frames. Nested animation checks therefore require frame indices `0..10`; byte-valued traits and signed-byte parameters alone do not prove that range. Text lookup may return null, and text drawing may fail to advance. Bounded checks require readable nonnull text, valid field/substitution buffers and successful bounded progress, with opaque engine effects stated separately.

The existing 240-byte scene-object constructor has a separate zero-credit source-domain repair: signed-halfword coordinates are multiplied by 65,536 rather than left-shifting a negative signed value. The complete signed-halfword products are representable in signed 32 bits and retain identical native bytes. This repair changes no metadata, profile, allocation, resource or callback contract, and does not establish scheduler or engine behavior.
