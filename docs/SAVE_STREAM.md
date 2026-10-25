# Save-stream reconstruction

The reconstructed path connects the published menu-choice and actor-need
save/load callers to a shared byte/bit cursor, record views, slot transfers,
header initialization and audio/display-status handoff. Its historical snapshot
contained 59 matching C functions covering 4,588 bytes. Each full extent, pool
and alignment was linked at its original ROM address and compared with the fixed reference. Each also
has a compiled changed-source control. These are static and compiler results;
no runtime save/load or EEPROM compatibility claim is made.

The connected actor-tail reader and writer at `0x0800EB30` and `0x0800EB3C`
separately add two matching C functions and 24 bytes. Each transfers 28 bytes
through the existing byte provider and has normal/strict comparisons with
rejecting count controls. The adjacent reset hook was already owned. The
newly qualified grouped reader and writer add two further C extents and
868 bytes (468 plus 400); the actor-entry family now contains 25 extents and
3,224 bytes. Their full-project matching and progress gates pass. See the [actor-entry evidence](ACTOR_ENTRIES_RECONSTRUCTION.md) for
backing and interface limits. These additions remain separate from the
historical 59-function snapshot and do not establish complete save paths.

## Shared storage and format limits

Literal loads identify the shared state at `0x03005D90`. The observed header
occupies its first 16 bytes; buffer pointer is `+0x10`. Four 40-byte decoded
records fit `+0x14..+0xB3`, followed by four validity bytes at `+0xB4..+0xB7`.
The selected slot is a word at `+0xB8`; byte cursor and signed bit position are
`+0xBC` and `+0xC0`. Used-byte and percentage words at `+0xC4` and `+0xC8` come
from the still-unconverted buffer builder at `0x080379A0`. `SaveStreamBitCursor`
at `0x03005E4C` is an overlapping view of the same cursor fields, not another
allocation. Four slots are established by the accepted startup/scan loops;
individual slot routines have no index checks.

Byte reads skip to the next byte whenever the signed bit position is positive.
Byte writes first preserve only bits below that position, then advance and
reset it. One-bit and two-bit values are read or written low bits first; the
pair routines round odd bit positions up to the next even position. Four-bit
reads round partial positions up to the next nibble. Zero-count packed
operations skip their element loops; pair/nibble alignment still occurs before
the count check. Signed byte-copy lengths and packed full-word counts stay
unchecked, matching the original operations.

The record loader at `0x0801BB68` reads one marker byte into `0x03004334`, then
four bytes at record `+0`, six at `+4`, three at `+0xC`, and sixteen at `+0x10`.
It reads two packed pairs at `+0x20/+0x21`, then six nibbles at `+0x22..+0x27`.
The three-byte value is sign-extended by ORing its upper byte when bit 23 is set;
the code does not clear the upper byte on a positive value. Field content names
remain provisional. This is a decoded 40-byte view, not a claim that the full
save format has been identified.

The separate game-state loader at `0x0801B704` likewise reads three bytes into
the full value word at `0x03003954`, ORing `0xFF000000` only when bit 23 is set.
A positive value preserves byte `0x03003957`. Cold startup and the defaults
reset establish zero locally, but the serial-session step subsequently replaces
the entire word with received record word one on both its matched and unmatched
routes. The sender copies its full value word; the inspected receiver checks
identity word zero without a range check on word one. An earlier reset therefore
does not establish the high byte at the later load.

The peer-value domain and last writer between loading and settlement remain
open. The existing controlled serial/load fixture used a zero peer word and zero
serialized low 24 bits; its selector watch does not establish high-byte
preservation. These are static producer facts, without a natural stale-value
execution or universal nonnegative/capped settlement-input claim.

## Transfer and checksum boundary

Slots use 255 transfers of eight bytes, with block address `255 * slot + 2`, so
the working span is 2,040 bytes. The lower interfaces at `0x0804C9BC` and
`0x0804CCB0` narrow the block argument to 16 bits. The read interface now has
a matching C body, as does the game write/retry interface. Their returned status
is discarded by these game loops. The lower write interface performs its own
observed retries; the game loops add no retries or bounds.

