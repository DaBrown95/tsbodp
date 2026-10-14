# Three-cell movement probe

`frame_probe_movement_cells` is the provisional name for the complete 312-byte
Thumb extent at `0x0802AA78..0x0802ABB0`. The accepted contact collector calls it
when velocity is nonzero and the captured flags intersect `0x10040`. It probes
three directions starting one below the direction byte, wrapping at eight.
The radius is `0x80000` when the probe direction equals the freshly loaded
direction byte and `0x40000` otherwise. It adds each velocity to the current
values at the captured next-position address, then converts the signed high
halves to a grid cell.

The initial flags word remains a snapshot across calls. A false low-byte grid
status returns immediately; the original converter writes only the first two
cell bytes on success and leaves them untouched on failure. Equal packed cells
skip both property queries. The occupied and marked bits, captured mode and
surface flags, and terrain mask 2 select the observed stopping paths. A blocked
probe calls the stop helper and applies contact 37. The original converter at
`0x08048AF8` remains explicit and receives no C credit from this caller match.

The point union is eight bytes with alignment four; its signed halfword at byte
six supplies the Y high half without a short-pointer alias to the point object.
The existing packed-cell object is four bytes with alignment four, its index at
zero, and the actor cell view places it at `0xC4`. Existing object and direction
views establish the accesses, not a new allocator capacity. Directions, pointers,
coordinate sums and capacities remain unchecked outside the observed domains.

The source matches with the pinned compiler and the supported per-function
`-O2 -mthumb-interwork -fno-rerun-loop-opt` profile, using the regular assembler.
This makes no claim about the historical compiler options. With the default
profile, the compiler's second loop pass hoists the flags shift into an extra
stack slot and emits 320 bytes. The retained dumps identify that real producer;
no filler, synthetic accesses, output changes or compiler changes are used.
Two genuine cell comparison values occupy R0 and R2 until their mask operations.
They are dead before either property call. Removing either constraint changes
the native output; their source values never span a call.

Fresh positive and changed-source controls cover the whole extent, literal pool
and native object. Strict declaration diagnostics and actual type/layout
mutations accompany the caller and accepted direct-provider proofs. The bounded
267-case instruction/model comparison includes low-byte conversion failures,
same-cell skipping, every observed direction, signed high halves, and provider
mutations of direction, position and flags. It uses explicit abstract hooks for
the called providers, poisons caller-saved registers and checks callee-save and
stack restoration. Its 20 control divergences and three interpreter failures are
finite model evidence; they do not establish gameplay, hardware behavior or
unbounded capacity and arithmetic domains.

The adjoining accepted `frame_apply_movement_contact` (220 bytes) and
`frame_refresh_movement_contacts` (88 bytes) read each signed coordinate's high
half as `(short)(coordinate >> 16)`. This replaces the earlier `short *` alias
of the two-word point with accesses through its actual `int` fields. The pinned
target has four-byte signed coordinates and two-byte signed halves; native
arithmetic right-shift and signed-half conversion behavior is checked separately.
This is a target-specific source refinement, not a portability claim. All four
expression changes preserve the full original extents, pools, existing source
controls, compiler profiles, callback signatures and memory ordering. They add
no C coverage. The bounded instruction checks include signed high-halfword
edges and real field reloads after abstract provider mutations; they do not
establish arbitrary pointer or arithmetic domains, hardware or gameplay.
