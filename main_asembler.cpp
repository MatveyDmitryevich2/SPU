#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

#include "asembler.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"

int main(void)
{
    Asembler_t spu = {};
    AsemblerCtor(&spu);

    Zapis_comand(&spu);

    fwrite(spu.massiv_comand, sizeof(int64_t), (uint64_t)spu.cteracia_dla_massiv_comand, spu.komandi_v_chislah);

    AsemblerDtor(&spu);

    return 0;
}
