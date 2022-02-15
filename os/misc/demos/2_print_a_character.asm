; a boot sector that prints a character using interrupt 0x10 / ah 0x0e

mov ah, 0x0e                ; int 10 / ah 0x0e BIO teletype output 
mov al, "O"                 ; character we want to print 
int 0x10                    ; BIOS video interrupt

mov ah, 0x0e                ; int 10 / ah 0x0e BIO teletype output 
mov al, "M"                 ; character we want to print 
int 0x10                    ; BIOS video interrupt

mov ah, 0x0e                ; int 10 / ah 0x0e BIO teletype output 
mov al, "G"                 ; character we want to print 
int 0x10                    ; BIOS video interrupt

here:
jmp here                ; jump repeatedly to label 'loop'; neverending

times 510-($-$$) db 0   ; pads out 0s until we reach 510th byte

dw 0xaa55               ; BIOS magic number; BOOT magic #




; Would you like to know more?
; ---------------------------

; a boot sector that prints a character using interrupt 0x10 for video mode
; put different values in the registers AH 0x0e

; registers are built into the CPU.  they're fast. 

; ax,bx,cx,dx these are four general purpose registers
; ax might be the accumulator
; this is in 16 bit mode 

; CPU modes 
; --------------
; CPU modes define the size of the registers and the 
; operations that can occur on them
; in 16 bit mode you can do 16 bit operations on the registers 

; 16 bit real mode 
; 32 bit protected mode 
; 64 bit long mode 

; ax 
; ah        al
; 00000000  00000000

; 32 bit protected mode 
; eax, ebx, ecx, edx 
; to access the upper 16 bits of these you use 
; it's ax,bx,cx,dx 

; 64 bit long mode 
; rax,rbx...


; BIOS interrupts
; ----------------
; Bios interrupts use these registers to setup values that mean certain things 
; 
; The bios teletype output interrupt 
; puts a character at the cursor and advances the cursor by 1.
; It's called by putting 0x0e in AH and a character in AL then 
; executing the video interrupt 0x10
;
; mov ah, 0x0e                ; int 10 / ah 0x0e BIO teletype output 
; mov al, "T"                 ; character we want to print 
; int 0x10                    ; BIOS video interrupt
; 
; we call the BIOS interrupt with the int instruction 
;
; BIOS video interrupt, do teletype output, character 
; int 0x10 [ 0x0e "T" ]

