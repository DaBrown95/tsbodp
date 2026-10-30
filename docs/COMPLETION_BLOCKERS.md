# Remaining reconstruction and closure work

The current gates verify **2,534 C functions / 317,164 C extent bytes**, plus
**4,068 assembly bytes**. Original slices still supply 16,455,984 bytes of assets
and unconverted code. Whole-ROM equality is proven; complete source ownership
is not. The fixed 319,640 bytes remain a historical comparison, not a complete
code denominator.

The [manifest](../config/build-us-eu.json), [inventory](../assets/rom-inventory.json)
and generated [triage](TRIAGE.md) contain **10 unowned rows / 5,220 estimated
bytes**. This finite worklist does not establish that all executable regions
have been discovered. Candidate scores grant no source credit.

## Latest accepted source

The [point-to-cell converter](../src/frame/frame_grid_point_to_cell.c) at
`0x48AF8` and [inverse projector](../src/frame/frame_grid_inverse_point.c) at
`0x48BF8` add **two C functions / 216 extent bytes**. Their native function
bodies are 126 and 86 bytes; each extent also owns two alignment bytes. Real
origin inputs retain the partial-word lifetime that produces the original
save history, while the complex view lets the compiler forward the high word.
Both words are assigned before their own reads. The same producer works in
both complete functions, with their distinct output and stack lifetimes.
Both real eight-to-nine source controls reject by one byte; the full-ROM
control also rejects. The original repeated upper-Y test and missing upper-X
test remain documented bugs. See [projection](GRID_INVERSE_RECONSTRUCTION.md).

## Remaining source work

| Region | Consequential obstacle |
| --- | --- |
| Renderer `0x23E8` (1,400), finalizer `0x3248` (348) | Recover the remaining real stack homes and comparison lifetimes. Native input and partial-word ownership have improved complete candidates; exhausted binding and address-only families stay parked. |
| ARM map drawer `0xB564` (320) | Preserve native traversal, source writebacks and payload carriers together. Individually successful fragments have not produced a complete match. |
| Activity preparation `0x19640` (544) | Preserve geometry roles and bound reloads while recovering the native availability and output-pointer allocation. |
| Scene object `0x28234` (160) | Its entry remains weakly supported. Incoming searches have no qualified hit; coordinate graph candidates remain nonmatches. No absence or executable exclusion follows. |
| Selected-map worker `0x39CF0` (392), map collapse `0x495C4` (116) | Remaining producer and address/base continuity differences need complete source matches. |
| Serial provider `0x3D788` (200) | Parked at one byte different, with both compiler investigations preserved. Reopen only for materially new evidence. |
| Serial IRQ `0x3DC48` (1,616) | Preserve the 1,624-byte nonmatch and native receive/readiness lifetimes. Prior callback/contract repairs supplied no missing source fact. |
| Audio master `0x49968` (124) | Two bytes remain unexplained around a reachable native NOP. Original SDK lineage does not justify an assembly exception. |

Further compiler or tool work needs a concrete unfinished consumer and a
falsifiable experiment. A worse complete candidate is useful when it reveals
a native lifetime or changes the next experiment; it earns zero recovered C.
Useful failed source families remain private with consolidated findings.

## Executable ownership and semantic uncertainty

The census retains **97 callback and 21 dispatch observations at 111 physical
sites**. Observed table prefixes do not prove complete target populations.
Unqualified serialized selectors, callback writers, aliases and executable
installations can still conceal unowned executable code. The finite rooted
instruction account has no unowned instruction bytes outside the remaining
worklist; it does not establish an executable denominator.

The audio effect path is a concrete open ownership question. Its native byte
selector does not enforce the observed 51-record prefix. A finite capture of
766 potential field locations recovers only existing source owners where
exact entries are qualified. Effects 106/107 also produce unqualified ROM-window
operands, including `0x08ED0975`. Their source words have independent numeric
data uses; that does not exclude alternate callback interpretation. No actual
selecting module/state, complete effect domain or new executable entry has
been established. Resolve the reaching selector domain before seeding bodies
from these words. This diagnostic adds **zero source or ownership closures**.

Within existing source extents, historical formals, field names and event
meanings are semantic uncertainties. Unknown code/data/padding roles and
alternate entries require a separate ownership assessment: **754 owned-extent
bytes still have unresolved roles**. Neither category becomes closed merely
because the containing source extent matches.

Known copies cover 19,188 distinct ROM source bytes, including data. Writer and
incoming-target populations remain open. The twelve bytes at `0x1DB20..0x1DB2C`
still have no independently established entry or source/data owner. Other
serialized, palette, scene and saved-state obligations remain in the
[whole-ROM inventory](WHOLE_ROM_INVENTORY.md), [bounded findings](BOUNDED_INVENTORY.md)
and [runtime observations](RUNTIME_OBSERVATIONS.md). Matching source establishes
no new runtime execution.

## Completion gate

Finish when every executable region has a matching source owner, genuine
assembly exceptions are justified, material inventory gaps are resolved, and
a clean reproducible byte-identical build and final documentation are on
`main`. Keep references fixed, changed-source controls, source ownership,
mapped extents and runtime evidence separate. Run applicable tests and
`make progress`; audit staged contents and outgoing history before publishing.
Keep contribution features disabled. Follow the [retention policy](LOCAL_OUTPUT_RETENTION.md):
retain one current paired full proof, unique useful attempts and bounded
failures, then retire obsolete outputs. The reconstruction remains incomplete.
