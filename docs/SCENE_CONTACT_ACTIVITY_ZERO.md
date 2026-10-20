# Activity-zero initialization

`scene_contact_activity_zero_initialize` at `0x0802425C` reconstructs its full
452-byte extent: 390 instruction bytes, sixty referenced literal bytes and two
alignment zeros. Normal and strict comparisons match, and changing the actual
used-buffer initialization from 43 bytes to 42 rejects by one byte in both
profiles. This is source/compiler evidence without new gameplay observations.

The initializer configures the background, palette slots and two transient
definitions, sets the existing state flag, creates the primary actor and
publishes it into the first player slot. It clears the 43-byte used buffer,
copies the selected option's clock, and creates items of kinds two, three and
four using their separate counts. Its final loop creates option objects, places
them on land, changes their flags, installs the relation callback and sets
speed `0x30000` with timers 120 and 80. It retains the native count reads,
unconditional dereferences and lack of allocation recovery.

The source reuses the existing actor-item state and twenty-byte option record,
twelve-byte scene-player slot, option-object fields and collision owner. The
native stores clear secondary callback `+0xCC` and install the relation callback
at `+0xC8`. Both use `CollisionObject.on_collision[2]`; the existing dispatcher
and installed callback share the two-object self/other protocol. No new
collision overlay or callback cast is introduced.

Two include guards allow the actual public source to compose its actor-item,
player and option headers. Removing either guard makes that same source fail
on repeated definitions; this is an actual include requirement. Each of the
thirteen direct providers remains exact under normal and strict compilation in
its separate source context. Target checks cover thirteen physical offsets and
sizes. The existing matching land-placement provider is retained. Movement at
`0x08024720` now matches separately, as described below.

The accepted algorithm reuses a retained earlier exact attempt after porting it
to current canonical owners and provider declarations. Its source spelling is
not proven historical. Option indices, resource populations, count/used-buffer
capacity, successful allocation, land-placement termination, later writers and
callback populations remain engine preconditions. Source ownership of this
initializer does not close the activity or executable inventory.

## Movement worker

[Matching C](../src/frame/frame_actor_update_24720.c) owns all 472 bytes at
`0x08024720`: 430 instruction bytes, 36 literal bytes and six zero alignment
bytes. The step callback at `0x08024968` calls it before applying pending
animation updates. The existing constructor installs that step callback.

The source captures the byte state once and dispatches states two, three and
eight before entering any handler; other values return. State two starts
acceleration or limits velocity, state three updates direction and applies the
selected option speed, and state eight initializes or expires its timer while
turning the actor. The native discarded vector-length call remains present.
Separate handler labels retain the original dispatch topology; the earlier
switch and inline branch bodies selected a different compiler tree. No state,
side effect or idle case was added to move the compiler pivot.

The actor uses the existing `FrameActorObject`, and the selected speed uses
`FrameActorItemState` and the twenty-byte `FrameActorItemOption`. The actual
vector, direction, flag, timer and variant providers retain their public
contracts. The short R0 player argument is used by the immediately following
rotation call, with no intervening call or conflicting live value.

Normal and strict checks give 22 exact positives and reject 22 real source
controls across the worker, nine providers and its caller. Changing the actual
random upper bound from 31 to 30 changes one byte. Twelve actual API contexts
pass, eight wrong contracts reject, and target checks establish 34 layout and
three type facts. These compiler findings add no runtime qualification.

Defined inputs require a live writable actor, input player below four,
direction below sixteen where the vector table is read, and live scene and
selected option backing. Approximate-length calculations require representable
signed arithmetic, including absolute values and the smaller-component scaling.
The initializer does not prove those domains for arbitrary later writers.
Allocation, resources, callback populations and complete activity gameplay
remain open.
