#include "asembler.h"
#include "globalniy_enum.h"
#include "schitivanie_faila.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>  
#include <assert.h>
#include <stdint.h>

enum Oshibki_Asemblera AsemblerCtor(Asembler_t* const asem, const char* asm_file_name, const char* bin_file_name)
{
    assert(asem != NULL);
    assert(asm_file_name != NULL);
    assert(bin_file_name != NULL);

    asem->komandi = fopen(asm_file_name, "r");
    asem->komandi_v_chislah = fopen(bin_file_name, "w + b"); // FIXME открывать в внешней функции записи его, до этого момента он не нужен
    if ((asem->komandi == nullptr) || (asem->komandi_v_chislah == nullptr))
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
        return OSHINKA_PRI_OTKRITII_FAILA;
    }

    asem->razmer_faila = Chitaet_razmer_faila(asem->komandi);
    asem->buffer = (char*)calloc(asem->razmer_faila, sizeof(char));
    fread(asem->buffer, sizeof(char), asem->razmer_faila, asem->komandi);

    // FIXME делать дефолтный размер, потом реалоцировать
    asem->massiv_comand = (int64_t*)calloc(asem->razmer_faila + 1, sizeof(int64_t));
    //fprintf(stderr, "\n%lu\n", asem->razmer_faila);
    //fprintf(stderr, "%s\n", asem->buffer);
    asem->struct_metok = (Metki_t*)calloc(MAX_COLICHESTVO_METOK, sizeof(Metki_t));

    for (int i = 0; i < MAX_COLICHESTVO_METOK; i++)
    {
        asem->struct_metok[i].adres_stroki = -1; // FIXME вынести счётчик
    }

    fclose (asem->komandi);
    return NET_OSHIBOK;
}

void AsemblerDtor(Asembler_t* const asem)
{
    assert(asem != NULL);

    fwrite(asem->massiv_comand, sizeof(int64_t), (uint64_t)asem->nomer_komandi, asem->komandi_v_chislah);
    fclose (asem->komandi_v_chislah); // FIXME закрывать так рано как можешь(в этом случае в конструкторе) СДЕЛАЛ

    free(asem->buffer);
    asem->buffer = NULL;

    free(asem->massiv_comand);
    asem->massiv_comand = NULL;
}

enum Oshibki_Asemblera Zapis_comand_pervichnaia(Asembler_t* const asem)
{
    assert(asem != NULL);

    char komanda[RAZMER_COMANDI] = {};
    char argument[RAZMER_ARGUMENTA] = {};
    char bufer_stroki[RAZMER_ARGUMENTA + RAZMER_ARGUMENTA] = {};

    for (char* posicia_v_buffere = asem->buffer; posicia_v_buffere < asem->buffer + asem->razmer_faila; posicia_v_buffere = strchr(posicia_v_buffere, '\n') + 1)
    {
        memcpy(bufer_stroki, posicia_v_buffere, strchr(posicia_v_buffere, '\n') - posicia_v_buffere);

        int kolichaestvo_slov_v_stroke = sscanf(bufer_stroki, "%s %s", komanda, argument);
        //fprintf(stderr, "--%d--\n", kolichaestvo_slov_v_stroke);
        enum Comandi opredelitel_metki_komanda = Perevod_asembler(komanda);
        enum Comandi opredelitel_metki_argument = Perevod_asembler(argument);

        if (kolichaestvo_slov_v_stroke == 1)
        {
            if (opredelitel_metki_komanda < 0) { Ishet_metku(asem, komanda); }
            // FIXME ++ сделать отдельно
            else { asem->massiv_comand[asem->nomer_komandi++] = opredelitel_metki_komanda; }
        }

        if (kolichaestvo_slov_v_stroke == 2)
        {
            asem->massiv_comand[asem->nomer_komandi++] = opredelitel_metki_komanda;
            if (opredelitel_metki_argument < 0) 
            {
                asem->massiv_comand[asem->nomer_komandi++]
                    = Ishet_metku_dla_jumpa(asem, argument, opredelitel_metki_komanda, opredelitel_metki_argument);
            }
            else { asem->massiv_comand[asem->nomer_komandi++] = opredelitel_metki_argument; }
        }

        memset(bufer_stroki, 0, RAZMER_ARGUMENTA + RAZMER_ARGUMENTA);
    }

    return NET_OSHIBOK;
}

// FIXME ставь const везде где можно
enum Oshibki_Asemblera Zapis_comand_votorichnaia(Asembler_t* const asem)
{
    assert(asem != NULL);

