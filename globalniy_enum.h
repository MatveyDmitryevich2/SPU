#ifndef GLOBALNIY_ENUM_H
#define GLOBALNIY_ENUM_H

enum Comandi
{
    Comandi_metka = -1,
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
    Registri_ax     = 0,
    Registri_bx     = 1,
    Registri_cx     = 2,
    Registri_dx     = 3,
};

#endif //GLOBALNIY_ENUM_H