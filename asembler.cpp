#include "asembler.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

enum Oshibki_Asemblera AsemblerCtor(Asembler_t* spu)
{    
    if (spu == NULL) { return UKAZTENEL_NA_STRUKTURU_ASEMBLER_POEHAL; }

    spu->komandi = fopen("Komandi.txt", "r");
    spu->komandi_v_chislah = fopen("Chislovie_komani.txt", "w + b");
    if ((spu->komandi == nullptr) || (spu->komandi_v_chislah == nullptr))
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
        return OSHINKA_PRI_OTKRITII_FAILA;
    }

    spu->razmer_faila = Chitaet_razmer_faila(spu->komandi);
    spu->buffer = (char*)calloc(spu->razmer_faila + 1, sizeof(char));
    fread(spu->buffer, sizeof(char), spu->razmer_faila, spu->komandi);

    spu->massiv_comand = (int64_t*)calloc(spu->razmer_faila + 1, sizeof(int64_t));
    //fprintf(stderr, "\n%lu\n", spu->razmer_faila);
    //fprintf(stderr, "%s\n", spu->buffer);
    spu->struct_metok = (struct Metki_t*)calloc(MAX_COLICHESTVO_METOK, sizeof(Metki_t));

    for (int i = 0; i < MAX_COLICHESTVO_METOK; i++)
    {
        spu->struct_metok[i].adres_stroki = -1;
    }

    return NET_OSHIBOK;
}

enum Oshibki_Asemblera Zapis_comand(Asembler_t* spu)
{
    if (spu == NULL) { return UKAZTENEL_NA_STRUKTURU_ASEMBLER_POEHAL; }

    char bufer_cmd[RAZMER_COMANDI] = "";

    int64_t ateracia_dla_zapisi_slova = 0;
    for (uint64_t iteracia_po_simvolam = 0; iteracia_po_simvolam <= spu->razmer_faila; 
         iteracia_po_simvolam++, ateracia_dla_zapisi_slova++)
    {
        if ((spu->buffer[iteracia_po_simvolam] != ' ') && (spu->buffer[iteracia_po_simvolam] != '\n'))
        {
            fprintf(stderr, "a: %ld\n", ateracia_dla_zapisi_slova);
            bufer_cmd[ateracia_dla_zapisi_slova] = spu->buffer[iteracia_po_simvolam];
            fprintf(stderr, "%c\n", spu->buffer[iteracia_po_simvolam]);
        }

        else
        {
            fprintf(stderr, "cmd: %s\n", bufer_cmd);

            Comandi kakaia_komanda = Menaet_komandu_na_enum(bufer_cmd);
            if (kakaia_komanda < 0) 
            { 
                spu->massiv_comand[spu->cteracia_dla_massiv_comand] = strtol(bufer_cmd, NULL, 10); 
            }
            else 
            { 
                spu->massiv_comand[spu->cteracia_dla_massiv_comand] = kakaia_komanda; 
            }

            spu->cteracia_dla_massiv_comand++;

            memset(bufer_cmd, 0, RAZMER_COMANDI);

            ateracia_dla_zapisi_slova = -1;
        }
    }

    return NET_OSHIBOK;
}

enum Comandi Menaet_komandu_na_enum(char* bufer_cmd)
{
         if (strncmp(bufer_cmd, Comandi_push1,  sizeof(Comandi_push1))  == 0) { return Comandi_push;  }
    else if (strncmp(bufer_cmd, Comandi_add1,   sizeof(Comandi_add1))   == 0) { return Comandi_add;   }
    else if (strncmp(bufer_cmd, Comandi_sub1,   sizeof(Comandi_sub1))   == 0) { return Comandi_sub;   }
    else if (strncmp(bufer_cmd, Comandi_mul1,   sizeof(Comandi_mul1))   == 0) { return Comandi_mul;   }
    else if (strncmp(bufer_cmd, Comandi_divv1,  sizeof(Comandi_divv1))  == 0) { return Comandi_divv;  }
    else if (strncmp(bufer_cmd, Comandi_out1,   sizeof(Comandi_out1))   == 0) { return Comandi_out;   }
    else if (strncmp(bufer_cmd, Comandi_in1,    sizeof(Comandi_in1))    == 0) { return Comandi_in;    }
    else if (strncmp(bufer_cmd, Comandi_sqrt1,  sizeof(Comandi_sqrt1))  == 0) { return Comandi_sqrt;  }
    else if (strncmp(bufer_cmd, Comandi_sin1,   sizeof(Comandi_sin1))   == 0) { return Comandi_sin;   }
    else if (strncmp(bufer_cmd, Comandi_cos1,   sizeof(Comandi_cos1))   == 0) { return Comandi_cos;   }
    else if (strncmp(bufer_cmd, Comandi_dump1,  sizeof(Comandi_dump1))  == 0) { return Comandi_dump;  }
    else if (strncmp(bufer_cmd, Comandi_hlt1,   sizeof(Comandi_hlt1))   == 0) { return Comandi_hlt;   }
    else if (strncmp(bufer_cmd, Comandi_ja1,    sizeof(Comandi_ja1))    == 0) { return Comandi_ja;    }
    else if (strncmp(bufer_cmd, Comandi_jae1,   sizeof(Comandi_jae1))   == 0) { return Comandi_jae;   }
    else if (strncmp(bufer_cmd, Comandi_jb1,    sizeof(Comandi_jb1))    == 0) { return Comandi_jb;    }
    else if (strncmp(bufer_cmd, Comandi_jbe1,   sizeof(Comandi_jbe))    == 0) { return Comandi_jbe;   }
    else if (strncmp(bufer_cmd, Comandi_je1,    sizeof(Comandi_je1))    == 0) { return Comandi_je;    }
    else if (strncmp(bufer_cmd, Comandi_jne1,   sizeof(Comandi_jne1))   == 0) { return Comandi_jne;   }
    else if (strncmp(bufer_cmd, Comandi_jmp1,   sizeof(Comandi_jmp1))   == 0) { return Comandi_jmp;   }
    else if (strncmp(bufer_cmd, Comandi_popr1,  sizeof(Comandi_popr1))  == 0) { return Comandi_popr;  }
    else if (strncmp(bufer_cmd, Comandi_pushr1, sizeof(Comandi_pushr1)) == 0) { return Comandi_pushr; }
    else if (strncmp(bufer_cmd, Comandi_ax1,    sizeof(Comandi_ax1))    == 0) { return Comandi_ax;    }
    else if (strncmp(bufer_cmd, Comandi_bx1,    sizeof(Comandi_bx1))    == 0) { return Comandi_bx;    }
    else if (strncmp(bufer_cmd, Comandi_cx1,    sizeof(Comandi_cx1))    == 0) { return Comandi_cx;    }
    else if (strncmp(bufer_cmd, Comandi_dx1,    sizeof(Comandi_dx1))    == 0) { return Comandi_dx;    }
    else                                                                      { return Comandi_chislo;}
}

void AsemblerDtor(Asembler_t* spu)
{
    fclose (spu->komandi_v_chislah);
    fclose (spu->komandi);

    free(spu->buffer);
    spu->buffer = NULL;

    free(spu->massiv_comand);
    spu->massiv_comand = NULL;
}