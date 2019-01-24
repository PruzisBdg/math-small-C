/*-------------------------------------------------------------------------------------------------
|
|  FUNCTION:  FIRFP_Run
|
|  Crunches new sample 'i' through floating-point FIR 'f'; returns one new 
|  filtered result.
|
-------------------------------------------------------------------------------------------------*/

#include "firfilt.h"

#ifdef _USE_ARRAY_INDICES
PUBLIC float FIRFP_Run( S_FIRFP * f, float i )
{

   U8    c;
   float acc;
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
      acc += f->buf[p] * f->coffs[coffs];         /* Accumulate coff * sample.     */
      
      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == 0 ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = 0; else f->put++;     /* wrap? */

   /* Return result */
   return acc;
}


#else
PUBLIC float FIRFP_Run( S_FIRFP * f, float i )
{

   U8       c;
   float    acc;
   float    *p;
   float    CONST *coffs;

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
      acc += *p * (*coffs);         	/* Accumulate coff * sample.     */

      /* The put ptr is at the last sample in the buffer. Go back from there. */
      if( p == f->buf ) p = f->end; else p--;  /* wrap? */
   }

   /* Now advance 'put' ptr to next empty slot */
   if( f->put >= f->end ) f->put = f->buf; else f->put++;     /* wrap? */

   /* Return result */
   return acc;
}

#endif // _USE_ARRAY_INDICES

// -------------------------------------- eof ------------------------------------------ 
