
#include "fourier.h"
void my_main(int argc, char *argv[]) {
	unsigned MAXSIZE;
	unsigned MAXWAVES;
	unsigned i,j;
	uint32_t RealIn[4096];  /*float *RealIn;*/
	uint32_t ImagIn[4096]; /*float *ImagIn;*/
	uint32_t RealOut[4096];    /*float *RealOut;*/
	uint32_t ImagOut[4096];   /*float *ImagOut;*/
	uint32_t coeff[4096];  /*float *coeff;*/
	uint32_t amp[4096];/*float *amp;*/

	uint32_t RealIn_i[8192];   /*float *RealIn;*/
	uint32_t ImagIn_i[8192];   /*float *ImagIn;*/
	uint32_t RealOut_i[8192];    /*float *RealOut;*/
	uint32_t ImagOut_i[8192];    /*float *ImagOut;*/
	uint32_t coeff_i[8192];  /*float *coeff;*/
	uint32_t amp_i[8192];/*float *amp;*/
	int invfft=0;
	MAXSIZE=4;
	MAXWAVES=4;
 /* Makes MAXWAVES waves of random amplitude and period */
//  printf("\ni is : %d",MAXWAVES);
  coeff[0] = 0x43bf8000;//int_to_float(383);
  coeff[1] = 0x44424000;//int_to_float(777);
  coeff[2] = 0x44464000;//int_to_float(793);
  coeff[3] = 0x43c10000;//int_to_float(386);
  amp[0] =   0x445d8000;//int_to_float(886);
  amp[1] =   0x4464c000;//int_to_float(915);
  amp[2] =   0x43a78000;//int_to_float(335);
  amp[3] =   0x43f60000;//int_to_float(492);

 for(i=0;i<MAXSIZE;i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 /* randomly select sin or cos */
		 if (i%2)
		 {
		 		RealIn[i]+=fpmul(coeff[j],fp_Cos(fpmul(amp[j],int_to_float(i))));
			}
		 else
		 {
		 	RealIn[i]+= fpmul(coeff[j],fp_Sin(fpmul(amp[j],int_to_float(i))));
		 }
  	 ImagIn[i]=0;
	 }
 }

 /* regular*/
//  fft_float (MAXSIZE,0,RealIn,ImagIn,RealOut,ImagOut);

//  fft_float (MAXSIZE,1,RealIn,ImagIn,RealOut,ImagOut);
 
//  printf("RealOut:\n");
//  for (i=0;i<MAXSIZE;i++)
//    printf("%f \t", RealOut[i]);
//  printf("\n");

// printf("ImagOut:\n");
//  for (i=0;i<MAXSIZE;i++)
//    printf("%f \t", ImagOut[i]);
//    printf("\n");


}
