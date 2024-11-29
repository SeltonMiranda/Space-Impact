#include "../../includes/frontend/graphics.h"

#include <allegro5/allegro_primitives.h>

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
    int frame = (_player->current_frame / 15) % 12 + 1;
    al_draw_bitmap(_resources->player.sprites[frame], _player->x, _player->y,
                   0);
  }

  al_draw_bitmap(_resources->player.sprites[0], _player->x, _player->y, 0);
}

void draw_enemies(Enemy *enemies, int spawned) {
  ALLEGRO_COLOR color;
  switch (enemies[0]._type) {
    case ENEMY_1:
      color = al_map_rgb(255, 0, 0);
      break;
    case ENEMY_2:
      color = al_map_rgb(0, 0, 255);
      break;
    case ENEMY_3:
      color = al_map_rgb(255, 0, 0);
      break;
    case ENEMY_4:
      color = al_map_rgb(0, 0, 255);
      break;
  }

  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive) {
      al_draw_filled_rectangle(enemies[i].x, enemies[i].y, enemies[i].x + 30,
                               enemies[i].y + 30, color);
    }
  }
}

void draw_shots(Gun *_gun) {
  for (int i = 0; i < 100; i++) {
    if (_gun->shots[i].is_fired == 1) {
      al_draw_filled_circle(_gun->shots[i].x, _gun->shots[i].y, 20,
                            al_map_rgb(0, 255, 0));
    }
  }
}