nonRep: nonRep.c concelho.o distrito.o freguesia.o
	gcc -Wall -o nonRep nonRep.c *.h *.o

distrito.o: distrito.h distrito.c
	gcc -Wall -c distrito.h distrito.c

concelho.o: concelho.h concelho.c
	gcc -Wall -c concelho.h concelho.c

freguesia.o: freguesia.h freguesia.c
	gcc -Wall -c freguesia.h freguesia.c

clean:
	rm -f *.*~ *~ nonRep *.o *.gch wget* bd.txt
