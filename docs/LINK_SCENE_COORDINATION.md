# Link coordination in the scene and fade paths

`transition_link_update` at `0x0803D6C0` adds 200 matching C bytes, including
its two literal-pool islands and alignment. The accepted fade-in, fade-out and
request-handoff callers now connect to its canonical name at the same address.
The function uses ordinary C without register bindings. Its original
`link_transfer_finished` dependency at `0x0803D850` remains unconverted.

The game word at `0x03004310` gates the path with bit `0x20`. A byte result of
one from the original provider clears link word `0x03007334` mask `0x4` and the
captured game word's bit `0x20`. The partial endpoint at `0x03002CB0` receives
identifier minus one, active zero and slot `0xFF`. The function updates volatile
halfwords at `0x04000128`, `0x04000200` and `0x0400012A`: mask `0x4` of the first
selects the conditional `0xFFBF` mask, followed by the unconditional `0xFF7F`
mask and a `0xFFFF` write. These are observed register accesses; the complete
protocol and runtime completion conditions remain uncertain.

If the provider has not returned one, the recording word at `0x03002180` mask
`0x1` selects event kind one or three through the accepted 244-byte event-record
function. The eight-byte payload initializes its first word only. Its second
word remains unspecified, as in the original caller; both selected event kinds
ignore that word in the accepted callee. No extra initialization is introduced.
The function returns integer one after the completed cleanup and zero otherwise.

Capturing the unmasked game word and a distinct real `~0x20` mask before the
volatile link-word update preserves the original scheduling and register
lifetimes. The earlier pre-masked snapshot yielded 200 bytes with 22 differences;
an unmasked snapshot without the separate mask yielded 196 bytes with 154
differences. The ordinary-C mask lifetime gives the complete 200-byte match.
An explicit register-bound alternative also matched and remains private; the
accepted source does not need it.

The current source has a rejected changed-source control that changes the link
mask from four to eight. Source, headers, original bytes and comparison reports
are retained under ignored `reports/audio-root/transition-link-lifetimes/` and
`transition-link-canonical/`; prior five failed attempts remain local. The
connected callers receive fresh positive and changed-source proofs when their
shared declarations are updated. This establishes compiler and byte equality,
not link gameplay, hardware timing or runtime coverage of the provider.

## Signed endpoint slot

The connected `event_get_link_slot` dependency at `0x0803E438` adds sixteen
matching C bytes. It reads the existing unsigned slot byte at endpoint `+5`
and returns its signed-byte interpretation as an integer; `0xFF` therefore becomes minus
one. The field remains unsigned in the shared partial endpoint view. The
existing event-record producer receives a fresh match and changed-source
proof against this provider. The original received-event caller compares the
returned word directly; a byte-return declaration adds redundant caller-side
widening. The integer-return model retains the same sixteen-byte callee while
matching that observed ABI use. All existing header consumers are reproved.
The getter control selects the adjacent active
byte and is rejected; no instructions or original literal bytes are embedded
in the source.

The received-event dispatcher at `0x0803A1A4/632` and completion poll at
`0x0803D850/408` remain unconverted. Private semantic dispatcher and polling
trials, including complete original extents, are retained under
`reports/audio-root/link-event-apply-evidence/`, `link-events-trial/` and
`link-transfer-finished-*`; their mismatches receive no source credit.
