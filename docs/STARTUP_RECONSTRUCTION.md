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
extent. The hardware source hands off to the separate ordinary C entry described
below; the assembly exception does not claim that C body.

The stable assembly verifier matches each entire original-address extent. Each
real source mutation is the same size and rejected: change the entry branch,
IRQ mode or copy decrement. Additional mutations change a pool pointer and the
alignment fill and are rejected independently. A joint link uses the actual
ARM reset and Thumb copy symbols: all three sections still match, no extra
allocated section or interworking veneer appears, and no relocation remains.
Commands, source snapshots, expected/candidate bytes and controls are retained
locally under ignored `reports/current-goal/startup-exception/`. The reference
hash is unchanged. These are compiler/linker comparisons. Separate bounded
[boot observations](RUNTIME_OBSERVATIONS.md) record reset and game-entry arrivals;
gameplay and complete executable ownership are not claimed.

## Ordinary C game entry

[`startup_game_entry`](../src/startup/game_entry.c) at `0x08025C0C` now matches
the complete 224-byte original-address extent: 196 Thumb instruction bytes and
28 compiler-generated literal-pool bytes. The next distinct entry is at
`0x08025CEC`. The earlier 196-byte CFG extent described instructions only.
No instruction payload, assembly statement or invented return is present in
the C definition.

The entry configures WAITCNT and blending, calls the initialization chain,
installs the VBlank callback, and repeatedly runs scene handoff followed by
SWI 05 waits. Its signed absolute VBlank-count difference and unsigned frame
period comparison follow the same source form as the accepted transition
record fades. The changed-source control sets the period to three instead of
two; it retains the 224-byte size and rejects by one byte. Current shared
header snapshots, linked bytes, compiler mapping symbols, comparisons and a
compact call-dependency table are retained under ignored
`analysis/startup-game-entry/`.

All 31 direct callees now have separate source ownership: 30 readable C
definitions and the SWI 05 hardware wrapper below. The installed VBlank
callback also has a matching C definition. The last five initialization roots
now own actor/need resources, the buffer at `0x03005E5C`, map-cell buffers,
counter slots and pending VCount rows. The buffer's wider role remains unknown.
Ownership of these startup bodies does not close their transitive callees,
copied routines, complete callback domains, or counter-wrap behavior.
The entry was reached once in the separate 300-frame HLE boot.

## Memory and display initialization

[`startup_initialize_memory`](../src/startup/initialize_memory.c) at
`0x080350A4` and its five helpers own the contiguous 268-byte path through
`0x080351B0`. They preserve the initialized IWRAM/EWRAM spans, clear unused
RAM, then clear VRAM, OAM and palette memory through volatile DMA3 accesses
and the original control readbacks. Word and halfword fill types preserve
the transfer widths; compiler literal pools and zero alignment remain owned
by their full source extents.

[`display_initialize`](../src/display/initialize.c) owns the complete 20-byte
entry at `0x0800D564`: it clears the hardware display-control halfword and
calls the existing typed mode setter with zero. All seven functions have
fresh exact comparisons and meaningful changed-source controls; the renamed
game entry also retains its exact 224-byte comparison and control. Local
source/header snapshots and comparisons are under ignored
`analysis/startup-initializers/canonical/`. These source matches do not
establish physical DMA timing or complete ownership of their transitive paths.

## Connected startup providers

The [actor resource initializer](../src/startup/initialize_actor_resources.c)
and four connected allocation/reset routines cover 164 C bytes. They preserve
the ten actor-need records, the 128-node need-effect pool with 256-byte stride,
the selected-object reset and free-list rebuilding without inventing allocation
or lifetime rules. See [actor-state evidence](ACTOR_STATE_RECONSTRUCTION.md).

The [map-cell initializer](../src/frame/frame_initialize_map_cell_buffers.c)
owns 68 bytes, including its three allocation sizes and the extra-types pointer
alias. The separate [buffer allocator](../src/startup/allocate_buffer_03005e5c.c)
owns 24 bytes and stores an 8,192-byte allocation in the byte-pointer slot at
`0x03005E5C`. Typed pointer storage explains the original address lifetime across
the allocator call in several of these functions.

