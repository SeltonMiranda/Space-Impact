#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

typedef struct Background {
  ALLEGRO_BITMAP *_background;
} Background;

void render_background(ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *buffer,
                       int bg_x);

#endif  // __GRAPHICS__