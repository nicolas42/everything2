
 ; macos
 ; fasm my_first_boot_loader.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -boot a -fda my_first_boot_loader.bin
 ; fasm my_first_boot_loader.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=my_first_boot_loader.bin,if=floppy

 ;linux
 ; fasm my_first_boot_loader.asm && qemu-system-i386 -drive format=raw,file=my_first_boot_loader.bin,if=floppy



    ;; Read a disk sector and then jump to it
    ;; -----------------------------------------------
    
    ;; Uses INT13 AH=2 to read from disk into memory
    ;; Does the data segment register need to be set When moving to es:bx where es!=0 ?




    org 0x7c00                  ; 'origin' of Boot code; helps make sure addresses don't change


    ;; set up ES:BX memory address/segment:offset to load sector(s) into
    mov ax, 0x0000
    mov es, ax                  
    mov bx, 0x7e00                 ; ES:BX = 0x0000:0x7e00

    ;; Set up disk read
    mov dh, 0x0                 ; head 0
    mov dl, 0x0                 ; drive 0
    mov ch, 0x0                 ; cylinder 0
    mov cl, 0x02                ; starting sector to read from disk

read_disk:
    mov ah, 0x02                ; BIOS int 13h/ah=2 read disk sectors
    mov al, 0x01                ; # of sectors to read
    int 0x13                    ; BIOS interrupts for disk functions
    jc read_disk                ; retry if disk read error (carry flag set/ = 1)

    ;; ;; reset segment registers for RAM
    ;; mov ax, 0x0000
    ;; mov ds, ax                  ; data segment
    ;; mov es, ax                  ; extra segment
    ;; mov fs, ax                  ; ""
    ;; mov gs, ax                  ; ""
    ;; mov ss, ax                  ; stack segment


    
    jmp 0x7e00              ; never return from this!


    ;; Boot Sector magic
    times 510-($-$$) db 0       ; pads out 0s until we reach 510th byte
    dw 0xaa55                   ; BIOS magic number; BOOT magic #



;;; This gets loaded into ram at 0x7e00 and then run


    org 0x7e00

    ;; Set video mode
    mov ah, 0x00                ; int 0x10/ ah 0x00 = set video mode
    mov al, 0x02
    int 0x10

    ;; Change color/Palette
    mov ah, 0x0B
    mov bh, 0x00
    mov bl, 0x01
    int 0x10

    mov ah, 0x0e
    mov al, 'o'
    int 0x10
    mov al, 'm'
    int 0x10
    mov al, 'g'
    int 0x10
    mov al, 0xA
    int 0x10
    mov al, 0xD
    int 0x10


    ;; print something
    mov bx, you_have_booted
    call print_string

    jmp $


include "src/print_string.asm"
include "src/print_hex.asm"


str1:   db 'Hello World!', 0xa, 0xd, 0
str2:   db 'You say goodbye but I say hello.  Hello, hello.', 0xa, 0xd, 0
str3:   db "omg it's some hex => ",0
you_have_booted:   db 'You have loaded a sector from a disk and then run it.', 0xa, 0xd, 0



    ;; padding why not
    times 1024-($-$$) db 0

