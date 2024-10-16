#include "asembler.h"
#include "funkcii_globalnie.h"
#include "schitivanie_faila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

uint64_t Chitaet_razmer_faila(FILE *komandi)
{
    assert(komandi != NULL);

    fseek(komandi, 0, SEEK_END);
    uint64_t razmer_faila = ftell(komandi);
    fseek(komandi, 0, SEEK_SET);

    return razmer_faila;
}

enum Comandi Menaet_komandu_na_enum(char* bufer_cmd)
{
         if (strncmp(bufer_cmd, Comandi_push1,  sizeof(Comandi_push1))  == 0) { return Comandi_push;  }
    else if (strncmp(bufer_cmd, Comandi_add1,   sizeof(Comandi_add1))   == 0) { return Comandi_add;   }
    else if (strncmp(bufer_cmd, Comandi_sub1,   sizeof(Comandi_sub1))   == 0) { return Comandi_sub;   }
    else if (strncmp(bufer_cmd, Comandi_mul1,   sizeof(Comandi_mul1))   == 0) { return Comandi_mul;   }
    else if (strncmp(bufer_cmd, Comandi_divv1,  sizeof(Comandi_divv1))  == 0) { return Comandi_divv;  }
    else if (strncmp(bufer_cmd, Comandi_out1,   sizeof(Comandi_out1))   == 0) { return Comandi_out;   }
    else if (strncmp(bufer_cmd, Comandi_in1,    sizeof(Comandi_in1))    == 0) { return Comandi_in;    }
    else if (strncmp(bufer_cmd, Comandi_sqrt1,  sizeof(Comandi_sqrt1))  == 0) { return Comandi_sqrt;  }
    else if (strncmp(bufer_cmd, Comandi_sin1,   sizeof(Comandi_sin1))   == 0) { return Comandi_sin;   }
    else if (strncmp(bufer_cmd, Comandi_cos1,   sizeof(Comandi_cos1))   == 0) { return Comandi_cos;   }
    else if (strncmp(bufer_cmd, Comandi_dump1,  sizeof(Comandi_dump1))  == 0) { return Comandi_dump;  }
    else if (strncmp(bufer_cmd, Comandi_hlt1,   sizeof(Comandi_hlt1))   == 0) { return Comandi_hlt;   }
    else if (strncmp(bufer_cmd, Comandi_ja1,    sizeof(Comandi_ja1))    == 0) { return Comandi_ja;    }
    else if (strncmp(bufer_cmd, Comandi_jae1,   sizeof(Comandi_jae1))   == 0) { return Comandi_jae;   }
    else if (strncmp(bufer_cmd, Comandi_jb1,    sizeof(Comandi_jb1))    == 0) { return Comandi_jb;    }
    else if (strncmp(bufer_cmd, Comandi_jbe1,   sizeof(Comandi_jbe))    == 0) { return Comandi_jbe;   }
    else if (strncmp(bufer_cmd, Comandi_je1,    sizeof(Comandi_je1))    == 0) { return Comandi_je;    }
    else if (strncmp(bufer_cmd, Comandi_jne1,   sizeof(Comandi_jne1))   == 0) { return Comandi_jne;   }
    else if (strncmp(bufer_cmd, Comandi_jmp1,   sizeof(Comandi_jmp1))   == 0) { return Comandi_jmp;   }
    else if (strncmp(bufer_cmd, Comandi_popr1,  sizeof(Comandi_popr1))  == 0) { return Comandi_popr;  }
    else if (strncmp(bufer_cmd, Comandi_pushr1, sizeof(Comandi_pushr1)) == 0) { return Comandi_pushr; }
    else if (strncmp(bufer_cmd, Comandi_ax1,    sizeof(Comandi_ax1))    == 0) { return Comandi_ax;    }
    else if (strncmp(bufer_cmd, Comandi_bx1,    sizeof(Comandi_bx1))    == 0) { return Comandi_bx;    }
    else if (strncmp(bufer_cmd, Comandi_cx1,    sizeof(Comandi_cx1))    == 0) { return Comandi_cx;    }
    else if (strncmp(bufer_cmd, Comandi_dx1,    sizeof(Comandi_dx1))    == 0) { return Comandi_dx;    }
    else                                                                      { return Comandi_chislo;}
}

void AsemblerDtor(FILE* komandi_v_chislah, FILE* komandi, char* buffer, int64_t* massiv_comand)
{
    fclose (komandi_v_chislah);
    fclose (komandi);

    free(buffer);
    buffer = NULL;

    free(massiv_comand);
    massiv_comand = NULL;
}