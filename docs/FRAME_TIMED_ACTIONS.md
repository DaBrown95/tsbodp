# Timed actor action membership

The 48-byte membership query at `0x08007F58` extends the already recovered
timed-action descriptor path. It uses the same word-key search as the accepted
40-byte `frame_find_actor_action` and the same descriptor view consumed by the
accepted 292-byte state-19 update. Only the membership query earns new C credit
in this batch. The connected providers are rechecked with current headers and
actual changed-source controls.

The complete extent is `0x7F58..0x7F88`: a 42-byte instruction body, the
original two-byte zero alignment and the final table-address literal. The source
uses an ordinary inline search returning a signed-byte ordinal, followed by a
comparison with the minus-one sentinel. It adds no register binding, assembly,
volatile access, additional read or dummy initializer. The observed ordinal
range zero through 35 fits the signed-byte result of the existing search.

The table root is `0x0804EDA0`. Both searches compare the complete word key at
offset zero, advance by twelve bytes and stop at the first hit or after 36
records. Pinned compiler diagnostics confirm the existing twelve-byte,
four-byte-aligned descriptor view, its word key, duration halfword and animation,
variant, need and amount bytes. The table declaration remains incomplete: these
36 observed records do not establish the complete storage capacity. Wrong
stride, key width and API declarations are rejected in separate diagnostics.
Changing the actual incoming argument to a halfword also changes the compiled
extent, which supports the word argument contract rather than inferring it from
the byte-sized kinds at the current caller.

The query returns a complete word containing zero or one. The only mapped
incoming direct caller is the still-original catalog confirmation handler at
`0x08042964`. That caller tests the low byte of the result before selecting
between ordinary record insertion and the timed actor-action path. Its narrow
test does not require a narrow result declaration for the provider. The caller
and neighboring code remain explicit original regions. Static routing and the
shared table identify this as a membership query; they do not establish the
original function name or complete gameplay purpose.

Finite initialized instruction fixtures compare original and compiled query
bytes for first-hit behavior, duplicate keys and unknown complete-word IDs.
The genuine comparison-flip control diverges on unknown IDs. Truncated literal
or record inputs, an unmapped table root, an unsupported instruction and an
exhausted instruction budget are rejected by the private model. Those fixtures
do not establish hardware behavior, arbitrary pointer validity or complete
table bounds. Whole-ROM equality, static mapping and runtime behavior remain
separate claims. The larger catalog confirmation handler is still unmatched;
useful ordinary source hypotheses and raw comparisons remain preserved locally.
