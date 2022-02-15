    ;; jmp 0x7C00+100 jumps the code
    ;; it's important to be able to use numerical offsets like this since
    ;; code is loaded into different regions of ram and in different files.
    
;;; fasm jump_to_offset_demo.asm && qemu-system-i386 -drive format=raw,file=jump_to_offset_demo.bin,if=ide,index=0,media=disk

    org 0x7c00                  ; 'origin' of Boot code; helps make sure addresses don't change

    mov bx, newline
    call print_string
    mov bx, str1
    call print_string

    
    jmp 0x7C00+100              ; this is what all the fuss is about

    times 100-($-$$) db 0       ; pads out 0s until we reach 100th byte

    
    mov bx, str2
    call print_string

    jmp $



include "print_string.asm"


newline:    db 0xa,0xd,0
str1:       db 'Hi!', 0xa, 0xd, 0
str2:       db 'You just jumped to another section of code using a numerical offset!', 0xa, 0xd, 0

    ;; boot magic
    times 510-($-$$) db 0
    dw 0xaa55
