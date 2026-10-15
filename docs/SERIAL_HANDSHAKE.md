# Serial handshake IRQ and timeout

The handler at `0x0803D9E8` connects to the IRQ-table address installed
by the accepted status-poll starter. Its timeout at `0x0803E4EC` is a coherent
companion: the handler installs that callback twice and writes the snapshot it
reads. Together they reproduce 652 bytes at their original addresses under normal and
strict compilation, including complete literal pools and alignment.

| Function | Instructions | Literal pools | Zero bytes | Matching extent |
| --- | ---: | ---: | ---: | ---: |
| Handshake IRQ | 440 | 164 | 4 | 608 |
| Timeout callback | 32 | 8 | 4 | 44 |
| Total | 472 | 172 | 8 | 652 |

The handler clears its response count and two status locations, then checks
fresh volatile control halfwords. It scans four receive registers in descending
order. `0xBEEF`, `0xC0DE`, `0xBABE` and `0xDEAD` select an early count-five result;
`0xFEED` and `0xB0CA` count responses and set peer bits. `0xB0CA` also sets flag
`0x20000`. A nonzero response count updates the slot byte from control bits 4–5.

When that flag is set, slot zero checks the other active channels for `0xB0CA`;
the nonzero-slot path checks channel zero. A ready path installs the timeout,
captures the VBlank count, installs the original next-stage IRQ address, resets
the identifier and random-byte state, updates flags, and calls the original
start provider. Other paths send `0xB0CA` or `0xFEED`. The existing common restart
operation updates the control and timer halfwords when mask `0x4` is absent.
These access sequences do not establish a complete serial protocol.

The source retains the canonical endpoint prefix: identifier at zero, active at
four, unsigned slot at five and word-return callback at eight. Signed slot
inspection converts that existing byte; it adds no qualifier or alternate owner.
The IRQ table remains unsigned words. The word views at `0x03007350` and
`0x03002188` describe observed reset and VBlank-snapshot accesses. No conflicting
exact-start alias was found in the current accepted bindings; complete storage
ownership and absence of other overlapping consumers remain unproved.

The timeout subtracts the snapshot from the canonical unsigned VBlank word at
IRQ-context offset `0x1C`, then interprets the result as target signed `int` and
tests greater than 300. Subtraction wraps modulo 2^32 before that conversion;
this avoids signed subtraction overflow. It returns zero or one, compatible with
the existing word-return callback. This is a GNU target representation contract,
not a portable elapsed-time or hardware-completion guarantee. Valid context and
endpoint backing are required; the intended receive walk assumes active 0–4.

The timeout's static envelope is 42 bytes. Its retained `.align 2,0` directive
accounts for two trailing zeros in the matching 44-byte compiler extent; it emits
no instructions. The other two zero bytes are internal. Fresh linked evidence confirms a 42-byte function symbol and two source-emitted
trailing alignment bytes, with one allocated 44-byte text section.

The 113 source and concise matching reports survive, while obsolete generated
payloads were retired. They establish historical candidate lineage, not a replay
or a current match. The adopted bodies change only their first include line from those retained attempts.
There are no register bindings, copied instructions or new volatile qualifiers.

The original 100-byte start provider, 1,616-byte next-stage IRQ and downstream
200-byte record helper remain explicit boundaries with zero new C credit. Their
call/address ABI views do not qualify their implementations or the proposed
six-halfword whole-record representation. The start provider's unwritten payload
suffix is not promoted to initialized C. The separate 124-byte status reader
also remains on hold. No runtime fixture, peripheral timing or gameplay claim
is made for these functions.

Normal and strict positive/control builds agree on all seven retained native
artifacts per role. Changing the early count result from five to six changes one
byte; changing the timeout threshold from 300 to 301 changes twenty. Four
positive type units check the complete handler, timeout and accepted 20-byte
random-byte reset definitions, plus four context/word layout facts. Five wrong
contracts reject for three return-type conflicts, an incorrect field offset and
an explicit signedness conflict. The first signed/unsigned pointer-conversion
control compiled without a diagnostic; that weak fixture and its actual result
remain preserved, and are excluded from the five rejection claims. Only the two
replacement type fixtures were rerun. Supporting interface type evidence from
the preceding milestone is reused through unchanged source/header and actual
proof identities; it adds no byte or execution credit.

The fresh full-ROM matching build and refreshed progress record 1,705 verified C
functions and 242,112 C extent bytes, a gain of two functions and 652 bytes.
Separate instruction glue remains 500 bytes, and 16,534,604 ROM bytes remain
explicitly unconverted. The fixed 16 MiB reference is byte-identical and the
changed-source whole-ROM control rejects.

The two compiled entry roots also promote the existing original start-provider
entry through a direct call. Their static contributions are 440/164, 32/8 and
82/16 instruction/referenced-data bytes, respectively: 554 and 188 bytes move
from weak estimates into the qualified static census. The original start
provider gains no C credit. Eight zero bytes acquire compiler extent ownership;
six were estimated gaps and two extend the timeout envelope. Inventory mapped
extents become 323,788 bytes. Qualified instruction evidence is 270,608 bytes,
including the unchanged four-byte dual-use word; referenced-data union evidence
is 34,732 bytes, including that same word counted once in the physical
partition. The fixed historical comparison stays 319,640 bytes and the complete
game-code denominator remains open.

The treemap's bounded-body count changes from 768 to 766 because these two
entries move from a control-flow boundary label to a compiler-audited boundary
label. Their instruction/literal geometry is retained; no decoded body is lost.
