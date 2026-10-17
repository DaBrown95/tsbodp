# Window controller and view mode

The [456-byte controller](../src/resource/transition_object_tick_windows.c) at 0x080184D4 has readable matching C with the actual
`FrameObject *` callback interface. Normal and strict builds match its complete
native extent, including the literal pools and alignment, and changed-source
controls reject. Its captured view in R8 is saved and restored by the native
callee-save sequence. The four existing users of the same configuration also
match in both profiles with their controls.

The fixed eight-byte configuration at 0x08053504 has a [shared reconstructed union owner](../include/transition_view_configuration.h): two unsigned words and a real `FramePoint`. The values are 24 and 35.
Passing its point member preserves the native aggregate load without reading a
foreign object through a cast. The union name and original declaration remain
inferred; no wider storage or runtime ownership claim follows.

The raw state byte at object +0x4D is guarded at most 6 and directly indexes the
seven-word table at 0x08018510:

| State | Body |
| --- | --- |
| 0 | Delay, then first handler for first kind |
| 1 | Set flag 2 |
| 2 | Common cleanup only |
| 3 | Countdown, then state 5 |
| 4 | Second handler for first kind; created-position view |
| 5 | Second handler for second kind; existing view |
| 6 | Delay, then first handler for second kind and state 3 |

Legacy candidates mislabelled states 2–6. Correcting that mapping and using
ordinary created coordinates with a captured existing-view base explains the
matching code. The final compiler pass shares the state 4/5 setter and delay
suffix: five earlier calls become four physical calls. An explicit tail rewrite
is unnecessary.

## View mode

[transition_set_view_mode](../src/transition/transition_set_view_mode.c) at `0x0800E8B4`
takes a 32-bit unsigned mode and an unsigned byte view index, and returns no value. It
stores the mode’s low 16 bits, clears the view-effect mode byte, then dispatches on the
original full unsigned word when it is at most 5. Only mode 1 clears the view’s object
pointer; for example, `0x10001` stores 1 without taking that case.

The C source keeps six per-mode forward return labels. These distinct destinations delay
the pinned compiler’s early case grouping long enough to retain the native six-entry
dispatch table. Its later jump pass directs the five no-op cases to the shared return
while retaining mode 1’s object clear. This explains the matching control flow without
establishing the original source labels or syntax.

The existing GNU 2.10.1 assembler produces a 106-byte input section; the unchanged
linker supplies two natural zero-alignment bytes, yielding the complete 108-byte extent.
Normal and strict source builds match all 108 bytes, and both actual changed-source
controls reject. No original instruction bodies, output patches or masks supply the
match. The historical compiler flags and source syntax are not uniquely established, and
valid view-index domains remain open.

## Finite resource storage

The 50 structurally backed scene roots contain 105 physical pack records. All
105 base/selected copy layouts decode within the fixed ROM and 8,192-byte arena
bounds. This finite population contains no command-21 records. Six distinct
factory-14 payloads produce ten copy occurrences, all with first/second kinds
12/12. These select the already matched
[lightening](../src/transition/transition_mosaic_lightening_refresh.c) and
[darkening](../src/transition/transition_mosaic_darkening_refresh.c) mosaic handlers.
Four nonempty word groups contain 19 eight-byte records. Stored groups may be
dormant; copying their records does not establish execution or factory invocation.

Evaluating all 256 unsigned-byte inputs per root gives 6,101 numerically backed
directory-index outcomes and 6,699 unbacked outcomes, which remain unfollowed.
Seventeen lookup read windows cross the following root. These calculations do
not validate selectors: later bytes can belong to directories, payloads or
neighboring storage. The physical census does not close unchecked scene indices,
saved inputs, later writes, aliases, writable callbacks or complete target sets.

A separately qualified 36-byte routine at `0x0802A8FC` writes selector 1, calls
`resource_submit_scene(1, 0, 9)`, then stores 4 in `scene_mode[0]`. Its
`void(void)` interface is inferred and incoming callers remain unidentified;
the full matching and progress gates pass. The saved-byte loader can overwrite the
earlier selector reset, so that path's input domain remains open.

## Windowed fade-in handler

The 132-byte handler at `0x0803975C` also has matching C. It sets the native
window coordinates and layer masks, enables the two window bits, selects the
requested blend targets, then steps brightness from 16 through zero. Each
iteration requests refresh, steps backgrounds and palette jobs, prepares OAM
and waits for two VBlanks. The source retains the actual signed loop and all
six literal words. Normal and strict full-extent matches and changed layer-mask
controls cover the complete output.

The first handler table's observed fourteen-word prefix stores its address in
slot 13. The finite 105-pack census contains only factory kinds 12/12, so it
does not establish execution of this handler. The downstream palette-block
worker remains unconverted. The shared display header now declares the existing
plural `display_step_palette_blocks(void)` API, matching its actual definition;
all 511 existing matching header importers pass the fresh full build gate.

## Remaining selector domains

Transition selector domains remain open. The direct-call census finds 32
first-wrapper and 30 second-wrapper calls; 52 have current C owners, while ten
original callers supply immediate zero. Command 21's window kinds and factory
14's optional-view kinds copy serialized bytes without a 14-entry guard. A
first-table index 14 would read the following table's first entry; this is a
conditional static finding, not observed input or execution. Other serialized asset
populations, aliases, later writers and indirect incoming transfers still need
closure. Matching this controller does not resolve those inventory blockers.
