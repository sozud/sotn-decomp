rm -rf out
mkdir -p out
../../bin/cc1-psx-26 -O2 -mcpu=3000 -fgnu-linker -mgas -gcoff one.c -o ./out/one.s
../../bin/cc1-psx-26 -O2 -mcpu=3000 -fgnu-linker -mgas -gcoff two.c -o ./out/two.s
../../bin/cc1-psx-26 -O2 -mcpu=3000 -fgnu-linker -mgas -gcoff three.c -o ./out/three.s
python3 ../../tools/maspsx/maspsx.py --no-macro-inc --expand-div ./out/one.s > ./out/one_m.s
python3 ../../tools/maspsx/maspsx.py --no-macro-inc --expand-div ./out/two.s > ./out/two_m.s
python3 ../../tools/maspsx/maspsx.py --no-macro-inc --expand-div ./out/three.s > ./out/three_m.s
mipsel-linux-gnu-as ./out/one_m.s -o ./out/one.o
mipsel-linux-gnu-as ./out/two_m.s -o ./out/two.o
mipsel-linux-gnu-as ./out/three_m.s -o ./out/three.o
mipsel-linux-gnu-ld -T split.ld -Map ./out/split.map -o ./out/split.elf ./out/one.o ./out/two.o ./out/three.o
mipsel-linux-gnu-objdump -M -march=mips3000 -D  ./out/split.elf > ./out/split.s
