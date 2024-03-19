
#include "../../_libs/util.h"
#include "basicMath.h"
void usqrt(unsigned long x, struct int_sqrt *q)
{
      unsigned long a = 0L;                   /* accumulator      */
      unsigned long r = 0L;                   /* remainder        */
      unsigned long e = 0L;                   /* trial product    */

      int i;

      for (i = 0; i < BITSPERLONG; i++)   /* NOTE 1 */
      {
            r = (r << 2) + TOP2BITS(x); x <<= 2; /* NOTE 2 */
            a <<= 1;
            e = (a << 1) + 1;
            if (r >= e)
            {
                  r -= e;
                  a++;
            }
      }
}


void my_main(void)
{
  int a1 = 0x3f800000;//1.0
  int b1 = 0xc1280000;//-10.5
  int c1 = 0x42000000;//32.0
  int d1 = 0xc1f00000;//-30.0

  int a2 =  0x3f800000;//1.0
  int b2 = 0xc0900000;//-4.5
  int c2 = 0x41880000;//17.0
  int d2 = 0xc1f00000;//-30.0

  int a3 = 0x3f800000;//1.0
  int b3 = 0xc0600000;//-3.5
  int c3 = 0x41b00000;//22.0
  int d3 = 0xc1f80000;//-31.0

  int a4 = 0x3f800000;//1.0
  int b4 = 0xc15b3333;//-13.7
  int c4 = 0x3f800000;//1.0
  int d4 = 0xc20c0000;//-35.0

  int  x[3];
  int X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  // struct int_sqrt q;
  long n = 0;

  /* solve soem cubic functions */
  /* should get 3 solutions: 2, 6 & 2.5   */
  SolveCubic(a1, b1, c1, d1, &solutions, x);  

  /* should get 1 solution: 2.5           */
  SolveCubic(a2, b2, c2, d2, &solutions, x);  

  SolveCubic(a3, b3, c3, d3, &solutions, x);

  SolveCubic(a4, b4, c4, d4, &solutions, x);

  //   /* Now solve some random equations */
  // loop(&solutions,x);
  
  struct int_sqrt q;
  // /* perform some integer square roots */
  // for (i = 0; i < 1001; ++i)
  //   {
  //     usqrt(i, &q);
	// 		// remainder differs on some machines
  //   }
  // usqrt(l, &q); 
}




