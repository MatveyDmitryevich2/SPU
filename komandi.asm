main:
                in
                pop     cx
                call    factorial
                push    cx
                out
                hlt

factorial:
                dump
                push    0
                dump
                push    cx
                dump
                jb      iteration
                dump
                push    1
                pop     cx
                dump
                ret
iteration:      
                dump
                push    cx
                push    cx
                push    1
                sub
                dump
                pop     cx
                dump
                call    factorial
                dump
                push    cx
                mul
                dump
                pop     cx
                ret
