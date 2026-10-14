# Scene need-effect collection snapshot

`scene_save_need_effect_collection` reconstructs the complete 136-byte Thumb
extent at ROM `0x202E0..0x20368`, including both literal pools. The accepted
primary-scene exit passes scene entry data and scene ID using the existing
pointer and full-word argument contract. Its former address-based alias is
renamed without changing the caller's instructions, controls or compiler profile.

The function follows the active need-effect list at `0x03005868`. For every node
whose byte at `+0x62` is nonzero, it records the low byte of kind `+8`, optional
byte `+0x72`, and the upper byte of the signed halfword at `+0x70`. It then records
the associated object's direction at `+0x12` and signed high halfwords of its
16.16 position at `+0x1A` and `+0x1E`. Those two coordinates form the initialized
eight-byte `FramePoint` passed to original `frame_grid_point_to_cell` at
`0x48AF8`. The converter's returned status is ignored. Mode at `+0x5F` is read
after that call, and the list's next pointer is read after the copy wrapper.
These reload points and the separate object loads follow the original body.

The local record has 12-byte stride and four-byte alignment. Its four entry
bytes occupy offsets zero through three; the converter receives the cell at
`+4`; direction occupies byte eight. On success, the observed converter writes
two separate coordinate bytes at offsets four and five. On failure it leaves
both untouched, and the ignored status does not prevent copying the record.
Bytes six, seven, nine, ten and eleven always remain unwritten by this snapshot
and are still transported; a failed conversion also retains the previous
contents of bytes four and five. A GNU89 union exposes the complete
unsigned-byte representation; the copy wrapper uses that aligned byte view
rather than treating unspecified bytes as initialized integer values. Neither
source adds clearing, validation or synthetic reads. Coordinate access is a
separate word/halfword union view, with target little-endian offsets and layout
verified by the pinned compiler; it does not change the shared actor layout.

`actor_entry_save_collection_record` reconstructs `0x20C54..0x20C70` (28 bytes).
It calls the accepted 196-byte collection reservation provider at `0x204B0`
with the original context and word group. If a destination is returned, an
ordinary structure assignment copies all 12 representation bytes. Its natural
compiled body is 26 bytes followed by two assembler/linker zero alignment bytes.
It does not expose the residual return register as a meaningful C return value.
The existing provider's capacity guard and unchecked group, pointer and storage
limits remain in effect. No complete allocation capacity or gameplay behavior
is established by these two functions.

Source/control byte comparisons, strict declaration diagnostics, full native
extents, current literal header closure and layout/API checks are distinct from
finite execution models. The original converter remains explicit and earns no
recovered-C credit. Finite models initialize stack representation patterns to
observe transported bytes, execute both new bodies and the accepted reservation
body through their actual calls, and abstract only the original converter;
they cannot establish arbitrary provider effects, hardware behavior or gameplay.
