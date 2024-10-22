#include "asembler.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>  
#include <assert.h>
#include <stdint.h>

#include "globalniy_enum.h"
#include "schitivanie_faila.h"

void Otkritie_asm (Asembler_t* const asem, const char* asm_file_name)
{
    assert(asem != NULL);
    assert(asm_file_name != NULL);

    FILE* komandi = fopen(asm_file_name, "r");
    if (komandi == nullptr)
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
        assert(0);
    }

    asem->razmer_faila = Chitaet_razmer_faila(komandi);
    asem->buffer = (char*)calloc(asem->razmer_faila + 1, sizeof(char));
    fread(asem->buffer, sizeof(char), asem->razmer_faila, komandi);
    fclose(komandi);
    komandi = NULL;
}

void Otkritie_bin (Asembler_t* const asem, const char* bin_file_name)
{
    assert(asem != NULL);
    assert(bin_file_name != NULL);

    FILE* komandi_v_chislah = fopen(bin_file_name, "w + b");
    if (komandi_v_chislah == nullptr)
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена");
        assert(0);
    }

    fwrite(asem->massiv_comand, sizeof(int64_t), (uint64_t)asem->kolichestvo_komand, komandi_v_chislah);
    fclose(komandi_v_chislah);
    komandi_v_chislah = NULL;
}

enum Oshibki_Asemblera AsemblerCtor(Asembler_t* const asem, const char* asm_file_name)
{
    assert(asem != NULL);
    assert(asm_file_name != NULL);

    Otkritie_asm (asem, asm_file_name);
    // FIXME делать дефолтный размер, потом реалоцировать при каждой записи
    asem->massiv_comand = (int64_t*)calloc(asem->razmer_faila, sizeof(int64_t));
    asem->struct_metok = (Metki_t*)calloc(MAX_COLICHESTVO_METOK, sizeof(Metki_t));
    asem->metka_na_metki = true;

    return NET_OSHIBOK;
}

void AsemblerDtor(Asembler_t* const asem, const char* bin_file_name)
{
    assert(asem != NULL);
    assert(bin_file_name != NULL);

    Otkritie_bin (asem, bin_file_name);

    free(asem->buffer);
    asem->buffer = NULL;

    free(asem->massiv_comand);
    asem->massiv_comand = NULL;
}

enum Oshibki_Asemblera Zapis_comand(Asembler_t* const asem)
{
    assert(asem != NULL);

    char komanda[RAZMER_COMANDI] = {};
    char type[RAZMER_COMANDI] = {};
    char argument[RAZMER_ARGUMENTA] = {};
    char argument_2[RAZMER_ARGUMENTA] = {};
    char bufer_stroki[RAZMER_COMANDI * 2 + RAZMER_ARGUMENTA * 2] = {};

