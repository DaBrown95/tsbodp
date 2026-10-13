# Primary menu rows and background copy

This connected batch reconstructs four complete Thumb extents, totaling 648
matching C bytes. It closes the primary menu stage called by the accepted menu
initializer and feeds the accepted row renderer, background motion and window
transfer paths. Names and field roles remain inferred from static evidence.

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `display_menu_prepare_primary` | `0x0803EEFC` | 188 |
| `display_copy_background_rectangle` | `0x0800D968` | 108 |
| `display_enable_window` | `0x0804886C` | 24 |
| `display_menu_populate_primary_rows` | `0x0803F118` | 328 |

The extents include their literal pools and alignment. The earlier primary-stage
inventory envelope ended two bytes early; the complete replacement ends at the
following `0x0803EFB8` entry. The rectangle copier ends at `0x0800D9D4`.

## Primary stage and window handoff

The 188-byte stage invokes the unconverted relation-resource loader, fills
background 0 with tile 60 and clears request word `+10`. It copies an 18 by 5
rectangle of the panel map retained by the initializer at menu word `+10`, from
(9,14) to (9,14) on background 1 with tile offset `0xD116`. It starts background
0 at a target y of `-7602176` in the existing signed fixed-point representation
(-116 pixels), clears request word `+8`, enables window 0 and disables window 1.

An existing choice other than 255 invokes an unconverted restore stage. The
catalog-state byte at `+3A + 4*definition` selects the remaining branch: nonzero
hides the hint, requests the unconverted notice operation with arguments 1 and
2, and plays cue 80; zero populates the primary rows, calls the accepted line
renderer and hides the hint. The notice-owner global is retained as `void *`
because this caller does not establish its layout.

Window enabling calls the accepted display-layer enable operation with an
indexed mask from the existing window mask table. It forms the counterpart to
the accepted disable operation. The accepted configuration and rectangle setters
feed the VBlank window-register commit. This caller establishes window indices
0 and 1, without establishing the mask table's complete storage bound.

## Rectangle copy

The nine-argument copier uses the existing partial map-state array at
`0x03002EF8`, whose observed records have a 108-byte stride and a destination
pointer at `+10`. The source map has a 16-bit width at `+0`, height at `+2` and
16-bit tile entries at `+4`. The destination row stride is 32 entries. Each copied
entry stores the low 16 bits of the source tile plus the caller's offset.

Rows run only when height is positive; each row's inner loop runs only when
width is positive. After each row the source width is read again and both
cursors advance to the next row. The source does not invent clipping, pointer
validation, dirty flags or a transfer queue. These access contracts and the
accepted source layout do not prove behavior for invalid input pointers.

One semantic local, the remaining row count, is bound to `r2`. Its lifetime is
the copy loop, which makes no calls. The grouped destination offset
`y*32 + x`, typed map-state pointer and separate row count preserve the observed
address calculations and loads. Ordinary variants with different lifetimes
failed and remain in the private evidence. No instruction body is embedded.

## Row selection

The 328-byte row producer first asks the unconverted actor-indicator reader for
a candidate. It rejects the value 255 and values matching menu bytes `+26` or
`+27`. If this candidate is valid and the current choice is 255, it retains the
definition as the record group, advances those two history bytes and looks up
the new choice. Only an invalid first candidate falls back to the second
unconverted indicator reader; a valid fallback uses record group 24. The bytes'
broader meanings and the choice table's full storage bound remain unresolved.

The producer then obtains the accepted low-need mask for the local need-state
address `0x03003A00` with threshold 255. When the low byte is nonzero and the
whole mask is not 8, it searches bits 0 through 7, excluding bit 3. The first
eligible bit supplies the parameter for row code 27; the other four rows become
code 29 with zero parameters. If no eligible bit is found, the existing rows
remain in place. The alternative branch obtains five code/parameter pairs from
two explicit unconverted readers. The signed `1 << row` expression is limited
to the observed indices 0 through 7; that spelling retains the original shift
calculation without extending its safe range.

Finally, row 1 being code 29 clears flag bit 0 in the second scene object;
otherwise it sets that bit. The first scene object's bit is always cleared.
The partial object-slot view at `0x030043B0` retains pointers at `+14` and `+18`
and uses the accepted frame-object flags at `+0C`. These names denote observed
slots, without claiming the complete scene-object structure.

The primary stage and row producer use ordinary C without register bindings.
Separate candidate scopes preserve the actual reloads. Earlier flat scopes,
loop forms and unsigned shift spellings failed; their raw comparisons remain
available. The unconverted indicator readers, normal-row readers, relation
loader, hint, restore and notice operations remain explicit dependencies.

## Shared field refinement and verification

The attachment record's unchanged unsigned word at `+4` is now named `kind`.
New upstream initialization writes a complete-word kind and dispatchers test
values 49 and 7, supporting this name without claiming a complete kind domain or
callback-table interpretation. The accepted record allocator, begin-31 and
dispatch-31 sources use the refined label. All three were independently
recompiled with the current header and their real changed-source controls.

Each new canonical source has an independent complete-extent comparison and a
real compiled control. Changing the primary choice sentinel differs in one
byte; adding one to a copied tile differs in 42 bytes; changing the window mask
index differs in 14 bytes; and excluding bit 2 instead of bit 3 differs in one
byte. The three attachment controls reject with 1, 52 and 1 differing bytes for
the allocator, begin and dispatcher respectively. The current menu initializer,
line renderer and three existing window producers also match and reject their
controls after the shared header additions.

Raw expected and linked bytes, compile commands, source hashes, header snapshots
and earlier useful failures are retained under the ignored
`reports/agents/display_audio/catalog-presentation/` directory. Ready metadata is
`primary-ready.json`. These compiler and static mapping results do not establish
runtime execution, gameplay behavior or a completely reconstructed menu system.
