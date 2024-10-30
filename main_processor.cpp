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

int main()
{
    double* massiv_comand_bufer = Chtenie_komand_is_faila(IMA_CHITAEMOGO_FAILA);

    Processor_t spu = {};
    Constructor_spu(&spu, massiv_comand_bufer);

    Execute_spu(&spu);

    Dtor_spu(&spu, massiv_comand_bufer);

    return 0;
}