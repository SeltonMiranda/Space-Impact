#include "joystick.h"

#include <stdlib.h>

Joystick* create_joystick() {
  Joystick* j = (Joystick*)malloc(sizeof(Joystick));
  if (!j) return NULL;
  j->up = 0;
  j->down = 0;
  j->right = 0;
  j->left = 0;

  return j;
}

void destroy_joystick(Joystick* j) {
  free(j);
}

void update_joystick_right(Joystick* j) {
  j->right = j->right ^ 1;
}

void update_joystick_left(Joystick* j) {
  j->left = j->left ^ 1;
}

void update_joystick_up(Joystick* j) {
  j->up = j->up ^ 1;
}

void update_joystick_down(Joystick* j) {
  j->down = j->down ^ 1;
}
