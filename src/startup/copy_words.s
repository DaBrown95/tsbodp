/* The reset-only copy ABI takes source in r1, destination in r2 and exclusive
 * destination end in r4. It preserves r4 and LR, clobbering r0/r1/r2/r3 and flags.
 * The non-C r4 input and direct reset callers establish an assembly startup
 * interface. Leaf code without a stack frame alone would not prove origin. */
.syntax unified
.thumb
.text
.balign 2
.global startup_copy_words
.type startup_copy_words, %function
.thumb_func
startup_copy_words:
    subs r3, r4, r2
    beq .Ldone
    movs r0, #3
    adds r3, r3, r0
    bics r3, r0
    beq .Ldone
.Lcopy:
    ldmia r1!, {r0}
    stmia r2!, {r0}
    subs r3, #4
    bne .Lcopy
.Ldone:
    bx lr
.size startup_copy_words, .-startup_copy_words
.balign 4, 0
