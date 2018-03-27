OPTI = 3

prog: main.o
	g++ main.o -o prog

main.o: main.cpp
	g++ main.cpp -c -O$(OPTI) -o main.o

clean:
	rm *.o
	rm prog
