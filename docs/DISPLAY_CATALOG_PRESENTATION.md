# Catalog selection text presentation

The connected selection consumer at ROM `080217BC` now matches its complete
312-byte extent, including literal pools and zero alignment. Its direct
line-height setter at `0801AEBC` matches 12 bytes. The two-function batch adds
324 verified C bytes. Both use ordinary semantic C without register constraints
or embedded instruction bodies.

The selection consumer clears a background rectangle, selects a font and sets
line height to 12. For scene-request word `+8` values 0 through 4, it draws a name
from text index `504 + value` and a multiline description from `795 + value`.
For larger values, it uses `value - 5` as an index into the catalog context's
four-byte descriptor array. The first byte of the descriptor becomes the catalog
item argument. Byte value 255 suppresses the name/detail calls. The descriptor's
existing third-byte `type` field continues to select special descriptions inside
the already reconstructed catalog helpers; its first-byte role is newly observed
and remains named `unknown_00[0]` in the partial shared view.

The function reloads the scene-request word and descriptor byte after the name,
font and description calls. It then applies the observed unsigned-byte expression
`(item + 0x55) <= 0x17`, selecting byte values 171 through 194. That path reads one
byte at catalog-state base plus `0x41A`, uses it with text base `0x1789`, stages the
result in text field zero, and draws text 298 beneath the description. The source
uses an explicit integer address for this byte beyond the existing partial
context view. This establishes an observed access, not a complete catalog-state
layout or a new array bound. No complete descriptor count or validation of the
request's index has been inferred.

The helper `display_text_set_line_height(int)` stores the complete input word at
text raster state `+0x14`. Existing font selection initializes the same field from
the font line advance. Existing multiline drawing advances its signed Y position
by this field. The new header declares these operations without changing shared
structures, caller prototypes or previously accepted sources.

The consumer's canonical current-header source and a changed condition control
(`scene > 4` to `scene > 5`) are compiled independently; the control differs in
one byte. The setter's actual changed-source control adds one to the stored
height, and is rejected. Raw expected and actual bytes, commands, source hashes,
canonical snapshots, changed-source outputs and the earlier failed cached-item
and address-helper trials are preserved under the ignored
`reports/agents/display_audio/catalog-presentation/` path. The ready metadata is
`catalog-presentation-ready.json`.

The retained C rereads the descriptor fields directly. An earlier candidate
cached the first item byte and differed in 131 bytes even at the correct total
size; direct field expressions reproduce the observed loads and allocation.
This is compiler evidence, not a claim that these callbacks actually mutate a
particular field at runtime.

The scene request, catalog records and text IDs keep their established partial
views and provisional names. Static connection and exact linked bytes do not
establish runtime execution, gameplay behavior or complete subsystem coverage.
