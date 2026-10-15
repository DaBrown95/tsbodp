# Local evidence retirement, 15 October 2026

The owner replaced indefinite generated-artifact retention with one current full
proof and a bounded set of useful failure evidence. Unique source attempts and
concise findings remain; an old hash ledger alone does not require its payloads
to remain on disk.

| Allocated project footprint | Bytes |
| --- | ---: |
| Before direct cleanup | 23,572,508,672 |
| After direct cleanup | 3,215,286,272 |
| Net reduction | 20,357,222,400 |

These are whole-project disk-usage measurements, counting shared inodes once.
They are separate from filesystem free-space changes or sums of deleted path
sizes. The after measurement includes the current verified full build.

Older build generations, obsolete proof archives, superseded compiler-trial
payloads, intermediate outputs, duplicate snapshots, large historical ledgers
and unused experimental toolchain builds were deleted outright. They were not
moved into another archive. No Time Machine or unrelated files were touched.

Original ROM inputs, all Git history, source and untracked source work, distinct
headers, configuration, documentation, the working toolchain and necessary
source dependencies remain. The latest verified full proof includes its
changed-source negative controls. Files needed to finish the current connected
C milestone also remain.

Historical documents and receipts describe checks performed at their stated
time. Retired bulk artifacts are no longer available for revalidation; their
hashes are historical records. Current matching can be verified by a fresh build
from the retained source, pinned tools and the owner's ROM. Inventory discovery
and disk cleanup add no recovered-C credit.
