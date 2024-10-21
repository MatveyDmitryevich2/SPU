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

const char IMA_CHITAEMOGO_FAILA[] = "Chislovie_komani.txt";

const int KOLICHESTVO_REGISTROV = 4;

const int PEREHOD_NA_KOMANDU = 1;  
const int PEREHOD_NA_AEGUMENT = 1;

const int SMOTR_PERVIY_BIT = 1;
const int SMOTR_VTOROY_BIT = 2;
const int SMOTR_TRETIY_BIT = 4;
const int SMOTR_CHETVERTIY_BIT = 8;

const int RAZMER_ram = 20;



struct Processor_t
{
    int64_t* massiv_comand;
    int64_t ip;
    bool vikluchatel_cikla;
    struct Stack_t stk;
    int registers[KOLICHESTVO_REGISTROV];
    int64_t ram[RAZMER_ram];
};

int64_t* Chtenie_komand_is_faila(const char* IMA_CHITAEMOGO_FAILA);
enum Oshibki_SPU SPUConstrtor(Processor_t* spu, int64_t* massiv_comand_bufer);
void SPUDtor(Processor_t* spu, int64_t* massiv_comand_bufer);
enum Oshibki_SPU ExecuteSPU (Processor_t* spu);

int64_t Fetch(Processor_t* spu);
void Decode(Processor_t* spu);

void PushSPU(Processor_t* spu);
void AddSPU(Processor_t* spu);
void SubSPU(Processor_t* spu);
void MulSPU(Processor_t* spu);
void DivvSPU(Processor_t* spu);
void OutSPU(Processor_t* spu);
void InSPU(Processor_t* spu);
void SqrtSPU(Processor_t* spu);
void SinSPU(Processor_t* spu);
void CosSPU(Processor_t* spu);
void DumpSPU(Processor_t* spu);
void HltSPU(Processor_t* spu);
void JaSPU(Processor_t* spu);
void JaeSPU(Processor_t* spu);
void JbSPU(Processor_t* spu);
void JbeSPU(Processor_t* spu);
void JeSPU(Processor_t* spu);
void JneSPU(Processor_t* spu);
void JmpSPU(Processor_t* spu);
void PopSPU(Processor_t* spu);

#endif // PROCESSOR_H