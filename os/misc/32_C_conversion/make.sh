for file in *.asm; do fasm $file; done

# 1 sector is 512 bytes
# Lets make all the c binaries 20 sectors long why not.
# You'll have to change this if these programs get bigger
# 512 1024 2048 4096
# dd's seek parameter is zero indexed.  To make a 10240 byte file seek should be 10239

for f in $(echo "kernel editor calculator"); do 
    echo $f 
    i386-elf-gcc -c -m32 -march=i386 -ffreestanding -fno-builtin -nostdinc -O1 ${f}.c # 2>/dev/null # turn off compile errors and warnings
    i386-elf-ld -m elf_i386 -T ${f}.ld ${f}.o --oformat binary -o ${f}.bin
    dd if=/dev/zero of=${f}.bin bs=1 count=1 seek=10239 
done 

# "link"
cat bootSect.bin 2ndstage.bin testfont.bin fileTable.bin kernel.bin calculator.bin editor.bin > temp.bin 
dd if=/dev/zero of=OS.bin bs=512 count=2880 # count=2880
dd if=temp.bin of=OS.bin conv=notrunc

# run
# /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386     -drive format=raw,file=OS.bin,if=ide,index=0,media=disk
/Users/nick/qemu-2.9.1/x86_64-softmmu/qemu-system-x86_64 -drive format=raw,file=OS.bin,if=ide,index=0,media=disk

rm *.o bootSect.bin 2ndstage.bin testfont.bin fileTable.bin kernel.bin calculator.bin editor.bin temp.bin 

