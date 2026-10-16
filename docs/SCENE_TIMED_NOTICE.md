# Timed notice scene

Three connected C callbacks own the complete `0x08024C04–0x08024D18` interval:
**276 C extent bytes**, with no assembly instruction bodies. The names describe
the observed setup/timing behavior; the scene's original name is unknown.

| Callback | Original address | Complete extent |
| --- | --- | ---: |
| `scene_timed_notice_initialize` | `0x08024C04` | 188 |
| `scene_timed_notice_step` | `0x08024CC0` | 72 |
| `scene_timed_notice_shutdown` | `0x08024D08` | 16 |

The initializer configures two backgrounds and a font, renders text entries zero
and two while retaining the returned tile position, runs transition `(63, 1)`,
selects audio sequence zero and starts 60/90-step countdowns. The step callback
allows an input-triggered request after the shorter countdown, or requests scene
four when the longer countdown completes. Its short-circuit evaluation preserves
which counter calls execute. Shutdown runs transition `(63, 0)`.

The fixed callback words at ROM `0x579A0` identify these three entries as row
three of the audited scene dispatch table. Their source extents are independently
verified and disjoint: 242 instruction bytes, 28 pool bytes and six original
zero-alignment bytes. Shared declarations reuse the accepted display, audio,
input, transition and counter APIs; original resource data remains separate.
The countdown, input-mask and shutdown-mask controls each retain size and reject
by one byte. All frozen source and candidate hashes are preserved.

Current source/header snapshots, commands, raw comparisons, API check, frozen
hashes and exact scene-row relationship are retained under ignored
`analysis/audio-timed-notice/publication-canonical/`,
`publication-hashes.json` and `scene-row-relationship.json`. These are static and
compiler comparisons. No runtime execution, complete dispatch/index domain or
resulting gameplay is claimed.
