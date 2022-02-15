; demo
; nasm -f bin macos_minimal_executable.asm -o a.out && chmod +x a.out && ./a.out; echo $?

; This is a minimal executable on macos
; As you can see it requires a lot more than just the instructions.
; *But* nothing else will be added to this file.  Notice "nasm -f bin" for pure binary format.
; The only thing it does it return a value to the command line
; There's a bunch of header data that preceeds the code.
; The defines are just for readability



; Original File Contents
; -----------------------------
; A minimal Mach-o x32 executable for OS X El Capitan (with proper padding and symtable)
;
; Original (pre 10.10.5) version - https://gist.github.com/softboysxp/1084476
; $ nasm -O0 -f bin -o tiny_hello tiny_hello.asm
; $ chmod +x tiny_hello
; $ ./tiny_hello
; (returns 42)
; $

; c.f.
; http://osxbook.com/blog/2009/03/15/crafting-a-tiny-mach-o-executable/ ( the original tiny mach-o executable )
; http://feiri.de/macho/                        ( improved version, using a very clever trick to put code inside the load command itself)

; Constants (For readability)

%define MH_MAGIC_32         0xfeedface

%define CPU_ARCH_ABI32        0x00000000
%define CPU_TYPE_I386       0x00000007
%define CPU_TYPE_X86       CPU_ARCH_ABI32 | CPU_TYPE_I386

%define CPU_SUBTYPE_LIB32     0x80000000
%define CPU_SUBTYPE_I386_ALL    0x00000003

%define MH_EXECUTE          0x2
%define MH_NOUNDEFS         0x1

%define LC_REQ_DYLD         0x80000000
%define LC_LOAD_DYLIB       0xc
%define LC_LOAD_DYLINKER      0xe
%define LC_SEGMENT       0x1
%define LC_SYMTAB       0x2
%define LC_MAIN           0x28 | LC_REQ_DYLD

%define VM_PROT_READ        0x1
%define VM_PROT_WRITE       0x2
%define VM_PROT_EXECUTE       0x4

%define x86_THREAD_STATE32      0x4
%define x86_EXCEPTION_STATE32_COUNT 42


%define SYSCALL_CLASS_SHIFT     24
%define SYSCALL_CLASS_MASK      (0xFF << SYSCALL_CLASS_SHIFT)
%define SYSCALL_NUMBER_MASK     (~SYSCALL_CLASS_MASK)

%define SYSCALL_CLASS_UNIX      2

%define SYSCALL_CONSTRUCT_UNIX(syscall_number) \
      ((SYSCALL_CLASS_UNIX << SYSCALL_CLASS_SHIFT) | \
       (SYSCALL_NUMBER_MASK & (syscall_number)))

%define SYS_exit          1
%define SYS_write         4

%define N_EXT   0x1
%define N_ABS   0x2
%define N_SECT  0xe

%define REFERENCE_FLAG_UNDEFINED_NON_LAZY 0x00
%define REFERENCED_DYNAMICALLY 0x10




BITS 32

; Mach-O header
DD    MH_MAGIC_32                   ; magic
DD    CPU_TYPE_X86                 ; cputype
DD    CPU_SUBTYPE_I386_ALL    ; cpusubtype
DD    MH_EXECUTE                    ; filetype
DD    4                       ; ncmds
DD    end_commands - load_commands             ; sizeofcmds
DD    MH_NOUNDEFS                   ; flags

; Load commands
load_commands:

; Segment and Sections
DD    LC_SEGMENT                 ; cmd
DD    124                        ; cmdsize

DB    '__TEXT'             ; segname
DB    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                    ; last 10-byte of segname

DD    0x0                       ; vmaddr
DD    0x1000                      ; vmsize
DD    0                       ; fileoff
DD    filesize                    ; filesize
DD    VM_PROT_READ | VM_PROT_EXECUTE  ; maxprot
DD    VM_PROT_READ | VM_PROT_EXECUTE  ; initprot
DD    0x1                       ; nsects
DD    0x0                       ; flags

; __text section
DB    '__text'             ; sectname
DB    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                    ; last 10-byte of sectname
DB    '__TEXT'             ; segname
DB    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00                    ; last 10-byte of segname
DD    start                     ; addr
; it should be
; DD    end-start                 ; size
DD    mainsize                 ; size

DD    start                     ; offset
DD    0                         ; align
DD    0                         ; reloff
DD    0                         ; nreloc
DD    0                         ; flags
DD    0                         ; reserved1
DD    0                         ; reserved2

; linkedit segment

DD    LC_SEGMENT                 ; cmd
DD    56                        ; cmdsize

DB    '__LINKEDIT'             ; segname
DB    0x00, 0x00, 0x00, 0x00, 0x00, 0x00                    ; last 6-byte of segname

DD    0x1000                      ; vmaddr
DD    0x1000                      ; vmsize
DD    0x1000                       ; fileoff
DD    52                    ; filesize
DD    VM_PROT_READ ; maxprot
DD    VM_PROT_READ ; initprot
DD    0x0                       ; nsects
DD    0x0                       ; flags

; symtab

DD    LC_SYMTAB                 ; cmd
DD    24                        ; cmdsize

DD    4096; symoff
DD    2; nsyms
DD    string_table ; stroff
DD    end_string_table-string_table; strsize

;  unix_thread
dd    5                            ; cmd (LC_UNIXTHREAD)
dd    80                           ; cmdsize
dd    1                            ; flvaor (i386_THREAD_STATE)
dd    16                           ; count (i386_THREAD_STATE_COUNT)
dd    0, 0, 0, 0, 0, 0, 0, 0       ; state
dd    0, 0, start, 0, 0, 0, 0, 0  ; state

end_commands:

  headersize EQU ($-$$)

start:                          ; depending on the code generation size may vary a little bit
  xor   eax,eax
  inc   eax
  push  byte 42
  sub   esp, 4
  int   0x80                         ; _exit(42)
end:
  mainsize EQU end-start

; padding
  times (4096-headersize)-mainsize DB 0

  filesize  EQU 4096 ; not always true obviously

; __mh_execute_header sym
dd __mh_execute_header_string-string_table ; n_strx
db N_EXT | N_ABS; n_type
db 0x01 ; n_sect
dw REFERENCED_DYNAMICALLY ; n_desc
dd 0x0 ; n_value

; start sym
dd start_string-string_table ; n_strx
db N_EXT | N_SECT; n_type
db 0x01 ; n_sect
dw REFERENCE_FLAG_UNDEFINED_NON_LAZY ; n_desc
dd start ; n_value

string_table:
db 0x20, 0x00
__mh_execute_header_string:
db '__mh_execute_header', 0x0
start_string:
db 'start', 0x0
end_string_table: