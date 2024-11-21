#ifndef __PLAYER__
#define __PLAYER__

#include <allegro5/allegro5.h>

#include "gun.h"
#include "joystick.h"

typedef enum PLAYER_STATE { IDLE, MOVEMENT } PLAYER_STATE;

typedef struct Player {
  float x, y;
  Joystick *_joystick;
  Gun *_gun;
  int health;
  int current_frame;
  PLAYER_STATE _state;
} Player;

Player *create_player();

void update_joystick(Joystick *j, ALLEGRO_EVENT *event);

void update_player(Player *player);

void destroy_player(Player *player);

#endif  // __PLAYER__