The checksum at `0x08037F30` sums halfwords modulo 65,536. It halves the unsigned
byte length, then tests the remaining word as signed positive; a trailing odd
byte is not included. Slot validation stores and returns a word 0/1 for a zero
sum over 2,040 bytes. The record scan's decrementing repeat counter starts at
zero, so it reads and validates each of the four slots once.

Header initialization copies 16 bytes from an unconverted constant at
`0x0806A17C`, sums its eight halfwords, stores the negated sum at `+0xE`, and
writes two eight-byte blocks at address zero. Header validation reads those two
blocks, checks the additive sum and compares the first eight bytes with the
constant. The startup routine allocates a zeroed 2,040-byte buffer. On a failed
header check it writes the header, clears the buffer and writes only five
blocks (40 bytes) at each slot's starting block. It then passes header byte
`+0xA` to the text-resource bank selector and scans the slots. The inverse
setting producer stores a returned word narrowed to that byte, sets byte
`+0xB` to one and leaves word one in the return register. The setting's original
meaning beyond the connected text-resource selection is not established here.

Header validation does not constrain byte `+0xA` to the UI's bank range of zero
through five. Setting that byte to six and adjusting checksum halfword `+0xE`
can preserve both the template prefix and zero additive sum. This is a static
countermodel to the range assumption, without an EEPROM execution claim;
startup still forwards the byte unchecked to the selector. When each bank
observation is zero through five, the connected
[serial text reply](SCENE_CONTACT_MENU.md) has a 172-byte static output bound.

The commit routine invokes the unconverted buffer builder, suspends audio,
writes and reads a slot, resumes audio, validates and loads or clears its record,
then stores the selected slot. Its two game audio wrappers call the accepted
`audio_deactivate_hardware` and `audio_activate_hardware` functions. Transfer
begin saves `DISPSTAT` (`0x04000004`) into `0x03005D80`, writes `0x3FFF` to the
interrupt acknowledge register (`0x04000202`), clears `DISPSTAT`, and invokes
the matching transfer-configuration interface with 64. Transfer end restores
the saved status. This observed ordering does not prove concurrent safety or
successful physical-media writes.

## Source and verification evidence

The nibble reader uses two scoped C register bindings: the shared cursor pointer
in `r5` and the high-nibble scalar in `r1`. They are actual algorithm values and
are not live across function calls. The cursor is four bytes before the bit
position in the observed eight-byte view. Its inline low-nibble reader is a
semantic byte accessor. The connected nibble writer's register roles are
described below. There are no original instruction-body transcriptions, output
patches or comparison masks. The remaining functions use ordinary C.

Function boundaries include return paths, referenced literal pools and alignment
up to the next mapped entry. The checksum's instruction body is 34 bytes and its
accepted extent is 36 with alignment. Block read/write bodies are 46 bytes and
their extents are 48. Slot scan has a 122-byte CFG envelope and a 124-byte extent.
These remain bounded static claims, not a complete code inventory.

Useful failed approaches, original/actual bytes, assembly, source snapshots and
real negative controls remain in ignored local reports. The 108-byte buffer
builder is still unconverted; its candidates are excluded from coverage.
The higher game-state loader, retained condition module and unconverted
header-refresh branch remain explicit dependencies. The reconstructed
write-mode gate and grouped actor transfer are described below.

## Game-state producer and header representation

The header prefix is now a named 16-byte union with byte and eight-halfword
views, including the checksum at byte fourteen. The initializer and validator
sum its bounded halfword array directly. This preserves all following state
offsets and replaces traversal through a cast of the larger state object. The
representation does not expand the identified format or establish library
transfer success. All 66 previously accepted functions importing this header
were rebuilt with their actual changed-source controls after the refinement.

