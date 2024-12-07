#ifndef __RESOURCES_MANAGER__
#define __RESOURCES_MANAGER__

#include <allegro5/allegro5.h>

typedef struct Player_Sprites {
  ALLEGRO_BITMAP *sprites[13];
  ALLEGRO_BITMAP *engine;
} Player_Sprites;

typedef struct Enemy_Sprites {
  ALLEGRO_BITMAP *enemy_one;
  ALLEGRO_BITMAP *enemy_two;
  ALLEGRO_BITMAP *enemy_three;
  ALLEGRO_BITMAP *enemy_four;
} Enemy_Sprites;

typedef struct Shot_Sprites {
  ALLEGRO_BITMAP *normal_spritesheet;
  ALLEGRO_BITMAP *normal_shot[3];
  ALLEGRO_BITMAP *enemy_shot_spritesheet;
  ALLEGRO_BITMAP *enemy_shot[3];
} Shot_Sprites;

typedef struct Background {
  ALLEGRO_BITMAP *bg_one;
  ALLEGRO_BITMAP *bg_two;
  ALLEGRO_BITMAP *bg_common;
  float x;
} Background;

typedef struct Resources_Manager {
  Player_Sprites player;
  Background background;
  Shot_Sprites shots;
  Enemy_Sprites enemy;
} Resources_Manager;

Resources_Manager *create_resources();

void load_player_sprites(Resources_Manager *r);
void load_all_sprites(Resources_Manager *r);
void load_shots_sprites(Resources_Manager *r);
void load_enemy_sprites(Resources_Manager *r);

void destroy_resources(Resources_Manager *_resources);

#endif  // __RESOURCES_MANAGER__