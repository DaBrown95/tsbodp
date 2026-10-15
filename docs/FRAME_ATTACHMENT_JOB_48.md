# Attachment job kind 48

Three connected ordinary C bodies reproduce 596 bytes at their original
addresses, including both internal literal pools and the four observed zero
alignment bytes. Their fresh normal and strict positives match; each genuine
changed-source control differs by one byte under both profiles. No new low-level
glue is introduced.

| Body | ROM offset | Instructions | Literals | Zero alignment | Full span |
| --- | ---: | ---: | ---: | ---: | ---: |
| Begin | `0x468DC` | 72 | 0 | 0 | 72 |
| State update | `0x466B4` | 464 | 24 | 4 | 492 |
| Dispatch | `0x46924` | 32 | 0 | 0 | 32 |
| **Total** | | **568** | **24** | **4** | **596** |

The observed 36-byte need-effect definition row 102 at `0x08063CD4` supplies
the begin and dispatch callbacks at fields 12 and 16. The accepted allocator
copies these roles to state fields `0xF0` and `0xF4`, and the accepted attachment
status path calls the latter with the owner and actor. The record-kind guard
is 48; it is distinct from definition-row index 102. These are static producer
and consumer connections, without a claim that every possible writable callback
target or selector has been identified. Other callbacks in the row remain
explicit original code.

Begin allocates one of the existing three attachment records, stores the full
incoming kind, obtains attachment zero's point, requests route mode three and
animation six, and reports allocation success. Its local point has no invented
initialization: a defined source call requires complete output from the point
provider before the route reads it. Dispatch retains the original unconditional
lookup-result dereference, calls the worker only for kind 48 and otherwise
returns zero.

The worker observes the actor's need-state pointer before its phase switch.
Running byte exactly one forces phase one. Phase zero either enters the existing
low-need animation path or creates an optional parameter indicator, selects the
observed direction, enters phase 67, initializes the actor countdown and retains
the audio sample handle. Phase 67 selects adjustment-table row 12 across eight
needs and tracks the signed parameter or countdown. Parameter advancement selects
phase 68, which copies attachment one's position before completion. The need threshold can independently select
completion. Phase one stops the sample, restores the animation/effect and
finishes the retained indicator. Unknown phases retain result one.

The direction lookup at `0x0807FBF0` uses an index scaled by four and a word load
followed by a byte store. It has its own provisional `const unsigned int[]`
declaration and does not reuse the existing byte reverse-direction table at a
different address. The accessed width is confirmed; complete capacity and the
original declaration's signedness are not established.

The sources import existing selector-specific record, actor, need-effect and
work views. Layout checks establish their accessed sizes, offsets and target
alignment. These overlapping views are not presented as a universal effective
type or complete storage-owner proof. The existing allocator's 256-byte request
and clearing operation do not settle every reused-storage invariant. The signed
countdown's source-defined domain excludes `INT_MIN`; original native wrapping
outside that domain is a separate observation.

The actual indicator creator dereferences its object allocation before returning,
so an allocator-null case is outside that provider's defined completion domain.
Any simulated null return must be labelled as a caller-only formal diagnostic.
Reached indicator updates, need arrays, definition rows, direction words and
resource pointers require valid initialized backing and lifetimes.

The 25 positive target type units cover the 20 existing full provider definitions,
the three new definitions, 30 layout facts and word stride. Nine deliberate wrong
API, layout and stride units reject. The old-provider units are declaration/body
checks, not fresh linked matching pairs or proof that their internal calls are
all declared under the strict profile. The normal/strict native roles and the
header-name migration have separate complete preprocessor/native comparisons.

The supplied-code Thumb checks cover 232 base fixtures across three register
seeds: 211 initialized cases conditional on the selector views, 17 broader ABI
cases, two formal alias cases, one injected service-effect case and one native-only
`INT_MIN` case. The source-statement model therefore covers 231 conditional
fixtures; the native-only case is excluded from that claim. Actual dispatch enters
the supplied worker. All three retained source controls have witnesses.

Five sequences include begin, parameter advancement, attachment positioning and
cleanup; the 150 countdown needs 151 direct phase-67 calls before completion is
selected. Thirteen wrong models diverge in their complete projected outputs. A
fourteenth is separately rejected for an invalid byte-formal contract and is not
counted as an output divergence. Twenty-eight native/domain faults and 24 reader
corruptions reject. The missing-pool test reaches the actual four-byte read at
`0x080467A0`; it has no ROM fallback. Root separately replayed the frozen evidence
under a writer/process trap, rejected eight additional claim corruptions and
rejected installed validation before public adoption.

These fixtures use 20 explicit chosen service contracts, zero original native
adapters and an independent source-statement model. They do not execute the
providers' internal C, the actual C source on a host, hardware or the whole game.
The reused supplied-code executor is unchanged. The initial three-code-run
producer and later four-run replay recheck the same fixtures, rather than adding
source coverage or independent cases.

The fresh full build and refreshed progress gates pass with 1,693 verified C
functions covering 239,892 bytes, a gain of three functions and 596 bytes. The
16 MiB ROM is byte-identical, including literal pools and alignment; the
changed-source whole-ROM control rejects. The separate assembly glue remains
500 bytes, and 16,536,824 ROM bytes remain explicit unconverted regions.

The regenerated census moves four zero alignment bytes from estimated gaps into
compiler-owned extents. They do not become instruction bytes. Qualified static
instruction evidence remains 270,054 bytes, and inventory mapped extents remain
323,784 bytes. The fixed historical comparison stays 319,640 bytes. These extents
are not a complete game-code denominator; inventory discovery adds no C credit.

The next connected source target is job kind 71: its state worker and the begin
and dispatch callbacks supplied by definition row 100. The renderer and finalizer
remain difficult unmatched frontiers; their retained near-matches receive no C
credit. Callback completeness, universal selector-storage types and hardware or
gameplay behavior remain separate open questions.
