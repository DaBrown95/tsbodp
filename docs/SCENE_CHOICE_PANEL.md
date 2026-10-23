# Choice panel setup, input and exit

The five matching choice-panel bodies total 1,384 bytes: the 396-byte
initializer, 616-byte step handler, 188-byte text drawer, 124-byte shutdown and
60-byte close request. The text drawer adds one C function and 188 extent bytes;
the step uses its canonical name at the same address. The shared owner
refinements add no separate C-byte credit. These matches do not reconstruct the
complete phase or establish scheduler, display hardware or gameplay behavior.

The phase-2 table stores initializer, step and shutdown callbacks at
0x08057994. Each callback consumes no incoming arguments. The step calls the
close request and retains full-word state, timer, parameter and selector
values. Complete function comparisons include literal pools and alignment;
the only source assembly is a zero-alignment directive, not an original
instruction body. The normal and strict step positives match the complete
616-byte span. Its changed-source control tests the wrong timer sentinel and
differs in both profiles.

The 12-byte actor scene request remains its sole declared owner. Its first
four bytes are explicit unsigned count, x, y and flags fields at offsets 0, 1,
2 and 3; active and the compatible FrameObject pointer retain offsets 4 and 8.
The choice macros now name those actual members. Current reconstructed
sources had no word consumer of the former unknown_00 field beyond the four
character-access macros. This observation does not establish the contracts
of every original ROM consumer. Other existing request overlays remain
outside this refinement's source-definedness claim.

The same canonical four-player input owner is shared through a small guarded
header. It has four 12-byte views with a FrameObject pointer at each view's
offset 0, player count at offset 48 and local player at offset 49; target size
and alignment are 52 and 4. The existing catalog-world definition is likewise
shared through one guarded owner header. Its requested-kind byte remains at
offset 1855 in the observed 1,856-byte, alignment-4 prefix. Neither extraction
creates a second struct owner or changes a provider's ABI. All existing source
bodies are preserved. The complete 165-function, 36,484-byte importer bridge
qualifies the shared owner changes with 330 normal roles: 324 fresh roles and
six reused roles from the three panel bodies. All 1,980 comparisons of six
native leaf artifacts retain their prior bytes, and every existing positive
and changed-source identity is preserved. The preprocessed owner-definition
and member-access changes are separately recorded. The old three panel bodies
also have fresh strict positive and changed-source checks under these same
headers. A separate read-only replay rechecked the complete importer bridge.

Every step entry captures the selected actor pointer from the initialized
four-slot input owner before dispatch or prelude calls. Thus local player must
be within 0..3 even in states that do not dereference the actor. State 4 reads
the captured actor's initialized state and variant bytes at offsets 77 and 78
through unsigned-character representation. It does not introduce an
incompatible FrameActorObject view or infer universal actor allocation
ownership. The actor bytes are consumed before the first prelude call; the
source has no later actor-byte consumer to test.

After the prelude, the source reads the player again for the pressed-input
table. The three tested halfword predicates retain their actual producer and
priority: confirm, cancel, then navigation. There is no intervening call along
the false branch chain. The minimum-zero navigation arm separately reads the
player for its byte argument, with no intervening provider call. Stable-input
fixtures can check these accesses; they do not establish asynchronous input
or IRQ stability. Ordinary navigation uses initialized counts 1..5. A zero
count makes the maximum argument wrap to UINT_MAX under the source's integer
conversions; any use beyond the chosen input-provider contract requires
separate classification.

The dimensions expose only width and height at 0x03001f0c and 0x03001f0d.
The target compiler gives this dimensions struct size 4 and alignment 4; the
bodies access only its first two bytes. That property does not prove the
extent or ownership of surrounding storage. The five text IDs are an observed
ten-byte prefix, not evidence for unrelated capacity.

The initializer increments the existing byte count; it does not clear it.
After scanning at most five IDs, the resulting count, modulo 256, must fit
the initialized five-ID prefix before iteration. This is a post-scan backing
condition, not an incoming-count-at-most-five rule: 255 plus one wraps to zero.
Resource/font/substitution data must satisfy the actual provider contracts.
Each looked-up string must be nonnull and terminated within readable
initialized storage. Unsigned width and line arithmetic retain target-word
wrap behavior; defined-source fixtures pass a representable signed pixel
count to the signed BIOS remainder. No guard or initialization is invented.

Each width is first narrowed by its byte store, then capped by testing that
stored byte against 25. This differs from capping the full metric before
truncation. The old width byte is read before rounding the new metric. The
object-dependent path adds 32 before rounding and removes it before counting
wrapped lines. Available line width is 168 only for active == 1 with an
attached object, and otherwise 200. Height and coordinate stores also retain
their actual narrowing. Byte coordinates and dimensions sum to at most 510,
so the step's geometry shifts fit the target signed-word range.

