# Link status polling

Two connected C functions reproduce 320 bytes at their original addresses: the
status-poll starter at `0x0803D5C0` (256) and confirmation waiter at `0x0803E368`
(64). Normal and strict builds match the complete extents, including 234
instruction bytes, 80 literal-pool bytes and six zero alignment bytes. Each
changed-source control differs by one byte under both profiles.

The starter stores its full count argument before checking link flags `0x10004`.
A busy result returns five. Otherwise it writes `0xFFFF` to the serial-data
halfword, polls fresh volatile control halfwords, and can return seven when the
existing callback returns a word whose low byte is zero. That predicate includes
values such as 256; it is not a full-word zero test. The callback's canonical
prefix member is at offset eight and has type `unsigned int (*)(void)`.

After writing `0xFEED`, the starter selects its control path using mask `0x4`,
stores the Thumb handler address `0x0803D9E9` in the existing IRQ table's first
unsigned word, and performs the observed interrupt/timer register updates. It
then calls accepted `irq_wait_vblank` and the original status reader at
`0x0803E298` (a mapped 124-byte extent). That reader can return the full word at `0x0300218C`; no byte
narrowing is justified. Its unsigned-word declaration is a caller ABI view,
not proof of the original return signedness or source type.

The waiter sets link flag `0x20000`, then continues while flag `0x4` is absent OR
its unsigned wait count is below twenty. Keeping the volatile flag test first
also preserves the initial read even though count zero already requires the
body. No dummy read is added. If flag `0x4` stays set and the wait service returns, the loop calls it twenty
times before clearing flag `0x20000`. This does not establish a
frame duration or termination under changing flags; unsigned count wrap is
possible and hardware progress is untested.

The shared endpoint remains the existing partial access view. Its complete
wire-record layout has not been reconstructed. Existing full C definitions of the callback
setter/clock and IRQ-table setter/restorer support interface checks; they are
not direct callees of these two bodies. Only the VBlank waiter is an accepted
direct callee. A raw unsigned-word table store does not establish an original
`void(void)` IRQ prototype or validate every possible callback population.

The installed IRQ entry at `0x0803D9E8` and status-reader entry at `0x0803E298`
remain original boundaries with zero new C credit. Their mapped 608-byte and
124-byte extents include pools and gaps; this batch does not establish their
compiler-owned boundaries. The 113 static serial findings and held 117
scene-controller work supply prior context, alongside the existing IRQ and
endpoint source history. They do not prove polling gameplay, a complete link
protocol, portable MMIO semantics, callback lifetime or interrupt completion.
The target-specific function-pointer-to-word conversion and asynchronous access
assumptions remain explicit. No linked-game or hardware fixture has run here.

The checks cover thirteen physical layout/API facts and five complete existing
provider definitions. Only the 40-byte VBlank waiter is a direct accepted callee;
the four supporting callback/table interfaces account for 84 previously accepted
extent bytes. These are type checks, without new provider byte or execution
credit. Deliberately wrong clock return, callback offset, flag width and IRQ-table
element width reject for the intended errors. Source controls change busy result
five to six and the wait threshold twenty to nineteen.

The fresh full-ROM matching build and refreshed progress record 1,703 verified C
functions and 241,460 C extent bytes, a gain of two functions and 320 bytes.
Separate glue remains 500 bytes. The fixed 16 MiB ROM is byte-identical and the
changed-source whole-ROM control rejects; 16,535,256 bytes remain explicit
unconverted regions. Six observed zero bytes move from estimated gaps into
compiler-owned extents without becoming instruction bytes. Qualified static
instruction evidence stays 270,054 bytes and inventory mapped extents stay
323,786 bytes. The historical comparison remains 319,640 bytes; the complete
game-code denominator stays open.
