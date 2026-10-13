# Sequence selection through the shared VBlank control

`audio_select_sequence` at `0x080411BC` adds 136 matching C bytes, including
both literal-pool groups and alignment. Its accepted scene, resource-command
and received-entry callers retain their existing byte-argument API and exact
addresses. The new source uses the existing game options, eight-byte sequence
descriptors and partial `AudioVBlankControl`; it adds no layout changes or
low-level instruction glue.

The options byte at `0x03005D90 +9` gates selection. With that byte clear, the
function stores the incoming byte into the control's sequence ID. Otherwise,
a different ID or control flag bit two enters the request path. It sets flag
`0x80`, selects the eight-byte descriptor from `0x08D73F34`, and passes its
sequence pointer, low parameter byte and next parameter byte to the accepted
sequence starter at `0x0804A808` (the accepted 732-byte `audio_player_start`).
The full parameter-word read and separate byte read are both preserved. The
accepted forty-byte `audio_sync_game_state` provider at `0x08041534` supplies
the connected game/options synchronization.

After synchronization, the function clears flag bit two, retains the observed
discarded volatile word read at `0x03004334`, and stores pacing eight. The wider
purpose of that discarded read is unknown. It stores the ID only when control
flag bit one is clear. These field names follow the connected VBlank/sequence
path; the complete coordination protocol and runtime timing are not proven.

Five semantic register constraints preserve the original allocation: the main
control pointer in callee-saved `r5`, the parameter word in `r4`, the short
descriptor/table pointers in `r0`/`r1`, and the final short control pointer in
`r2`. The short values are consumed before calls, and the main pointer is an
actual control root retained through the standard callee-saved ABI. There are
no emitted assembly instruction bodies or artificial global aliases. The
previous best source produced all 136 bytes with a two-byte difference: it
reused the earlier root with a move instead of reloading the final literal.
Constraining the actual main pointer gives the required independent final
address lifetime and the complete match.

Current source, header closures, original bytes, object/link outputs and raw
failed comparisons remain under ignored `reports/audio-root/audio-select-*`
and `audio_select_sequence/`. The earlier untracked ordinary source is retained
before replacement. A changed-source control stores pacing seven instead of
eight and rejects. Compiler and byte equality establish this reconstruction
milestone; they do not establish gameplay, descriptor bounds, concurrent-state
correctness or historical compiler provenance.
