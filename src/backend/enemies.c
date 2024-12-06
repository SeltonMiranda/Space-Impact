#include "../../includes/backend/enemies.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Enemy *create_enemy(ENEMY_TYPE type, int quantity) {
  Enemy *enemy_vector = (Enemy *)malloc(sizeof(Enemy) * quantity);
  must_init(enemy_vector, "Enemy vector");

  for (int i = 0; i < quantity; i++) {
    enemy_vector[i]._type = type;
    enemy_vector[i].isAlive = ALIVE;
    enemy_vector[i]._gun = create_gun(ENEMY);
    enemy_vector[i]._gun->timer = rand_between(MIN_TIME, MAX_TIME);

    switch (type) {
      case ENEMY_1:
        enemy_vector[i].life = 1;
        enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH + i * ENEMY_PADDING;
        enemy_vector[i].y = (SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING;
        break;

      case ENEMY_2:
        enemy_vector[i].life = 2;
        enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH;
        if (enemy_vector[i].y > 500) enemy_vector[i].y = 0;
        enemy_vector[i].y =
            ENEMY_PADDING + (ENEMY_HEIGHT + ENEMY_PADDING) * (i % BATCH);
        break;

      case ENEMY_3:
        enemy_vector[i].life = 1;
        enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH + i * ENEMY_PADDING;
        enemy_vector[i].y = (SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING;
        break;

      case ENEMY_4:
        enemy_vector[i].life = 2;
        enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH + i * ENEMY_PADDING;
        enemy_vector[i].y = (SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING;
        break;
    }
  }

  return enemy_vector;
}

SpawnControl *create_spawn_control(ENEMY_TYPE type, int quantity) {
  SpawnControl *_SpawnControl = (SpawnControl *)malloc(sizeof(SpawnControl));
  must_init(_SpawnControl, "SpawnControl");

  _SpawnControl->enemies = create_enemy(type, quantity);
  _SpawnControl->total = quantity;
  _SpawnControl->spawned = 0;
  _SpawnControl->batch_size = 5;
  _SpawnControl->last_spawn_time = time(NULL);

  switch (type) {
    case ENEMY_1:
      _SpawnControl->interval = 5;  // em segundos
      break;
    case ENEMY_2:
      _SpawnControl->interval = 3;  // em segundos
      break;
    case ENEMY_3:
      _SpawnControl->interval = 20;  // em segundos
      break;
    case ENEMY_4:
      _SpawnControl->interval = 40;  // em segundos
      break;
  }

  return _SpawnControl;
}

void update_spawn_control(SpawnControl *_SpawnControl) {
  _SpawnControl->current_time = time(NULL);

  if (difftime(_SpawnControl->current_time, _SpawnControl->last_spawn_time) >=
      _SpawnControl->interval) {
    int to_spawn = (_SpawnControl->spawned + _SpawnControl->batch_size >
                    _SpawnControl->total)
                       ? _SpawnControl->total - _SpawnControl->spawned
                       : _SpawnControl->batch_size;

    _SpawnControl->spawned += to_spawn;
    _SpawnControl->last_spawn_time = _SpawnControl->current_time;
  }
}

static void update_enemy_position(Enemy *enemy) {
  enemy->x -= 1.0f;
  switch (enemy->_type) {
    case ENEMY_1:
      enemy->y = ((SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING) +
                 sin(enemy->x / 50) * 200;
      break;
    default:
      return;
  }
}

void update_enemies(Enemy *enemies, int spawned) {
  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive) {
      update_enemy_position(&enemies[i]);

      if (enemies[i]._gun->timer == 0 && enemies[i].x < SCREEN_WIDTH) {
        gun_shot(enemies[i]._gun, enemies[i].x,
                 enemies[i].y + ENEMY_HEIGHT / 2 - 1);
        enemies[i]._gun->timer = rand_between(MIN_TIME, MAX_TIME);
      }

      if (enemies[i]._gun->timer > 0) enemies[i]._gun->timer--;

      if (enemies[i].x < 0) {
        enemies[i].isAlive = DEAD;
      }

      update_gun(enemies[i]._gun, 0);
    }
  }
}

void destroy_enemy(Enemy *enemy_vector, int size) {
  for (int i = 0; i < size; i++) {
    destroy_gun(enemy_vector[i]._gun);
  }
  free(enemy_vector);
}

void destroy_spawn_control(SpawnControl *control) {
  destroy_enemy(control->enemies, control->total);
  free(control);
}