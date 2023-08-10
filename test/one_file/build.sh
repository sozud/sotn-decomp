mkdir -p out
../../bin/cc1-psx-26 -O2 -mcpu=3000 -fgnu-linker -mgas -gcoff all.c -o ./out/all.s
python3 ../../tools/maspsx/maspsx.py --no-macro-inc --expand-div ./out/all.s > ./out/all_m.s
mipsel-linux-gnu-as ./out/all_m.s -o ./out/all.o
mipsel-linux-gnu-ld -Map ./out/one_file.map -o ./out/one_file.elf ./out/all.o 
