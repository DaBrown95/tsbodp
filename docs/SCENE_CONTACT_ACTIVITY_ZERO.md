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
sizes. The existing matching land-placement provider is retained; movement at
`0x08024720` remains unconverted.

The accepted algorithm reuses a retained earlier exact attempt after porting it
to current canonical owners and provider declarations. Its source spelling is
not proven historical. Option indices, resource populations, count/used-buffer
capacity, successful allocation, land-placement termination, later writers and
callback populations remain engine preconditions. Source ownership of this
initializer does not close the activity or executable inventory.
