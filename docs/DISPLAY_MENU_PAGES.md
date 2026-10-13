# Menu background and scrolling-text closure

Five connected complete Thumb extents add 1,112 matching C bytes. They close the
third menu stage called by the accepted initializer, the hint operation called
by both the accepted primary stage and this third stage, and the scrolling-text
renderer fed by the third stage. Names and layouts follow static accesses and
remain provisional.

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `display_menu_prepare_tertiary` | `0x0803FF60` | 156 |
| `display_menu_draw_scrolling_text` | `0x0803FFFC` | 292 |
| `display_menu_show_hint` | `0x08040120` | 152 |
| `display_menu_prepare_state_42` | `0x0803FEC4` | 156 |
| `display_menu_prepare_choice_text` | `0x0803FD60` | 356 |

Each extent includes its literal pools and alignment. The first three end at
`0x0803FFFC`, `0x08040120` and `0x080401B8`; the fourth ends at `0x0803FF60`.
The fifth ends at `0x0803FEC4`. All five use ordinary semantic C, without fixed
register bindings or embedded instruction bodies.

## Third stage and background handoff

The third stage sets request word `+10` to 1 and invokes the hint operation with
argument 1. It loads background 2 through the accepted DMA resource loader, with
palette 0, x 15 and y 0. The tile base is `1 + 182*(resource_shown & 1)`; the byte
at menu `+24` is then toggled with 1. This preserves the observed alternation
without asserting a complete buffering or asynchronous lifetime contract.

The 44-byte greeting descriptor's word `+4` supplies this background resource.
It is now typed as `secondary_background_resource`, followed by four unknown
bytes at `+8`. The previously established background pointer at `+0C`, text-ID
pointer at `+0` and cue fields at `+20/+25` retain their offsets. The name
identifies this second observed pointer role, without identifying the original
resource names or a complete descriptor-table bound. Earlier byte-cast views
folded the `+4` address into a different literal and failed; the typed field
matches naturally.

For definition 0, the stage requests state 0 for the object pointer stored at
`0x030040E0`, then state 45 and variant state 4 for the pointer loaded from that
object's word `+90`. It rereads the parent pointer and word after each callback.
This caller establishes those pointer uses, without turning the entire unknown
word into a universal child-field contract for all objects. The final call to
the scrolling-text renderer passes a null text pointer; the renderer's static
branch may replace it with a resource lookup. No validation absent from the
original control flow is introduced.

## Connected state-42 producer

The adjacent producer at `0x0803FEC4` writes byte 42 to actor-selection offset
`+740` in the same game-state storage and invokes the unconverted `0x08040AB4`
consumer with -10. A partial access view reuses the existing catalog-state
symbol at `0x03003950`; it does not imply a complete catalog or game-state size.
The callee's entry narrows the argument to a byte and makes signed and unsigned
interpretations of that byte, supporting the signed-byte request prototype.
The producer then performs the same alternating secondary-background load,
plays greeting cue-table word 0 and calls the scrolling-text renderer with a
null pointer. The state and delta meanings remain inferred; the callee body is
not reconstructed by this batch.

## Choice-text producer

The 356-byte producer selects greeting text ID 5 by default. Definition 7 uses
text ID 2241 when parameter 4, read through the accepted signed-byte parameter
reader at the social-probe address `0x030039E8`, is greater than 3 after unsigned
interpretation. The explicit cast retains the observed unsigned branch rather
than replacing it with a signed comparison.

It invokes the unconverted choice initializer at `0x080180D4` with the partial
selection record at `0x03003D68`, the definition narrowed to a byte, and output
address `0x03003958`. The source retains this output as an offset of -1040 from
the selection record's anchor. Static address arithmetic resolves the shared
storage location; this caller does not establish the output's complete layout,
length or callback meaning.

A nonzero byte result stages text based on the selection record's byte `+2`
plus 6025 into substitution field 1. It loads the greeting descriptor's
background pointer at `+1C`, alternates the existing tile banks, plays cue-table
word 6 and renders text ID plus byte 1 of the text-variant table. A zero result
loads the existing `+0C` background, plays cue word 2 and renders text ID plus
one plus the current row's code. A separate full-word local holds that loaded
byte and its increment before the ID addition; this natural source scope
preserves the reference's arithmetic scheduling.

