#include "processor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "stack.h"
#include "globalniy_enum.h"
#include "schitivanie_faila.h"
#include "utils.h"

static int64_t FetchInstruction(Processor_t* spu);
static void Decode(Processor_t* spu);
static void PushSPU(Processor_t* spu);
static void AddSPU(Processor_t* spu);
static void SubSPU(Processor_t* spu);
static void MulSPU(Processor_t* spu);
static void DivvSPU(Processor_t* spu);
static void OutSPU(Processor_t* spu);
static void InSPU(Processor_t* spu);
static void SqrtSPU(Processor_t* spu);
static void SinSPU(Processor_t* spu);
static void CosSPU(Processor_t* spu);
static void DumpSPU(Processor_t* spu);
static void HltSPU(Processor_t* spu);
static void JaSPU(Processor_t* spu);
static void JaeSPU(Processor_t* spu);
static void JbSPU(Processor_t* spu);
static void JbeSPU(Processor_t* spu);
static void JeSPU(Processor_t* spu);
static void JneSPU(Processor_t* spu);
static void JmpSPU(Processor_t* spu);
static void PopSPU(Processor_t* spu);
static void CallSPU(Processor_t* spu);
static void RetSPU(Processor_t* spu);
static void DrowSPU(Processor_t* spu);

enum Oshibki_SPU SPUConstrtor(Processor_t* spu, int64_t* massiv_comand_bufer)
{
    assert(spu != NULL);
    assert(massiv_comand_bufer != NULL);

    spu->massiv_comand = massiv_comand_bufer;      
    spu->ip = 0;
    spu->vikluchatel_cikla = false;
    if (StackConstrtor(&spu->stk, 2) > 0) assert(0);
    memset(spu->registers, 0, KOLICHESTVO_REGISTROV);

    return NET_OSHIBOK_SPU;
}

void SPUDtor(Processor_t* spu, int64_t* massiv_comand_bufer)
{
    assert(spu != NULL);
    assert(massiv_comand_bufer != NULL);

    StackDtor(&(spu->stk));

    free(massiv_comand_bufer);
    massiv_comand_bufer = NULL;
    
    memset(spu, 0, sizeof(spu));
}

int64_t* Chtenie_komand_is_faila(const char* ima_chitaemogo_failaa) 
{
    assert(ima_chitaemogo_failaa != NULL);

    FILE* komandi_v_chislah = fopen(ima_chitaemogo_failaa, "r");
    if (komandi_v_chislah == nullptr)
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
    }

    size_t razmer_faila_bytes = Chitaet_razmer_faila(komandi_v_chislah);
    assert(razmer_faila_bytes % sizeof(int64_t) == 0); 

    int64_t* massiv_comand_bufer = (int64_t*)calloc(razmer_faila_bytes, sizeof(char));
    fread(massiv_comand_bufer, sizeof(char), razmer_faila_bytes, komandi_v_chislah);
    fclose (komandi_v_chislah);

    return massiv_comand_bufer;
}

enum Oshibki_SPU ExecuteSPU (Processor_t* spu)
{
    assert(spu != NULL);

    while (!spu->vikluchatel_cikla)
    {
        Decode(spu);
    }

    return NET_OSHIBOK_SPU;
}

int64_t FetchInstruction(Processor_t* spu)
{
    assert(spu != NULL);
    
    return spu->massiv_comand[spu->ip];
}

void Decode(Processor_t* spu)
{
    switch (FetchInstruction(spu))
    {
        case Comandi_push: { PushSPU(spu); }
        break;

        case Comandi_add:  { AddSPU(spu);  }
        break;

        case Comandi_sub:  { SubSPU(spu);  }
        break;

        case Comandi_mul:  { MulSPU(spu);  }
        break;

        case Comandi_divv: { DivvSPU(spu); }
        break;

        case Comandi_out:  { OutSPU(spu);  }
        break;

        case Comandi_in:   { InSPU(spu);   }
        break;

        case Comandi_sqrt: { SqrtSPU(spu); }
        break;
            
        case Comandi_sin:  { SinSPU(spu);  }
        break;

        case Comandi_cos:  { CosSPU(spu);  }
        break;

        case Comandi_dump: { DumpSPU(spu); }
        break;

        case Comandi_hlt:  { HltSPU(spu);  }
        break;

        case Comandi_ja:   { JaSPU(spu);   }
        break;

        case Comandi_jae:  { JaeSPU(spu);  }
        break;

        case Comandi_jb:   { JbSPU(spu);   }
        break;

        case Comandi_jbe:  { JbeSPU(spu);  }
        break;

        case Comandi_je:   { JeSPU(spu);   }
        break;

        case Comandi_jne:  { JneSPU(spu);  }
        break;

        case Comandi_jmp:  { JmpSPU(spu);  }
        break;

        case Comandi_pop:  { PopSPU(spu);  }
        break;

        case Comandi_call: { CallSPU(spu); }
        break;

        case Comandi_ret:  { RetSPU(spu);  }
        break;

        case Comandi_drow: { DrowSPU(spu); }
        break;

        default:           { assert(0);    }
    }
}

