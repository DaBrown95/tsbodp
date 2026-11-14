# Remaining C triage

4 unowned inventory rows / 3,684 bytes. Scores compare complete retained extents, including missing or extra bytes; they grant no source credit.

Regenerate with `python3 tools/triage.py`; check with `python3 tools/triage.py --check`. Private evidence may be unavailable on another checkout; recorded rows then say so. Historical active effort and search wall time are unrecorded, not zero.

| ROM | Name | Inventory | Best bytes / differences | Compared extent | Status | Priority | Context |
| --- | --- | ---: | ---: | ---: | --- | ---: | --- |
| `0x023E8` | `sub_080023E8` | 1400 | 1400 / 15 | 1400 | near-miss | 7 | canonical-current |
| `0x19640` | `sub_08019640` | 544 | 528 / 371 | 544 | attempted | — | canonical-current |
| `0x3DC48` | `link_serial_interrupt` | 1616 | unqualified/unavailable | — | attempted | — | — |
| `0x49968` | `sub_08049968` | 124 | unqualified/unavailable | — | suspected-not-C | — | — |

Fresh search comparisons awaiting source review:
- `0x023E8`: 1400 bytes / 22 differences over 1400 bytes; no source credit.
- `0x19640`: 544 bytes / 34 differences over 544 bytes; no source credit.
- `0x3DC48`: 1616 bytes / 373 differences over 1616 bytes; no source credit.

Priority1–7 follows the requested near-miss order; other full-size candidates with at most32 differing bytes also enter the near-miss queue. Existing attempts override the older “untouched” list. Private types and backing/API premises still require acceptance review.

Closed notes: `0x0A0A4`: Inventory290; retained full comparison292. Rejected cursor/header models excluded. `0x1510C`: Rejected induction-register collision excluded. `0x19D80`: Historical volatile368/121 is unqualified; use ordinary-state evidence. `0x42964`: Matching 656-byte C owner accepted; earlier request/ordinal binding collision excluded. `0x48AF8`: Inventory126; retained full comparison128 includes trailing alignment. `0x48BF8`: Inventory86; retained full comparison88 includes trailing alignment. `0x49968`: Reachable native NOP remains unexplained; suspected non-C origin.
