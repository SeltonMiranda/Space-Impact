#include "../../includes/backend/resourcesManager.h"

#include <allegro5/allegro_image.h>
#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

#define PLAYER_IDLE 0

Resources_Manager *create_resources() {
  Resources_Manager *r = (Resources_Manager *)malloc(sizeof(Resources_Manager));
  must_init(r, "Resources Manager");
  load_player_sprites(r);
  return r;
}

void load_player_sprites(Resources_Manager *rm) {
  rm->player.sprites[PLAYER_IDLE] =
      al_load_bitmap("assets/player/player_base.png");

  rm->player.engine = al_load_bitmap("assets/player/player_engine.png");
  for (int i = 0; i < 12; i++) {
    rm->player.sprites[i + 1] =
        al_create_sub_bitmap(rm->player.engine, 0, i * 128, 128, 128);
  }
}

void load_background(Resources_Manager *r) {
  r->background.bg_one = al_load_bitmap(BACKGROUND_LEVEL_ONE);
  r->background.bg_two = al_load_bitmap(BACKGROUND_LEVEL_TWO);
  r->background.bg_common = al_load_bitmap(BACKGROUND_COMMON);
  r->background.x = 0;
}

void load_shots_sprites(Resources_Manager *r) {
  r->shots.normal_spritesheet = al_load_bitmap(NORMAL_SHOT_SPRITE);
  r->shots.enemy_shot_spritesheet = al_load_bitmap(ENEMY_SHOT_SPRITE);

  for (int i = 0; i < 3; i++) {
    r->shots.normal_shot[i] =
        al_create_sub_bitmap(r->shots.normal_spritesheet, 0, i * SHOT_HEIGHT,
                             SHOT_WIDTH, SHOT_HEIGHT);
  }

  for (int i = 0; i < 3; i++) {
    r->shots.enemy_shot[i] = al_create_sub_bitmap(
        r->shots.enemy_shot_spritesheet, 0, i * ENEMY_SHOT_HEIGHT,
        ENEMY_SHOT_WIDTH, ENEMY_SHOT_HEIGHT);
  }
}

void load_enemy_sprites(Resources_Manager *r) {
  r->enemy.enemy_one = al_load_bitmap(ENEMY_ONE_SPRITE);
  r->enemy.enemy_two = al_load_bitmap(ENEMY_TWO_SPRITE);
  r->enemy.enemy_three = NULL;
  r->enemy.enemy_four = NULL;
}

void load_all_sprites(Resources_Manager *r) {
  load_background(r);
  load_shots_sprites(r);
  load_player_sprites(r);
  load_enemy_sprites(r);
}

void destroy_resources(Resources_Manager *_resources) {
  if (!_resources) return;
  al_destroy_bitmap(_resources->enemy.enemy_one);
  al_destroy_bitmap(_resources->enemy.enemy_two);
  al_destroy_bitmap(_resources->player.sprites[0]);
  al_destroy_bitmap(_resources->player.engine);
  al_destroy_bitmap(_resources->shots.normal_spritesheet);
  al_destroy_bitmap(_resources->shots.enemy_shot_spritesheet);
  free(_resources);
}