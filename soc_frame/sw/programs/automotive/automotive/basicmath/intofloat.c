#include <stdio.h>
int main(){
        /* Now solve some random equations */
    for(int i = 1; i < 10; i++) {
      for(int j = 10 ; j > 0 ; j--) {
        for(int k = 5; k < 30 ; k+=1) {
          for(int l = -1 ; l > -11 ; l--) {
  

            float a1 = (float)i;
            float b1 = (float)j;
            float c1 = (float)k;
            float d1 = (float)l;

            unsigned int* A1 = (unsigned int *)&a1;
            unsigned int* B1 = (unsigned int *)&b1;
            unsigned int* C1 = (unsigned int *)&c1;
            unsigned int* D1 = (unsigned int *)&d1;
            printf("a1 = 0x%8x; b1 = 0x%8x; c1 = 0x%8x; d1 = 0x%8x;\n",*A1,*B1,*C1,*D1);
            printf("SolveCubic(a1, b1, c1, d1, solutions, x); \n");
            printf("\n     /*******/       \n");

        }
      }
    }
  }
}