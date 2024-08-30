#include "util.h"
void my_main(){
    int x = 0x3f05f92c;
    display_print(0,0,"\ncos value is: ");
    display_print(1,fp_Sin(x),"\n");
    display_print(0,0,"\ncos value was: ");
    x = fpsub(0xBD912000,0x400ccccd);
    display_print(0,0,"\nsub value was: ");
        display_print(1,x,"\n");
}