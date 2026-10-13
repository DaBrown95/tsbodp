# Text and tile byte operations

This connected batch implements six runtime dependencies of
text substitution, text-resource expansion, grid-neighbor offsets and tile
allocation reset. The names describe their observed contracts; they do not
identify the original source library. These are independently reconstructed C
algorithms, with no imported instruction bodies or third-party source.

| Name | ROM entry | Complete extent |
| --- | --- | ---: |
| `display_text_copy_bytes` | `0804E7D0` | 96 bytes |
| `display_text_move_bytes` | `0804E830` | 136 bytes |
| `display_fill_bytes` | `0804E8B8` | 84 bytes |
| `display_text_append_string` | `0804E90C` | 72 bytes |
| `display_text_copy_string` | `0804E9E0` | 76 bytes |
| `display_text_string_length` | `0804EA2C` | 68 bytes |

The 532-byte subtotal includes literal pools and required alignment. Each extent
ends at the following independent Thumb entry. The find-character body between
`0804E954` and `0804E9E0` remains unconverted. No adjacent bytes are credited to
this batch.

## Contracts and compilation evidence

The byte operations receive a destination, a source or fill value, and an
unsigned byte count; they return the original destination. The copy routine
uses a forward traversal. The move routine selects a backward byte traversal
when the destination starts inside the source range, and otherwise uses the
forward path. Both use aligned four-word blocks, then individual words and
remaining bytes. The fill routine repeats the low eight bits of the integer
value across each word and uses the same block sizes. Its byte tail retains the
post-decrement count and checks the previous value explicitly.

The string-append routine scans to the destination's terminating zero, calls
the string-copy routine and returns the original destination. The string-copy
routine also returns the original destination; the length routine
returns the byte distance to the terminating zero. All three scan aligned words
using the common zero-byte test in `display_word_scan.h`, then finish with byte
accesses. Word scanning can read beyond the first zero byte within its aligned
word. The static body does not establish the caller's accessible-buffer bounds.
This is not a claim that arbitrary unterminated or undersized inputs are valid.

These entries use explicit per-function `compiler_flags: ["-O2"]` with the pinned
agbcc Thumb compiler, instead of the default interworking flag. Their observed
returns restore the PC directly. A caller's interworking-compatible declaration
and Thumb symbol remain unchanged. The byte-copy word source cursor has a local
C register binding to `r3`; it represents one meaningful cursor within the
aligned-copy branch and does not survive a call. No other register constraints
are used in this batch. The only top-level assembly in the string and fill/copy
files is zero-filled alignment, not an instruction body.

## Verification and connected callers

All six public sources compile and link to identical bytes at their original
entries, including their literal pools and alignment. Fresh changed-source
controls alter the block decrement, fill byte mask, string zero test or word
scan stride or append destination; all six produce nonidentical outputs. The string-copy control
changes 66 bytes, and the other five change one byte each. These are actual
compiled mutations, not comparisons against a fabricated different output.

The current accepted tile reset and configuration, text-copy expansion,
text-resource expansion and grid-neighbor callers also recompile exactly with
their existing changed-source controls rejected. Their symbol addresses and
ABI-identical declarations are retained. The new guarded runtime header supplies
the same prototypes to the reconstructed bodies without changing shared caller
headers.

Ignored local evidence is retained in
`reports/agents/display_audio/text-runtime/`: the selected raw trials, failed
interworking/allocation/loop variants, canonical public-source snapshots,
expected and actual bytes, disassembly, commands, source hashes and actual
negative-control outputs. `runtime-ready.json` records the six accepted entries
and the current-caller proof locations. The nearby 140-byte character finder is
still a private candidate, and its failed trials are excluded from coverage.

These are static contract and compiler/linker claims. The whole-ROM gate and
publication are separate checks, and this batch adds no runtime or gameplay
validation claim.
