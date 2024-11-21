#include "../../includes/frontend/graphics.h"

void render_background(ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *buffer,
                       int bg_x) {
  al_set_target_bitmap(buffer);

  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_draw_bitmap(background, bg_x, 0, 0);
  al_draw_bitmap(background, bg_x + SCREEN_WIDTH, 0, 0);

  al_set_target_backbuffer(al_get_current_display());
  al_draw_bitmap(buffer, 0, 0, 0);
}

void draw_player(Player *_player, Resources_Manager *_resources) {
  if (_player->_state == MOVEMENT) {
    int frame = (_player->current_frame / 8) % 12 + 1;
    al_draw_bitmap(_resources->player.sprites[frame], _player->x, _player->y,
                   0);
  }

  al_draw_bitmap(_resources->player.sprites[0], _player->x, _player->y, 0);
}
