# Menu row execution and result presentation

This connected path reconstructs nine C functions / 2,976 bytes. Each current
source compiles and links to the complete original extent, including its literal
pools and alignment; each has an actual compiled changed-source control. The
names describe the observed menu roles and remain provisional. These are static
and compiler-match findings, with no new runtime or gameplay evidence.

| ROM offset | Verified bytes | Source role |
| --- | ---: | --- |
| `0x3EB7C` | 896 | Execute the selected menu row |
| `0x3F3DC` | 364 | Choose and apply a primary result |
| `0x3F548` | 420 | Transfer and draw a primary result |
| `0x3F6EC` | 328 | Transfer and draw a choice result |
| `0x3F834` | 212 | Transfer and draw a secondary result |
| `0x401B8` | 512 | Prepare the footer and relation indicator |
| `0x40E84` | 128 | Apply a secondary result |
| `0x40F04` | 12 | Reset through the accepted choice-text producer |
| `0x40F94` | 104 | Stage result text with font/window setup |

## Connected behavior

The row executor adjusts the local actor needs through the accepted updater,
advances the world clock with a ROM-supplied delta, fills a background, changes
the window selection, clears the observed byte at menu state offset `+0x2C`,
sets its scroll target, and dispatches on the selected row code. Its generated
29-entry switch table is part of the exact C extent.

Codes 2–5 and 22 call the primary result path; codes 6–20 call the secondary
path. Codes 23–26 advance the selected 24-byte choice record using its row-entry
byte and call the choice presentation path. Other observed cases select notices,
text or the already accepted state-42 setup. The executor has no action for an
out-of-range code. Code names, full record counts and UI meaning are unresolved.

The primary handler reads a signed relation value, adds the selected code's
chance offset with byte narrowing, or selects the code-22 threshold branch. It
compares the observed narrowed bounded-RNG return with that probability. Its
success branch can update the scene request words at `+0x10/+0x14` for codes
3/4/5, then passes a signed result delta and signed text selector to the connected
consumers. The secondary handler performs the code-14 relation-flag handoff,
then applies the serialized result pair directly. RNG endpoint/distribution
semantics and result-table completeness are not established.

The primary and secondary text consumers share the observed 44-byte descriptor
stride. They queue background 2 transfers, alternate the resource buffer byte,
play the descriptor-selected cue and derive a text ID from the descriptor and
selected row. The primary consumer also uses its narrowed success argument to
select special offsets, write the observed actor-selection byte, and suppress
scrolling text for three row codes. The choice consumer tests flags at record
`+0x14` and selects descriptor resource/cue variants 6, 0 or 2; it then alternates
the same buffer byte and renders the text ID at record `+2`.

Text staging disables/enables the observed windows, selects background control,
font and line height, draws a bounded block through the accepted text API and
restores the background control. A null text pointer takes the accepted primary
menu setup path. The reset wrapper calls the accepted choice-text producer.
The background DMA, cue, relation-gauge and notice callees retain their separate
conversion status. The gauge at `0x40AB4` remains unconverted; the notice
producer at `0x27DD0` is now the accepted `resource_submit_scene` alias described
in [the queued handoff](SCENE_REQUEST_HANDOFF.md).

## Layout and boundaries

The result pair contains signed delta/text bytes, with a two-byte serialized
stride. Primary and secondary address calculations establish 10- and 30-byte
row strides. Their public views contain stride-only byte storage, and the
source computes the code-derived pair address explicitly. This avoids asserting
that a code is bounded by a nominal number of pair slots. Observed secondary
codes 6–20 would exceed a naive zero-based 15-element row declaration.

The literal secondary base `0x0807F68C` overlaps the previously named menu
control constants. Primary bases `0x0807F964` and `0x0807F970` are only twelve
bytes apart. These are address/stride views, with no claim that they are separate
complete arrays or that the leading bytes belong to a particular result row.
No extracted table contents are embedded in the source.

The descriptor view at `0x080612A4` is a partial role view of the same 44-byte
storage used by the actor greeting descriptors. The observed fields are a text
ID pointer at `+0`, resource words at `+4..+0x1C`, and a cue pointer at `+0x20`.
The choice record view is 24 bytes and shares storage with the accepted menu
text-record interface. The result-observer byte at game state `+0x20`, actor
selection at `+0x740`, and text-variant word at `+0x440` are separate partial
access views; they establish neither the complete game-state layout nor a bound
for incoming descriptor/choice indices.

The staging and reset CFG envelopes initially reported 102 and 10 bytes.
The verified extents are 104 and 12, including the two zero alignment bytes
before the next entries at `0x08040FFC` and `0x08040F10`. The primary text
consumer ends at `0x0803F6EC`, after 420 bytes. An earlier raw capture continued
into the following choice consumer; that capture was preserved, and its wider
range is excluded from the primary function boundary.

## Access and compiler evidence

The primary probability calculation performs two observed reads of the same
selected-code byte: `0x0803F3F8` supplies the comparison with code 22, and
`0x0803F400` supplies the value reduced by two for the chance-table offset. The
local `const volatile` byte pointer models those two physical reads. The shared
menu storage declaration is unchanged. This is an access view, without an
inference that an interrupt writes this byte, that asynchronous changes occur,
or that the original global declaration was volatile.

Within the original eight-body result batch, only the primary handler retains
a fixed C register binding: a short scene
request pointer in `r2`, confined to the selected-code/store scope and ending
before the result-consumer calls. No constrained values overlap in a register
or survive a call. The other seven functions use ordinary C without fixed
register bindings. Shared address helpers describe descriptor column and
serialized record offsets; they contain no original instruction-body assembly.

The source controls change the primary definition threshold, secondary code
condition, ordinary fallback text IDs, choice flag mask, line height, required
reset call and needs argument. Every compiled control is rejected. Public
current-source receipts and all useful failed attempts remain under the ignored
`reports/agents/display_audio/catalog-presentation/` directory; the ready receipt
is `menu-results-ready.json`. Earlier row-array models, redundant fixed-register
attempts and raw comparison files are retained as failed or superseded evidence.

The connected next targets are the unconverted relation gauge `0x40AB4/692`,
and secondary menu preparation `0x3F908/1112`. Their unsuccessful trials remain outside
C coverage. The connected notice handoff `0x27DD0` is reconstructed in the
queued scene-request path.

## Footer and relation indicator

The footer now owns all 512 bytes at `0x401B8`: 432 instruction bytes, 76 literal
bytes and four zero alignment bytes. It initializes seven observed menu object
slots, selects the indicator frame through the accepted signed relation and
percentage helpers, and draws caption 6222 at `(238, 96)` with style two and
tile value 442. It also initializes transient definitions four through seven,
loads the four observed palette blocks and restores the background control.

A small inline helper consumes the five real caption values in the order
`style, text, x, y, tile` and forwards them to the unchanged canonical draw API
in its existing order. This source form recovers the native argument lifetimes
without a new call, observation, binding or interface override. The local signed
16-bit position fields contain the representable constants 238 and 96. This is
one matching source spelling, without identifying the original source.
The footer retains R0/R1 constraints for the menu pointer and the numerator,
percentage and font arguments. The menu pointer ends at its field read; the
argument phases end at their consuming calls.

Normal and strict builds match the complete extent. Changing the caption lookup
from 6222 to 6223 produces a one-byte mismatch in each control. The actual menu
initializer and all thirteen distinct providers retain their current interfaces
and matching source proofs; the footer has 29 direct call sites. Allocation,
definition, text, resource and palette backing, later writers and runtime
populations remain conditional. This adds source ownership without a new
gameplay or complete-inventory claim.
