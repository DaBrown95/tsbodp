# Phase-row 22 map selection

Six connected C functions reproduce 2,216 bytes at their original USA/Europe
revision-0 ROM addresses, including literal pools and zero alignment. The names
are inferred from the coordinate tables, horizontal origin limits, input-driven
cursor movement, hovered-entry handling and preview palette sequence. They do
not establish recovered asset names or a complete gameplay interpretation.

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `scene_map_selection_initialize` | `0x08048DDC` | 432 |
| `scene_map_selection_step` | `0x08048F8C` | 844 |
| `scene_map_selection_initialize_objects` | `0x080492D8` | 300 |
| `scene_map_selection_select_entry` | `0x08049404` | 448 |
| `scene_map_selection_entry_under_cursor` | `0x08049638` | 156 |
| `scene_map_selection_shutdown` | `0x080496D4` | 36 |

The flat three-callback table at `0x0805797C` has row 22 at `base + 22 * 12`,
containing Thumb pointers `0x08048DDD`, `0x08048F8D` and `0x080496D5`.
The accepted scene-link menu action requests kind 22 through
`scene_submit_default_request(22)`. Its established request handoff removes the
queued-kind flag before indexing this table. This is evidence for the request
kind and phase-table row; it does not equate every scene, map or resource ID.

The initializer loads four background resources and their controls, stages the
resource palette and a sixteen-color alternate palette, selects one of four
mode values, creates the cursor and preview objects, then starts a transition.
The mode depends on header word six bit 1 and condition kind 3. The flat
conditional chain preserves the original flag reread after the condition call
and the second condition call on the observed alternative path. The body adds
no initialization of the palette-block handle or untouched object slots.

The update gives directional input priority over the two pressed-button tests.
It moves the cursor or scrolls the first three backgrounds, adjusts the retained
object position with the scroll, then tests the coordinate region under the
cursor. A new hovered entry configures the preview object and palette sequence;
a changed or absent entry clears the hover byte and conditionally removes the
block. Selecting an entry also creates and configures its text label. Shutdown
runs the reverse transition and clears palette jobs, the primary object list,
display state and the scene object slots.

## Representation and ABI evidence

Coordinate rows at `0x08084228` have two word fields and an eight-byte stride.
The cursor lookup scans indices 0 through 25. The new union describes only this
observed 208-byte prefix as `rows[26]` and `words[52]`. Its y-word access starts at
`words[1]` and uses a two-word stride, so it does not perform pointer arithmetic
outside the first row's y member. The full table capacity remains unestablished.
Other coordinate, limit, bound and palette tables retain unsized declarations.
The entry function still performs unchecked low-byte indexing; no new guard is
added for calls outside the observed direct caller domain.

The selected-entry function receives words and explicitly consumes each low
byte. Its first argument has the observed shift and zero-extension; its second
argument is tested through its low byte. The region lookup returns a word in
0 through 25 or 255. The update explicitly narrows that result and the original
collapse helper's result where the native caller does so.

The palette descriptor has a four-byte stride: resource byte at +0, bank byte
at +1 and count byte at +2. The mode's horizontal limits are two words at +0
and +4, named `first` and `last` from their comparison and origin-selection
roles. The existing frame views provide word positions at +18/+1C, state and
variant bytes at +4D/+4E, and the label's halfword delay at +5E. Only the observed
world bytes at +42C/+42E are given a separate partial access view. The request
word at RAM `0x03004334` has a distinct role name; it is not the established
`g_resource_scene_arg` root at `0x03004370`.

Pinned-compiler diagnostics establish the coordinate-row size/alignment 8/4,
the union prefix 208/4, and the bounds and palette-descriptor size/alignment 4/4.
This historical compiler gives these ordinary byte-field structures alignment
four. The world access view has a compiler size/alignment of `0x430`/4; the
observed fields end at +42E, followed by one padding byte in this declaration.
It is not a complete world-state model. Independent wrong-size, wrong-alignment,
wrong-world-offset and wrong-frame-delay controls fail compilation. The
background stride and system offsets +174/+188, and the frame field offsets,
are checked with the same pinned compiler rather than inferred from byte equality
alone.

Unsigned coordinate arithmetic and shifts preserve the native word patterns
before signed comparisons. Signed position additions and conversions retain
this compiler's observed behavior; arbitrary overflow inputs are not claimed to
be portable. Object creation results, optional object slots, row indices and
resource capacities remain unchecked where the original code leaves them so.
The hover and palette-block state may retain earlier values. No fabricated
bounds, clearing, extra reads or volatile RAM accesses are used.

## Boundaries and verification

`scene_map_selection_collapse_details` at `0x080495C4` remains an explicit
original provider covering 116 bytes through `0x08049638`. The retained semantic
C candidate differs in the three bytes selecting the first duration-address
scratch register. It receives no C credit. Independent helper entries at
`0x080492D8`, `0x08049404`, `0x080495C4` and `0x08049638` prevent treating the
whole update neighborhood as one function. Shutdown ends at `0x080496F8` before
the independent audio entry. Data inside literal pools is not classified as
instructions merely because a linear disassembler can decode it.

All six sources are ordinary C without register bindings. The only assembly
statement specifies original zero-filled alignment. Complete extent comparison,
allocated-section and Thumb-address checks, fresh changed-source controls,
current direct-provider and menu-caller proofs, and strict missing-declaration
diagnostics are retained privately. The initial 420-byte initializer, 848-byte
update, all intermediate mismatches and the 116-byte helper's failed lifetime
experiments remain available with raw comparisons. Static dispatch and type
findings, matching compiler output and runtime behavior remain separate claims;
no hardware or gameplay execution is asserted here.
