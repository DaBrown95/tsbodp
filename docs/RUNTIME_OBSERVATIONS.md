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
