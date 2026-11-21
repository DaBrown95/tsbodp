# Remaining C triage

1 unowned inventory row / 124 bytes. Scores compare complete retained extents, including missing or extra bytes; they grant no source credit.

Regenerate with `python3 tools/triage.py`; check with `python3 tools/triage.py --check`. Private evidence may be unavailable on another checkout; recorded rows then say so. Historical active effort and search wall time are unrecorded, not zero.

| ROM | Name | Inventory | Best bytes / differences | Compared extent | Status | Priority | Context |
| --- | --- | ---: | ---: | ---: | --- | ---: | --- |
| `0x49968` | `sub_08049968` | 124 | unqualified/unavailable | — | suspected-not-C | — | — |

Priority1–7 follows the requested near-miss order; other full-size candidates with at most32 differing bytes also enter the near-miss queue. Existing attempts override the older “untouched” list. Private types and backing/API premises still require acceptance review.

Closed notes: `0x0A0A4`: Inventory290; retained full comparison292. Rejected cursor/header models excluded. `0x1510C`: Rejected induction-register collision excluded. `0x19D80`: Historical volatile368/121 is unqualified; use ordinary-state evidence. `0x42964`: Matching 656-byte C owner accepted; earlier request/ordinal binding collision excluded. `0x48AF8`: Inventory126; retained full comparison128 includes trailing alignment. `0x48BF8`: Inventory86; retained full comparison88 includes trailing alignment. `0x49968`: Reachable native NOP remains unexplained; suspected non-C origin.
