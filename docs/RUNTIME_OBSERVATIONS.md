# Bounded boot observations

These emulator observations supplement static reconstruction evidence. They do
not establish all executable regions, all indirect targets, hardware behavior,
or complete source ownership. The separate static inventory census retains
`runtime_observations: 0`: that field describes the census's inputs, not the
absence of this independent experiment.

The target remains USA/Europe revision 0, SHA-256
`92ead9ff9467dbc23780e768278fe2e4bf7a0708447a0785770c129a5dbdb06e`.
The ROM, native emulator library and raw trace payloads remain local and ignored.
Only the harness, reproducibility instructions and bounded summary are public.

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

## Recorded result

The [machine-readable summary](../config/runtime-observations-us-eu.json)
records all 36 entry/site probes and 18 write probes, including zero-hit probes.
The 300-frame run reached 30 probes in 5,835,926 steps and 84,028,913
emulator ticks. Its replay was byte-identical: both 72,816-byte trace files have
SHA-256 `5422e126c328ce26917aa7553cc51c86e9fc42863527a7416879a11564907630`.
The wrong-watch trace has SHA-256
`c0a2b1b44c94921ec8cf7fb12a5d98ab8fb836b9b7f0ecd9a8f0a986478121e5`.
It reports zero watched writes and the same entry counts, final registers,
frames, steps and ticks. All three runs report zero fatal, error, warning,
stub and game-error log messages.

Renderer and finalizer entry counters each reached 810, the copied sorter 135,
background decoder one and copied tile allocator six. These arrivals connect
the remaining reconstruction work to this boot path. A separate calibrated
RAM-field follow-up records strip mode for all 810 renderer arrivals, across
six objects, with zero shared-part arrivals. Extending no-input boot to 3,600
frames records 10,710 arrivals of the same strip-only form. A bounded Start/A
path reaches non-strip direct-sequence objects but still no shared-part path.
The original 300-frame trace is byte-identical after the extra field observations
are removed. The six zero-hit entry probes include the selected left-mixer and
bias-fill entries, collision and tile decoding, and both map kernels; no
unreachability conclusion follows.

A separate source-directed key route accepts the language selection, enters a
nonempty name, and opens the appearance preview. It reaches shared rendering at
frame 1,180 without changing game code or memory. Dynamic watches then follow
four part-flag bytes and four variant-pointer words on object `0x0200D0A0`
through 128 renderer calls. Every window closes after the native return at
`0x08002940` retires to the saved caller with restored stack and CPU mode.
No watched writes or nested IRQ-dispatcher/audio-IRQ entries occur in these
windows. Replay is byte-identical (252,102 bytes, SHA-256
`04f4174c41701798224682737ab345d548474f9de84d150e360ec6700b438a3a`);
displaced watches preserve final CPU, timing, entry counts and field snapshots.
Authored fixtures independently catch byte and word writes inside and outside
the window, using typed after-step readbacks.

One source-supported Right press in the same preview supplies an actual-game
positive control. At frame 1,243 the accepted setter at `0x08001464` updates the
same object's part-zero pointer from `0x08D70CE0` to `0x08D70CE4`, and part one
from `0x08D70CF0` to `0x08D70D18`. Both writes occur outside rendering. That run
also completes 128 validated calls without selected-field writes or observed
nested IRQ entries inside them. These finite observations establish reachable
shared rendering and live watches, but do not justify `volatile`, explain the
third pointer reload, or close other writers, interrupt schedules or gameplay
paths. Unique private harnesses, calibration and route/control receipts remain
under ignored `analysis/renderer-shared-navigation/`; the public no-input
harness and its recorded 300-frame result are unchanged.

The two master-volume calls received `128` and `0x40080`, followed by converter
patch arguments five and four. Readbacks from all four watched instruction
pairs retained `0xE7DCA2CA` / `0xE7DCB2CB` after shift five, then changed to
`0xE7DCA24A` / `0xE7DCB24B` after shift four. The IRQ word at `0x0300004C`
changed from `0xE59F0034` to `0xE12FFF1E` (`BX LR`). Its first entry sample
contains the old instruction; seven later samples contain the replacement.
There were 67 total tail arrivals: the first and 66 later arrivals. Only the
first eight have individual instruction/register samples.

