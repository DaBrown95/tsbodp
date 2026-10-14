# Factory slot 12 palette resource

This connected path adds two matching C extents, 172 bytes. Factory slot 12
creates a positioned object with a fixed animation and a payload-selected palette
slot, installs its step callback, and applies the existing map-layer updater.
The callback requests removal when state is one. These names describe observed
accesses; they are provisional. Compiler equality, static routing and gameplay
behavior remain separate claims. No gameplay run is claimed.

| Function | ROM offset | Full extent |
|---|---:|---:|
| `frame_create_palette_resource` | `0xE280` | 144 |
| `frame_palette_resource_step` | `0xE310` | 28 |

The constructor owns all bytes through `0xE310`, including its three literal
words: flags `0x40019`, the animation address and the installed callback address.
The callback owns the next 28 bytes through the distinct, already recovered
`transition_reset_view` entry at `0xE32C`. Neither source needs an alignment
directive. No low-level assembly body or glue receives C credit in this batch.

## Factory and callback contracts

The resource factory table at `0x4F278`, slot 12 at `0x4F2A8`, contains
`0x0800E281`. The constructor has the existing `ResourceObjectFactory` contract:
two byte arguments and a `FrameObject *` result. It passes the zero-extended
group and entry values to the already recovered payload provider. The accepted
group spawner supplies those arguments through the factory table and records
the returned object. Arbitrary group, entry and pointer validity remain unchecked.

The payload has a word ID at zero, signed X/Y halfwords at four and six, and a
palette byte at eight. Its compiler partial view is 12 bytes with alignment four;
that rounded size does not establish a complete serialized-record capacity.
The native word load and existing aligned offset-table builder paths support
this model, while complete payload roots and arbitrary external pointer alignment
remain unproved. Coordinates multiply the signed halfwords by 65,536; every
possible halfword product fits the target signed word. The ID goes through the
accepted allocator's full-word `int` contract; the allocator's later halfword
store does not justify narrowing that interface.

The constructor zeros the actor-ID byte at `+4C` and direction byte at `+12`,
sets the fixed flags, installs the typed animation record at `0x0804F80C`,
resets transition state to zero and acquires the payload palette slot. It
installs `0x0800E311` at `+88` and clears both paired callback slots at `+C8/+CC`.
Those cleared slots use the existing two-pointer `CollisionCallback` contract;
the generic actor's provisional one-argument interaction view is unchanged.
The new step callback instead has the standard `void(FrameObject *)` contract.
Actual factory, step and collision-slot assignments are checked separately by
the pinned compiler.

State zero and states other than one do nothing. State one sets flags bit one.
The already accepted `frame_step_object` tests that bit on its next invocation
and routes to `frame_remove_object`. This establishes the static removal handoff,
not the timing or reachability of a gameplay scenario. The nearby original
`transition_set_view_mode` body at `0xE8B4` is a separate extent and gains no
C credit here.

## Partial object and flag evidence

The new whole-object access view measures 212 bytes with alignment four.
It records the used flags word at `+0C`, direction at `+12`, actor ID/state
at `+4C/+4D`, step callback at `+88` and paired callbacks at `+C8/+CC`.
Its bitfields access the actual `+D1` byte from the aligned object base;
there is no separately cast aggregate at an odd address. Compiler-produced
diagnostic objects establish contact-mode mask `0C`, double-size mask `20`
and the preserved bit-four mask `10`. The constructor clears only the first
two masks and retains bit four and all other bits.

The generic `FrameObject` view measures 312/4 and the accepted underlying
allocator requests 320 bytes. These are distinct facts. The new 212/4 view
establishes only its observed fields; neither equality nor those measurements
prove complete object contents, allocation success or arbitrary pointer validity.
The final layer updater and palette-slot provider are already accepted C and
earn no new credit here. Their names and storage domains remain provisional.

## Verification limits

Both new bodies are ordinary C with no register bindings, volatile accesses,
dummy initialization or instruction transcription. Fresh full-extent positives
and genuine changed-source controls are retained, together with separate strict
diagnostic positives and controls. The constructor's changed flags and callback's
changed state test both fail actual comparison. The twelve connected accepted
factory, allocation, position, animation, state, palette, layer, step and removal
providers are reverified with their existing controls and current literal headers.

Pinned compiler diagnostics check 29 layout facts, actual API assignments and
physical flag masks. Wrong widths, object packing and factory/callback formals
are rejected. Removing the real palette-provider declaration still gives an
identical constructor under the permissive legacy profile, but strict diagnostic
compilation rejects it. The declaration test is separate from byte equality.
Initialized mask objects live only in private diagnostic data; a first attempt to
offer those objects to the text-only matching gate was correctly rejected and
preserved. No acceptance check was weakened.

Sixty-eight finite initialized constructor and callback cases agree with the
original bytes and an independent branch model. They cover coordinate extremes,
palette arguments, preserved bit four, standard callback states and caller-clobbered
register poisoning; changed-source controls diverge in 56 cases. The palette-user
model contains sixteen explicitly initialized abstract slots, not a complete
storage claim. Null allocation, an unmapped payload and an out-of-model palette
slot are rejection controls; the source adds no guards for them. Provider effects
are abstracted, and higher incoming argument bits are ABI-only injections. These
fixtures do not establish hardware or gameplay behavior. Whole-ROM equality is
verified separately when the batch is integrated and published.
