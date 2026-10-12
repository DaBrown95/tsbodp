/* Shared distant pool: the intervening Thumb copy helper has its own extent.
 * PC-relative references preserve their displacement after the IWRAM copy. */
.text
.balign 4
.global irq_nested_mask_literal, irq_table_literal
irq_nested_mask_literal:
    .word 0x20f4
irq_table_literal:
    .word g_irq_table