static void DrowSPU(Processor_t* spu)
{
    
}
static void CallSPU(Processor_t* spu)
{
    if (StackPush(&(spu->stk), spu->ip + PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT) > 0) assert(0);
    spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU];
    DEB_PR("21\n");
}

static void RetSPU(Processor_t* spu)
{
    int64_t a = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    spu->ip = spu->massiv_comand[a];
    DEB_PR("22\n");
}

static void PushSPU(Processor_t* spu)
{
    spu->ip++;
    int64_t type_pu = FetchInstruction(spu); spu->ip++;
    int64_t resultat_pu = 0;

    if (type_pu & SMOTR_PERVIY_BIT) { resultat_pu = FetchInstruction(spu); spu->ip++; }
    if (type_pu & SMOTR_VTOROY_BIT) { resultat_pu += spu->registers[FetchInstruction(spu)]; spu->ip++; }
    if (type_pu & SMOTR_TRETIY_BIT) { resultat_pu = spu->ram[resultat_pu]; spu->ip++; }

    if (StackPush(&(spu->stk), resultat_pu) > 0) assert(0);

    DEB_PR("1\n");
}

static void AddSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (StackPush(&(spu->stk), b + a) > 0) assert(0);
    
    spu->ip += PEREHOD_NA_KOMANDU;

    DEB_PR("2\n");
}

static void SubSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (StackPush(&(spu->stk), b - a) > 0) assert(0);
    
    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("4\n");
}

static void MulSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (StackPush(&(spu->stk), b * a) > 0) assert(0);
    
    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("5\n");
}

static void DivvSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;

    if(a == 0) { assert(0); }

    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (StackPush(&(spu->stk), b / a) > 0) assert(0);

    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("6\n");
}

static void OutSPU(Processor_t* spu)
{
    int64_t a = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);

    printf("%ld\n", a); 
    
    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("7\n");
}

static void InSPU(Processor_t* spu)
{
    int64_t a = 0;
    scanf("%ld", &a);
    if (StackPush(&(spu->stk), (int)spu->massiv_comand[a]) > 0) assert(0);

    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("8\n");
}

static void SqrtSPU(Processor_t* spu)
{
    int64_t a = 0;

    if(a < 0) { assert(0); }

    if (StackPop(&(spu->stk), &a) > 0) assert(0);

    if (StackPush(&(spu->stk), sqrt(a)) > 0) assert(0);
    
    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("9\n");
}

static void SinSPU(Processor_t* spu)
{
    int64_t a = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);

    if (StackPush(&(spu->stk), sin(a)) > 0) assert(0);
    
    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("10\n");
}

static void CosSPU(Processor_t* spu)
{
    int64_t a = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);

    if (StackPush(&(spu->stk), cos(a)) > 0) assert(0);
    
    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("11\n");
}

static void DumpSPU(Processor_t* spu)
{
    for (long long i = (long long)spu->stk.vacant_place - 1; i >= 0; i--)
    {
        fprintf(stderr, "   [%lld] = ", i);
        fprintf(stderr, "%lu\n", (long unsigned)spu->stk.array_data[i]);
    }

    spu->ip += PEREHOD_NA_KOMANDU;
    DEB_PR("12\n");
}

static void HltSPU(Processor_t* spu)
{
    DEB_PR("13\n");
    spu->vikluchatel_cikla = PEREHOD_NA_KOMANDU;
}

static void JaSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);
    
    if (b > a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
    else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
    DEB_PR("14\n");
}

static void JaeSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (b >= a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
    else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
    DEB_PR("15\n");
}

static void JbSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (b < a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
    else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
    DEB_PR("16\n");
}

static void JbeSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (b <= a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
    else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
    DEB_PR("17\n");
}

static void JeSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if (b == a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
    else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
    DEB_PR("18\n");
}

static void JneSPU(Processor_t* spu)
{
    int64_t a = 0;
    int64_t b = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0);
    if (StackPop(&(spu->stk), &b) > 0) assert(0);

    if(b != a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
    else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
    DEB_PR("19\n");
}

static void JmpSPU(Processor_t* spu)
{
    spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU];
    DEB_PR("20\n");
}

static void PopSPU(Processor_t* spu)
{
    spu->ip++;
    int64_t type_po = FetchInstruction(spu); spu->ip++;
    int64_t resultat_po = 0;

    int64_t a = 0;
    if (StackPop(&(spu->stk), &a) > 0) assert(0); 
    
    if (type_po & SMOTR_CHETVERTIY_BIT)
    {
        spu->registers[FetchInstruction(spu)] = a;
        spu->ip++; 
    }
    else
    {
        if (type_po & SMOTR_PERVIY_BIT)
        { 
            resultat_po = FetchInstruction(spu);
            spu->ip++;
        }
        if (type_po & SMOTR_VTOROY_BIT)
        { 
            resultat_po += spu->registers[FetchInstruction(spu)];
            spu->ip++; 
        }

        spu->ram[resultat_po] = a;
    }

    DEB_PR("3\n");
}