The 280-byte producer at `0x0801B928` writes the marker, then accesses a separate
partial world-state view at `0x03003950`. It writes four bytes at `+0`, six clock
bytes at `+8`, and three low bytes of the word at `+4`, then serializes records
starting at `+0x10` and `+0xDC`. The clock occupies the already-established
eight-byte `DisplayTimeRecord` at `0x03003958`; this producer omits its reserved
halfword. The other word meanings remain uncertain. The world pointer is
initialized after the marker write, matching the observed call/literal order
without register constraints.

The producer also writes five bytes starting at `0x030040E7` as lengths one,
two and two. Its unchecked selector at that address plus 42 chooses the first
bit of a 56-byte row at `0x03004130`. This overlaps the published input and
clock-selection views; it does not establish a separate allocation or table
bound. One-bit fields at world `+0x747/+0x749`, byte fields at
`+0x741/+0x742/+0x746/+0x726/+0x72E`, and a halfword at `+0x744` follow. After
one retained unconverted module serializer and four accepted serializers, it
writes byte `+0x740`. Their content roles remain provisional.

The paired, still-unconverted loader at `0x0801B704` restores only
`0x030040E7..0x030040EB` through those three byte-copy calls. Its fresh byte
read at `0x0801B78C` instead selects the row through `0x03004111`. That address
is shared by `InputConfig.local_player`, `TransitionViewContext.current_view`
and the clock-selection row. The five restored bytes therefore do not bound
the incoming row selector.

There is a concrete additional writer: [world-default reset](../src/save/reset_world_defaults.c)
clears 52 bytes at `0x030040E0`, including selector byte 49. Its following store
sets byte 48 to one and leaves byte 49 zero. On the expiring phase-two path
with `matched08 == 0`, the [serial-session step](../src/scene/scene_contact_step_serial_session.c)
calls that reset and world initialization, commits slot three, then queues
request kind one / mode five. Phase-table row ten names the serial-session
callbacks. Once the handoff accepts the request, row one's begin callback reaches
[scene preparation](../src/scene/scene_prepare_load.c), whose mode-five branch
calls the buffer loader and then `0x0801B704`. This identifies a static producer
and a connected possible load route, without establishing a natural runtime
arrival or a preserved zero.

After the serial step returns, the [handoff driver](../src/scene/step_request_handoff.c)
refreshes live objects before processing the queued request. The serial end
callback also runs a transition across VBlanks before the next begin callback.
Object callbacks, interrupts and later aliases remain possible intervening
writers. Establish the last writer and its preservation through `0x0801B78C`
for each claimed incoming route; the reset does not close that population or
explain the loader's remaining compiler mismatch.

