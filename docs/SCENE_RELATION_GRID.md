# Relation-grid scene

The inferred phase-17 lifecycle has seven recovered ordinary C functions totaling 1,780 bytes. Their complete original extents, including literal pools and alignment, match in normal and strict declaration profiles. Changed-source controls reject for every function. This is source and compiler evidence; it does not establish whole-scene gameplay or hardware behavior.

| Function | ROM offset | Bytes |
| --- | ---: | ---: |
| Initialize | `0x3615C` | 544 |
| Step | `0x3637C` | 440 |
| Create objects | `0x36534` | 216 |
| Draw detail | `0x3660C` | 312 |
| Sort relations | `0x367C8` | 124 |
| Shutdown | `0x36844` | 36 |
| Create indicator | `0x36868` | 108 |

The lifecycle table at `0x5797C` has twelve-byte rows. Row 17 installs initialize, step and shutdown at `0x0803615D`, `0x0803637D` and `0x08036845`. Names and owner interpretations remain provisional.

The refresh service at `0x36744` remains original and contributes no recovered C. Its held 132-byte candidate differs in two bytes. The trait getter at `0x3203C`, descriptor getter at `0x32044` and relation-detail service at `0x40D68` also remain explicit original boundaries. The last receives a four-byte pair of signed halfwords in the third argument word; the eight-byte `FramePoint` is a different interface.

Initialization sorts 24 relation indices by signed relation value, configures backgrounds and text, creates the visible object group, and draws trait and parameter indicators. The step function navigates two rows of three entries, pages within the observed range, redraws the detail panel and issues scene requests. It preserves repeated input and slot loads around opaque calls.

The fixed-address world access view reaches 160 bytes: trait inputs begin at `+0x18`, the relation-values view at `+0x20`, and six four-byte signed-parameter records at `+0x88`. The byte cursor advances only after the previous root-relative consumers finish. These are observed access views and bounded fixture contracts, not proof of a complete original C owner or effective type.

The grid itself accesses a twelve-pointer prefix of the scene object slots. The accepted shutdown helper clears seventeen slots, so a nested shutdown check needs seventeen mapped writable slots. Neither observation establishes the complete global capacity. Initialized selection `0..5` and page `0..9` keep the grid's index within the 24-entry index table; the original entry lookup occurs before its value guard. Allocation and resource availability remain caller or engine preconditions.

The actual indicator resource contains eleven frames. Nested animation checks therefore require frame indices `0..10`; byte-valued traits and signed-byte parameters alone do not prove that range. Text lookup may return null, and text drawing may fail to advance. Bounded checks require readable nonnull text, valid field/substitution buffers and successful bounded progress, with opaque engine effects stated separately.

The existing 240-byte scene-object constructor has a separate zero-credit source-domain repair: signed-halfword coordinates are multiplied by 65,536 rather than left-shifting a negative signed value. The complete signed-halfword products are representable in signed 32 bits and retain identical native bytes. This repair changes no metadata, profile, allocation, resource or callback contract, and does not establish scheduler or engine behavior.
