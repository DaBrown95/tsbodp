# Internal AI scratch: ROM inventory refinement

Not reader documentation. Public explanation and commands belong in README.

The scanner recognizes the agbcc Thumb switch sequence only when the compare,
unsigned range guard, scale, table load and MOV-to-PC agree. Both BHI and BLS
with a default branch are supported. Every table target must be local, even
(MOV preserves Thumb mode), outside the table itself and decodable. Cases are
blocks, not function seeds. Tables join literal-data accounting.

Weak pointer-only candidates can be folded when another body reaches them by
fallthrough, as a switch case, or through a recognized stack-return sequence.
Direct-call and audit evidence protects independent entries. Folded aliases
remain recorded. The smaller entry count is map cleanup, not lost source.

`control_flow_bounded` is an instruction-body result, not a proven compiler
function extent. Alignment and pool ownership remain estimated; the envelope
is still clipped at the next surviving entry. Stack balance and runtime
reachability are not established. The 19 compiler-owned extents remain the only
green source credit.

Remaining dynamic control:

- IRQ dispatch at ROM 0x25C uses writable RAM table 0x03004290. The default table
  at ROM 0x53558 supplies observed targets, not an exhaustive target set.
- Shared register dispatch veneers must be distinguished from their callers.
  The inventory records each BL caller and resolves literal-derived targets
  when possible. A direct call to BX LR is an ordinary return, not a callback.
- Audio mixer kernel table at ROM 0xD6F4A4 includes ARM RAM entries and ARM ROM
  entry 0x08049BF0. The latter corrected an earlier Thumb candidate. Runtime
  index bounds and writes are not exhaustively proven; null slots stay visible.
- The audio-frame memory-loaded callback remains dynamic. Do not read its
  initial RAM value as if it were immutable runtime state.

ARM conditional loads cannot establish unconditional pointer constants. Shifted
arithmetic is left unknown unless modeled. Conditional returns preserve the
fallthrough path. ARM/Thumb conflicts use physical ROM ownership, including
RAM aliases, and retain independent conflicting evidence for review.

The earlier 124-site count covered terminal transfers only. The refined map
also inventories indirect call sites through shared veneers; do not compare
those two counts as the same completeness metric.
