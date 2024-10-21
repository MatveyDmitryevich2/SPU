#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "stack.h"
#include "processor.h"
#include "globalniy_enum.h"
#include "schitivanie_faila.h"
#include "utils.h"

int main(void)
{
    int64_t* massiv_comand_bufer = Chtenie_komand_is_faila(IMA_CHITAEMOGO_FAILA);

    Processor_t spu = {};
    SPUConstrtor(&spu, massiv_comand_bufer);

    ExecuteSPU (&spu);
    //fprintf(stderr, "%d\n", stk.array_data[0]);

    SPUDtor(&spu, massiv_comand_bufer);

    return 0;
}