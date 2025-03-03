#ifndef MATH_COMMON_H
#define MATH_COMMON_H

#include "bldcfg.h"
#include "spj_stdint.h"

#define RAM_IS
#define rIDATA
#define CONST_FP const
#define GENERIC
#define CODE const

// ---- Changes to SysTime
#define T_STime T_ShortTime		// 16-bit time
#define        _ResetTimer(timer)  { (timer) = _Now(); }
#define ElapsedS(timer) (Elapsed_S(&(timer)))
#define T_LTime T_Time

/* ---------------------------- Bits / Flags ------------------------------------ */

/* To manipulate a bit at a given (bit) position */
#define _BitM(bit) (1 << (bit))
#define _notB(bit)  0

/*   To manipulate bits with a bit mask.  */
#define SETB(reg,mask) {(reg) |= (mask);}
#define CLRB(reg,mask) {(reg) &= ~(mask);}

#define BSET(reg,mask) ((reg) & (mask))
#define BCLR(reg,mask) (!((reg) & (mask)))

#define ALL_SET(v,m) (((v)&(m))==(m))
#define ANY_SET(v,m) (((v)&(m))!=0)
#define NOT_SET(v,m) (((v)&(m))==0)

#define CLIP(n, min, max) (((n)<(min))?(min):(((n)>(max))?(max):(n)))

#endif // MATH_COMMON_H
