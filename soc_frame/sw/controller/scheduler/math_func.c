#include "math_func.h"
unsigned int clamp_add( unsigned int number, unsigned int add )
{
	#ifdef DBG_MATH_CLAMP
		print_str("\nclamp_add number: ");print_dec(number);
		print_str("\nadd: ");print_dec(add);
	#endif

	unsigned int temp = number;

	number += add;
	
	if ( number < temp ) // overflow
	{
		#ifdef DBG_MATH_CLAMP
			print_str("\ndetected overflow, set to");print_dec(MAX);
		#endif

		number = MAX;
	}

	return number;
}

unsigned int clamp_sub( unsigned int number, unsigned int sub )
{
	#ifdef DBG_MATH_CLAMP
		print_str("\nclamp_sub number: ");print_dec(number);
		print_str("\nsub: ");print_dec(sub);
	#endif

	unsigned int temp = number;

	number -= sub;
	
	if ( number > temp ) // underflow
	{
		#ifdef DBG_MATH_CLAMP
			print_str("\ndetected underflow, set to 0\n");
		#endif

		number = 0;
	}

	return number;
}
