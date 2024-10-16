#ifndef FUNKCII_GLOBALNIE_H
#define FUNKCII_GLOBALNIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

enum Comandi
{
    Comandi_chislo = -1,
    Comandi_push   = 1,
    Comandi_pop    = 3,
    Comandi_add    = 2,
    Comandi_sub    = 4,
    Comandi_mul    = 5,
    Comandi_divv   = 6, 
    Comandi_out    = 7,
    Comandi_in     = 8,
    Comandi_sqrt   = 9,
    Comandi_sin    = 10,
    Comandi_cos    = 11,
    Comandi_dump   = 12,
    Comandi_hlt    = 13,
    Comandi_ja     = 14,
    Comandi_jae    = 15,
    Comandi_jb     = 16,
    Comandi_jbe    = 17,
    Comandi_je     = 18,
    Comandi_jne    = 19,
    Comandi_jmp    = 20,
    Comandi_popr   = 21,
    Comandi_pushr  = 22,
    Comandi_ax     = 0,
    Comandi_bx     = 1,
    Comandi_cx     = 2,
    Comandi_dx     = 3,
};

#endif //FUNKCII_GLOBALNIE_H