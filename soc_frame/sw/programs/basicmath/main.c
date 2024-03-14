
#include "../../_libs/util.h"
/* The printf's may be removed to isolate just the math calculations */
#define BITSPERLONG 32

#define TOP2BITS(x) ((x & (3L << (BITSPERLONG-2))) >> (BITSPERLONG-2))

struct int_sqrt {
      unsigned sqrt,
               frac;
};


void SolveCubic(float32_t  a,
                float32_t  b,
                float32_t  c,
                float32_t  d,
                int    *solutions,
                float32_t *x)
{
      float32_t a1 = float_divide(b,a);
      float32_t a2 = float_divide(c,a);
      float32_t a3 = float_divide(d,a);
      float32_t tmp1 = float_sub(float_mul(a1,a1) , float_mul(a2,stringToFloat("3")));
      float32_t  Q = float_divide(tmp1,stringToFloat("9"));


      tmp1 = float_mul(stringToFloat("2"),a1);
      tmp1 = float_mul(tmp1,a1);
      tmp1 = float_mul(tmp1,a1);
      float32_t tmp2 = float_mul(stringToFloat("9"),a1);
      tmp2 = float_mul(tmp2,a2);
      float32_t tmp3 = float_mul(stringToFloat("27.0"),a3);
      tmp1 = float_sub(tmp1,tmp2);
      tmp1 = float_add(tmp1,tmp3);
      float32_t  R = float_divide(tmp1,stringToFloat("54.0"));

    tmp1 = float_mul(R,R);
    tmp2 = float_mul(Q,Q);
    tmp2 = float_mul(tmp2,Q);

    float32_t R2_Q3 = float_sub(tmp1,tmp2);


      if (extractSign(R2_Q3))
      {
            *solutions = 3;
            float32_t theta = float_acos(float_divide(R,float_Sqrt_Taylor_series(float_mul(float_mul(Q,Q),Q))));
            tmp1 = float_mul(stringToFloat("-2"),Q);
            tmp2 = float_Cos_Taylor_series(float_divide(theta,stringToFloat("3")));
            tmp3 = float_divide(a1,stringToFloat("3"));
            x[0] = float_sub(float_mul(tmp1,tmp2),tmp3);

            tmp2 = float_Cos_Taylor_series(float_divide(theta,stringToFloat("3")));
            tmp3 = float_divide(a1,stringToFloat("3"));
            x[0] = float_sub(float_mul(tmp1,tmp2),tmp3);

            tmp2 = float_Cos_Taylor_series(float_divide(float_add(theta,float_mul(stringToFloat("2"),stringToFloat("3.14"))),stringToFloat("3")));
            tmp3 = float_divide(a1,stringToFloat("3"));
            x[1] = float_sub(float_mul(tmp1,tmp2),tmp3);

            tmp2 = float_Cos_Taylor_series(float_divide(float_add(theta,float_mul(stringToFloat("4"),stringToFloat("3"))),stringToFloat("3")));
            tmp3 = float_divide(a1,stringToFloat("3"));
            x[2] = float_sub(float_mul(tmp1,tmp2),tmp3);
      }
      else
      {
            *solutions = 1;
            x[0] = power(float_add(float_Sqrt_Taylor_series(R2_Q3),float_fabs(R)),float_divide(stringToFloat("1") ,stringToFloat("3")));
            x[0] = float_add(x[0],float_divide(Q,x[0]));
            if(extractExponent(R))
              x[0].value &= 0x7FFFFFFF;
            else
              x[0].value |= 0x80000000;
            x[0] = float_sub(x[0], float_divide(a1,stringToFloat("3")));
      }
}

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
  float32_t a1 = stringToFloat("1");
  float32_t b1 = stringToFloat("-10.5");
  float32_t c1 = stringToFloat("32.0");
  float32_t d1 = stringToFloat("-30.0");
  
  float32_t a2 = stringToFloat("1");
  float32_t b2 = stringToFloat("-4.5");
  float32_t c2 = stringToFloat("17.0");
  float32_t d2 = stringToFloat("-30.0");

  float32_t a3 = stringToFloat("1");
  float32_t b3 = stringToFloat("-3.5");
  float32_t c3 = stringToFloat("22.0");
  float32_t d3 = stringToFloat("-31.0");

  float32_t a4 = stringToFloat("1");
  float32_t b4 = stringToFloat("-13.7");
  float32_t c4 = stringToFloat("1");
  float32_t d4 = stringToFloat("-35.0");

  float32_t  x[3];
  float32_t X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  // struct int_sqrt q;
  long n = 0;

  /* solve soem cubic functions */
  /* should get 3 solutions: 2, 6 & 2.5   */
  // SolveCubic(a1, b1, c1, d1, &solutions, x);  

  // // /* should get 1 solution: 2.5           */
  // SolveCubic(a2, b2, c2, d2, &solutions, x);  

  // SolveCubic(a3, b3, c3, d3, &solutions, x);

  // SolveCubic(a4, b4, c4, d4, &solutions, x);

    // /* Now solve some random equations */
  //   for(int i = 1; i < 10; i++) {
  //     for(int j = 10 ; j > 0 ; j--) {
  //       for(int k = 5; k < 30 ; k+=1) {
  //         for(l = -1 ; l > -11 ; l--) {
  //           char* A1,B1,C1,D1;
  //           intToString(i,A1);
  //           intToString(j,B1);
  //           intToString(k,C1);
  //           intToString(l,D1);
  //           float32_t a1 = stringToFloat(A1);
  //           float32_t b1 = stringToFloat(B1);
  //           float32_t c1 = stringToFloat(C1);
  //           float32_t d1 = stringToFloat(D1);

  //           SolveCubic(a1, b1, c1, d1, &solutions, x);  
  //       }
  //     }
  //   }
  // }
  
  struct int_sqrt q;
  // /* perform some integer square roots */
  for (i = 0; i < 1001; ++i)
    {
      usqrt(i, &q);
			// remainder differs on some machines
    }
  usqrt(l, &q);


 
  
}


