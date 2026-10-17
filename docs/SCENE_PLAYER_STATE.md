# Player actor initialization

The initializer at `0x0801E1BC` reproduces 140 complete extent bytes, including
its literal pool and alignment. Its proper interface takes `FrameObject *`
and an unsigned player byte. The already owned player constructor allocates
320 bytes, constructs the existing actor view and calls this initializer.
The declared actor view occupies 312 bytes; the allocation size is not a new
structure layout.

The initializer installs the original `0x0801DFE5` step callback, stores the
player byte at object `+0x13`, clears flag one in the selected 12-byte view slot
and sets object flags `0x204`. World mode byte `+0x42E` selects animation/state/
variant values 1/16/2 when zero and 86/27/0 otherwise. That mode access uses a
real element of the existing character-array member. The view flags are a
16-bit member at slot `+4`; the native current-view index still requires valid
backing. Existing provider scalar-view contracts and object lifetimes remain
preconditions.

Normal and strict positives reproduce the complete slot. Changing the stored
player to player plus one rejects the full 144-byte control output against the
140-byte reference, including its four extra bytes. Actual initializer,
installed-callback and three provider definitions pass API checks; wrong
formals and three deliberately wrong layout facts reject. The initial layout
fixture's missing token-separating spaces are retained as a fixture failure,
separate from those intended layout rejections. The public include name and
shared header received a fresh source/control pair in the full build gate.
Its preprocessed body is byte-identical to the qualified private source.

## Installed player step

The installed callback at `0x0801DFE4` now reproduces all 276 bytes: 236
instruction bytes, 36 literal bytes and four zero alignment bytes. Together
with the initializer, it owns 416 extent bytes. The initializer installs the
proper `void (FrameObject *)` callback.

The step skips the needs updater for variant states 51 through 54, then always
chooses a need action and runs the actor state. Flag `0x20000000` selects the
double-direction table and limit eight; otherwise the limit is four. Pending
bits `0x16` request a direction/flip update. Bits `0x14` also bind the appearance
group, select an animation variant and choose a command table from the
appearance's first byte. The requested animation is reread after the variant
setter. Direction is reread before setting the flip bit. Finally the step
clears pending updates and the actual last character-array element of the
selection state at offset `0x42F`.

Connected source and interface changes recover the native output. A single
actor pointer carrier removes a separately live formal alias. Direct pending
field access also recovers the delayed address capture and shared zero. The
animation setter has a promoted
`int, int` external interface and a C89 identifier-list definition retaining
nominal signed-byte parameter objects. Default argument promotions preserve
that interface and the setter's native 132-byte body; the tested modern full-int
definition fails. This avoids the narrow caller prototype moving the signed group read
after the direction read. Finally, direct update-field tests retain a genuine
byte operand through widening. The compiler's register-move pass rejects its
subregister as a destructive destination and chooses the mask instead. A
promoted local capture produces the two-byte failure; disabling the pass fixes
that test but creates eighteen other differences. The successful explanation
uses the ordinary compiler profile and no register bindings.

Normal and strict positives match the complete callback. Changing its final
pending value from zero to one rejects the full 280-byte control at 31 offsets,
including the four extra bytes. The actual callback and backing layout pass
type checks; wrong callback formals, result and pending offset reject. The six
actual callee definitions are checked in their own header contexts. All
importers of the changed shared animation declaration receive fresh positive
and changed-source checks in the full gate.

The declaration and compiler output establish a consistent reconstruction,
not historical syntax. Valid actor/state storage, direction and signed
animation indices, variant/command resources and pointer lifetimes remain
preconditions. Callback writers, complete input populations and gameplay
behavior remain open.
