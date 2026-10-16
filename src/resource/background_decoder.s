/* Native background resource decoder, ROM 0x2ec..0x618.
 * Copied execution: IWRAM 0x03003370..0x0300369c.
 *
 * Independently reconstructed from the fixed reference disassembly and
 * instruction/dataflow review. Positive whole-routine assembly lineage is
 * documented in docs/RESOURCE_BACKGROUND_DECODER.md. The historical
 * Pucrunch ARM source is provenance evidence only; its text is not reused.
 * This is an adapted decoder, not an exact identification of that release.
 *
 * Entry: r0 compressed input, r1 output, r2 optional decoded-size pointer.
 * Return: original callee-preserved state restored; optional size written.
 * Private readers share r0 cursor, r5 value, r8 sentinel buffer, r9 count.
 * One-bit refill returns CPSR.C; it must not materialize a C-ABI result.
 * Main state: r2 packed widths, r4 escape prefix, r6 length, r7 copy cursor,
 * r10 pending output byte, r11 saved escape/high length/halfword count,
 * ip pending-byte flag. Instruction flags and conditional forms are semantic.
 */
.syntax unified
.cpu arm7tdmi
.arm
.text
.balign 4, 0

.equ DECODER_STACK_BYTES, 36
.equ GAMMA_BIT_LIMIT, 8
.equ LONG_RLE_THRESHOLD, 128
.equ RLE_CODE_LIMIT, 32
.equ END_OF_STREAM_CODE, 255

.global resource_background_decoder
.type resource_background_decoder, %function
resource_background_decoder:
    push    {r1, r2, r4-r12, lr}
    sub     sp, sp, #DECODER_STACK_BYTES

    @ Header bytes: table storage size, initial escape, extra distance bits,
    @ escape width. Keep the native word loads and packed parameter register.
    ldr     r11, [r0], #4
    mov     r5, #255
    and     r3, r5, r11
    and     r4, r5, r11, lsr #8
    lsr     r2, r11, #16
    lsr     r5, r2, #8
    rsb     r5, r5, #8
    add     r2, r5, r2, lsl #8
    add     r5, sp, #4
.Lcopy_rank_table:
    ldr     r11, [r0], #4
    str     r11, [r5], #4
    subs    r3, r3, #4
    bne     .Lcopy_rank_table
    mov     r8, #0x80000000
    mov     ip, #0
    b       .Lnext_token

    @ Gamma prefix length: the first three tests are unrolled in native code.
    @ Every exhausted word is refilled with a low sentinel and returned carry.
.Lread_gamma:
    mov     r5, #1
    mov     r9, r5
    adds    r8, r8, r8
    ldreq   r8, [r0], #4
    adcseq  r8, r8, r8
    blo     .Lreader_count_down
    add     r9, r9, #1
.Lgamma_more_prefix:
    adds    r8, r8, r8
    ldreq   r8, [r0], #4
    adcseq  r8, r8, r8
    blo     .Lreader_count_down
    add     r9, r9, #1
    adds    r8, r8, r8
    ldreq   r8, [r0], #4
    adcseq  r8, r8, r8
    blo     .Lreader_count_down
    add     r9, r9, #1
    adds    r8, r8, r8
    ldreq   r8, [r0], #4
    adcseq  r8, r8, r8
    blo     .Lreader_count_down
    add     r9, r9, #1
    cmp     r9, #GAMMA_BIT_LIMIT
    bne     .Lgamma_more_prefix
    subs    r9, r9, #1
    bne     .Lappend_bits
    bx      lr

    @ Caller entered with Z=C=1 after consuming the sentinel. Preserve the
    @ native conditional ADCS; BCC or ADC in the caller uses its carry result.
.Lrefill_one_bit:
    ldr     r8, [r0], #4
    adcseq  r8, r8, r8
    bx      lr

    @ Fast extraction when the sentinel does not cross the requested width.
.Lappend_bits:
    lsls    r3, r8, r9
    beq     .Lreader_bit_loop
    rsb     r3, r9, #32
    lsr     r3, r8, r3
    orr     r5, r3, r5, lsl r9
    lsl     r8, r8, r9
    bx      lr
.Lread_bits:
    lsls    r5, r8, r9
    beq     .Lreader_bit_loop
    rsb     r5, r9, #32
    lsr     r5, r8, r5
    lsl     r8, r8, r9
    bx      lr
.Lread_byte_slow:
    mov     r9, #8
.Lreader_bit_loop:
    adds    r8, r8, r8
    ldreq   r8, [r0], #4
    adcseq  r8, r8, r8
    adc     r5, r5, r5
.Lreader_count_down:
    subs    r9, r9, #1
    bne     .Lreader_bit_loop
    bx      lr

    @ The previous escape becomes a literal prefix as its replacement is read.
.Lchange_escape:
    lsrs    r9, r2, #16
    blne    .Lread_bits
    mov     r11, r4
    mov     r4, r5
    mov     r5, r11
.Lliteral_suffix:
    ands    r9, r2, #255
    blne    .Lappend_bits
    eors    ip, ip, #1
    movne   r10, r5
    addeq   r10, r10, r5, lsl #8
    strheq  r10, [r1], #2
