#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <assert.h>
#include <stdint.h>

int main()
{
    char komanda[25] = {};
    char type[25] = {};
    char argument[25] = {};
    char argument_2[25] = {};




    char numbers1[40] = { "push 4" };
    int kolichaestvo_slov_v_stroke = sscanf(numbers1, "%s %s %s %s", komanda, type, 
                                                                     argument, argument_2);

    fprintf(stderr, "push 4 --- %d ----- %s %s %s %s\n", kolichaestvo_slov_v_stroke, 
                                                         komanda, type, 
                                                         argument, argument_2);


    char numbers2[40] = { "push 4 + ax" };
    kolichaestvo_slov_v_stroke = sscanf(numbers2, "%s %s %s %s", komanda, type, 
                                                                 argument, argument_2);

    fprintf(stderr, "push 4 + ax --- %d ----- %s %s %s %s\n", kolichaestvo_slov_v_stroke, 
                                                              komanda, type, argument, argument_2);

    char numbers3[40] = { "push [ 4 ]" };
    kolichaestvo_slov_v_stroke = sscanf(numbers3, "%s %s %s %s", komanda, type, 
                                                                 argument, argument_2);

    fprintf(stderr, "push [ 4 ] --- %d ----- %s %s %s %s\n", kolichaestvo_slov_v_stroke, 
                                                             komanda, type, argument, argument_2);

    char numbers4[40] = { "push [ 4 + dx ]" };
    kolichaestvo_slov_v_stroke = sscanf(numbers4, "%s %s %s %s", komanda, type, 
                                                                 argument, argument_2);
                                                                 
    fprintf(stderr, "push [ 4 + dx ] --- %d ----- %s %s %s %s\n", kolichaestvo_slov_v_stroke, komanda, 
                                                                  type, argument, argument_2);
}