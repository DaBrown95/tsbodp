# Record-selection update and actions

Six connected replacements cover 1,136 bytes, including their literal pools,
dispatch table and alignment. Names describe observed behaviour and remain
provisional.

| ROM offset | Function | Bytes |
| --- | --- | ---: |
| `0x25038` | Nine-state update | 708 |
| `0x252FC` | Confirm selected slot | 180 |
| `0x257CC` | Change selected slot | 68 |
| `0x25810` | Cancel selection | 24 |
| `0x25828` | Create four scene objects | 76 |
| `0x25874` | Draw a confirmation choice | 80 |

The update connects local input, object handoff, confirmation text, palette jobs,
audio cues and save-header/slot commits. A bounded nine-entry table supplies its
switch targets. The return-phase and countdown paths preserve unsigned wrap:
zero decrements to `UINT_MAX` and triggers the transition.

## State and interface evidence

The original initializer at `0x24E18` allocates sixteen zeroed bytes. Its first
word is the return phase; the next two four-byte groups hold observed occupied
and enabled slot flags. The last four bytes retain unknown names. The update
and original handoff helpers use the byte at allocation offset 13. This is a
phase-specific view of an allocation, not a complete type for every use of the
shared resource-pointer global.

The existing 24-byte `SceneRequest` owns the scene, parameter, phase and timer
words at offsets 8, 12, 16 and 20. The existing 52-byte input configuration view
supplies its local-player byte at offset 49. Slot changes call the horizontal
helper that reads the nonlocal pressed table, then reread the player's byte and
consume the low byte of the separate local pressed table. That distinction and
the byte read are preserved.

Confirming a load stores the selected save slot, suspends audio, reads the slot,
resumes audio and tests the low byte of validation. Selection is reloaded after
each call. Mode-one confirmation uses the allocation's enabled and occupied
flags. The two handoff helpers at `0x253B0` and `0x254A4` remain distinct original
dependencies; both consume a byte first argument and a word second argument.

## Matching evidence and limits

All six ordinary C bodies match under normal and strict compilation. Each has
a real changed-source control under both profiles. The controls change a
queued scene mode, input-direction mask, audio cue, object identifier,
confirmation colour or final default request. They each change an actual
output byte. Raw inputs, commands, compiler output and failed attempts are
retained locally.

The update's producer-order comparisons are retained: its first ordinary body
had the correct 708-byte extent with 24 differences. Grouping the cached-player
assignment inside its index expression restored native load/pool order.
Distinct read-value scopes removed five further differences; direct canonical
array expressions removed the remaining six. Merely narrowing a local value
to a halfword made no byte difference. The choice drawer computes its real
tile and pixel coordinates before text lookup, preserving their lifetimes
across that call. No fixed-register variables or original instruction bodies
are embedded in these replacements.

Finite execution evidence is qualified separately from compiler matching. Its
scope is the 708-byte update with declared boundary-service abstractions;
converted helper interiors are not silently included. It is not gameplay
coverage or a proof of all provider behaviours. Defined connected inputs require
a live sixteen-byte state, player indices 0–3, valid object slots, valid save
slot indices and the existing provider contracts.

The retained check uses 871 initialized fixtures across three seeds and six
separate sequences, with twenty chosen service abstractions. It compares the
supplied original Thumb extent, a statement model and a host surrogate of the
actual C body. The models share hooks and assumptions; they are corroboration,
not independent oracles. The changed final request diverges in 24 executions.
Nineteen execution guards and ten evidence-corruption controls also pass.

The initializer, panel drawer and handoff helpers remain explicit original ROM
regions. Held initializer and panel attempts earn no C credit. Background-map
and saved-clock owner refinements are separate pending work. No low-level glue
was added. The inventory and denominator limits in
[the whole-ROM survey](WHOLE_ROM_INVENTORY.md) still apply; the fixed historical
comparison remains 319,640 mapped extent bytes.
