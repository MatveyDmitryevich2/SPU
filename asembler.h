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


enum Oshibki_Asemblera // <-------------------------
{ //                                               |
    NET_OSHIBOK                            = 0, // |
    UKAZTENEL_NA_STRUKTURU_ASEMBLER_POEHAL = 1, // | Разные стили названий енумов
    UKAZTENEL_NA_MASSIV_ASEMBLER_POEHAL    = 2, // |
    OSHINKA_PRI_OTKRITII_FAILA             = 3, // |
}; //                                              |
//                                                 |
enum Opredelenie_comandi // <----------------------
{
    METKA                                  = 1,
    KOMANDA                                = 2,
    PUSTAIA_STROKA                         = 3,
    SINTAKSIS_OSHIBKA                      = 4,
};

enum Smotrenie_bitov // FIXME СМОТРЕНИЕ???
{
    PERVIY_BIT                             = 1,
    VTOROY_BIT                             = 2,
    TRETIY_BIT                             = 4,
    CHETVERTIY_BIT                         = 8,
};


const char NACHALNIY_FAIL[]                = "komandi.txt";
const char KONECNIY_FAIL[]                 = "chislovie_komani.txt";
const size_t PEREHOD_NA_SLED_STROKU        = 1; 
const size_t SDVIG_V_MASSIVE               = 2; // НУ ТЫ И ДАУН - Нигде не используется

const size_t RAZMER_COMANDI                = 25;
const size_t RAZMER_ARGUMENTA              = 25;

const size_t MAX_COLICHESTVO_METOK         = 16;
const size_t POSHLO_NAHUI_DVOETOCHIE       = 1;

const size_t CHASTOTA_PROVERKI_KOL_COMAND  = 5; // FIXME НАЗВАНИЕ ГОВНО
const size_t RAZMER_MASSIVA_KOMAND         = 20; // НУ ТЫ И ДАУН - Так COMAND или KOMAND
const size_t SHAG_DLA_MASSIVA_COMND        = 2; // FIXME C(K)OMAND


struct Metki_t
{
    size_t adres_stroki;
    char metka[RAZMER_COMANDI];
};

struct Info_o_stroke 
{
    char komanda[RAZMER_COMANDI];
    char type[RAZMER_COMANDI]; // FIXME tip?
    char argument[RAZMER_ARGUMENTA];
    char argument_2[RAZMER_ARGUMENTA];
    char bufer_stroki[RAZMER_COMANDI * 2 + RAZMER_ARGUMENTA * 2];

    char* posicia_v_buffere; // FIXME buf(f)er?
};

struct Asembler_t
{
    size_t razmer_faila;

    char* buffer; // FIXME buf(f)er?

    int64_t* massiv_comand;
    size_t razmer_mas_com; // FIXME mas_com???
    size_t kolichestvo_komand;

    bool metka_na_metki;
    int schetchik_metok;
    Metki_t* struct_metok;

    Info_o_stroke rabota_s_itoy_strokoi;
};


const char Comandi_push_[] = "push";
const char Comandi_pop_ [] = "pop";
const char Comandi_add_ [] = "add";
const char Comandi_sub_ [] = "sub";
const char Comandi_mul_ [] = "mul";
const char Comandi_divv_[] = "div";
const char Comandi_out_ [] = "out";
const char Comandi_in_  [] = "in";
const char Comandi_sqrt_[] = "sqrt";
const char Comandi_sin_ [] = "sin";
const char Comandi_cos_ [] = "cos";

const char Comandi_drow_[] = "drow";
const char Comandi_dump_[] = "dump";
const char Comandi_hlt_ [] = "hlt";

const char Comandi_ja_  [] = "ja";
const char Comandi_jae_ [] = "jae";
const char Comandi_jb_  [] = "jb";
const char Comandi_jbe_ [] = "jbe";
const char Comandi_je_  [] = "je";
const char Comandi_jne_ [] = "jne";
const char Comandi_jmp_ [] = "jmp";

const char Comandi_call_[] = "call";
const char Comandi_ret_ [] = "ret";

const char Registri_ax_ [] = "ax";
const char Registri_bx_ [] = "bx";
const char Registri_cx_ [] = "cx";
const char Registri_dx_ [] = "dx";


enum Oshibki_Asemblera Asembler_ctor(Asembler_t* const asem, const char* asm_file_name);
void Asembler_dtor(Asembler_t* const asem);
enum Oshibki_Asemblera Zapis_comand_v_massiv(Asembler_t* const asem);
void Otkritie_bin (Asembler_t* const asem, const char* bin_file_name); // FIXME Лишний пробел

#endif // FIXME Не подписал какой if закончил (обычно пишешь)