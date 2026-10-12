# Connected heap allocation and release

Sixteen connected functions supply 1,144 bytes of matching C. The latest four
add 472 bytes. All complete linked
extents match at their original ROM addresses, including literal pools and
alignment. Actual changed-source controls reject for every function. This
closes the allocation, zeroing, resize and release core used by text rendering
and map resource loading. Copy and arena bootstrap are also reconstructed.

| Function | ROM address | Bytes |
| --- | --- | ---: |
| `heap_initialize` | `0x08027830` | 52 |
| `heap_allocate` | `0x08027864` | 128 |
| `heap_allocate_zeroed` | `0x080278E4` | 164 |
| `heap_free` | `0x08027988` | 40 |
| `heap_resize_in_place` | `0x080279B0` | 152 |
| `heap_clear` | `0x08027A48` | 108 |
| `heap_copy` | `0x08027AB4` | 104 |
| `heap_initialize_arena` | `0x08027B20` | 72 |
| `heap_block_bytes` | `0x08027B68` | 32 |
| `heap_link_physical` | `0x08027B88` | 20 |
| `heap_link_free` | `0x08027B9C` | 20 |
| `heap_prepend_free` | `0x08027BB0` | 36 |
| `heap_unlink_physical` | `0x08027BD4` | 44 |
| `heap_unlink_free` | `0x08027C00` | 48 |
| `heap_merge_previous` | `0x08027C30` | 68 |
| `heap_merge_next` | `0x08027C74` | 56 |

## Layout and ownership evidence

Each 16-byte block header has next/previous physical pointers at zero/four
and next/previous free links at eight/twelve. Allocated headers instead encode
the arena index in the word at eight and minus one in the word at twelve;
these are tags, not live free-list pointers. A block's capacity is the next
physical header address, or the arena end when no next header exists, minus
its address and 16. A 16-byte arena descriptor has physical head, free head,
recorded byte count and end pointer at zero/four/eight/twelve.

Arena descriptors begin at `0x03001DC0`; the separately observed count word
is at `0x03001DD0`. These addresses overlap the second descriptor position
under a generic unsized array view. Neither the loop nor initializer proves
that multiple arenas are valid for this game's storage. The array stays
unsized. The reconstructed bootstrap reads ROM words at `0x0807FA7C` and
`0x0807FA80`, whose values are `0x02000000` and `0x020027F8`. It rounds their
difference to 16 bytes and passes arena zero, begin `0x02002800` and end
`0x02040000` to initialization. One direct call to the arena initializer was
found at `0x08027854`; that bounded byte-pattern scan does not establish a
complete executable callgraph or prove one-time initialization. Initialization
sets both heads to `begin + 16`, stores
`end - begin - 16`, clears that initial header and increments the count. It
does not reset the count or validate the supplied arena index/range.

Allocation rounds its requested word size up to a multiple of 16, retaining
unsigned overflow. It searches arenas in ascending order and each arena's
free list for the first adequate block. A larger block is split at
`block + 16 + rounded_bytes`, linked into both lists, and the selected block
is removed from the free list and tagged allocated. A same-size block is
used without splitting; failure returns null. There is no positive minimum
size or extra header-sized remainder check. Semantic `do`/`available` control
flow preserves the original search exit and pool layout naturally. An inline
C helper shares this semantic operation between the ordinary and zeroed
allocators; both compile to their complete original bodies. The zeroed variant
rounds first, allocates, and clears the rounded byte count only on success.
Its extra rounding remains explicit, including word-sized overflow behavior.

Release subtracts 16 from the supplied pointer without a null check, decodes
its arena tag, prepends it to the free list, merges the following physical
block when free, then merges the preceding physical block when free. The
physical and free helpers preserve their distinct link offsets. Previous
merge writes through the released block's next free pointer without checking
it for null; the preceding free block would supply a free-list entry under
the expected invariant, but the code alone does not prove a valid heap.
Invalid pointers, duplicate release and corrupt links are unchecked here.

In-place resize rounds to 16 bytes and returns the original pointer on success.
Shrinking inserts a following free block and merges it with the next free
physical block. Growing examines the following physical block, rejects an
allocated or insufficient block, splits any remaining capacity, then removes
that consumed block from both lists. It never relocates or copies the contents.
The code does not check for a missing following physical block before reading
its capacity, or validate the supplied allocation pointer. Names describe these
static operations, not a claim that arbitrary calls are safe.

The byte copy routine uses aligned word loads/stores when both pointers are
aligned and copies the remaining bytes afterward; otherwise it copies bytes
forward. It returns the original destination. There is no overlap handling or
`memmove` guarantee.

The byte clear routine handles an unaligned leading prefix, writes a repeated
word pattern with aligned stores, then writes the final zero through three
bytes and returns the original pointer. It accepts a word-sized value: high
bits are not explicitly masked before constructing the repeated pattern.
The C word shifts use unsigned values to preserve defined wrap behavior;
byte stores narrow naturally. Zero length performs no stores. This is static
and compiler evidence, without a runtime allocation test claim.

## Matching evidence and connected callers

The public source/header closure proofs and all raw controls are indexed by
`reports/agents/display_audio/background_motion/scene/redraw/heap-measure-ready.json`.
The two link controls generate 24 bytes rather than 20 and reject by 20
different/missing/extra bytes; unlink controls reject by nine bytes. All other
heap controls reject by one byte, changing capacity header size, free tag,
coalescing sentinel, release header offset, rounding, initial header position
or leading fill calculation. Useful earlier loop, alias and lifetime failures
remain local.

The next public closure and actual controls are indexed by the neighboring
`heap-next-ready.json`. Zeroed allocation rejects by two bytes; resize, copy
and bootstrap controls each reject by one. Refactoring the existing ordinary
allocator to the shared inline header still matches all 128 bytes, and changing
its passed allocation size rejects by one byte. Useful failed direct-expanded
zeroed, resize lifetime, signed-copy-tail and incorrect bootstrap-symbol trials
remain local.

All bodies are semantic C. Resize binds only its moving physical-block pointer
and combined-capacity local to `r6` and `r2`; trials removing either constraint
failed. These are C register-allocation constraints, without an embedded
instruction sequence. Other heap bodies use no fixed register constraints. Free, clear and
next-merge each keep their two-byte zero-filled alignment directive separate
from the body. The accepted map callers and text transfer controller now use
canonical `heap_allocate`, `heap_free` and `heap_clear` names; their prior
callsite names described roles, not distinct implementations. Text pixel
allocation calls the reconstructed `heap_allocate_zeroed` at
`0x080278E4`. The four renamed callers still match 92, 92, 132 and 304 bytes,
and their compiled controls reject by one, one, 57 and one bytes respectively.
Those fresh receipts are indexed by the local `heap-rename-proof.json` beside
the core receipt. Full-ROM equality, static heap layout and runtime behavior
remain separate claims.
