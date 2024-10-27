#include "asembler.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>  
#include <assert.h>
#include <stdint.h>

#include "globalniy_enum.h"
#include "schitivanie_faila.h"

static void Otkritie_asm(Asembler_t* const asem, const char* asm_file_name);
static void Realoc_na_massiv_comand(Asembler_t* const asem);
static void Zanulenie_strok_posle_raboti_so_strokoy(Asembler_t* const asem);
static size_t Schitaet_razmer_stroki(Asembler_t* const asem);
static bool Poisk_pustoy_stroki(Asembler_t* const asem);
static enum Comandi Poisk_komandi(const char* bufer_cmd);
static enum Comandi Poisk_registra(const char* bufer_cmd);
static enum Comandi Poisk_metki(const char* bufer_cmd);
static enum Opredelenie_comandi Handler(Asembler_t* const asem);
static void Rabota_s_komandoi(Asembler_t* const asem);
static void Rabota_s_comandami_bez_argumenta(Asembler_t* const asem);
static void Rabota_s_poprigunchikami(Asembler_t* const asem);
static int64_t Ishet_metku_dla_jumpa(Asembler_t* const asem);
static void Rabota_s_push(Asembler_t* const asem);
static void Rabota_s_pop(Asembler_t* const asem);
static void Zapis_metki(Asembler_t* const asem);


// global --------------------------------------------------------------------------------------------------------------

enum Oshibki_asemblera Asembler_ctor(Asembler_t* const asem, const char* asm_file_name)
{
    assert(asem != NULL);
    assert(asm_file_name != NULL);

    Otkritie_asm (asem, asm_file_name);
    asem->razmer_masiva_comand = RAZMER_MASSIVA_COMAND;
    asem->massiv_comand = (int64_t*)calloc(asem->razmer_masiva_comand, sizeof(int64_t));
    asem->struct_metok = (Metki_t*)calloc(MAX_COLICHESTVO_METOK, sizeof(Metki_t));
    asem->metka_na_metki = true;

    return NET_OSHIBOK;
}

void Asembler_dtor(Asembler_t* const asem)
{
    assert(asem != NULL);

    free(asem->buffer);
    asem->buffer = NULL;

    free(asem->massiv_comand);
    asem->massiv_comand = NULL;

    free(asem->struct_metok);
    asem->struct_metok = NULL;

    memset(asem, 0, sizeof(*asem));
}

enum Oshibki_asemblera Zapis_comand_v_massiv(Asembler_t* const asem)
{
    assert(asem != NULL);
    
    Realoc_na_massiv_comand(asem);

    for (asem->rabota_s_itoy_strokoi.posicia_v_buffere = asem->buffer;
         asem->rabota_s_itoy_strokoi.posicia_v_buffere < asem->buffer + asem->razmer_faila;
         asem->rabota_s_itoy_strokoi.posicia_v_buffere 
         = strchr(asem->rabota_s_itoy_strokoi.posicia_v_buffere, '\n') + PEREHOD_NA_SLED_STROKU)
    {
        size_t adres_nachala_novoy_stroki = (size_t)(strchr(asem->rabota_s_itoy_strokoi.posicia_v_buffere, '\n') 
                                                     - asem->rabota_s_itoy_strokoi.posicia_v_buffere);

        memcpy(asem->rabota_s_itoy_strokoi.buffer_stroki, asem->rabota_s_itoy_strokoi.posicia_v_buffere, 
               adres_nachala_novoy_stroki);
        
        sscanf(asem->rabota_s_itoy_strokoi.buffer_stroki, "%s", asem->rabota_s_itoy_strokoi.komanda);

        switch (Handler(asem))
        {
            case METKA: { Zapis_metki(asem); } break;
            case KOMANDA: { Rabota_s_komandoi(asem); } break;
            case PUSTAIA_STROKA: {} break;
            case SINTAKSIS_OSHIBKA: {} break; //доделаьб
            default: assert(SINTAKSIS_OSHIBKA);
        }

        Zanulenie_strok_posle_raboti_so_strokoy(asem);
    }

    asem->metka_na_metki = false;
    return NET_OSHIBOK;
}

