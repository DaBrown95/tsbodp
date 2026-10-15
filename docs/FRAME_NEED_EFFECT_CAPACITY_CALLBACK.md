# Need-effect capacity callback contract

This connected change recovers the 52-byte provider
`frame_need_effect_check_actor_header` at `0x0800CC8C` and refines the existing
capacity/check interfaces with zero additional C or assembly credit for that
interface repair. It makes the two reconstructed views compatible with the
three reconstructed installed providers, while preserving all four callers'
observed low-byte result consumption. Names and access types remain inferred;
matching bytes and static calls do not establish original headers or gameplay.

## Actual storage and installed prefix

The allocator at `0x0802E2CC` copies definition word `+28` into need-effect state
`+0xE4`. Definition word `+8` instead supplies state `+0xEC`; it is a separate
role. The state access view is 256 bytes with alignment four; the definition
view is 36 bytes with alignment four. This mapping is supported by the actual
loads and stores, not by the order of a proposed callback typedef.

In the observed 148-row prefix at `0x08062E7C`, stride 36, the `+28` word selects
`frame_check_optional_attachment_capacity` at `0x0802F348` in 135 rows and
`frame_optional_choice_context_available` at `0x080442D0` in rows 112 and 113.
The recovered provider at `0x0800CC8C` occupies rows 53 and 84. All three
reconstructed definitions return an unsigned word and take a
`FrameNeedEffectState *` and a `FrameObject *`. They produce zero or one in
their current bodies. Assigning each actual definition to either refined
shared field is checked by the target compiler.

Three original targets occupy the other nine observed rows: `0x080131D8`,
`0x08021DF4` and `0x080164F8`. Their C signatures remain unproved.
The prefix does not establish full table capacity or permit arbitrary kind
indices. The compatible-type finding is bounded to the three reconstructed
providers; it is not a blanket indirect-call claim for those original targets.

## Callers and preserved result width

The check fields in `FrameActionOwnerCallbacks` and `FrameActionSearchNode`
now use the same word-returning, need-effect-state/actor pointer contract.
`frame_need_effect_begin_choices` and `frame_actor_use_target` explicitly
convert the result to a byte before comparing it with one.
`frame_actor_state_39` and `frame_find_action_target` explicitly convert it
to a byte before testing for nonzero. The search-node owner argument uses a
real need-effect-state access-view cast; no function-pointer cast is added.
The prior `+0xE8/+0xF0/+0xF4/+0xF8` refinements are preserved.

The native call sites transfer owner and actor through `r0/r1`, use the existing
`bx r2` veneer, then perform the corresponding low-byte shifts and comparison.
The refinement adds no read, write, branch, initialization or register binding.
All original function metadata, profiles and changed-source controls are retained.
The complete 189 accepted literal importers, covering 25,344 context bytes,
are recompiled with actual controls; nine direct functions also have strict
declaration-diagnostic pairs. All original pools and alignment are compared.
Removing any one caller's explicit result conversion rejects its complete match
under both the normal and strict diagnostic profiles. Former return types and
owner tags fail actual-definition assignment checks separately.

## Bounded source and native checks

The finite provider check executes the two original and reconstructed providers
and their actual attachment-count and object-ID helpers, with no abstract hooks.
Its 960 initialized cases vary the three record pointers, capacity byte, two
actor attachment pointers, attachment mode, context active byte and ID halfword.
The actual provider source controls diverge in 224 cases. The actor attachment
access requires a readable 320-byte prefix with initialized accessed fields,
including slots at `+312/+316`;
the common 312-byte `FrameObject` prefix alone does not establish those accesses.
The owner access uses its 256-byte view with initialized fields on each selected path. These are input
preconditions, not new source guards or proven allocation guarantees.

A separate 4,096 numeric ABI diagnostic interprets each actual post-call
shift/comparison/rejection sequence and compares it with the explicit byte
conversion. Values beyond zero and one diagnose the caller's width contract;
they are not claimed outputs of the three reconstructed providers or a source model of
the complete generic callers. Four uninitialized-memory rejections and an
instruction-budget rejection describe the finite interpreter, not GBA faults.

The separate initializer/`+0xEC` audit makes no EC repair proposal without an
actual generic caller. State `+0xE0` remains unknown in this role. Writes to
the separate `FrameObject` program words at `+0xE0/+0xE4` are not reclassified
as need-effect callbacks. Unknown targets, arbitrary pointer validity and
runtime behavior remain outside this refinement.

## Connected actor-header provider

The recovered `0x0800CC8C` provider first calls the existing byte-returning
attachment-count helper. A nonzero count together with owner byte `+96` equal
to one rejects the check. Otherwise it rejects an actor whose unsigned ID
halfword `+8` equals seven and whose unsigned halfword `+0x0A` is at most 31.
The latter field's wider meaning remains unknown; no gameplay label is inferred.
It returns the literal word zero or one. Both incoming pointer values are
actually used. The complete 52 instruction bytes end at the independent entry
`0x0800CCC0`, with no pool or alignment borrowed. Ordinary C needs no fixed
registers, volatile accesses, added guards or assembly directives.

The new provider's actual ID-seven to ID-six source control changes one byte
under the normal and strict diagnostic profiles. Its actual definition and
prototype have three compiler-checked assignments and 13 physical checks;
five real wrong-header cases reject, including byte/signed halfword changes.
Removing the actual attachment-count declaration yields a measured legacy
52-byte candidate with 37 differences and a strict missing-declaration rejection.

Its separate finite qualification has 786 defined cases: 784 initialized
owner/actor inputs plus two short-circuit inputs that omit only an unread field.
It executes the actual original/reconstructed provider and accepted 40-byte
attachment-count helper, without abstract hooks. Unsigned halfwords include
32768 and 65535, and the threshold includes 31 and 32. The actual source
control diverges in 78 cases. Four uninitialized-read rejections and one budget
rejection remain finite-interpreter diagnostics. These cases supplement the
960 existing-provider cases; the 4,096 numeric caller-width diagnostics remain
separate and do not assert additional provider outcomes.

The combined proposal has one new C function/52 bytes, 189 unchanged existing
context functions/25,344 bytes, 190 actual normal pairs and ten direct strict
pairs. All 93 prospective literal headers and the existing caller conversions
are checked against the newly published baseline. Existing source profiles,
control mutations, addresses and metadata remain unchanged.
