# Attachment job kind 71

Three connected ordinary C bodies reproduce 556 bytes at their original
addresses. Normal and strict positives match all bytes, including literal pools
and alignment. Each genuine changed-source control differs by one byte under
both profiles. No new low-level glue is introduced.

| Body | ROM offset | Instructions | Literals | Zero alignment | Full span |
| --- | ---: | ---: | ---: | ---: | ---: |
| State update | `0x34DB8` | 430 | 20 | 2 | 452 |
| Begin | `0x34FB8` | 72 | 0 | 0 | 72 |
| Dispatch | `0x35000` | 32 | 0 | 0 | 32 |

The compiler and linker confirm complete ownership of these spans. The bounded
original CFG separates 534 instruction bytes, 20 referenced literal bytes and
two observed zero alignment bytes. The alignment bytes are compared in place
and do not become instruction bytes.

The 36-byte definition row 100 at `0x08063C8C` supplies begin and dispatch at
fields 12 and 16. The existing installer copies them to state fields `0xF0` and
`0xF4`; the accepted status path calls the latter with owner and actor. Record
kind 71 is distinct from row index 100. Four other row callbacks remain original;
the callback at field 28 is the accepted optional-capacity check.

Begin stores the full incoming kind, obtains attachment zero's point and calls
the route service with mode zero and style one, then requests animation six.
The actual `MOVS R3,#0` at `0x08034FE8` supplies the route's fourth, word-sized
formal. The sibling kind-48 begin uses mode three. The ignored point-provider result
requires both local point words to be initialized before the route reads them.

The worker captures the actor's need state before dispatch. Running byte exactly
one forces cleanup. Phase zero either enters the low-need animation path or
clears the indicator before reading the signed parameter. A conditional center
call and a separate unconditional center call are both retained; there is no
kind-48 direction-word lookup. The normal path selects phase 80, animation 40,
countdown 90 and cue 34, retaining the returned sample handle.

Phase 80 selects adjustment-table row 12 across eight needs; definition byte 35
selects the multiplier-table entry. The non-10 parameter branch
updates the indicator, rereads the parameter and checks advancement and the need
threshold. The parameter-10 branch only decrements the signed countdown and
checks minus one. Starting at 90 selects cleanup after 91 direct phase-80 calls;
cleanup is a subsequent call, not a claimed frame duration. Phase eight observes
flag `0x400000`. Cleanup stops the sample and finishes any retained indicator.

Existing overlapping actor/state/work views remain conditional selector-specific
contracts, not a universal storage-owner proof. Reached pointers, need arrays,
rows and resources require initialized backing and valid lifetimes. Signed
countdown decrement excludes `INT_MIN`. An allocator-null indicator result is
outside the actual creator's defined completion domain. Dispatch retains the
unconditional lookup-result dereference. No source initialization or null guard
has been invented.

The 30 target layout facts pass. Deliberately wrong layout and API units reject.
The 20 existing full-provider type units are reused through exact source and
header identity; they were not recompiled for this batch. Provider type evidence
is separate from nested provider semantics and callback completeness. No new
runtime fixtures, hardware or gameplay checks have been executed for this batch.

The fresh full matching build and refreshed progress gates pass with 1,696
verified C functions covering 240,448 bytes, a gain of three functions and
556 bytes. All 16 MiB match the fixed reference ROM; the changed-source whole-ROM
control rejects. Separate assembly glue remains 500 bytes, and 16,536,268 ROM
bytes remain explicit unconverted regions.

The census moves two zero alignment bytes into compiler-owned extents while
retaining 270,054 qualified static instruction bytes and 323,784 mapped extent
bytes. The historical comparison stays 319,640 bytes. These quantities establish
no complete game-code denominator and add no inventory-derived C credit.

Further connected targets include definition row 99's dispatcher and substantial
state workers. The renderer and finalizer remain unmatched; their retained
ordinary-source attempts receive no C credit.
