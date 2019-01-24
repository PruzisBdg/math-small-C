/*---------------------------------------------------------------------------------------------
|
|  FUNCTION:  Vec_WrapString
|
|  Stretches a 'string' over the top or bottom of 'in'; returns the 'string' as a vector
|  with the same number of points as 'in'.
|
|  PARAMETERS:  'string'   - the 'string' over 'in'
|               'in'       - source vector
|               'ctl'      - control flags
|
|                 Vec_WrapString_Over     - over the top of the curve
|                 Vec_WrapString_Under    - under the bottom of the curve
|
|     control flags are:
|
|	DATE		   AUTHOR            DESCRIPTION OF CHANGE
|	--------		-------------		-------------------------------------
|
----------------------------------------------------------------------------------------------*/

#include "vec.h"

/* Enable watch variables for use in PC Debugger */
//#define _DGG_WRAP_STRING

PUBLIC void Vec_WrapString( S_Vec *string, S_Vec const *in, U8 ctl )
{
   T_VecCols LVAR c;

   S16   LVAR gradDiv,          /* scale for best gradient range over curve        */
              x0, y0, y, inY,
              grad,             /* gradient of projection                          */
              gradStep,         /* stepsize for changing projection line gradient  */
              cutX,             /* the most recent intersection                    */
              minXStep,         /* smallest x segment length                       */
              startGradStep,    /* initial gradient at start of each segment       */
              minGradStep;      /* smallest gradient in converging on a tangent    */
   S32   LVAR l;
   U8    LVAR cut, wasCut;      /* flags to control search for tangent to curve    */

   #ifdef _DGG_WRAP_STRING

   S16   segCnt = 0;       /* number of segments traversed                    */
   S32   stepSum = 0;      /* sun gradient steps across all segments          */
   S32   prevStepSum = 0;  /* to get latest step interval                     */
   S32   evalCnt = 0;      /* total tangent points evaluated = work done      */

   S16   segs[50];         /* points each segment                             */
   S16   segSteps[50];     /* convergence steps each segment                  */
   S16   grads[50];        /* tangent gradient each segment                   */

   #endif

   /* Get optimum scaling for gradient. Assume that the curve we are trying to stretch
      around has a typical gradient of 2, when displayed with a 1:1 aspect ratio. The
      gradients we use in 'wrapping' the curve will be will run from say 2/10 to 2*10.
      Choose a gradient scaling which gives equal numerical headroom either side of
      the nominal gradient i.e such that a gradient = 2 is scaled to sqrt(32768) = 200(approx.)
   */
   #define _GradScale 500

   l = (_GradScale * (S32)in->cols) / _Vec_Max(in);    /* Gradient scale = 500 / aspect_ratio    */
   l = CLIP(l, 1, MAX_S16);                     /* Clip in case aspect ratio is extreme   */
   gradDiv = l;

   /* ------ Method:

      Starting at LHS, project a line to the right. Rotate the line until it makes
      a tangent to the curve. Fill the output vector with the straight line segment
      between start and tanget. Move start point to the tangent and project a 2nd line;
      find next tangent.. Repeat until at RHS of curve.
   */

   /* First set a lower limit on x-axis step. About 40 steps to traverse a curve. */
   minXStep = in->cols / 40;
   minXStep = MAX(minXStep, 1);     /* but at least 1 */

   /* Set the initial gradient stepping for the next segment search to be 1/4
      of 45deg (relative to 1:1 aspect ratio). Not the most efficient but simple
      and robust.
   */
   startGradStep = 2 * _GradScale / 2;
   startGradStep = MAX(startGradStep, 4);

   /* Set the minimum gradient step to 1/50th the initial gradient. This limits the numbers
      of steps required for a segment to converge to a tangent on the curve.
   */
   minGradStep = startGradStep / 50;
   minGradStep = MAX(minGradStep, 1);

   x0 = 0;                             /* start at LHS               */
   y0 = Vec_Read1(in, 0, x0);          /* Get start 'y'              */
   grad = 0;                           /* Initial line is horizontal */

   /* Loop until at RHS of curve */
   while(1)
   {
      gradStep = startGradStep;

      #ifdef _DGG_WRAP_STRING
      segCnt++;
      #endif

      wasCut = FALSE;         /* until cut the curve (below) */

      /* Loop until find line which is tangent to a point further up the curve */
      while(1)
      {
         #ifdef _DGG_WRAP_STRING
         stepSum++;
         #endif

         /* Make a test line at the current gradient, extending from current
            start point to RHS of curve.
         */
         for( c = x0 + 1, cut = FALSE; c < in->cols; c++ )  /* for each point on the line       */
         {
            #ifdef _DGG_WRAP_STRING
            evalCnt++;
            #endif

            y = y0 + (((S32)grad * (c - x0)) / gradDiv);    /* Get 'y' coord                    */

            inY = _Vec_Read1(in, 0, c);

            if( ((y < inY) && BCLR(ctl, _Vec_WrapString_Under)) ||
                ((y > inY) && BSET(ctl, _Vec_WrapString_Under)) )          /* coord below (above) the curve?   */
            {
               cut = TRUE;                                  /* then we cut the curve...         */
               cutX = c;                                    /* here.                            */

               if( (cutX - x0) < minXStep )
               {
                  cutX += minXStep;
                  cutX = MIN(cutX, in->cols - 1);
               }
               break;
            }
         }
         if( cut != wasCut ) gradStep /= 2;                 /* overshot tangent? => reduce step */

         if( gradStep < minGradStep ) break;                /* step tiny, got tangent           */

         if( !cut )                                         /* OR wrap under and below curve?   */
         {
            if(BSET(ctl, _Vec_WrapString_Under))
               { grad += gradStep; }
            else
               { grad -= gradStep; }
         }
         else
         {
            if(BSET(ctl, _Vec_WrapString_Under))
               { grad -= gradStep; }
            else
               { grad += gradStep; }
         }
         wasCut = cut;                                      /* Log above/below for this line    */
      }

      /* Got tangent, fill in line segment in the output vector */
      for( c = x0; c <= cutX; c++ )
      {
         y = y0 + (((S32)grad * (c - x0)) / gradDiv);
         Vec_Write1( string, y, 0, c);
      }

      #ifdef _DGG_WRAP_STRING

      segs[segCnt-1] = cutX - x0;
      segSteps[segCnt-1] = stepSum - prevStepSum;
      grads[segCnt-1] = grad;
      prevStepSum = stepSum;

      #endif

      if( cutX >= in->cols-1 )         /* reached RHS of curve?   */
         { break; }                    /* then done               */
      else
         { x0 = cutX; y0 = y; }        /* else segment end point becomes new start point - go again */
   }
}

 
