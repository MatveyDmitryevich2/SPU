#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "stack.h"
#include "processor.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"

int main(void)
{
    int64_t* massiv_comand_bufer = Chtenie_komand_is_faila();

    Processor_t spu = {}; // FIXME обрабатывать через if и функцию обработки
    if (SPUConstrtor(&spu, massiv_comand_bufer) > 0) { assert(0); }

    // FIXME вынести в функцию execute
    while (spu.vikluchatel_cikla == 0) 
    {
        switch (spu.massiv_comand[spu.ip])
        {
            case Comandi_push:
            {
                if (StackComandi_push(&(spu.stk), (int)spu.massiv_comand[spu.ip + PEREHOD_NA_AEGUMENT]) > 0) { assert(0); }
                
                spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT;
                DEB_PR("1");
            }
            break;
        
            case Comandi_add: 
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), b + a) > 0) assert(0);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("2");
            }
            break;

            case Comandi_sub:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), b - a) > 0) assert(0);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("4");
            }
            break;

            case Comandi_mul:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), b * a) > 0) assert(0);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("5");
            }
            break;

            case Comandi_divv:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), b / a) > 0) assert(0);

                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("6");
            }
            break;

            case Comandi_out:
            {
                int a = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);

                printf("%d\n", a);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("7");
            }
            break;

            case Comandi_in:
            {
                int a = 0;
                scanf("%d", &a);
                if (StackComandi_push(&(spu.stk), (int)spu.massiv_comand[a]) > 0) assert(0);

                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("8");
            }
            break;

            case Comandi_sqrt:
            {
                int a = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), sqrt(a)) > 0) assert(0);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("9");
            }
            break;
                
            case Comandi_sin:
            {
                int a = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), sin(a)) > 0) assert(0);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("10");
            }
            break;

            case Comandi_cos:
            {
                int a = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);

                if (StackComandi_push(&(spu.stk), cos(a)) > 0) assert(0);
                
                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("11");
            }
            break;

            case Comandi_dump:
            {
                for (long long i = (long long)spu.stk.vacant_place - 1; i >= 0; i--)
                {
                    fprintf(stderr, "   [%lld] = ", i);
                    fprintf(stderr, "%lu\n", (long unsigned)spu.stk.array_data[i]);
                }

                spu.ip += PEREHOD_NA_KOMANDU;
                DEB_PR("12");
            }
            break;

            case Comandi_hlt:
            {
                DEB_PR("13");
                spu.vikluchatel_cikla = PEREHOD_NA_KOMANDU;
            }
            break;

            case Comandi_ja:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);
                
                if (b > a) { spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("14");
            }
            break;

            case Comandi_jae:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (b >= a) { spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("15");
            }
            break;

            case Comandi_jb:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (b < a) { spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
            DEB_PR("16");
            }
            break;

            case Comandi_jbe:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (b <= a) { spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("17");
            }
            break;

            case Comandi_je:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if (b == a) { spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("18");
            }
            break;

            case Comandi_jne:
            {
                int a = 0;
                int b = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);
                if (StackComandi_pop(&(spu.stk), &b) > 0) assert(0);

                if(b != a) { spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU]; }                      
                else { spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT; }
                DEB_PR("19");
            }
            break;

            case Comandi_jmp:
            {
                spu.ip = spu.massiv_comand[spu.ip + PEREHOD_NA_KOMANDU];
                DEB_PR("20");
            }
            break;

            case Comandi_popr:
            {
                int a = 0;
                if (StackComandi_pop(&(spu.stk), &a) > 0) assert(0);

                spu.registers[spu.massiv_comand[spu.ip + PEREHOD_NA_AEGUMENT]] = a;
                spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT;
                DEB_PR("21");
            }
            break;

            case Comandi_pushr:
            {
                if (StackComandi_push(&(spu.stk), spu.registers[spu.massiv_comand[spu.ip + PEREHOD_NA_AEGUMENT]]) > 0) assert(0);

                spu.ip += PEREHOD_NA_KOMANDU + PEREHOD_NA_AEGUMENT;
                DEB_PR("22");
            }
            break;
        }
    }

    //fprintf(stderr, "%d\n", stk.array_data[0]);

    StackDtor(&(spu.stk)); // FIXME вызывать в spu dtor
    SPUDtor(massiv_comand_bufer);

    return 0;
}