#include "../../includes/backend/boss.h"

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Boss *create_boss() {
  Boss *boss = (Boss *)malloc(sizeof(Boss));
  must_init(boss, "Boss");

  boss->current_frame = 0;
  boss->life = 300;
  boss->spawn_timer = 30;
  boss->state = BOSS_STATE_NOT_SPAWNED;
  boss->x = SCREEN_WIDTH - 100;
  boss->y = -BOSS_WIDTH;

  return boss;
}

int boss_should_spawn(Boss *boss) {
  if (boss->spawn_timer == 0) return 1;
  return 0;
}

void spawn_boss(Boss *boss) {
  boss->state = BOSS_STATE_SHOW;
}

void update_boss(Boss *boss) {
  if (boss->state == BOSS_STATE_NOT_SPAWNED) return;

  if (boss->state == BOSS_STATE_SHOW) {
    boss->y -= BOSS_SPEED;
    return;
  }

  if (boss->y == (SCREEN_HEIGHT - BOSS_HEIGHT) / 2) {
    boss->state = BOSS_STATE_ATTACKING;
  }
}