#include "schitivanie_faila.h"

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

uint64_t Chitaet_razmer_faila(FILE* komandi)
{
    assert(komandi != NULL);

    fseek(komandi, 0, SEEK_END);
    size_t razmer_faila = (size_t)ftell(komandi);
    fseek(komandi, 0, SEEK_SET);

    return razmer_faila;
}