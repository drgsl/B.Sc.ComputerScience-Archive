/*
*  Program: com-2.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    /* Scriem o frază incompletă, pe descriptorul 1, "asociat" fluxului stdout. */
    write(1,"..., tuturor!",13);

    return 0;
}
