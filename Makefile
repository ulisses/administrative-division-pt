CC=gcc
LEX=flex
YACC=yacc

lista: lista.y lista.l distrito.o concelho.o freguesia.o
	$(YACC) -d lista.y
	$(CC) -c y.tab.c
	$(LEX) lista.l
	$(CC) -c lex.yy.c
	$(CC) y.tab.o lex.yy.o -lfl -o lista freguesia.o concelho.o distrito.o

distrito.o: distrito.h distrito.c
	gcc -Wall -c distrito.h distrito.c

concelho.o: concelho.h concelho.c
	gcc -Wall -c concelho.h concelho.c

freguesia.o: freguesia.h freguesia.c
	gcc -Wall -c freguesia.h freguesia.c

clean:
	rm -f y.tab.* lex.yy.* lista *.*~ *~ *.gch *.o
