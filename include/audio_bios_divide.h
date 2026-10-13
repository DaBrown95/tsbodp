/*
 * Adapted from FastIntDivide and FastIntDivideRem in Krawall's lib/tools.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: separate ARM and Thumb wrappers, project names and coverage markers.
 * Licensed under GNU LGPL version 2.1 or, at your option, any later version.
 * Distributed without any warranty; see licenses/Krawall-LGPL-2.1.txt.
 */
#ifndef AUDIO_BIOS_DIVIDE_H
#define AUDIO_BIOS_DIVIDE_H
/* Explicit BIOS division glue. The seven instructions at each inline site are
 * verified separately and excluded from matching C byte coverage. The labels
 * emit no bytes and let the linked ELF prove the exact accounting boundaries. */
static __inline__ void audio_bios_divide_remainder(int numerator, int denominator,
                                                  int *result, int *remainder)
{
 __asm__ volatile (
  "__tsbodp_glue_audio_divide_begin_%=:\n"
  " mov r0,%2\n"
  " movs r1,%3\n"
  " swine 0x60000\n"
  " ldr r2,%0\n"
  " str r0,[r2]\n"
  " ldr r2,%1\n"
  " str r1,[r2]\n"
  "__tsbodp_glue_audio_divide_end_%=:\n"
  : "=m" (result), "=m" (remainder)
  : "r" (numerator), "r" (denominator)
  : "r0", "r1", "r2", "r3"
 );
}
/* Explicit Thumb BIOS division glue. The six instructions at each inline site
 * are verified separately and excluded from matching C coverage. The branch
 * preserves the observed zero-denominator handoff; it is not a C division. */
static __inline__ void audio_bios_divide_thumb(int numerator, int denominator,
                                              int *result)
{
 __asm__ volatile (
  "__tsbodp_glue_audio_divide_begin_%=:\n"
  " mov r0,%1\n"
  " mov r1,%2\n"
  " beq .Ltsbodp_divide_skip_%=\n"
  " swi 6\n"
  ".Ltsbodp_divide_skip_%=:\n"
  " ldr r2,%0\n"
  " str r0,[r2]\n"
  "__tsbodp_glue_audio_divide_end_%=:\n"
  : "=m" (result)
  : "r" (numerator), "r" (denominator)
  : "r0", "r1", "r2", "r3"
 );
}
#endif
