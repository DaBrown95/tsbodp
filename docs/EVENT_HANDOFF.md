# Event payload representation copies

The existing 244-byte recorder at `0x0803A41C` now copies the first four
representation bytes of its actual `EventPayload` argument into an unsigned
word before kinds 2 and 7 read that word. The two copies use
`__builtin_memcpy`; the selected target has four-byte unsigned integers. They
replace the two integer-pointer dereferences through the declared byte array.
The public payload type, function signature, record layout, globals, metadata
and all other source bodies remain unchanged.

The copies occur inside the two consuming cases. They introduce no scalar read
for kinds that ignore the input. Kind 2 narrows the copied word to the output
halfword; kind 7 stores the word. For these cases, the first four input bytes
must have initialized representations. This is a focused object-representation
copy, not a claim that the upper four argument bytes have been initialized.

The selected compiler lowers each aligned four-byte copy inline. The complete
linked extent remains 244 bytes: 150 instruction bytes, 88 literal-pool bytes
and six zero bytes. Its sole function symbol owns the full extent. All six
native artifacts match the preceding recorder proof; preprocessed C changes.
Normal and strict positives match, and changing output flag `0x40` to `0x80`
changes one byte in both profiles. A full-source target check confirms
`sizeof(unsigned int) == 4`; a conflicting formal using the existing
`EventData` union rejects with a type conflict.

Two larger source representations failed and remain unaccepted. Copying the
argument into a separate local union produced 252 bytes. Giving the canonical
payload a named word/byte union produced 236 bytes: the compiler kept the
argument in registers instead of its original stack home. That seven-file
experiment was restored before this single-file repair. Its source proposals,
concise findings and small raw comparisons remain local. No register binding,
new qualifier, output patch or instruction transcription is used here.

The five existing caller bodies still contain their earlier word-pointer
stores. An attempted typed-word copy in the fade-in caller retained its
140-byte extent but changed 21 bytes because a loop-invariant zero acquired
another saved register. Testing stopped at that first caller; the remaining
four were not compiled under that proposal. This recorder repair does not
certify those caller stores or the entire end-to-end path.

The original 100-byte connection starter is also still unconverted. Its
typed-word-copy candidate produced 96 bytes. The random-result narrowing
omitted the original register move, with the shorter instruction sequence also
changing pool alignment. That candidate adds no C credit. The full-width active
count getter remains an original provider, while the slot and random-bound
providers have accepted source. See [the preceding handshake milestone](SERIAL_HANDSHAKE.md)
for the connected IRQ and timeout evidence.

Kinds 8–10 retain their existing foreign aggregate output views. The receiver's
record/payload overlays, partial global ownership, caller argument suffixes,
MMIO backing and asynchronous behavior remain separate uncertainties. The
repair establishes neither complete protocol behavior nor new runtime or
gameplay evidence.

This milestone adds zero functions and zero C bytes. The verified total remains
1,705 functions and 242,112 C extent bytes, with 500 separately counted glue
bytes. The fresh full build, source controls, inventory and treemap passed,
along with 298 tests and fourteen full-proof failure cases. Inventory discoveries and source-quality repairs do not
earn additional recovered-C credit. The fixed historical mapped-extent
comparison remains 319,640 bytes; the complete game-code denominator remains
open.
