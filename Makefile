EXE=main

make: main.c DES.c keyManipulation.c
	gcc -o $(EXE) main.c DES.c keyManipulation.c

run: make
	./$(EXE)