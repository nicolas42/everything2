QEMU=/Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 

for file in *.asm; do fasm $file; done

# Concatenate the binary files.  Order matters.
files="bootSect.bin 2ndstage.bin testfont.bin kernel.bin fileTable.bin calculator.bin editor.bin"
cat $files > temp.bin;
# pad with zeros
dd if=/dev/zero of=OS.bin bs=512 count=10000;
dd if=temp.bin of=OS.bin conv=notrunc; # do not truncate the output file

$QEMU -drive format=raw,file=OS.bin,if=ide,index=0,media=disk

rm $files



