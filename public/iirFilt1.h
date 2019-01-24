 /*---------------------------------------------------------------------------
|
|                  1st-order IIR filters
|
|
|
|
|
|
|
|      Rev 1.2   Apr 01 2011 15:18:34   spruzina
|   Adds IIR1_Read() to read a filter without cranking it.
|
|      Rev 1.1   Aug 20 2009 08:32:32   spruzina
|   Added 'float' versions of the IIR coefficient macros, for range-checkin. e.g '_IIR1_HztoCoff_float()'.
|
|      Rev 1.0   May 19 2009 12:56:26   spruzina
|   Initial revision.
|
|--------------------------------------------------------------------------*/

#ifndef IIRFILT1_H
#define IIRFILT1_H

/* If basic types are supplied by the Host project instead \public\common.h then don't
   resupply them from common.h.
*/
#ifndef _BASIC_TYPES_FROM_HOST_PROJECT
   #include "math_common.h"
#endif


/* ------------------- Macros to generate filter coffs ------------------------------------

   Derives 'm' for a 1st order IIR filter of the form

      y(n+1) = y(n) - k * y(n) + k * x(n)   where 0 < k < 1

   'fo' is the desired cutoff freq; 'rate' is the sample rate for the filter

   A 1st order IIR has an exponential step response:

      y = yo(1 - exp(-t/Tc))

   where 'Tc' is the time constant.

   For a 1st order IIR

      y(n) = (1-k)^n

   If these two are equivalent:

      (1-k)^n = exp(-t/Tc)  => k = exp(-t/n*Tc)

   At t = Tc, n = Fs * Tc where Fs = sample freq

      => k = 1 - exp(-1/Fs*Tc)

   The filter corner freq is fo = 1/(2*PI*Tc)

      => k = 1 - exp(-2*PI*fo/Fs)

   The IIR filters are implemented as:

      y(n+1) = y(n) - y(n)/m + x(n)/m  where m = 1/k

      => m = 1 / (1 - exp(-2*PI*fo/Fs))

   Expanding to 2 terms gives:

      m = 1 / 1 - (1 - p + p^2/2.. )            exp(x) = x + x^2/2! + x^3/3!....

        = 1 / p - p^2/2    where p = 2*PI*fo/Fs

   For any p, 2-term truncations adds less error to 'm' than that due sampling.

   0.5 is added to compensate for roundown.
*/

// The '_float' versions are for range-checking with ASSERT

#define _IIR1_HztoCoff(fo, rate) ((S16)( 0.5 + (1.0/( ((2.0*PI*(fo))/(rate)) - (2.0*PI*PI*(fo)*(fo)/((rate)*(rate))) )) ))
#define _IIR1_HztoCoff_float(fo, rate) ( 0.5 + (1.0/( ((2.0*PI*(fo))/(rate)) - (2.0*PI*PI*(fo)*(fo)/((rate)*(rate))) )) )

#define _IIR1_SecstoCoff(tc, rate) ((S16)( 0.5 + (1.0/( (1.0/((tc)*(rate))) - (1.0/(2.0*(tc)*(tc)*(rate)*(rate))) )) ))
#define _IIR1_SecstoCoff_float(tc, rate) ( 0.5 + (1.0/( (1.0/((tc)*(rate))) - (1.0/(2.0*(tc)*(tc)*(rate)*(rate))) )) )

#define _IIR1_SecstoCoff_Intvl(tc, intvl) ((S16)( 0.5 + (1.0/( ((float)(intvl)/(tc)) - (((intvl)*(intvl))/(2.0*(tc)*(tc))) )) ))
#define _IIR1_SecstoCoff_Intvl_float(tc, intvl) ( 0.5 + (1.0/( ((float)(intvl)/(tc)) - (((intvl)*(intvl))/(2.0*(tc)*(tc))) )) )





/* -------------------------- Filters as functions ------------------------------ */

typedef struct
{
   S32 acc;
   U8  div;    // the filter coff
} S_IIR1;

// Both high and low pass
PUBLIC void IIR1_Init( S_IIR1 RAM_IS *f, U8 div );
PUBLIC S16  IIR1_InitVal( S_IIR1 RAM_IS *f, U8 div, S16 initVal );
PUBLIC S16  IIR1_Rescale( S_IIR1 RAM_IS *f, U8 newDiv );
PUBLIC U8   IIR1_GetCoff( S_IIR1 RAM_IS *f );
PUBLIC S16  IIR1_Read( S_IIR1 RAM_IS *f );

// Low pass
PUBLIC S16 IIR1_LPass_Run( S_IIR1 RAM_IS *f, S16 in );
PUBLIC S16 IIR1_LPass_RunNewScale( S_IIR1 RAM_IS *f, S16 in, U8 newDiv );
PUBLIC S16 IIR1_LPass_Prime( S_IIR1 RAM_IS *f, S16 in );

// High pass
PUBLIC S16 IIR1_HPass_Run( S_IIR1 RAM_IS *f, S16 in );
PUBLIC S16 IIR1_HPass_Prime( S_IIR1 RAM_IS *f, S16 init_dy );





/* --------------------------- Filters Inline ------------------------------------- */

/* ------------------------------- Low pass --------------------------------------------

   y(n+1) = y(n) - k*(y(n) + k*x(n+1)   where 0 < k < 1

   To avoid roundoff errors in integer arithmetic these are implemented with a long accumulator

      y(n+1) = acc(n+1)/m = (acc(n) - acc(n)/m + x(n)) / m

   where m = 1/k

*/

// Runs IIR, returns y(n+1)
#define _IIR1_LPass_Run(acc, x, m) (((acc) = ((acc) - ((acc)/(m)) + (x))) / (m))

// N.B does not return y
#define _IIR1_LPass_Tunable(acc, x, m) \
   (acc) = ((acc) - ((acc)/(m)) + (((S32)(x) << 8)/(m)))


/* --------------------------------- High pass -------------------------------------- */

#define _IIR1_HPass_Run(acc, x, m)   ((x) - _IIR1_LPass_Run((acc), (x), (m)))



// ------------------------- 1st order IIR vector filter ------------------------------

typedef struct
{
   S32 *acc;      // accumulators, one for each channel
   U8  size,      // vector size
       div;       // filter div for each channel
} S_IIR1Vec;

PUBLIC void IIR1Vec_LPass_Init(S_IIR1Vec CONST *f);
PUBLIC void IIR1Vec_LPass_Run(S_IIR1Vec CONST *f, S16 *out, S16 *in );

#endif // IIRFILT1_H

// -------------------------------- eof ----------------------------------------------


