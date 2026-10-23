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
| `scene_link_catalog_build` | `0x21658` | 356 |
| `scene_link_catalog_try_entry` | `0x218f4` | 216 |
| `scene_link_catalog_draw_quantity` | `0x21a7c` | 156 |
| `scene_link_catalog_draw_panel` | `0x21b9c` | 368 |
| `scene_link_catalog_shutdown` | `0x21d0c` | 64 |

The total is 2,988 bytes, including the compared literal pools and alignment.
These bodies use ordinary C with explicit alignment where needed; they add no
instruction-body assembly or low-level glue coverage. Each replacement has a
changed-source negative control and a separate strict declaration diagnostic.

The initializer selects the request phase, prepares background resources and
five quantity captions, then builds and draws the catalog objects. The
controller handles navigation, confirmation, request submission, link events
and quantity adjustment. Its helpers apply the observed actor-entry policy,
format the selected quantity and draw explanatory panels. The exit path selects
a transition and clears its display objects and jobs. The builder creates the
phase-specific details and five captions, and manages eight entry slots. The two
acceptance handlers at `0x219cc` and `0x21b18` remain explicit original providers.

## Access and compiler evidence

The common header records access views rather than complete ownership types:

- The request at `0x03004350` has selection, quantity and phase words at offsets
  8, 12 and 16.
- The world view at `0x03003950` exposes a value at offset 4, entry-list pointer at
  `0xf0`, collection pointer at `0x3f8`, and requested-kind byte at `0x73f`.
- The list uses the canonical `ConditionActorEntries`: count at zero, capacity
  at one and entry pointer at four. Its four-byte records expose `kind`,
  `value1` and `value2` at offsets zero, one and two. The former catalog `count`
  name referred to the capacity byte; this correction preserves every access.
- The owner slots at `0x030043b0` contain the first object, eight entry slots,
  five caption slots and two detail slots, spanning an observed 64 bytes. The
  existing canonical frame-object array also serves the matching clear routine,
  which clears slots zero through sixteen; that producer requires 68 bytes of
  backing without proving the complete allocation size or valid pointees.
- The input view at `0x030040e0` exposes the actor pointer and player bytes at
  offsets 48 and 49. Input arrays retain their canonical halfword accesses.
- Background control words at `0x08053644` and `0x08053648` use distinct C names
  for layers 0 and 1. Their shared data must not be rebound under one name.

Direct input-array expressions, the decrement-success navigation edge, and
repeated typed context-entry reads reproduce the controller's two request-root
lifetimes and address calculations. That controller repair requires no register
bindings or compiler profile changes. The pinned compiler's physical layout checks and actual
provider-definition assignments qualify the declared interfaces. They do not
identify unique original source types.

The matching world reset passes world `+0xDC` to `actor_entry_prepare`. That
producer installs list fourteen at world `+0x168` through the pointer at `+0xF0`.
The fixed fifteen definition capacities are thirteen eights, fifty and eight.
Their sum is 162; list fourteen's eight records occupy context
`+0x2FC..+0x31C`, or world `+0x3D8..+0x3F8`. Thus the builder's
eight reads fit this initialized list. This is a
producer-backed conditional bound, not an added native guard or proof of every
later pointer/capacity writer.

The pointer at world `+0x3F8` is the same producer's separate `0x84C`-byte
`ActorEntryCollection` allocation. The former byte access at
`collection + 0x785 + 4 * scene` is its `groups[scene].count`: groups start at
`0x784`, have four-byte stride and count at offset one. The canonical collection
types are shared with the actor-entry services through a focused header.
The permission reader reaches this access only after the idle-exclusion
predicate accepts scene 16, 17, 18, 21, 23, 24, 25, 39, 40, 46, 47 or 48.
Its special entry-141/scene-9 edge skips the collection read. Those accepted
indices fit fifty groups, provided the scene ID stays unchanged between its
predicate argument and subsequent native reload. Valid initialized allocation,
scene stability and later writers remain premises.