.Lnext_token:
    mov     r5, #0
    mov     r11, #0
    lsrs    r9, r2, #16
    blne    .Lread_bits
    cmp     r5, r4
    bne     .Lliteral_suffix
    bl      .Lread_gamma
    mov     r6, r5
    lsrs    r5, r5, #1
    bne     .Llong_lz
    adds    r8, r8, r8
    bleq    .Lrefill_one_bit
    blo     .Llz_low_byte
    adds    r8, r8, r8
    bleq    .Lrefill_one_bit
    blo     .Lchange_escape

    @ RLE: low length, optional high length, then rank or literal byte code.
    bl      .Lread_gamma
    mov     r6, r5
    cmp     r5, #LONG_RLE_THRESHOLD
    blo     .Lrle_byte_code
    adds    r8, r8, r8
    bleq    .Lrefill_one_bit
    adc     r6, r5, r5
    and     r6, r6, #255
    bl      .Lread_gamma
    sub     r11, r5, #1
.Lrle_byte_code:
    bl      .Lread_gamma
    cmp     r5, #RLE_CODE_LIMIT
    addlo   r5, r5, #3
    ldrblo  r5, [sp, r5]
    movhs   r9, #3
    blhs    .Lappend_bits
    and     r5, r5, #255
    add     r6, r6, #1
    add     r6, r6, r11, lsl #8
.Lfill_byte:
    tst     ip, #1
    addne   r10, r10, r5, lsl #8
    strhne  r10, [r1], #2
    subne   r6, r6, #1
    add     r10, r5, r5, lsl #8
.Lfill_pair_count:
    and     r5, r6, #1
    lsrs    r6, r6, #1
.Lfill_pairs:
    strhne  r10, [r1], #2
    subs    r6, r6, #1
    bgt     .Lfill_pairs
    movs    ip, r5
    andne   r10, r10, #255
    b       .Lnext_token

    @ LZ distance high part, optional extension, then its low byte.
.Llong_lz:
    bl      .Lread_gamma
    cmp     r5, #END_OF_STREAM_CODE
    beq     .Lfinish_output
    sub     r11, r5, #1
    lsr     r9, r2, #8
    ands    r9, r9, #255
    beq     .Llz_low_byte
    lsl     r11, r11, r9
    bl      .Lread_bits
    orr     r11, r11, r5
.Llz_low_byte:
    lsls    r5, r8, #8
    lsrne   r5, r8, #24
    lslne   r8, r8, #8
    bleq    .Lread_byte_slow
    add     r11, r5, r11, lsl #8
    sub     r7, r1, r11
    sub     r7, r7, #1
    add     r7, r7, ip
    add     r6, r6, #1

    @ Adjacent source can refer to the pending byte not yet stored to VRAM.
    sub     r5, r1, r7
    cmp     r5, #1
    bgt     .Lcopy_forward
    bne     .Lcopy_cached_byte
    ldrb    r5, [r7], #1
    tst     ip, #1
    beq     .Lfill_byte
    add     r10, r10, r5, lsl #8
    strh    r10, [r1], #2
    sub     r6, r6, #1
    b       .Lfill_pair_count
.Lcopy_cached_byte:
    tst     ip, #1
    ldrbeq  r5, [r7], #1
    andne   r5, r10, #255
    b       .Lfill_byte

    @ Peel an odd source byte before the halfword forward-copy loops.
.Lcopy_forward:
    tst     r7, #1
    beq     .Lcopy_pair_count
    ldrb    r5, [r7], #1
    eors    ip, ip, #1
    movne   r10, r5
    addeq   r10, r10, r5, lsl #8
    strheq  r10, [r1], #2
    subs    r6, r6, #1
.Lcopy_pair_count:
    lsrs    r11, r6, #1
    beq     .Lcopy_last_byte
    tst     ip, #1
    bne     .Lcopy_pairs_pending
.Lcopy_pairs:
    ldrh    r5, [r7], #2
    strh    r5, [r1], #2
    subs    r11, r11, #1
    bne     .Lcopy_pairs
    b       .Lcopy_tail
.Lcopy_pairs_pending:
    ldrh    r5, [r7], #2
    add     r5, r10, r5, lsl #8
    strh    r5, [r1], #2
    lsr     r10, r5, #16
    subs    r11, r11, #1
    bne     .Lcopy_pairs_pending
    mov     ip, #1
.Lcopy_tail:
    tst     r6, #1
    beq     .Lnext_token
.Lcopy_last_byte:
    ldrb    r5, [r7], #1
    eors    ip, ip, #1
    movne   r10, r5
    addeq   r10, r10, r5, lsl #8
    strheq  r10, [r1], #2
    b       .Lnext_token

    @ Keep native odd-byte flush and nullable decoded-size behavior exactly.
.Lfinish_output:
    tst     ip, #1
    strbne  r10, [r1], #1
    add     sp, sp, #DECODER_STACK_BYTES
    pop     {r0, r2, r4-r12, lr}
    cmp     r2, #0
    bxeq    lr
    subs    r1, r1, r0
    str     r1, [r2]
    bx      lr
.size resource_background_decoder, .-resource_background_decoder
.balign 4, 0
