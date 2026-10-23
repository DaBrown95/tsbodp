# Contact activity definition six

This reconstructed path adds 20 matching C functions and 3,504 bytes at their
original entries. It follows definition row six through its initializer,
controller, five object factories, five installed object updates, input-pair
decision, cleanup and channel-volume helpers, and the connected audio notices.
The names describe observed roles; they do not identify the original game names.
Full-ROM equality, static ownership, compiler type/layout checks and the finite
instruction fixtures remain separate evidence.

| Matching function | ROM offset | Full extent |
| --- | ---: | ---: |
| scene_contact_activity_six_initialize | 2252C | 260 |
| scene_contact_activity_six_step | 22630 | 172 |
| scene_contact_activity_six_check_pair | 226DC | 320 |
| scene_contact_activity_six_create_first | 2281C | 144 |
| scene_contact_activity_six_create_second | 228AC | 148 |
| scene_contact_activity_six_create_gauge | 22940 | 132 |
| scene_contact_activity_six_step_second | 229C4 | 172 |
| scene_contact_activity_six_step_gauge | 22A70 | 176 |
| scene_contact_activity_six_create_primary | 22B20 | 292 |
| scene_contact_activity_six_step_primary | 22C44 | 728 |
| scene_contact_activity_six_create_secondary | 22F1C | 292 |
| scene_contact_activity_six_step_secondary | 23040 | 344 |
| scene_contact_activity_six_set_channel_pair_volume | 23198 | 48 |
| scene_contact_activity_six_step_first | 231C8 | 88 |
| scene_contact_activity_six_remove_finished | 23220 | 24 |
| audio_game_select_activity_callback | 412C8 | 24 |
| audio_game_set_channel_volume | 41328 | 12 |
| audio_game_get_channel_volume | 41334 | 12 |
| audio_game_default_activity_notice | 414C0 | 52 |
| audio_game_parameter_activity_notice | 414F4 | 64 |

Each complete extent includes its original literal pools and alignment. The
controller at 22630 ends at 226DC: its two zero bytes and final three literal
words belong to the 172-byte extent. The earlier 168-byte mapping was provisional.
The preceding 19 sources use ordinary C without register bindings. The primary
update uses four register constraints on actual values, described below.
Alignment directives only express the original zero section alignment.

## Dispatch and primary update

The 28-byte definition at 08059604 is row six of the table at 0805955C. Its first
two words are 0802252D and 08022631. The accepted secondary-activity initializer
and controller call these as `void(void)`. The accepted frame scheduler calls
object updates as `void(struct FrameObject *)`, passing the same object whose
callback is loaded from offset 136. Five factories install those exact callback
types without a function-pointer cast. Primary and secondary factories also
install the accepted `resource_object_before_step` at 08001AE0.

The primary constructor now installs the matching
[primary update](../src/scene/scene_contact_activity_six_step_primary.c) at
**22C44..22F1C, 728 bytes**: 700 instruction bytes and 28 literal-pool bytes,
with no terminal alignment bytes. Its canonical callback remains
`void(struct FrameObject *)`; the constructor changes only the same-address
provider name.

State zero handles completion, misses and the three amount thresholds. It
chooses the original primary/secondary animations and cues, updates score and
failure fields, and advances the variant state. States one and two wait for
the established completion flag; state two restores the saved sequence and
sample volumes. The final pending-update test selects the requested direction
variant before clearing that byte. Option indexing, pointers and backing keep
their existing preconditions; no guard or initialization is added.

Two short byte results use R0: the miss-path `events & 0xF1` value ends at its
byte store, and `events & 8` ends at its conversion to the separate word value.
Neither byte value crosses a call. The normalized word uses R5 through its
actual post-animation amount store, and the option-table pointer uses R9
through its real later lookups. Capturing the byte results after the AND
preserves the retained anonymous byte constant and later OR dataflow. This closes the retained five-byte mismatch without extra reads,
invented liveness, clobbers or instruction bodies. Failed attempts remain local.

The accepted `_call_via_r1` and `_call_via_r3` bridges are existing zero-C glue.
The four-byte R0/R2 transfer veneers at 0804CCF0/0804CCF8 remain original. No
bridge or copied instruction body is included in this batch's C byte count.
The generic actor interaction callback view is unchanged.

