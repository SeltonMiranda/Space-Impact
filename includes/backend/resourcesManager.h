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

  ALLEGRO_BITMAP *boss_one_first_shot;
  ALLEGRO_BITMAP *boss_one_second_shot_spritesheet;
  ALLEGRO_BITMAP *boss_one_second_shot[5];

  ALLEGRO_BITMAP *boss_two_first_shot[4];
  ALLEGRO_BITMAP *boss_two_second_shot[4];
} Shot_Sprites;

typedef struct Background {
  ALLEGRO_BITMAP *bg_one;
  ALLEGRO_BITMAP *bg_two;
  ALLEGRO_BITMAP *bg_common;
  float x;
} Background;

typedef struct Boss_Sprite {
  ALLEGRO_BITMAP *boss_one;
  ALLEGRO_BITMAP *boss_two;
} Boss_Sprite;

typedef struct Explosion_FX {
  ALLEGRO_BITMAP *explosion_spritesheet;
  ALLEGRO_BITMAP *explosion[9];
} Explosion_FX;

// typedef struct Special_Sprites {
//   ALLEGRO_BITMAP *shot_one[]
// } Special_Sprites;

typedef struct Resources_Manager {
  Player_Sprites player;
  Background background;
  Shot_Sprites shots;
  Enemy_Sprites enemy;
  Boss_Sprite boss;
  Explosion_FX explosion;
} Resources_Manager;

Resources_Manager *create_resources();

void load_player_sprites(Resources_Manager *r);

void load_shots_sprites(Resources_Manager *r);

void load_boss_sprites(Resources_Manager *r);

void load_explosion_sprites(Resources_Manager *r);

void load_enemy_sprites(Resources_Manager *r);

void load_all_sprites(Resources_Manager *r);

void destroy_resources(Resources_Manager *_resources);

#endif  // __RESOURCES_MANAGER__