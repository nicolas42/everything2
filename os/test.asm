;;; fasm test.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=test.bin,if=ide,index=0,media=disk
;;;
;;; Simple Boot loader that uses INT13 AH2 to read from disk into memory
;;;
    org 0x7c00                  ; 'origin' of Boot code; helps make sure addresses don't change

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


    jmp 0x7C00+100

    times 100-($-$$) db 0       ; pads out 0s until we reach 100th byte



;; -------------------------------------------------------------
;; kernel 
;; -------------------------------------------------------------


    
    mov bx, str2
    call print_string

    mov bx, str3
    call print_string

    mov bx, newline
    call print_string

    mov dx, 0x12AB
    call print_hex

    jmp $



include "src/print_string.asm"
include "src/print_hex.asm"


str1:          db 'Hello World!', 0xa, 0xd, 0
str2:          db 'You say goodbye but I say hello.  Hello, hello.', 0xa, 0xd, 0
str3:          db "omg it's some hex => ",0
newline:       db 0xA, 0xD, 0

    ;; boot magic
    times 510-($-$$) db 0
    dw 0xaa55