    for (char* posicia_v_buffere = asem->buffer;
         posicia_v_buffere < asem->buffer + asem->razmer_faila;
         posicia_v_buffere = strchr(posicia_v_buffere, '\n') + 1)
    {
        memcpy(bufer_stroki, posicia_v_buffere, strchr(posicia_v_buffere, '\n') - posicia_v_buffere);
        
        sscanf(bufer_stroki, "%s", komanda); 
        enum Comandi opredelitel_metki_komanda = Perevod_asembler(komanda);

        if ((opredelitel_metki_komanda != Comandi_push) && (opredelitel_metki_komanda != Comandi_pop))
        {
            int kolichaestvo_slov_v_stroke = sscanf(bufer_stroki, "%s %s", komanda, argument);
            //fprintf(stderr, "--%d--\n", kolichaestvo_slov_v_stroke);
            enum Comandi opredelitel_metki_argument = Perevod_asembler(argument);

            if (kolichaestvo_slov_v_stroke == 1)
            {
                if (opredelitel_metki_komanda < 0) 
                { 
                    if (asem->metka_na_metki) { Ishet_metku(asem, komanda); }
                }
                else { asem->massiv_comand[asem->kolichestvo_komand++] = opredelitel_metki_komanda; }
            }

            if (kolichaestvo_slov_v_stroke == 2)
            {
                asem->massiv_comand[asem->kolichestvo_komand++] = opredelitel_metki_komanda;
                if (opredelitel_metki_argument < 0) 
                {
                    asem->massiv_comand[asem->kolichestvo_komand++]
                        = Ishet_metku_dla_jumpa(asem, argument, opredelitel_metki_komanda, opredelitel_metki_argument);
                }
                else { asem->massiv_comand[asem->kolichestvo_komand++] = opredelitel_metki_argument; }
            }
        }
        if (opredelitel_metki_komanda == Comandi_push)
        {
            if (strchr(bufer_stroki, '[') == NULL) 
            {
                int kolichaestvo_slov_v_stroke = sscanf(bufer_stroki, "%s %s + %s", komanda, argument, argument_2);

                if (kolichaestvo_slov_v_stroke == 2)
                {
                    asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(komanda);

                    if (Perevod_asembler(argument) < 0) 
                    { 
                        asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT;
                        asem->massiv_comand[asem->kolichestvo_komand++] = (enum Comandi)strtol(argument, NULL, 10);
                    }
                    else 
                    { 
                        asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT;
                        asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument);
                    }
                }
                if (kolichaestvo_slov_v_stroke == 3)
                {
                    asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(komanda);
                    asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT + VTOROY_BIT;
                    asem->massiv_comand[asem->kolichestvo_komand++] = (enum Comandi)strtol(argument, NULL, 10);
                    asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument_2);
                }

            }
            else
            {
                int kolichaestvo_slov_v_stroke = sscanf(strchr(bufer_stroki, '[') + 1, "%s + %s", argument, argument_2);
                asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(komanda);

                if (kolichaestvo_slov_v_stroke == 1)
                {
                    if (Perevod_asembler(argument) < 0)
                    {
                        asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT + TRETIY_BIT;
                        asem->massiv_comand[asem->kolichestvo_komand++] = (enum Comandi)strtol(argument, NULL, 10);
                    }
                    else
                    {
                        asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT + TRETIY_BIT;
                        asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument);
                    }
                }
                if (kolichaestvo_slov_v_stroke == 2)
                {
                    asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT + VTOROY_BIT + TRETIY_BIT;
                    asem->massiv_comand[asem->kolichestvo_komand++] = (enum Comandi)strtol(argument, NULL, 10);
                    asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument_2);
                }
            }
        }
        if (opredelitel_metki_komanda == Comandi_pop)
        {
            if (strchr(bufer_stroki, '[') == NULL)
            {
                sscanf(bufer_stroki, "%s %s", komanda, argument);
                asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(komanda);
                asem->massiv_comand[asem->kolichestvo_komand++] = CHETVERTIY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument);
            }
            else
            {
                int kolichaestvo_slov_v_stroke = sscanf(strchr(bufer_stroki, '[') + 1, "%s + %s", argument, argument_2);
                asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(komanda);
                
                if (kolichaestvo_slov_v_stroke == 2)
                {
                    asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT + PERVIY_BIT;
                    asem->massiv_comand[asem->kolichestvo_komand++] = (enum Comandi)strtol(argument, NULL, 10);
                    asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument_2);
                }
                if (kolichaestvo_slov_v_stroke == 1)
                {
                    if (Perevod_asembler(argument) < 0)
                    {
                        asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT;
                        asem->massiv_comand[asem->kolichestvo_komand++] = (enum Comandi)strtol(argument, NULL, 10);
                    }
                    else
                    {
                        asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT;
                        asem->massiv_comand[asem->kolichestvo_komand++] = Perevod_asembler(argument);
                    }
                }
            }
        }

        memset(bufer_stroki, 0, RAZMER_ARGUMENTA * 2 + RAZMER_ARGUMENTA * 2);
        memset(komanda, 0, RAZMER_COMANDI);
        memset(type, 0, RAZMER_COMANDI);
        memset(argument, 0, RAZMER_ARGUMENTA);
        memset(argument_2, 0, RAZMER_ARGUMENTA);
    }
    asem->metka_na_metki = false;
    return NET_OSHIBOK;
}
//FIXME const ставить
enum Comandi Ishet_metku_dla_jumpa(Asembler_t* asem, 
                                   char* argument, 
                                   enum Comandi komanda_komanda, 
                                   enum Comandi komanda_argument)
{
    assert(asem != NULL);
    assert(argument != NULL);

    if (isdigit(argument[0]) == 0)
    {
        for (int i = 0; i < MAX_COLICHESTVO_METOK; i++)
        {
            if (strcmp(asem->struct_metok[i].metka, argument) == 0)
            {
                return (enum Comandi)asem->struct_metok[i].adres_stroki;
            }
        }

        return (enum Comandi)0;
    }

    return (enum Comandi)strtol(argument, NULL, 10);
}

void Ishet_metku(Asembler_t* asem, char* slovo)
{
    assert(asem != NULL);
    assert(slovo != NULL);

    
    strcpy(asem->struct_metok[asem->schetchik_metok].metka, slovo);
    asem->struct_metok[asem->schetchik_metok].adres_stroki = asem->kolichestvo_komand;
    asem->schetchik_metok++;
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
    else if (strncmp(bufer_cmd, Comandi_pop1,   sizeof(Comandi_pop1))    == 0)   { return Comandi_pop;   }
    // FIXME вынести чек регистров в отдельную функцию
    else if (strncmp(bufer_cmd, Registri_ax1,   sizeof(Registri_ax1))    == 0)   { return Registri_ax;   }
    else if (strncmp(bufer_cmd, Registri_bx1,   sizeof(Registri_bx1))    == 0)   { return Registri_bx;   }
    else if (strncmp(bufer_cmd, Registri_cx1,   sizeof(Registri_cx1))    == 0)   { return Registri_cx;   }
    else if (strncmp(bufer_cmd, Registri_dx1,   sizeof(Registri_dx1))    == 0)   { return Registri_dx;   }
    else                                                                         { return Comandi_metka; } 
    // FIXME А если не правильная комманда а не метка
}