# sh dosemu_wrapper.sh $in $out $FLAGS $FOLDER


# sh dosemu_wrapper.sh test.c test.o -O2 3.5


dosemu -quiet -dumb -f ./dosemurc -K . -E "build.bat test.c test.o -O2 3.5"
dosemu -quiet -dumb -f ./dosemurc -K . -E "build.bat test.c test.o -O2 3.5"

unix2dos -n link.txt linkdos.txt
dosemu -quiet -dumb -f ./dosemurc -K . -E "link.bat"

dosemu -quiet -dumb -f ./dosemurc -K . -E "cpe.bat"
