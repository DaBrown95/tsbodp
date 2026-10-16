# Startup counter slots

Eight connected ordinary C definitions own the complete `0x08045854–0x08045994`
interval, end exclusive: **320 C extent bytes**, comprising 282 instruction,
28 literal and ten original zero-alignment bytes. No assembly instructions or
original instruction bodies are embedded in the source.

| Function | Original address | Complete extent |
| --- | --- | ---: |
| `game_step_counter_slot` | `0x08045854` | 100 |
| `game_initialize_counter_slots` | `0x080458B8` | 24 |
| `game_reset_counter_slot` | `0x080458D0` | 44 |
| `game_start_countdown_slot` | `0x080458FC` | 44 |
| `game_start_incrementing_slot` | `0x08045928` | 48 |
| `game_pause_counter_slot` | `0x08045958` | 20 |
| `game_resume_counter_slot` | `0x0804596C` | 24 |
| `game_get_counter_slot` | `0x08045984` | 16 |

The startup entry calls the initializer, which resets indices zero through
three. The [shared view](../include/game_counter.h) gives each 16-byte record at
`0x03002200` an index word at zero, mode word at four, paused bit at byte eight
and unsigned counter at twelve. Other bits and bytes remain uninterpreted.
Mode one counts down while unpaused and reports completion at zero; mode two
increments while unpaused. The native scene callers at `0x08024C04` and
`0x08024CC0` start slots zero/one with values 60/90 and consume byte completion
results. Those callers are separate source-ownership work.

Two compiler explanations close this path. A one-bit paused field reproduces
the original negative preservation mask; a plain byte field narrowed it to 254.
The [stepper](../src/counter/step.c) uses a word-sized result assigned on every
path and narrows it at the byte return. This produces the original common
`r1`-to-`r0` exit. Initializing that result at entry extended its lifetime into
`r5`; making the local itself a byte let GCC alias constants directly to `r0`.
No register bindings or compiler-flag sweep were needed. The two explicit
alignment directives own genuine trailing zero word-boundary bytes.

All eight full extents match with unchanged frozen source and candidate hashes.
Each actual source/header comparison includes a real rejected control: slot
count, paused state, mode, increment, modified field or returned field. Seven
controls retain size. Changing pause to resume produces 24 bytes against the
20-byte reference and rejects by 17 bytes. The existing verifier compares the
entire changed output and accepts a rejected control regardless of its size;
no verifier change, trimming or masking was introduced.

Current local proofs, API/layout checks, exact gap-free interval accounting and
frozen hashes are retained under ignored `analysis/startup-init-458b8/`, using
`publication-canonical-report.json`, `publication-hashes.json` and
`module-partition.json`. Names and type views remain reconstructed. These are
static and compiler comparisons; complete incoming index/transfer domains,
entry-specific runtime execution and gameplay are not established.
