# Local output retention

After a verified milestone is published, run
`python3 tools/retain_build_runs.py` to inspect its plan, then
`python3 tools/retain_build_runs.py --apply` to remove superseded successful
build outputs. The plan pins the current pilot/build reports, actual inputs and
each selected run's report. A changed current proof or input, linked directory,
altered receipt or unexpected path aborts removal.
If a newer pilot has not yet completed the full build, retirement stops until
the paired pilot/full proof is current; it cannot retire the pilot referenced
by the retained full-ROM proof.

Keep one current successful paired pilot/full-ROM proof intact, including
source/header snapshots, changed-source controls and raw outputs. The helper
directly retires a superseded success only when every actual C, assembly,
header and control input is byte-identical to an input in that current proof.
It records the retirement under ignored `reports/us-eu/retention/`; it creates
no historical proof archive. The completed journal records each input-map count
and digest; the full map remains in the plan for the checks before deletion.
Retire a fulfilled plan after retaining its compact journal. Run-specific dependency files and old hash
receipts alone do not require retaining duplicate payloads.

Any unique source, header or control input holds the old run for deliberate
review. Preserve the unique attempt and its useful comparison before manually
retiring its other generated outputs. Failed and incomplete gates also require
review; retain only the bounded useful failures for active reconstruction.

For private compiler trials, retain one current best candidate per target and
useful failures that distinguish a source/compiler hypothesis. Preserve source,
raw expected/candidate comparisons, actual control inputs, commands and
receipts. Once a comparison is recorded, discard obsolete object and linked
intermediates. Retain preprocessing only when it is the sole input or an active
compiler diagnostic. Header snapshots may use a shared hash store with a
verified restoration path; unresolved inputs and active proofs remain intact.
Large speculative trial matrices need a stated hypothesis and a bounded trial
count. Do not retain duplicate build/toolchain provisioning trees after their
receipts have been reviewed.

Measure filesystem available space before and after cleanup. Summed file or
directory allocation can double-count APFS clones, and snapshots or delayed
reclamation can postpone visible recovery. Project retention does not authorize
deleting backup restore points.
