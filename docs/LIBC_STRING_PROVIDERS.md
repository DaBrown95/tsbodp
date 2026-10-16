# Character search and counted string-copy providers

Two connected ordinary-C providers rebuild 252 bytes at the original addresses,
including literal pools and alignment, with no assembly credit:

| Provider | ROM extent | C bytes | Matching consumer |
| --- | --- | ---: | --- |
| [`display_text_find_character`](../src/display/text_find_character.c) | `0804E954..0804E9E0` | 140 | Resource text expansion tests for `@` |
| [`runtime_copy_padded_string`](../src/runtime/copy_padded_string.c) | `0804EA70..0804EAE0` | 112 | World defaults copy the fixed name into 16 bytes |

Search narrows the requested character to a byte, scans aligned words with the
zero/character detector, then finishes with byte comparisons. Its 138-byte symbol
and two original terminal zero-alignment bytes end at the already owned string
copy provider. Counted copy uses aligned words only while at least four bytes
remain and no zero byte is present, then copies bytes and pads the remaining
count with zero. It returns the original destination; original bytes after its
112-byte return extent are not claimed.

These sources adapt Newlib's `libc/string/strchr.c` and `strncpy.c` from
[`pret/agbcc` revision `da598c1d918402c42c0c0d7128ba14567f3175e9`](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libc/string).
The complete [Newlib distribution notices](../licenses/Newlib-COPYING.txt) are
preserved, with trailing whitespace trimmed; the applicable Berkeley notice is
also printed in
each adapted source. Changes are project names/direct declarations, target
32-bit detector selection, unsigned-byte API for counted copy, and an explicit
previous-count lifetime in its padding loop. No original instruction bodies or
post-compilation changes are used.

The pinned libc Makefile supplies the reproducible old-AGBCC recipe
`-O2 -fno-builtin`. Fixed-source counterfactuals also match these two bodies with
current AGBCC. The compiler choice therefore does not identify the historical
compiler or uniquely explain earlier failed paraphrases. Preserve the matching
source types/control flow rather than attributing equality to a profile switch.
This differs from the independent byte-clear provider at `0804E7B4`, whose
explicit-previous source fails under the tested current profile.

Fresh public-source/header comparisons include semantic changed-source controls:
returning the character after the match, or padding with one. Both compile to the
same size and reject by one byte. The renamed defaults caller also recompiles
exactly with its compiling control. Source ownership does not establish complete
incoming transfers, string or destination bounds, aligned-word readable extent,
or gameplay execution.

With the previously owned providers, the nine complete source extents from
`0804E7B4` through `0804EAE0` cover 812 contiguous bytes without a gap or overlap.
This is local ownership accounting, not a complete runtime or game denominator.
