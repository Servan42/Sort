EXE=sort
FLAGS= -Wall -g 

$(EXE) : sort.o
	gcc -o $(EXE) sort.o

sort.o : sort.c
	gcc $(FLAGS) -c sort.c

clean : 
	rm -f -v *.gch *.o
.PHONY : clean

cleanall : clean
	rm -f -v $(EXE)
.PHONY : cleanall