#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

int main()
{
    char numbers[] = "70";
    uint64_t a = strtol(numbers, NULL, 10);
    printf("%lu", a);

    return 0;
}