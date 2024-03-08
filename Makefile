all: compil clean run

compil:
	clang++ -Wall -Ofast -march=native lab1.cpp

run: lab1
	./lab1

clean: 
	rm -rf a.out