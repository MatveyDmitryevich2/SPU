#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

#include "asembler.h"
#include "globalniy_enum.h"
#include "schitivanie_faila.h"

//FIXME испрвивть хеш в стеке
//git status
//git add .
//git status
//git commit -m ""
//git push


int main(const int argc, const char *argv[])
{
    Asembler_t asem = {};
    Asembler_ctor(&asem, Schitivanie_nasvania_faila(argc, argv));

    Zapis_comand_v_massiv(&asem);
    asem.kolichestvo_komand = 0;
    Zapis_comand_v_massiv(&asem);

    for (int i = 0; i < asem.schetchik_metok; i++)
    {
        fprintf(stderr, "---%s---%lu---\n", asem.struct_metok[i].metka, asem.struct_metok[i].adres_stroki);
    }

    for (size_t i = 0; i < asem.kolichestvo_komand; i++)
    {
        //fprintf(stderr, "[%d]: %d\n", i, asem.massiv_comand[i]);
        fprintf(stderr, "%ld ", asem.massiv_comand[i]);
    }

    Zapis_massiva_cmd_v_fail (&asem, KONECNIY_FAIL);
    Asembler_dtor (&asem);

    return 0;
}