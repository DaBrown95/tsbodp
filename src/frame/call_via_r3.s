.syntax unified
.cpu arm7tdmi
.thumb
.section .text
.align 2
.global _call_via_r3
.type _call_via_r3, %function
.thumb_func
_call_via_r3:
    bx r3
    nop
.size _call_via_r3, . - _call_via_r3
