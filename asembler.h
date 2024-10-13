#ifndef ASEMBLER_H
#define ASEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>


const char Comandi_push1[]  = "push";
const char Comandi_pop1[]   =  "pop";
const char Comandi_add1[] = "add";
const char Comandi_sub1[]   =  "sub";
const char Comandi_mul1[]   =  "mul";
const char Comandi_divv1[]  =  "div";
const char Comandi_out1[]   =  "out";
const char Comandi_in1[]    =   "in";
const char Comandi_sqrt1[]  = "sqrt";
const char Comandi_sin1[]   =  "sin";
const char Comandi_cos1[]   =  "cos";
const char Comandi_dump1[]  = "dump";
const char Comandi_hlt1[]   =  "hlt";
const char Comandi_ja1[]    =   "ja";
const char Comandi_jae1[]   =  "jae";
const char Comandi_jb1[]    =  "jb";
const char Comandi_jbe1[]   =  "jbe";
const char Comandi_je1[]    =  "je";
const char Comandi_jne1[]   =  "jne";
const char Comandi_jmp1[]   =  "jmp";
const char Comandi_popr1[]  =  "popr";
const char Comandi_pushr1[] =  "pushr";
const char Comandi_ax1[]    =  "ax";
const char Comandi_bx1[]    =  "bx";
const char Comandi_cx1[]    =  "cx";
const char Comandi_dx1[]    =  "dx";

enum Comandi
{
    Comandi_chislo = -1,
    Comandi_push   = 1,
    Comandi_pop    = 3,
    Comandi_add    = 2,
    Comandi_sub    = 4,
    Comandi_mul    = 5,
    Comandi_divv   = 6, 
    Comandi_out    = 7,
    Comandi_in     = 8,
    Comandi_sqrt   = 9,
    Comandi_sin    = 10,
    Comandi_cos    = 11,
    Comandi_dump   = 12,
    Comandi_hlt    = 13,
    Comandi_ja     = 14,
    Comandi_jae    = 15,
    Comandi_jb     = 16,
    Comandi_jbe    = 17,
    Comandi_je     = 18,
    Comandi_jne    = 19,
    Comandi_jmp    = 20,
    Comandi_popr   = 21,
    Comandi_pushr  = 22,
    Comandi_ax     = 0,
    Comandi_bx     = 1,
    Comandi_cx     = 2,
    Comandi_dx     = 3,
};

uint64_t Chitaet_razmer_faila(FILE* komandi);
enum Comandi Menaet_komandu_na_enum(char* bufer_cmd);

#endif //ASEMBLER_H