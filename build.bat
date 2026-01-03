( cc65 -t nes -Oirs menu.c -o ./build/menu.s ) ^
&& ( ca65 crt0.s -o ./build/crt0.o ) ^
&& ( ca65 chr.s -o ./build/chr.o ) ^
&& ( ca65 nametable.s -o ./build/nametable.o ) ^
&& ( ca65 palette.s -o ./build/palette.o ) ^
&& ( ca65 ./build/menu.s -o ./build/menu.o ) ^
&& ( ld65 -C nes_aorom.cfg -o ./build/menu.nes ./build/crt0.o ./build/chr.o ./build/nametable.o ./build/palette.o ./build/menu.o nes.lib ) ^
&& ( del /Q "build\crt0.o" "build\chr.o" "build\menu.o" "build\nametable.o" "build\palette.o" "build\menu.s") ^
&& ( "./tools/fceux-2.6.6-win64/fceux64.exe" ./build/menu.nes )