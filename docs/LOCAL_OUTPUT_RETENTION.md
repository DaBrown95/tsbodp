# Local output retention

After a verified milestone is published, run
`python3 tools/retain_build_runs.py` to inspect its plan, then
`python3 tools/retain_build_runs.py --apply` to remove superseded successful
build outputs. The plan pins the current pilot/build receipts and each selected
run's report. A changed current proof, linked directory, altered receipt or
unexpected path aborts removal.

Keep the current successful paired pilot/full-ROM proof and one preceding
success intact, including source/header snapshots, changed-source controls and
raw outputs. Older successful runs retain their original compressed report,
compressed C and control inputs, and header hash receipts under ignored
`reports/pruned-build-runs/`; their large reproducible output directories are
removed. The retained report explicitly records that its working artifacts
were pruned. Failed or incomplete gates are held for deliberate review.

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
