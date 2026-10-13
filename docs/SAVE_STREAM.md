# Save-stream reconstruction

The reconstructed path connects the published menu-choice and actor-need
save/load callers to a shared byte/bit cursor, record views, slot transfers,
header initialization and audio/display-status handoff. It has 26 matching C
functions covering 1,788 bytes. Each full extent, pool and alignment was linked
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
output patches or comparison masks. The other 25 functions use ordinary C.

Function boundaries include return paths, referenced literal pools and alignment
up to the next mapped entry. The checksum's instruction body is 34 bytes and its
accepted extent is 36 with alignment. Block read/write bodies are 46 bytes and
their extents are 48. Slot scan has a 122-byte CFG envelope and a 124-byte extent.
These remain bounded static claims, not a complete code inventory.

Useful failed approaches, original/actual bytes, assembly, source snapshots and
real negative controls remain in ignored local reports. The 108-byte buffer
builder and 148-byte nibble writer are still unconverted; candidates are excluded
from coverage. The library transfer bodies, full game-state serializer and the
unconverted header-refresh branch also remain explicit. Next connected targets
are those producers and the higher game-state load/save consumers.
