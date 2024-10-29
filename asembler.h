#ifndef ASEMBLER_H
#define ASEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include "globalniy_enum.h" 


enum Oshibki_asemblera 
{
    NET_OSHIBOK                            = 0,
    UKAZTENEL_NA_STRUKTURU_ASEMBLER_POEHAL = 1,
    UKAZTENEL_NA_MASSIV_ASEMBLER_POEHAL    = 2,
    OSHINKA_PRI_OTKRITII_FAILA             = 3,
};

enum Opredelenie_comandi
{
    SINTAKSIS_OSHIBKA                      = 0,
    METKA                                  = 1,
    KOMANDA                                = 2,
    PUSTAIA_STROKA                         = 3,
};

enum Prosmotr_bitov
{
    PERVIY_BIT                             = 1,
    VTOROY_BIT                             = 2,
    TRETIY_BIT                             = 4,
    CHETVERTIY_BIT                         = 8,
};


static const char* NACHALNIY_FAIL                 = "komandi.asm";
static const char* KONECNIY_FAIL                  = "chislovie_komandi.bin";
static const size_t PEREHOD_NA_SLED_STROKU        = 1;

static const size_t RAZMER_COMANDI                = 25;
static const size_t RAZMER_ARGUMENTA              = 25;
 
static const size_t MAX_COLICHESTVO_METOK         = 16;
static const size_t POSHLO_NAHUI_DVOETOCHIE       = 1;

static const size_t CHASTOTA_PROVERKI_KOL_COMAND  = 5;
static const size_t RAZMER_MASSIVA_COMAND         = 20;
static const size_t SHAG_DLA_MASSIVA_COMAND       = 2;


struct Metki_t
{
    size_t adres_stroki;
    char metka[RAZMER_COMANDI];
};

struct Info_o_stroke 
{
    char komanda[RAZMER_COMANDI];
    char type[RAZMER_COMANDI];
    char argument[RAZMER_ARGUMENTA];
    char argument_2[RAZMER_ARGUMENTA];
    char buffer_stroki[RAZMER_COMANDI * 2 + RAZMER_ARGUMENTA * 2];

    char* posicia_v_buffere;
};

struct Asembler_t
{
    size_t razmer_faila;

    char* buffer;

    int64_t* massiv_comand;
    size_t razmer_masiva_comand;
    size_t kolichestvo_komand;

    bool metka_na_metki;
    int schetchik_metok;
    Metki_t* struct_metok;

    Info_o_stroke rabota_s_itoy_strokoi;
};


static const char Comandi_push_[] = "push";
static const char Comandi_pop_ [] = "pop";
static const char Comandi_add_ [] = "add";
static const char Comandi_sub_ [] = "sub";
static const char Comandi_mul_ [] = "mul";
static const char Comandi_divv_[] = "div";
static const char Comandi_out_ [] = "out";
static const char Comandi_in_  [] = "in";
static const char Comandi_sqrt_[] = "sqrt";
static const char Comandi_sin_ [] = "sin";
static const char Comandi_cos_ [] = "cos";

static const char Comandi_drow_[] = "drow";
static const char Comandi_dump_[] = "dump";
static const char Comandi_hlt_ [] = "hlt";

static const char Comandi_ja_  [] = "ja";
static const char Comandi_jae_ [] = "jae";
static const char Comandi_jb_  [] = "jb";
static const char Comandi_jbe_ [] = "jbe";
static const char Comandi_je_  [] = "je";
static const char Comandi_jne_ [] = "jne";
static const char Comandi_jmp_ [] = "jmp";

static const char Comandi_call_[] = "call";
static const char Comandi_ret_ [] = "ret";

static const char Registri_ax_ [] = "ax";
static const char Registri_bx_ [] = "bx";
static const char Registri_cx_ [] = "cx";
static const char Registri_dx_ [] = "dx";
static const char Registri_ex_ [] = "ex";
static const char Registri_fx_ [] = "fx";
static const char Registri_gx_ [] = "gx";
static const char Registri_hx_ [] = "hx";
static const char Registri_ix_ [] = "ix";
static const char Registri_mx_ [] = "mx";



enum Oshibki_asemblera Asembler_ctor(Asembler_t* const asem, const char* asm_file_name);
void Asembler_dtor(Asembler_t* const asem);
enum Oshibki_asemblera Zapis_comand_v_massiv(Asembler_t* const asem);
void Zapis_massiva_cmd_v_fail (Asembler_t* const asem, const char* bin_file_name);
const char* Schitivanie_nasvania_faila(const int argc, const char* const argv[]);

#endif //ASEMBLER_H