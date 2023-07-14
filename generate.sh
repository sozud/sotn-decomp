rm -rf c2.gpr 
rm -rf *.rep
rm -rf c2.lock
rm -rf c2.lock~
python3 ./tools/ghidra/create-project.py --ghidra-root /home/d/ghidra_10.3_PUBLIC --exe ./disks/saturn/0.BIN --symbols ./symbols.json 
sh ~/ghidra_10.3_PUBLIC/ghidraRun /home/d/sotn-decomp/c2.gpr