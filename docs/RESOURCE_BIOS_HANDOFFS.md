# Connected resource BIOS handoffs

These seven Thumb entries are explicit assembly glue: 28 verified bytes and
zero compiled C bytes. Each extent contains one service call and `BX LR`, with
no literal pool or alignment bytes. They retain the existing address-based
service names and source/destination ABI declarations. Their separate linked
positive images equal all four reference bytes; independently assembled edits
to the service number each differ by one byte. The return instruction and
extent stay identical in those controls.

| Entry | ROM offset | Platform service interpretation |
| --- | ---: | --- |
| `resource_bios_swi_0b` | `0x4C8C4` | CpuSet |
| `resource_bios_swi_0c` | `0x4C8C0` | CpuFastSet |
| `resource_bios_swi_11` | `0x4C8DC` | LZ77 output using byte writes |
| `resource_bios_swi_12` | `0x4C8D8` | LZ77 output using halfword writes |
| `resource_bios_swi_13` | `0x4C8D4` | Huffman decoding |
| `resource_bios_swi_14` | `0x4C8E8` | Run-length output using byte writes |
| `resource_bios_swi_15` | `0x4C8E4` | Run-length output using halfword writes |

The service interpretation comes from mGBA's BIOS service enumeration and
dispatch, rather than from game addresses. Source and destination use R0/R1;
the copying services additionally receive control in R2. The decompression
pairs differ in write width, relevant to VRAM destinations. CpuSet control bit
26 selects word transfers. The copying services require suitable address
alignment. These are platform contracts corroborated by the emulator source;
the matching wrapper proof does not execute or reconstruct the BIOS itself.
See [mGBA service IDs](https://github.com/mgba-emu/mgba/blob/master/include/mgba/internal/gba/bios.h)
and [mGBA BIOS dispatch](https://github.com/mgba-emu/mgba/blob/master/src/gba/bios.c).
No emulator implementation has been copied into this repository.

The reconstructed dispatcher at `0x16978` uses CpuSet for raw payloads, then
the byte-writing LZ77/Huffman/run-length services for selectors 1/2/3. Its
alternate at `0x16ABC` uses CpuFastSet and the halfword-writing LZ77/run-length
entries. That alternate has no selector-2 operation. These source observations
remain distinct from supported-input or gameplay claims. The copied ARM
callbacks at RAM `0x030036D0` and `0x03003370` are custom bodies, remain
unconverted, and receive no C coverage from these service wrappers.

Installation at `0x16A48` uses CpuSet with controls `0x04000084` and
`0x040000D4`, copying 528 and 848 bytes. Map installation at `0x39E78` uses
controls `0x04000054` and `0x04000039`, copying 336 and 228 bytes. Those copy
extents include following instruction prefixes; they do not define the
semantic function boundaries. Map snapshot/restore at `0x39ED4`/`0x39F30`
uses the CpuFastSet entry with word count `0x3000`. Provider linkage and these
counts are static facts from the accepted callers, rather than runtime checks
of alignment or buffer capacity. Existing display-specific aliases for the
same physical service entries remain valid and add no duplicate body.

The ignored proof directory contains each original four-byte slice, linked
candidate, changed-service candidate, retained assembly, ELF symbol audit,
commands, hashes and complete comparisons. The one function symbol owns the
whole `.text` extent at the original Thumb address. Neither image has another
allocated section or unresolved relocation. Source inspection permits only
the declared service call and return, with no embedded ROM data or fabricated
padding. No C source body, toolchain profile or compiler flag changes accompany
this glue batch. Whole-ROM integration must be checked separately after the
seven providers are promoted; no whole-ROM or gameplay result is claimed by
these private proofs.
