#include "../../../includes/backend/collision/collision.h"

static int collide(float ax1, float ay1, float ax2, float ay2, float bx1,
                   float by1, float bx2, float by2) {
  if (ax1 > bx2) return 0;
  if (ax2 < bx1) return 0;
  if (ay1 > by2) return 0;
  if (ay2 < by1) return 0;

  return 1;
}

static void handleSpecialCollision(Player *player) {
  player->special_attack->is_active = 1;
  player->special_attack->on_map = 0;
  player->special_attack->burst_time = time(NULL);
}

static void handleShotToEnemyCollision(Shot *shot, Enemy *enemy) {
  enemy->life -= 1;
  shot->is_fired = 0;
  if (enemy->life <= 0) enemy->isAlive = DEAD;
}

void check_player_shots(Gun *gun, Enemy *enemies1, int spawned1,
                        Enemy *enemies2, int spawned2) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (gun->shots[i].is_fired) {
      for (int j = 0; j < spawned1; j++) {
        if (enemies1[j].isAlive &&
            collide(gun->shots[i].x, gun->shots[i].y, gun->shots[i].x + 40,
                    gun->shots[i].y + 40, enemies1[j].x, enemies1[j].y,
                    enemies1[j].x + ENEMY_WIDTH,
                    enemies1[j].y + ENEMY_HEIGHT)) {
          handleShotToEnemyCollision(&gun->shots[i], &enemies1[j]);
        }
      }
    }
  }

  for (int i = 0; i < MAX_SHOTS; i++) {
    if (gun->shots[i].is_fired) {
      for (int j = 0; j < spawned2; j++) {
        if (enemies2[j].isAlive &&
            collide(gun->shots[i].x, gun->shots[i].y, gun->shots[i].x + 40,
                    gun->shots[i].y + 40, enemies2[j].x, enemies2[j].y,
                    enemies2[j].x + ENEMY_WIDTH,
                    enemies2[j].y + ENEMY_HEIGHT)) {
          handleShotToEnemyCollision(&gun->shots[i], &enemies2[j]);
        }
      }
    }
  }
}

void check_special_item_collision(Player *player) {
  if (player->special_attack->on_map &&
      collide(player->x, player->y, player->x + PLAYER_WIDTH,
              player->y + PLAYER_HEIGHT, player->special_attack->x,
              player->special_attack->y, player->special_attack->x + 10,
              player->special_attack->y + 10)) {
    handleSpecialCollision(player);
  }
}

static void handleShotToPlayerCollision(Shot *shot, Player *player) {
  player->health -= 1;
  shot->is_fired = 0;
}

void check_enemy_shots(Enemy *enemies1, int spawned1, Enemy *enemies2,
                       int spawned2, Player *player) {
  for (int i = 0; i < spawned1; i++) {
    for (int j = 0; j < MAX_SHOTS; j++) {
      if (enemies1[i]._gun->shots[j].is_fired &&
          collide(player->x, player->y, player->x + PLAYER_WIDTH,
                  player->y + PLAYER_HEIGHT, enemies1[i]._gun->shots[j].x,
                  enemies1[i]._gun->shots[j].y,
                  enemies1[i]._gun->shots[j].x + 40,
                  enemies1[i]._gun->shots[j].y + 40)) {
        handleShotToPlayerCollision(&enemies1[i]._gun->shots[j], player);
      }
    }
  }

  for (int i = 0; i < spawned2; i++) {
    for (int j = 0; j < MAX_SHOTS; j++) {
      if (enemies2[i]._gun->shots[j].is_fired &&
          collide(player->x, player->y, player->x + PLAYER_WIDTH,
                  player->y + PLAYER_HEIGHT, enemies2[i]._gun->shots[j].x,
                  enemies2[i]._gun->shots[j].y,
                  enemies2[i]._gun->shots[j].x + 40,
                  enemies2[i]._gun->shots[j].y + 40)) {
        handleShotToPlayerCollision(&enemies2[i]._gun->shots[j], player);
      }
    }
  }
}

void check_player_enemy_collision(Player *player, Enemy *enemies1,
                                  int spawned_enemies1, Enemy *enemies2,
                                  int spawned_enemies2) {
  for (int i = 0; i < spawned_enemies1; i++) {
    if (enemies1[i].isAlive &&
        collide(player->x, player->y, player->x + PLAYER_WIDTH,
                player->y + PLAYER_HEIGHT, enemies1[i].x, enemies1[i].y,
                enemies1[i].x + ENEMY_WIDTH, enemies1[i].y + ENEMY_HEIGHT)) {
      player->health--;
      enemies1[i].life--;
      if (enemies1[i].life == 0) enemies1[i].isAlive = DEAD;
    }
  }

  for (int i = 0; i < spawned_enemies2; i++) {
    if (enemies2[i].isAlive &&
        collide(player->x, player->y, player->x + PLAYER_WIDTH,
                player->y + PLAYER_HEIGHT, enemies2[i].x, enemies2[i].y,
                enemies2[i].x + ENEMY_WIDTH, enemies2[i].y + ENEMY_HEIGHT)) {
      player->health--;
      enemies2[i].life--;
      if (enemies2[i].life == 0) enemies2[i].isAlive = DEAD;
    }
  }
}

void check_boss_collision(Player *player, Boss *boss) {
  if (collide(player->x, player->y, player->x + PLAYER_WIDTH,
              player->y + PLAYER_HEIGHT, boss->x, boss->y, boss->x + BOSS_WIDTH,
              boss->y + BOSS_HEIGHT)) {
    player->health = 0;
  }

  Gun *g = player->_gun;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (g->shots[i].is_fired &&
        collide(g->shots[i].x, g->shots[i].y, g->shots[i].x + 40,
                g->shots[i].y + 40, boss->x, boss->y, boss->x + BOSS_WIDTH,
                boss->y + BOSS_HEIGHT)) {
      boss->life--;
      g->shots[i].is_fired = 0;
      if (boss->life == 0) boss->state = BOSS_STATE_DEAD;
    }
  }
}

void check_all_collisions(Player *player, Enemy *enemies1, int spawned_enemies1,
                          Enemy *enemies2, int spawned_enemies2, Boss *boss) {
  check_special_item_collision(player);
  check_player_enemy_collision(player, enemies1, spawned_enemies1, enemies2,
                               spawned_enemies2);

  // disparos dos inimigos no jogador
  check_enemy_shots(enemies1, spawned_enemies1, enemies2, spawned_enemies2,
                    player);
  // disparos do jogador no inimigo
  check_player_shots(player->_gun, enemies1, spawned_enemies1, enemies2,
                     spawned_enemies2);

  check_boss_collision(player, boss);
}