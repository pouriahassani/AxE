
#include "fourier.h"
#include <stdlib.h>

void my_main(int argc, char *argv[]) {
	unsigned MAXSIZE;
	unsigned MAXWAVES;
	unsigned i,j;
	uint32_t RealIn[4096];  /*float *RealIn;*/
	uint32_t ImagIn[4096]; /*float *ImagIn;*/
	uint32_t RealOut[4096];    /*float *RealOut;*/
	uint32_t ImagOut[4096];   /*float *ImagOut;*/
	uint32_t coeff[4];  /*float *coeff;*/
	uint32_t amp[4];/*float *amp;*/

	// uint32_t RealIn_i[8192];   /*float *RealIn;*/
	// uint32_t ImagIn_i[8192];   /*float *ImagIn;*/
	// uint32_t RealOut_i[8192];    /*float *RealOut;*/
	// uint32_t ImagOut_i[8192];    /*float *ImagOut;*/
	// uint32_t coeff_i[8192];  /*float *coeff;*/
	// uint32_t amp_i[8192];/*float *amp;*/
	int invfft=0;
	MAXSIZE=4096;
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
  uint32_t tmp = 0; 
 for(i=0;i<MAXSIZE;i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0x00000000;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 /* randomly select sin or cos */
		 if (i%2)
		 {
			
			// display_print(1,coeff[j],"");display_print(0,0,"coeff\n");
			// display_print(1,fp_Cos(fpmul(amp[j],int_to_float(i))),"");display_print(0,0,"fp_cos\n");
			// display_print(1,fpmul(amp[j],int_to_float(i)),"");display_print(0,0,"fpmul(amp,int(i))\n");
			tmp = fpmul(coeff[j],fp_Cos(fpmul(amp[j],int_to_float(i))));
			RealIn[i] = fpadd(RealIn[i],tmp);
		 }
		 else
		 {
			tmp = fpmul(coeff[j],fp_Sin(fpmul(amp[j],int_to_float(i))));
			RealIn[i] = fpadd(RealIn[i],tmp);
		 }
		
		// display_print(0,0,"\nRealIn i ");display_print(2,i,"");display_print(0,0," j ");display_print(2,j,"");
		// display_print(0,0,"===> "); display_print(1,RealIn[i],"");
  	 ImagIn[i]=0;
	 }
	//  display_print(0,0,"\nFinal RealIN i ");display_print(2,i,"");
	//  display_print(0,0,"===> ");display_print(1,RealIn[i],"");
 }

 /* regular*/
 fft_float (MAXSIZE,0,RealIn,ImagIn,RealOut,ImagOut);

 fft_float (MAXSIZE,1,RealIn,ImagIn,RealOut,ImagOut);
 

//  for (i=0;i<MAXSIZE;i++){
// 	display_print(0,0,"\nRealOut: ");
//     display_print(2,RealOut[i],"");
//  }

//  for (i=0;i<MAXSIZE;i++){
// 	display_print(0,0,"\nImagOut: ");
//     display_print(2,ImagOut[i],"");
//  }

}
