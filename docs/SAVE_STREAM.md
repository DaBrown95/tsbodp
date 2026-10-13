# Save-stream reconstruction

The reconstructed path connects the published menu-choice and actor-need
save/load callers to a shared byte/bit cursor, record views, slot transfers,
header initialization and audio/display-status handoff. It has 43 matching C
functions covering 3,184 bytes. Each full extent, pool and alignment was linked
at its original ROM address and compared with the fixed reference. Each also
has a compiled changed-source control. These are static and compiler results;
no runtime save/load or EEPROM compatibility claim is made.

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

## Transfer and checksum boundary

Slots use 255 transfers of eight bytes, with block address `255 * slot + 2`, so
the working span is 2,040 bytes. The lower interfaces at `0x0804C9BC` and
`0x0804CCB0` narrow the block argument to 16 bits and perform the library
transfer; they remain explicit unconverted interfaces. Their returned status
is discarded by these game loops. The source does not add retries or bounds.

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
`+0xA` to an unconverted setting interface and scans the slots. The inverse
setting producer stores a returned word narrowed to that byte, sets byte
`+0xB` to one and leaves word one in the return register. The setting's original
meaning and full callee contract are not established here.

The commit routine invokes the unconverted buffer builder, suspends audio,
writes and reads a slot, resumes audio, validates and loads or clears its record,
then stores the selected slot. Its two game audio wrappers call the accepted
`audio_deactivate_hardware` and `audio_activate_hardware` functions. Transfer
begin saves `DISPSTAT` (`0x04000004`) into `0x03005D80`, writes `0x3FFF` to the
interrupt acknowledge register (`0x04000202`), clears `DISPSTAT`, and invokes
the unconverted transfer-configuration interface with 64. Transfer end restores
the saved status. This observed ordering does not prove concurrent safety or
successful physical-media writes.

## Source and verification evidence

The nibble reader uses two scoped C register bindings: the shared cursor pointer
in `r5` and the high-nibble scalar in `r1`. They are actual algorithm values and
are not live across function calls. The cursor is four bytes before the bit
position in the observed eight-byte view. Its inline low-nibble reader is a
semantic byte accessor. There are no original instruction-body transcriptions,
output patches or comparison masks. The other 42 functions use ordinary C.

Function boundaries include return paths, referenced literal pools and alignment
up to the next mapped entry. The checksum's instruction body is 34 bytes and its
accepted extent is 36 with alignment. Block read/write bodies are 46 bytes and
their extents are 48. Slot scan has a 122-byte CFG envelope and a 124-byte extent.
These remain bounded static claims, not a complete code inventory.

Useful failed approaches, original/actual bytes, assembly, source snapshots and
real negative controls remain in ignored local reports. The 108-byte buffer
builder and 148-byte nibble writer are still unconverted; candidates are excluded
from coverage. The library transfer bodies, several game-state subserializers and the
unconverted header-refresh branch also remain explicit. Next connected targets
are those producers and the higher game-state load/save consumers.

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
and real negative controls. The nibble writer and the remaining child/module
serializers stay unconverted.

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
controls against the final union/header closure. The buffer builder, nibble
writer, grouped subrecord loader/serializer and retained condition module
remain explicit unconverted interfaces. Static transfer order and compiler
equality do not establish save compatibility or gameplay behaviour.
