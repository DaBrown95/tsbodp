# Emulator observations

These notes record what the game does when run in the mGBA emulator, to
support the static reconstruction. They are a small number of finite
experiments. They do not show which regions are executable, what every
indirect call can reach, how real hardware behaves, or that any code is fully
accounted for. The static inventory census reports `runtime_observations: 0`
because it does not read these results; that does not mean no observations
exist.

The target is USA/Europe revision 0, SHA-256
`92ead9ff9467dbc23780e768278fe2e4bf7a0708447a0785770c129a5dbdb06e`.
The ROM, the built emulator library and the raw traces stay on the local
machine and are not published. The repository holds the harness, the recipe
below and the summaries.

## Emulator recipe

Use a clean [mGBA 0.10.5 checkout](https://github.com/mgba-emu/mgba/tree/26b7884bc25a5933960f3cdcd98bac1ae14d42e2)
at `toolchains/mgba-source`, pinned to commit
`26b7884bc25a5933960f3cdcd98bac1ae14d42e2`. Preserve its source and licences.
With CMake, Ninja and a native C compiler already available, build the static
GBA core without frontends or optional dependencies:

```sh
git -C toolchains/mgba-source rev-parse HEAD
git -C toolchains/mgba-source status --short
cmake -S toolchains/mgba-source -B toolchains/mgba-build -G Ninja \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DLIBMGBA_ONLY=ON -DM_CORE_GBA=ON -DM_CORE_GB=OFF \
  -DUSE_DEBUGGERS=ON -DUSE_EDITLINE=OFF -DUSE_GDB_STUB=OFF \
  -DENABLE_SCRIPTING=OFF -DBUILD_QT=OFF -DBUILD_SDL=OFF \
  -DBUILD_LTO=OFF -DCMAKE_BUILD_TYPE=MinSizeRel \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build toolchains/mgba-build --target mgba --parallel 4
```

The recorded build used CMake 4.4.4 and AppleClang 21 on macOS arm64. Its
`libmgba.a` is 1,235,544 bytes, SHA-256
`2bf6624179d69b7541ac3d07f046009663d5d85182de4139f357f4c7e1bd8604`.
That native archive hash identifies this local build; it is not a portable
expected hash for other hosts. The unchanged upstream source built with no
errors. Warnings concerned 108 four-character game-ID initializers, one
`futimens` availability check and one unused CLI parameter.

The harness must include generated `mgba/flags.h` before the core declarations;
`USE_DEBUGGERS` changes the `mCore` layout. Include both
`toolchains/mgba-source/include` and `toolchains/mgba-build/include`. The recorded
macOS link uses `libmgba.a`, `-framework Foundation` and `-lm`. `MinSizeRel` uses
`-Os` while avoiding upstream's automatic Apple Release LTO. No global install,
package install, GUI or dependency fetch is needed for this core build.

Build and run the [public harness](../tools/observe_boot.c) against the local ROM:

```sh
mkdir -p analysis/runtime-boot
cc -std=c11 -Os -DBUILD_STATIC \
  -Itoolchains/mgba-source/include -Itoolchains/mgba-build/include \
  tools/observe_boot.c toolchains/mgba-build/libmgba.a \
  -framework Foundation -lm -o analysis/runtime-boot/observe_boot
rom_path="baseroms/Sims, The - Bustin' Out (USA, Europe) (En,Fr,De,Es,It,Nl).gba"
analysis/runtime-boot/observe_boot "$rom_path" 300 50000000 0 \
  > analysis/runtime-boot/boot.jsonl
analysis/runtime-boot/observe_boot "$rom_path" 300 50000000 0 \
  > analysis/runtime-boot/replay.jsonl
analysis/runtime-boot/observe_boot "$rom_path" 300 50000000 0x10000000 \
  > analysis/runtime-boot/wrong-watch.jsonl
cmp analysis/runtime-boot/boot.jsonl analysis/runtime-boot/replay.jsonl
python3 -m unittest discover -s tests -p test_boot_observer.py -v
```

This is the recorded macOS link command; other hosts need their platform's
native link dependencies. Validate the local ROM against the fixed target hash
before running. The harness accepts bounded runs up to 3,600 frames and
100,000,000 steps. It accepts only the normal watch locations or the aligned
`0x10000000` displacement. The five authored-fixture tests cover STM readback,
the wrong-watch control, pre-entry register timing, missing ROM rejection and
invalid bounds. They use synthetic instructions, with no original game payload.

## Boot observation

The [machine-readable summary](../config/rev0/runtime-observations.json)
records all 36 entry and call-site probes and 18 write probes, including those
that were never hit. A 300-frame run with no keys held reaches 30 of the
probes in 5,835,926 steps and 84,028,913 emulator ticks. A second run gives
byte-identical output: both traces are 72,816 bytes with SHA-256
`5422e126c328ce26917aa7553cc51c86e9fc42863527a7416879a11564907630`. A control
run that watches the wrong addresses (SHA-256
`c0a2b1b44c94921ec8cf7fb12a5d98ab8fb836b9b7f0ecd9a8f0a986478121e5`) reports
no watched writes and the same entry counts, final registers, frames, steps
and ticks. None of the three runs logs a fatal error, error, warning, stub
call or game error.

The renderer and its finalizer are each entered 810 times, the copied sorter
135 times, the background decoder once and the copied tile allocator six
times. The six probes that were never hit include the left-mixer and
bias-fill entries, collision and tile decoding, and both map kernels. A probe
that is not hit in this run does not mean its code is unreachable.

The renderer entry shows how the game's objects are drawn:

- During the 300-frame boot, all 810 renderer entries are in strip mode, across
  six objects, and none uses the shared-part path. Running 3,600 frames with
  no input gives 10,710 entries, again strip-only. A short Start/A sequence
  reaches objects that use direct sequences, still without the shared-part path.
- A source-directed key route accepts the language, enters a name and opens the
  appearance preview. It reaches shared rendering at frame 1,180 without
  changing game code or memory. Watches on four part-flag bytes and four
  variant-pointer words of the object at `0x0200D0A0` follow 128 renderer
  calls. Each window ends when the return at `0x08002940` goes back to the
  saved caller with stack and CPU mode restored. No watched writes and no
  nested IRQ-dispatcher or audio-IRQ entries occur in them. A replay is
  identical (252,102 bytes, SHA-256
  `04f4174c41701798224682737ab345d548474f9de84d150e360ec6700b438a3a`).
- A Right press in the same preview is a positive control. At frame 1,243 the
  setter at `0x08001464` changes the object's part-zero pointer from
  `0x08D70CE0` to `0x08D70CE4` and part one from `0x08D70CF0` to `0x08D70D18`,
  both outside rendering. Another 128 calls complete with no writes to the
  watched fields and no nested IRQ entries. These runs show that shared
  rendering is reachable and that the watches work. They do not justify
  `volatile`, explain the third pointer reload, or rule out other writers,
  interrupt timing or gameplay paths.

### Audio and interrupt code

The two master-volume calls receive `128` and `0x40080`, followed by converter
patch arguments five and four. Readbacks at the four watched instruction
pairs hold `0xE7DCA2CA` and `0xE7DCB2CB` after shift five, then
`0xE7DCA24A` and `0xE7DCB24B` after shift four. The IRQ word at `0x0300004C`
changes from `0xE59F0034` to `0xE12FFF1E` (`BX LR`). The first sample taken
at entry shows the old instruction and the seven later samples the
replacement. The tail is entered 67 times, but only the first eight have
individual instruction and register samples.

The converter entry at `0x03000B38` is entered 268 times. Each of its eight
writable instruction-word sites is reached 18,492 times, and every retained
sample at each site holds the shift-four words. These are arrivals before the
instruction runs. The probe at `0x03000AB4` was once labelled as conversion;
the entry is `mixBias`, and its zero hit count is kept under the corrected
label.

Both arrivals at `0x080499B0` show the Thumb NOP halfword `0x46C0`, and no
store runs at that site. The clipping endpoint word ends at `0x80808000`,
whose low byte is zero. The probe is exact-byte, so it does not cover other
byte writes within that word. Writes that publish resource and map callbacks
and IRQ vectors are recorded, but they are not claimed to be all the writers
or all the possible targets.

### Pending-display queue

The pending-display initialiser is reached once. The VCount callback, its
indirect-call site at `0x08046E6E` and the default no-op at `0x08047080` each
have 270 arrivals. The first eight samples at the call site carry the Thumb
target `0x08047081` in `r2` and the argument addresses `0x03002258` and
`0x0300225C` in `r0` and `r1`. The first staged and queued callback words
have three and four hooked writes and both end at that default target. Only
those first words were watched.

A later observer watches all 23 callback-shaped words (eleven staged and
twelve queued), using 92 byte-address watches, through all 128 selected
renderer returns, which end at frame 1,433 after 43,437,271 steps and
402,438,870 ticks. No callback is injected and no game code or register is
patched. All 1,454 hooked writes have typed readbacks. The last queued word,
at `0x030023C0`, overlaps the tile bitmap and has 1,387 hits, 740 changes and
eight groups of CPU and DMA writer contexts; its bitmap values are not
execution targets. The contexts distinguish the queue reset, the fixed bitmap
fill, the commit's word AND and the mark-allocated byte OR. The immediate-release
path at `0x08047A34` is not reached on this route.

All 1,403 call-site arrivals are counted. Eight samples and 1,395 counted
duplicates carry index zero, the default target `0x08047081` and the argument
addresses above. One startup BL reaches the register-call veneer, and its BX
then reaches the default target with the expected arguments, return address,
stack and Thumb state. These show arrival at a point, before the target
instruction runs, and do not show that every later call returned or what other
targets are possible.

#### Row-shift fixture

A fixture boots the ROM normally and pauses at `0x08025CA6`, just after the
pending-display initialiser returns. It checks the twelve queued rows, eleven
staged rows, count one and the default callback `0x08047081`. It then calls
the game's own flush, insertion and VCount functions, setting only arguments
and return linkage and leaving game code and queue data alone. No natural
caller of the insertion function is known.

After a flush, inserting line 2 and flushing, inserting line 1 again selects
index one. Each insertion calls `heap_move(0x03002324, 0x03002314, 144)`, which
loads and stores 36 words. The helper's backward trailing-byte decrement leaves
an offset of minus one. On the second shift, the load at `0x08027816` uses bus
address `0x03002323`, so the aligned word `0x08047081` is rotated right by 24
bits into `0x04708108`. The store at `0x08027818` then writes that value to
the queued callback word at `0x03002330`.

The next flush copies the malformed callback to `0x03002280`. Two controlled
VCount calls run the valid default callback and advance the flag to two. A
third loads the target at `0x08046E6C`, giving `r2=0x04708108`,
`r0=0x03002278` and `r1=0x0300227C`. Execution stops at `0x08046E6E`, before
the indirect BL, so the malformed target never runs. The count stays one
throughout and is not consulted.

| Case (fresh emulator) | Copy loads/stores | Default callbacks run | Endpoint |
| --- | --- | --- | --- |
| Baseline | 0 / 0 | 1 | Flag wraps to zero. |
| One insertion | 36 / 36 | 2 | Flag wraps to zero. |
| Two insertions | 72 / 72 | 2 | Third target loaded; stopped before BL. |

Each case replays identically. The double-insertion run ends at frame 29,
after 2,124,986 steps and 8,168,013 ticks; its 11,047-byte trace has SHA-256
`0dd51137e639947c21582295ed3e96cdd3c93e5ef41cd309f27baa240b701657`. A
hand-written calibration checks that an aligned load of `0x12345678` at
low address bits three gives `0x34567812`. A one-step budget stops after the
insertion's first stack push with every row byte unchanged. The result is
one conditional case where a write to the queue becomes a loaded callback
target. It does not show that the call is valid in the real game, that the
queue is ever scheduled this way, or what the other writers and targets are.
A malformed data-derived target is not evidence of undiscovered code.

## New-game routes

All routes below use normal key input, the unmodified ROM, the replacement BIOS
and a fixed RTC of zero.

### Scene request byte

After the language, name and appearance route, 25 Right presses reduce the
selector budget from 25 to zero and leave row counts `[10,10,5,0,0]`; two Down
presses change rows. Every sampled state keeps budget plus row counts at 25.
Confirming and then the phase-25 A inputs reach primary gameplay.

At frame 2,003, `STRB R0,[R1]` at `0x0801B63C` stores `R0=14` to `0x0300408F`,
and the byte changes from zero to 14. At frame 2,471, guarded Start input
reaches `0x080260EE`, which loads from `0x0300408F` and keeps `R0=14`. The
default-request entry receives 14 with `LR=0x080260F5`, and the submitter then
receives `(14,0,0)`. The scene handoff reaches row 14's begin callback at
`0x0801D1D0` with active kind 14 and previous kind 1. Observation stops at
that entry, before its first instruction, so completed menu setup is not
claimed.

The run ends at frame 2,489 after 96,192,151 steps and 699,070,957 ticks,
within the 3,600-frame and 100-million-step limits. A cold replay is
identical: each trace is 332,579 bytes with SHA-256
`cdc01cd1360142102040385e909c1ef8fc059d24bad793be298478b87801c1bf`. Moving
the write watches elsewhere keeps the entry counts, route and final CPU and
timing state, and records no writes. All three runs have empty stderr and no
fatal, error, warning, stub or game-error logs.

This is one route from the initialising store through the load to the
consumer. Frame samples are not a complete watch of byte writes, so other
writers, aliases, saved-state inputs, the range of scene kinds and other
gameplay paths are unchecked.

### Terrain redirection in scene six

This route asks why holding Left also changes the player's Y coordinate. The
run uses blank in-memory save state, a fixed RTC and the same BIOS and keys.
No game memory, code, random result or saved state is injected. The first idle
point is `(286.3115234375,285.2626953125)`, not the nominal spawn point. The
initial scene program moves the player toward `(284,283)`, and the state-13
completion test allows a residual within three pixels on each axis.

The approach holds Down for 86 sampled frames, then Left for ten. Read-only
probes watch the live actor in native frames 2558 to 2566, before and after
velocity integration, terrain response, offset acceptance and later frame
stages. The replay with probes keeps all 1,427 earlier JSON records exactly
(including step counts) once the new probe records, summary and
entry-counter rows are removed, and records 26 snapshots with no dropped
records or invalid spans. The input is Left, input disabling is zero,
direction is six, response is three and velocity is `(-3,0)`.

At native frame 2563, terrain contact three resets the integrated Left
proposal and accepts offset `(0,-2)`. At frame 2565, contact 15 accepts
`(-2,-1)`. These changes to the proposed points are seen after redirection
and terrain collection and before global collision and optional animation
preparation. Earlier contact-zero samples keep the ordinary Left proposal. So
the two deflections happen in the [terrain response](../src/frame/frame_apply_movement_contact.c)
and the [redirect worker](../src/frame/frame_redirect_movement.c). Equal points
after collection and before commit show no net change later, though they do
not exclude writes in between that cancel out.

A longer run with the same keys extends the vertical stop band to `378..452`,
the first portal object's own Y extent. Its first 1,450 records match the
earlier replay exactly through the last frame-2566 point. After 86 Down and
158 Left samples it stops at frame 2714 at `(87.3115234375,377.2626953125)`,
with no portal request and no arrival at scene one. There are no terrain
probes after frame 2566, so the later motion cannot be attributed to a writer.
The object's extent is not the real contact area, so this run does not show the
portal is absent or unreachable. This longer run has no replay or
displaced-watch control. Both runs report no fatal, error, warning, stub or
game-error messages.

A static query of the initial map reproduces all four observed contacts and
their filter values (zero, zero, three and 15). The calibrated decoder model
decodes the 1,044-byte primary type map and reuses the two earlier pattern
streams in memory. All 520 initial block indices are in `0..142` and fit the
2,576-byte pattern backing. A separate 56-byte BIOS run-length stream is not
input to that decoder. Of 75 integer Down-then-Left polylines ending at X16
and Y378..452, none has both legs clear of terrain contact. These tests use
integer centres and the small movement footprint, stopping at the first
contact, and do not simulate fixed-point movement, redirection or object
collisions. Overlap with the portal also depends on the player's collision
box, which is separate. Animation can change the live type map, and the
static query does not cover those writers, the real allocation or the
installation history.

The static portal chain toward scene zero depends on the player actually
traversing it. These runs do not reach the scene-zero selector.

### Selected resource-program list

On the new-game route the command call at `0x0800AE0C` sees an installed
program list. While preparing root `0x08D76254`, the program-group builder
receives the selected pack `0x08D7680C` and writes a 176-byte program image
starting at `0x020272DC`. Rebuilding its six groups from the ROM reproduces
every installed byte. The pack pointer is seen at the builder call, separate
from the earlier observation of the selection byte.

Group zero holds only its terminator. Group one consumes commands 16, 14 and
zero, with byte steps 12, 8 and 4, and its records equal the installed bytes.
The two callback operands name the [view-motion handler](../src/resource/commands/resource_command_start_view_motion.c)
at `0x08011E41` and the [resource selector](../src/resource/commands/resource_command_select_resource.c)
at `0x08012189`, and both return. Observation stops before the group's first
epilogue instruction at frame 2,033, after 80,856,202 steps.

The replay is identical. Probes moved elsewhere record no hits and keep the
CPU and timing endpoint, and the added installer probes keep the earlier
records, operands, steps and navigation. Six observer failure commands and
six corrupted-observation and source-pin controls are rejected. Equal bytes
at installation and at use do not rule out writes in between, show the
allocation is live, give the table capacity or cover later programs.

### Delayed view activation

Continuing the same key sequence, command 16's view effect leads to mode-one
activation at `0x0800E604`. At frame 2,169 the arguments are object group zero
and program group four, and the group-enabled helper excludes object spawning
in this call. At the interpreter's first record, the loaded root is
`R2=0x020272DC` and the cursor is `R5=0x0202732C`, at offset 80.

Group four consumes commands 24, 11 and zero, with byte steps 16, 8 and 4. The
operands name the [object-interval handler](../src/resource/commands/resource_command_start_object_interval.c)
at `0x08012349` and the [delay handler](../src/resource/commands/resource_command_start_delay.c)
at `0x0801211D`, and both return. All of the 176-byte image matches the
builder output and eight observed points in the program image. The activation
returns to `0x0800E608` with no open interpreter frame after 85,906,412
steps. The replay is identical, probes moved elsewhere keep the keys,
navigation and endpoint with no events recorded, and six argument failures and
twelve derived observation and source-pin failures are rejected. Equal images
at single points do not rule out writes in between, show the allocation is
live, or cover the full range of selectors and later delivery.

## Controlled fixtures

These fixtures call individual game functions with chosen inputs on a paused
emulator, rather than playing through the game. Each case starts from a fresh
core and replays identically.

### Installed tile decoder

The [fixture summary](../config/rev0/runtime-tile-fixture.json) records a call
to the tile decoder after normal reset and installation. Startup reaches the
installer at `0x08016A48` and its return to `0x08025C5A` after 1,955,632
steps, 27 frames and 7,602,758 ticks. The callback word holds `0x030036D0`
and all 528 installed bytes equal their ROM source: 504 for the decoder and
24 for the copied start of the following function.

The fixture supplies a fixed frame input at `0x08FD9134` (with a 112-byte
guard) and an OBJ VRAM destination at `0x06010080`. The installed ARM code
produces the expected 128 bytes in 742 steps, with 64 halfword stores and ten
history reads. All five backward-copy load sites run after the bytes they read
have been written. Output, count, stack and code guards pass, and the stack
and preserved registers are restored. The output hash equals that of an
earlier model.

Twenty parser samples cover five visits to the compare, shift, OR and
conditional-add positions. Live RAM and prefetched instructions keep the
original CMP, LSR, ORR order. The five lengths are three, the distances are 4,
9, 38, 76 and 72, and the extended-repeat condition is false on this input.
A hand-written four-byte literal case passes, and the missing-terminator,
one-step-budget and odd-output-pointer cases are rejected by the fixture's
guards. Those rejections do not show how the original code behaves on
malformed input.

During each call, IRQ and FIQ are masked and timing events are suspended, and
the private EWRAM stack and count and the chosen VRAM span do not involve the
game's allocator. Natural scene execution and other inputs, callbacks, code
writers, IRQ and DMA, and gameplay are not covered. The 504-byte C version
differs from the ROM by eleven bytes.

### Serial reset to loader

Normal key input reaches serial-session kind 10, mode 0, at frame 1,047. At
its first step, three controlled Thumb calls run the original world
initialiser, the 108-byte peer-record producer and the receiver. Stack,
control mode and preserved registers are checked on return. The peer payload is
unchanged, the receiving identity word is set to one and the peer word is
zero. The receiver supplies phase two and countdown 45. This is a controlled
delivery after real screen navigation, not a multiplayer exchange.

The real session, transport, save and actor allocations pass their backing
checks. Initialisation supplies the 162 actor slots and an empty fifty-group
collection, and the resulting save is 831 bytes. After a slot-three write and
read, all 2,040 buffer bytes match, with checksum zero, validity set and slot
three selected. The full buffer hash is
`778f4363d9ec9730979d8c331d082aa3cf2bdd63a3960bb832f5b50650918c8a`. No host
code supplies the media readback.

Store hooks cover aligned byte, halfword, word and multiple stores, IWRAM
mirrors and DMA, and pass the original operations through unchanged. Values
are read back after the underlying store, rather than trusting the STM
watchpoint shim. Seven hand-written ARM and Thumb calibration operations
cover an unaligned word, a decrementing multiple store, DMA, a mirrored byte
and an unaligned halfword. A control with the watched region moved records no
writes and identical CPU state and timing.

From the receiver's return to the loader's byte load, the only write to the
selector is the clear's `STMIA` at `0x08027A8A`, which writes zero to the word
holding `0x03004111`. The `LDRB` at `0x0801B78C` then retires at `0x0801B78E`
with R1 zero. The run ends at frame 1,269 after 40,302,530 steps, with IRQs
and timing active, 241 dispatcher-entry arrivals and 27 audio-handler
arrivals. A control that seeds the selector with 90 just before the clearing
STM reads back zero with the same endpoint. No fatal, error, warning, stub or
game-error logs occur.

This covers one controlled input and one callback and backing state. Other
loader routes, writers, aliases, IRQ and backing populations, real peer
delivery and handheld behaviour are not covered. The loader's 548-byte
function still differs from the ROM in 17 bytes.

### Palette word as data

This fixture checks whether the ROM word `0x08088B14`, which holds
`0x0800E1EF`, is read as palette data. After a fresh reset, hand-written IWRAM
scene globals select scene eight and period three. The palette pair points to a
private aligned 512-byte EWRAM buffer at `0x02020000` and the destination
`0x05000000`; the private EWRAM stack starts at `0x0203F000`. Calls run in
Thumb system mode with IRQ and FIQ masked and timing suspended. No game
instruction or callback is written and natural scene initialisation does not run.

The selector at `0x08026794` returns `0x08088964` after 23 instructions. The
palette loader at `0x080116F8` calls the transfer and byte-copy bodies with
count 256, giving 128 word loads and stores. After 694 instructions in the
second call, execution stops at `0x080119EE`, before the DMA register
sequence, with SP `0x0203EFE4`. All 512 staging bytes equal the source
palette. At `0x08027AF0` the LDM reads the word at `0x08088B14` into R0, and
the state after the instruction holds `0x0800E1EF`. The STM at `0x08027AF2`
stores it at `0x020201B0`. The observer checks the retired load and the stored
memory directly.

The period-two selection copies a different palette and never reads the
word. Count 216 copies 432 bytes and stops just before it, and count 218
copies 436 bytes and includes it once. A one-instruction budget stops before
the copy. All five cases agree on instruction-address and opcode hashes on a
fresh-core replay. Expected copied prefixes, surrounding guards and the source
word are checked. The DMA source and destination registers are write-only, so
reads of them are not used as evidence, and no palette DMA or displayed image
is claimed.

The first fixture run was rejected before the copy because the second call
cleared the Thumb flag while the emulator was already in Thumb mode, which
gave an invalid prefetch setup. Setting the mode and flag consistently fixed
this, and the corrected run rejects emulator error logs and passes the count,
stack and prefetch checks.

The result is one case where the word is used as palette data. It does not show
that the word is code, where R1 is prepared, or that anything runs at
`0x0800E1EE`. It does not cover natural scene-eight reachability, the full
scene, table and backing ranges, other readers or other execution.

### Row-six secondary decoding

This fixture runs the game's dispatcher at `0x08016978`, its SWI 11 wrapper at
`0x0804C8DC` and the delta pass at `0x08016B78` on the two row-six secondary
streams at `0x08DBFF38` and `0x08DC0D00`. They use codec nine: BIOS LZ77
followed by the game's halfword delta pass. The replacement BIOS provides the
HLE service, so this is not retail BIOS or hardware. Synthetic EWRAM output and
separate system and supervisor stacks do not overlap. The game path starts and
returns with IRQ and FIQ masked, and the BIOS stub clears F briefly during its
system and supervisor phases. Timing events stay suspended, IRQ and FIQ modes
are excluded and execution is limited to the game functions and the small
BIOS service, stall and return path. No game code or callback is changed.

Both calls return 56 bytes after 1,001 and 1,163 steps. Each output byte is
initialised before it is inspected, and all LZ77 history reads and delta reads
use initialised bytes. Each delta pass makes 27 halfword stores. Both headers
are `(26, 1)`, with 26 data halfwords ranging from zero to 24 and from zero to
18. Source bytes, output and stack guards, stack restoration and the
inspected I/O state stay intact.

Hand-written literal-only raw and delta cases tell the codec flag apart and
check exact output. A one-instruction budget stops before decoding, and a
wrong-mode case is rejected before execution. All six cases reproduce their
results and rolling instruction and opcode checksums on a fresh-core replay,
with no emulator errors. The first run exposed an error in the observer: a
fixture opcode inspection was counted as a game load. Counting only
execution steps fixed it.

For source indices 0 to 25, adding the actual combined prefixes gives tile IDs
471 to 495 and 258 to 276, all inside the separately modelled 496 and 277
initialised groups. This settles the question for those secondary values. The
animation callers do not establish the full range of index, coordinate or map.
The eight fixed animation payloads and their activation chain depend on actor
and view completion and stable backing. Wider serialised data, the live heap
and backing, installation context, other writers and natural scene execution
are not covered.

## What an observation means

Breakpoint checks run after one emulator step and compare the next
instruction address with the probe: raw PC minus four in ARM mode or minus two
in Thumb mode. They record arrival before that instruction runs. A separate
initial check handles a probe at the initial PC. An interrupt can intervene
before the next instruction, so arrival alone does not show the instruction
retired.

Write watchpoints run before the underlying store. Single stores show their
proposed value, but mGBA 0.10.5's multiple-store shim supplies zero for every
word, so a recorded shim value cannot show an STM payload. The readback at the
end of the step records the word after that step, and repeated writes during
one step can share one readback.

DMA word and halfword stores pass through these hooks, and the CPU PC in a
DMA callback is context, not the address of a CPU store. Direct host memory
changes, including some HLE reset `memset` operations, bypass the hooks.
Watchpoints group bytes within an access width, so shifting a word probe by
one to three bytes is not an independent negative control. Unmapped reads have
no stored word and must not be read as successful writes.

The runs use mGBA's replacement BIOS with startup skipped, a fixed RTC and no
held keys unless a route says otherwise. HLE services and timing do not
reproduce every retail BIOS detail. Probe hits and a finite boot cannot
establish the full set of callbacks, jump-table targets, later gameplay paths
or modified code locations. Per-probe output limits keep a bounded number of
examples, and total hit counters are kept apart from the retained samples.
None of these observations adds matching C or changes the static census.
