CC   = gcc
OBJ  = main.o sum.o $(RES)
LINKOBJ  = main.o sum.o $(RES)
BIN  = sum
RM = rm -f
INCS =  
CFLAGS = $(INCS) 

all: sum

clean: 
	${RM} *.o *.exe

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

sum.o: sum.c
	$(CC) -c sum.c -o sum.o $(CFLAGS)
