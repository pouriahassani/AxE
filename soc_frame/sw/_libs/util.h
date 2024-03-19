#ifndef UTIL_H
#define UTIL_H
// Define a structure to represent single-precision floating-point numbers

typedef unsigned int uint32_t;

typedef struct {
    uint32_t value;
} float32_t;

#define MAX ( 0xFFFFFFFF )
#define MAX_HALF ( 0x7FFFFFFF )

#define OUTPORT 0x00000000

#define FINISHED ( 0x00FFFFFC )

#define ASSERT(expr) \
    if (expr) \
        {} \
    else \
        { emb_assert(__LINE__,__FILE__,#expr); }

//~ { print_dec(__LINE__);print_str(#expr);nl(); }
//~ { print_dec(__LINE__);print_str(#expr); }
__attribute__((noinline))
int fpmul(int rs1, int rs2);

__attribute__((noinline))
int fpadd(int rs1, int rs2);


__attribute__((noinline))
int fpsub(int rs1, int rs2);


__attribute__((noinline))
int fpdiv(int rs1, int rs2);
// is now done in the asm file.

void signal_fin();

void signal_kill_sim();
// -----------------------------------------------------------------------------
// 
// P R I N T
// 
// -----------------------------------------------------------------------------

// TODO - add some define to supress debug output. do it here so you don't
// have to worry about it when adding new output.

// char
// -------------------------------------

void print_char(char ch);
// inline void print_char(char ch);
// str
// -------------------------------------
void print_str_str_n( const char *p,const char * t );
void print_str_dec_n( const char *T,unsigned int val );

void print_str(const char *p);
void print_str_n(const char *p);
// dec
// -------------------------------------

void print_dec_n(unsigned int val);

void print_dec(unsigned int val);

// hex
// -------------------------------------

void print_hex(unsigned int val, int digits);

// binary
// -------------------------------------

void print_bin(unsigned int val, int bits);
// newline
// -------------------------------------

void nl();

// print_assert
// -------------------------------------
void emb_assert( unsigned int line, const char *file, const char *exp );

// Helper function to extract the sign bit from a float32_t number
uint32_t extractSign(float32_t a);

// Helper function to extract the sign bit from a float32_t number
uint32_t fp_ExtractSign(int a);

// Helper function to extract the exponent bits from a float32_t 	$(CC) -march=$(ARCH) $(CFLAGS) -nostartfiles -o ./$(ARCH)_main.elf $(LINK) ../sp.S -DSTACK_POINTER=$(STACK_POINTER) ../crt0.o ../start.S $(SRC) ./main.cnumber
uint32_t extractExponent(float32_t a);

// Helper function to extract the exponent bits from a float32_t 	$(CC) -march=$(ARCH) $(CFLAGS) -nostartfiles -o ./$(ARCH)_main.elf $(LINK) ../sp.S -DSTACK_POINTER=$(STACK_POINTER) ../crt0.o ../start.S $(SRC) ./main.cnumber
uint32_t fp_ExtractExponent(int a);

// Helper function to extract the fraction bits from a float32_t number
uint32_t extractFraction(float32_t a);

// Helper function to extract the fraction bits from a float32_t number
uint32_t fp_ExtractFraction(int a);

// Helper function to create a float32_t number from sign, exponent, and fraction
float32_t makeFloat(uint32_t sign, uint32_t exponent, uint32_t fraction);


void multiply_fractions(uint32_t a, uint32_t b, uint32_t* result_fraction, uint32_t* result_exp);
// Function to perform subtraction of two float32_t numbers
float32_t float_mul(float32_t a, float32_t b);


// Function to add two floats using integer operations
float32_t float_add(float32_t a, float32_t b);

// Function to perform subtraction of two float32_t numbers
float32_t float_sub(float32_t a, float32_t b);

// Function to convert fraction to binary
uint32_t fractionToBinary_int_exist(uint32_t fraction, uint32_t numBits,uint32_t digits);


// Function to convert fraction to binary
uint32_t fractionToBinary_int_non_exist(uint32_t fraction,uint32_t digits,uint32_t *Exp_shift,char *iszero);

// Perform division of two floats using integer operations
float32_t float_divide(float32_t a, float32_t b);

// Function to compute the inverse sine (asin) using polynomial approximation
float32_t float_asin(float32_t x);

// Function to compute the inverse sine (asin) using polynomial approximation
int fp_Asin_simple(int x);

// Function to compute the inverse sine (asin) using polynomial approximation
int fp_Asin(int x);

// Function to compute the inverse sine (asin) using polynomial approximation
float32_t float_asin_Taylor_series(float32_t x);

// Function to compute the inverse sine (asin) using polynomial approximation
float32_t float_Sqrt_Taylor_series(float32_t y);
// Function to compute the sqrt(x) using polynomial approximation

/*
NOTE: This function is an apporximation of sqrt(x) where 0 < x < 30.
If your x is not in this range consider normalizing by adjusting the value
of const_15 and the Devider
the approximation is g(x) = sqrt(x+1)  for -1 < x < 1. You need to bring the range of your x to this range 
using follwoing formula:  
your function ==> f(x) for  n < x < m
f(x) = sqrt(m-n) * g(x/(m-n) - 1) for -1 < x < 1
*/

int fp_Sqrt(int y);

// Function to compute the cos using polynomial approximation
float32_t float_Cos_Taylor_series(float32_t x);

// Function to compute the cos using polynomial approximation
int fp_Cos(int x);

uint32_t fp_Sin(uint32_t x);
// Function to compute the pow(x,y) assuming that y doesnt have integer     
float32_t power(float32_t base, float32_t exponent_t);


// Function to compute the pow(x,y) using polynomial approximation 
//  Here we assume that exponent is normalized and not in the denormalized range
int fp_Pow(int base, int exponent);

// Function to compute the pow(x,y) using polynomial approximation 
//  Here we assume that exponent is normalized and not in the denormalized range
// int pow_fp_itr(int base, int exponent) {
//         // if exponent is zero return 1.0
//     int result = 0x3f800000;// result  = 1.0
//     if(exponent == 0)
//         return 0x3f800000;// return 1.0

//     if(base == 0x3f800000)// if base == 1.0
//         return 0x3f800000;// return 1.0

//     if(base == 0)
//      return 0;

//     for(int i=0 ; i < exponent ; i++)
//         result = fpmul(result,base);
//     return result;
// }

// calculate absolute value of floating point number x
int fp_Fabs(int x);

int fp_Reg2deg(int x);

int eg2rad(int x);
int fp_Acos(int x);


// Function to convert an integer to a string
void intToString(int num, char* str);

int fp_Exp(int x);
// Casting float to integer. if x is greater than the range of integer the result is valid
// This is equivalent of (int)x where x is a float
int cast_Fp_To_Int(int x);
// int_to_float convert int value between certain range to float format 
uint32_t int_to_float(int x);
void memset_Char_t(unsigned char* ptr,char value,int size);

void memset_Int_t(int* ptr,int value,int size);

#endif
