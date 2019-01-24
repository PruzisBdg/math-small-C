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
//#include <intrins.h>

#ifdef _USE_ARRAY_INDICES
PUBLIC S16 FIR_Run( S_FIR * f, S16 i )
{

   U8    c;
   S32   acc;
   U8    p, coffs;

   f->buf[f->put] = i;  /* Add new 'i' */

   /* Get sum of products of coffs[] and buffer, starting from the most recent sample. 
      Note that the filter runs BACK through the samples from the youngest. This allows 
      the buffer to be longer than the filter, adding a delay if required.
   */
   for( c = f->taps,                   /* for each tap                  */
        coffs = 0,                     /* forward from start of coffs   */
        p = f->put,                    /* backward from youngest sample */
        acc = 0;                       /* init accumulator              */
        c; 
        c--, coffs++ ) 
   {
      acc += f->buf[p] * (S32)f->coffs[coffs];         /* Accumulate coff * sample.     */
      
      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == 0 ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = 0; else f->put++;     /* wrap? */

   /* Scale output, clip if overrange and return result */
   return ClipS32toS16(acc >>  f->rShift);
}


#else
PUBLIC S16 FIR_Run( S_FIR * f, S16 i )
{

   U8    c;
   S32   acc, prev, term;
   S16   *p;
   S16   CONST *coffs;

   *f->put = i;  /* Add new 'i' */

   /* Get sum of products of coffs[] and buffer, starting from the most recent sample. 
      Note that the filter runs BACK through the samples from the youngest. This allows 
      the buffer to be longer than the filter, adding a delay if required.
   */
   for( c = f->taps,                   /* for each tap                  */
        coffs = &f->coffs[0],          /* forward from start of coffs   */
        p = f->put,                    /* backward from youngest sample */
        acc = 0;                       /* init accumulator              */
        c; 
        c--, coffs++ ) 
   {
      prev = acc; 
      term = *p * (S32)*coffs;         /* Accumulate coff * sample.     */
      acc += term;

      if( term > 0 )                   /* Check for overrange.          */        
      {                 
         if( acc < prev ) 
         {
            acc = MAX_LONG;
            break;
         }
      }
      else if( acc > prev ) 
      {
         acc = MAX_LONG;
         break;
      }

      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == f->buf ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = f->buf; else f->put++;     /* wrap? */

   /* Scale output, clip if overrange and return result */
   return ClipS32toS16(acc >> f->rShift);
}

#endif

// -------------------------------------- eof ------------------------------------------- 