Object validity and supported callback domains remain provisional. On reached
typed entry reads, selection must be at least 5 and `selection - 5` must select
one of the eight initialized records. Native wrapping reads
for smaller selections do not establish a defined C array access. Panel kinds
0 through 4 have explicit text paths; the native default passes a null text
pointer and is not silently admitted to the ordinary string-provider domain.

The event ABI transports an eight-byte payload. Some controller event paths
leave bytes unwritten that their recorder kind does not consume. Those bytes
are preserved, without fabricated initialization; any seeded-stack transport
observations are separate native diagnostics. Full-ROM byte equality, bounded
initialized behavior checks, static connections and gameplay evidence are
separate claims. These owner and bound findings add no C extent or runtime
credit. Both acceptance handlers remain unconverted.

The two edited bodies retain all 1,616 extent bytes. All sixty affected source
contexts match under normal and strict compilation, with their genuine
changed-source controls rejected in both profiles. Five actual-definition
contexts verify 26 distinct layout facts; seven wrong pointer/layout cases
reject. The full-ROM, control, inventory and progress gates pass. Nine existing
alignment annotations receive only the controller's updated source hash.

## Builder and shared array lifetimes

The builder owns all 356 bytes at `0x21658`: 324 instruction bytes and 32
literal bytes in three pools. Its snapshot of the prepared secondary list's
entry pointer precedes the first constructor. The request phase selects the detail
objects; eight descending entry records then select a constructor, the empty
entry object, or the existing-owner subtype-317 arm. Five captions follow.
The existing-owner arm still requires a valid object; the source adds no null
guard or invented initialization.

`ActorEntryContext` now declares the producer's common inline backing as
`ConditionActorEntry storage[162]`, preserving offset `94`, 648 bytes and the
collection pointer at `31C`. The matching prepare routine assigns pointers as
`storage + offset`. Under that prepared pointer and continuing backing lifetime,
the builder reads elements 161 through 154 and its final unused decrement
reaches element 153 in the same array. An unrelated eight-element list does
not satisfy this contract. Later selector retargeting alone does not change
the already captured pointer.

The existing canonical `g_display_scene_frame_objects` array supplies the
separate owner cursors. Entry slots run from eight through one, ending at
unused slot zero. Caption slots run from thirteen through nine, ending at
unused slot eight. Under continuing common-array backing, both cursors stay
within that array; neither is
formed by decrementing before a separate structure member array.

GNU local register constraints name actual consumed native values: the saved
entry pointer and later mask use separate R9 phases, the entry cursor uses R4,
the entry-owner cursor R6 and the definition-table base R10. Short R0 phases
carry each owner base and the entry kind before calls; the existing-owner
flags arm consumes R1 without a call. Earlier prefix scratch values have died,
and the caption cursor reuses R4 after the entry phase. No R7 constraint,
extra observation, barrier or instruction body is added.

The useful private progression separates the causes: an early cursor removed
the saved-base/derived-cursor path; its real R4 phase restored the native homes;
the common owner array supplied defined cursor decrements; real R0 base
handoffs prevented folded offset literals. The remaining owner/index swap
came from LOCAL's constant-equivalence priority penalty, and the native R6
owner handoff preserves its actual call-spanning lifetime. The complete result
matches without patches or ignored bytes. The genuine subtype comparison
control differs in 42 bytes under normal and strict compilation. These source
results do not close later writers, invalid serialized state, valid object
populations or runtime/gameplay behavior.

The builder and all 41 importers of the refined actor-entry context pass normal
and strict compilation with their genuine changed-source controls. Seven
separate actual-definition contexts verify 37 distinct layout assertions;
ten wrong pointer or layout cases reject. The full-ROM, control, inventory and
progress gates pass.

## Secondary kinds and existing-owner inputs

With intact prepared aliases and no later writer, reset leaves the eight
secondary kinds as `142` followed by seven `255` sentinels. Definition 142 has
subtype 135, so this domain avoids the builder's subtype-317 existing-owner
arm. With valid constructor results and initializer phase 0, 1 or 3, the
builder makes sixteen constructor calls.
This is a conditional reset domain, not a complete list-writer population.

