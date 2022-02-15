
 ; macos
 ; fasm os.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -boot a -fda os.bin
 ; fasm os.asm && /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=os.bin,if=floppy

 ;linux
 ; fasm os.asm && qemu-system-i386 -drive format=raw,file=os.bin,if=floppy


    ;; My second bootloader.  I can't seem to read more than 3 sectors.

use16
    org 0x7c00

    call read_sectors
    jmp 0x0000:0x7e00           ; don't want to return
    
    
;; VARIABLES
drive_num: db 0
num_sectors_to_read:     db 02h     ; 3 sectors


read_sectors:   
    mov byte [drive_num], dl	; DL contains initial drive # on boot

    ;; READ 2ND STAGE BOOTLOADER INTO MEMORY FIRST
    mov bl, [num_sectors_to_read]
    mov di, 7E00h       ; Memory address to read sectors into

    mov dx, 1F6h        ; Head & drive # port
    mov al, [drive_num] ; Drive # - hard disk 1
    and al, 0Fh         ; Head # (low nibble)
    or al, 0A0h         ; default high nibble to 'primary' drive (drive 1), 'secondary' drive (drive 2) would be hex B or 1011b
    out dx, al          ; Send head/drive #

    mov dx, 1F2h        ; Sector count port
    mov al, 03h         ; # of sectors to read
    out dx, al

    mov dx, 1F3h        ; Sector # port
    mov al, 2h          ; Sector to start reading at (sectors are 1-based)
    out dx, al

    mov dx, 1F4h        ; Cylinder low port
    xor al, al          ; Cylinder low #
    out dx, al

    mov dx, 1F5h        ; Cylinder high port
    xor al, al          ; Cylinder high #
    out dx, al

    mov dx, 1F7h        ; Command port (writing port 1F7h)
    mov al, 20h         ; Read with retry
    out dx, al

;; Poll status port after reading 1 sector
second_stage_loop:
    in al, dx           ; Status register (reading port 1F7h)
    test al, 8          ; Sector buffer requires servicing
    je second_stage_loop     ; Keep trying until sector buffer is ready

    mov cx, 256         ; # of words to read for 1 sector
    mov dx, 1F0h        ; Data port, reading 
    rep insw            ; Read bytes from DX port # into DI, CX # of times
    
    ;; 400ns delay - Read alternate status register
    mov dx, 3F6h
    in al, dx
    in al, dx
    in al, dx
    in al, dx

    cmp bl, 0
    ret

    dec bl
    mov dx, 1F7h
    jmp second_stage_loop

    
;; Boot Sector magic
times 510-($-$$) db 0       ; pads out 0s until we reach 510th byte
dw 0xaa55                   ; BIOS magic number; BOOT magic #





;;; ---------------------------------------------------------------    
;;; Second Sector 
;;; ---------------------------------------------------------------

;; This sector is read into memory and jumped to by the first sector


    org 0x7E00

    ;; Set video mode
    mov ah, 0x00                ; int 0x10/ ah 0x00 = set video mode
    mov al, 0x02
    int 0x10

    ;; Change color/Palette
    mov ah, 0x0B
    mov bh, 0x00
    mov bl, 0x01
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



    ; fill with zeroes
    times 512+512*3-($-$$) db 0

