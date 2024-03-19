/*============================================================================

    fourierf.c  -  Don Cross <dcross@intersrv.com>

    http://www.intersrv.com/~dcross/fft.html

    Contains definitions for doing Fourier transforms
    and inverse Fourier transforms.

    This module performs operations on arrays of 'float'.

    Revision history:

1998 September 19 [Don Cross]
    Updated coding standards.
    Improved efficiency of trig calculations.

============================================================================*/

#include "ddcmath.h"
#include "fourier.h"
typedef unsigned int uint32_t;


void fft_float (
    unsigned  NumSamples,
    int       InverseTransform,
    uint32_t    *RealIn,     //float
    uint32_t    *ImagIn,//float
    uint32_t    *RealOut,//float
    uint32_t    *ImagOut )  //float
{
    unsigned NumBits;    /* Number of bits needed to store indices */
    unsigned i, j, k, n;
    unsigned BlockSize, BlockEnd;

    uint32_t angle_numerator = fpmul(0x40000000,DDC_PI);//double angle_numerator = 2.0 * DDC_PI;
    uint32_t tr, ti;     /* double: temp real, temp imaginary  */



    if ( InverseTransform )
        angle_numerator = fpsub(0,angle_numerator);

    NumBits = NumberOfBitsNeeded ( NumSamples );

    /*
    **   Do simultaneous data copy and bit-reversal ordering into outputs...
    */

    for ( i=0; i < NumSamples; i++ )
    {
        j = ReverseBits ( i, NumBits );
        RealOut[j] = RealIn[i];
        ImagOut[j] =  ImagIn[i];
    }

    /*
    **   Do the FFT itself...
    */

    BlockEnd = 1;
    for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
    {
        /*double*/ uint32_t delta_angle = fpdiv(angle_numerator,int_to_float(BlockSize));       
        /*double*/ uint32_t sm2 = fp_Sin ( fpmul(0xc0000000 , delta_angle) );//sin ( -2 * delta_angle );
        /*double*/ uint32_t sm1 = fp_Sin ( fpsub(0,delta_angle) );//sin ( -delta_angle );
        /*double*/ uint32_t cm2 = fp_Cos ( fpmul(0xc0000000 , delta_angle) );//cos ( -2 * delta_angle );
        /*double*/ uint32_t cm1 = fp_Cos ( fpsub(0,delta_angle) );//cos ( -delta_angle );
        /*double*/ uint32_t w = fpmul(0x40000000 , cm1);//double w = 2 * cm1;
        /*double*/ uint32_t ar[3], ai[3];// double ar[3], ai[3];
        /*double*/ uint32_t temp;//double temp;

        for ( i=0; i < NumSamples; i += BlockSize )
        {
            ar[2] = cm2;
            ar[1] = cm1;

            ai[2] = sm2;
            ai[1] = sm1;

            for ( j=i, n=0; n < BlockEnd; j++, n++ )
            {
                ar[0] =fpsub(fpmul(w,ar[1]) , ar[2]);//ar[0] = w*ar[1] - ar[2];
                ar[2] = ar[1];
                ar[1] = ar[0];

               ai[0] =fpsub(fpmul(w,ai[1]) , ai[2]);//ai[0] = w*ai[1] - ai[2];
                ai[2] = ai[1];
                ai[1] = ai[0];

                k = j + BlockEnd;
                tr = fpsub(fpmul(ar[0],RealOut[k]) , fpmul(ai[0],ImagOut[k]));// ar[0]*RealOut[k] - ai[0]*ImagOut[k];
                ti = fpadd(fpmul(ar[0],ImagOut[k]) , fpmul(ai[0],RealOut[k]));//ar[0]*ImagOut[k] + ai[0]*RealOut[k];

                RealOut[k] = fpsub(RealOut[j] , tr);
                ImagOut[k] = fpsub(ImagOut[j] , ti);

                RealOut[j] = fpadd(RealOut[j], tr);//RealOut[j] += tr;
                ImagOut[j] = fpadd(ImagOut[j] , ti); //ImagOut[j] += ti;
            }
        }

        BlockEnd = BlockSize;
    }

    /*
    **   Need to normalize if inverse transform...
    */

    if ( InverseTransform )
    {
        uint32_t denom = int_to_float(NumSamples);//  double denom = (double)NumSamples;

        for ( i=0; i < NumSamples; i++ )
        {
            RealOut[i] = fpdiv(RealOut[i],denom);//RealOut[i] /= denom;
            ImagOut[i] = fpdiv( ImagOut[i],denom);//ImagOut[i] /= denom;
        }
    }
}


/*--- end of file fourierf.c ---*/
