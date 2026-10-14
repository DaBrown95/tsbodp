# Resource contact and clock-gated notice path

Three matching C functions reconstruct the connected factory slot 10 path.
Names describe observed operations; the original gameplay role is uncertain.

| Function | ROM entry | Complete extent |
| --- | --- | ---: |
| `frame_create_contact_resource` | `0x080294B0` | 196 |
| `frame_begin_contact_action` | `0x080111AC` | 76 |
| `frame_tick_contact_action` | `0x08029574` | 560 |

The total is three functions and 832 C bytes. Each complete extent, pools and
original alignment compiles and links identically. Actual changed-source
controls change the constructor flags, interaction state guard and failure
notice ID. Separate private strict declaration diagnostics use the same pinned
compiler without changing the acceptance profile. Twenty-four current accepted
functions are freshly checked as the direct providers and actual factory,
update and collision callback loaders. No new assembly glue is needed.
Whole-ROM equality, these source proofs and runtime behaviour are separate
claims; this batch makes no gameplay or execution claim.

## Factory and layouts

The table rooted at `0x0804F278` has slot 10 at `0x0804F2A0`, containing
`0x080294B1`. The matching group loader calls that factory with byte group and
entry indices, then records them in the returned object's owner fields. The
constructor's byte formals match the existing `ResourceObjectFactory` typedef.
Its word locals retain explicit byte casts and reproduce the original entry
conversions before payload lookup.
Its twelve-byte serialized view reads a word ID at zero, signed coordinates at
four and six, and four configuration bytes at eight through eleven. Multiplying
signed halfwords by 65536 fits every input in a signed 32-bit result.
Allocation and the returned payload are unchecked.

It sets flags `0x60405`, copies those four bytes into object `+0x64..+0x67`,
resets transition state, clears D1 bits 2..3 and 5 while preserving bit 4,
sets layer three and palette slot two, and installs the interaction and step
callbacks. Bytes `+0xAF` and `+0xB4` become one. The animation record rooted at
`0x0805982C` is passed to the matching animation setter and layer/visibility
wrapper. This record remains original data and is not embedded in source.

The factory's four pools at `0x08029564..0x08029570` hold the flags,
`0x080111AD`, `0x08029575` and animation pointer. The full extent ends at the
step entry. The step's last return is at `0x080297A0`; the original zero
halfword at `0x080297A2` aligns the distinct following entry `0x080297A4`.
Its 96 bytes of referenced pool data remain inside its 560-byte ownership.
The interaction owns its pressed-input pool and alignment up to `0x080111F8`.

The independent guarded role header contains partial views, rather than
changing the provisional generic actor structure. Pinned compiler assertions
establish the resource view's size 216 and alignment four, with step `+0x88`,
partner `+0x90`, enable bytes `+0xAF/+0xB4`, callback `+0xC8`, following flags
byte `+0xD2` and display attributes `+0xD5`. Its D1 bitfields reside within an
object viewed from its aligned base. Initialized diagnostic objects establish
mask `0x0C` for the two-bit contact mode and `0x20` for double size; changing
that mode to three bits instead produces `0x1C`. A real packed-view control
rejects the size/alignment assertions. Diagnostic data objects receive no
source coverage. The generic three-bit D1 access view remains unchanged for
other consumers.

The contact and step views both have size 148 and alignment four, with state
at `+0x4D` and partner pointer at `+0x90`. The contact view reads ID at eight;
the step view reads kind, parameter and hours at `+0x64..+0x67`. These views do
not prove the remainder of an object's type or lifetime.

## Two-object interaction and step handoff

The callback at `0x080111AC` consumes both incoming `CollisionObject *`
pointers. Its formals and the resource view's callback field match the
canonical `CollisionCallback` typedef. Explicit casts select the partial
contact views and store the partner through the frame-object pointer view. The
other object must have ID zero and state 16, the owner must be in state zero,
and pressed-input bank element zero must contain bit one. It sets the partner
state to zero, owner state to four, records that partner, and clears input.
The observed input root is `0x03004228`, the shared pressed array, distinct
from the local-only pressed root. There are no null or capacity checks.

The copied ARM collision dispatcher calls the callback slots at `+0xC8/+0xCC`
with `(a,b)` and `(b,a)`. Its matching source and native transfer sites establish
R1 as the other object, including the copied execution-address mapping.
The constructor's pool at `0x08029568` is the only aligned ROM word containing
`0x080111AD` in the retained scan; static direct-call metadata records no direct
caller. That bounded scan does not prove all possible runtime writers.
Pinned declaration diagnostics assign the new functions to the existing
factory and collision typedefs successfully. Two actual controls restore the
earlier word-formal factory or frame-pointer callback declaration and are
rejected as incompatible function-pointer types under the strict diagnostic
profile. The earlier models could reproduce bytes, so byte equality alone
did not establish those C call contracts. No diagnostic probe receives C
coverage.

The generic actor declaration `frame_actor_interaction_default` names the
separate original address `0x08011275`. Its generic one-argument interaction
view stays provisional and is not refined by this distinct resource callback.

The step begins with two copies of the eight-byte clock constant at
`0x08051AA4`. Its explicit idle state zero is produced by the interaction and
reset branch. In state four, a word/bitfield clock view inserts each configured
hour into bits 16..23 while preserving the other clock bytes. The two real
record views are then passed to the existing clock APIs. The constant, hour
encoding and field roles follow those providers; they do not establish clock
rate or callback frequency.

It checks the row/column pair selected through a four-byte record rooted at
`0x0805983C`, then the selected completion flag, need average above thirty and
whether the world clock lies within the configured hours using mask six.
Failure paths choose notice IDs `0x1857`, `0x1855` or `0x1858`. An available
window sets the success flag, ID `0x1854`, option IDs 210/211 and notice byte
three to one. Outside the window, ID `0x1856` is paired with two formatted
clock substitutions. Common code sets notice bytes four/one/two to 0/1/4,
copies label `kind + 0x1859`, and submits default scene request two.
An unsuccessful check additionally updates the partner's direction, animation
and variant before the owner advances to state five.

In state five, previous request parameter one selects the owner's parameter
as mode and submits scene kind twenty with its kind and corresponding world
value, then sets that completion bit. The other result restores partner state
16, clears the partner and returns the owner to idle zero. No state or object
validity guards were added.

The world access view aliases root `0x03003950`: clock `+8`, the eight need
words `+0xB0`, values `+0x735..+0x73C` and completion byte `+0x73D`.
Messages alias `0x030059F0` as the three observed halfwords; the notice byte
view aliases `0x03005A00`. Other published views interpret overlapping storage
for other roles. Pinned layout assertions cover these exact offsets, clock
union size eight/alignment four, condition stride four and notice offsets.
The wider state ownership, option lifetime and index bounds remain uncertain.
Kind values outside the observed eight-element view, shifts outside the C
word range, missing partner objects, formatting capacity and dynamically
changed callbacks are not validated. Current static linkage and compiler
matches do not resolve those runtime limits.
