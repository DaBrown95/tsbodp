# Scene target and spawn-point resources

This connected source batch reconstructs four functions and 248 matching C
bytes. These paths connect resource-table factories to the already recovered
primary-list queries and the shared actor-state dispatcher. The names describe
observed data flow; their full gameplay roles remain provisional.

| Address | Extent | Matching C function |
| --- | ---: | --- |
| `0x0803A5B4..0x0803A614` | 96 | `frame_create_scene_target_resource` |
| `0x0803A648..0x0803A660` | 24 | `frame_scene_target_resource_step` |
| `0x08016B9C..0x08016C04` | 104 | `frame_create_spawn_point_resource` |
| `0x08016C50..0x08016C68` | 24 | `frame_spawn_point_resource_step` |

The factory table rooted at `0x0804F278` has slot 15 at `0x0804F2B4` pointing
to `0x0803A5B5`, and slot 18 at `0x0804F2C0` pointing to `0x08016B9D`.
Each is a compatible two-byte-argument `ResourceObjectFactory`. The constructors
allocate through the accepted 64-byte scene-object allocator before retrieving
the selected payload. They convert signed halfword x/y coordinates to fixed
point by multiplying by 65536, copy the selector word's low halfword to object
ID, store flags `0x22000`, select state zero and variant one, install the
standard one-object step callback, and return the object. Allocation and
payload results remain unchecked, as in the original.

`ResourceObjectEntry.factory` is the halfword at byte eight of the object
record. The payload getter returns that same record's byte-eight address, so
the low halfword of its first word is the selected factory index. Under the
observed table dispatch, these two constructors therefore create IDs 15 and
18. The upper halfword is loaded but remains uninterpreted. The first payload
view has eight observed bytes and size/alignment 8/4. The second has ten
observed bytes and size/alignment 12/4, including two bytes of compiler-imposed tail padding in that partial
view. These word-load views express the original fullword access and
current object-record alignment preconditions; they do not establish every
serialized root's alignment, complete storage or capacity.

The ID-15 constructor clears the subtype halfword. The accepted 52-byte
`frame_find_scene_target` query selects ID 15 and returns its x/y coordinates;
state 34's 176-byte route handler and the 48-byte optional-choice completion
path use that query. The ID-18 constructor copies payload byte eight to the
subtype halfword and byte nine to object direction at `+0x12`. The accepted
76-byte `frame_scene_read_spawn` query requires ID 18 and the requested subtype,
optionally returns direction, and writes x/y. The accepted 400-byte scene actor
initializer spawns resource groups before using that query for a saved actor.

Both constructors install callbacks at object `+0x88`: their literal words are
`0x0803A649` at `0x0803A610` and `0x08016C51` at `0x08016C00`. Each callback
leaves state zero and states other than one alone. State one calls the accepted
468-byte `frame_run_actor_state` dispatcher, whose state-one branch updates
flags to `(flags & ~1) | 0x82`. The callback signatures agree with the standard
object dispatcher. No collision slot, generic callback interface or existing
header is changed. All four sources are ordinary C without register bindings,
assembly alignment directives, volatile accesses or fabricated initialization.

The existing `FrameObject` view is 312 bytes with alignment four inside the
observed 320-byte allocation. Its ID, subtype, direction, state, flags, position
and step-callback offsets are checked separately from matching bytes. Compatible
factory/callback/provider assignments and genuine wrong-width, signedness,
alignment and argument-type controls preserve the distinction between source
layout evidence and object equality. Literal pools and internal zero alignment
belong to each complete verified extent; adjacent accepted queries and the
following interaction handler have separate boundaries and gain no new credit.

Fresh positive and changed-source negative comparisons cover all four new
functions plus fourteen connected accepted callers and providers: eighteen
normal pairs and four additional strict declaration pairs. Separate diagnostics
check 51 layout facts, fourteen compatible assignments and seven changed-header
failures. Removing the actual allocator declaration retains each constructor's
legacy byte match but fails its strict declaration check. Private failed sources, the former
more coupled role headers and all raw controls remain retained locally.

Finite initialized-memory checks compare original bytes, linked source and
independent bit-pattern models using abstract allocator, position and state
providers. Additional constructor-to-query fixtures manually link the returned
object into an initialized primary-list fixture and execute the accepted query
bodies; their genuine changed-ID query controls distinguish the connection.
Caller-saved register poisoning and failure cases test these bounded models.
The 132 direct fixtures distinguish 108 actual source controls; all 76 chained
query fixtures distinguish their actual changed-ID controls. Thirteen
interpreter failure cases remain separate from game behavior. These checks do
not execute the full allocator or resource loader, establish arbitrary
pointer/domain validity, or prove gameplay. Other factory rows and unconverted
providers remain explicit in the current inventory; that inventory is incomplete.
