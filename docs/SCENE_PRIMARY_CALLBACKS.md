# Primary scene step and exit

The two callbacks at `0x08026014/392` and `0x0802619C/280` add 672 matching C
bytes, including every pool and alignment byte. Both are ordinary C with no
register bindings or instruction-body assembly. They are the step and end
columns of scene-phase row 1; its begin callback is the already accepted
808-byte `scene_initialize`, which receives no additional credit here.

## Connected frame and input path

The step captures the selected actor through four 12-byte view slots. It checks
the selected 56-byte status row's word at `+4`, calls the original `0x0803C598`
provider when mask `0x1C0000` is clear, and returns after clearing game flag
`0x20` when the accepted four-byte `scene_step_early_exit` query returns byte value one.
The query currently returns zero; its call and conditional remain in the matching
caller.

It then updates each view's map and the original view provider, advances
transient effects and character animation, and tests the captured actor's
state/variant. States 16 and 27 can process input unless variant five, view
effect mode one or game mask `0x810` prevents it. Pressed bit eight queues the
byte at world `+0x73F`; otherwise bit four in either first input slot queues
kind 11. Both paths call the accepted cue API with four. The final per-view
loop runs the accepted environment and period/audio providers for the selected changed view, and updates
each view only while the queue's change predicate remains zero.

The count is reloaded after calls. Its byte-width loop preserves wrap and
unchecked indexing rather than introducing bounds. Capturing the initial
count before the variant address, then creating the real count pointer only
inside the nonempty loop, closes the remaining register/lifetime differences.
Capturing the existing resource-effect base before the selected byte preserves
the original load and pool order. No dead reads or synthetic barriers are used.

## Exit and retained state

The exit selects the accepted fade path from game mask `0x20020`, then saves
the first actor's direction and signed integer coordinates into view bytes
`+7`, `+8` and `+10`. The existing actor's `position.x/y` are signed 16.16 words;
right shifts by 16 naturally compile to the original signed halfword reads at
actor `+0x1A` and `+0x1E`. A halfword-only access view produced shorter,
nonmatching unsigned loads and is excluded.

It passes scene entry data and scene ID to original `0x080202E0`. Five distinct
calls to the queued-kind getter select the retained-state path for kinds 5,
13, 1, 20 and 27; other kinds use the original alternate provider. Expressing
that ordinary condition with the alternate branch first preserves the original
branch and pool placement. The five calls remain individual; the getter is not
declared pure and no cached-value substitution is introduced.

Game flag `0x20000` causes `0x100000` to be set. The accepted selected-row
object cleanup runs before the request-mode branches. For request mode zero, the exit
runs the original audio provider, releases the primary object list,
clears the accepted active need-effect states,
passes the registration pointer to accepted `frame_destroy_map_registration`, clears it, and clears
the audio-control bit eight. The shared volatile eight-bit field retains both
original reads around that update. Mode two resets tile allocation; other
modes clear transient effects. The common tail clears render effects, releases
scene transient tiles, resets deferred display and the original palette
provider, resets display and installs the accepted default VBlank callback.

## Shared access views and static table

`scene_primary.h` imports the existing actor and fixed-point definitions.
Its slot view overlaps the established input/view context at `0x030040E0`.
The 56-byte initial status view starts at `0x03004130`, with flags at `+4`;
the change-word view starts at `0x03004134`, matching existing need/UI records.
The resource-effect mode uses the existing 40-byte `ResourceViewEffect` type.
The single world request byte at `0x03003950 + 0x73F` has a bounded access view;
its wider gameplay meaning and the complete world layout remain uncertain.

Expanded local inspection verifies 28 consecutive three-pointer rows at
`0x0805797C..0x08057ACC`. All 84 words are Thumb entry forms; adjacent packed
data is not a pointer row. The exit's observed kind-27 calls independently
support including the final row. The map stores this physical table as 84
flat pointer entries and records the 28-row, 12-byte organization. Per-site
target lists conservatively include all phase columns. This does not establish
arbitrary runtime kind bounds, exhaust all callback contracts or prove runtime
reachability.

Observed table entries remain runtime uncertainty when `targets_complete` is
false. The inventory callback counter now also includes incomplete observed
tables and direct dynamic calls; ROM/RAM aliases count once at their physical
site. Regression fixtures cover populated-but-incomplete tables, complete
calls, noncall dispatches and duplicate aliases. This is a mapping improvement,
separate from C byte coverage.

## Verification and next targets

Both current public sources have rejected one-byte changed-source controls,
complete linked extents and current source/header receipts. Useful count-loop,
coordinate and branch-order failures remain under ignored
`reports/audio-root/scene-primary-callback-trial/`,
`scene-primary-step-scopes/`, `scene-primary-count-coordinate-types/`,
`scene-primary-private-controls/` and `scene-primary-canonical/`. A failed
promotion with an incomplete resource-effect type is retained separately;
the accepted source uses the existing complete type.

Next connected targets are the original per-view updates, retained scene-state
providers, the remaining scene-phase families and the transfer-completion provider. Names
and types reflect static accesses and compiler matches. No runtime, gameplay
or physical-save claim is made.

The later cleanup closure replaces the original `0x0802EB9C` alias with
`frame_clear_need_effect_states`. The accepted step and exit receive current
positive and changed-source proofs after that declaration change. Their byte
credit stays at the original 672; the 104-byte provider is counted once in its
own connected batch.

The local-selection ingress at `0x0803C598` is now connected through
`frame_step_local_need_effect_selection`. The step's gated call retains its
original address and signature; the provider adds 112 bytes in the selection
and schedule batch. Both primary callbacks receive fresh positive and actual
changed-source proofs against the updated declarations, with no additional
credit for their already accepted 672 bytes.
