# Window coordinate updates

The frame-loop window path has matching C through both coordinate records of
each window. Its four new complete extents total 240 bytes, including pools and
alignment:

| Function | ROM offset | Instructions | Literals | Alignment | Extent |
| --- | --- | ---: | ---: | ---: | ---: |
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
directives account for the ten alignment bytes in the table.

All ten connected definitions, including six existing callers and storage
services, match and reject their genuine changed-source controls. Actual
definition/type checks also reject incorrect argument widths, signedness,
arity, backing count, field offsets and division declarations. These establish
source and interface evidence, not runtime or complete writer/index domains.

The separate rectangle setter at `0x48A14` remains unconverted. Its best
four-scalar candidate emits 68 bytes with 15 differences. A tested two-point
argument hypothesis changes both that body and its existing caller, so the
four-scalar project declaration is retained. Other original code and the
remaining executable-inventory uncertainties stay explicit.
