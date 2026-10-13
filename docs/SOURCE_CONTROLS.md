# Matching-source rejection controls

Every accepted C function now has an individual compiled changed-source control.
The original nineteen-function, 676-byte baseline was revalidated at its pinned
addresses and full extents, then supplied with nineteen controls. Its C sources
and reference bytes are unchanged; this verification adds zero source coverage.

Controls alter a stored word, literal address, table index, blend mask, IRQ copy
count, interrupt mask, line shift, callback branch or counter increment. The
default VBlank control omits its frame update; the no-op control adds a volatile
acknowledge write. All nineteen changed sources compile and link, and all
nineteen differ from the fixed expected bytes. The controls are never executed
and are not used as accepted replacements.

Raw source/header snapshots, compiler/link commands, original bytes, candidate
bytes and comparison reports remain in ignored
`reports/audio-root/legacy-source-controls/`. The complete positive extents total
676 bytes; control differences include changed literal pools and shorter/longer
function extents, without masking either kind of difference.

The full matching build separately checks each individual C control, the
standalone and inline low-level glue controls, and its changed-source whole-ROM
control. Whole-ROM equality still includes explicit unconverted regions and
does not establish runtime behavior or a complete inventory of game code.
