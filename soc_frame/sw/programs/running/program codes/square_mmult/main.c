
// C program to multiply two square matrices. 

//~ https://www.geeksforgeeks.org/c-program-multiply-two-matrices/

//~ #include <stdio.h>

// result
// 10 10 10 10
// 20 20 20 20
// 30 30 30 30
// 40 40 40 40

#include "util.h"

//~ #define N 4
//~ #define N 8
#define N 4

// This function multiplies mat1[][] and mat2[][], 
// and stores the result in res[][] 
void multiply(int mat1[][N], int mat2[][N], int res[][N]) 
{ 
    int i, j, k; 
    for (i = 0; i < N; i++) 
    { 
        for (j = 0; j < N; j++) 
        { 
            res[i][j] = 0; 
            for (k = 0; k < N; k++) 
                res[i][j] += mat1[i][k]*mat2[k][j]; 
        } 
    } 
} 
  
void my_main()
//~ int main()
{
    print_str( "s_mmult s\n" );
    
    int mat1[N][N] =
                    {
                        {1, 1, 1, 1},
                        {2, 2, 2, 2},
                        {3, 3, 3, 3},
                        {4, 4, 4, 4}
                    }; 
  
    int mat2[N][N] =
                    {
                        {1, 1, 1, 1},
                        {2, 2, 2, 2},
                        {3, 3, 3, 3},
                        {4, 4, 4, 4}
                    };
    //~ int mat1[N][N] =
                    //~ {
                        //~ {1, 1, 1, 1, 1, 1, 1, 1},
                        //~ {2, 2, 2, 2, 2, 2, 2, 2},
                        //~ {3, 3, 3, 3, 3, 3, 3, 3},
                        //~ {4, 4, 4, 4, 4, 4, 4, 4},
                        //~ {5, 5, 5, 5, 5, 5, 5, 5},
                        //~ {6, 6, 6, 6, 6, 6, 6, 6},
                        //~ {7, 7, 7, 7, 7, 7, 7, 7},
                        //~ {8, 8, 8, 8, 8, 8, 8, 8}
                    //~ }; 
  
    //~ int mat2[N][N] =
                    //~ {
                        //~ {1, 1, 1, 1, 1, 1, 1, 1},
                        //~ {2, 2, 2, 2, 2, 2, 2, 2},
                        //~ {3, 3, 3, 3, 3, 3, 3, 3},
                        //~ {4, 4, 4, 4, 4, 4, 4, 4},
                        //~ {5, 5, 5, 5, 5, 5, 5, 5},
                        //~ {6, 6, 6, 6, 6, 6, 6, 6},
                        //~ {7, 7, 7, 7, 7, 7, 7, 7},
                        //~ {8, 8, 8, 8, 8, 8, 8, 8}
                    //~ };
    
    //~ int mat1[N][N] =
                    //~ {
                        //~ {1, 1, 1, 1},
                        //~ {2, 2, 2, 2},
                        //~ {3, 3, 3, 3},
                        //~ {4, 4, 4, 4}
                    //~ }; 
  
    //~ int mat2[N][N] =
                    //~ {
                        //~ {1, 1, 1, 1},
                        //~ {2, 2, 2, 2},
                        //~ {3, 3, 3, 3},
                        //~ {4, 4, 4, 4}
                    //~ };
    
    int res[N][N]; // To store result
    int i, j;
    multiply(mat1, mat2, res);
    
    //~ print_str("Result matrix is \n");
    //~ printf("Result matrix is \n");
    for (i = 0; i < N; i++)
    { 
        //~ for (j = 0; j < N; j++)
        //~ {
           //~ print_dec( res[i][j] );
        //~ }
        //~ print_str("n");
        //~ for (j = 0; j < N; j++)
        //~ {
           //~ printf("%d ", res[i][j]);
        //~ }
        //~ printf("\n");
    }
    
    print_str( "s_mmult d\n" );
} 
