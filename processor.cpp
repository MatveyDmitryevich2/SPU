#include "processor.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

enum Oshibki_SPU SPUConstrtor(Processor_t* spu)
{
    if (spu == NULL) { return UKAZTENEL_NA_STRUKTURU_SPU_POEHAL; }

    int64_t chooo1[] = {1, 0, 21, 0, 22, 0, 22, 0, 5, 7, 22, 0, 1, 1, 2, 21, 0, 22, 0, 1, 10, 17, 4, 13};
    spu->ip = 0;
    spu->vikluchatel_cikla = 0;
    spu->massiv_comand = chooo1;

    return NET_OSHIBOK;
}