    char komanda[RAZMER_COMANDI] = {};
    char argument[RAZMER_ARGUMENTA] = {};
    char bufer_stroki[RAZMER_ARGUMENTA + RAZMER_ARGUMENTA] = {};

    int64_t bufer_razmera_masiva_kamand = asem->nomer_komandi;
    fprintf(stderr, "--%d--\n", asem->nomer_komandi);
    asem->nomer_komandi = 0;

    for (char* posicia_v_buffere = asem->buffer; posicia_v_buffere < asem->buffer + asem->razmer_faila; posicia_v_buffere = strchr(posicia_v_buffere, '\n') + 1)
    {
        memset(bufer_stroki, 0, RAZMER_ARGUMENTA + RAZMER_ARGUMENTA);
        memcpy(bufer_stroki, posicia_v_buffere, strchr(posicia_v_buffere, '\n') - posicia_v_buffere);

        int kolichaestvo_slov_v_stroke = sscanf(bufer_stroki, "%s %s", komanda, argument);

        enum Comandi opredelitel_metki_komanda = Perevod_asembler(komanda);
        enum Comandi opredelitel_metki_argument = Perevod_asembler(argument);

        if (kolichaestvo_slov_v_stroke == 1) 
        {
            if (opredelitel_metki_komanda < 0) {}
            else { asem->nomer_komandi++; }

            continue;
        }
        if (kolichaestvo_slov_v_stroke < 1) {
            assert(0 && "kolichaestvo_slov_v_stroke < 1");
            continue;
        } 

        asem->nomer_komandi++;

        if (opredelitel_metki_argument < 0) //метка или число
        {          
            if (isdigit(argument[0]) == 0)  //метка
            {
                for (int i = 0; i < MAX_COLICHESTVO_METOK; i++)
                {
                    if (strcmp(asem->struct_metok[i].metka, argument) == 0)
                    {
                        //fprintf(stderr, "--%d--\n", asem->massiv_comand[asem->nomer_komandi]);
                        //fprintf(stderr, "asem->nomer_komandi: %ld\n", asem->nomer_komandi);
                        //fprintf(stderr, "asem->struct_metok[i].adres_stroki: %ld\n",  asem->struct_metok[i].adres_stroki);

                        asem->massiv_comand[asem->nomer_komandi] = asem->struct_metok[i].adres_stroki;
                        asem->nomer_komandi++;
                        //fprintf(stderr, "asem->nomer_komandi: %ld\n", asem->nomer_komandi);
                        //fprintf(stderr, "--%d--\n", asem->massiv_comand[asem->nomer_komandi - 1]);
                    }
                }
            }
            else { asem->nomer_komandi++; }  //число

        }
        else { asem->nomer_komandi++; }  //регистр
    }

    fprintf(stderr, "--%d--\n", asem->nomer_komandi);
    asem->nomer_komandi = bufer_razmera_masiva_kamand;

    return NET_OSHIBOK;
}

enum Comandi Ishet_metku_dla_jumpa(Asembler_t* asem, char* argument, enum Comandi komanda_komanda, enum Comandi komanda_argument)
{
    assert(asem != NULL);
    assert(argument != NULL);

    if (isdigit(argument[0]) == 0)
    {
        for (int i = 0; i < MAX_COLICHESTVO_METOK; i++)
        {
            if (strcmp(asem->struct_metok[i].metka, argument) == 0) { return (enum Comandi)asem->struct_metok[i].adres_stroki; }
        }

        return (enum Comandi)0;
    }

    return (enum Comandi)strtol(argument, NULL, 10);
}

void Ishet_metku(Asembler_t* asem, char* slovo)
{
    assert(asem != NULL);
    assert(slovo != NULL);

    for(int i = 0; i < MAX_COLICHESTVO_METOK; i++)
    {
        if(asem->struct_metok[i].adres_stroki == -1)
        {
            strcpy(asem->struct_metok[i].metka, slovo); //записал метку в строку
            asem->struct_metok[i].adres_stroki = asem->nomer_komandi; //записал адрес для цикла

            break;
        }
    }
}


enum Comandi Perevod_asembler(const char* bufer_cmd)
{
    assert(bufer_cmd != NULL);

