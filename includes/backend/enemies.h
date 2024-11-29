#ifndef __ENEMIES__
#define __ENEMIES__

#include "gun.h"
#include "time.h"

typedef enum { ENEMY_1 = 0, ENEMY_2, ENEMY_3, ENEMY_4 } ENEMY_TYPE;

typedef struct {
  ENEMY_TYPE _type;
  float x, y;
  int life;
  int isAlive;
  Gun *_gun;
} Enemy;

typedef struct {
  time_t current_time;     // tempo atual;
  time_t last_spawn_time;  // tempo do ultimo spawn
  int total;               // total de inimigos
  int interval;            // intervalo de spawn
  int spawned;             // contador de inimigos já spawnados
  int batch_size;          // quantidade por spawn
  Enemy *enemies;
} SpawnControl;

SpawnControl *create_spawn_control(ENEMY_TYPE type, int quantity);

Enemy *create_enemy(ENEMY_TYPE type, int quantity);

void update_enemies(Enemy *enemies, int spawned);

void update_spawn_control(SpawnControl *_SpawnControl);

void destroy_enemy(Enemy *enemy_vector, int size);

void destroy_spawn_control(SpawnControl *control);

#endif  // __ENEMIES__