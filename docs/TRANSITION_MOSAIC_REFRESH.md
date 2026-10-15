# Paired mosaic transitions and frame refresh

Milestone 125 reconstructs the paired kind-12 handlers as
`transition_mosaic_lightening_refresh` and `transition_mosaic_darkening_refresh`.
Their complete original spans are:

| ROM offset | Handler | Instruction bytes | Literal bytes | Zero alignment | Full span |
| --- | --- | ---: | ---: | ---: | ---: |
| `0x38EEC` | Lightening | 298 | 40 | 2 | 340 |
| `0x39040` | Darkening | 286 | 36 | 2 | 324 |
| **Total** | | **584** | **76** | **4** | **664** |

Normal and strict source builds match both full spans at their original addresses;
changing the blend-control source expression is rejected in both profiles.
The full-ROM build and its changed-source control pass separately. No assembly
glue is added.

## Connection and interfaces

The [record-selection shutdown](SCENE_RECORD_SELECTION_HANDOFFS.md) requests
transition kind 12. The original second-handler table slot at `0x0806A248`
contains Thumb target `0x08039041`, connecting that request to darkening. The
paired first-handler slot at `0x0806A210` contains Thumb target `0x08038EED`.
That first-handler connection is static table evidence; an executed kind-12
first-handler caller has not been observed. The unsigned-short parameters and
function names describe observed register use and
behaviour; they remain reconstructed names and types.

Both routines use the existing `FrameObject` and primary-list owner. Target
checks confirm object size 312, alignment four, next pointer at zero, list size
eight and first pointer at zero. Their flag accesses use the legal unsigned-character
representation at byte `0xD1`, mask `0x10`; it introduces no alternate object tag
or incompatible field view. The host finite harness maps its wider pointers
explicitly and makes no claim that its 344-byte host layout equals the target.

All five direct service providers already have matching C: refresh request,
background updates, palette jobs, OAM preparation and VBlank wait. Five actual full-provider definitions,
covering 752 already accepted C bytes, pass normal-profile API type checks;
five incompatible result declarations are rejected. The refresh result is an
unsigned byte and is ignored here. Strict checking of the inherited palette-job
provider stops at its undeclared nested palette-block service. That preserved
interface gap is outside this routine's strict body check and remains open.

## Behaviour and source evidence

Each routine configures blend targets, captures `DISPCNT` once, enables mosaic
on each initially enabled background, and sets mask `0x10` on the initial object
chain when object display was enabled. Darkening uses levels 0, 2, 4, 6, 8,
10, 12 and 14 for all four mosaic nibbles and the brightness halfword. Lightening
starts its two signed-short counters at 16 and subtracts two before each store,
using levels 14, 12, 10, 8, 6, 4, 2 and 0. Their actual values stay nonnegative
and representable, including all signed shifts. Each of the eight stages
requests refresh, updates backgrounds and palettes, prepares OAM, then waits for
two VBlanks: 48 service calls and 16 waits in total.

Cleanup tests the captured display state and walks the current list afresh.
It clears mask `0x10` on that final list; it does not restore each object's
previous bit. These bodies leave their background mosaic and register writes in place;
subsequent service effects remain separate.
Calls require initialized register halfwords, live list objects and finite valid
chains that remain stable during each walk. Service callbacks may change the
head between walks. Progress through the real wait service depends on the
interrupt and scheduling environment.

The local display snapshot is a volatile unsigned short. The original stores
and rereads that halfword in its stack slot. Darkening experiments with ordinary
scalar and aggregate forms instead retain it in registers; lightening adopts its
independently observed stack producer without repeating those experiments. This supports the accepted source
producer, without proving the original declaration or any asynchronous writer.
The unsigned word cleanup mask is computed only after the final nonnull-head
test. Failed source forms and their unmodified comparisons remain in local
ignored reports; no instruction transcription, output patch or fabricated
padding is used.

## Bounded execution evidence and limits

The darkening check covers 64 logical fixtures under three seeds: 32 stable chosen
service cases, 16 direct unsigned-short formal cases and 16 separately labelled
adversarial callback diagnostics. It compares the original, matching and actual
changed-source Thumb bodies with the actual C statements and a separate
statement model: 576 Thumb executions and 384 host-C executions. The source
control differs in 168 fixture/seed cases. Eight incorrect behaviour models
have witnesses, including stale-list cleanup, a fresh display-state read,
restoring old flag bits, an extra stage, one wait and swapped service order.

Twenty-three memory, ownership, ABI and unsupported-instruction failure guards
and ten reader guards pass. An independent read-only replay repeats the finite
results and seven claim-corruption controls. The darkening harness supplies exactly its
324-byte body and five explicit chosen services; it has no original-service
adapters or ROM fallback. The services share explicit hook contracts, so this is
not an independent service oracle, a proof of nested-provider definedness,
hardware timing, gameplay behaviour or exhaustive runtime targets.

Lightening is checked separately against the same 64 input fixtures under three
seeds, with its own original, positive and changed-source 340-byte bodies and a
fresh actual C harness. Its 576 Thumb and 384 host-C executions agree with the
explicit descending-counter statement model. The actual source control differs
in 168 fixture/seed cases. Nine wrong models have witnesses; storing level 16
before decrementing and using the ascending counterpart each differ in all 192
fixture/seed cases. Its own 23 fault guards use the 340-byte epilogue positions,
and its ten reader guards and an independent read-only replay with seven
claim-corruption controls pass. The earlier 324-byte evidence remains separately
scoped and unchanged. All chosen-service and hardware/gameplay limits above also
apply to this second harness.

Source coverage becomes 1,690 matching C functions and 239,296 C extent bytes,
with 500 glue bytes counted separately. This milestone adds two functions and
664 bytes. The [whole-ROM inventory](WHOLE_ROM_INVENTORY.md) remains a separate
static classification with an open denominator and the fixed historical
319,640-byte mapped-extent comparison.
