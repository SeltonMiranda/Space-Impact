#include "gun.h"

#include <stdlib.h>

Gun *create_gun() {
  Gun *_gun = (Gun *)malloc(sizeof(Gun));
  if (_gun == NULL) return NULL;

  for (int i = 0; i < 100; i++) {
    _gun->shots[i].is_fired = 0;
  }

  _gun->timer = 5;
  return _gun;
}

void destroy_gun(Gun *gun) {
  free(gun);
}