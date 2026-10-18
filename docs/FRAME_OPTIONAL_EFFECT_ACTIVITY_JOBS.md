# Optional effect activity jobs

Five connected callbacks/workers at `0x0803A660`, `0x0803A76C`,
`0x0803A808`, `0x0803A9D4`, and `0x0803AA24` recover 920 C bytes.
Their whole original extents include internal literals and the original zero
alignment: the 352-byte worker has a 350-byte symbol and two zero bytes; the
64-byte dispatcher has a 62-byte symbol and two zero bytes. All five are ordinary
C without register constraints. The source uses the pinned target compiler;
it does not establish original compiler or original source provenance.

The 148-row observed definition prefix has these begin/dispatch pointers in
rows 90, 109, and 110. Its existing E8 selector writes kind 53 or 45 first, may
write kind 12 second, and returns one. The EC callback `0x0803A9CC` (8 bytes)
already has matching C ownership as `frame_prepare_optional_attachment_kinds_12_45_53`.
The stored initializer `0x0803A968/4`, neighboring check `0x0803A96C/40`, and
F8 callback `0x0803AA64/4` now have source ownership. Their complete 48-byte
extents contain 44 instruction bytes and four source alignment bytes: the check
has a 38-byte function symbol and two trailing zero bytes; F8 has a two-byte
function symbol and two trailing zero bytes.

The initializer returns word one; its unused owner formal and result use remain
inferred compatible contracts. F8 is an empty void owner callback, so the
historical removal label does not prove destructor semantics. The check calls
the existing unsigned-byte attachment counter before testing owner byte96 for
exactly one. Its explicitly unrooted name records that these rows do not install
it. The existing family header declares all three forms. Real source controls
change the initializer result, owner-byte comparison, or an actual owner-byte
store in F8. Matching source and typed interfaces do not close incoming targets,
runtime populations or the observed table's capacity.

The dispatcher consumes the stored full-word kind. A genuine operation-kind
enum avoids this compiler's ASCII-weighted integer-switch cost heuristic;
the unsigned-word predecessor differs in nine bytes. Actual target diagnostics
show the enum is four bytes, alignment four, with unsigned-compatible word
representation. This enum is a recovered classification, not evidence of an
original enum declaration. Unknown word values take the unchanged zero-result
default. Begin and the three workers return words, including one while active
and two on completion. Callback field assignments retain their actual owner
and actor pointer tags.

Begin uses the real three-record allocator, stores the kind, and saves the
actor's position at owner offsets 104/108 **before** the position/route calls.
This differs from the separate position-cycle family's 100/104 view. The new
partial owner view is 228 bytes/alignment four inside the established 256-byte
state allocation; indicator 88, effect 100, and sample 224 are actual accesses.
Actor, effect and indicator views are partial within their observed allocations;
this does not establish arbitrary pointer validity or capacities.

Kind 12 counts with explicit unsigned-word increment followed by the pinned
target's signed conversion. Its forced running state is exactly one. Kind 45
treats any nonzero running byte as completion and uses the shared optional
consumer/indicator. Kind 53 routes, creates an effect, mirrors its actual OAM
bit for linked directions three/seven, then waits through the accepted needs
timer and routes back to the saved point before cleanup. Sample and saved-point
fields must have a prior producer before reached consuming phases; no new
initialization, guard or hidden traffic is introduced. The accepted timer's
signed decrement excludes INT_MIN from the defined-C finite domain.

Private initialized fixtures compare source effects, original bytes, compiled
bytes, ordered writes and actual changed-source controls. Fourteen accepted
providers execute as nested Thumb bodies. Twelve explicitly named provider
hooks supply chosen position/route, cue/stop, creation, adjustment, percentage,
random/cue and resource effects. Eighteen complete-output hook-result cases are
ignored-result/ABI diagnostics, not actual attachment-position failure outcomes.
Both local point words must be written before a reached route read; separate
omission observations are native-only diagnostics and make no defined-C claim.
Four connected begin/dispatch/worker chains have explicit external running or
completion-flag writes; scheduling is not modeled. Actual hardware, sample
playback, allocation failure behavior, route semantics, complete callback
reachability and gameplay remain unproved.

The 2,202 initialized cases include 28 accepted E8-selector context cases and
18 chosen-hook result cases; 235 actual source-control divergences are retained.
Eight memory/provider/interpreter rejections are separate from the three
native-only diagnostics (two incomplete local points and signed-timer INT_MIN).
Four connected chains contain 19 step comparisons, reported separately from
the initialized case total. The source-counter wrap cases remain defined for
the pinned target conversion; they do not broaden the signed-decrement domain.
A separate 48-case supplement starts effect OAM byte 211 clear or with chosen
preservation masks. Clear cases cover directions 0..7; preservation cases cover
three/seven, both with and without a created effect. It retains 48 actual
source-control divergences and 12 wrong-bit model divergences. This addresses
a recorded fixture blind spot: the main cases initially used byte 0x5C, where
both bits three and four were already set, so an incorrect OR-eight model
passed them. The actual source/native OR-sixteen was always correct. The
2,202-case model and its 235 divergences remain unchanged; the supplement
reuses the same producer-owned model and interpreter, without a new independent
model claim.

Linked directions in fixtures are 0..7. Any reached reverse-table access still
requires a readable indexed byte; broader table capacity is not established.