The corrected converter entry at `0x03000B38` has 268 arrivals. Each of its
eight known writable instruction-word sites has 18,492 arrivals. All eight
retained samples at each site contain the shift-four words
`0xE7DCA24A` / `0xE7DCB24B`; converter-entry snapshots also retain all four
word pairs in that state. These are arrivals before instructions execute.
The old `0x03000AB4` probe was mislabeled as conversion: the source entry is
`mixBias`. Its zero-hit counter is preserved with the corrected label. The
new probes preserve every prior address's hit count, all watched final words
and final machine state; no complete input/state domain is claimed.

Both arrivals at `0x080499B0` show the Thumb NOP halfword `0x46C0`; the trace's
32-bit snapshot also includes the following halfword. No store at that NOP
site was executed. The clipping endpoint word finishes at `0x80808000`, whose
low byte is zero; the exact-byte probe does not cover other byte writes within
that word. Selected resource/map callback publications and IRQ-vector writes
are recorded, without a claim that these are all writers or possible targets.

The pending-display initializer is reached once. The VCount callback, its
indirect-call site at `0x08046E6E` and default no-op at `0x08047080` each have
270 arrivals. The first eight retained call-site samples carry Thumb target
`0x08047081` in `r2` and argument addresses `0x03002258` / `0x0300225C` in
`r0` / `r1`; the no-op entry samples retain those arguments. The first staged
and queued callback words have three and four hooked writes, respectively,
and both finish at that default target. Only those first callback words were
watched. Other rows, publications, count bounds and target populations remain
unresolved. Adding these probes preserved the previous counters and complete
final machine state; obsolete trace payloads were retired after replay/control
verification, while the unique older harness draft was retained locally.

## Pending-display storage follow-up

The latest canonical private observer watches all 23 syntactic callback-shaped
words: eleven staged words and twelve queued words, using 92 byte-address
watches. It completes all 128 selected renderer returns at frame 1,433, after
43,437,271 observer steps and 402,438,870 ticks. No callback was injected and no
game code or register was patched.

All 1,454 hooked writes have typed after-step readbacks. Across the watched
words, 30 write-detail records were emitted, 735 alias details were coalesced
and 689 unchanged writes were counted without repeated detail. No output was
dropped. The final queued callback-shaped word at `0x030023C0` aliases the tile
bitmap: it has 1,387 hits/readbacks, 740 changes and eight CPU/DMA writer-context
groups. Its arbitrary bitmap values are not execution targets. The canonical
contexts distinguish queued reset, fixed bitmap fill, commit's word AND and
mark-allocated byte OR; the DMA PC is context, not a CPU store address. The
statically supported immediate-release context at raw PC `0x08047A34` was not
observed on this route.

All 1,403 call-site arrivals were counted. Eight retained tuples and 1,395
counted duplicates carry index zero, default target `0x08047081` and argument
addresses `0x03002258` / `0x0300225C`. One startup BL reached the register-call
veneer, then its BX reached the default target with the expected arguments,
return address, stack and Thumb state. These are point-arrival witnesses; the
target instruction had not retired at the target witness. They do not establish
that every later call retired or close the incoming target population.

The actual 128 writer-guard checks passed. Thirteen further commands passed:
log-overflow, authored 516-store fixture and displaced-fixture controls, a
missing-ROM failure, seven invalid-bound failures, a cold real replay and a
displaced-watch real route. The fixture retains the corrected frame-one endpoint,
515 alias changes, typed STM/word/byte/halfword values and unchanged nearby
storage. The cold replay is byte-identical to the 75,721-byte normal trace.
Displaced watches report zero hooks/readbacks while preserving the complete
execution endpoint, final CPU state, route counters, filtered transfer protocol
and all 23 logical final words. Seven reporter mutations were rejected after
both real comparisons passed. Warning/error counters remain zero;
informational/debug counts are retained separately.