## Storage and types

The new [activity role header](../include/scene_contact_activity_six.h) gives an
observed 48-byte, alignment-four access prefix rooted through 030043F4. The
accepted scene initializer allocates 420 bytes and publishes the selected scene
and option. The prefix uses the following actual fields; complete state storage
and other row-specific views remain outside this claim.

| Offset | Access | Evidence |
| ---: | --- | --- |
| 0 | primary object pointer | initializer store |
| 12 / 14 | signed amount / unsigned failures halfwords | pair increment, gauge and primary consumer |
| 19 / 20 / 21 | option / common phase / common flags bytes | table access and accepted scene control |
| 24 / 28 / 32 / 36 | secondary / first / second / gauge pointers | initializer and moving-object selection |
| 40 | signed palette-timer halfword | decrement, sign reload and comparison with -1 |
| 42 | event byte | audio, pair and character coordination |
| 43 / 44 | saved sequence / sample volumes | initializer copies |

The common score at offset eight is separate from the amount at offset twelve.
The already matching score provider modifies that common score, result and flags.
The first moving object's byte 4C is used as a selection-exclusion marker; the
existing generic field name remains provisional.

The flags access view spans 216 bytes with alignment four within the 320-byte
object allocation. It reaches D1, D3 and D5 through the whole aligned object.
These factories clear D1 bits 2..3 and bit 5, retain bit 4, use D3 bit 4 for the
secondary character, and set D5 layer/palette fields. An initialized compiler
diagnostic produces D1=2C, D3=10 and D5=FC for contact=3, double=1, secondary=1,
layer=3 and palette=15. This local two-bit contact role does not widen or replace
the generic actor's three-bit field view. The full matching base object remains
312 bytes/alignment four; the 320-byte allocation is a separate fact.

The second object's word at 58 is copied from the audio notice's parameter.
Its access prefix is 92 bytes/alignment four. No duration or timestamp unit is
inferred. Primary appearance bytes at 03003970 and the secondary record at
0805A6B8 provide group at zero and variant at two. Under the pinned compiler
their ordinary aggregate is four bytes/alignment four, consistent with both
word-aligned roots; the three accessed bytes do not imply a packed structure.

The options at 0805367C have a 12-byte stride: signed speed word at zero,
threshold bytes at 4..7, reward at 8 and sequence at 9. Five records are observed
before the following palette-range data at 080536B8. First, second and gauge
animation prefixes have four, two and three 16-byte records respectively.
Palette pointer roots 08053760, 08053764 and 08053768 are three distinct arguments;
combining them into one invented array changed the original producer lifetimes.
Unchecked option/appearance selectors and complete capacities remain uncertain.

## Input and moving objects

The first and second factories create subtype ranges 0..3 and 0..1 through the
accepted RNG. Both use actual velocity Y at offset 2C; an earlier X-field source
had a one-byte mismatch and was rejected. Their coordinates start at 187/160
and 213/161 pixels. The first selection interval is the unsigned word range
24..72 pixels, with the upper endpoint excluded; the second is 25..73. A selected
object leaving below its lower threshold clears its slot. Passing the second
object also signals a miss, mutes channels zero and one when needed, selects the
failure palette and starts a six-step palette timer. An object at signed Y<=0
is marked for removal through flag two.

The pair decision requires both selected slots, a held direction corresponding
to first subtype, and pressed A/B corresponding to second subtype. Correct input
restores the channel pair to 64, selects the success palette, sets both object
flags and increments the signed amount halfword. The reward is doubled only
inside the strict first-Y interval 42..54 pixels. Incorrect input signals the
failure cue/palette and mutes the pair. Both outcomes mark the objects' byte 4C,
clear the selected slots and restart the palette timer. A genuine guard value
and a separately consumed button mask recovered the original compiler phases;
no register annotations or extra reads were added.

The gauge scales the amount against one of three option thresholds. The final
comparison uses **previous frame at DA**, distinct from current frame at DB.
Confusing those fields caused a retained one-byte mismatch. The secondary
character uses amount milestones 4, 7 and 13, event masks 0x20/0x40/0x80, actual pending
updates and the accepted animation/variant providers. Fresh global and object
loads after opaque calls are preserved.

