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

The installed step remains unowned. Its current readable candidate uses the
actual actor carrier for all provider calls, removing an independently live
formal-pointer alias and recovering the native saved-register roles. It still
produces 280 bytes against 276 and has 55 differing bytes. Signed animation-load
order and remaining allocation details are unresolved. An initializer match
therefore does not establish completion of the actor update path, callback
populations or gameplay behavior.
