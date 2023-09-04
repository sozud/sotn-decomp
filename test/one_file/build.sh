mkdir -p out
cpp all.c ./out/all.c
../../bin/cc1-psx-26 -O2 -mcpu=3000 -fgnu-linker -mgas -gcoff ./out/all.c -o ./out/all.s
python3 ../../tools/maspsx/maspsx.py --no-macro-inc --expand-div ./out/all.s > ./out/all_m.s
mipsel-linux-gnu-as ./out/all_m.s -o ./out/all.o
mipsel-linux-gnu-ld -T all.ld -Map ./out/one_file.map -o ./out/one_file.elf ./out/all.o 
mipsel-linux-gnu-objdump -M -march=mips3000 -D  ./out/one_file.elf > ./out/one_file.s
