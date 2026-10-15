# Connected scene startup, time flags and period audio

Four matching C functions recover 408 complete extent bytes, including their
literal pools and alignment: `scene_audio_for_period` at `0x08026A9C` (136),
`scene_prepare_load` at `0x08026B24` (128),
`scene_initialize_transient_slots` at `0x08026BC8` (76), and
`scene_check_initial_time_flags` at `0x08026C48` (68). Names and the new partial
views describe observed accesses; original names and full storage ownership are
unknown. This connects the accepted scene initializer to existing save loading,
clock comparison, transient tile allocation and audio selection. Whole-ROM
matching, these source extents, static mapping and gameplay are separate claims.

The period getter switches on the full unsigned argument. Cases zero through
three return the corresponding byte at offsets 8..11 of a twelve-byte scene
record; other values return zero. Its original scene-ID word, twelve-byte
stride and repeated literal pools remain intact. The previously recovered
period refresh contains the same selection expression inline. The scene
initializer, need-effect audio restoration and optional playback use this
getter. The original scene records remain explicit ROM data.

Load preparation first clears the selected-resource byte. Mode four and the
default initialize world state; modes five and six pass a full word read at
options-root offset 184 to the accepted buffer loader; mode seven skips those
calls. The loader's actual formal is unsigned word and its accepted body ignores
that argument. This read does not prove a runtime option value. Preparation then
clears flags at offset four of each observed 56-byte player record, according
to the existing unsigned player-count byte at input-root offset 48. It clears
scene flags and calls the recovered time predicate. No count clamp, allocation
bound or asynchronous counter guarantee has been added. The new player view
overlaps the established single-player scene-flags view. The 188-byte options
view shares the audio-options root; neither is a new independent object or a
complete ownership declaration.

The time predicate compares the current clock with clocks at world offsets
`0x71C` and `0x724`, using mask six for hour and minute. It sets scene flag one
only when the current value is strictly later than the first and strictly
earlier than the second. Equal endpoints are excluded; this body has no wrapping
interval rule. Day, seconds and ticks do not participate. The accepted clock
comparison determines signed component ordering.

Transient setup initializes bank zero, slot two when the unsigned scene ID is
at most fourteen, and slots three, six and seven unconditionally. Four original
sprite-resource roots are retained as address references. The matched allocation
provider receives its actual byte/byte/resource-pointer formals and returns an
unsigned halfword; this caller ignores that return. Tile availability, resource
validity, rendered output and scene reachability remain unchecked here.

Only the initializer's two actual helper names change to their canonical names
at identical addresses. Its source also includes the existing point definition
before transition declarations taking points by value. A fresh strict compile
exposed incomplete-type warnings in the earlier include order; adding the real
definition preserves every output byte. The shared scene header changes only
the matching two declarations. All 43 literal importers and six connected
providers are recompiled with their changed-source controls, without changing
other metadata or compiler profiles. The new helpers use ordinary C and a
natural zero-tail alignment directive; they contain no register bindings.

Private verification retains 53 normal source/control pairs, five strict pairs
and 232 native object/link artifacts. Twenty-five target layout checks and ten
API assignments include the four actual new definitions and six actual provider
definitions. Twelve wrong layout or API probes reject. Removing the time-predicate
declaration leaves the 128-byte legacy output identical but makes the strict
compiler reject it. The earlier missing-point-definition diagnostics and all
useful source mismatches remain private.

The bounded interpreter compares original, compiled C and changed-source bodies
in 673 initialized cases: 105 period-selection cases, nineteen transient-slot
cases, 252 time-flag cases and 297 preparation cases. The four source controls
diverge in 12, one, 36 and 297 cases respectively (346 total). Nine invalid or
incomplete model inputs are rejected. The fixture traces retain 5,031 paired nested comparisons of the original and
compiled clock-comparison and time-predicate providers, representing 10,062
native interpreter executions; save-world initialization, buffer loading and transient
allocation remain explicit abstract call hooks. Large selectors, signed-byte
clock boundaries and initialized caller domains are deliberately bounded model
inputs, not evidence of gameplay states or complete resource domains. The model
has no display, interrupt, audio hardware or gameplay execution. An initial
fixture-construction error is preserved and excluded from accepted evidence.
