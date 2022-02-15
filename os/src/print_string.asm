;; print a string pointed to by the bx register
print_string:
    pusha               ; store all register values onto the stack

print_string_loop:
    mov ah, 0x0e
    mov al, [bx]
    cmp al, 0
    je print_string_return
    int 0x10
    add bx,1
    jmp print_string_loop

print_string_return:
    popa                ; restore register values
    ret

