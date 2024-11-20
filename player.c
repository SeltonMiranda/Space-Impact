#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#define PLAYER_SPEED 5.0
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128

#define SHOT_COOLDOWN 10

Player *create_player() {
  Player *_player = (Player *)malloc(sizeof(Player));
  if (_player == NULL) return NULL;

  _player->health = 3;
  _player->x = 100;
  _player->y = 100;
  _player->_joystick = create_joystick();
  _player->_gun = create_gun();
  _player->current_frame = 0;
  _player->_state = IDLE;

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
    case ALLEGRO_KEY_Z:
      update_joystick_fire(j);
      break;
  }
}

void update_player(Player *player) {
  player->_state = IDLE;
  
  if (player->_joystick->down) {
    player->_state = MOVEMENT;
    player->y += PLAYER_SPEED;
    if (player->y >= 600 - PLAYER_HEIGHT) player->y = 600 - PLAYER_HEIGHT;
  }

  if (player->_joystick->up) {
    player->_state = MOVEMENT;
    player->y -= PLAYER_SPEED;
    if (player->y <= 0) player->y = 0;
  }

  if (player->_joystick->left) {
    player->_state = MOVEMENT;
    player->x -= PLAYER_SPEED;
    if (player->x <= 0) {
      player->x = 0;
    }
  }

  if (player->_joystick->right) {
    player->_state = MOVEMENT;
    player->x += PLAYER_SPEED;
    if (player->x >= 1200 - PLAYER_WIDTH) player->x = 1200 - PLAYER_WIDTH;
  }

  if (player->_joystick->fire) {
    if (player->_gun->timer == 0) {
      gun_shot(player->_gun, player->x + PLAYER_WIDTH, player->y + PLAYER_HEIGHT / 2 - 1);
      player->_gun->timer = SHOT_COOLDOWN;
    }

    if (player->_gun->timer > 0) player->_gun->timer--;
  }

  
  update_gun(player->_gun, 1);
}

void destroy_player(Player *player) {
  destroy_gun(player->_gun);
  destroy_joystick(player->_joystick);
  free(player);
}
