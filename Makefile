stack.o : stack.c stack.h
	clang -g -c stack.c

token.o : token.c token.h
	clang -g -c token.c

print.o : print.c print.h token.h stack.h
	clang -g -c print.c

jc.o : jc.c token.h print.h
	clang -g -c jc.c

jc : jc.o token.o print.o stack.o
	clang -Wall -s -o jc jc.o token.o print.o stack.o

clean : 
	rm jc *.o 