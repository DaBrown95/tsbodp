.syntax unified
.cpu arm7tdmi
.thumb
.section .text
.align 2
.global _call_via_r1
.type _call_via_r1, %function
.thumb_func
_call_via_r1:
    bx r1
    nop
.size _call_via_r1, . - _call_via_r1
