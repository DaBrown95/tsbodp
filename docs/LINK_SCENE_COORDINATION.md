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

## Applying received records

`link_apply_received_events` at `0x0803A1A4` adds 632 matching C bytes, including
the fourteen-entry switch table and literal pools through the next function at
`0x0803A41C`. It uses ordinary C without register bindings. The original
408-byte completion poll at `0x0803D850` calls it directly but remains
unconverted. Its timing and hardware protocol still lack runtime evidence.

The record array at `0x030072B0` has the same twelve-byte layout as the accepted
event-record producer: kind and sequence bytes, a reserved halfword and an
eight-byte payload. A word-fill view shares that exact base. The loop reloads
the peer-count byte at `0x03007358`; it has no observed upper-bound check. For
each peer, it retains the slot-getter call even when its return is discarded.
A changed sequence and nonzero kind update the saved sequence at `0x030072E0`
and clear that peer's halfword input at `0x03004268`. Kind three installs the
payload halfword and sets link bit `0x80` when the integer slot matches the
peer. Kind two passes the payload halfword to the accepted random-seed setter.
Kinds zero, one and six share the observed no-op switch destination. Every
record, including ignored and unknown kinds, is cleared with the accepted
CPU-copy wrapper's fixed-source three-word control `0x05000003`.

Kinds four and five select four distinct peer bits, `0x100000` through
`0x800000`, using explicit peer-zero-through-three tests. Kind five acts only
when the identifier at `0x03002D60` is minus one, installs the count and three
payload bytes at offsets `0x78` through `0x7B`, and stores request `+0x10` as
four. The identifier assignment occurs only inside those four peer tests;
the later metadata stores have no additional range guard. Kind seven writes
the payload word to the identifier view's four-word array at `+4`.

The pair view at `0x03002D74` has a sixteen-byte stride with eight-byte halves;
kinds eight and nine call the accepted byte-copy provider for the respective
half. Kind ten assigns an eight-byte payload through the vector view at
`0x03002DB4`. These views overlap the partial identifier view at `+0x14` and
`+0x54`. Their declarations describe observed access roles, not separate
storage, complete allocations or valid bounds for arbitrary peer counts.
Kind eleven sets link masks `0x80000` and `0x8000`, clears game bit `0x20`, and
submits scene request `(1, 2, current_scene)`. Kinds twelve and thirteen call
explicit unconverted providers at `0x080042A4` and `0x0800450C`.

The separate record-halfword input view and word-fill destination preserve
observed address lifetimes. The vector's integer destination address is
consumed by the actual structure assignment. The lexical switch order matches
the original block order, including eleven before ten; the complete switch
table supplies evidence for the no-op labels. Earlier typed-source, fill-view
and case-order attempts are retained with raw comparisons. The final ordinary
C source matches all 632 bytes and rejects a changed-source control that
clears bit `0x40` instead of `0x80`. Proofs remain under ignored
`reports/audio-root/link-event-receive-canonical/`; raw extent and failed
attempts remain under `link-event-apply-evidence/` and `link-events-*`.

The completion poll's best private 408-byte candidate still has 101 differing
bytes and receives no C coverage. Its original body and failed semantic
attempts remain under `reports/audio-root/link-transfer-finished-*`.
