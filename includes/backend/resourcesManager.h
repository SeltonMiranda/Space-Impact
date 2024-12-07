#ifndef __RESOURCES_MANAGER__
#define __RESOURCES_MANAGER__

#include <allegro5/allegro5.h>

typedef struct Player_Sprites {
  ALLEGRO_BITMAP *sprites[13];
  ALLEGRO_BITMAP *engine;
} Player_Sprites;

typedef struct Background {
  ALLEGRO_BITMAP *bg_one;
  ALLEGRO_BITMAP *bg_two;
  ALLEGRO_BITMAP *bg_common;
  float x;
} Background;

typedef struct Resources_Manager {
  Player_Sprites player;
  Background background;
} Resources_Manager;

Resources_Manager *create_resources();

void load_player_sprites(Resources_Manager *rm);
void load_all_sprites(Resources_Manager *r);

void destroy_resources(Resources_Manager *_resources);

#endif  // __RESOURCES_MANAGER__