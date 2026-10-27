# Remaining C triage

19 unowned inventory rows / 7,994 bytes. Scores compare complete retained extents, including missing or extra bytes; they grant no source credit.

Regenerate with `python3 tools/triage.py`; check with `python3 tools/triage.py --check`. Private evidence may be unavailable on another checkout; recorded rows then say so. Historical active effort and search wall time are unrecorded, not zero.

| ROM | Name | Inventory | Best bytes / differences | Compared extent | Status | Priority | Context |
| --- | --- | ---: | ---: | ---: | --- | ---: | --- |
| `0x023E8` | `sub_080023E8` | 1400 | 1400 / 21 | 1400 | near-miss | 7 | canonical-current |
| `0x03248` | `sub_08003248` | 348 | 336 / 187 | 348 | attempted | — | canonical-current |
| `0x067E0` | `sub_080067E0` | 148 | 152 / 92 | 148 | attempted | — | canonical-current |
| `0x0A0A4` | `sub_0800A0A4` | 290 | 292 / 2 | 292 | near-miss | — | private-provisional |
| `0x0B564` | `frame_map_draw_iwram` | 320 | 320 / 116 | 320 | attempted | — | canonical-current |
| `0x0F034` | `sub_0800F034` | 308 | 308 / 4 | 308 | near-miss | 3 | canonical-current |
| `0x11C60` | `sub_08011C60` | 400 | 400 / 108 | 400 | attempted | — | canonical-current |
| `0x19640` | `sub_08019640` | 544 | 528 / 371 | 544 | attempted | — | canonical-current |
| `0x28234` | `sub_08028234` | 160 | 160 / 71 | 160 | attempted | — | canonical-current |
| `0x39CF0` | `sub_08039CF0` | 392 | 392 / 109 | 392 | attempted | — | canonical-current |
| `0x3D788` | `sub_0803D788` | 200 | 200 / 1 | 200 | near-miss | 1 | canonical-current |
| `0x3DC48` | `link_serial_interrupt` | 1616 | 1624 / 809 | 1616 | attempted | — | private-provisional |
| `0x40AB4` | `sub_08040AB4` | 692 | 692 / 306 | 692 | attempted | — | canonical-current |
| `0x42964` | `sub_08042964` | 656 | 652 / 594 | 656 | attempted | — | private-provisional |
| `0x48A14` | `sub_08048A14` | 68 | 68 / 10 | 68 | near-miss | 6 | canonical-current |
| `0x48AF8` | `sub_08048AF8` | 126 | 128 / 112 | 128 | attempted | — | canonical-current |
| `0x48BF8` | `sub_08048BF8` | 86 | 88 / 2 | 88 | near-miss | — | canonical-current |
| `0x495C4` | `sub_080495C4` | 116 | 116 / 3 | 116 | near-miss | — | canonical-current |
| `0x49968` | `sub_08049968` | 124 | unqualified/unavailable | — | suspected-not-C | — | — |

Fresh search comparisons awaiting source review:
- `0x023E8`: 1400 bytes / 22 differences over 1400 bytes; no source credit.
- `0x48A14`: 68 bytes / 10 differences over 68 bytes; no source credit.
- `0x48BF8`: 88 bytes / 2 differences over 88 bytes; no source credit.
- `0x495C4`: 116 bytes / 3 differences over 116 bytes; no source credit.

Priority1–7 follows the requested near-miss order; other full-size candidates with at most32 differing bytes also enter the near-miss queue. Existing attempts override the older “untouched” list. Private types and backing/API premises still require acceptance review.

Closed notes: `0x0A0A4`: Inventory290; retained full comparison292. Rejected cursor/header models excluded. `0x1510C`: Rejected induction-register collision excluded. `0x19D80`: Historical volatile368/121 is unqualified; use ordinary-state evidence. `0x42964`: Rejected request/ordinal binding collision excluded; private owner remains provisional. `0x48AF8`: Inventory126; retained full comparison128 includes trailing alignment. `0x48BF8`: Inventory86; retained full comparison88 includes trailing alignment. `0x49968`: Reachable native NOP remains unexplained; suspected non-C origin.