void Zapis_massiva_cmd_v_fail (Asembler_t* const asem, const char* bin_file_name)
{
    assert(asem != NULL);
    assert(bin_file_name != NULL);

    FILE* komandi_v_chislah = fopen(bin_file_name, "w + b");
    if (komandi_v_chislah == nullptr)
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена, ВЕЩИ СОБРАЛ СЬЕБАЛСЯ НАХУЙ");
        assert(0);
    }

    fwrite(asem->massiv_comand, sizeof(int64_t), asem->kolichestvo_komand, komandi_v_chislah);
    fclose(komandi_v_chislah);
    komandi_v_chislah = NULL;
}

const char* Schitivanie_nasvania_faila(const int argc, const char* const argv[])
{
    if (argc == 2)
    {
        return argv[1];
    }

    return NACHALNIY_FAIL;
}

// static --------------------------------------------------------------------------------------------------------------

static void Otkritie_asm(Asembler_t* const asem, const char* asm_file_name)
{
    assert(asem != NULL);
    assert(asm_file_name != NULL);

    FILE* komandi = fopen(asm_file_name, "r");
    if (komandi == nullptr)
    {
        fprintf(stderr, "Файл не открылся, как и твоя головка члена, ВЕЩИ СОБРАЛ СЬЕБАЛСЯ НАХУЙ");
        assert(0);
    }

    asem->razmer_faila = Chitaet_razmer_faila(komandi);

    asem->buffer = (char*)calloc(asem->razmer_faila + 1, sizeof(char));

    fread(asem->buffer, sizeof(char), asem->razmer_faila, komandi);
    fclose(komandi);
    komandi = NULL;
}

static void Realoc_na_massiv_comand(Asembler_t* const asem)
{
    assert(asem != NULL);

    if (asem->kolichestvo_komand + CHASTOTA_PROVERKI_KOL_COMAND > asem->razmer_masiva_comand)
    {
        asem->razmer_masiva_comand = asem->razmer_masiva_comand * SHAG_DLA_MASSIVA_COMAND;
        asem->massiv_comand = (int64_t*)realloc(asem->massiv_comand, asem->razmer_masiva_comand * sizeof(int64_t));
    }
}

static void Zanulenie_strok_posle_raboti_so_strokoy(Asembler_t* const asem)
{
    assert(asem != NULL);

    memset(asem->rabota_s_itoy_strokoi.buffer_stroki, 0, RAZMER_ARGUMENTA * 2 + RAZMER_ARGUMENTA * 2);
    memset(asem->rabota_s_itoy_strokoi.komanda, 0, RAZMER_COMANDI);
    memset(asem->rabota_s_itoy_strokoi.type, 0, RAZMER_COMANDI);
    memset(asem->rabota_s_itoy_strokoi.argument, 0, RAZMER_ARGUMENTA);
    memset(asem->rabota_s_itoy_strokoi.argument_2, 0, RAZMER_ARGUMENTA);
}

static void Zapis_metki(Asembler_t* const asem)
{
    assert(asem != NULL);

    if (asem->metka_na_metki)
    {
        memcpy(asem->struct_metok[asem->schetchik_metok].metka,
               asem->rabota_s_itoy_strokoi.komanda,
               Schitaet_razmer_stroki(asem));

        asem->struct_metok[asem->schetchik_metok].adres_stroki = asem->kolichestvo_komand;
        asem->schetchik_metok++;
    }
}

static size_t Schitaet_razmer_stroki(Asembler_t* const asem)
{
    assert(asem != NULL);
    
    size_t razmer_stroki = 0;

    while (asem->rabota_s_itoy_strokoi.komanda[razmer_stroki] != '\0')
    {
        razmer_stroki++;
    }

    return razmer_stroki - POSHLO_NAHUI_DVOETOCHIE;
}

static enum Opredelenie_comandi Handler(Asembler_t* const asem)
{
    assert(asem != NULL);

         if (Poisk_pustoy_stroki(asem))                              { return PUSTAIA_STROKA;    }
    else if (Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda) > 0) { return KOMANDA;           }
    else if (Poisk_metki(asem->rabota_s_itoy_strokoi.komanda))       { return METKA;             }
    else                                                             { return SINTAKSIS_OSHIBKA; }
}

