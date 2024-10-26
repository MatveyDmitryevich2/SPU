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
    Asembler_ctor(&asem, NACHALNIY_FAIL);

    Zapis_comand_v_massiv(&asem);
    asem.kolichestvo_komand = 0;
    Zapis_comand_v_massiv(&asem);

    for (int i = 0; i < asem.schetchik_metok; i++) // FIXME добавь таб V
    fprintf(stderr, "---%s---%lu---\n", asem.struct_metok[i].metka, asem.struct_metok[i].adres_stroki);

    for (size_t i = 0; i < asem.kolichestvo_komand; i++)
    {
        //fprintf(stderr, "[%d]: %d\n", i, asem.massiv_comand[i]);
        fprintf(stderr, "%ld ", asem.massiv_comand[i]);
    }
    // FIXME    V Пробел
    Otkritie_bin (&asem, KONECNIY_FAIL); // FIXME название говно
    Asembler_dtor(&asem);

    return 0;
}