#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

enum Oshibki_SPU
{
    NET_OSHIBOK                            = 0,
    UKAZTENEL_NA_STRUKTURU_SPU_POEHAL      = 1,
    UKAZTENEL_NA_MASSIV_SPU_POEHAL         = 2,
    OSHIBKA_V_VINIMANII_ZNACHENIA_IS_STEKA = 3,
};

const int KOLICHESTVO_REGISTROV = 4;
const int PEREHOD_NA_FUNKCIU = 1; 
const int PEREHOD_NA_AEGUMENT = 1;

//#define DEBUG_FPRINTF

#ifdef DEBUG_FPRINTF
    #define DEB_PR(...) fprintf(stderr, __VA_ARGS__);
#else
    #define DEB_PR(...)
#endif

struct Processor_t
{
    int64_t* massiv_comand;
    size_t ip;
    bool vikluchatel_cikla;
    struct Stack_t stk;
    int registers[KOLICHESTVO_REGISTROV];
};

enum Oshibki_SPU SPUConstrtor(Processor_t* spu);

#endif // PROCESSOR_H