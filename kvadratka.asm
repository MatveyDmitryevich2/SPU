main:
                in
                pop     ax
                in
                pop     bx
                in
                pop     cx


                push    bx
                push    bx
                mul

                push    4
                push    ax
                push    cx
                mul
                mul

                sub

                pop     dx
                dump

                push    0
                push    ax
                jne     a_ne_null
                call    lin_ili_net
a_ne_null:
                push    0
                push    dx
                jbe     d_ne_otric
                call    d_menshe_null
d_ne_otric:
                push    0
                push    dx
                jne     d_ne_null
                call    d_null
d_ne_null:
                push    2
                out


                push    dx
                sqrt
                pop     dx

                push    -1
                push    bx
                mul

                push    dx

                sub

                push    2
                push    ax
                mul

                div

                out


                push    dx

                push    -1
                push    bx
                mul

                add

                push    2
                push    ax
                mul

                div

                out

                hlt










lin_ili_net:
                push    0
                push    bx
                jne     b_ne_null
                
                push    0
                push    cx
                jne     c_ne_null

                push    -1
                out

                push    999
                out
                hlt


c_ne_null:
                push     0
                out

                hlt


b_ne_null:
                push    1
                out

                push    cx
                push    bx
                div
                push    -1
                mul
                out
                hlt





d_menshe_null:
                push    0
                out
                hlt


d_null:
                push    1
                out

                push    bx
                push    -1
                mul

                push    2
                push    ax
                mul

                div

                out
                hlt
