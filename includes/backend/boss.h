#ifndef __BOSS__
#define __BOSS__

typedef enum BOSS_TYPE { LEVEL_ONE_BOSS = 0, LEVEL_TWO_BOSS } BOSS_TYPE;

typedef enum BOSS_STATE {
  BOSS_STATE_NOT_SPAWNED = 0,
  BOSS_STATE_ATTACKING,
  BOSS_STATE_SHOW
} BOSS_STATE;

typedef struct Boss {
  float x, y;
  BOSS_TYPE type;
  BOSS_STATE state;

  int life;
  int current_frame;
  int spawn_timer;
} Boss;

Boss *create_boss();

int boss_should_spawn(Boss *boss);

void spawn_boss(Boss *boss);

#endif  // __BOSS__