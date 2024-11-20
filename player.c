#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#define PLAYER_SPEED 5.0
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128

Player *create_player() {
  Player *_player = (Player *)malloc(sizeof(Player));
  if (_player == NULL) return NULL;

  _player->health = 3;
  _player->x = 100;
  _player->y = 100;
  _player->_joystick = create_joystick();
  _player->_gun = create_gun();

  return _player;
}

void update_joystick(Joystick *j, ALLEGRO_EVENT *event) {
  switch (event->keyboard.keycode) {
    case ALLEGRO_KEY_DOWN:
      update_joystick_down(j);
      break;
    case ALLEGRO_KEY_UP:
      update_joystick_up(j);
      break;
    case ALLEGRO_KEY_LEFT:
      update_joystick_left(j);
      break;
    case ALLEGRO_KEY_RIGHT:
      update_joystick_right(j);
      break;
  }
}

void update_player(Player *player) {
  if (player->_joystick->down) {
    player->y += PLAYER_SPEED;
    if (player->y >= 600 - PLAYER_HEIGHT) player->y = 600 - PLAYER_HEIGHT;
  }

  if (player->_joystick->up) {
    player->y -= PLAYER_SPEED;
    if (player->y <= 0) player->y = 0;
  }

  if (player->_joystick->left) {
    player->x -= PLAYER_SPEED;
    if (player->x <= 0) {
      player->x = 0;
    }
  }

  if (player->_joystick->right) {
    player->x += PLAYER_SPEED;
    if (player->x >= 1200 - PLAYER_WIDTH) player->x = 1200 - PLAYER_WIDTH;
  }
}

void destroy_player(Player *player) {
    destroy_gun(player->_gun);
    destroy_joystick(player->_joystick);
    free(player);
}
