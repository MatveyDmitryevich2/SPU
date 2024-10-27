#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

static void DrowSPU(int64_t* massiv);

int main()
{
    int64_t ram[10000];

    for(size_t a = 1; a <= 51; a++)
    {
        for (size_t i = 0; i <= 50; i++)
        {
            ram[1000 + i + a * 51] = 0;
            if (((i - 25) * (i - 25) + (a - (25 + 1)) * (a - (25 + 1))) == 625) { ram[1000 + i + a * 51] = 1; }
        }
    }
    ram[1000 + 25 + 26 * 51] = 4;



    DrowSPU(ram);

    return 0;
}

static void DrowSPU(int64_t* massiv) //с тысячного адерса начинается видеопамять
{
    for(size_t a = 1; a <= 51; a++)
    {
        for (size_t i = 0; i <= 50; i++)
        {
            if (massiv[i + a * 51 + 1000] == 0) { fprintf(stderr, "%c ", '*'); }
            else                                { fprintf(stderr, "%c ", '0'); }
        }
        fprintf(stderr, "\n");
    }
}