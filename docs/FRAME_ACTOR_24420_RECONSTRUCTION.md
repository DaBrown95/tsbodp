# Actor constructor at 08024420

`frame_create_actor_24420` owns the complete 320-byte source extent at
`0x08024420–0x08024560`: 274 bytes of Thumb instructions, 44 bytes of compiler
literal pools and two alignment bytes. Its gameplay role is provisional.
The source installs three renderer part tables using the shared selected
appearance, assigns part order and horizontal flip, and installs step,
pre-step and collision callbacks. The matching 108-byte step callback at
`0x08024968` refreshes the animation variant and horizontal flip from pending updates, then clears those updates.
The matching 28-byte part flag setter at `0x08001584` enables bit 1 in a
canonical part record. These three bodies own 456 bytes in total. The shared
vector constructor `frame_make_direction_vector` at `0x080019CC` adds 60 source bytes, and
`frame_approximate_vector_length` at `0x0802736C` adds 52. All five bodies
therefore own 568 bytes. The 48-byte contact callback at `0x08024A08`
adds the connected state-eight writer, bringing these six bodies to 616 bytes.
It disables flags 5 on the colliding object, enables flag 2 and assigns state
eight to the other object when its ID is zero, then plays cue 181.

The callback now calls the matching 472-byte
[movement worker](SCENE_CONTACT_ACTIVITY_ZERO.md#movement-worker) at
`0x08024720`, bringing these seven bodies to 1,088 source bytes. Its early
dispatch uses only the existing states two, three and eight, preserving the
native tree before the handler bodies. The vector constructor writes a scaled
direction to an output point; approximate length receives a two-word point by
value and returns the larger absolute component plus three eighths of the
smaller. Their actual public interfaces agree with the movement source.
Backing, selector/writer domains and complete activity gameplay remain open.

The direct call at `0x080242E6` loads a contiguous two-word position from
`0x08056284` into `r0/r1`, with direction in `r2`. A `FramePoint` passed by value
reproduces the constructor's register lifetime and full extent. Treating the
coordinates as two independent integer parameters emitted two extra argument
moves; narrow coordinate parameters emitted entry truncations absent from the
reference. Initial compiler RTL distinguishes the matching `DI` position
pseudo, read through two `SI` subregisters, from the independent scalar pseudos.
This is evidence for this constructor's ABI; it does not establish the
renderer or finalizer's unresolved source dataflow.

The complete matches and changed-source controls are retained in the local
proof package: cue `180` to `179` in the constructor, enabled part bit `2` to `1`,
and callback update mask `0x14` to `0x10`. Each of those changes one byte and
is rejected by the stable verifier. The vector controls substitute the X
component for Y and change the smaller-component factor from `3` to `2`;
these are rejected with 58 and 21 differing bytes respectively. The contact
callback changes state eight to seven and rejects by one byte. These matches
do not establish complete bounds for the indexed ROM tables. Earlier private
activity-zero proofs already recorded the constructor ABI, callback and vector
matches; this intake uses the canonical headers and fresh controls.
