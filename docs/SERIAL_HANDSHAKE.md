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


## Active-byte getter continuation

The connected getter at `0x0803E42C` now owns 12 C bytes: six instruction bytes,
four literal bytes and two native zero-alignment bytes. It returns the canonical
unsigned active byte at endpoint offset four as a full word, compatible with
the existing controller import. The inferred field role does not establish a
complete peer-count or protocol domain. Its first recipe matches, and changing
the source to read the slot byte rejects by one byte. Actual-definition API and
layout checks pass; wrong offset and byte-return contracts reject. All 256
initialized byte values agree in a finite source witness, which supplies no
peripheral or runtime execution evidence.

The larger controller, next-stage IRQ, connection starter and status reader
remain explicit original-code boundaries. In particular, matching this getter
does not initialize another caller's unwritten event payload or establish its
complete storage ownership. Fresh full matching/control and progress gates
cover the getter together with land placement; no assembly instruction body or
new compiler profile is used.

## Byte snapshot and shutdown helpers

The current-byte getter at `0x0803A510` (12 bytes), saved-byte getter at
`0x0803A51C` (12) and snapshot at `0x0803A528` (20) now have matching C.
Together with the existing reset they own the complete 64-byte local interval.
The snapshot copies the cached random byte to the saved byte. The generator
updates that cache on its non-refill path; this is not necessarily the low byte
of every most recently returned random word. Record preparation calls the current
getter and snapshot; the unconverted next-stage IRQ calls the saved getter.
The retained source and positive/control proofs were revalidated before adoption.
The three real mutations reject by four, four and eight bytes, respectively.

The independent cleanup body at `0x0803E314` owns 84 C bytes, comprising 56
instruction and 28 literal bytes. Its first recipe reproduces the existing
cleanup suffix of the accepted wait routine: conditional clearing of
interrupt-enable bit `0x40`, clearing bit `0x80`, the serial-data store and
active/slot reset.
Changing the slot reset from 255 to 254 rejects by one byte. Canonical layout,
MMIO access and actual-definition API checks pass. No incoming transfer is
identified; `void(void)` describes the recovered side effects and does not prove
the historical prototype or callback population.

The main identifier poll and status reader remain held. Static startup,
interrupt-enable and writer evidence supports asynchronous identifier/slot
accesses under compatible guards. Making only the actual identifier poll read
volatile reproduces the prior 408-byte / 101-difference candidate exactly;
that read already stays inside the loop. Slot volatility also does not explain
the native unsigned snapshot and retained all-ones OR: the pinned compiler folds
that OR even when it retains a volatile read. No qualifier is added merely to
force those instructions, and no runtime or complete protocol claim is made.


## Surrounding serial-scene source

Four retained exact recipes now have fresh source controls and actual API checks:

| Function | ROM offset | C extent bytes |
| --- | --- | ---: |
| `scene_link_status_initialize` | `0x1BD18` | 352 |
| `scene_link_status_draw_notice` | `0x1C340` | 164 |
| `scene_link_status_create_indicator` | `0x1C3E4` | 120 |
| `scene_link_status_shutdown` | `0x1C45C` | 32 |

Their 668 bytes comprise 564 instruction bytes, 96 literal bytes and eight native
zero-alignment bytes. The authored bodies are unchanged from the retained
attempts; each same-size meaningful control rejects by one byte. Twenty-six
provider declarations agree with actual owned definitions, and target layout
and wrong-contract checks pass. Full matching/control and progress gates pass.
The initializer constructs the four indicator objects and endpoint state;
the notice drawer preserves its table delay and staged-string word; shutdown
retains the real fade, object-list release and display resets.

The 1,224-byte controller at `0x0801BE78` stays original. Matching its surrounding
calls does not validate its unwritten kind-11 event argument. The existing
recording fade provider also retains its prefix-store/suffix qualifications;
these new callers add no event payload or invented initialization. Resource
prefixes, object/list backing, allocation success, incoming indices, writable
fields, scheduling and gameplay remain separate open domains. These entries
add source ownership without claiming completion of the serial path.

## Peer response predicate

The response predicate at `0x0803E48C` has matching C ownership for its complete
64-byte extent: 52 instruction bytes, eight literal bytes and four original
zero alignment bytes. It reads the canonical response count at `0x0300218C`
and byte mask at `0x03007338`, succeeding for exactly `(2,3)`, `(3,7)` or
`(4,15)`. The accepted handshake resets and populates these fields. This is the
response count; the starter's expected-count word at `0x03002190` is separate.
Changing the final mask from 15 to 14 keeps the extent and rejects one byte.

The held row-nine step calls the predicate at `0x0801C01C` and tests its low
byte. The reconstructed word-return API preserves the actual zero/one result;
the original narrow-versus-word return spelling remains unknown. Complete
incoming, writer, interrupt and protocol domains remain open.

Earlier private notes conflated this entry with the heavily tried 408-byte
`link_transfer_finished` at `0x0803D850`: an old private row-nine alias reused
that name for `0x0803E48C`. Exact-address and definition review separates them.
No authored prior attempt was found for this 64-byte predicate; its first
canonical short-circuit recipe matches. The 408-byte failures and the separate
124-byte status-reader hold remain unchanged.

The held 1,224-byte status controller now uses the actual provider names and
the same empty-member payload representation as the catalog. Its low-byte peer
result test has an explicit narrowing conversion at the caller. All 39 native
calls retain their 21 targets, and twenty actual provider definitions pass the
canonical API checks. Output remains 1,224 bytes with eleven differences; the
controller gains no ownership. The remaining entry-zero and indicator-loop
register differences survive these interface repairs. Genuine-value register
constraints made the local instructions agree but changed compiler-wide
allocation; retained intermediate output explains the extra pre-GCSE copy. No
dead initialization, dummy instruction or assembly replacement is admitted.
