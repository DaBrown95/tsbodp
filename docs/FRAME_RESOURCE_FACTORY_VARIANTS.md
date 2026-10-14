# Render-variant and timed-selector factory paths

The USA/Europe revision-0 resource factory table has observed entries at
`0x4f2d4` and `0x4f2c8` containing Thumb addresses `0x0804155d` and
`0x080271e1`. These are table slots 23 and 20, respectively. The accepted
resource-group walker supplies two byte arguments through `ResourceObjectFactory`.
The two new factory declarations use that exact pointer type. Names describe the
observed call and field roles; they remain provisional.

The render-variant factory owns `0x4155c..0x41610` (180 bytes). It obtains the
resource payload, allocates using its full first word, and returns immediately
when allocation fails. Successful allocation copies signed halfword coordinates
as 16.16 positions, copies subtype byte eight into the object halfword at ten,
clears the two contact bits at `+0xd1` and its double-size bit, and sets layer one
at `+0xd5`. Bit four at `+0xd1` is preserved. Subtype zero enables `0x40001` and
acquires palette slot two; subtype one enables `0x40011` and installs the palette
pointer root at `0x0807fb2c`. The subsequent animation lookup reloads the object
subtype after the palette call, then the existing state-update wrapper computes
its ground layer. The initial layer store is an observed store even though that
later provider can replace it.

The pinned compiler makes the payload access view 12 bytes/alignment four;
accesses cover bytes zero through eight. The whole-object bitfield prefix is
216 bytes/alignment four, with its actual stores at `+0xd1` and `+0xd5` inside
the accepted 320-byte allocation. The generic `FrameObject` view is independently
312 bytes/alignment four. None of these prefixes establishes a complete original
object or serialized-record capacity. A diagnostic initializer produces `0x2c`
at `+0xd1` and `0x04` at `+0xd5`. Initializer value three alone cannot distinguish
a two-bit contact field from a three-bit field: the genuine wrong-width control
also compiles the unchanged constructor, producing 180 bytes with 26 differences.
The existing generic three-bit field remains a separate provisional access view.

The animation pointer root at `0x08d7416c` has two observed valid descriptors,
`0x0807fa8c` and `0x0807fadc`. The following word is `0x00c900d9`, which is not
a valid descriptor address. The palette root begins with `0x08afae08`, the same
palette pointer found in the subtype-one animation descriptor; its following
word is `0x00001c03`. The declarations express pointer roots with unknown
capacity. The constructor's default subtype path still performs an unchecked
animation lookup; valid subtype bounds and palette-frame bounds are not inferred
from a matching constructor.

The timed-selector wrapper owns `0x271e0..0x27218` (56 bytes). It calls the already
accepted 480-byte scene-selector constructor, obtains the payload again, and
copies bytes 13 and 14 into the returned object's existing hour fields at
`+0x67` and `+0x68`. The byte-only tail view is 15 bytes/alignment one; it does not
move or append fields to the parent's 16-byte/alignment-four payload view. The
parent's native word-access precondition still applies to actual resources.
The fresh payload lookup remains after the parent call. In selector state four,
the accepted 524-byte tick copies those hour bytes into clock records and passes
them to the time formatter and the two text-field providers.

The parent can return null for its scene-two/selector-thirteen/save-flag guard.
The wrapper has no null guard and performs its two unchecked byte stores. This
path remains explicit. It does not install a new interaction callback or refine
the existing selector callback views.

Both functions use ordinary C without register bindings, inline assembly or
volatile accesses. Their entire original extents, including all literal pools
and alignment, match under the pinned acceptance profile and the separate strict
diagnostic profile. The render factory's flags-helper prototype and the timed
wrapper's parent prototype are required explicitly: removing either declaration
can leave legacy byte equality while the strict compiler rejects the source.
The existing getter, group walker, allocation, position, flag, palette, animation,
layer, parent-constructor, tick and interaction contexts are recompiled with their
actual changed-source controls under current literal header snapshots.

Finite initialized instruction fixtures compare original bytes, compiled bytes
and an independent branch model with abstract provider effects and caller-clobber
poisoning. They cover allocation failure, both observed render subtypes, preserved
contact bit four, coordinate extremes, hour extremes and explicit provider
mutations. Invalid animation pointers and the timed null-parent store are model
rejections. High argument words, high selector bits, out-of-range hours and injected
provider mutations are ABI or model-only cases. The animation hook covers only
its descriptor delay; palette and ground-layer hooks are bounded abstractions.
These checks do not establish gameplay, complete resource bounds, hardware
behaviour or execution of every original provider. Unconverted neighboring
factories and the catalog confirmation remain explicit original regions.
