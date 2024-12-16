
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -fPIC -O3
OBJDIR = obj

stack.o: stack.c stack.h fstack.h dstack.h
	$(CC) -c stack.c -o $(OBJDIR)/stack.o $(CFLAGS)

fstack.o: fstack.c fstack.h stack.h
	$(CC) -c fstack.c -o $(OBJDIR)/fstack.o $(CFLAGS)

dstack.o: dstack.c dstack.h stack.h
	$(CC) -c dstack.c -o $(OBJDIR)/dstack.o $(CFLAGS)

test.o: test.c stack.h fstack.h dstack.h
	$(CC) -c test.c -o $(OBJDIR)/test.o $(CFLAGS)

#compile la librairie en dynamique .so et statique .a
#copie le .h dans le dossier parent
lib: stack.o fstack.o dstack.o
	$(CC) -shared $(OBJDIR)/stack.o $(OBJDIR)/fstack.o $(OBJDIR)/dstack.o -o ../libstack.so $(CFLAGS)
	cp stack.h ../libstack.h
	ar rcs ../libstack.a $(OBJDIR)/stack.o $(OBJDIR)/fstack.o $(OBJDIR)/dstack.o

#compile et execute le programme de test
test: test.o stack.o fstack.o dstack.o
	$(CC) $(OBJDIR)/test.o $(OBJDIR)/stack.o $(OBJDIR)/fstack.o $(OBJDIR)/dstack.o -o $@ $(CFLAGS)
	./$@
