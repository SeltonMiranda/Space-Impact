#ifndef __GUN__
#define __GUN__

#include "shot.h"

typedef struct Gun {
    float timer;
    Shot shots[100];
} Gun;

Gun *create_gun();

void destroy_gun(Gun *gun);
#endif // __GUN__