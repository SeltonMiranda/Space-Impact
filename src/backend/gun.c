#include "../../includes/backend/gun.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../includes/utils/utils.h"

Gun *create_gun(Gun_Source _source) {
  Gun *_gun = (Gun *)malloc(sizeof(Gun));
  must_init(_gun, "Gun");

  for (int i = 0; i < MAX_SHOTS; i++) {
    _gun->shots[i].is_fired = 0;
    _gun->shots[i].current_frame = 0;
  }
  _gun->_source = _source;
  _gun->timer = 0;
  return _gun;
}

void gun_shot(Gun *_gun, float x, float y) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (_gun->shots[i].is_fired == 0) {
      _gun->shots[i].is_fired = 1;
      _gun->shots[i].x = x;
      _gun->shots[i].y = y;
      break;
    }
  }
}

void update_gun(Gun *_gun, int isPlayer) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (_gun->shots[i].is_fired == 1) {
      if (isPlayer)
        _gun->shots[i].x += SHOT_SPEED;
      else
        _gun->shots[i].x -= SHOT_SPEED;

      if (_gun->shots[i].x < 0 || _gun->shots[i].x > 1200) {
        _gun->shots[i].is_fired = 0;
        _gun->shots[i].current_frame = 0;
      }
      _gun->shots[i].current_frame++;
    }
  }
}

void destroy_gun(Gun *gun) {
  free(gun);
}