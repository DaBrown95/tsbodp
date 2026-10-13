# View motion and resource-effect controller

`transition_step_view` at `0x0800E3A8` contributes 844 verified matching C bytes,
including its six-entry switch table, literal pools and zero tail alignment.
The accepted scene initializer and primary frame update now call its canonical
name at the same original address. Both callers have fresh byte proofs and
changed-source controls. This connects their per-view loop to the accepted
approach helper, variant-state provider, resource-group activator, point-copy
and subtraction operations, and audio sample-stop provider.

The controller reuses the established twelve-byte view slots at `0x030040E0`,
48-byte motion records at `0x030017D8` and 40-byte resource-effect records at
`0x030030B0`. These are access views inferred from address arithmetic and field
widths. They do not establish the number of records, complete state allocation
or validity of arbitrary incoming view indices. The one-byte sound handle at
`0x03003354` is passed to the existing audio stop operation; its ownership and
purpose during gameplay remain unknown.

Motion mode zero copies tracked positions or averages their signed high halves
with the saved positions when the interpolation byte equals one. The observed
masked deltas and threshold `0x1FFFF` select each coordinate independently.
Mode one performs no work. Mode two approaches the target and advances to mode
three on return value eight. Mode three decrements a halfword delay and, on
underflow to `0xFFFF`, captures a return target and selects mode four. Mode four
approaches that target and clears both motion and effect modes on completion.
These names describe static operations; camera behavior and timing are untested.

Mode five coordinates two resource-effect cases. Effect mode one approaches
its object's position, counts down a phase, restores saved velocity and variant
state when the object equals the current view, and activates the two resource
groups once. Effect mode three tests the ready byte and post-decrements the
signed counter at `+0x18`, captures and subtracts points, advances the phase,
negates the parameter at `+0x14` on alternating phases and applies its Y offset.
Expiration clears the effect mode, activates groups and stops the stored sound
handle. Unknown bytes and provisional parameter names remain explicit.

Five real register constraints recover the observed producer lifetimes. The
byte offset of the selected effect is retained in callee-saved `r9`. An inline
phase reader captures its actual halfword in `r0` before returning an ordinary
value. The return-to-tracking zero, counter pointer and parameter-address offset
use separate short `r0` scopes with no live bound value across a call. No
instruction body, empty assembly barrier or synthetic volatile access is used.
The only standalone assembly directive requests the observed zero alignment.

The final Y-coordinate match uses a sequenced capture of the actual tracked
object pointer and a by-value fixed-point union. Its complete word initializes
both halves before the signed high half is read. This is distinct from reading
uninitialized aggregate storage. It introduces no new public layout. Other
signed-high accesses retain the existing target-width cast view. Signed shifts,
subtraction, negation and multiplication rely on the pinned compiler's observed
output and do not prove portable C semantics for every numeric value. No new
bounds checks, arithmetic guards or initializers were added.

Useful failures from the earlier 89-byte discrepancy, the 12- and five-byte
frontiers and excluded pointer/union/helper alternatives remain in ignored
reports. The canonical source and its actual delta-mask mutation were compiled
and compared across the complete original extent. Full-ROM equality, these
static findings and runtime/gameplay behavior are separate claims. The view
mode setter at `0x0800E8B4` and projection/display handoff remain connected
unconverted targets.