         if (strncmp(bufer_cmd, Comandi_push1,  sizeof(Comandi_push1))   == 0)   { return Comandi_push;  }
    else if (strncmp(bufer_cmd, Comandi_add1,   sizeof(Comandi_add1))    == 0)   { return Comandi_add;   }
    else if (strncmp(bufer_cmd, Comandi_sub1,   sizeof(Comandi_sub1))    == 0)   { return Comandi_sub;   }
    else if (strncmp(bufer_cmd, Comandi_mul1,   sizeof(Comandi_mul1))    == 0)   { return Comandi_mul;   }
    else if (strncmp(bufer_cmd, Comandi_divv1,  sizeof(Comandi_divv1))   == 0)   { return Comandi_divv;  }
    else if (strncmp(bufer_cmd, Comandi_out1,   sizeof(Comandi_out1))    == 0)   { return Comandi_out;   }
    else if (strncmp(bufer_cmd, Comandi_in1,    sizeof(Comandi_in1))     == 0)   { return Comandi_in;    }
    else if (strncmp(bufer_cmd, Comandi_sqrt1,  sizeof(Comandi_sqrt1))   == 0)   { return Comandi_sqrt;  }
    else if (strncmp(bufer_cmd, Comandi_sin1,   sizeof(Comandi_sin1))    == 0)   { return Comandi_sin;   }
    else if (strncmp(bufer_cmd, Comandi_cos1,   sizeof(Comandi_cos1))    == 0)   { return Comandi_cos;   }
    else if (strncmp(bufer_cmd, Comandi_dump1,  sizeof(Comandi_dump1))   == 0)   { return Comandi_dump;  }
    else if (strncmp(bufer_cmd, Comandi_hlt1,   sizeof(Comandi_hlt1))    == 0)   { return Comandi_hlt;   }
    else if (strncmp(bufer_cmd, Comandi_ja1,    sizeof(Comandi_ja1))     == 0)   { return Comandi_ja;    }
    else if (strncmp(bufer_cmd, Comandi_jae1,   sizeof(Comandi_jae1))    == 0)   { return Comandi_jae;   }
    else if (strncmp(bufer_cmd, Comandi_jb1,    sizeof(Comandi_jb1))     == 0)   { return Comandi_jb;    }
    else if (strncmp(bufer_cmd, Comandi_jbe1,   sizeof(Comandi_jbe))     == 0)   { return Comandi_jbe;   }
    else if (strncmp(bufer_cmd, Comandi_je1,    sizeof(Comandi_je1))     == 0)   { return Comandi_je;    }
    else if (strncmp(bufer_cmd, Comandi_jne1,   sizeof(Comandi_jne1))    == 0)   { return Comandi_jne;   }
    else if (strncmp(bufer_cmd, Comandi_jmp1,   sizeof(Comandi_jmp1))    == 0)   { return Comandi_jmp;   }
    else if (strncmp(bufer_cmd, Comandi_popr1,  sizeof(Comandi_popr1))   == 0)   { return Comandi_popr;  }
    else if (strncmp(bufer_cmd, Comandi_pushr1, sizeof(Comandi_pushr1))  == 0)   { return Comandi_pushr; }
    // FIXME вынести чек регистров в отдельную функцию
    else if (strncmp(bufer_cmd, Registri_ax1,   sizeof(Registri_ax1))    == 0)   { return Registri_ax;   }
    else if (strncmp(bufer_cmd, Registri_bx1,   sizeof(Registri_bx1))    == 0)   { return Registri_bx;   }
    else if (strncmp(bufer_cmd, Registri_cx1,   sizeof(Registri_cx1))    == 0)   { return Registri_cx;   }
    else if (strncmp(bufer_cmd, Registri_dx1,   sizeof(Registri_dx1))    == 0)   { return Registri_dx;   }
    else                                                                         { return Comandi_metka; } 
    // FIXME А если не правильная комманда а не метка
}






















// enum Oshibki_Asemblera Zapis_comand_pervichnaia(Asembler_t* asem)
// {
//     assert(asem != NULL);

//     char komanda[RAZMER_COMANDI] = {};
//     char argument[RAZMER_ARGUMENTA] = {};
//     char bufer_stroki[RAZMER_ARGUMENTA + RAZMER_ARGUMENTA] = {};

//     size_t slesh_n = 0;
//     for(char* posicia_v_buffere = asem->buffer; posicia_v_buffere < asem->buffer + asem->razmer_faila; posicia_v_buffere = strchr(posicia_v_buffere, '\n') + 1)
//     {
//         int kolichaestvo_slov_v_stroke = sscanf(posicia_v_buffere, "%s %s", komanda, argument);
//         fprintf(stderr, "--%d--\n", kolichaestvo_slov_v_stroke);
//         if (kolichaestvo_slov_v_stroke == 1)
//         {
//             fprintf(stderr, "%s\n", komanda);
//         }

//         if (kolichaestvo_slov_v_stroke == 2)
//         {
//             fprintf(stderr, "%s %s\n", komanda, argument);
//         }
//     }

//     return NET_OSHIBOK;
// }