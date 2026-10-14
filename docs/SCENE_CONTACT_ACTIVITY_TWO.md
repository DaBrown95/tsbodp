# Contact definition row two

The observed row-two definition has an initializer and controller at
`0x0800BEB8` and `0x0800BFC4`. Its two callback words are in the 28-byte
kind-20 definition record at `0x08059594`. Both have the specific
`void(void)` contract used by the accepted contact dispatcher. The following
connected replacements cover 14 functions and 2,540 C extent bytes. Their
names describe observed roles and remain provisional.

| Entry | Bytes | Role |
| --- | ---: | --- |
| `0x0800BEB8` | 268 | Initialize the backgrounds, seven row objects and controls |
| `0x0800BFC4` | 176 | Advance the two-control input handoff |
| `0x0800C074` | 108 | Create the primary control object |
| `0x0800C0E0` | 108 | Create the secondary control object |
| `0x0800C14C` | 192 | Create one row object and install its update |
| `0x0800C20C` | 188 | Run the row timer and animation phases |
| `0x0800C2C8` | 188 | Draw a row using its new position and resource choice |
| `0x0800C384` | 168 | Create the next idle event object |
| `0x0800C42C` | 764 | Move an event, reflect it and resolve a row result |
| `0x0800C728` | 96 | Reset the two control programs and shared event counter |
| `0x0800C788` | 108 | Launch the prior event and create the next one |
| `0x0800C7F4` | 44 | Finish an event after its animation completes |
| `0x0800C820` | 60 | Finish a successful row result |
| `0x0800C85C` | 72 | Draw the activity score |

The implementation is in
[scene_contact_activity_two.h](../include/scene_contact_activity_two.h),
[scene_contact_activity_two_access.h](../include/scene_contact_activity_two_access.h)
and the corresponding `src/scene/scene_contact_activity_two_*.c` files.
No existing callback interface is widened by this path.

## Connected transfers and boundaries

The row constructor installs `0x0800C20D` in the object callback field at
136. The transfer function installs `0x0800C42D` in the old event object,
then replaces the shared idle-event pointer with a newly created object.
An earlier private hypothesis confused that installed callback with
`0x0800C7F5`; the original transfer pool and failed hypothesis are retained.
The large event update installs `0x0800C821` for a successful row and
`0x0800C7F5` for a missed or boundary event. These are one-`FrameObject *`
callbacks, consistent with the accepted scheduler's `on_step(object)` call.

`0x0800C42C..0x0800C728` is one complete 764-byte extent, including its
internal literal pools. `0x0800C57C` is an internal loop label rather than a
new function. The completion callback has a 42-byte function symbol followed
by the original two zero alignment bytes; the distinct next entry is
`0x0800C820`. Source alignment remains explicit. No copied instruction body,
output patch, masked difference or changed reference is used.

The transfer uses the already accepted 12-byte `frame_set_position` at
`0x080014A4`. One private trial guessed a different address; its three
remaining call bytes and wrong symbol pin were preserved before the live
provider correction. This is a dependency correction, with no extra C credit.

## Access views and data evidence

The shared state is an observed 96-byte prefix inside the contact
initializer's 420-byte allocation. It contains the event counter halfword at
10, the local score halfword at 12, the selected-row halfword at 14, option
byte at 19 and flags byte at 21. Seven eight-byte entries begin at 24; the
primary, secondary and next-event pointers are at 80, 84 and 88, and the audio
handle is at 92. The initializer's descending loop and the event's bounded
row search establish the seven-entry producer domain. They do not establish
all valid external indexes or complete scene storage.

The control and row object views are 216-byte prefixes with alignment 4.
The existing common `FrameObject` and actor views have size 312 and alignment
4; the allocator reserves 320 bytes. These values describe distinct views
and allocation capacity. The two-bit contact field and double-size bit are
in byte `0xD1`; the layer and palette fields are in `0xD5`. The row constructor
also sets bit `0x20` in byte `0xD3` for rows above three. Compiler diagnostics
and physical mapping checks accompany the byte matches.

