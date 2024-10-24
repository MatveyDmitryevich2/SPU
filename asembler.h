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

const int RAZMER_COMANDI = 25;
const int RAZMER_ARGUMENTA = 20;
const int MAX_COLICHESTVO_METOK = 16;
const char NACHALNIY_FAIL[] = "Komandi.txt"; 
const char KONECNIY_FAIL[] = "Chislovie_komani.txt";

const int PERVIY_BIT = 1;
const int VTOROY_BIT = 2;
const int TRETIY_BIT = 4;
const int CHETVERTIY_BIT = 8;

const size_t RAZMER_MASSIVA_KOMAND = 20;
const int SHAG_DLA_MASSIVA_COMND = 2;

struct Metki_t
{
    int64_t adres_stroki;
    char metka[RAZMER_COMANDI];
};

struct Asembler_t
{
    size_t razmer_faila;
    char* buffer;
    int64_t* massiv_comand;
    int64_t razmer_mas_com;
    int64_t kolichestvo_komand;
    bool metka_na_metki;
    
    int schetchik_metok;
    Metki_t* struct_metok;
};

enum Oshibki_Asemblera
{
    NET_OSHIBOK                            = 0,
    UKAZTENEL_NA_STRUKTURU_ASEMBLER_POEHAL = 1,
    UKAZTENEL_NA_MASSIV_ASEMBLER_POEHAL    = 2,
    OSHINKA_PRI_OTKRITII_FAILA             = 3
};

const char Comandi_push1[] = "push";
const char Comandi_pop1[]  = "pop";
const char Comandi_add1[]  = "add";
const char Comandi_sub1[]  = "sub";
const char Comandi_mul1[]  = "mul";
const char Comandi_divv1[] = "div";
const char Comandi_out1[]  = "out";
const char Comandi_in1[]   = "in";
const char Comandi_sqrt1[] = "sqrt";
const char Comandi_sin1[]  = "sin";
const char Comandi_cos1[]  = "cos";
const char Comandi_dump1[] = "dump";
const char Comandi_hlt1[]  = "hlt";
const char Comandi_ja1[]   = "ja";
const char Comandi_jae1[]  = "jae";
const char Comandi_jb1[]   = "jb";
const char Comandi_jbe1[]  = "jbe";
const char Comandi_je1[]   = "je";
const char Comandi_jne1[]  = "jne";
const char Comandi_jmp1[]  = "jmp";

const char Registri_ax1[]  = "ax";
const char Registri_bx1[]  = "bx";
const char Registri_cx1[]  = "cx";
const char Registri_dx1[]  = "dx";


void Otkritie_asm (Asembler_t* const asem, const char* asm_file_name);
void Otkritie_bin (Asembler_t* const asem, const char* bin_file_name);
enum Oshibki_Asemblera AsemblerCtor(Asembler_t* const asem, const char* NACHALNIY_FAIL);
void AsemblerDtor(Asembler_t* const asem, const char* bin_file_name);

enum Oshibki_Asemblera Zapis_comand(Asembler_t* const asem);
void Ishet_metku(Asembler_t* asem, char* slovo);
enum Comandi Ishet_metku_dla_jumpa(Asembler_t* const asem, char* argument);
enum Comandi Perevod_asembler(const char* bufer_cmd);

void Realoc_na_massiv_comand(Asembler_t* const asem);

#endif //ASEMBLER_H