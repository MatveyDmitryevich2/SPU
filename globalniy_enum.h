#ifndef GLOBALNIY_ENUM_H
#define GLOBALNIY_ENUM_H

enum Comandi
{
    Comandi_pizdeeec = -1,

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
    Comandi_drow   = 23,

    Comandi_call   = 21,
    Comandi_ret    = 22,
    
    Registri_ax    = 0,
    Registri_bx    = 1,
    Registri_cx    = 2,
    Registri_dx    = 3,
    Registri_ex    = 4,
    Registri_fx    = 5,
    Registri_gx    = 6,
    Registri_hx    = 7,
    Registri_ix    = 8,
    Registri_mx    = 9,
};

#endif //GLOBALNIY_ENUM_H