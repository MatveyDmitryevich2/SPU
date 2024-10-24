#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

#include "asembler.h"
#include "globalniy_enum.h"
#include "schitivanie_faila.h"


int main(void)
{
    Asembler_t asem = {};
    AsemblerCtor(&asem, NACHALNIY_FAIL);

    Zapis_comand(&asem);
    asem.kolichestvo_komand = 0;
    Zapis_comand(&asem);

    for ( int i = 0; i < asem.schetchik_metok; i++)
    fprintf(stderr, "---%s---%ld---\n", asem.struct_metok[i].metka, asem.struct_metok[i].adres_stroki);

    for (int i = 0; i < asem.kolichestvo_komand; i++)
    {
        //fprintf(stderr, "[%d]: %d\n", i, asem.massiv_comand[i]);
        fprintf(stderr, "%ld ", asem.massiv_comand[i]);
    }

    AsemblerDtor(&asem, KONECNIY_FAIL);

    return 0;
}