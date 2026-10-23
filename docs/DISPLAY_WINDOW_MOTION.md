# Window coordinate updates

The frame-loop window path has matching C through both coordinate records of
each window. Eight connected source extents total 624 bytes, including pools and
alignment:

| Function | ROM offset | Instructions | Literals | Alignment | Extent |
| --- | --- | ---: | ---: | ---: | ---: |
| [Open from center](../src/display/begin_window_from_center.c) | `0x48724` | 142 | 8 | 2 | 152 |
| [Close to center](../src/display/begin_window_to_center.c) | `0x487BC` | 142 | 8 | 2 | 152 |
| [Set corner position](../src/display/set_window_corner_position_unrooted_48974.c) | `0x48974` | 32 | 4 | 0 | 36 |
| [Set corner velocity](../src/display/set_window_corner_velocity_unrooted_48998.c) | `0x48998` | 40 | 4 | 0 | 44 |
| [Step both windows](../src/display/step_windows.c) | `0x489C4` | 22 | 0 | 2 | 24 |
| [Disable window layers](../src/display/disable_window_layers.c) | `0x489DC` | 14 | 0 | 2 | 16 |
| [Configure masks](../src/display/configure_window_masks.c) | `0x489EC` | 34 | 4 | 2 | 40 |
| [Step coordinate records](../src/display/step_window_axes.c) | `0x48A58` | 148 | 8 | 4 | 160 |

The frame driver calls the updater for window indices zero and one. A record
with flag two set follows its target while its timer is positive, snaps to both
target coordinates on the last frame, clears that flag and decrements the
timer. With a zero timer it adds the two per-frame steps instead. An updated
record sets the owning window's commit flag. The existing VBlank reader then
publishes the integer coordinate halves.

The single canonical `WindowState` remains 60 bytes. Its two 28-byte records
start at offsets four and 32. Each record has halfword flags and duration at
offsets zero and two, current coordinate words at four and eight, step words at
12 and 16, and target words at 20 and 24. Current words retain the fixed-point
union view used by their signed integer halves. The existing starter, rectangle
setter and VBlank reader now access these declared array subobjects directly;
they no longer cast between incompatible structure views.

The updater's raw halfword count, promoted comparison value and saved countdown have
distinct native lifetimes. Its GNU register variables name actual consumed
flags, count, coordinate and pointer values. Explicit target capture preserves
the observed load order; the masked flag result is the value of a real store.
The sources contain no instruction bodies or output fixups. Zero alignment
directives account for the fourteen alignment bytes in the table.

The updater qualification covers ten connected definitions, including six
existing callers and storage services; each matches and rejects its genuine
changed-source control. Actual definition/type checks also reject incorrect
argument widths, signedness, arity, backing count, field offsets and division
declarations. These establish
source and interface evidence, not runtime or complete writer/index domains.

The separate rectangle setter at `0x48A14` remains unconverted. Its best
four-scalar candidate emits 68 bytes with 15 differences. A tested two-point
argument hypothesis changes both that body and its existing caller, so the
four-scalar project declaration is retained. Other original code and the
remaining executable-inventory uncertainties stay explicit.

## Opening from center

The [152-byte opening service](../src/display/begin_window_from_center.c) at
`0x48724` now has a C owner under its existing
`scene_choice_panel_original_window_begin(unsigned short)` interface. It reads
window one's four current coordinate words, computes signed midpoints, and
writes that center to both coordinate records of window zero. It publishes
the signed integer halves to the two window-zero coordinate registers, then
copies window one's corresponding coordinates to window zero's targets.
Each record receives the incoming duration and active flag two. The final
layer mask is `0x2000`.

The four target-coordinate reads follow the two MMIO halfword stores in native
order. Each is expressed through a volatile `int` lvalue of the same canonical
position member, preserving that existing word observation without adding a
read. The initial snapshots and later samples need not be equal if state
changes. This source qualifier does not establish the original declaration,
an IRQ writer, hardware timing or a bound on arbitrary coordinates. The same
array, backing and representable signed-arithmetic premises as the closing
service apply.

Normal and strict builds match all 152 bytes: 142 instruction bytes, eight
literal bytes and two zero-alignment bytes. Changing the final layer mask from
`0x2000` to `0x6000` rejects both complete comparisons. The actual choice-panel
step caller, layer provider and closing helper also pass normal/strict matching
and genuine controls. Separate actual-definition checks cover the opening
service, its caller and provider with 23 physical layout facts; five wrong
signature or layout cases reject. No runtime or complete writer population is
added.

## Closing to center

The 152-byte service at `0x487BC` now has a C owner under its existing
`scene_choice_panel_original_window_end(unsigned short)` interface. It captures
the four current coordinates of window one, computes each midpoint as signed
`(last-first)/2 + first`, and copies those coordinates into window zero. It
publishes the signed integer halves to the two window-zero coordinate registers,
then gives both corner records the midpoint targets, incoming duration and
active flag two. Its final call enables layer mask `0x6000`.

The source uses the existing two-element `WindowState` array and each record's
two-element current-coordinate array. Starting at window one makes
`source[-1]` the declared window-zero element. Both coordinate-array pointer
phases stay within their own arrays; no private point/corner structure view is
needed. The four coordinate captures precede the stores, and the second motion
record's address is introduced after the first record's updates. These real
value phases recover the native bytes without register bindings or instruction
assembly. Signed differences and midpoint sums must remain representable.

Normal and strict builds match all 152 bytes, including 142 instruction bytes,
eight literal bytes and two compiler-emitted zero alignment bytes. Changing the
real final layer mask from `0x6000` to `0x2000` rejects both comparisons by two
bytes. Separate actual-definition checks cover this helper, its existing close
caller and the layer provider; five wrong interface/layout cases reject. The
rectangle setter at `0x48A14` remains unconverted. These source services do not
establish complete window writers, input bounds, hardware timing or the full
choice-panel lifecycle.

The two independently bounded corner setters add 80 C extent bytes: 72
instruction bytes and eight literal bytes. Both use the existing 60-byte
window and 28-byte corner records. The position setter changes only the two
current words. The velocity setter writes both per-frame steps and sets active
flag two; it preserves the duration, targets and owning window's commit flag.
The updater commits active velocity changes when duration is zero. Defined
backing requires window and corner indices in 0..1, with no added bounds check.

Each setter passes complete normal/strict comparisons and a changed-source
control that increments the second stored value. Neither has an established
incoming caller; these matches add source ownership without runtime coverage.
Together with the existing starter and three services at `0x489C4..0x48A14`,
they complete source ownership of the local 208-byte span `0x48944..0x48A14`.
The following rectangle setter and wider caller/writer populations remain open.
