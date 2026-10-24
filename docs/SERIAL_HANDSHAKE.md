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
the identifier and random-byte state, updates flags, and calls the
rebuilt start provider. Other paths send `0xB0CA` or `0xFEED`. The existing common restart
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

The 100-byte start provider now matches from C as described below. The
1,616-byte next-stage IRQ, downstream 200-byte record helper and separate
124-byte status reader remain unowned. Their call/address views do not qualify
those implementations. The start payload's upper representation remains
unspecified; no runtime fixture, peripheral timing or gameplay claim follows.

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

The transfer-completion poll at `0x0803D850` now owns all 408 bytes from
[C](../src/link/link_transfer_finished.c): 328 instruction bytes and 80 literal
bytes. Its call-free address, timestamp and mask phases reproduce the native
read order; an ordinary late flags alias lets the compiler allocate and preserve
R7. The accepted source uses the existing canonical endpoint and timestamp word
owners. The 200-byte caller and 16-byte slot reader use that same endpoint view,
and the unused partial endpoint declaration is removed. Normal/strict matches,
genuine changed-source controls, actual-definition interfaces, full-ROM and
progress gates pass.

The separate 124-byte status reader remains held. Slot volatility does not
explain its native unsigned snapshot and retained all-ones OR: the pinned
compiler folds that OR even when it retains a volatile read. Static startup,
interrupt-enable and writer evidence supports asynchronous identifier/slot
accesses under compatible guards; neither this evidence nor the poll's match
closes runtime, participant, writer or complete protocol domains.


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

When these surrounding bodies were adopted, the 1,224-byte controller at
`0x0801BE78` remained original. Its later matching reconstruction is described
below. The existing recording fade provider retains its prefix-store/suffix
qualifications. Resource prefixes, object/list backing, allocation success,
incoming indices, writable fields, scheduling and gameplay remain separate
open domains; source ownership does not close the whole serial path.

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
canonical short-circuit recipe matches. The distinct 408-byte poll now matches
as described above; the separate 124-byte status-reader hold remains unchanged.

The canonical API repair first preserved the controller's 1,224-byte /
eleven-difference candidate: all 39 native calls retained their 21 targets.
The later matching recipe below resolves the entry and indicator-loop
producers. Retained failed constraints explain why adding an entry-zero local
changed compiler-wide allocation. No dead initialization, dummy instruction
or assembly replacement is admitted.

## Linked-status controller

`scene_link_status_step` at `0x0801BE78` reconstructs the observed phase-9 step
callback in 1,224 complete C extent bytes. The disjoint static partition is
980 instruction bytes, 228 referenced data bytes (including the seven-entry
switch table), and 16 zero bytes at eight pool-alignment gaps. The ELF function
and section both own the complete extent; the next owned entry is `0x0801C340`.
The changed-source control changes the actual start-result exclusion from seven
to six and is rejected with 56 differing bytes at the same size.

Two actual producers explain the final match. The initialized flag value two
uses a genuine local `R3` constraint entirely inside a loop with no calls;
the ordinary cursor remains available for commoning its pointer read. The first
input-byte write uses a real character pointer to the complete `InputConfig`
object. Naming that consumed base preserves the original object-root address
and offset calculation while avoiding the compiler's temporary field-clearing
zero, which first CSE otherwise reuses for a later store. A direct character
expression instead folded the member address into a different literal pool and
failed; the retained failures distinguish these causes.

The kind-11 path initializes the GNU empty member of the existing payload union.
Its by-value ABI copies eight bytes of unspecified representation; this does
not initialize an eight-byte array or promise zero padding. Current canonical
header checks include the actual controller, recorder and all 20 owned direct
providers; the 124-byte status reader at `0x0803E298` remains an original
word-returning boundary. The peer predicate has its own word API and an explicit
low-byte conversion at this consumer, distinct from the 408-byte serial poll.

This ordinary-C recipe requires the complete input object through its 50 member
bytes, valid initialized indicator objects/flags, count values in zero through
four at the indicator loops, valid four-slot input indices, and signed flicker
increments within the C integer range. Native additions alone do not prove those
runtime conditions or portable overflow behavior. Opaque provider preconditions,
all incoming/writer populations and whole-protocol/gameplay closure remain open.

The initializer (352), controller (1,224), notice helper (164), indicator helper
(120) and shutdown (32) now own the complete local interval
`0x0801BD18..0x0801C47C`: five C bodies and 1,892 extent bytes. The observed scene
table row and its accepted phase consumers support the begin/step/end linkage;
they do not establish every runtime scene index. The 124-byte status reader
and 1,616-byte next-stage IRQ remain separate reconstruction blockers. The
accepted 408-byte poll does not close their domains. An earlier actual-owner
IRQ recipe lowered two-byte representation
copies inline but materialized two stack stores and four frame bytes absent
from the native body; that rejected attempt earns no C credit.

## Canonical record owner

`EventRecord` now contains a named union of its existing fields and six
halfwords. It remains twelve bytes, aligned to four, with kind, sequence,
reserved and payload at offsets 0, 1, 2 and 4. The eight-byte by-value payload
ABI is unchanged. The recorder uses the fields view; the receive consumer reads
its case-three halfword directly through the union. That consumer preserves the
actual input address captured before `event_get_link_slot`, matching the native
R7 lifetime across the call. Removing that address snapshot produced a different
632-byte body and was rejected.

