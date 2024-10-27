#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include "stack.h"


enum Oshibki_SPU
{
    NET_OSHIBOK_SPU                                            = 0,
    UKAZTENEL_NA_STRUKTURU_SPU_POEHAL_YOBANIY_V_ROT_BLYAT      = 1,
    UKAZTENEL_NA_MASSIV_SPU_POEHAL                             = 2,
};


static const int SMOTR_PERVIY_BIT                                     = 1;
static const int SMOTR_VTOROY_BIT                                     = 2;
static const int SMOTR_TRETIY_BIT                                     = 4;
static const int SMOTR_CHETVERTIY_BIT                                 = 8;

static const int PEREHOD_NA_KOMANDU                                   = 1;  
static const int PEREHOD_NA_AEGUMENT                                  = 1;

static const int KOLICHESTVO_REGISTROV                                = 4;

static const int RAZMER_ram                                           = 10000;

static const char IMA_CHITAEMOGO_FAILA[]                              = "chislovie_komandi.bin";


struct Processor_t
{
    int64_t* massiv_comand;
    int64_t ip;
    bool vikluchatel_cikla;
    struct Stack_t stk;
    int64_t registers[KOLICHESTVO_REGISTROV];
    int64_t ram[RAZMER_ram];
};


int64_t* Chtenie_komand_is_faila(const char* IMA_CHITAEMOGO_FAILA);
enum Oshibki_SPU Constructor_spu(Processor_t* spu, int64_t* massiv_comand_bufer);
void Dtor_spu(Processor_t* spu, int64_t* massiv_comand_bufer);
enum Oshibki_SPU Execute_spu (Processor_t* spu);

#endif // PROCESSOR_H