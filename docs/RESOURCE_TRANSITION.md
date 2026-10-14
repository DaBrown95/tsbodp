# Resource transition constructor and delay callback

The connected constructor at `0x08018790` and delay callback at `0x080187D0`
match their complete 64- and 80-byte extents, respectively. Both are ordinary C
without register bindings. The constructor includes the two literal words at
`0x080187C8` and `0x080187CC` and its original zero alignment; the next entry
begins at `0x080187D0`. The delay callback returns at `0x0801881E`, immediately
before the next entry at `0x08018820`.

The constructor allocates a scene object, writes ID 24 and flags `0x2008`, stores
the low byte of its incoming kind at object offset `0x4C`, requests state zero,
and installs the callback selected by the complete incoming word. Its callback
table at `0x08052AC8` has an observed three-entry prefix: the original window
callback, this delay callback, and the matching alpha callback. This prefix does
not establish the table's capacity. Neither kind nor the allocation result is
checked. The two matching resource-command callers pass constants zero and one.

The incoming word is significant: a byte formal inserts four narrowing bytes
that are absent from the original constructor. The public declaration therefore
uses `unsigned int`. All 96 matching functions that import `resource_commands.h`
were freshly checked with actual changed-source controls under this declaration;
their source bodies remain unchanged. The old byte API also fails a compiler
function-pointer assignment check. This records the supported source contract,
not a claim about the historical declaration's spelling.

The delay callback interprets the existing object through the partial
`TransitionObject` view. In state zero it decrements the signed word countdown
and requests state one on reaching minus one. In state one it activates the
object's two resource groups, reloads flags after that call, and sets flag 2.
Every state clears the pending byte. The new callback takes the same single
`FrameObject *` argument as the generic step field and explicitly casts that
pointer to the partial field view.

The constructor likewise uses the provider's actual `TransitionObject *`
state-setter declaration and an explicit access-view cast. Its lightweight
allocator declaration is the same `FrameObject *(void)` contract as the matching
allocator definition. An older runtime header separately declares the state
setter with a `FrameObject *` pointee. That pre-existing interface difference
is recorded for a later coherent repair; this batch avoids importing it and
does not change the runtime header or provider body.

Pinned compiler layout checks confirm the existing `FrameObject` view is
312 bytes with alignment four, while the scene allocator reserves 320 bytes.
Its ID, flags, kind byte and step pointer occur at `0x08`, `0x0C`, `0x4C` and
`0x88`. The partial `TransitionObject` view is 116 bytes with alignment four;
state, pending, countdown and the two group bytes occur at `0x4D`, `0x4F`,
`0x58`, `0x70` and `0x71`. These views do not describe the entire allocation.
Actual wrong formal, field-width, callback-pointer and packing declarations
are rejected separately from byte comparison.

The two new functions and their changed-source controls pass strict declaration
diagnostics. Their complete objects contain only allocated text. The current
closure also covers the scene allocator, state setter and group activator.
Fifteen bounded initialized Thumb fixtures compare the fixed original, matching
body and real control. Five cases distinguish the controls. Abstract provider
hooks clobber caller-saved registers and include a changed flags value during
activation, exercising the actual post-call reload. They do not execute the
providers' whole gameplay effects. Three NULL allocation cases produce faults
in this finite memory model; no hardware-fault claim or source guard is added.

Arbitrary table indices, pointer validity, capacity and signed countdown
overflow remain unchecked. The view-mode setter at `0x0800E8B4`, its six-entry
dispatch table, and other failed candidates remain explicitly original. This
batch provides static and compiler evidence, not startup or gameplay evidence.
