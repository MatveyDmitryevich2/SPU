#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

static void DrowSPU(int64_t* massiv);//a = 51  b = 1

int main()
{
    int64_t ram[10000];

    for(size_t a = 0; a <= 10; a++)
    {
        for (size_t i = 0; i <= 10; i++)
        {
            ram[1000 + i + a * 11] = 0; // 56 - 86
            if ((i - 5) * (i - 5) + (a - 5) * (a - 5) <= 25) { ram[1000 + i + a * 11] = 1; }
        }
    }
    ram[1000 + 5 + 5 * 11] = 1;



    DrowSPU(ram);

    return 0;
}

static void DrowSPU(int64_t* massiv) //с тысячного адрeса начинается видеопамять
{
    for(size_t a = 0; a <= 10; a++)
    {
        for (size_t i = 0; i <= 10; i++)
        {
            if (massiv[i + a * 11 + 1000] == 0) { fprintf(stderr, "%c  ", '*'); }
            else                                { fprintf(stderr, "%c  ", '8'); }
        }
        fprintf(stderr, "\n");
    }
}