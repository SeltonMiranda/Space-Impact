MAIN=SpaceImpact
LIBS=
ALLEGRO_LIBS=$(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 --libs --cflags)
CFLAGS=-Wall -Wextra -pedantic -g --std=c99


all:$(MAIN)

$(MAIN): main.o 
	gcc -o $(MAIN) $^ $(ALLEGRO_LIBS) $(CFLAGS)

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o *.gch $(MAIN)