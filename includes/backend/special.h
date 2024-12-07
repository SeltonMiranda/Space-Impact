#ifndef __SPECIAL_ATTACK__
#define __SPECIAL_ATTACK__

#include <time.h>

#include "gun.h"

typedef enum SPECIAL_TYPE { SPECIAL_GUN_ONE = 0, SPECIAL_GUN_TWO } SPECIAL_TYPE;

typedef struct Special {
  int is_active;
  int damage;
  SPECIAL_TYPE type;
  time_t time;
  Gun *gun;
} Special;

Special *init_special();

#endif  // __SPECIAL_ATTACK__