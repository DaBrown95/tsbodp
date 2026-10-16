# Header attachment jobs

The complete local interval `0x08012E74..0x08013330` has nine matching C
functions / 1,212 extent bytes: tick (192), workers (400/272), initializer (4),
header check (52), choices (100), EC (8), begin (140) and dispatcher (44).
The already-owned mode lookup at `0x0802C750` contributes a separate 44 bytes.
The dispatcher ends at `0x08013330`; the old 88-byte estimate was incorrect.
The kind-49 worker owns its 44-entry local switch table. Literal pools and
original zero alignment are included; no register binding, added qualifier or
changed compiler profile supplies these matches.

Observed definition rows 63, 64, 65, 66, 67 and 75 pair the accepted header check and choices with these begin/dispatch callbacks. The allocator copies definition +12 to state F0 and +16 to F4. Begin has the existing word-return/state/object/word-kind contract; dispatch has word-return/state/object. F8 points to the matching tick at `0x08012E74` (table word `0x08012E75`). The distinct entry at `0x08013330` now has source as the initializer for rows 68/70/72; it is not this family's F8. EC `0x08013270` now has matching C source. This observed 149-row prefix is not a complete definition-table capacity.

Begin captures the first occupied record before allocation. On allocation success it writes the full incoming kind and calls the mode lookup even for kinds it subsequently rejects. Kind 49 stores byte +20 of the new record as 2 when mode is zero or the previous record byte is 1, and otherwise as 1. Kind 50 chooses attachment zero without this extra byte store. The allocator's own byte +20 initialization is distinct. Other kinds return zero after the allocation and kind write. The real attachment initializer follows the mode call; initializing it before that call produced a different register allocation. Position status and route return are ignored; the local point must be initialized by the reached position provider before the route reads it.

Worker 49 recognizes phases 0, 1, 39, 41 and 43. Its explicit phase 1 returns 2 directly and is needed to reproduce the original switch table. Worker 50 recognizes phases 0, 37 and 38; phase 1 invokes the original condition update and restores the object's before-step callback before returning 2. Both workers use the actual record's signed timer word as an unsigned switch selector and retain the original low-byte consumption of the timer helper. No running-byte override is invented.

The mode lookup returns the shared game byte +32 for ID zero. For a nonzero ID it reads the first byte of the eight-byte actor definition row indexed by subtype minus 32. Ordinary source fixtures require subtype at least 32 and a valid row; the body adds no guard and no complete table capacity is proved. Direction fixtures use observed word-table indices 0..7. Owner-kind fixtures use the six mapped definition rows. Bounds arithmetic must stay representable, and the signed actor timer must not be INT_MIN at an executed decrement. The separate numeric native diagnostic tests that wrap but makes no ordinary-C claim.

At the earlier five-body milestone, proofs included five normal and five strict positive/changed-source pairs, plus 17 accepted direct-provider normal pairs: 22 normal and five strict pairs, 108 native object/linked artifacts, and 59 current project headers. Forty-six physical assertions and eight API assignments pass; nine altered-header cases reject. Three actual omitted declarations retain identical legacy bytes and reject under strict diagnostics.

The finite packet records 2,032 source/original/compiled cases: 2,030 bounded initialized cases plus two synthetic point-status ABI-only cases whose hooks still write both output words. There are 922 actual source-control divergences. Two separate six-step begin/dispatch/completion chains execute the real nested helper bodies. Fifteen bodies execute in the model; six external providers have explicit bounded effects for point output, route status, need adjustment, audio and condition update. Eleven invalid-input/interpreter controls reject, including missing point output, unsupported service, missing provider and budget. A separate INT_MIN countdown diagnostic is numeric native-only. These are finite instruction/source fixtures, not hardware, scheduling, gameplay or complete generic caller semantics.


The recovered F8 tick coordinates one or two attachments. It preserves both
actual count queries, selects the header byte before unsigned subtraction of
18, and shares the real game-state root for relation storage and mode. Paired
phase 43 records request animation 18, enter 39 and select cue 150/149; either
phase 40 ends both records at 1. The single-record branch requests animation
50 for phase 43. Valid attachment backing and relation indices remain required.

The first source had two branch-local first-record variables: the second arm's
result used a different register, leaving three differences in 192 bytes.
One shared first-record local reproduces the native lifetime and all bytes.
No call, read or operation was added. Changing both animation-18 calls to 19
rejects two bytes. The four-byte initializer is independently installed by all
six observed rows and returns one; its return-zero control rejects one byte.
Both current actual-definition API checks and the full matching/control and
progress gates pass. Source ownership of this interval does not close writable
callbacks, scheduling, complete table capacity or gameplay.