static bool Poisk_pustoy_stroki(Asembler_t* const asem)
{
    assert(asem != NULL);

    for (size_t i = 0; asem->rabota_s_itoy_strokoi.buffer_stroki[i] != '\0'; i++)
    {
        if (!isspace(asem->rabota_s_itoy_strokoi.buffer_stroki[i])) // если не пробельный символ то 0
        {
            return false;
        }
    }

    return true;
}

static enum Comandi Poisk_metki(const char* bufer_cmd)
{
    assert(bufer_cmd != NULL);
    
    if (strchr(bufer_cmd, ':') != NULL)
    {
        return (Comandi)1;
    }

    return (Comandi)0;
}

static enum Comandi Poisk_komandi(const char* bufer_cmd)
{
    assert(bufer_cmd != NULL);

         if (strncmp(bufer_cmd, Comandi_push_, sizeof(Comandi_push_)) == 0) { return Comandi_push;     }
    else if (strncmp(bufer_cmd, Comandi_add_,  sizeof(Comandi_add_))  == 0) { return Comandi_add;      }
    else if (strncmp(bufer_cmd, Comandi_sub_,  sizeof(Comandi_sub_))  == 0) { return Comandi_sub;      }
    else if (strncmp(bufer_cmd, Comandi_mul_,  sizeof(Comandi_mul_))  == 0) { return Comandi_mul;      }
    else if (strncmp(bufer_cmd, Comandi_divv_, sizeof(Comandi_divv_)) == 0) { return Comandi_divv;     }
    else if (strncmp(bufer_cmd, Comandi_out_,  sizeof(Comandi_out_))  == 0) { return Comandi_out;      }
    else if (strncmp(bufer_cmd, Comandi_in_,   sizeof(Comandi_in_))   == 0) { return Comandi_in;       }
    else if (strncmp(bufer_cmd, Comandi_sqrt_, sizeof(Comandi_sqrt_)) == 0) { return Comandi_sqrt;     }
    else if (strncmp(bufer_cmd, Comandi_sin_,  sizeof(Comandi_sin_))  == 0) { return Comandi_sin;      }
    else if (strncmp(bufer_cmd, Comandi_cos_,  sizeof(Comandi_cos_))  == 0) { return Comandi_cos;      }
    else if (strncmp(bufer_cmd, Comandi_dump_, sizeof(Comandi_dump_)) == 0) { return Comandi_dump;     }
    else if (strncmp(bufer_cmd, Comandi_hlt_,  sizeof(Comandi_hlt_))  == 0) { return Comandi_hlt;      }
    else if (strncmp(bufer_cmd, Comandi_ja_,   sizeof(Comandi_ja_))   == 0) { return Comandi_ja;       }
    else if (strncmp(bufer_cmd, Comandi_jae_,  sizeof(Comandi_jae_))  == 0) { return Comandi_jae;      }
    else if (strncmp(bufer_cmd, Comandi_jb_,   sizeof(Comandi_jb_))   == 0) { return Comandi_jb;       }
    else if (strncmp(bufer_cmd, Comandi_jbe_,  sizeof(Comandi_jbe_))  == 0) { return Comandi_jbe;      }
    else if (strncmp(bufer_cmd, Comandi_je_,   sizeof(Comandi_je_))   == 0) { return Comandi_je;       }
    else if (strncmp(bufer_cmd, Comandi_jne_,  sizeof(Comandi_jne_))  == 0) { return Comandi_jne;      }
    else if (strncmp(bufer_cmd, Comandi_jmp_,  sizeof(Comandi_jmp_))  == 0) { return Comandi_jmp;      }
    else if (strncmp(bufer_cmd, Comandi_pop_,  sizeof(Comandi_pop_))  == 0) { return Comandi_pop;      }
    else if (strncmp(bufer_cmd, Comandi_call_, sizeof(Comandi_call_)) == 0) { return Comandi_call;     }
    else if (strncmp(bufer_cmd, Comandi_ret_,  sizeof(Comandi_ret_))  == 0) { return Comandi_ret;      }
    else if (strncmp(bufer_cmd, Comandi_drow_, sizeof(Comandi_drow_)) == 0) { return Comandi_drow;     }
    else                                                                    { return Comandi_pizdeeec; }
}

