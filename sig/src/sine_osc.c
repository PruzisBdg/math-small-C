/*---------------------------------------------------------------------------
|
|                 Damped Sine Oscillator - Floating Point
|
|     The oscillator is:  y(0) = [2 * k * y(-1)] + y(-2) + x(0)
|
|     where:
|                         f(osc)
|           k = cos(2*PI* ------ )
|                           fs
|
|     Add damping by    y(-1) = g * y(-1)  and y(-2) = g * y(-2)
|
|--------------------------------------------------------------------------*/

#include "sine_osc.h"
#include "util.h"

/* -----------------------------------------------------------------------
|
|  SineOscF_Init()
|
|  Start oscillator 'q' with no output. Set gain to 'g0' and frequency 
|  from 'k'.
|
|--------------------------------------------------------------------------*/

PUBLIC void SineOscF_Init(S_SineOscF *q, float k0, float g0)
{
   ZeroBytesU8(q, sizeof(S_SineOscF));
   SineOscF_Update(q, k0, g0);
}

/* -----------------------------------------------------------------------
|
|  SineOscF_Update()
|
|  Set gain to 'g0' and frequency from 'k'.
|
|--------------------------------------------------------------------------*/

PUBLIC void SineOscF_Update(S_SineOscF *q, float k0, float g0) 
{ 
   q->k = k0; q->g = g0; 
}

/* -----------------------------------------------------------------------
|
|  SineOscF_Prime()
|
|  Do a running start with from 'n' as the peak input
|
|--------------------------------------------------------------------------*/

PUBLIC void SineOscF_Prime(S_SineOscF *q, S16 n)
{
   q->z1 = n;
   q->z2 = n;
}

/* -----------------------------------------------------------------------
|
|  SineOscF_Run()
|
|  Iterate the oscillator for on cycle with 'n' as the new input.
|
|  Returns the oscillator output.
|
|--------------------------------------------------------------------------*/

PUBLIC float SineOscF_Run(S_SineOscF *q, S16 n)
{
   float y;

   // 150usec @ 22MHz C8051
   y = q->g * ((q->k * q->z1) - q->z2 + n);
   q->z2 = q->g * q->z1;
   q->z1 = y;
   
   return y;
}

// ------------------------------- eof ----------------------------------------

 
