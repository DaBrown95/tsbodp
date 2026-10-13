# Group selector object and second collision callback

Observed factory table slot 17 at `0x0804F2BC` contains `0x08047589`. Its
constructor, update and interaction callbacks form a connected matching C path
of 304 complete bytes:

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `frame_create_group_selector` | `0x08047588` | 204 |
| `frame_group_selector_step` | `0x08047654` | 24 |
| `frame_group_selector_interact` | `0x08011458` | 76 |

These are provisional behavior-based names. The constructor includes all twenty
literal bytes and ends at its update callback's independent prologue. The
interaction ends at the next independent prologue; it has no literal pool. No
asset bytes or original instruction bodies are embedded in the replacements.

The payload supplies a word ID, two signed halfword coordinates, a subtype byte
at `+8`, a cue byte at `+9`, an available byte at `+0xA`, and object/program group
bytes at `+0xB/+0xC`. The factory checks allocation failure and returns null
unchanged. On success it assigns the ID with halfword truncation, the subtype,
flags `0xE0405`, and the four payload values to object `+0x68..+0x6B`. It clears
the OAM graphics mode and double-size bit and sets OAM layer three. The palette
word table at `0x0807FC3C` and sixteen-byte animation-record table at `0x0807FC2C`
are indexed by the current subtype. The subtype is reloaded after the palette
handoff before selecting the animation record. Neither table's complete length
or permitted subtype domain is established; no bound is added.

The generic one-object tick is installed at object `+0x88`. It ignores state
zero and other values and delegates state one to the existing actor state
dispatcher, which updates the object's flags for that state. The factory sets
state zero through the existing state setter. The resource-group spawn walker
supplies group/entry owner bytes and the default resource before-step callback.

The primary collision slot at `+0xC8` is null; the second slot at `+0xCC` receives
the new interaction callback. This callback consumes both incoming objects. It
requires the other object's halfword ID to be zero, its state byte at `+0x4D` to
be sixteen, and this selector's available byte at `+0x6B` to equal one. It plays
the cue at `+0x6A`, sets animation frame one, activates the object/program groups
at `+0x68/+0x69`, writes zero to availability, and clears input. Thus the second
argument is material to this observed path; a one-object callback declaration
would omit its actual ID/state checks.

The already matched copied ARM collision dispatcher calls both collision slots
with `(a,b)` or `(b,a)`, selecting slot `+0xC8 + bound_index * 4`. The local view
therefore declares both slots with two `FrameObject *` arguments. It does not
change the generic actor header's provisional one-argument view. Whether the
required second bound actually occurs for a particular resource or gameplay
scene remains a runtime question.

All three functions match as ordinary C without register bindings or volatile
accesses. Their actual source controls change the constructor flags, tick state
and required availability value and reject one byte each. The matching
animation-record setter, animation-frame setter, palette handoff and input clear
are also freshly recompiled: four existing functions totaling 572 bytes, with
all four actual changed-source controls rejected. Together with the separate
actor/program trigger path, this connects allocation, both collision callback
slots, group activation, frame updates, actor state and audio/input coordination.

Raw expected and linked bytes, current source/header snapshots, real source
mutations, complete boundaries and failed initial literal-address evidence remain
under ignored `reports/agents/actor-interaction/`. Source matching and static
connections are separate from whole-ROM matching and runtime behavior. No actual
collision execution, input timing, table domain or gameplay completion is claimed.
Signed coordinate shifts and signed/unsigned byte narrowing preserve the pinned
target compiler's behavior without asserting portable ISO C behavior for every
possible input.
