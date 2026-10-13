# Scene clock, palette, audio and retained display

Seven connected replacements add 644 matching C bytes. Each complete original
extent, every literal pool and all alignment bytes match after compiling and
linking the current public source. All seven are ordinary C with no register
bindings or instruction-body assembly. Their separately compiled changed-source
controls reject. This establishes source and byte comparisons; it does not
establish runtime scheduling, gameplay behaviour or a complete game inventory.

| Function | ROM offset | Bytes | Changed-source differences |
| --- | --- | ---: | ---: |
| `scene_refresh_environment` | `0x266B0` | 228 | 1 |
| `scene_refresh_period_audio` | `0x26854` | 180 | 1 |
| `scene_allocate_retained_palette` | `0x26908` | 32 | 2 |
| `scene_retain_display` | `0x26928` | 84 | 1 |
| `scene_release_display` | `0x2697C` | 16 | 1 |
| `scene_clear_retained_display` | `0x2698C` | 100 | 1 |
| `scene_step_early_exit` | `0x269F0` | 4 | 1 |

The accepted primary-scene step calls the clock/audio refresh paths for its
selected changed view. The accepted primary exit calls the two retained-display
paths according to the queued scene kind. The accepted request-queue initializer
calls the palette allocator. These are observed call connections, separate from
proof of every possible runtime caller or scene-kind domain.

## Clock and audio connection

The current clock at `0x03003958` uses the already reconstructed eight-byte
`DisplayTimeRecord`. The access view adds clocks at relative `+0x71C` and `+0x724`
and an enable byte at `+0x72C`. Only those fields are named; the intervening bytes
and complete world storage remain unknown. The names `first` and `second` reflect
the observed order of comparisons rather than an established gameplay event.

The refresh captures a null palette result before reading the clock period.
A changed period updates scene context `0x03004320 + 4`, then queries the original
palette selector. For an unchanged period with the enable byte set, the accepted
time-equality helper compares hour and minute through mask six. A first-clock
match sets context flag one and can load background animation one; a second-clock
match clears that flag and can stop the default animation. Game flag `0x10` gates
the animation operations, and the load also requires scene ID at most fourteen.
The alpha configurator follows either eligible animation change.

The palette selector is queried after the enabled-clock branch even if neither
clock comparison matched. A nonnull result creates the accepted palette job for
first colour 64, count 192, duration eight, interval zero and flags one. Its index
is stored at context `+8`, still named `unknown_08` in the existing shared type.
The compiler match does not justify changing every use of that shared word.

The audio refresh independently reads the current period and compares the saved
context period. Unless audio-control flag eight is set, periods zero through
three select one byte at table-record offsets eight through eleven; other
periods pass zero. Records at `0x08057224` have the same twelve-byte stride and
base as the existing palette-range configuration access view. The new bounded
view interprets only these four audio bytes and does not infer a table bound.
The call uses the accepted `audio_select_sequence` provider.

## Retained display connection and boundaries

The allocator obtains 512 zeroed bytes for context `+12` and writes scene ID 50.
The retain path forces a background-animation reload, calls the explicit original
provider at `0x9DF0`, and snapshots map VRAM through the accepted map helper.
Unless game flag `0x20000` is set, it calls the original provider at `0x121C` and
sets game flag eight. It then sets request mode two and copies 256 halfwords
from OBJ palette memory `0x05000200` to the retained palette allocation. The
BIOS-copy control is the original halfword count, not an inferred byte count.

The short release path calls original provider `0xA834` and the accepted map
resource release. Its complete boundary is `0x2697C..0x2698C`: the next PUSH at
`0x2698C` begins a separate 100-byte cleanup function. An earlier raw inspection
range combined them; that range is retained as evidence and is not credited as
one function.

The separate cleanup runs only with game flag eight. It clears that flag,
uses original provider `0x125C`, releases the primary linked object list and
calls original provider `0x2EB9C`, then clears both reconstructed transient-effect
families. It clears audio-control bits one and eight, destroys map registration
through the canonical grid helper, clears the registration pointer, and calls
the short release's two providers. The volatile audio-control field retains its
observed read/update accesses. Unconverted providers remain explicit; their
call-site signatures do not establish their full bodies.

The primary-step early-exit query is exactly four bytes at `0x269F0..0x269F4`
and returns byte zero. The following PUSH at `0x269F4` begins a separate dispatch
body. Its table and cases receive no credit from the constant query. The byte
return spelling is supported by its accepted caller's narrowing and comparison;
it remains a provisional C contract.

## Verification and retained failures

Local complete comparisons and current header/source receipts are recorded in
`reports/agents/frame-input/scene-primary-view/scene-environment-ready.json` and
its canonical proof directory. Each source has a real separately compiled
mutation: palette-job duration, audio gate, allocation size, request mode,
release provider, cleanup gate or query result. No comparison was masked and
no output was patched.

The connected 192-byte `scene_palette_source` at `0x26794` remains unconverted.
It selects among four pointers in sixteen-byte records at `0x0805747C`, with a
fallback word at offset `0x40` in the existing 72-byte scene-resource records.
The retained best complete-size attempt differs in 85 bytes; the initial
188-byte attempt, pointer-lifetime variants and raw originals remain private.
A declaration-after-statement compiler rejection is also preserved. Neither
matching prefixes nor the original palette provider receive C credit.

Next targets are that selector and the original retain/release providers, while
the central object renderer and copied ARM sort remain difficult explicit
candidates. Today's fixed 319,640 mapped-extent comparison baseline is not a
claim of complete game coverage.
