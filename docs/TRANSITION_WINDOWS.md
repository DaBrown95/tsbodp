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

## Remaining selector domains

Transition selector domains remain open. The direct-call census finds 32
first-wrapper and 30 second-wrapper calls; 52 have current C owners, while ten
original callers supply immediate zero. Command 21's window kinds and factory
14's optional-view kinds copy serialized bytes without a 14-entry guard. A
first-table index 14 would read the following table's first entry; this is a
conditional static finding, not observed input or execution. Serialized asset
populations, aliases, later writers and indirect incoming transfers still need
closure. Matching this controller does not resolve those inventory blockers.
