#include "graphics.h"

void render_background(ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *buffer,
                       int bg_x) {
  al_set_target_bitmap(buffer);

  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_bitmap(background, bg_x, 0, 0);
  al_draw_bitmap(background, bg_x + SCREEN_WIDTH, 0, 0);

  al_set_target_backbuffer(al_get_current_display());
  al_draw_bitmap(buffer, 0, 0, 0);
}
