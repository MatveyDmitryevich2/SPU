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
    Oshibki_Asemblera asm_error = AsemblerCtor(&asem, NACHALNIY_FAIL, KONECNIY_FAIL);

    Zapis_comand_pervichnaia(&asem);
    Zapis_comand_votorichnaia(&asem);

    //fprintf(stderr, "---%s---%d---\n", asem.struct_metok->metka, asem.struct_metok->adres_stroki);

    for (int i = 0; i < asem.nomer_komandi; i++)
    {
        //fprintf(stderr, "[%d]: %d\n", i, asem.massiv_comand[i]);
        fprintf(stderr, "%d ", asem.massiv_comand[i]);
    }

    AsemblerDtor(&asem);

    return 0;
}


//1 0 21 0 22 0 22 0 5 7 22 0 1 1 2 21 0 22 0 1 10 17 0 13 первичная
//1 0 21 0 22 0 22 0 5 7 22 0 1 1 2 21 0 22 0 1 10 17 23 13 вторичная

//1 0 21 0 22 0 22 0 5 7 22 0 1 1 2 21 0 22 0 1 10 17 23 13