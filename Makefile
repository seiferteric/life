

all: life

life:
	gcc life.c -o life -lSDL

clean:
	rm life
