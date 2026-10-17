# Shared point storage and callback contracts

`FramePoint` remains two 32-bit words. Only `FrameObject.next_position` now owns
an eight-byte named union: a real `FramePoint word` subobject and signed pixel
halves at object +0x22/+0x26. Object size 312, alignment 4 and all established
offsets are unchanged. Twenty-two existing C users adopt this storage view,
using the word subobject, its address or the pixel halves.
Six signed halfword reads in terrain, movement and transient emission now use
the actual owner instead of foreign short/point views.

The connected check also exposed two existing source-contract issues. The
render-effect resource destination now preserves its source's `const`
qualification; this does not make its sequence-pointer target immutable. Three
setters use the representable value -1 for the signed one-bit `render_special`
field, consistent with the existing negative-value readers and setter. No
bitfield signedness, storage, compiler profile or original output changes.

Private qualification covers 28 existing functions / 6,952 extent bytes: 28 normal
and 28 strict matches, with 56 rejecting actual source controls. ARM-target layout
and type checks cover 81 facts, 28 actual definitions and six deliberately wrong
contracts. Two earlier unexpected diagnostic failures remain explicit; they are
not relabelled negative controls. The fresh full matching/progress gate supplies
publication evidence for the integrated sources and headers.

Six additional initializer/tick bodies add 24 extent bytes: 18 instruction bytes
and six zero alignment bytes. They supply the remaining nonnull callback bodies
for observed definition rows 1, 79/86 and 132. Each has null definition +24/state FC;
the common nonoptional average query contributes 100 there. Initializer callers
pass the state and ignore the result; word-return one is a matching inferred
contract, not unique historical type recovery. State-F8 ticks take the state
pointer and do nothing. They are not removal callbacks.

Normal/strict source controls reject all six replacements. One first private
normal command array was not retained after a path-recording assertion; that
output remains a reconciled diagnostic. A failed integration gate exposed a
missing complete state definition in a tick control; the include repair changes
no body. The fresh full pilot records the actual publication inputs and controls.
Neighbouring EC 0x13360/8 remains original: its
selector writes no action bytes, so no grounded LR-saving switch is invented.

These are source and compiler findings. They do not close arbitrary definition
indices, writable callbacks, transitive dependencies or runtime populations.
The copied sorter's legal direct halfword loads still leave two mismatching
bytes; it receives no C credit. See the [remaining work](COMPLETION_BLOCKERS.md).
