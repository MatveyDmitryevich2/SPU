#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

#include "asembler.h"

int main(void)
{
    FILE* komandi = fopen("Komandi.txt", "r");
    if (komandi == nullptr)
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
        return EXIT_FAILURE;
    }

    uint64_t razmer_faila = Chitaet_razmer_faila(komandi);
    char* buffer = (char*)calloc(razmer_faila + 1, sizeof(char));
    fread(buffer, sizeof(char), razmer_faila, komandi);

    uint64_t* massiv_comand = (uint64_t*)calloc(razmer_faila + 1, sizeof(uint64_t));
    //fprintf(stderr, "\n%lu\n", razmer_faila);

    //fprintf(stderr, "%s\n", buffer);

    char bufer_cmd[25] = "";

    for (int64_t iteracia_po_simvolam = 0, ateracia_dla_zapisi_slova = 0, cteracia_dla_massiv_comand = 0; 
         iteracia_po_simvolam <= razmer_faila; iteracia_po_simvolam++, ateracia_dla_zapisi_slova++)
    {
        if ((buffer[iteracia_po_simvolam] != ' ') && (buffer[iteracia_po_simvolam] != '\n'))
        {
            fprintf(stderr, "a: %d\n", ateracia_dla_zapisi_slova);
            bufer_cmd[ateracia_dla_zapisi_slova] = buffer[iteracia_po_simvolam];
            fprintf(stderr, "%c\n", buffer[iteracia_po_simvolam]);
        }

        else
        {
            fprintf(stderr, "cmd: %s\n", bufer_cmd);

            enum Comandi kakaia_komanda = Menaet_komandu_na_enum(bufer_cmd);
            if (kakaia_komanda < 0) { massiv_comand[cteracia_dla_massiv_comand] = (uint64_t)strtol(bufer_cmd, NULL, 10); }
            else { massiv_comand[cteracia_dla_massiv_comand] = kakaia_komanda; }
            cteracia_dla_massiv_comand++;

            memset(bufer_cmd, 0, 25);

            ateracia_dla_zapisi_slova = -1;
        }
    }

    for (size_t i = 0; i <= razmer_faila; i++)
    {
        fprintf(stderr, "%lu", massiv_comand[i]);
    }

    free(buffer);
    buffer = NULL;

    free(massiv_comand);
    massiv_comand = NULL;
    return 0;
}
