# Linked entry scene object setup

The scene callback table's observed row twenty-three contains begin, step and
end entries at `0x08003750`, `0x08003ABC` and `0x08005648`. The accepted catalog
handler queues this scene, and the accepted event receiver applies its actor
entry and notice actions. The table and these callers establish a connected
static path; they do not close every runtime scene index or callback target.

`scene_link_entry_build_linked_objects` at `0x08003F08` reconstructs the linked
object setup in 344 complete C extent bytes. It calls eight already reconstructed
providers for object creation, variant selection, positioning and text. It
creates the selected catalog actor, a separate object in pointer slot ten, and
two controls in slots four and five. The selected actor and both controls
receive variant eleven and the observed fixed-point positions. The caption loop uses the received participant
count and identifier: the caption whose index matches the received identifier
gets the fixed X position and shifted Y position; other captions use the
four-byte coordinate records directly.
It enables each caption object and sets the text background control afterward.
Names and participant roles remain provisional static interpretations.

The implementation uses existing `FrameObject`, catalog and received-join types,
plus a read-only four-byte caption prefix. Only its two coordinate bytes have
names; the remaining two bytes are unknown. Four rows are observed in the
connected fixed-count setup path. The linked loop relies on a received count
between zero and four at every test, valid catalog resources, at least eleven
writable pointer slots and successful allocations before dereferencing the
returned objects. It retains the original count and identifier reads around
opaque calls. No validation, allocation recovery or complete shared-RAM owner
has been invented. Position arithmetic uses representable signed products,
including negative positions, without shifting negative signed values.

The original 326-byte map estimate ended at the instruction return. The verified
344-byte envelope also owns its referenced trailing pool and alignment, ending
at the separately called entry `0x08004060`. Its disjoint classification is
292 instruction bytes, 48 referenced literal bytes and four zero alignment bytes.
The full linked span, both pools and all alignment bytes match. This boundary
repair adds no separate C credit beyond that one 344-byte function.

Strict compilation uses the actual provider headers. Target fixtures check
sixteen layout facts and eight callable types. Deliberately changing the caption
stride, variant argument width or position object's type is rejected; the actual
source control changes the first variant from eleven to ten and must fail the
full-byte comparison. The inventory tool now recomputes per-row observed byte
counts after the final extent overlay, including surviving estimate fragments.
Regression tests cover the formerly omitted trailing pool, out-of-extent
observations, dual byte roles and split fragments carrying stale larger counts.
This report correction adds no source credit or newly observed execution.
These are compiler and static findings. Runtime execution
and gameplay have not been validated.

The adjacent 404-byte builder remains unconverted: ordinary candidates have
seventeen and twenty-four differing bytes. Reusing its counters did not resolve
the allocation difference; retained compiler diagnostics explain that failed
hypothesis. The begin and step callbacks, the remaining setup/update helpers,
renderer and finalizer also remain explicit original regions. The begin
callback's selection representation and the step callback's ignored,
uninitialized payload words still require source-domain work. No reconstructed-C
credit is awarded for those candidates or for inventory discoveries. The
319,640-byte historical comparison remains fixed; a complete code denominator
has not been established.
