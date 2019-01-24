/*---------------------------------------------------------------------------
|
|                          Alpha / Beta Tracker
|
|
|
|
|
|
|   
|      Rev 1.0   May 19 2009 12:56:20   spruzina
|   Initial revision.
|  
|--------------------------------------------------------------------------*/

#ifndef ABTRACKER_H
#define ABTRACKER_H

#include "math_common.h"
#include "iirfilt1.h"
#include "systime.h"
#include "arith.h"

// Configures an S_ABTracker
typedef struct
{
   S16 dydtScale;                // dydt = dydtScale * (y - lastY) / since_lastY
   U8  k1,                       // y update filter coff
       k2;                       // dydt update filter coff
} S_ABTrackerCfg;

// An AB Tracker
typedef struct
{
   S_ABTrackerCfg CONST *cfg;    // (fixed) configuration for this tracker
   T_Timer        lastUpdate;    // time of the last tracker update
   U8             updateCnt;     // counts 1st few updates; is 0,1 or 2
   S16            y,             // position after the most recent update
                  dydt;          // drift after the most recent update
   S_IIR1         yFilt,         // y (postion) update filter
                  dyFilt;        // drift (dydt) update filter
} S_ABTracker;

PUBLIC void ABTracker_Init(S_ABTracker *t, S_ABTrackerCfg CONST *cfg);
PUBLIC void ABTracker_Update(S_ABTracker *t, S16 y);
PUBLIC S16  ABTracker_Read(S_ABTracker *t);
PUBLIC S16  ABTracker_Read_dydt(S_ABTracker *t);

#endif // ABTRACKER_H