Seven 88-byte ROM rows begin at `0x0804F480`, immediately before the separate
60-byte resource prefix at `0x0804F6E8`. Each row has three eight-byte tile
positions and three distinct 16-byte animation records: successful result at
24, ready animation at 40, and unsuccessful result at 56. Their original
pointer roots are `0x0804F498`, `0x0804F4A8` and `0x0804F4B8`. The former
private source used record 56 for both result branches and differed in one
literal-pool byte. That failed source and raw comparison remain preserved;
the successful branch now uses the evidenced record 24.

The 60-byte resource view has a background pointer at zero, animation records
at 4, 20 and 36, palette pointer at 52, and byte fields at 56, 57 and 58.
The initializer and bounded random choices support the observed three-record
prefix. The rate view is a three-by-three byte prefix at `0x0804F79C`, indexed
by the row's choice and the event subtype. The four-byte score records at
`0x0804F464` provide initial and reward bytes at zero and one. Wider storage,
arbitrary options, malformed subtypes and arbitrary direction values remain
unestablished; the extern declarations do not invent complete capacities.

The common score provider writes the contact amount at offset 8 and the
result/flags fields. This is separate from the local activity score at 12,
which is decremented for a boundary event and read by the score drawer.
The drawer's 16-byte local numeric buffer corresponds to the original
20-byte stack frame with the outgoing fifth argument at its bottom. This is
available output storage, not proof of the original source array declaration
or every formatter's capacity.

## Source and compiler evidence

All 14 bodies use ordinary C without fixed register bindings. A genuine
four-byte, alignment-4 control-word record snapshots the existing flags word
at object offset 12 and commits it after modifying its bits. It has exactly
one unsigned-word member at offset zero and no padding or fabricated union.
Its aggregate store conservatively preserves the original pointer-slot
reloads in the controller, reset and transfer. Every snapshot is initialized
before use. Direct scalar, opaque-pointer and full-width-bitfield trials are
retained as unsuccessful alternatives; no volatile qualifier or unused
initialization was introduced.

The event update calculates real lower and upper points in two phases: a
16-pixel row box followed by its eight-pixel margin. Each component is written
before its first source read. The compiler reproduces incoming `R2`/`R3`
stack snapshots from those aggregate lifetimes, but these are not extra C
parameters. There is no copy or read of an uninitialized aggregate. Separate
coordinate and byte-rate pointer scopes reproduce the actual address
lifetimes, and the reward is loaded before its signed division. Field-address
arithmetic uses the pinned 32-bit target word to address the actual integer
coordinate fields, without treating separate struct members as an array.

The fixed-product provider has the accepted signed-word contract. The signed
runtime division helper remains an explicit original dependency with zero
new C credit. Coordinate addition and reflection expressions use explicit
word wrapping where required by the original arithmetic. The row update's
phase 11 falls through into phase 12, including the possible second animation
call after timer expiry; fresh object fields are read after opaque providers.

Per-function normal and strict diagnostic builds reproduce every extent,
including pools and alignment. Changed-source controls alter real layer,
phase, tile, flag or cue operations and must reject. A missing animation-frame
prototype produced a legacy 188-byte match but failed the strict declaration
check; the current canonical declaration is present and that failure is
retained. Layout and callback-assignment diagnostics reject wrong widths,
alignment, capacities, record types and callback arguments independently of
instruction equality.

The finite checks execute eight update/control/draw entry bodies with
initialized scene and object storage, caller-clobber poisoning and an
independent branch model. Their scope includes timer fallthrough, row outcomes,
boundary/reflection arithmetic, two incoming-register poison cases and
explicit provider mutations testing fresh global loads. Calls into other
bodies are bounded abstract providers for this fixture set, even when their
C bodies also match. These checks are not a full nested game run, IRQ or
hardware model, interleaving proof, complete-capacity proof or gameplay test.
Whole-ROM verification and publication are separate milestone gates.
