/*---------------------------------------------------------------------------
|
|                 Damped Sine Oscillator - Floating Point
|
|
|
|
|
|
|   
|      Rev 1.0   May 19 2009 12:56:30   spruzina
|   Initial revision.
|  
|--------------------------------------------------------------------------*/

#ifndef SINEOSC_H 
#define SINEOSC_H

#include "common.h"

typedef struct
{
   float z1, z2,     // samples s(n-1) s(n-2)
         k,          // sets frequency,   k = cos(2*PI*fosc/fs)
         g;          // damping
} S_SineOscF;

PUBLIC void SineOscF_Init(S_SineOscF *q, float k0, float g0);
PUBLIC void SineOscF_Update(S_SineOscF *q, float k0, float g0);
PUBLIC float SineOscF_Run(S_SineOscF *q, S16 n);
PUBLIC void SineOscF_Prime(S_SineOscF *q, S16 n);

#endif // SINEOSC_H
