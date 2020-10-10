EXE=main

make: sequential.c DES.c keyManipulation.c
	gcc -o $(EXE) sequential.c DES.c keyManipulation.c

run: make
	./$(EXE)

run4: make
	./$(EXE)
	./$(EXE)
	./$(EXE)
	./$(EXE)