The contiguous [counter module](COUNTER_RECONSTRUCTION.md) owns eight C
functions and 320 bytes at `0x08045854..0x08045994`. Its one-bit paused member
and word-sized local result with byte return reproduce the original masks and
stepper exit without fixed registers. The [pending VCount path](DISPLAY_RECONSTRUCTION.md)
owns six C definitions and 304 bytes: initializer, queue/reset, arming, callback
and default no-op. Its indirect callback takes addresses of two row-state words.
Eleven staged rows and twelve reset writes do not establish a universal queue
count or backing-capacity bound. The default ROM row identifies one callback;
other writers and target populations remain open.

Every accepted provider has an entire-extent comparison and a changed-source
control. The meaningful no-op and pause controls grow their outputs and are
rejected by the unchanged verifier, which compares extra bytes as well as the
original extent. The renamed game entry also retains its own period-change
control. Source/control equality does not establish execution of every provider.

## BIOS wait handoff

[`startup_bios_wait_vblank`](../src/startup/bios_wait_vblank.s) matches its
complete eight-byte extent at `0x0804C8EC`: six Thumb instruction bytes and two
zero alignment bytes before the independent entry at `0x0804C8F4`. It takes no
C arguments, clears scratch `r2`, invokes symbolic BIOS service `05`
(`VBlankIntrWait`), then returns through `LR`. The SWI/register interface
justifies assembly hardware glue; it adds no recovered C. No raw opcode or
original instruction payload is embedded in the source.

The stable glue verifier rejects a real service change from `05` to `04`
(`IntrWait`) by one byte while retaining the full eight-byte size. The existing
C prototype and Thumb alias remain unchanged. Source, boundary evidence, linked
bytes and the control are retained under ignored
`analysis/startup-game-entry/swi05/`. BIOS behavior outside this wrapper and
physical hardware equivalence remain separate questions.

## IRQ dispatcher copy boundaries

The 512-byte installation beginning at ROM `0x160` is larger than the IRQ
routine. The existing [dispatcher source](../src/irq/irq_dispatcher.s) owns
296 instruction bytes through `0x288`; the separate pool owns eight bytes at
`0x2A0..0x2A8`. The intervening 24-byte startup copy helper is already owned
above. These total 328 source extent bytes. The remaining 184 copied bytes
contain two zero words, a provisional 60-byte ARM debugger wrapper at `0x2B0`,
and the first 116 bytes of the background decoder. Their copy does not make
them dispatcher instructions or establish a call target. The wrapper's
`MOV R12,R12`, branch and embedded `PRF %r0%` record agree with the
[official no$gba debugger-message protocol](https://problemkaputt.de/gbahlp.htm).
Its 16-byte alignment also agrees with the documented macro's `.align 4`
spelling under GNU assembler semantics. The outer register-preservation
sequence still lacks a matching ordinary-C producer or established source
origin; no whole-wrapper assembly exception has been accepted. The read word
at `0x030015B0` is the first word after the installed audio image and is cleared
by the existing unused-IWRAM initializer. Later value producers and actual
wrapper entries remain unresolved.

The dispatcher's banked-stack/SPSR entry, unrolled IRQ priorities, Game Pak
stop and switch to a System-mode callback agree with the assembly family in
[pinned Krawall startup source](https://github.com/sebknzl/krawall/blob/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0/examples/crt0/crt0.s#L581-L697).
That later source corroborates the hardware ABI and assembly origin; it is not
proof of the exact game-era revision. The existing source/control proof still
owns the full dispatcher, so this boundary review adds no source credit.

The dispatcher permits enabled Timer 1/VCount IRQs to preempt a System-mode
handler, while excluding nested VBlank through its `0x20F4` mask. The accepted
main loop also schedules scene work outside the default VBlank callback.
Retained renderer/finalizer samples have IRQs enabled in System mode. These
facts do not establish that any specific renderer input was concurrently
modified, and do not justify inventing volatile fields to force a reload.
