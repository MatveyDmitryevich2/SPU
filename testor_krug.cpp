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
    for(size_t a = 0; a <= 50; a++)
    {
        for (size_t i = 0; i <= 50; i++)
        {
            ram[1000 + i + a * 51] = 0; // 56 - 86
            if ((i - 25) * (i - 25) + (a - 25) * (a - 25) <= 100) { ram[1000 + i + a * 51] = 1; }
        }
    }
    ram[1000 + 25 + 25 * 51] = 1;
    DrowSPU(ram);
    return 0;
}
static void DrowSPU(int64_t* massiv) //с тысячного адрeса начинается видеопамять
{
    for(size_t a = 0; a <= 50; a++)
    {
        for (size_t i = 0; i <= 50; i++)
        {
            if (massiv[i + a * 51 + 1000] == 0) { fprintf(stderr, "%c  ", '*'); }
            else                                { fprintf(stderr, "%c  ", '8'); }
        }
        fprintf(stderr, "\n");
    }
}