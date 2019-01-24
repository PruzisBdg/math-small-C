
#include <stdio.h>

#pragma LARGE


#define _IU_VolPcent(n)  ((int)(100.0 * (n)))

int co2_CorrectFor_N2O_O2( int co2In, int n2o, int o2 ) {

   float co2f, n2of, o2f, co2Pwr3;

   /* Concentrations into the IB2 are in '_IU_VolPcent'. Result is in '_IU_VolPcent'. So the
      the terms in the equation which are added together must each be normalised to '_IU_VolPcent'.
      Each Constant must be scaled to match whatever it is added to.

      Make these powers of _IU_VolPcent(1) for shorthand.
   */
   #define _vp1 ((float)_IU_VolPcent(1))
   #define _vp2 (_vp1 * _vp1)
   #define _vp3 (_vp1 * _vp1 * _vp1)
   #define _vp4 (_vp1 * _vp1 * _vp1* _vp1)

   // k1 - k5 from the spreadsheet. See above.
   #define k1 (7.00E-4)
   #define k2 (2.20E-4)
   #define k3 (-0.94)
   #define k4 (25000.0)
   #define k5 (-1.0)

   // These variables are used multiple times, so convert them to float now.
   co2f = (float)co2In;
   n2of = (float)n2o;
   o2f  = (float)o2;

   // CO2^3 is used twive. make it here.
   co2Pwr3 = co2f * co2f * co2f;

   return (int)
      (
         co2f                                // the uncorrected Co2
         -                                   // minus
         (                                   // the cross-effect from N2O
            (k1/_vp4) * co2f * n2of 
            * 
            ( 
               (1.0*_vp3) 
               + 
               ( 
                  k2 * co2f * n2of
                  *
                  (
                     (k5*_vp1) + co2f
                  )
               )
            ) 
         )
         +                                   // plus
         (                                   // the cross-effects from O2.
            (k3*_vp1) * o2f * co2Pwr3 
            / 
            ( (k4*_vp4) + (o2f * co2Pwr3))
         )
      );
}

void main(void)
{
   int res1, res2, res3;
   
   res1 = co2_CorrectFor_N2O_O2(_IU_VolPcent(10), _IU_VolPcent(0), _IU_VolPcent(0) );
   res2 = co2_CorrectFor_N2O_O2(_IU_VolPcent(11.5), _IU_VolPcent(80), _IU_VolPcent(0) );
   res3 = co2_CorrectFor_N2O_O2(_IU_VolPcent(10), _IU_VolPcent(0), _IU_VolPcent(80) );

   printf("%d  %d  %d\r\n", res1, res2, res3);

   while(1);
}

// -------------------------- eof ------------------------------------------