## Audio handoff

The [audio access header](../include/audio_game_activity.h) preserves the
accepted SDK's `void(int,int)` callback, unsigned-word channel arguments and
unsigned-word volume result. The getter's signed-byte load is converted to that
existing unsigned return type. The new notice view uses a parameter word at
03007360 and the existing pacing/sequence/volatile flag bytes at offsets 4..6;
it is an eight-byte alignment-four access view at the same physical storage as
the older byte control view. Neither view claims the complete original object.

The callback selector reads the observed two-entry prefix at 0807FA84. Its words
are 080414C1 and 080414F5. The initializer selects index one through the matching
SDK installer. The accepted mark-effect producer passes kind three and its
byte effect operand as R1; the callback stores that parameter word and sets flag
four. Kinds two and six set flag two. The default callback also handles kind five
by setting flag sixteen. The controller consumes flag four to create both moving
objects while completion event sixteen is clear, resets the palette timer when
needed, checks the pair, then observes completion flag two. Discarded volatile
RMW reads are retained as emitted by the original source model.

The SDK callback global is 020025B4. Accepted mark, row-advance, jingle-finish and
tick producers, the installer and channel providers are included in the current
proof context. The word-return declarations are independently checked against
their actual accepted SDK headers under its GCC 3.0.2 profile. Omitting the
getter prototype still legacy-matches the 12-byte wrapper but is rejected by the
separate strict declaration diagnostic.

On the named uninterrupted initialization route, sequence volume 255 makes the
selector active. A previously set completion-notice flag `0x02` forces a sequence
start followed by its clear; a skipped start requires that flag already clear.
Stale completion is therefore excluded at that return. This does not establish
freshness of notice flag `0x04` or its parameter. Later callback kinds two and six
set notice flag `0x02`, and the controller sets event flag `0x10`. All inspected
activity event masks preserve existing flag `0x10` within one live allocation
under serialized named writers. The primary checks completion before a pending
miss, so that entry does not increment failures when both are set.

The five observed option records contain these thresholds:

| Option | First | Second | Third | Failures |
| ---: | ---: | ---: | ---: | ---: |
| 0 | 5 | 255 | 255 | 10 |
| 1 | 5 | 10 | 255 | 8 |
| 2 | 5 | 10 | 255 | 6 |
| 3 | 5 | 10 | 15 | 5 |
| 4 | 5 | 10 | 15 | 4 |

These records do not prove amount at most fifteen or failures capped by these
thresholds.
Animation state one skips the primary's threshold checks while pair input can
still increment amount; no animation-duration/input-rate bound is established.
Complete writers, IRQ interleaving, option validity, allocation and backing
remain open. These static facts add no compiler match or runtime observation.

## Verification limits and next targets

Every new body has a positive and a genuine changed-source control under both
the acceptance and strict declaration profiles. Current accepted providers and
actual indirect dispatchers are revalidated with complete literal header
closures, source/native ownership, relocated pools and alignment. Compiler
assertions and initialized bytes independently test access layouts; wrong
field widths, signs, callback arity and SDK types are rejected.

The retained finite proof checks 1,102 initialized cases across the preceding
19 bodies, including
signed/unsigned coordinate edges, option/subtype domains, input success/failure,
timer wrap, frame identity, channel bounds, callback kinds and injected post-call
state changes. There are 338 changed-source divergences and five interpreter or
precondition rejection cases. Caller-clobbered registers are poisoned and
callee-save/stack preservation is checked. The source branch model and native
interpreter share explicit provider outcomes; some matching children are opaque
hooks when called from a parent. Negative callback parameters and injected
effects are ABI/model cases beyond the concrete byte effect producer. These
fixtures do not execute the whole game, prove hardware interleaving or resolve
unchecked allocation, array and gameplay domains.

The primary update has fresh normal and strict full-extent matches and genuine
score-40-to-41 controls. All 15 current importers of its role header have fresh
normal/strict positives and changed-source controls. Actual definitions and
interfaces are checked separately. The new primary match adds no runtime cases
to the retained 19-body fixture set. Complete capacities, later writers and
original structure names remain provisional; matching this path does not close
the game's remaining executable ownership.
