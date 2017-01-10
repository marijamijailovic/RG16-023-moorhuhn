PROGRAM = moorhuhn
CC  	= gcc
CCLIBS	= -lGL -lGLU -lglut -lSOIL -lm
CCFLAGS	= -Wall
OBJ 	= main.o	\
				callback.o \
				initialize.o	\
				object.o \
				scene.o \
				collision.o \
				gui.o

%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)

.PHONY: clean

clean:
	rm -rf $(PROGRAM)
	rm -rf *.o
	rm -rf *~
