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
#include "utils.h"

int main(void)
{
    int64_t* massiv_comand_bufer = Chtenie_komand_is_faila(IMA_FAILA);

    Processor_t spu = {};
    SPUConstrtor(&spu, massiv_comand_bufer); // FIXME обрабатывать через if и функцию обработки

    ExecuteSPU (&spu);
    //fprintf(stderr, "%d\n", stk.array_data[0]);

    SPUDtor(&spu, massiv_comand_bufer);

    return 0;
}