# Choice panel setup, input and exit

The four matching choice-panel bodies total 1,196 bytes: the 396-byte
initializer, 616-byte step handler, 124-byte shutdown and 60-byte close request.
The new source gain is the step handler alone, one function and 616 bytes.
The existing three bodies retain their source and native bytes. The shared
owner refinements add no C-byte credit. These matches do not reconstruct the
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
These four bodies perform no allocation and do not infer object presence from
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

The remaining original targets are the 188-byte
scene_choice_panel_draw_text_original body and five separate window services:
scene_choice_panel_original_configure_windows,
scene_choice_panel_original_set_window,
scene_choice_panel_original_window_begin,
scene_choice_panel_original_window_end and
scene_choice_panel_original_disable_windows. They retain zero recovered-C
credit here. Their effects are explicit external contracts, not reconstructed
instruction bodies or an implicit complete lifecycle model.

A byte match, a type check and a bounded finite result answer different
questions. Larger storage ownership, universal source domains, actual hardware
timing and gameplay remain untested by this qualification.
