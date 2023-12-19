#include "stdio.h"

#include "ecall.h"
#include "misc.h"

void ecall(rz_register_t a0, rz_register_t *a1) {
    switch (a0)
    {
    case 1:     //print int from a1
        printf("%d \n", a1);
        break;
    case 10:     //print float from a1
        printf("%f \n", a1);
        break;
    case 100:    //print str from a1
        printf("%s \n", a1);
        break;
    case 1011:    //print char from a1
        printf("%c \n", a1);
        break;
    default:
        break;
    }
}