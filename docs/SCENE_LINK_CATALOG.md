# Link catalog controller and display activity

Names describe inferred roles, not recovered original identifiers. The phase
callback table at ROM offset `0x5797c` connects row 16 to the initializer at
`0x20f34`, controller at `0x210e0`, and shutdown at `0x21d0c`. Static table
membership does not establish runtime callback selection or gameplay coverage.

The connected C replacements are:

| Function | ROM offset | Matching extent bytes |
| --- | --- | ---: |
| `scene_link_catalog_initialize` | `0x20f34` | 428 |
| `scene_link_catalog_step` | `0x210e0` | 1,400 |
| `scene_link_catalog_try_entry` | `0x218f4` | 216 |
| `scene_link_catalog_draw_quantity` | `0x21a7c` | 156 |
| `scene_link_catalog_draw_panel` | `0x21b9c` | 368 |
| `scene_link_catalog_shutdown` | `0x21d0c` | 64 |

The total is 2,632 bytes, including the compared literal pools and alignment.
These bodies use ordinary C with explicit alignment where needed; they add no
instruction-body assembly or low-level glue coverage. Each replacement has a
changed-source negative control and a separate strict declaration diagnostic.

The initializer selects the request phase, prepares background resources and
five quantity captions, then builds and draws the catalog objects. The
controller handles navigation, confirmation, request submission, link events
and quantity adjustment. Its helpers apply the observed actor-entry policy,
format the selected quantity and draw explanatory panels. The exit path selects
a transition and clears its display objects and jobs. The object builder at
`0x21658` and the two acceptance handlers at `0x219cc` and `0x21b18` remain
explicit original providers until separately matched and qualified.

## Access and compiler evidence

The common header records access views rather than complete ownership types:

- The request at `0x03004350` has selection, quantity and phase words at offsets
  8, 12 and 16.
- The world view at `0x03003950` exposes a value at offset 4, context pointer at
  `0xf0`, policy pointer at `0x3f8`, and requested-kind byte at `0x73f`.
- The context prefix has a count byte at offset 1 and a pointer to four-byte
  entries at offset 4. Known entry bytes are at offsets 0, 1 and 2.
- The owner slots at `0x030043b0` contain the first object, eight entry slots,
  five caption slots and two detail slots, spanning an observed 64 bytes.
- The input view at `0x030040e0` exposes the actor pointer and player bytes at
  offsets 48 and 49. Input arrays retain their canonical halfword accesses.
- Background control words at `0x08053644` and `0x08053648` use distinct C names
  for layers 0 and 1. Their shared data must not be rebound under one name.

Direct input-array expressions, the decrement-success navigation edge, and
repeated typed context-entry reads reproduce the controller's two request-root
lifetimes and address calculations. No register bindings or compiler profile
changes are required. The pinned compiler's physical layout checks and actual
provider-definition assignments qualify the declared interfaces. They do not
identify unique original source types.

Array capacity, object validity and supported callback domains remain
provisional. On reached typed entry reads, the initialized C fixtures require
selection at least 5 and a valid `selection - 5` element. Native wrapping reads
for smaller selections do not establish a defined C array access. Panel kinds
0 through 4 have explicit text paths; the native default passes a null text
pointer and is not silently admitted to the ordinary string-provider domain.

The event ABI transports an eight-byte payload. Some controller event paths
leave bytes unwritten that their recorder kind does not consume. Those bytes
are preserved, without fabricated initialization; any seeded-stack transport
observations are separate native diagnostics. Full-ROM byte equality, bounded
initialized behavior checks, static connections and gameplay evidence are
separate claims. No hardware or gameplay execution is established here.

## Explicit no-payload cancel event

The catalog controller's existing kind-11 cancel edge now selects an initialized
GNU empty-record member of the shared payload union immediately before its
recorder call. This expresses a no-payload variant for a recorder kind that
ignores payload data. It does not initialize the eight transport bytes or permit
reading the inactive byte member. Seven existing payload byte paths gain only
the shared `storage.` member path; all other source operations are unchanged.

The complete existing 1,400-byte span still matches. Actual initial compiler
output contains no memory clobber or value store at the empty-member assignment;
its unused address computation is removed. The emitted kind-11 call retains
`R1 <- [SP+8]` and `R2 <- [SP+12]`, matching the native setup at `0x080215FE`.
The existing link-flag source control remains 1,400 bytes and is rejected with
two differing bytes. The normal optimization/interworking profile is unchanged;
`-da` captures diagnostic output only, and the publication gate uses the literal
normal flags.

Strict checks retain the eight-byte/four-aligned payload, twelve-byte event
record, actual mode/input field geometry and by-value recorder API. All seventeen
import declarations and fifteen actual owned provider definitions pass; wrong
recorder-formal and input-offset fixtures are rejected. The two original accept
services remain explicit without recovered definitions. Other partial payloads,
existing representation casts, selection/input domains and runtime/gameplay
limits remain qualified. This repair adds no new function or C-byte ownership.