Two initializer predicates use the attached-object word at 0x03005a08, not
the independent request selector at 0x03004358: the 32-pixel allowance and
one-line height-5 override. Fixed-ROM literal decoding established this after
an earlier private source hypothesis used the wrong root. Its failed
comparisons remain preserved. The initializer control restores both wrong
predicates; object/selector crosscases distinguish them. The initial request
selection store still uses 0x03004358. When active == 1, a nonnull attached
object must be a writable compatible FrameObject for flag and position access.
These five bodies perform no allocation and do not infer object presence from
the independent selector.

State 1 and the close request store timer 10. States 2 and 3 use unsigned
predecrement and compare the new value against UINT_MAX. Ten direct countdown
calls leave zero; the eleventh changes zero to UINT_MAX and performs the
completion branch. The window provider's duration argument 10 is separate
from this direct-call count and does not establish scheduler or hardware
timing. State 2 conditionally sets object flag bit 0 and enters state 4. State
3 clears the selected display rectangle and submits the full resource-scene
argument. The close request plays cue 80, conditionally clears object flag
bit 0, starts the original window close and stores state 3.

Shutdown clears the existing 12-byte request and ten-byte ID prefix, disables
the original windows, then either clears primary-object flags for queued kind
1 or invokes the recorded transition/retention/effect/display providers and
installs the canonical default VBlank callback. Those providers retain their
actual contracts and effects.

Finite qualification is separate from the native/type producer. It covers
seven supplied C bodies totaling 1,260 bytes: the four panel bodies plus the
existing 64-byte queue context resource_submit_scene (32),
scene_submit_default_request (16) and scene_queued_request_kind (16). The
986 fixtures comprise 941 initialized bounded and 45 direct-formal
source-defined cases, each checked with three initialization seeds. The
qualification includes 36 direct lifecycle sequences, 16 wrong models and
actual changed-source witnesses for all seven bodies; the new step control
has 26 divergent cases per seed. It uses 26 explicit chosen external effects
and no original-native adapters. A separate writer-trapped full replay
rechecked these results without writes or process creation. These bounded
results do not reconstruct every font, heap, window or renderer provider.
Actual installed-artifact, full-ROM and publication gates remain separate
requirements.

## Text drawer and native counter lifetime

The [text drawer](../src/scene/scene_choice_panel_draw_text.c) owns
`0x08034A54..0x08034B10`: 166 instruction bytes, twenty literal bytes and two
alignment bytes. It uses the sole twelve-byte actor-request owner directly,
with no incompatible private request cast. The caller, font selector, resource
expander and line-drawing provider retain their actual separate interfaces.

The drawer captures X and Y from the request bytes, scales by eight and adds
eight. Active value one with an attached object adds 32 to X and changes width
from 200 to 168. Each entry selects font three, palette zero or three and fill
minus one. Palette three requires active zero and equality between the full
request selector word and the entry index. It expands the selected text ID,
captures its first byte, then increments the index even for empty text. Every
draw updates tile from the provider's return and adds twelve to Y. The actual text
pointer and word limit are passed by address; limit starts at `0x7FFFFFFF` once
for the whole traversal and is not reset for each string.

One GNU register variable describes the actual counter in callee-saved R4.
Its lifetime starts at `0x34A8A`, after coordinate setup and the optional object
branch. It supplies the palette comparison, text-ID offset, increment before
the first line draw and fresh count test, surviving the three provider calls.
All providers preserve R4, and no other live R4 value overlaps it. The ordinary
canonical source gives 188 bytes with nine Y/index R4/R5 differences. Keeping
the later-born counter in R4 leaves the earlier Y calculation in R0 and its
saved value in R5, matching the complete body. Binding Y instead coalesces its
earlier temporary and removes the native move; that failed form is retained.
These are measured source and compiler lifetimes, not recovered original
declarations or compiler identity.

The count is reloaded after provider calls. The five observed text IDs therefore
require a valid index on every iteration, not merely an initial count bound.
Strings, font/substitution storage, provider progress and representable line
coordinates remain preconditions. The source preserves the unchecked reads
and original loop behavior. No new runtime trace or finite gameplay population
is claimed. Full normal/strict comparisons and genuine Y-increment controls
qualify the complete extent, including its skipped internal alignment and pools.

The remaining original window targets are
scene_choice_panel_original_set_window at `0x48A14` and
scene_choice_panel_original_window_begin at `0x48724`.
The 152-byte [close-to-center service](DISPLAY_WINDOW_MOTION.md#closing-to-center)
at `0x487BC` now matches from the canonical window owner under its existing
scene_choice_panel_original_window_end interface. Configuration and disable
services are already owned by the canonical [window sources](DISPLAY_WINDOW_MOTION.md).
The remaining external contracts do not establish a complete lifecycle model.

A byte match, a type check and a bounded finite result answer different
questions. Larger storage ownership, universal source domains, actual hardware
timing and gameplay remain untested by this qualification.
