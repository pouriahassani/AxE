/*
blowfish_test.c:  Test file for blowfish.c
-> renamed to main.c

Copyright (C) 1997 by Paul Kocher

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define PICO (1)
#define MULTI (1)

#ifdef PICO
    #include "util.h"
#else
    #include <stdio.h>
#endif

#include "blowfish.h"

void my_main(void) {
    
    print_str("blowfish s\n");
    
    uint32_t L = 1, R = 2;
    BLOWFISH_CTX ctx;
    
    Blowfish_Init (&ctx, (uint8_t *)"TESTKEY", 7);
    
    Blowfish_Encrypt(&ctx, &L, &R);
    
    #ifndef PICO
        printf("%08lX %08lX\n", (long unsigned int)L, (long unsigned int)R);
    #endif
    
    if (L == 0xDF333FD2L && R == 0x30A71BB4L)
    {
        
        #ifdef PICO
            print_str("Test encryption OK.\n");
        #else
            printf("Test encryption OK.\n");
        #endif
        
    }
    else
    {
        #ifdef PICO
            print_str("Test encryption OK.\n");
        #else
            printf("Test encryption OK.\n");
        #endif
    }
    
    Blowfish_Decrypt(&ctx, &L, &R);
    
    if (L == 1 && R == 2)
    {
        #ifdef PICO
            print_str("Test decryption OK.\n");
        #else
            printf("Test decryption OK.\n");
        #endif
    }
    else
    {
        #ifdef PICO
            print_str("Test decryption failed.\n");
        #else
            printf("Test decryption failed.\n");
        #endif
    }
    
    print_str("blowfish d\n");
}
