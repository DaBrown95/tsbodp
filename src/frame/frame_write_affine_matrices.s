/* Observed Thumb BIOS handoff. Explicit low-level glue; excluded from C. */
.syntax unified
.thumb
.text
.global frame_write_affine_matrices
.type frame_write_affine_matrices, %function
.thumb_func
frame_write_affine_matrices:
    svc #0x0f
    bx lr
.size frame_write_affine_matrices, .-frame_write_affine_matrices
