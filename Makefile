

all: life

life: life.c
	gcc life.c -o life -lSDL

clean:
	rm -f life