The payload union also contains a genuine `EventPayload` member. Three recorder
copies and the consumer's case-ten read use that member directly, replacing
casts between incompatible object types. These remain the same eight-byte
copies at the original addresses, with no additional storage or accesses.

Normal and strict builds reproduce the recorder (244 bytes), receive consumer
(632) and unchanged endpoint initializer (356). Their three real source controls
reject by one byte in each profile. A unit containing ten actual definitions
checks the interfaces, including the still-unconverted provider and IRQ for
syntax only; six wrong contracts reject. The pinned compiler verifies 48 target
layout facts and the twelve-byte representation mask. This requalifies 1,232
already-owned bytes and adds no C functions or bytes. The full matching and
progress gates also rebuild all 51 transitive header importers.

This owner makes direct union halfword transfers possible without addressable
local copies, removing the two unwanted stack stores and their frame allocation.
The IRQ remains unowned. The current shared-counter candidate emits 1,624 bytes
with 809 differing bytes against the complete 1,616-byte reference. Its actual
peer variable covers both reset-to-zero loops and naturally occupies native R7.
Genuine checksum, word-result, setup and bank-cursor lifetimes preserve their
measured native producers without extra accesses.

A separate experiment gives three native terminal failure edges one common
fresh slot read, using a legal operation scope and parent restart label. It
emits 1,608 bytes with 1,040 differences. The shared producer exists, but its
ordinary global root and address extraction still differ from the native IP
owner; the other restart consumers remain separate. Neither experiment passes
the full comparison or earns source credit. Further work requires the actual
owner reaching definitions and remaining topology, not another volatile
qualifier. The 200-byte provider also remains unmatched; its separate
setup-address producers already appear in initial compiler output.

The six-global-slot composition remains 1,632 bytes / 1,498 differences. Its
duplicate setup-address carrier receives five constant-equivalence priority
penalties in LOCAL, increasing its recorded live length from 262 to 8,384.
This compiler metric affects allocation priority; it is not a runtime lifetime.
One later experiment removes only the forced IP home from the canonical setup
owner. The owner then naturally receives IP, but GCSE still creates a separate
carrier that receives R8. Their recorded live lengths grow from 329 to 10,528
and from 248 to 1,984 respectively. COMBINE also removes the existing late R3
handoff. The complete result is 1,604 bytes / 1,456 differences against the fixed
1,616 bytes, so this owner-relaxation line is closed without source credit.

A proposed composition of six native low-register address handoffs was stopped
before compilation. Three use R7; the pinned Thumb backend rejects byte and
halfword addresses mentioning its frame-pointer register before reload, even
when the function has no local data frame. The earlier R3-only experiment does
not establish that those R7 phases can survive. No R7 workaround or subset
binding trial follows from the proposal. A new owner, consumer or applicable
original-build fact is still required.

The pinned compiler's union-punning exception requires direct union access.
Taking an escaped halfword pointer, including through an integer address, does
not inherit that exception after fields-view writes. Known pointer banks and
record extents do not establish initialized bytes, all incoming indices,
asynchronous writers, callback populations or complete protocol behavior. The
IRQ, 200-byte record helper and status-reader boundaries remain original code,
with zero additional source credit from that owner change.

## Connection-start provider

The [provider at `0x0803A550`](../src/link/link_start_connection.c) owns 100 C
extent bytes: 82 instruction bytes, 16 literal bytes and two final zero
alignment bytes. Its function symbol ends after 98 bytes; the next independent
entry begins at `0x0803A5B4`. One existing 98-byte worklist row is removed, and
the two previously unresolved tail bytes are classified as alignment. No new
entry or instruction observation is added.

It sets game flag `0x20`, caches the actual active-byte provider's word result
at `0x03007358`, and caches the signed-slot provider's low byte at
`0x03007340`. A zero cached slot obtains the existing bounded-random result
with limit 65535, writes that value to the payload word and records kind two.
Other slots write a zero word and record kind one. The actual two handshake
call sites now use this shared declaration; their addresses and compiled bytes
are unchanged. Names and complete protocol roles remain provisional.

The canonical eight-byte, four-aligned payload union retains its empty member
and byte view and adds a real unsigned-word member at offset zero. Writing it
initializes the four bytes consumed by kind two. The upper four representation
bytes remain unspecified, and kind one reads no payload; this is not a claim
that the whole argument is initialized. No type-punned byte array, fabricated
load, tail zeroing or instruction body is used.

Normal and strict positives match the complete 100 bytes, and changing kind
two to three rejects by one byte. The recorder, seven existing by-value
callers, aggregate receiver, three actual providers and handshake caller pass
current-header positive/control qualification in separate contexts. Actual
definition checks preserve the random helper's unsigned-short API, the active
provider's unsigned-word result and the slot provider's signed-word result.
Payload size/alignment/word offset and record layout are checked, with wrong
contracts rejected. Full-ROM and changed-source gates remain separate from
these compiler/interface results. No endpoint population, complete protocol,
writer-domain or runtime evidence is added.
