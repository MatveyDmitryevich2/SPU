#ifndef ASEMBLER_H
#define ASEMBLER_H

#include "funkcii_globalnie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

struct Asembler_t
{
    FILE *komandi;
    FILE* komandi_v_chislah;
    uint64_t razmer_faila;
    char* buffer;
    int64_t* massiv_comand;
    int64_t ateracia_dla_zapisi_slova;
};

const char Comandi_push1[]  = "push";
const char Comandi_pop1[]   =  "pop";
const char Comandi_add1[]   = "add";
const char Comandi_sub1[]   =  "sub";
const char Comandi_mul1[]   =  "mul";
const char Comandi_divv1[]  =  "div";
const char Comandi_out1[]   =  "out";
const char Comandi_in1[]    =  "in";
const char Comandi_sqrt1[]  =  "sqrt";
const char Comandi_sin1[]   =  "sin";
const char Comandi_cos1[]   =  "cos";
const char Comandi_dump1[]  =  "dump";
const char Comandi_hlt1[]   =  "hlt";
const char Comandi_ja1[]    =  "ja";
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

enum Comandi Menaet_komandu_na_enum(char* bufer_cmd);
void AsemblerDtor(FILE* komandi_v_chislah, FILE* komandi, char* buffer, int64_t* massiv_comand);

// FIXME сделать структуру ассемблера для хранения состояния и всякой хрени + ctor dtor

#endif //ASEMBLER_H