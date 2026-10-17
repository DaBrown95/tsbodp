# Window controller and selector frontier

The 456-byte controller at 0x080184D4 remains original. Its raw state byte at
object +0x4D is guarded at most 6, then directly indexes the seven-word table at
0x08018510. The native mapping is:

| State | Body |
| --- | --- |
| 0 | Delay, then first handler for first kind |
| 1 | Set flag 2 |
| 2 | Common cleanup only |
| 3 | Countdown, then state 5 |
| 4 | Second handler for first kind; created-position view |
| 5 | Second handler for second kind; existing view |
| 6 | Delay, then first handler for second kind and state 3 |

All 17 unique retained legacy seeds mislabelled states 2–6, placing cleanup at 6.
One controlled correction changes only five case labels. Its 460-byte output
still differs in 145 bytes from the complete 456-byte native extent. Old explicit
R7 usage is unqualified, and existing-view argument construction still adds an
instruction and alignment. No source credit follows.

A subsequent experiment uses ordinary created coordinates and a separate,
captured existing-view base. Together with the corrected labels, it matches all
456 native bytes. Callback and effective-owner contracts, register preservation
and changed-source qualification still require review before adoption; this
private binary match receives no source credit.

The final compiler pass already merges the state 4/5 setter and delay suffix.
Five calls in the saved pre-final RTL become four physical calls. A proposed
explicit common-tail rewrite is therefore unnecessary. Reproduction retained
the old 460/149 binary exactly; its three intermediate-file hashes differed only
in a filename note. No normalized hash is substituted. Both historical frame
and IRQ headers differ from the current headers and were explicitly retained.

Transition index domains remain open. The static direct-call census finds 32
first-wrapper and 30 second-wrapper calls; 52 have current C owners, while ten
original callers supply immediate zero. Two dynamic source paths copy serialized
bytes without a 14-entry guard: command 21's window kinds and factory 14's optional
view kinds. In particular, command 21's state 4 enters the native created-position
path. A first-table index 14 would read the following table's first entry; this
is a conditional static finding, not an observed input or execution. Serialized
asset populations, aliases, later writers and indirect incoming transfers still
need closure.
