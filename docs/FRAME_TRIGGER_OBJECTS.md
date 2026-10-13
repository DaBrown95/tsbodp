# Actor and program trigger objects

The paired resource factory paths reconstruct seven complete C extents, totaling
980 bytes. Observed factory table slot 19 at `0x0804F2C4` points to
`0x08020CCD`; slot 4 at `0x0804F288` points to `0x080223C1`. These are entries
in the table rooted at `0x0804F278`, consumed by the already reconstructed
resource-group spawn walker. They do not establish a complete table inventory
or a proven gameplay name for either kind.

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `frame_create_actor_trigger` | `0x08020CCC` | 148 |
| `frame_trigger_actor_handoff` | `0x08020D60` | 204 |
| `frame_actor_trigger_step` | `0x08020E2C` | 172 |
| `frame_actor_trigger_interact` | `0x08020ED8` | 92 |
| `frame_create_program_trigger` | `0x080223C0` | 148 |
| `frame_program_trigger_step` | `0x08022454` | 160 |
| `frame_program_trigger_interact` | `0x080224F4` | 56 |

Each complete extent ends at the next independent prologue. The two state
callbacks include their original six-entry jump tables and the table-address
literal. The interaction at `0x08020ED8` contains an internal eight-byte literal
pool between its two state-setting routes. The handoff contains both its world
base and `0x42E` offset literals, plus two copies of the flag-clear mask. Zero
alignment at these boundaries remains explicit; no adjacent instructions or
unexplained filler are included in C coverage.

## Payload and collision callback contract

The shared header is a local access view, preserving the broader actor view.
The serialized payload supplies a word ID at `+0`, signed halfword coordinates
at `+4/+6`, byte width/height at `+8/+9`, an unsigned halfword duration at `+0xA`,
a kind byte at `+0xC`, and argument bytes at `+0xD/+0xE`. The actor slot uses
`+0xD` as its actor handoff mode. The program slot uses `+0xD/+0xE` as object and
program group selectors for `resource_activate_groups`. The payload view ends
at the last accessed byte; its complete serialized record length is unknown.

Both factories allocate through `frame_allocate_scene_object`, preserve the
word-to-halfword ID truncation, set flags to twelve, and convert coordinates to
16.16 words. They store duration multiplied by thirty at object `+0x64`. They
install a generic one-object update callback at `+0x88` and a two-object
interaction callback at `+0xC8`. Each installs one collision bound: `+0xAF` is
its count, signed byte coordinates occupy `+0xB0..+0xB3`, and its kind at `+0xB4`
is one. The factories store negative width/height for the first corners and
positive width/height for the second corners. The byte values are interpreted
as signed coordinates by the existing copied collision dispatcher. No shape,
allocation or payload bounds checks are added; these factories retain the
original unchecked allocation result.

The already matched 640-byte ARM collision dispatcher, copied to `0x03002A20`,
loads callback slot `+0xC8 + bound_index * 4` and invokes it with both objects,
reversing their order for the second object's callback. The new local callback
field therefore uses `(struct FrameObject *, struct FrameObject *)`. Neither
callback discards the incoming R1 contract: the actor trigger checks R1 object's
halfword ID and stores that object at trigger `+0x90`; the program trigger checks
its ID. The generic actor header's provisional one-argument declaration remains
unchanged. A complete game-wide callback type or exhaustive indirect target map
is not claimed.

## Interaction, countdown and actor state handoff

Both callbacks require the other object to have ID zero. The actor path also
requires bit zero in `g_input_pressed[g_input_config.local_player]`, using the
existing shared input base at `0x030040E0` and pressed array at `0x03004228`.
It stores the other object as its target before requesting trigger state five
for kind zero or state four for a nonzero kind. Both paths clear flag four after
the request. The program path performs the same state choice without this key
condition and without storing a target. Input bounds and press consumption are
not introduced.

State one sets flag two. States zero and two perform no work. State four loads
the current payload using the existing object owner/group bytes, performs the
handoff, copies duration to the signed timer at `+0x58`, and requests state three.
State five performs the handoff and requests state one. State three decrements
the timer; exactly minus one restores flag four and requests state zero. A zero
duration therefore completes on the next timer update. The observed arithmetic
and unchecked timer domains are preserved; names describe this static flow
rather than a measured time unit or proven gameplay trigger policy.

Actor handoff mode zero excludes variants 65, 67 and 68 and requires the shared
world byte at `+0x42E` to be zero. Mode one accepts only variants 67 and 68, using
the observed unsigned-byte difference test. Other full-word mode values perform
no work. Both accepted routes copy the trigger's two position words to the target
actor's position and next position, clear both velocity words and flag
`0x400000`, then enter actor state 42. Mode zero requests animation 37, variant
65, cue 28 and direction seven; mode one requests animation 38, variant 66, cue
30 and direction three. The already reconstructed state dispatcher routes state
42 to the 780-byte handler at `0x08007900`, whose variants 65 through 68 continue
this path through animation completion, movement and attachment updates. These
links provide coherent useful functionality without assigning an unsupported
original gameplay name.

## Compiler and evidence limits

Five replacements match as ordinary C without register bindings. The handoff
uses one genuine world-base pointer in R0, confined to the byte test before any
call, to preserve its separate world-base and large-offset literals. The actor
interaction keeps the genuine second object in R2 only through the target store,
before either state-setting call; it is not read after a call. Ordinary forms,
failed allocation variants and all raw full-extent comparisons remain in ignored
`reports/agents/actor-interaction/` reports. No volatile access, synthetic guard,
output patch or original instruction body is embedded in the claimed C.

Seven actual source mutations compile and reject: each factory's multiplier
thirty becomes twenty-nine; the actor handoff's cue 28 becomes 27; each timer
callback's restore flag four becomes eight; each interaction's zero-kind test
becomes one. Twelve existing connected functions totaling 2,608 bytes, including
the copied dispatcher, resource walker, actor state dispatcher and state 42,
are freshly recompiled with their actual changed-source controls. Current source
and literal header inputs, source-local header bundles, linked bytes, original
ROM addresses and complete extents are retained with those receipts.

Matching source, whole-ROM byte equality and static callback/data connections are
separate from runtime evidence. These comparisons do not establish actual
collision execution, hardware timing, input behavior or gameplay completion.
Negative coordinate shifts and byte narrowing retain the pinned target compiler's
behavior; portable ISO C behavior for arbitrary inputs is not asserted.
