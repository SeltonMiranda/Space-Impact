MAIN=SpaceImpact
LIBS=
ALLEGRO_LIBS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs --cflags)
CFLAGS=-Wall -Wextra -pedantic -g --std=c99
OBJECTS=main.o graphics.o


all:$(MAIN)

$(MAIN): $(OBJECTS)
	gcc -o $(MAIN) $^ $(ALLEGRO_LIBS) $(CFLAGS)

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o *.gch $(MAIN)