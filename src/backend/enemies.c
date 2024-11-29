#include "../../includes/backend/enemies.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

#define ENEMY_WIDTH 30
#define ENEMY_HEIGHT 30

#define DEAD 0
#define ALIVE 1

#define ENEMY_PADDING 50

Enemy *create_enemy(ENEMY_TYPE type, int quantity) {
  Enemy *enemy_vector = (Enemy *)malloc(sizeof(Enemy) * quantity);
  if (!enemy_vector) {
    printf("Couldn't load enemy_vector\n");
    exit(1);
  }

  for (int i = 0; i < quantity; i++) {
    enemy_vector[i]._type = type;
    enemy_vector[i].isAlive = ALIVE;
    enemy_vector[i].x = SCREEN_WIDTH + ENEMY_WIDTH + i * ENEMY_PADDING;
    enemy_vector[i].y = (SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING;
    enemy_vector[i]._gun = create_gun(ENEMY);
    if (!enemy_vector[i]._gun) {
      printf("Couldn't load enemy_vector[%d]._gun\n", i);
      exit(1);
    }

    switch (type) {
      case ENEMY_1:
        enemy_vector[i].life = 1;
        break;

      case ENEMY_2:
        enemy_vector[i].life = 2;
        break;

      case ENEMY_3:
        enemy_vector[i].life = 1;
        break;

      case ENEMY_4:
        enemy_vector[i].life = 2;
        break;
    }
  }

  return enemy_vector;
}

SpawnControl *create_spawn_control(ENEMY_TYPE type, int quantity) {
  SpawnControl *_SpawnControl = (SpawnControl *)malloc(sizeof(SpawnControl));
  if (!_SpawnControl) {
    exit(1);
  }

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
      _SpawnControl->interval = 40;  // em segundos
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

void update_enemies(Enemy *enemies, int spawned) {
  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive) {
      enemies[i].x -= 2;
      if (enemies[i]._type == ENEMY_1) {
        enemies[i].y = ((SCREEN_HEIGHT - ENEMY_HEIGHT) / 2 - ENEMY_PADDING) +
                       sin(enemies[i].x / 50) * 200;
      }

      if (enemies[i].x < 0) {
        enemies[i].isAlive = DEAD;
      }
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