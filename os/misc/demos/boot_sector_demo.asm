    org 0x7c00


    ;; Set video mode
    mov ah, 0x00                ; int 0x10/ ah 0x00 = set video mode
    mov al, 0x02
    int 0x10

    ;; Change color/Palette
    mov ah, 0x0B
    mov bh, 0x00
    mov bl, 0x01
    int 0x10

    ;; print some stuff
    mov bx, str1
    call print_string

    mov bx, str2
    call print_string

    mov bx, str3
    call print_string

    mov dx, 0x12AB
    call print_hex

    jmp $



include "print_string.asm"
include 'print_hex.asm'


str1:          db 'Hello World!', 0xa, 0xd, 0
str2:          db 'You say goodbye but I say hello.  Hello, hello.', 0xa, 0xd, 0
str3:          db "omg it's some hex => ",0

    ;; boot magic
    times 510-($-$$) db 0
    dw 0xaa55
