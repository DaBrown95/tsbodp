# First 32 KiB source milestone

The USA/Europe revision-zero target now has 309 verified matching C functions
covering 32,828 bytes, including their literal pools and alignment. The starting
baseline was revalidated at 19 functions and 676 bytes: the gain is 290 functions
and 32,152 bytes. The final connected batch adds 58 functions and 6,280 bytes to
the previously published 251-function, 26,548-byte state.

The fixed comparison baseline is the 319,640 mapped extent bytes observed at
the start of this goal. It is a static estimate, not a complete inventory of
the game's code, and is not the denominator for whole-ROM source coverage.

The reconstructed paths include:

- Interrupt setup and callback tables, VBlank wrapper, wait/acknowledgement and
  frame/audio handoff. The copied ARM dispatcher and necessary CPU-state glue
  are explicit assembly, separately counted at 352 bytes.
- Frame scheduling, object lifecycle, actor animation and need state, input
  sampling/repeat/direction updates, indicator creation and effect construction.
- Display transfer queues, sprite/background preparation, OAM/affine and palette
  lifecycles, copied ARM tile allocation and collision callback dispatch.
- Resource group execution and its full observed nonzero command callback
  family, connected view configuration/math, condition completion/scene
  selection, and game-facing sample/sequence control and VBlank coordination.

These are connected source paths with remaining original dependencies, not
claims that the complete frame, display, resource or audio engines are decompiled.
The subsystem evidence notes record the observed field offsets, callback
installation, indirect targets, copied RAM execution addresses and provisional
names. In particular, copied C is linked at its observed RAM execution address
and integrated at its original ROM load address; it is distinct from ARM glue.

The final `make progress` gate rebuilt and compared every accepted extent,
including 290 per-function changed-source C controls and four assembly controls.
All were rejected; the original baseline's generic changed-source control was
also rejected. The linked 16,777,216-byte ROM was identical to the fixed reference,
and its independent changed-source whole-ROM control was rejected. `make test`
passed all 72 tooling tests. Inventory and the public treemap were refreshed.
Source and helper hashes were checked for drift after the gate.

The fixed SHA-256 remains
`92ead9ff9467dbc23780e768278fe2e4bf7a0708447a0785770c129a5dbdb06e`.
The build accounts for 32,828 C bytes, 352 assembly-glue bytes and 16,744,036
explicitly unconverted bytes. Whole-ROM equality does not establish runtime,
audible output or gameplay behaviour; those have not been tested here.

Remaining uncertainties include the complete actor/collision allocation limits,
individual need labels, several movement-table flag meanings, condition and scene
semantics, and unresolved indirect callees. The next connected targets are the
actor state dispatcher and handlers, object renderer/finalizer, view controller
at `0800E3A8`, background-map rectangle operations, condition activation/refresh,
and audio sequence/mixer internals. Useful close matches are retained locally
without source-coverage credit. No reference changes, output patches, masks,
original instruction-body transcriptions or speculative matches were accepted.
