# Choice panel setup and exit

This partial scene lifecycle contains the 396-byte initializer, 124-byte shutdown
and 60-byte close request. The 616-byte step handler and 188-byte text drawer
remain original ROM services. The five original window services are separate
dependencies. Matching these three bodies does not reconstruct the complete
phase or establish scheduler, display hardware or gameplay behavior.

The phase-2 table stores initializer, step and shutdown callbacks at
0x08057994. Each callback consumes no incoming arguments. The close request is
called by the original step handler. Complete function comparisons include
literal pools and alignment; the only source assembly is a zero-alignment
directive, not an original instruction body.

The existing 12-byte actor scene request remains its sole declared owner. The
initializer interprets its first word through unsigned-character lvalues as
count, x, y and flags at byte offsets 0, 1, 2 and 3; active and object retain
their canonical fields at offsets 4 and 8. This does not introduce a second
incompatible struct alias. The dimensions expose only width and height at
0x03001f0c and 0x03001f0d. The target compiler gives this dimensions struct
size 4 and alignment 4; the bodies access only its first two bytes. That type
property does not prove the extent or ownership of surrounding storage. The
five text IDs are an observed ten-byte prefix, not evidence for the capacity
of unrelated surrounding storage.

The initializer increments the existing count; it does not clear that count.
Ordinary bounded lifecycle fixtures require a readable initialized five-ID
prefix, a count whose additions remain within the same prefix, and valid
resource/font/substitution data. Each looked-up string must be nonnull and
terminated within readable initialized storage. Width measurement must have
its actual font and substitution contracts. The unsigned width and line
arithmetic retains target-word wrap behavior; calls to the signed BIOS
remainder use a representable signed pixel count in defined-source fixtures.
No invented guard or initialization is added to the game source.

Each width is first narrowed by its real byte store, then capped by testing
that stored byte against 25. This differs from capping the full metric before
truncation. The old width byte is read before rounding the new metric. The
object-dependent path adds 32 before rounding and removes it before counting
wrapped lines. The available line width is 168 only for active == 1 with an
attached object, and otherwise 200. Height stores and coordinate byte stores
also retain their actual narrowing behavior.

Two initializer predicates use the attached-object word at 0x03005a08, not the
independent request selector at 0x03004358: the 32-pixel allowance and the
one-line height-5 override. Fixed-ROM literal decoding established this after
an earlier private source hypothesis used the wrong root. That hypothesis and
its raw failed comparisons remain preserved. The actual changed-source
control restores those two wrong predicates; object/selector crosscases must
separate them. The initial request selection store still uses 0x03004358.

When active == 1, the initialized object pointer, if nonnull, must designate a
writable compatible FrameObject for flag and position access. No allocation
is performed by these three bodies, and object presence is not inferred from
the independent request selector. The original step's four-player, 52-byte
input view and text-drawer progress contract remain outside recovered source
coverage. A full lifecycle cannot silently assume those original services
were modeled as reconstructed C.

Shutdown clears exactly the existing 12-byte request and ten-byte ID prefix,
disables the original windows, then either clears primary-object flags for
queued kind 1 or invokes the recorded transition/retention/effect/display
providers and installs the canonical default VBlank callback. Those external
providers keep their actual contracts and side effects. The close request
plays cue 80, conditionally clears object flag bit 0, starts the original
ten-tick window close, and stores full-word timer 10 and state 3.

A function byte match alone does not establish defined source domains,
complete provider behavior or gameplay. Physical/API checks, changed-source
controls and bounded finite results are separate evidence. Original-service
bodies and larger storage ownership remain outside recovered source coverage.
