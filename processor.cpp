#include "processor.h"
#include "stack.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

enum Oshibki_SPU SPUConstrtor(Processor_t* spu, int64_t* massiv_comand_bufer)
{
    // FIXME assert spu massiv_comand_bufer
    if (spu == NULL) { return UKAZTENEL_NA_STRUKTURU_SPU_POEHAL; }

    if (StackConstrtor(&spu->stk, 2) > 0) assert(0);
    spu->ip = 0;
    spu->vikluchatel_cikla = false;
    spu->massiv_comand = massiv_comand_bufer;

    return NET_OSHIBOK_SPU;
}

int SPUDtor(int64_t* massiv_comand_bufer)
{
    // FIXME assert

    free(massiv_comand_bufer);
    // massiv_comand_bufer = NULL;

    return 0; // FIXME void function 
}

int64_t* Chtenie_komand_is_faila() // FIXME передавать имя файла 
{
    FILE* komandi_v_chislah = fopen("Chislovie_komani.txt", "r");
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