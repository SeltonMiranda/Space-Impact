#include "../../includes/backend/level.h"

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Level *loadLevel(LEVEL_PHASE phase) {
  Level *l = (Level *)malloc(sizeof(Level));
  must_init(l, "Level");

  l->background_x = 0;
  l->phase = phase;
  switch (l->phase) {
    case LEVEL_PHASE_ONE:
      l->boss = create_boss(LEVEL_ONE_BOSS);
      l->sp1 = create_spawn_control(ENEMY_1, 100);
      l->sp2 = create_spawn_control(ENEMY_2, 200);
      break;

    case LEVEL_PHASE_TWO:
      return l;
  }

  return l;
}

static void update_background(Level *l) {
  l->background_x -= BACKGROUND_SPEED;
  if (l->background_x <= -SCREEN_WIDTH) l->background_x = 0;
}

void update_level(Level *l) {
  update_background(l);
  update_spawn_control(l->sp1);
  update_spawn_control(l->sp2);
  update_enemies(l->sp1->enemies, l->sp1->spawned);
  update_enemies(l->sp2->enemies, l->sp2->spawned);
  update_boss(l->boss);
  if (boss_should_spawn(l->boss)) spawn_boss(l->boss);
}

void destroy_level(Level *l) {
  destroy_boss(l->boss);
  destroy_spawn_control(l->sp1);
  destroy_spawn_control(l->sp2);
  free(l);
}