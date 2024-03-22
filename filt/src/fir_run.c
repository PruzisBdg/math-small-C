/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIR_Run
|
|  DESCRIPTION:
|
|     Crunches new sample 'i' through FIR 'f' and return one new filtered result.
|
|     If the result (in the accumulator) exceeds the range of S16, then clip
|     the result to the limits of S16.
|
|  PARAMETERS:    - 'f'  the filter
|                 - 'i'  new input sample
|
|  RETURNS:       - the filtered result
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"
#include "arith.h"
#include "common.h"

   #if _TOOL_IS == TOOL_CC430
#include "msp430x24x.h"
   #endif

#ifdef _USE_ARRAY_INDICES
PUBLIC S16 FIR_Run( S_FIR * f, S16 i )
{
   U8    c;
   U8    p, coffs;
   S32   acc;

   f->cfg.buf._s16[f->put] = i;        /* Add new 'i' */

   /* Get sum of products of coffs[] and buffer, starting from the most recent sample.
      Note that the filter runs BACK through the samples from the youngest. This allows
      the buffer to be longer than the filter, adding a delay if required.
   */
   for( c = f->cfg.taps,               /* for each tap                  */
        coffs = 0,                     /* forward from start of coffs   */
        p = f->put,                    /* backward from youngest sample */
        acc = 0;                       /* init accumulator              */
        c;
        c--, coffs++ )
   {
         #if _TOOL_IS == TOOL_CC430
      /* For MSP430H2xxx use the hardware multiplier. This has signed/unsigned 8/16bit and
         a 32bit MAC BUT... MAC is unsigned-only, can't use it for FIRs which use S16.
      */
      MPYS = f->cfg.coffs[coffs];                              /* Load for signed 16x16          */
      OP2 = f->cfg.buf._s16[p];                                /* 2nd operand triggers multiply. */
      acc += (((S32)RESHI << 16) + RESLO);                     /* Accumulate 32bit products      */
         #else
      // else straight 'C', compiler chooses implementation.
      acc += f->cfg.buf._s16[p] * (S32)f->cfg.coffs[coffs];    /* Accumulate coff * sample.     */
         #endif

      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == 0 ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = 0; else f->put++;     /* wrap? */

   /* Scale output, (maybe) clip if overrange and return result */

         #if _TOOL_IS == TOOL_CC430
   // For MSP430 hard-code >> 16, otherwise uses a SLOW shift-loop.
   if(f->cfg.rShift == 16) {
      acc = acc >> 16; }
   else {
      acc = acc >> f->cfg.rShift; }
         #else
   acc = acc >> f->cfg.rShift;
         #endif

   return
      f->cfg.flags.noOutClip == 1
         ? (S16)acc
         : ClipS32toS16(acc);
}


#else
PUBLIC S16 FIR_Run( S_FIR * f, S16 i )
{

   U8    c;
   S32   acc;
   S16   *p;
   S16   CONST *coffs;

   *f->put = i;  /* Add new 'i' */

   /* Get sum of products of coffs[] and buffer, starting from the most recent sample.
      Note that the filter runs BACK through the samples from the youngest. This allows
      the buffer to be longer than the filter, adding a delay if required.
   */
   for( c = f->cfg.taps,                     /* for each tap                  */
        coffs = &f->cfg.coffs[0],            /* forward from start of coffs   */
        p = f->put,                          /* backward from youngest sample */
        acc = 0;                             /* init accumulator              */
        c;
        c--, coffs++ )
   {
      if(f->cfg.flags.checkOverrange == 0)   /* Omit accumulator overrange check */
      {
         acc += *p * (S32)*coffs;            /* then just add coff*smpl       */
      }
      else                                   /* else also test if add overranges acc */
      {
         S32 prev, term;

         prev = acc;
         term = *p * (S32)*coffs;            /* Accumulate coff * sample.     */
         acc += term;

         if( term > 0 )                      /* Added positive number.        */
         {
            if( acc < prev )                 /* Sign reversal? */
            {
               acc = MAX_LONG;               /* then clip acc at +Max         */
               break;
            }
         }
         else if( acc > prev )               /* else added negative number -> overranged? */
         {
            acc = MAX_LONG;                  /* then clip acc at -Max         */
            break;
         }
      }

      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == f->cfg.buf._s16 ) p = f->end; else p--;  /* wrap? */
   } // ends: for( c = f->cfg.taps ...

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = f->cfg.buf._s16; else f->put++;     /* wrap? */

   /* Scale output, clip if overrange and return result */
   acc = acc >> f->cfg.rShift;
   return
      f->cfg.flags.noOutClip == 1
         ? (S16)acc
         : ClipS32toS16(acc);
}

#endif

// -------------------------------------- eof -------------------------------------------
