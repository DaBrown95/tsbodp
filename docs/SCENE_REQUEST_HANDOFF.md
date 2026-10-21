# Queued scene requests and frame handoff

Eleven connected C replacements cover 564 bytes at their original Thumb entries:

| Function | ROM address | Full extent |
| --- | --- | ---: |
| `scene_step_request_handoff` | `0x08027CAC` | 168 |
| `scene_initialize_request_queue` | `0x08027D54` | 80 |
| `scene_current_request_kind` | `0x08027DA4` | 12 |
| `scene_queued_request_kind` | `0x08027DB0` | 16 |
| `scene_submit_default_request` | `0x08027DC0` | 16 |
| `resource_submit_scene` | `0x08027DD0` | 32 |
| `scene_step_transient_and_views_unrooted_27df0` | `0x08027DF0` | 48 |
| `scene_request_changed` | `0x08027E20` | 36 |
| `scene_run_begin_callback` | `0x08027E44` | 56 |
| `scene_run_step_callback` | `0x08027E7C` | 40 |
| `scene_run_end_callback` | `0x08027EA4` | 60 |

All are ordinary C without register bindings or instruction-body assembly.
Full extents include literal pools and alignment. The 14-byte default-wrapper
CFG estimate excludes its two alignment bytes; the change predicate similarly
occupies 36 bytes rather than its provisional 34-byte CFG envelope. The two
getters have separate returns and literal pools. The separately owned no-op
at `0x08027EE0` lies outside this eleven-body range.

## Shared records and call order

The existing 24-byte `SceneRequest` view at `0x03004350` is the active record.
The full structure assignments establish same-sized previous and queued views
at `0x03004370` and `0x03004390`. The previous address already has choice-state
and resource-argument overlays; those views retain their own observed roles.
Submission writes `kind | 0x80`, the second and third fullword arguments, then
zeroes the remaining three words. No input narrowing or bounds check is added.
The third word retains the active view's `scene` field name, but callers also
pass notice-owner pointer words there; it is not universally a scene ID.

`display_scene_stage_08027dc0` is the existing caller alias of
`scene_submit_default_request`. `display_menu_request_notice` is the existing
pointer-argument caller alias of `resource_submit_scene`; its three word-wide
arguments reach the same entry. Existing caller bytes remain unchanged. The
default wrapper submits the supplied kind with zero mode and argument.

Initialization clears the active first word, copies the active record into
both other views, calls the provider `0x08026908`, then
queues kind 12 or 3 according to save-header byte 11. That byte's broader
meaning remains provisional.

The handoff calls the accepted 200-byte `transition_link_update` provider at `0x0803D6C0` and increments the existing
frame allocation epoch. It compares the two complete first words, including
the queued `0x80` bit, so a request can force a handoff even when its underlying
kind is unchanged. During a change it sets game flag `0x10`, runs the old phase's
end callback, clears the queued `0x80` and game flag `0x800`, copies active to
previous and queued to active, runs the new begin callback, then clears `0x10`.
There are no extra writes to those flags outside the observed sequence.

Every iteration increments IRQ-context `frame_work_count` at `+0x30`, polls
input, runs the active step callback, requests object refresh, steps backgrounds,
calls the window and palette update providers, and prepares OAM
transfer. This connects accepted input, display and VBlank transfer functions;
it does not establish runtime timing or gameplay correctness.

The refresh provider returns a byte, as established by its accepted C body
at `0x08001168`; this caller discards that result. The shared queue declaration
is corrected from the initial void return spelling to `unsigned char`, and all
ten queue consumers retain identical bytes and rejected source controls after
that type correction. This adds no reconstructed C coverage.

## Indirect transfer evidence

The three callback fields occupy offsets 0, 4 and 8 of a 12-byte ROM row at
`0x0805797C`. The begin phase skips the previous-kind-2/current-kind-1 case.
The end phase skips a queued kind of 2 after masking `0x80`; the step phase only
tests its pointer. Each phase checks its callback before invoking it. Pointer
dispatch compiles through the existing `_call_via_r1`, `_call_via_r0` and
`_call_via_r2` bridges at `0x0804CCF4`, `0x0804CCF0` and `0x0804CCF8`. These
low-level bridges retain their separately counted assembly ownership; this
cohort adds no bridge coverage.

The initial bounded inspection retained rows 0 through 16. The connected
[primary callbacks](SCENE_PRIMARY_CALLBACKS.md) extend it through row 27, ending
at adjacent nonpointer data, and add the 84-word physical table to the static
map. Row 1 begins at accepted `scene_initialize`; row 15 begins at accepted
`display_menu_initialize`. Current ownership is recorded in the manifest and
linked callback notes; row zero's distinct no-op entry `0x08027EE0` is already
source-owned. No arbitrary kind validation or
callback-argument contract is inferred. The active-kind getter has no
established inbound call in the current static map.

## Verification evidence

The first semantic record-copy and handoff candidates match naturally.
Expressing the change predicate with its unequal branch first closes three
conditional/return-byte differences. Capturing the real callback table before
the active kind closes 13 load-order and literal-pool differences in the begin
phase. Neither adjustment adds dead accesses or output padding.

Each current source has an actual compiled changed-source control, and the
comment-updated palette-menu transition consumer is reverified with its control.
The current paired build proof retains complete comparisons, controls and
source/header contexts. Unique historical source attempts and bounded findings
remain in ignored reports; obsolete generated payloads are retired under the
[retention policy](LOCAL_OUTPUT_RETENTION.md). Names and callback types follow
static accesses and compiler matches; no runtime claim is made.

The remaining work includes unowned scene callbacks and the original
`0x0803D850` transfer-completion provider. The current
[blocker list](COMPLETION_BLOCKERS.md) governs the next targets.

## Unrooted transient and view coordinator

The adjacent body at `0x08027DF0` calls `frame_step_transient_effects`, then
starts an unsigned byte index at zero. If it is below the count at the existing
`ScenePrimaryViews` root `0x030040E0 + 0x30`, it calls `scene_update_view(index)`,
increments the byte and tests a fresh count. The count address is retained only
inside the reached loop; no count snapshot, clamp, extra read or new state view
is introduced. The two provider definitions keep their separate compilation
contexts and existing void/no-argument and void/word-argument interfaces.

The complete 48-byte extent contains 44 instruction bytes and the four-byte
root literal at `0x08027E1C`, with no alignment tail. Normal and strict source
comparisons and genuine increment-by-two controls cover that full extent.
Actual-definition and API/layout checks use the shared count owner. This
replaces one old estimated row and adds no new mapped extent.

No current direct caller or canonical entry word establishes an incoming root.
The chosen void/no-argument interface and unused historical formals remain
provisional. Reached view/provider backing and a suitable live count remain
preconditions; the four-slot access view does not prove every count or writer.
This is compiler and static evidence, with no new runtime or gameplay claim.
