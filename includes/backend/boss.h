#ifndef __BOSS__
#define __BOSS__

#include <time.h>

typedef enum BOSS_TYPE { LEVEL_ONE_BOSS = 0, LEVEL_TWO_BOSS } BOSS_TYPE;

typedef enum BOSS_STATE {
  BOSS_STATE_NOT_SPAWNED = 0,
  BOSS_STATE_SPAWNED,
  BOSS_STATE_ATTACKING
} BOSS_STATE;

typedef struct Boss {
  float x, y;
  BOSS_TYPE type;
  BOSS_STATE state;

  time_t timer;
  int life;
  int current_frame;
  int direction;  // 1 para cima e -1 para baixo
} Boss;

Boss *create_boss(BOSS_TYPE type);

int boss_should_spawn(Boss *boss);

void spawn_boss(Boss *boss);

void update_boss(Boss *boss);

void destroy_boss(Boss *boss);

#endif  // __BOSS__