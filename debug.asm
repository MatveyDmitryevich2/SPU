                push 50
                pop  ax

                push 5
                pop  cx

                push 8
                pop  dx

                push cx
                push ax
                push 2
                div
                sub

                push cx
                push ax
                push 2
                div
                sub

                mul

                push dx
                push ax
                push 2
                div
                push 1
                add
                sub

                push dx
                push ax
                push 2
                div
                push 1
                add
                sub

                mul

                add

                push ax
                push 2
                div

                push ax
                push 2
                div

                mul
                dump
                hlt
