# Independently bounded attachment checks

Thirteen previously mapped prologue candidates now have matching C for their
complete 40-byte extents. Each body is 38 instruction bytes followed by two zero
alignment bytes. They share the existing attachment-count predicate: return zero
when the actor has an attachment and the owner byte at offset `0x60` equals one;
otherwise return one.

| ROM offset | Source |
| --- | --- |
| `0x18408` | [frame_unrooted_attachment_check_18408](../src/frame/frame_unrooted_attachment_check_18408.c) |
| `0x1A364` | [frame_unrooted_attachment_check_1a364](../src/frame/frame_unrooted_attachment_check_1a364.c) |
| `0x22098` | [frame_unrooted_attachment_check_22098](../src/frame/frame_unrooted_attachment_check_22098.c) |
| `0x25968` | [frame_unrooted_attachment_check_25968](../src/frame/frame_unrooted_attachment_check_25968.c) |
| `0x25B1C` | [frame_unrooted_attachment_check_25b1c](../src/frame/frame_unrooted_attachment_check_25b1c.c) |
| `0x2873C` | [frame_unrooted_attachment_check_2873c](../src/frame/frame_unrooted_attachment_check_2873c.c) |
| `0x35800` | [frame_unrooted_attachment_check_35800](../src/frame/frame_unrooted_attachment_check_35800.c) |
| `0x35C14` | [frame_unrooted_attachment_check_35c14](../src/frame/frame_unrooted_attachment_check_35c14.c) |
| `0x3CF10` | [frame_unrooted_attachment_check_3cf10](../src/frame/frame_unrooted_attachment_check_3cf10.c) |
| `0x437B4` | [frame_unrooted_attachment_check_437b4](../src/frame/frame_unrooted_attachment_check_437b4.c) |
| `0x44CD8` | [frame_unrooted_attachment_check_44cd8](../src/frame/frame_unrooted_attachment_check_44cd8.c) |
| `0x464A0` | [frame_unrooted_attachment_check_464a0](../src/frame/frame_unrooted_attachment_check_464a0.c) |
| `0x48610` | [frame_unrooted_attachment_check_48610](../src/frame/frame_unrooted_attachment_check_48610.c) |

The definitions use the existing `FrameNeedEffectState` owner and the actual
unsigned-byte attachment-count provider. No new memory view, executable assembly
or original instruction body is embedded in C. Every full positive extent matches
at its fixed address; changing the owner-byte test from one to two rejects each
match. Actual definition and target type checks reject incorrect arity, return
width, owner/actor pointer types, field offset/width and provider backing count.

These entries were already discovered. Their incoming callback roots and
historical names remain unidentified; the address names preserve that uncertainty.
The two consumed arguments and return convention are source-interface evidence,
not complete callback, writer, index, backing or runtime domains. The two tail
bytes have an alignment role, which does not exclude alternative execution.
Executable inventory and source ownership remain incomplete.
