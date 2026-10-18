# Bounded inventory follow-up, 15 October 2026

This is the earlier bounded checkpoint. The subsequent requested
[whole-ROM survey](WHOLE_ROM_INVENTORY.md) supersedes its open audio-kernel and
conservative phase-column annotations; the historical findings below are retained.

This internal pass reviewed 23 scoped sites or boundary facts across three
connected clusters. Existing maps, matching caller receipts and local failed
attempts were inspected first. Original-image control flow and literal loads
support the static findings below; they do not establish runtime reachability,
complete callback populations or recovered C. Raw traces and comparison evidence
remain in ignored local reports.

| Area | Established static evidence | Confidence and remaining uncertainty |
| --- | --- | --- |
| Scene callbacks | Calls at `0x08027E66`, `0x08027E94` and `0x08027ECA` select fields 0, 4 and 8 of the 12-byte rows at `0x0805797C`. Each observed column has 28 entries. | High confidence from fixed-ROM loads, veneers and matching caller source/control pairs. Runtime kind bounds and unconverted-callback argument contracts remain open; the exporter currently retains a conservative union of all columns. |
| Phase 7 | Callback entries are `0x08024E18`, `0x08025038` and `0x0802579C`. The step has a 708-byte CFG envelope, not the 1,892-byte distance to the shutdown callback. Its guarded nine-case table contains local Thumb blocks. | Static envelopes, not compiler-owned sizes. The initializer's 542-byte envelope excludes two following zero bytes; a future full comparison must examine the proposed 544-byte aligned span. Shutdown has 40 instruction bytes and eight literal bytes. |
| Finalizer | The reviewed 348-byte span at `0x08003248` contains 326 reachable instruction bytes, 20 referenced literal bytes and two zero alignment bytes. Pools are `[0x08003278,0x08003280)`, `[0x08003350,0x08003354)` and `[0x0800339C,0x080033A4)`. | High bounded static confidence. This corrects a prior local two-pool note. The terminal register transfer is a saved-return epilogue; no callback or jump table was found. Ordinary matching C remains unresolved. |
| Renderer | The 1,400-byte envelope at `0x080023E8` contains 1,292 instruction bytes, 96 referenced literal bytes and 12 zero alignment bytes. Nine direct calls reach five providers. | Resource and variant pointer selection is data access, not a code-pointer table. Matching C and universal resource/owner contracts remain unresolved. |
| Object callbacks | `before_step`, `on_step` and `on_remove` are writable object fields at offsets `0x98`, `0x88` and `0x8C`, called at `0x08001D2E`, `0x08001D4A` and `0x08000940`. | Matching consumers establish the slots, object argument and ignored results. Target populations remain open. The step consumer reloads flags after the callback. |
| Copied object ordering | The scheduler's fixed ARM target `0x03002900` maps to ROM `0x0800B840`. Its 284-byte copy contains 272 instruction bytes and a 12-byte pool, with no nested callback/table dispatch. | The historical `frame_draw_iwram` key is retained. Object-table ordering/sort is the supported provisional role; exact comparison semantics and matching C remain to be reconstructed. |
| IRQ/audio handoff | Default IRQ slot 3 handles mask `0x10` (Timer 1); slot 5 handles Timer 0. The VBlank audio veneer reaches ARM `0x03001080`, the accepted 220-byte `audio_mix_frame` extent, comprising 204 instruction and 16 literal bytes. | Copy and fixed-target evidence is strong. Writable handlers and the tick callback remain dynamic; the latter is reloaded after channel mixing. |
| Mixer dispatch | The historical `index_load_runtime_address` at `0x03000D08` identifies the target-pointer load. Index byte loads occur at `0x03000CE4` and `0x03000CE8`, followed by the sum at `0x03000CF8`. | No universal index bound or mask was established. Null slots remain explicit, and eight copied-RAM kernel entries still lack proven function extents. Known source targets do not close the runtime target set. |

The generated inventory already records the reviewed renderer, finalizer and
copied-sort instruction/literal counts and the phase-7 step envelope. This pass
adds no safely established entry or mapped extent, so it leaves those outputs
and the verified treemap unchanged. Proposed column-specific target annotations
and corrected historical role labels remain separate from extent or C credit;
they can accompany the next relevant verified source/map batch.

The published baseline remains 1,678 matching C functions and 236,692 C bytes,
with 500 bytes of separately counted ARM/Thumb glue. The fixed historical
comparison is 319,640 mapped extent bytes; it is not a complete game-code
denominator. Whole-ROM equality, static mapping and runtime behavior remain
separate claims.

The pass ends here. Connected reconstruction resumes with the copied object
ordering routine and the phase-7 callback path, alongside the held ordinary-C
renderer/finalizer work. Exhaustive inventory is not a prerequisite.

## Object visibility helper at `0x080011B8`

The 100-byte helper returns one when `forced_visible` is exactly one. Otherwise it obtains the selected view origin, converts the object's position through the existing point provider, and tests inclusive bounds: X from origin minus 100 through origin plus 340, and Y from origin minus 100 through origin plus 260. The proposed interface is `int(FrameObject *, FrameU8)`; the actual provider definitions and ARM32 point/object layouts pass separate type and offset checks.

The complete native span matches under ordinary and strict compilation. The matching C keeps the real margin value in R6 and the cached origin X in R4 after the provider calls, with each upper-bound subtotal carried in R0. Those GNU register variables describe actual values and overlapping lifetimes; they contain no instruction bodies. The final two commutative operand orders also matter to the emitted Thumb ADD encodings. A changed margin is rejected in both profiles. These results establish one matching source spelling, not the original source or uniquely determined compiler choices.

The non-forced path still requires a valid view-origin entry and representable signed coordinate arithmetic. Type/layout checks do not establish every provider access's effective-type legality, incoming-call coverage or runtime behavior. The full matching and progress gates cover this source. The renderer, finalizer and view-index domains remain open.
