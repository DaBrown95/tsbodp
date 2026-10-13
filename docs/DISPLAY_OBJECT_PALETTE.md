# Object palette lifecycle reconstruction

The connected object palette family now has six independently matching C
functions, totalling 352 bytes. They join the published need-effect appearance
updater, scene/map palette reset, fixed-bank initializer and alternate palette
transfer producer. Names and access views describe static evidence; no new
runtime or gameplay claim follows from these matches.

| Function | ROM entry | Verified extent |
| --- | --- | ---: |
| `frame_set_object_palette` | `0x08030168` | 92 |
| `frame_reset_object_palette_slots` | `0x080301C4` | 44 |
| `frame_set_subtype_object_palette` | `0x08030258` | 16 |
| `frame_release_object_palette` | `0x08030268` | 68 |
| `frame_count_free_object_palettes` | `0x080302B4` | 44 |
| `frame_find_object_palette_slot` | `0x080302E0` | 88 |

Each extent includes its original literal pool and alignment. These are Thumb
functions executing at their ROM addresses; none uses a copied RAM execution
address. Their C algorithms use no register bindings or instruction bodies.
The only assembly declarations specify the original zero-filled alignment.

## Shared state and connected callers

The literal state address is `0x03001E48`. The existing `FrameMapPaletteState`
view has a word at offset zero followed by sixteen eight-byte slots. Each slot
has an ID byte, another byte, a users byte, an unknown byte and a pointer to
palette source pointers. Reset clears 132 bytes and then sets all sixteen ID
bytes to `255`. This establishes the accessed reset span and row stride,
without asserting a complete inventory of adjacent RAM storage. The published
`g_frame_palette_slots` partial view shares this base: its users byte at row
`+6` is the same byte as the state's slot users field at `4 + row * 8 + 2`.

Scene initialization and scene/map resource loading call the reset. Their
previous `scene_stage_080301c4` name was an address-based placeholder, now
refined to `frame_reset_object_palette_slots` at the same address. The published
fixed-bank initializer defines banks 1–7; the new lookup and free count visit
banks 8–15. The published object-removal caller's `frame_cleanup_callbacks`
alias at `0x08030269` is now `frame_release_object_palette`. Actor creation and
saved scene-effect creation previously called `frame_install_actor_script` at
`0x08030259`; that alias now names the subtype palette wrapper. All three
retain their original addresses and argument representations. The resource
globals still carry their earlier `script` labels and byte-array declarations;
explicit pointer-sequence access casts record the callee's newly established
role without asserting a full resource-table extent. Local word inspection
finds consecutive ROM source pointers separated by 32-byte palette payloads,
supporting this role but not a complete table inventory. The need-effect updater's three special appearances call the new
setter, whose transfer calls the accepted alternate producer at `0x08011708`.

The lookup remembers the first free dynamic bank while continuing to search
occupied banks. It reuses an occupied bank when its first palette source pointer
matches the requested first pointer. The compiled single-iteration loop and
its unusual optimizer-generated continuation are preserved by a semantic
one-element comparison; this is not evidence that all palette frames match.
If neither a free bank nor a match exists, lookup returns `255`. The setter
preserves the original unchecked use of that result.

The setter assigns the object's four-bit display palette, writes the low bytes
of the object's halfword ID and subtype into the slot, increments the byte
users count, and records the source-pointer sequence. It indexes that sequence
with the state word and stages sixteen palette entries at `bank << 4`. The word
is named `frame` by its existing access view, but this batch does not establish
who advances it, a valid sequence length, or an animation timing contract.
The subtype wrapper advances the supplied pointer sequence by the object's
halfword at `+0x0A` before calling the setter; it does not load a second table.

Release tests object flag `0x08000000`, decrements a nonzero users byte, and
marks the bank free only when the count becomes zero and the bank lies in
8–15. It leaves the object's flag, the saved source pointer and the slot's
other bytes intact. The source uses a byte cursor starting at the state base
plus `bank * 8`, with ID at cursor `+4` and users at `+6`. This explicit access
view reproduces the direct byte store and address order without changing the
shared typed layout. Earlier typed assignments produced a larger extent;
those failed comparisons remain local.

## Verification evidence

Current public sources and header closure compile to their complete original
extents. Actual compiled source mutations reject for all six functions:
transfer count 16→15, first searched bank 8→7, reset size 132→128, subtype
sequence offset plus one, first counted bank 8→7, and release lower bound
7→6. They differ by 1, 3, 1, 12, 2 and 1 bytes respectively. The changed-source
subtype control also changes the extent from 16 to 20 bytes. The accepted
292-byte need-effect updater, 808-byte scene initializer, 140-byte object
removal, 600-byte actor constructor and 252-byte saved scene-effect constructor
were independently recompiled with their existing controls after the canonical
header refinement. Each existing caller mutation rejects with one differing
byte. The scene/map resource loader's reset alias and changed-source proof are
coordinated in the separate frame-path batch.

Raw positives, failed typed release variants and changed-source evidence are
retained under ignored `reports/agents/display_audio/interaction/`. Full-ROM
integration, mapping gates and publication are recorded separately by the
milestone build. The remaining palette-frame update producer and broader
resource ownership rules remain unconverted or uncertain.
