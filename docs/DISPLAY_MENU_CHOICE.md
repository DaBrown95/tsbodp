# Menu choice stamp and persistence lifecycle

Four connected Thumb extents add 172 matching C bytes. They follow the choice
record produced by the accepted menu choice-text stage, and the secondary
stage's explicit stamp-check call. The choice initializer remains unconverted;
its clock-copy/add dependency is reconstructed in [DISPLAY_TIME.md](DISPLAY_TIME.md).
Static layouts and compiler matching do not establish
runtime chronology, save-file compatibility or gameplay behavior.

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `display_menu_test_choice_stamp` | `0x0801817C` | 68 |
| `display_menu_save_choice` | `0x080181C0` | 48 |
| `display_menu_load_choice` | `0x080181F0` | 52 |
| `display_menu_choice_enabled` | `0x08018224` | 4 |

These extents end at the following table entries and `0x08018228`. Each includes
its alignment; all use ordinary C without register constraints or embedded
instruction bodies.

## Partial selection record and stamp comparison

The persistence/comparison functions observe eight bytes: enable, definition and
text-kind bytes at `+0/+1/+2`, an unknown byte at `+3`, a signed 16-bit component
at `+4` and signed byte components at `+6/+7`. This refines the accepted
choice-text stage's previously partial three-byte access view without changing
any existing offset. The subsequently reconstructed copy/add dependency writes
eight bytes beginning at `+4`, establishing an observed extent through `+11`.
The header now captures the observed twelve-byte view: it retains the existing
ordering fields at `+4/+6/+7` and adds signed second/tick bytes at `+8/+9` and an
uninterpreted halfword at `+10`. This does not prove the complete storage bound.

The comparison first clears the enable byte. It compares the stored components
lexicographically against a four-byte current stamp: a signed 16-bit component
at `+0`, signed byte at `+2`, and byte at `+3` interpreted through a signed-byte
cast. Equality and greater-than cases return 1; lesser cases return 0. The
current stamp's final byte retains its unsigned declaration and explicit signed
conversion, matching the actual byte load and narrowing sequence. The names
`major`, `minor` and `part` originally described ordering only. The connected
clock arithmetic now identifies their roles as day, hour and minute respectively,
from the signed day remainder and 24/60 carry radices. Valid input ranges and
runtime chronology remain unverified.

The unconverted secondary menu stage calls this comparator with selection
record `0x03003D68` and current stamp `0x03003958`, then removes selected actor
entries when the check fails. The accepted choice-text producer already passes
that same current-stamp address as the initializer's third argument. Thus the
negative offset of 1040 recorded in the preceding menu evidence connects shared
RAM storage to this four-byte stamp comparison. The former “resource effect”
inference was incorrect: `0x0801074C` copies an eight-byte clock record and adds
the hour/minute/second/tick offset. Its constant at `0x08D70D48` has hour 24 and
all other components zero, making this a next-day deadline operation. This is
static arithmetic evidence, not a runtime chronology claim.

## Persistence handoff

Saving a disabled record first assigns sentinel 24 to both the definition and
text-kind bytes. It then invokes the existing unconverted `frame_write_save_value`
dependency three times, in order: four bytes beginning at stamp `+4`, one byte
at definition `+1`, and one byte at text kind `+2`. The enable byte is not written
by this function.

Loading invokes `frame_load_save_value` with the same addresses, widths and
order. If both restored selector bytes differ from 24, it sets enable to 1.
When either equals 24, it leaves the enable byte in place; the source preserves
that observed behavior rather than inventing a reset. The four-byte accessor
returns the enable byte directly. The serializer bodies, storage format and
runtime read/write failures remain outside this batch's claims.

## Verification and remaining work

The canonical sources match their full linked extents with current headers.
Actual compiled controls change the comparator's enable reset from 0 to 1,
the save definition sentinel from 24 to 23, the load text-kind comparison from
24 to 23, and the accessor field from enable to definition. These reject with
1, 34, 1 and 1 differing bytes respectively. All five published menu background
and scrolling-text functions also match and reject their controls after the
same-layout record refinement.

Ignored raw comparisons, source edits, commands and include snapshots are
retained under `reports/agents/display_audio/catalog-presentation/`; ready
metadata is `menu-choice-lifecycle-ready.json`. Earlier useful failures remain
unchanged.

The direct initializer at `0x080180D4` has an exact-size 168-byte private semantic
candidate with six remaining scheduling bytes. It still receives no
source coverage. It observes the same enable and selector fields, chooses from
an eight-byte-stride definition table, adds an actor entry and invokes the
now-reconstructed clock-copy/add helper. Closing this initializer and the 1,112-byte
secondary stage would connect both lifecycle directions more fully.
