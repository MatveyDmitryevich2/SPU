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

int main(void) // НУ ТЫ И ДАУН - нахуя void
{
    int64_t* massiv_comand_bufer = Chtenie_komand_is_faila(IMA_CHITAEMOGO_FAILA);
    //                             ^
    //                             ---------------- Почему разные стили названий функций
    Processor_t spu = {}; //                      | 
    SPUConstrtor(&spu, massiv_comand_bufer); // < | SPUConstrrrrrrtor  
                                             //   |
    ExecuteSPU(&spu); //                        < |
    //                                            |
    SPUDtor(&spu, massiv_comand_bufer); //      < |

    return 0;
}