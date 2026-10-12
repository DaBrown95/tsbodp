> Historical first pilot. The later [RAM and interrupt milestone](RAM_AND_INTERRUPTS.md)
> adds a matching complete ROM layout and 14 further C functions.

# Initial ROM audit and matching pilot

Recorded 12 October 2026. Main target: original USA/Europe multilingual release.
USA revision 1 is retained as a separate comparison reference.

## Verified identities

Both files are 16,777,216 bytes with title `THE SIMS ADV`, game code `ASIE`, fixed
header byte `0x96`, and valid header checksums. All catalogue checks pass.

| Target | Revision | SHA-1 |
| --- | --- | --- |
| USA/Europe | 0 | `fb5662172fadebf4577f6f6f163741fc041c11e6` |
| USA revision 1 | 1 | `7038fa0e4cb8aeac9e48a0b45574db66cba39e73` |

USA/Europe SHA-256:
`92ead9ff9467dbc23780e768278fe2e4bf7a0708447a0785770c129a5dbdb06e`.

USA revision 1 SHA-256:
`c1fc9976b968336f7f65ba8a13d5e796e41908d047ee1aa6b247ca4222e76427`.

SHA-1, MD5, CRC32 and size agree with [No-Intro metadata mirrored by libretro](https://github.com/libretro/libretro-database/blob/master/metadat/no-intro/Nintendo%20-%20Game%20Boy%20Advance.dat),
catalogue version 2026.10.07. SHA-256 was independently calculated locally and
is now pinned. The supplied files were read without alteration.

## Bounded static findings

- ARM startup begins at `0x080000C0` and switches to Thumb at `0x080000EC`.
- The startup Thumb entry pointer is `0x08025C0D` (code at `0x08025C0C`).
- Startup copies `0x15B0` bytes from `0x08FDA478` to IWRAM `0x03000000`, and
  `0x27F8` bytes from `0x08FDBA28` to EWRAM `0x02000000`. Executable extents
  within these regions are not yet classified.
- Startup installs ARM IRQ dispatcher `0x08000160` through `0x03007FFC`.
- ROM offset `0xD6F4E4` contains a `player.c` revision string dated 19 March
  2003. This is consistent with the prior Krawall lead, but does not by itself
  establish the exact library revision or every audio routine.
- Revision 1 first differs after the header at offset `0x114`, a startup source
  pointer. Direct same-offset differences cannot be interpreted as semantic
  changes because code and data may have moved.

`make analyze` regenerates the map and local disassembly. This is a bounded
startup audit, not a complete ROM map or a runtime test.

## Exact linked C matches

| Reconstructed name | Address | Bytes, including pools and padding |
| --- | --- | ---: |
| `set_word_0300217c` | `0x0803E448` | 12 |
| `get_word_0300217c` | `0x0803E454` | 12 |
| `set_irq_table_entry` | `0x0801F8C4` | 16 |
| `configure_blending` | `0x080393D4` | 40 |
| `set_word_03002180_bit0` | `0x0803E460` | 44 |

All five match with the pinned agbcc Thumb backend and `-O2 -mthumb-interwork`.
They are compiled from authored C and linked at the listed addresses with GNU
binutils; the indexed table's external symbol is resolved by the linker.
No original instruction body, inline assembly or byte patch is used in these C
candidates. Names are reconstructed; the gameplay meaning of the two RAM words
is not established.

Total: five matching functions, 124 linked bytes. This is not a whole-game code
percentage. The matrix also passes at `-O3` and `-Os`; `-O0` fails all five,
and `-O1` fails the bit-update routine. The original compiler version and options
remain incompletely identified.

A deliberate C edit to store `value + 1` instead of `value` fails comparison
after compilation and linking. Prior mismatching candidates, raw differences,
source snapshots and commands are retained in ignored run directories.

## Next bounded work

Map the copied RAM regions and identify a connected subsystem with a loop,
structure access and cross-function calls. Extend source and symbol definitions,
preserve relocation evidence, and establish the whole-ROM section layout.
Only then can whole-ROM source-driven matching be claimed. No gameplay test,
whole-ROM build, commit or remote publication has been performed in this pilot.
