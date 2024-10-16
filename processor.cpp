#include "processor.h"
#include "stack.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>
#include <math.h>

enum Oshibki_SPU SPUConstrtor(Processor_t* spu, int64_t* massiv_comand_bufer)
{
    if (massiv_comand_bufer == NULL) { assert(0); }
    if (spu == NULL) { assert(0); }

    if (StackConstrtor(&spu->stk, 2) > 0) assert(0);
    spu->ip = 0;
    spu->vikluchatel_cikla = false;
    spu->massiv_comand = massiv_comand_bufer;

    return NET_OSHIBOK_SPU;
}

void SPUDtor(Processor_t* spu, int64_t* massiv_comand_bufer)
{
    if (spu == NULL) { assert(0); }

    StackDtor(&(spu->stk));

    free(massiv_comand_bufer);
}

int64_t* Chtenie_komand_is_faila(const char* ima_faila) 
{
    if (ima_faila == NULL) { assert(0); }

    FILE* komandi_v_chislah = fopen(ima_faila, "r");
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
    if (spu == NULL) { assert(0); }

    while (spu->vikluchatel_cikla == 0) 
    {
        switch (spu->massiv_comand[spu->ip])
        {
            case Comandi_push:
            {
                if (StackComandi_push(&(spu->stk), (int)spu->massiv_comand[spu->ip + PEREHOD_NA_AEGUMENT]) > 0) { assert(0); }
                
                spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT;
                DEB_PR("1");
            }
            break;
        
            case Comandi_add: 
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), b + a) > 0) assert(0);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("2");
            }
            break;

            case Comandi_sub:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), b - a) > 0) assert(0);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("4");
            }
            break;

            case Comandi_mul:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), b * a) > 0) assert(0);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("5");
            }
            break;

            case Comandi_divv:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), b / a) > 0) assert(0);

                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("6");
            }
            break;

            case Comandi_out:
            {
                int64_t a = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);

                printf("%ld\n", a);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("7");
            }
            break;

            case Comandi_in:
            {
                int64_t a = 0;
                scanf("%ld", &a);
                if (StackComandi_push(&(spu->stk), (int)spu->massiv_comand[a]) > 0) assert(0);

                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("8");
            }
            break;

            case Comandi_sqrt:
            {
                int64_t a = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), sqrt(a)) > 0) assert(0);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("9");
            }
            break;
                
            case Comandi_sin:
            {
                int64_t a = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), sin(a)) > 0) assert(0);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("10");
            }
            break;

            case Comandi_cos:
            {
                int64_t a = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);

                if (StackComandi_push(&(spu->stk), cos(a)) > 0) assert(0);
                
                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("11");
            }
            break;

            case Comandi_dump:
            {
                for (long long i = (long long)spu->stk.vacant_place - 1; i >= 0; i--)
                {
                    fprintf(stderr, "   [%lld] = ", i);
                    fprintf(stderr, "%lu\n", (long unsigned)spu->stk.array_data[i]);
                }

                spu->ip += PEREHOD_NA_KOMANDU;
                DEB_PR("12");
            }
            break;

            case Comandi_hlt:
            {
                DEB_PR("13");
                spu->vikluchatel_cikla = PEREHOD_NA_KOMANDU;
            }
            break;

            case Comandi_ja:                       //ctrl + H
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);
                
                if (b > a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("14");
            }
            break;

            case Comandi_jae:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (b >= a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("15");
            }
            break;

            case Comandi_jb:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (b < a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
            DEB_PR("16");
            }
            break;

            case Comandi_jbe:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (b <= a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("17");
            }
            break;

            case Comandi_je:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if (b == a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("18");
            }
            break;

            case Comandi_jne:
            {
                int64_t a = 0;
                int64_t b = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu->stk), &b) > 0) assert(0);

                if(b != a) { spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("19");
            }
            break;

            case Comandi_jmp:
            {
                spu->ip = spu->massiv_comand[spu->ip + PEREHOD_NA_KOMANDU];
                DEB_PR("20");
            }
            break;

            case Comandi_popr:
            {
                int64_t a = 0;
                if (StackComandi_pop(&(spu->stk), &a) > 0) assert(0);

                spu->registers[spu->massiv_comand[spu->ip + PEREHOD_NA_AEGUMENT]] = (int)a;
                spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT;
                DEB_PR("21");
            }
            break;

            case Comandi_pushr:
            {
                if (StackComandi_push(&(spu->stk), spu->registers[spu->massiv_comand[spu->ip + PEREHOD_NA_AEGUMENT]]) > 0) assert(0);

                spu->ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT;
                DEB_PR("22");
            }
            break;

            default: { assert(0); }
        }
    }

    return NET_OSHIBOK_SPU;
}