The same 44-byte descriptor now types word `+1C` as
`choice_background_resource`, retaining twelve unknown bytes at `+10`. All
other offsets remain unchanged. The variant byte used by the preceding renderer
is now the first element of an unsized byte-table declaration, whose observed
second element is used here; neither use proves the table's complete bound.

## Hint resource and map read

A nonzero byte argument sets flag bit 0 on the scene-object slot at `+8`, loads
the hint resource at `0x08FB8CE4` into background 1 with tile base 407 and palette
14 at (1,3), and reads tile (3,3) from the returned map. The returned pointer's
first 16-bit word supplies the width; map entries begin four bytes later. The
low 16-bit tile return plus 407 is retained in menu word `+0`, and menu byte
`+28` becomes 1.

A zero argument clears the object's flag bit, fills a 17 by 10 rectangle at
(1,3) on background 1 with tile 572, and clears menu byte `+28`. The neutral
unconverted `display_read_map_tile` dependency at `0x0800DA08` remains explicit.
Its private semantic candidates have not matched its complete 24-byte extent;
they receive no source coverage. The hint caller establishes a 16-bit return
and four arguments, without a bound or clipping claim for arbitrary maps.

## Text layout and scroll extent

The renderer accepts a text pointer. A nonzero relation-record byte at game
state `+3A + 4*definition` replaces it with text selected from greeting text ID
5 plus the byte at `0x0807FA6C`. It selects font 3, color 0 and line height 12,
clears request words `+8/+0C`, and starts tile 258 at (16,32) with width 104. A
post-test loop calls the accepted text renderer, advances y by 12, retains the
returned tile position and increments the line count until the advanced text
pointer reaches a zero byte. Empty and null inputs retain the original access
behavior; this source does not invent guards.

The complete-word line count is converted to double and subtracts 5.0 before
conversion to an unsigned word. A signed interpretation of that stored word
then selects the branch: a nonnegative value gains 1, while a negative value
becomes zero. Thus the retained extent is based on the count minus four visible
line positions. The exact floating conversion and subtraction remain in the C
source, rather than being replaced by an algebraically shorter integer formula.
This is a static arithmetic finding, not a claim about page navigation or
visible gameplay.

The compiler-generated unsigned conversion adds `2^32` when its initial signed
conversion is negative. Raw helper inspection identifies `0x0804D49C` as the
addition entry and `0x0804D4CC` as the subtraction entry: the latter flips the
second operand's decoded sign before the shared addition core. The emitted
calls use those inferred identities, with signed conversion at `0x0804DC28`
and unsigned integer conversion at `0x0804CDC4`. The latter compares against
`2^31`, calls a signed conversion core and applies the high-bit bias when needed.
The final comparison reads the retained unsigned word through a signed cast;
these observed conversions do not establish a valid input range for arbitrary
text lengths or negative floating inputs. The helper bodies remain unconverted.

Finally, when request word `+8` equals the retained extent or the extent is
zero, the renderer clears flag bit 0 in object slot `+10` and sets it in slot
`+8`; otherwise it applies the opposite flags. The partial menu-object view now
names the observed `+10` pointer `scroll`; it does not establish the complete
object-list layout or the flags' broader gameplay meanings.

## Verification and remaining work

All five canonical sources match their complete linked extents. Actual source
controls change hint tile 407 to 406, the alternating tile stride 182 to 181,
and the double constant 5.0 to 4.0; the compiled results differ by 32, 1 and 1
bytes respectively. Changing the actor-selection byte from 42 to 41 also
differs in one byte. The choice producer's actual 2241-to-2240 control differs
in 136 bytes, including changed instruction layout. The accepted primary stage,
initializer, line renderer,
state-46 handler, rectangle copier, row producer and fallback indicator all
match and reject their existing controls after the same-layout header updates.

Raw expected and linked bytes, source edits, commands, header snapshots and
useful failed candidates remain under the ignored
`reports/agents/display_audio/catalog-presentation/` directory. The ready
metadata is `menu-pages-ready.json`. These matching and static-layout findings
are separate from whole-ROM integration and runtime/gameplay evidence.

The next connected targets are the secondary menu stage, choice restoration,
normal-row code and parameter readers, and the still unconverted tile reader.
The 112-byte primary indicator reader has a close private candidate, but its
remaining register/scheduling differences keep it outside coverage.
