#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

#include "asembler.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"

int main(void)
{
    // FIXME вынести в функцию
    FILE* komandi = fopen("Komandi.txt", "r");
    FILE* komandi_v_chislah = fopen("Chislovie_komani.txt", "w + b");
    if ((komandi == nullptr) || (komandi_v_chislah == nullptr))
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
        return EXIT_FAILURE;
    }

    // FIXME size_t а не uint64_t, размер же
    uint64_t razmer_faila = Chitaet_razmer_faila(komandi);
    char* buffer = (char*)calloc(razmer_faila + 1, sizeof(char));
    fread(buffer, sizeof(char), razmer_faila, komandi);

    int64_t* massiv_comand = (int64_t*)calloc(razmer_faila + 1, sizeof(int64_t));
    //fprintf(stderr, "\n%lu\n", razmer_faila);

    //fprintf(stderr, "%s\n", buffer);

    // FIXME вынести до сюда

    // FIXME -v- вынести в функцию ассемблирования, main должен быть небольшим
    char bufer_cmd[25] = "";

    int64_t cteracia_dla_massiv_comand = 0;
    int64_t ateracia_dla_zapisi_slova = 0;
    for (uint64_t iteracia_po_simvolam = 0; iteracia_po_simvolam <= razmer_faila; 
         iteracia_po_simvolam++, ateracia_dla_zapisi_slova++)
    {
        if ((buffer[iteracia_po_simvolam] != ' ') && (buffer[iteracia_po_simvolam] != '\n'))
        {
            fprintf(stderr, "a: %ld\n", ateracia_dla_zapisi_slova);
            bufer_cmd[ateracia_dla_zapisi_slova] = buffer[iteracia_po_simvolam];
            fprintf(stderr, "%c\n", buffer[iteracia_po_simvolam]);
        }

        else
        {
            fprintf(stderr, "cmd: %s\n", bufer_cmd);

            Comandi kakaia_komanda = Menaet_komandu_na_enum(bufer_cmd);
            if (kakaia_komanda < 0) 
            { 
                massiv_comand[cteracia_dla_massiv_comand] = (int64_t)strtol(bufer_cmd, NULL, 10); 
            }
            else 
            { 
                massiv_comand[cteracia_dla_massiv_comand] = kakaia_komanda; 
            }

            cteracia_dla_massiv_comand++;

            memset(bufer_cmd, 0, 25); // FIXME вынести 25 в константу 

            ateracia_dla_zapisi_slova = -1;
        }
    }

    fwrite(massiv_comand, sizeof(int64_t), (uint64_t)cteracia_dla_massiv_comand, komandi_v_chislah);

    AsemblerDtor(komandi_v_chislah, komandi, buffer, massiv_comand);

    return 0;
}
