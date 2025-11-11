# TESTING SCRIPT NO. 1
nasm temp.asm -f elf64 -o temp.o
ld temp.o -o temp
cp ./temp ./dist/linux_x64/
cd ./dist/linux_x64/