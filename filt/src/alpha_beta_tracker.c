/*---------------------------------------------------------------------------
|
|                          Alpha / Beta Tracker
|
|  Given a series of samples at irregular intervals an estimator provides an 
|  estimate of same at some time after the last sample.
|
|     Given:
|        - a new sample                                        - Yn
|        - post-priori estimate of the of the variable at 
|          the last sample point                               - Y
|        - estimate of 1st derivative at last sample point     - dYdt
|
|     Do the following:
|
|     1. A-priori estimate of var at this time:
|
|           Ye = Y + dYdt*time since last sample
|
|     2. A-priori estimate dYdt.
|
|           dYe = (Yn - Y) / time since last sample.
|
|     3. Post-priori estimate of dY/dt based on error between previous (post-
|        priori) estimate and the new a-priori one.
|
|           dYdt = dYdt + k1*(dYe - dYdt)
|
|     4. Post-priori estimate of Y based on error between new sample and
|        the a-priori estimate.
|
|           Y = Ye + k2*(Yn - Ye)
|
|  k1, k2 determine the sensitivity of the outputs Y, dYdt to the new data; larger 
|  k's cause the outputs to track input changes more promptly at the expense
|  of rejecting noise in the sequence of incomiong samples.
|
|--------------------------------------------------------------------------*/

#include "math_common.h"
#include "iirfilt1.h"
#include "systime.h"
#include "arith.h"
#include "abtracker.h"

/*-----------------------------------------------------------------------------------------
|
|  ABTracker_Init()
|
|  Initialise tracker 't' from 'cfg'.
|
------------------------------------------------------------------------------------------*/

PUBLIC void ABTracker_Init(S_ABTracker *t, S_ABTrackerCfg CONST *cfg)
{
   t->cfg = cfg;
   IIR1_Init( &t->yFilt, cfg->k1 );
   IIR1_Init( &t->dyFilt, cfg->k2 );
   t->updateCnt = 0;
}

/*-----------------------------------------------------------------------------------------
|
|  ABTracker_Update()
|
|  Update the tracker with new sample 'n'
|
------------------------------------------------------------------------------------------*/

PUBLIC void ABTracker_Update(S_ABTracker *t, S16 y)
{
   S16 dye;
   
   if( Elapsed(&t->lastUpdate) == 0) return;       // no time since last update? then don't do this one
   
   if(!t->updateCnt)                               // 1st sample for tracker
   {
      t->y = IIR1_LPass_Prime(&t->yFilt, y);       // so 'y' estimate is the whole 1st sample
      t->dydt = 0;                                 // and initial drift = 0
   }
   else                                            // else 2nd sample or more
   {
                                                   // A-priori 'dy/dt'
      dye = ClipS32toS16((t->cfg->dydtScale * (S32)AplusBS16(y, -t->y)  ) / Elapsed(&t->lastUpdate));
   
      if(t->updateCnt == 1)                        // 1st sample?
      {                                            // then post-priori dy/dt is the whole 'dye'
         t->dydt = IIR1_LPass_Prime(&t->dyFilt, dye);  
      }
      else                                         // else 2nd sample onwards
      {                                            // so post-priori dy/dt old dy/dt plus part of new
         t->dydt = IIR1_LPass_Run(&t->dyFilt, dye);
      }                                            // post-priori 'y'
      t->y = IIR1_LPass_Run(&t->yFilt, ABTracker_Read(t));
   }
   
   _ResetTimer(t->lastUpdate);                     // Mark the time of this update
   if(t->updateCnt < 2) t->updateCnt++;            // bump update cnt, only needs to be 0,1 or 2
}

/*-----------------------------------------------------------------------------------------
|
|  ABTracker_Read()
|
|  Return the current output of tracker 't'
|
------------------------------------------------------------------------------------------*/

PUBLIC S16 ABTracker_Read(S_ABTracker *t)
{
   return AplusBS16(t->y, ClipS32toS16(t->dydt * (S32)Elapsed(&t->lastUpdate) / t->cfg->dydtScale));
}


/*-----------------------------------------------------------------------------------------
|
|  ABTracker_Read_dydt()
|
|  Return the current dy/dt of tracker 't'
|
------------------------------------------------------------------------------------------*/

PUBLIC S16  ABTracker_Read_dydt(S_ABTracker *t)
{
   return t->dydt;
}

// ------------------------------ eof ---------------------------------------

 
