#ifndef __GUN__
#define __GUN__

#include "shot.h"

typedef struct Gun {
    float timer;
    Shot shots[100];
} Gun;

#endif // __GUN__