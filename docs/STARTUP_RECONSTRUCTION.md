# Hardware startup source

The cartridge branch, reset code and reset-only copy helper have exact source
and full-ROM integration proofs. They are justified assembly exceptions and
add no recovered-C credit.

| Source extent | Instruction bytes | Data/alignment bytes | Basis for assembly |
| --- | ---: | ---: | --- |
| [Cartridge entry](../src/startup/rom_entry.s), ROM `0x000000..0x000004` | 4 | 0 | The hardware enters in ARM state; this branch crosses the cartridge header to reset. |
| [Reset and image installation](../src/startup/reset.s), ROM `0x0000C0..0x000130` | 72 | 40 | Writes CPSR to select IRQ/system modes, initializes their banked stack pointers, installs the BIOS IRQ callback and switches from ARM to Thumb. The Thumb side calls the custom `r1`/`r2`/`r4` copy interface, then enters the original game entry through an explicit mode handoff. |
| [Word-copy helper](../src/startup/copy_words.s), ROM `0x000288..0x0002A0` | 22 | 2 | Reset supplies the exclusive destination end in callee-saved `r4`, outside the ordinary C argument convention. The helper preserves that register, rounds the byte count to words and uses a direct load/store loop. A leaf without a stack frame alone would not establish assembly origin. |

These three extents total 140 bytes: 98 instruction bytes, 40 literal-data
bytes and two assembler-owned zero alignment bytes. The helper's actual
function symbol spans 22 bytes. Its aligned extent ends immediately before
the already separate IRQ-dispatcher pool. The reset function spans ARM code,
Thumb code and its literal data, with assembler mapping symbols preserving
those distinct roles.

The reset pool names the two stack pointers, BIOS IRQ-vector slot, ROM/RAM
image boundaries and odd Thumb game-entry pointer symbolically. Its ten words
are data, not instruction payload. The dispatcher address uses the fixed
relative layout, as ARM7 ADR cannot relocate to a separately assembled external
extent. The startup does not define or replace the ordinary C game entry at
`0x08025C0C`, which remains unconverted.

The stable assembly verifier matches each entire original-address extent. Each
real source mutation is the same size and rejected: change the entry branch,
IRQ mode or copy decrement. Additional mutations change a pool pointer and the
alignment fill and are rejected independently. A joint link uses the actual
ARM reset and Thumb copy symbols: all three sections still match, no extra
allocated section or interworking veneer appears, and no relocation remains.
Commands, source snapshots, expected/candidate bytes and controls are retained
locally under ignored `reports/current-goal/startup-exception/`. The reference
hash is unchanged. These are compiler/linker comparisons; startup execution,
gameplay and complete executable ownership are not claimed.
