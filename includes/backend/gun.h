#ifndef __GUN__
#define __GUN__

#include "shot.h"

#define MAX_SHOTS 256

typedef struct Gun {
  int timer;
  Shot shots[MAX_SHOTS];
} Gun;

Gun *create_gun();

void gun_shot(Gun *_gun, float x, float y);

void update_gun(Gun *_gun, int isPlayer);

void draw_shots(Gun *_gun);

void destroy_gun(Gun *gun);
#endif  // __GUN__