The earlier trace's output-cap failure at frame 1,257 and 39/128 returns remains
historical evidence: it explicitly dropped one changed-write detail. Its strict
all-log-levels-zero reporting issue and later unknown-writer stops are also
preserved locally. The successful successor coalesces detail without losing
write/readback accounting. These observations add no C credit or static-census
input and close no arbitrary writer, alias, queue-count, callback-index or target
domain. Other paths and gameplay remain open.

## Controlled installed tile-decoder fixture

The [fixture summary](../config/runtime-tile-fixture-us-eu.json) records a
controlled call to the tile decoder after ordinary reset and installation in
the same pinned mGBA core. Startup reaches the installer at `0x08016A48` and
its actual return to `0x08025C5A` after 1,955,632 instruction steps, 27 frames
and 7,602,758 emulator ticks. The callback word contains `0x030036D0`; all
528 installed bytes equal their fixed ROM source. The decoder occupies 504 of
those bytes; the remaining 24 are the following body's copied prefix.

The fixture then supplies the
[fixed transient frame input](DISPLAY_RECONSTRUCTION.md#fixed-transient-tile-input)
at `0x08FD9134`, with a 112-byte input guard and a chosen OBJ VRAM destination
at `0x06010080`. The actual installed ARM code produces the expected 128 bytes
in 742 instruction steps, using 64 halfword output stores and ten history reads.
All five backward-copy load sites execute after the bytes they read have been
written. Output, count, stack and code guards pass, and the stack and preserved
registers are restored on return. The output hash equals the earlier model's.

Twenty before/after parser samples cover five visits to the compare, shift,
OR and conditional-add positions. Live RAM and prefetched instructions retain
the original CMP/LSR/ORR order. The five lengths are three; distances are
4, 9, 38, 76 and 72. The extended-repeat condition is false on this input.
An authored four-byte literal control passes; missing-terminator, one-step
budget and odd-output-pointer controls are rejected by the fixture's guards.
These rejections do not establish native malformed-input safety.

The whole observation repeats identically from a fresh emulator core. Its cases
share one paused core with explicit CPU/data setup between calls. During each
call, IRQ/FIQ are masked and timing events are suspended; the private EWRAM
stack/count and chosen VRAM span do not observe the game's allocator. Natural
scene execution and other input, callback, code-writer, IRQ/DMA and gameplay
domains remain open. The 504-byte C candidate still differs by eleven bytes
and gains no credit.
Private source, expected data, freezes, commands and observations remain under
ignored `analysis/tile-installed-native-fixture-20261021/`.

## Controlled serial reset-to-loader fixture

A controlled fixture follows the [serial reset/load route](SAVE_STREAM.md).
Ordinary key input reaches serial-session kind 10 / mode 0 at frame 1,047.
At its first step, three explicitly controlled Thumb calls run the original
world initializer, 108-byte peer-record producer and receiver. Stack, control
mode and preserved registers are checked on return. The peer payload stays
unchanged; the receiving identity word is authored as one while the peer word
is zero. The native receiver supplies phase two and countdown 45. This is
controlled delivery after natural screen navigation, not a demonstrated
multiplayer exchange.

The real session, transport, save and actor allocations pass their backing
checks. Native initialization supplies the 162 actor slots and empty fifty-group
collection. The resulting save uses 831 bytes. All 2,040 native buffer bytes
match after slot-three write/read, with checksum zero, validity set and slot
three selected. The full buffer hash is
`778f4363d9ec9730979d8c331d082aa3cf2bdd63a3960bb832f5b50650918c8a`.
No host replacement supplies the media readback.

Physical store hooks account for aligned byte, halfword, word and multiple
stores, IWRAM mirrors and DMA, forwarding the original operations unchanged.
Typed reads occur after the underlying store, rather than trusting the STM
watchpoint shim. Seven authored ARM/Thumb calibration operations cover an
unaligned word, decrementing multiple store, DMA, mirrored byte and unaligned
halfword. A displaced-region control records zero writes with identical CPU
state and timing.

From receiver return through loader byte-load retirement, the fixture observes
one physical selector write: the native clear's `STMIA` at `0x08027A8A` writes
zero to the word containing `0x03004111`. The original `LDRB` at `0x0801B78C`
then retires at `0x0801B78E` with R1 equal to zero. The run ends at frame 1,269
after 40,302,530 total instruction steps. IRQs and timing remain active, with
241 watched dispatcher-entry arrivals and 27 audio-handler arrivals. Callback
snapshots describe arrivals, not retired-call counts.

Cold replay is byte-identical. Displaced watches retain the same execution
endpoint and record no writes. A separate positive control seeds the selector
with 90 immediately before the actual clearing STM; its typed readback is zero
and the execution endpoint is unchanged. No emulated instruction can consume
that atomic calibration sentinel. No fatal, error, warning, stub or game-error
logs occur. Private source, commands, complete observations, controls and two
independent reviews remain under ignored
`analysis/loader-selector-serial-native-fixture-20261021/`.

This closes the named observation for one controlled input and callback/backing
state. Other loader routes, writers, aliases, IRQ and backing populations,
natural peer delivery and handheld behavior remain open. Emulator/HLE limits
still apply. The loader's 548 / 17 source mismatch is unchanged; this observation
adds no C, instruction, mapped-extent or inventory-count credit.

## Controlled palette-word data-copy fixture

A named native-call fixture checks whether ROM word `0x08088B14`, containing
`0x0800E1EF`, is consumed as palette data. After a fresh emulator reset, authored
IWRAM scene globals select scene eight and period three. The palette pair points
to a private aligned 512-byte EWRAM staging buffer at `0x02020000` and destination
`0x05000000`; the private EWRAM stack begins at `0x0203F000`. Calls run in Thumb
SYSTEM mode with IRQ/FIQ masked and timing events suspended. No game instruction
or callback is written. This setup does not run natural scene initialization.

The original selector at `0x08026794` returns `0x08088964` after 23 instructions.
The original palette loader at `0x080116F8` calls the transfer and byte-copy
bodies with count 256, producing 128 word loads and stores. After 694 instructions
in this second call, execution stops at `0x080119EE`, before the DMA register
sequence, with SP `0x0203EFE4`. All 512 staging bytes equal the source palette.
At `0x08027AF0`, the native LDM reads the word at `0x08088B14` into R0;
post-instruction observation records `0x0800E1EF`. The following STM at `0x08027AF2` stores that
value at `0x020201B0`. The observer checks actual retired-load state and stored
memory, without relying on the multiple-store watchpoint shim.

The contrasting period-two selection copies a different palette and never
reads the selected word. Count 216 copies 432 bytes and stops immediately before
it; count 218 copies 436 bytes and includes it once. A one-instruction budget
control stops before the copy. Recorded results and instruction-address/opcode
hashes agree on fresh-core replay for all five cases; this is not a retained
full-machine snapshot.
Expected copied prefixes, surrounding guards and the original source word are
checked; the emulator's DMA register shadow stays unchanged. DMA source and
destination registers are write-only, so bus reads of them are not used as
state evidence. No palette DMA or displayed-image result is claimed.

The first fixture run rejected before the copy: its second call cleared the
Thumb flag while the emulator was already in Thumb mode, producing an invalid
prefetch setup. Explicit mode/flag consistency fixes that setup; the failed
source, executable, outputs and diagnostic remain in the private evidence.
The corrected run rejects emulator error logs and passes the count, stack and
prefetch checks. The fixed reference and game source are unchanged.

This establishes one bounded palette data use of the
[pointer-shaped word](WHOLE_ROM_INVENTORY.md#palette-word-resembling-an-interior-entry).
It establishes no executable consumer, prepared-R1 producer or execution at
`0x0800E1EE`. Natural scene-eight reachability, full scene/table/backing domains,
other consumers and alternate execution remain open. No source, instruction,
mapped-extent or inventory-count credit is added; generated assets and the
current paired matching proof remain unchanged.

## Controlled row-six secondary decoding

A bounded mGBA 0.10.5 fixture executes the original dispatcher at `0x08016978`,
its SWI-11 wrapper at `0x0804C8DC` and the delta pass at `0x08016B78` for the
two named row-six secondary streams, `0x08DBFF38` and `0x08DC0D00`. These use
codec nine: BIOS LZ77 followed by the native halfword delta operation. The
replacement BIOS provides the HLE service; this is not retail BIOS or hardware
execution. Synthetic EWRAM output and separate system/supervisor stacks are
disjoint. The game path starts and returns with IRQ/FIQ masked; the unchanged
BIOS stub temporarily clears F in its system/supervisor phases. Timing events
remain suspended, IRQ/FIQ modes are excluded and execution is restricted to
the named game bodies and actual small BIOS service/stall/return path.
No game code or callback is changed.

Both calls return 56 bytes naturally, after 1,001 and 1,163 CPU steps. Each
output byte is initialized before inspection; all LZ77 history reads and native
delta reads use initialized bytes. Each delta pass makes 27 halfword stores.
The resulting header is `(26, 1)` for both streams. Their 26 data halfwords
range from zero to 24 and zero to 18 respectively. Source bytes, output/stack
guards, stack restoration and the inspected I/O state remain intact.

Authored literal-only raw and delta calibrations distinguish the codec flag
and check exact expected output. A one-instruction budget stops before decoding;
a wrong-mode case rejects before execution. All six cases reproduce their
results and rolling instruction/opcode checksums on fresh-core replay, without emulator
errors. The first run caught an observer-attribution error: a fixture opcode
inspection was counted as a game load. Restricting that accounting to execution
steps fixes the observer; its failed packet and repair remain private.

For source indices 0..25, adding the actual combined prefixes gives tile IDs
471..495 and 258..276, all inside the separately modeled 496 and 277 initialized
groups. This closes that finite secondary-value question. The
[animation callers](FRAME_MAP_ANIMATION.md#row-six-writer-domain) do not establish
the complete index, coordinate or map domain. The separately projected eight
fixed animation payloads and their direct-state activation chain remain
conditional on actor/view completion and stable backing. Wider serialized
populations, live heap/backing, installation context, other writers and natural
scene execution remain open. No C, instruction, mapped-extent or inventory-count
credit follows, and no unchanged full matching build is required.

## Meaning of an observation

Hardware breakpoint checks run after one emulator step and compare the next
instruction address with the probe: raw PC minus four in ARM mode or minus two
in Thumb mode. They record arrival before that instruction executes. A separate
initial check handles a probe already at the initial PC. An interrupt can
intervene before the next instruction; arrival does not itself prove that
instruction retired.

Write watchpoints run before the underlying hooked store. Single stores expose
their proposed value, but mGBA 0.10.5's multiple-store shim supplies zero for
every word. A recorded shim value therefore cannot establish an STM payload.
End-of-step readback records the word after that step; repeated writes during
one step can share the same final readback.

DMA word and halfword stores pass through these hooks. The CPU PC in a DMA
callback is context, not the address of a CPU store. Direct host memory changes,
including some HLE reset `memset` operations, bypass the hooks. Watchpoint
comparisons also group bytes within an access width, so shifting a word probe
by one to three bytes is not an independent negative control. Unmapped reads
have no stored word and must not be interpreted as successful writes.

The run uses mGBA's replacement BIOS with startup skipped, fixed RTC and no
held keys. HLE services and timing do not reproduce every retail BIOS detail.
Probe hits and a finite no-input boot cannot identify complete callback domains,
jump-table targets, later gameplay paths, or every modified code location.
Per-probe output limits preserve bounded examples; total hit counters remain
separate from the retained event samples. No trace result adds matching C credit.
