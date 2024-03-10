
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "util.h"

#define test(p) (primes[p >> 6] & 1 << (p & 0x3f))
#define set(p) (primes[p >> 6] |= 1 << (p & 0x3f))
#define is_prime(p) !test(p)

int my_main()
{
    //~ print_str( "primes s\n" );
    
    int limit = 10;
    uint64_t primes[ 8 ];
    
    int64_t p = 2;
    int64_t sqrt_limit = 3;
    
    while (p <= limit >> 1) {
        for (int64_t n = 2 * p; n <= limit; n += p) if (!test(n)) set(n);
        while (++p <= sqrt_limit && test(p));
    }
    
    for (int i = limit; i > 0; i--) {
        
        if (is_prime(i)) {
            
            if ( 7 == i )
            {
                //~ print_str("correct\n");
            }
        }
    }
    //~ print_str("primes d\n");
}
