#ifndef __PLAYER__
#define __PLAYER__

#include <allegro5/allegro5.h>

#include "gun.h"
#include "joystick.h"

typedef enum PLAYER_STATE {
  IDLE,
  MOVEMENT
} PLAYER_STATE;

typedef struct Player {
  float x, y;           // Posicao do jogador
  Joystick *_joystick;  // Movimentacao do jogador
  Gun *_gun;            // Arma do jogador
  int health;           // Vida do jogador
  int current_frame;    // Frame atual da sprite
  PLAYER_STATE _state;
} Player;

Player *create_player();

void update_joystick(Joystick *j, ALLEGRO_EVENT *event);

void update_player(Player *player);

void destroy_player(Player *player);

#endif  // __PLAYER__