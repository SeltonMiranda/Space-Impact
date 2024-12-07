#include "../../includes/backend/boss.h"

#include <stdio.h>
#include <time.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Boss *create_boss(BOSS_TYPE type) {
  Boss *boss = (Boss *)malloc(sizeof(Boss));
  must_init(boss, "Boss");

  boss->type = type;
  boss->current_frame = 0;
  boss->life = BOSS_LIFE;
  boss->spawned = 0;
  boss->timer = time(NULL);
  boss->state = BOSS_STATE_NOT_SPAWNED;
  boss->x = SCREEN_WIDTH - 150;
  boss->y = -BOSS_HEIGHT;
  boss->direction = DOWN;

  return boss;
}

int boss_should_spawn(Boss *boss) {
  if (boss->spawned) return 0;
  if (difftime(time(NULL), boss->timer) >= BOSS_TIME_SPAWN) return 1;
  return 0;
}

void spawn_boss(Boss *boss) {
  boss->state = BOSS_STATE_SPAWNED;
  boss->spawned = 1;
}

void update_boss(Boss *boss) {
  if (boss->state == BOSS_STATE_DEAD) return;

  if (boss->state == BOSS_STATE_NOT_SPAWNED) return;

  boss->y += (boss->direction * BOSS_SPEED);
  if (boss->y <= 0) {
    boss->y = 0;
    boss->direction = DOWN;
  }

  if (boss->y >= SCREEN_HEIGHT - BOSS_HEIGHT) {
    boss->y = SCREEN_HEIGHT - BOSS_HEIGHT;
    boss->direction = UP;
  }
}

void destroy_boss(Boss *boss) {
  free(boss);
}