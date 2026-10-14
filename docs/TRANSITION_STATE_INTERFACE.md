# Shared transition state interface

The accepted 36-byte provider at `0x08001C04` reads and writes the state byte
at object offset `0x4D`. When it changes that state, it sets mask 1 in the
pending byte at `0x4F`. Equal states leave both bytes unchanged. Its state
argument remains an unsigned byte and its return is effect-only.

Earlier declarations disagreed about the first pointer type: the actor
runtime used `FrameObject *`, while transition, menu-page and scene-redraw
headers used `TransitionObject *`. Both kinds of object-pointer expressions
occur in accepted callers. Those declarations were byte-compatible at the
target ABI but were not compatible C function types across translation units.
Separate caller byte matches and strict declaration checks did not resolve
that mismatch.

All four declarations and the definition now use one `void *` base argument.
The provider explicitly casts that base to the existing partial
`TransitionObject` access view. Existing caller expressions and their casts
remain unchanged; their object pointers convert to the common interface.
This models the shared object-state operation without changing unrelated
callback or factory interfaces. It is a supported reconstruction contract,
not a claim about the original declaration's spelling.

The provider also includes the canonical frame definition so the existing
by-value `FramePoint` declarations in the transition header are complete
during strict diagnostics. The original state comparison, stores and pending
mask compile to the complete same 36 bytes. The actual pending-mask control
still changes those bytes. Four independent function-pointer assignments
check the generic contract; restoring each earlier pointee declaration is
rejected as incompatible. Every affected current literal importer is checked
again with its actual changed-source control.

The partial transition view remains 116 bytes with alignment 4. This change
adds no field, capacity, pointer-validity or null guard and does not recover
the full allocation format. It gains zero C functions or bytes: the provider
was already accepted. Static type and compiler evidence remain separate from
hardware or gameplay execution.
