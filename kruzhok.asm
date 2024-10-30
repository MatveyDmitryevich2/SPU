main:
                push 50
                pop  ax
                push 10
                pop ex
                push 0
                pop cx
                push 0
                pop dx


                call vneshniy_for14

                push 1000

                push ax
                push 2
                div

                add

                push ax
                push 1
                add

                push ax
                push 2
                div

                mul

                add
                
                pop bx
                push 1

                pop [ bx ]

                drow
                hlt

vneshniy_for14:
                NEXT1:
                push 0
                pop cx
                call vnutreniy_for16
                

                push 1
                push dx
                add
                pop dx

                push dx
                push ax
                jbe NEXT1
                ret

vnutreniy_for16:
                NEXT2:
                call secs18
                call secs19

                push cx
                push 1
                add

                pop cx
                push cx
                push ax
                dump
                jbe NEXT2
                ret

secs18:
                push 1000
                push cx
                add
                push ax
                push 1
                add
                push dx
                mul
                add
                
                pop bx
                push 0
                pop [ bx ]
                ret

secs19:
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
                sub

                push dx
                push ax
                push 2
                div
                sub

                mul

                add

                push ex
                push ex
                mul

                ja delaem_3

                push 1000
                push cx
                add

                push ax
                push 1
                add

                push dx

                mul

                add
                
                pop bx
                push 1
                pop [ bx ]
delaem_3:
                ret