The [controlled native fixture](RUNTIME_OBSERVATIONS.md#controlled-serial-reset-to-loader-fixture)
now observes that reset as the sole physical selector writer through the
retired loader read, which returns zero, for one authored unmatched-peer input
and its actual callback/IRQ state. Native payload generation, complete save
write/read comparison, replay and watch controls pass. This finite result does
not establish preservation for other incoming routes or resolve the source match.

The connected 128-byte record producer at `0x08031F7C` writes its first sixteen
bytes, two pairs and six nibbles, then invokes child serializers at offsets
`+0x18/+0x20/+0x88/+0xA0`. The final child is the already accepted
`frame_save_actor_needs` at `0x0802B958`, which writes the shifted high halves
of eight values from its 32-byte input span. The partial source view covers
that observed span through `+0xBF`; it does not establish the complete record
size. The `+0x20` child at `0x08035F2C` traverses the already-established
104-byte relation-values view in three passes: 24 signed value bytes, 24 flag
nibbles and 24 first bytes from each record's retained delay area as nibbles.
The source uses the existing four-byte relation-record layout without changing
its neutral field names. The `+0x88` child at `0x0803D198` takes six signed
words, shifts each arithmetically by sixteen and writes its two low bytes.
This establishes a 24-byte input span; the original value roles remain
provisional. These two child extents are 76 and 36 bytes including alignment,
with ordinary C and compiled changed-source controls. The typed child views
preserve offsets `+0x20/+0x88/+0xA0` and the observed span through `+0xBF`.
All 71 existing save-header consumers were rechecked after that refinement.
The 28-byte child at
`0x08032020` writes five nibble values at `+2` before the value at `+0`. The
32-byte module at `0x080293A0` writes eight nibbles at `0x03004085` followed by
one byte. The 52-byte module at `0x08010AE0` writes four words at
`0x03004064`; nearby bit-mask readers support the flag-word name. These four
functions are direct producer dependencies, with their own full-extent matches
and real negative controls. The condition modules at `0x08029D18/0x08029C8C`
now match all 140 bytes each.

The first decoded record's two pair bytes and six nibble bytes also form an
eight-byte selector view at `0x03005DC4`, with subsequent records forty bytes
apart. This is shared storage used by actor-group selection, not a new buffer.
The accepted transfer/record view and the separate selector view retain the
same addresses and strides.

## Remaining world-field transfer branches

The direct producer at `0x080383A4` snapshots halfwords at world
`+0x426/+0x42A` into local halfwords, writes the bit at `+0x42E`, the nibble at
`+0x42D` and the byte at `+0x42C`, then writes both captured halfwords. Its
104-byte extent includes alignment and four literal words. The second branch
at `0x080333C4` writes bytes at `0x03003D8E/0x03003D8D/0x03003D8C`, captures
halfwords at `0x03003D82/0x03003D86`, writes those local halfwords and finally
captures and writes the byte at `0x03003D8B`. Its extent is 96 bytes.

Both use bounded prefix structures and shared semantic inline accessors. The
auxiliary byte cursor starts inside the full declared partial object, so its
backward offsets stay within that representation. These source views overlap
the established world RAM: `g_save_world_fields` starts at `0x03003950` and
`g_save_auxiliary_fields` at `0x03003D80`. The field names describe observed
storage and transfer order; their gameplay roles and full owning allocation
are unknown. Both ordinary C sources match their full original extents and
their real changed-source controls reject. The main producer's two call aliases
now use those canonical interfaces. All 71 pre-existing save-header consumers
were rebuilt with their controls against the final shared header closure.

## Inverse record and field path

The 128-byte inverse record consumer at `0x08031EFC` reads the same sixteen
prefix bytes, two pairs and six separate nibbles as the producer, then calls
the inverse children at `+0x18/+0x20/+0x88/+0xA0`. The final child is the
already accepted `frame_load_actor_needs` at `0x0802B934`; its eight word
stores cover the same 32-byte span. The higher game-state loader at
`0x0801B704` remains unconverted, so this batch closes its record/field
dependencies rather than claiming the complete load path.

The relation consumer at `0x08035D30` reads 24 value bytes, clears prefix
byte four, reads 24 flag nibbles and counts those with bit two set, then reads
24 first delay bytes as nibbles before calling the accepted relation metrics
updater. Prefix byte four of this values view coincides with the established
`high_count` byte at the relation state base plus `0x24`. Its neutral prefix
field name is retained. The earlier 102-byte mapped instruction envelope
ended at its return; two alignment bytes before the next prologue at
`0x08035D98` make the verified extent 104 bytes.

The 36-byte six-word inverse at `0x0803D174` reads two low bytes into an
unsigned word temporary and shifts the word left sixteen before each store.
The source preserves that partial write and unsigned shift: it adds no
clearing of the temporary. The shifted-out upper bytes are not serialized
content. This is a match to the observed compiler output, not a portable
runtime claim about indeterminate temporary bytes. The 28-byte nibble child
at `0x08032004` reads five values at `+2` before the value at `+0`. The
32-byte state reader at `0x08029380` reads eight nibbles and one trailing byte;
the 52-byte flag reader at `0x08010AAC` reads four words separately.

The field consumers at `0x08038350` and `0x08033610` have verified extents of
84 and 100 bytes. They reverse the corresponding producer transfer order,
then replace complete aligned words at world `+0x424/+0x428` and auxiliary
`+0/+4/+8`. Halfword inputs are shifted left sixteen and the final auxiliary
byte left twenty-four, clearing the lower bits as the original stores do.
The shared field views now express each four-byte location as a word/prefix
union. Their high halfwords and byte retain the exact producer offsets;
following offsets do not change. These overlapping partial views still do
not establish separate allocations or a complete world-state size.

All eight inverse sources use ordinary C, match their full original extents
including pools and alignment, and have real compiled changed-source controls.
All 75 previously accepted save-header consumers were also rebuilt with their
controls against the final union/header closure. The buffer builder and higher
game-state loader remain explicit unconverted interfaces. Static transfer order and compiler equality do not establish save compatibility or gameplay behaviour.

## Condition table and serialized backing

The [writer](../src/save/world_write_condition_module.c) and
[reader](../src/save/read_condition_state.c) now own 280 bytes: 272 instruction
bytes and eight literal bytes. Fixed owner address snapshots before the first
transfer preserve native register allocation. Normal/strict matches and real
loop limit controls pass. Backing and save populations remain open; unused
original formals remain provisional.

The fixed ROM condition table contains five 32-byte rows and thirty pointed
definitions; the separately identified scene/mode table follows immediately.
Row counts select 29 groups with 95 entries, and no definition has more than
five entries. These finite records support the usual row 0–4, selected-column
and selected-entry bounds; they do not validate incoming indices or other
writers. Both condition modules transfer all 360 flag positions
in the 724-byte reset span, including 112 positions outside that
definition-selected subset. Those additional transfers remain required.
With valid stream state, live backing and no interfering writes, the completed
reader normalizes all 360 flag bytes to zero or one. Its separate selected-row
transfer replaces only the first byte of a word, retaining the upper three
bytes and adding no row-range check. Setter count tests occur after relevant
state writes and therefore provide no general incoming-index guard. These
storage findings do not establish valid save populations or runtime save
compatibility.

## Condition display-bit transfer and completion

The paired 20-byte routines at `0x0802C90C/0x0802C920` write and read fifteen
bytes of the existing `g_condition_display_bits` view at `0x03001E00`. The
140-byte condition modules at `0x08029D18/0x08029C8C` call
these direct children after transferring their row and cell bits. The already
accepted clear/set routines use this same byte array; the accepted menu fallback
indicator also reads it. The transfer length establishes a 120-bit storage span,
not a checked valid-kind range.

The 84-byte completion handler at `0x0802C96C` traverses eight-byte ROM rows at
`0x0805FAB4`, matching the full-word kind before calling the existing group
completer with row and column bytes. A full-word kind of 119 terminates the
scan. Its index is a wrapping byte, and the source preserves that narrowing and
sentinel termination. After processing the table it clears the requested bit
with an unchecked byte index and low-three-bit shift. The two unused row bytes,
the complete table extent and the gameplay meaning of completion remain
provisional; the code supplies no kind-range check or independent table bound.

All three ordinary C sources match their original addresses, complete extents,
literal pools and alignment. Their real changed-source controls reject. The
five accepted byte-transfer and condition providers were also rebuilt with
controls against current headers. The larger row/cell modules and complete game
loader remain excluded from matching coverage; the grouped record pair now has
its own full qualification below.

## Buffer-load wrapper and saved text-resource selection

The 64-byte wrapper at `0x08037C8C` resets the byte cursor to the current
buffer and clears the signed bit position, calls the still-unconverted game
loader at `0x0801B704`, then stores the cursor difference as used bytes and
computes its unsigned percentage of 2,040 bytes. The source preserves the
word multiplication before division and adds no capacity check. This accepts
the wrapper, not its larger callee or the complete load transaction.

The saved header option now has a bounded source-level role: the 60-byte
selector at `0x08044FC0` stores its low byte at `0x030021F8`, uses the original
full-word argument to index the pointer table at `0x08D7419C`, and passes the
selected pointer to the accepted `display_text_set_resource`. It then reads
the stored byte and writes 32 for value two, or 44 otherwise, at `0x030021F9`.
That derived byte's further meaning and the table's valid index range remain
unknown. The declaration is unsized and the source adds no index check.
The old byte formal was an unsupported inference: narrowing occurs at the
store, while the table lookup uses the complete input word.

The 12-byte getter at `0x08044FFC` zero-extends the stored bank byte into a
word return. The 32-byte initializer at `0x08044FA0` selects bank zero and
allocates 1,024 bytes for the existing text-buffer pointer at `0x030021F4`.
The published lookup consumer uses that pointer with the same 1,024-byte
limit. Allocation failure is not checked by the initializer. These three
functions connect the existing save startup/header updater and text-resource
decoder; they do not establish language names or a complete localization
format. The old neutral save-option call aliases now use the canonical text
bank declarations without changing target addresses.

All four ordinary C sources match complete original extents, pools and
alignment with real changed-source controls. All accepted consumers of the
changed save header, both old option callers and the text/heap providers were
reproved against the current shared declarations. Larger game-state and
condition-module candidates remain private and excluded.

## Nibble producer closure

The direct writer at `0x08037A0C` now matches its complete 148-byte extent,
including both referenced literal words and their embedded pool alignment.
Its pointer and full-word count interface is unchanged. Capturing the source
pointer and then the count before alignment preserves their observed lifetimes;
no aggregate argument or new external interface is needed.

Alignment happens before the zero-count check. For a partial nibble, the code
preserves only bits below the signed bit position, then rounds positions up to
four or advances the cursor and resets the position. The source adds no bit
position checks. At position zero, it overwrites the destination byte with the
input's low nibble, clearing the old high nibble. At the other loop position,
it preserves the destination's low nibble, replaces the high nibble, advances
the byte cursor and resets the position. Input bytes and the full-word count
remain unchecked. These operations do not establish a valid cursor range or
make the shift expressions portable outside the original bit-position domain.

Seven C register bindings retain meaningful algorithm values: the source
snapshot, input cursor, bit-position pointer, nibble mask, low-branch input
value, retained destination byte and high-nibble value. The source snapshot's
last use precedes reuse of its register for the bit-position pointer. Branch
value bindings have disjoint scopes, and the routine makes no function calls.
The compiled entry and return preserve all four used callee-saved registers.
There are no embedded original instructions, output modifications or artificial
volatile accesses. A real mask change from fifteen to fourteen changes the
compiled bytes. All current accepted save-header consumers are recompiled with
their own source controls after removing the old unconverted-writer comment.
The main game-state loader, condition modules and buffer builder remain
explicit unconverted paths. The grouped actor pair and write-mode gate are
qualified separately below.

## Parameter selection, DMA handoff and serial read

Three connected ordinary C functions close the selector at `0x0804C8F4`
(72 bytes), DMA handoff at `0x0804C93C` (128 bytes) and read provider at
`0x0804C9BC` (176 bytes). The selector stores a parameter pointer at
`0x030074E4`. Inputs four and 64 choose twelve-byte constant rows at
`0x08D7074C` and `0x08D70758`. Other values choose the first row and return
one; recognized values return zero. The rows supply byte-size words, block
limits of 64 and 1,024, wait-control halfwords and address lengths of six
and fourteen bits. These are observed fields and values, not a copied data
asset or a complete media-format specification. The three unused tail bytes
and wider table storage remain provisional. Named nonstorage typed macros
express the observed RAM pointer address and both constant-row addresses.
They create no separate C storage or duplicate constant table.

DMA handoff saves the interrupt master-enable halfword at `0x04000208`,
clears it, masks the wait-control register at `0x04000204` with `0xF8FF`
and ORs the selected row's wait value. It then writes the source and
destination pointer registers at `0x040000D4` and `0x040000D8`, and the
control word at `0x040000DC`, with its halfword count and bit 31 set. It polls
bit 15 of the high halfword at `0x040000DE` before restoring the saved master
enable. Both pointer-register lvalues and scalar hardware views are volatile.
The source's single polling loop reproduces the original initial probe and
inner probe; it adds no timeout or completion result. Wait-control changes
remain in place after the routine returns.

The read provider explicitly narrows its full-word block input to a halfword
before comparing it with the selected block limit. A rejected block returns
`0x80FF` without a transfer. The accepted game block loop retains its observed
call-side halfword narrowing through an explicit cast. For an accepted block,
the provider builds an address command backward in a 68-halfword stack buffer
and transfers the selected address length plus three halfwords to
`0x0D000000`. The command count includes one trailing stack halfword that
this routine does not initialize; the source preserves that observed
non-clearing behaviour. It then reads 68 halfwords from that same fixed port. After
skipping four returned halfwords, it packs their low bits into four halfwords
and stores them backward through the destination. Each shift assignment
narrows to sixteen bits before the following OR. The destination must permit
those observed halfword accesses; the code adds no alignment or capacity
check. The short offset-before-buffer address calculation preserves the
original pointer lifetime without a fixed register constraint.

All three complete extents, literal pools and alignment match with explicit
`agbcc` Thumb `-O1 -mthumb-interwork` flags. Retained `-O2` attempts show the
otherwise different loop and register allocation; no compiler-output change
or embedded instruction body is used. An initial symbol-address formulation
matched only the text span: at `-O1`, this compiler emitted unused `.LC`
address constants into allocated `.rodata`. The full-build gate rejected
those objects. The compiler's constant-pool marking is conditional on its
expensive-optimization flag; enabling that flag removed the storage but
changed DMA instructions and was excluded. The typed numeric-address views
preserve the same algorithm and exact text with no nonempty allocated
sections outside `.text`. Both source objects and linked objects, including
controls, are checked for this restriction. No sections are stripped or
compiler output normalized. Real changed-source controls alter
selector comparison, DMA control and rejected-block status and reject for
each function. All current accepted save-header consumers are rebuilt with
their own controls, including the queued scene handoff and current game
block caller. The connected write path is described below. Whole-ROM equality
and these source matches do not establish successful physical-media or runtime
save/load behaviour.

## Serial write, polling completion and read-back retries

Five more ordinary C functions reconstruct the write core at `0x0804CA80`
(352 bytes), its wait wrapper at `0x0804CA6C` (20 bytes), comparison at
`0x0804CBE0` (88 bytes), wait-and-compare retry path at `0x0804CC38`
(64 bytes) and game write-and-compare retry path at `0x0804CCB0` (64 bytes).
These extend the same parameter, DMA and read interfaces used by the game
block loop. All five use explicit `agbcc` Thumb `-O1 -mthumb-interwork` flags.

The core captures its source pointer before narrowing the input block to a
halfword and its wait argument to a byte. It rejects a block at or beyond the
selected limit with `0x80FF`. Its 82-halfword stack buffer holds a trailing
zero, the low bits of four source halfwords, the selected address bits and
the two-halfword command prefix, constructed backward. The transfer count is
the address-bit count plus 67. The selected parameter rows' lengths six and
fourteen fit this buffer; the routine adds no validation for other parameter
values, source alignment or source capacity.

After DMA, the core polls bit zero at `0x0D000000`. A zero wait byte returns
at the first observed completion. A nonzero wait byte keeps polling the
vertical-count register at `0x04000006`, accumulating a positive count
difference or a wrap difference computed as current plus 228 minus previous.
After the accumulated word exceeds 136, a still-incomplete low port bit yields
`0xC001`; otherwise the status remains zero. No elapsed-count update occurs
while the vertical count stays unchanged, so this is not a general timeout
against a stalled counter. The source preserves the original access order.
Volatile stack views of the three halfword polling values and the accumulated
word retain their observed repeated loads. This is a compiler access view,
not evidence of asynchronous modification or the original source qualifiers.
The branch-scoped elapsed pointer exists before each difference calculation;
no register constraint or embedded instruction is used.

The comparison narrows its block input, reads four halfwords through the
accepted read provider and returns `0x8000` on the first difference from the
source. It ignores the read provider's returned status, matching the original
call. Each retry path permits three attempts, compares only after a zero
write status, and returns immediately on a successful comparison. The wait
path calls the matched wait wrapper. The game path calls the now source-owned
56-byte mode gate at `0x0804CC78`. Its native error value is `0x8080`, correcting
the earlier `0x8200` assumption: the load at `0x0804CCA4` addresses pool word
`0x0804CCAC`. The actual parameter row selected by value four has byte size 512.
One corrected ordinary-C recipe under the existing `-O1` profile matches all
56 bytes; changing `0x8080` to `0x8081` rejects one byte. The gate narrows its
block argument, returns that error for byte size 512, otherwise calls the owned
core with wait zero. No caller binding or API change is required. This closes
the contiguous 644-byte write family `0x0804CA6C..0x0804CCF0`; prior wrong-value
sources remain failed evidence. The game writer's full-word formal is explicitly narrowed in
its body; its accepted game caller retains the original halfword call-side
narrowing through an explicit cast.

All five extents, pools and alignment match without register constraints.
Their source objects and linked objects, including actual changed-source
controls, have no nonempty allocated section outside `.text`. Changing the
timeout threshold, wrapper wait value, mismatch status or retry bound rejects
the corresponding match. All current accepted save-header consumers are
recompiled with their own controls after the interface refinement. Earlier
loop, polling-workspace, register-binding and mode-gate failures remain local
and excluded. Static polling order and byte equality do not prove successful
physical-media writes, concurrent safety or save-format compatibility.

## Paired grouped actor transfer

The reader at `0x0801FCF8` (468 bytes) and writer at `0x0801FECC`
(400 bytes) now pass complete source qualification: two C functions and
868 bytes. The reader includes 456 instruction bytes and twelve literal bytes;
the writer includes 390 instruction bytes, eight literal bytes and two alignment
bytes. The full-project matching and progress gates pass with both installed.

The canonical collection has 160 twelve-byte records and fifty four-byte group
descriptors with start at byte zero, count at byte one and flags at byte two.
Older foreign headers inverted start/count and do not qualify those attempts.
The fifteen small-list loops instead transfer count at byte zero and traverse
capacity at byte one. Both grouped functions require mutable complete backing
of at least `0x348` bytes through input `+0x347`; the canonical context is only
a `0x320` prefix. Their 28-byte tail begins at `+0x320` and the complete
menu-choice record at `+0x33C`.

The reader clears the full `0x84C` collection and initializes the word receiving
one stream byte per group to zero. Each group consumes that byte and decrements
the word to zero before the next read. Two separate collection-count observations remain: the
first supplies the descriptor start, the second the total update and record
address. The latter's actual `r6` lifetime ends before the first record-reader
call. The writer's `r6` start snapshot instead survives the count-byte writer
call before supplying its record address. Valid capacities, collection indices,
complete backing and stream/provider state are preconditions, not new checks.

The reader keeps one genuine complete byte base and leaves its register
unconstrained. Its actual next-group `r8` value survives small-list calls; the
short count snapshot excludes the conflicting field-slot allocation naturally.
An explicit unsigned-byte truncation before shifting restores the large-record
low-nibble producer. Both sources preserve the actual late `r4` copy-then-add
cursor and a separate `r5` counter across the final five byte calls. Retained
old constructor and register-role attempts are disclosed; no embedded original
instructions, fabricated traffic or compiler-output changes are used.

Fresh normal/strict builds without diagnostic flags match all bytes, and both
first-list-limit controls changing fifteen to fourteen reject by one byte.
The actual-definition reader API unit passes 35 target facts and rejects nine
incompatible contracts; the writer unit passes 31 facts and rejects seven. The
reader unit uses its six actual providers plus the copy dependency; native incoming evidence
from the still-unconverted `0x0801B704` loader is recorded separately, with no
fabricated caller definition. The weekly/secondary-flag routine at
`0x0802005C` remains unconverted; its target domains and those of the condition
modules remain open. The actor-entry family's 25 extents and 3,224 bytes do not establish the
complete save format, executable inventory, valid save population or runtime
save compatibility.
