# Collision-variant factory path

The observed resource factory slot eight at ROM `0x4f298` contains Thumb pointer
`0x0800bd69`. The accepted group walker supplies two byte arguments through
`ResourceObjectFactory`. The matching constructor owns `0xbd68..0xbe84`
(284 bytes); its installed one-object step owns `0xbe84..0xbeb8` (52 bytes).
Both complete extents include original zero alignment and the constructor's
internal literal pool and five-way jump table. The step's C symbol is 50 bytes,
followed by two original zero bytes; explicit source alignment supplies them.
Names describe the visible factory, palette, animation and collision connections
and remain provisional.

The constructor obtains a word-aligned payload prefix, allocates using its first
word, and copies signed halfword coordinates as 16.16 positions. It does not guard
allocation failure. It stores flags `0x60015`, copies payload byte eight to the
object subtype halfword at ten and separately to kind byte `0x4c`, clears contact
bits two and three and double-size bit five at `0xd1`, and applies the ground
layer. Bit four at `0xd1` is preserved. The constructor installs step pointer
`0x0800be85` at `+0x88` and the existing two-object movement-reset callback
`0x08011329` at `+0xc8`, stores 24 at `+0xae`, resets state and selects the subtype
palette. The role of byte `+0xae` is not inferred beyond that observed store.

Sharing byte `+0x101` first gains mask `0x02`. Kind zero clears that same bit;
kinds one through four store shared group zero through three at `+0x102`.
The final animation lookup rereads kind after the opaque palette call. Its
record root at `0x0804f368` has five observed 16-byte descriptors; the palette
pointer root at `0x0804f3b8` has five observed pointers. Default kinds still reach
unchecked palette and animation lookups. Neither this source nor the observed
prefix establishes complete table capacity or valid arbitrary identifiers.

A failed source used the unrelated byte at `+0x100` in the kind-zero branch,
producing 280 bytes with 92 differences. The original literal at `0xbe38` is
`0x101`, confirming the shared byte used above. A separate failed source kept
both the generic object pointer and a second typed view live across calls,
adding an unnecessary preserved register. The accepted source uses one actual
whole-object access root and ordinary API casts, without register bindings,
extra reads, dummy initialization, guards or volatile operations.

The pinned compiler verifies the payload view as 12 bytes/alignment four, with
accesses through byte eight. The whole-object access prefix is 260 bytes/alignment
four and fits the existing 320-byte allocation; the independently accepted generic
`FrameObject` view is 312 bytes/alignment four. Field checks include kind/state/
pending at `+0x4c/+0x4d/+0x4f`, step at `+0x88`, the byte at `+0xae`, contact at
`+0xc8`, and sharing/group at `+0x101/+0x102`. A compiled initializer verifies the
physical `0x2c` contact/double mask at `+0xd1`. The width-three counterexample is
also compiled against the unchanged constructor because initializer value three
alone does not distinguish those field widths. The wider original layouts and
serialized resource capacity remain unknown.

The step changes flags only in state one when bit `0x1000` is absent, clearing
bit zero and setting bit one. It clears pending-update byte `+0x4f` in every
state, including state zero and unhandled states. No state or flag condition is
added to that final store.

The accepted copied ARM collision dispatcher owns ROM `0xb0e8..0xb368` and
executes at copied address `0x03002a20`. Its callback array begins at `+0xc8`;
the observed transfers supply the two collision-object pointers in R0 and R1.
The installed movement-reset callback already consumed two arguments, but its
nominal `FrameObject` pointer tags differed from the dispatcher's concrete
`CollisionCallback`. Its declaration and formals now use `CollisionObject` tags
and real local `FrameObject` access views for the existing movement helper.
The updater's three explicit callback-slot storage casts use that same type.
Both old bodies match unchanged extents and unchanged source controls, with no
new C credit, address changes or function-pointer casts. All current literal
importers of the corrected header are freshly recompiled with their own controls.
The broader actor view and its separate one-argument callback field remain
provisional and unchanged.

New source and corrected old bodies pass the acceptance profile and a separate
strict declaration profile. Actual type assignments connect the factory to
`ResourceObjectFactory` and the installed callback to `CollisionCallback` in both
directions. Restoring either former nominal callback type is rejected by the
strict compiler. Real missing palette and movement-helper declarations can leave
legacy bytes unchanged while strict compilation rejects the source.

Finite initialized instruction fixtures cover all five observed variants,
coordinate extremes, preserved bits, state and flag combinations, nullable
allocation failure, and the already accepted two-object callback. The interpreter
executes the actual computed Thumb jump and poisons caller-saved registers at
abstract provider calls. Original and compiled bytes agree with an independent
branch model. Null allocation, an invalid table prefix and a null collision
partner are explicit model rejections; no source guard or hardware fault is
claimed. The palette, animation and ground-layer providers are abstract hooks;
the movement-reset hook models bounded existing field writes. High argument and
selector words and provider mutations are synthetic ABI or model-only cases.
These proofs do not establish complete resource bounds, gameplay or hardware
behaviour. Other original regions, including catalog confirmation, remain explicit.
