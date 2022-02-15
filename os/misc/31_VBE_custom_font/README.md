
Get qemu and fasm then run make


assembles the binaries with fasm then links them using cat and dd 

run the output in qemu-386

outputs a high resolution screen with a bitmapped font

The order of the files, which is important is

bootSect.bin 2ndstage.bin testfont.bin kernel.bin fileTable.bin calculator.bin editor.bin

calculator and editor can be taken out and the system will still boot and do the high resolution VBE stuff