static enum Comandi Poisk_registra(const char* bufer_cmd)
{
    assert(bufer_cmd != NULL);

         if (strncmp(bufer_cmd, Registri_ax_, sizeof(Registri_ax_)) == 0) { return Registri_ax;      }
    else if (strncmp(bufer_cmd, Registri_bx_, sizeof(Registri_bx_)) == 0) { return Registri_bx;      }
    else if (strncmp(bufer_cmd, Registri_cx_, sizeof(Registri_cx_)) == 0) { return Registri_cx;      }
    else if (strncmp(bufer_cmd, Registri_dx_, sizeof(Registri_dx_)) == 0) { return Registri_dx;      }
    else                                                                  { return Comandi_pizdeeec; }
}

static void Rabota_s_komandoi(Asembler_t* const asem)
{
    assert(asem != NULL);

    Comandi komanda = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);

    fprintf(stderr, "%d\n", komanda);

    if ((komanda >= Comandi_sub && komanda <= Comandi_hlt)
        || komanda == Comandi_ret
        || komanda == Comandi_add
        || komanda == Comandi_drow)
    {
        //fprintf(stderr,"drugie---\n");
        Rabota_s_comandami_bez_argumenta(asem);
    }
    else if ((komanda >= Comandi_ja && komanda <= Comandi_jne) || komanda == Comandi_call)
    {
        //fprintf(stderr,"jamp---\n");
        Rabota_s_poprigunchikami(asem);
    }
    else if (komanda == Comandi_push)
    {
        //fprintf(stderr,"push---\n");
        Rabota_s_push(asem);
    }
    else if (komanda == Comandi_pop)
    {
        //fprintf(stderr,"pop---\n");
        Rabota_s_pop(asem);
    }
}

static void Rabota_s_comandami_bez_argumenta(Asembler_t* const asem)
{
    assert(asem != NULL);

    Realoc_na_massiv_comand(asem);

    asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);
}

static void Rabota_s_poprigunchikami(Asembler_t* const asem)
{
    assert(asem != NULL);

    Realoc_na_massiv_comand(asem);

    sscanf(asem->rabota_s_itoy_strokoi.buffer_stroki, "%s %s",
           asem->rabota_s_itoy_strokoi.komanda,
           asem->rabota_s_itoy_strokoi.argument);

    asem->massiv_comand[asem->kolichestvo_komand] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);
    asem->kolichestvo_komand++;
    asem->massiv_comand[asem->kolichestvo_komand] = Ishet_metku_dla_jumpa(asem);
    asem->kolichestvo_komand++;
}

static int64_t Ishet_metku_dla_jumpa(Asembler_t* const asem)
{
    assert(asem != NULL);

    Realoc_na_massiv_comand(asem);

    for (size_t i = 0; i < MAX_COLICHESTVO_METOK; i++)
    {
        if (strcmp(asem->struct_metok[i].metka, asem->rabota_s_itoy_strokoi.argument) == 0)
        {
            return (int64_t)asem->struct_metok[i].adres_stroki;
        }
    }

    return 0;
}

static void Rabota_s_push(Asembler_t* const asem)
{
    assert(asem != NULL);
    
    Realoc_na_massiv_comand(asem);

    if (strchr(asem->rabota_s_itoy_strokoi.buffer_stroki, '[') == NULL) 
    {
        int kolichaestvo_slov_v_stroke = sscanf(asem->rabota_s_itoy_strokoi.buffer_stroki, "%s %s + %s",
                                                asem->rabota_s_itoy_strokoi.komanda,
                                                asem->rabota_s_itoy_strokoi.argument,
                                                asem->rabota_s_itoy_strokoi.argument_2);

        if (kolichaestvo_slov_v_stroke == 2)
        {
            Realoc_na_massiv_comand(asem);
            asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);

            if (Poisk_registra(asem->rabota_s_itoy_strokoi.argument) < 0)
            { 
                asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++]
                =
                (enum Comandi)strtol(asem->rabota_s_itoy_strokoi.argument, NULL, 10);
            }
            else 
            { 
                asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++]
                =
                Poisk_registra(asem->rabota_s_itoy_strokoi.argument);
            }
        }
        if (kolichaestvo_slov_v_stroke == 3)
        {
            Realoc_na_massiv_comand(asem);

            asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);
            asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT + VTOROY_BIT;
            asem->massiv_comand[asem->kolichestvo_komand++]
            =
            (enum Comandi)strtol(asem->rabota_s_itoy_strokoi.argument, NULL, 10);
            asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_registra(asem->rabota_s_itoy_strokoi.argument_2);
        }

    }
    else//(strchr(asem->rabota_s_itoy_strokoi.buffer_stroki, '[') != NULL)
    {
        Realoc_na_massiv_comand(asem);

        int kolichaestvo_slov_v_stroke = sscanf(strchr(asem->rabota_s_itoy_strokoi.buffer_stroki, '[') + 1, "%s + %s",
                                                       asem->rabota_s_itoy_strokoi.argument,
                                                       asem->rabota_s_itoy_strokoi.argument_2);

        asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);

        if (kolichaestvo_slov_v_stroke == 1)
        {
            Realoc_na_massiv_comand(asem);

            if (Poisk_registra(asem->rabota_s_itoy_strokoi.argument) < 0)
            {
                asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT + TRETIY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++]
                =
                (enum Comandi)strtol(asem->rabota_s_itoy_strokoi.argument, NULL, 10);
            }
            else
            {
                asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT + TRETIY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++]
                =
                Poisk_registra(asem->rabota_s_itoy_strokoi.argument);
            }
        }
        if (kolichaestvo_slov_v_stroke == 2)
        {
            Realoc_na_massiv_comand(asem);

            asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT + VTOROY_BIT + TRETIY_BIT;
            asem->massiv_comand[asem->kolichestvo_komand++]
            =
            (enum Comandi)strtol(asem->rabota_s_itoy_strokoi.argument, NULL, 10);
            asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_registra(asem->rabota_s_itoy_strokoi.argument_2);
        }
    }
}

static void Rabota_s_pop(Asembler_t* const asem)
{
    assert(asem != NULL);
    Realoc_na_massiv_comand(asem);

    if (strchr(asem->rabota_s_itoy_strokoi.buffer_stroki, '[') == NULL)
    {
        Realoc_na_massiv_comand(asem);

        sscanf(asem->rabota_s_itoy_strokoi.buffer_stroki, "%s %s", asem->rabota_s_itoy_strokoi.komanda,
                                                                   asem->rabota_s_itoy_strokoi.argument);

        asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);
        asem->massiv_comand[asem->kolichestvo_komand++] = CHETVERTIY_BIT;
        asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_registra(asem->rabota_s_itoy_strokoi.argument);
    }
    else
    {
        Realoc_na_massiv_comand(asem);

        int kolichaestvo_slov_v_stroke = sscanf(strchr(asem->rabota_s_itoy_strokoi.buffer_stroki, '[') + 1, "%s + %s",
                                                       asem->rabota_s_itoy_strokoi.argument,
                                                       asem->rabota_s_itoy_strokoi.argument_2);

        asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_komandi(asem->rabota_s_itoy_strokoi.komanda);
        
        if (kolichaestvo_slov_v_stroke == 2)
        {
            Realoc_na_massiv_comand(asem);
            
            asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT + PERVIY_BIT;
            asem->massiv_comand[asem->kolichestvo_komand++]
            =
            (enum Comandi)strtol(asem->rabota_s_itoy_strokoi.argument, NULL, 10);
            asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_registra(asem->rabota_s_itoy_strokoi.argument_2);
        }
        if (kolichaestvo_slov_v_stroke == 1)
        {
            Realoc_na_massiv_comand(asem);

            if (Poisk_registra(asem->rabota_s_itoy_strokoi.argument) < 0)
            {
                asem->massiv_comand[asem->kolichestvo_komand++] = PERVIY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++]
                =
                (enum Comandi)strtol(asem->rabota_s_itoy_strokoi.argument, NULL, 10);
            }
            else
            {
                asem->massiv_comand[asem->kolichestvo_komand++] = VTOROY_BIT;
                asem->massiv_comand[asem->kolichestvo_komand++] = Poisk_registra(asem->rabota_s_itoy_strokoi.argument);
            }
        }
    }
}