There is a named later insertion path. The
[need-effect factory](../src/frame/frame_create_need_effect_resource.c) can
preserve a payload kind of 33 or 34. Its installed selector writes action 7;
under the existing enabled, attachment, optional and choice-space conditions,
the [common choice builder](../src/display/build_need_effect_choices.c) can
append action 40. Selecting it and continuing the state/animation sequence
reaches [finish action](../src/display/finish_need_effect_action.c), which
inserts the object's kind into the secondary list through world `+0xF0`.
The live selected object, intact choice data and actual UI-result delivery
remain premises; this is not a natural-input trace.

A concrete retained payload now supplies an initial kind 33: the 16-byte
factory-five record at `0x08D75CA8`, selected by scene four, physical pack one,
selector zero. It becomes runtime object group three, slot zero; the two actual
payload offsets resolve to arena byte 1,440. Initial setup spawns groups zero
and one. Its initial program one can additionally spawn group three: command
33 at `0x08D75CE4` requires condition row four, column zero to be complete.
Completion kind 91 has a matching table row and writer, but a valid natural
history reaching that condition remains unproved.

This payload does not establish an action-40-ready object. It passes enabled
zero; allocation clears state byte `+0x63`, and both kind-33/34 initializers only
return one. With stable fields in scene four, the eligibility predicate is false
and the common choice builder does not append action 40. Action seven still
exists. A later writer to this same live state's `+0x62` or `+0x63`, or an
established change of world/history, is needed before that insertion route can
be claimed for this payload. Allocation, backing, later writers and actual UI
delivery remain premises; no natural runtime route or C coverage is added.

The accepted resource command 40 is a concrete possible enabling writer. It
loads the selected object's word at `+0x64`, then writes one at that pointer's
`+0x63`. For this need-effect object, the pointer is its effect state, so the
store can satisfy eligibility without changing enabled byte `+0x62`. The five
retained programs for this selected case contain only commands 0, 15, 33 and
43. An actual record or caller selecting resource command 40 for group three,
slot zero, or another writer to the same live state, remains unestablished.
The handler's existence does not prove this enabling event occurs.

A separate [collection-restoration path](SCENE_NEED_EFFECT_COLLECTION.md#restoration-and-enabled-state)
constructs each saved effect with constant enabled argument one. A backed
kind-33/34 record can therefore produce a fresh state with `+0x62 == 1`, under
successful allocation and valid placement premises. The stream contains six
record bytes and no enabled byte. This supplies another construction route;
a naturally produced kind-33/34 saved collection record remains unproved.
The snapshot requires nonzero `+0x62`, so setting only `+0x63` on the original
enabled-zero payload state does not make that state enter the snapshot.

Restoration returns each new object, but the scene-collection loop discards
that result. The object is published to primary list `0x030024F0`; a queued-16
primary exit can retain that list at `0x03002CA0` when flag `0x20000` is clear.
Neither operation publishes catalog owner slot two at `0x030043B8`. Placement
toggles the object's linked byte `+0x83`; it does not publish that owner slot.
The known kind-14/17/23 clearing handoffs still apply when reached from this
restored scene. A valid retained primary object and a valid catalog owner
require separate identity and lifetime evidence.

After reset plus one successful kind-33 or kind-34 insertion, entry one selects
subtype 317 and owner slot two at `0x030043B8`. The builder reaches that slot
before any constructor for it; its 317 arm reads the old owner and clears its
flags. Earlier construction fills slots zero, fourteen and fifteen, and the
later entry-zero construction cannot establish slot two before this read.
The examined kind-14, kind-17 and kind-23 handoffs to catalog kind 16 call end
routines that clear all seventeen slots before begin. The examined kind-9
shutdown releases the primary list while leaving the owner words uncleared.
Neither supplies a live-owner guarantee for this case under the accepted
helpers' valid, disjoint backing premises.

A cleared or stale owner is a backing/lifetime outcome, not evidence of a new
executable target. No hardware fault or nonexecution claim follows. The next
needed evidence is a valid producer and interaction history for the original
payload or restored record, plus an actual owner-slot publisher and lifetime.
Other aliases, IRQ writes, serialized entries and incoming routes remain open.
No guard, new C match or runtime coverage is added here.

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
