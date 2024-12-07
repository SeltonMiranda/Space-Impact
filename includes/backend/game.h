#ifndef __GAME__
#define __GAME__

#include "../frontend/graphics.h"
#include "level.h"
#include "player.h"
// #include "../collision/collision.h"

#include <allegro5/allegro5.h>

#include "resourcesManager.h"
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>

typedef enum GAME_STATE {
  GAME_STATE_MENU = 0,
  GAME_STATE_LEVEL_ONE,
  GAME_STATE_LEVEL_TWO,
  GAME_STATE_VICTORY,
  GAME_STATE_GAME_OVER
} GAME_STATE;

typedef struct Game {
  GAME_STATE state;
  Level *level;
  Player *player;
  Resources_Manager *rm;
  int score;
  int is_running;

  ALLEGRO_BITMAP *background;
  ALLEGRO_TIMER *game_timer;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_DISPLAY *display;

} Game;

void init_allegro();

void init_game(Game *game);

void game_loop(Game *game);

void game_run(Game *game);

void handleKeyPress(Game *game, ALLEGRO_EVENT *ev);

void update_game_state(Game *game);

#endif  // __GAME__