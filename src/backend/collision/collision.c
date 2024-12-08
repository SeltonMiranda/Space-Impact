#include "../../../includes/backend/collision/collision.h"

#include <stdio.h>

static int collide(float ax1, float ay1, float ax2, float ay2, float bx1,
                   float by1, float bx2, float by2) {
  if (ax1 > bx2)
    return 0;
  if (ax2 < bx1)
    return 0;
  if (ay1 > by2)
    return 0;
  if (ay2 < by1)
    return 0;

  return 1;
}

static void acquireSpecial(Player *player) {
  player->special_attack->is_active = 1;
  player->special_attack->on_map = 0;
  player->special_attack->burst_time = time(NULL);
}

void check_special_item_collision(Player *player) {
  if (player->special_attack->on_map &&
      collide(player->x, player->y, player->x + PLAYER_WIDTH / 2,
              player->y + PLAYER_HEIGHT / 2, player->special_attack->x,
              player->special_attack->y, player->special_attack->x + 10,
              player->special_attack->y + 10)) {
    acquireSpecial(player);
  }
}

static void handleShotToEnemyCollision(Shot *shot, Enemy *enemy) {
  enemy->life--;
  shot->is_fired = 0;
  if (enemy->life <= 0)
    enemy->isAlive = DEAD;
}

void check_player_shots(Gun *gun, Enemy *enemies1, int spawned1,
                        Enemy *enemies2, int spawned2) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (gun->shots[i].is_fired) {
      for (int j = 0; j < spawned1; j++) {
        if (enemies1[j].isAlive &&
            collide(gun->shots[i].x, gun->shots[i].y,
                    gun->shots[i].x + SHOT_WIDTH / 2,
                    gun->shots[i].y + SHOT_HEIGHT / 2, enemies1[j].x,
                    enemies1[j].y, enemies1[j].x + ENEMY_WIDTH / 2,
                    enemies1[j].y + ENEMY_HEIGHT / 2)) {
          handleShotToEnemyCollision(&gun->shots[i], &enemies1[j]);
        }
      }
    }
  }

  for (int i = 0; i < MAX_SHOTS; i++) {
    if (gun->shots[i].is_fired) {
      for (int j = 0; j < spawned2; j++) {
        if (enemies2[j].isAlive &&
            collide(gun->shots[i].x, gun->shots[i].y,
                    gun->shots[i].x + SHOT_WIDTH / 2,
                    gun->shots[i].y + SHOT_HEIGHT / 2, enemies2[j].x,
                    enemies2[j].y, enemies2[j].x + ENEMY_WIDTH / 2,
                    enemies2[j].y + ENEMY_HEIGHT / 2)) {
          handleShotToEnemyCollision(&gun->shots[i], &enemies2[j]);
        }
      }
    }
  }
}

static void handleSpecialShotToEnemyCollision(Shot *shot, Enemy *enemy,
                                              SPECIAL_TYPE type) {
  if (type == SPECIAL_GUN_ONE) {
    enemy->life -= 4;
  } else {
    enemy->life -= 8;
  }
  shot->is_fired = 0;
  if (enemy->life <= 0)
    enemy->isAlive = DEAD;
}

void check_player_special_shots(Special *sp, Enemy *enemies1, int spawned1,
                                Enemy *enemies2, int spawned2) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (sp->gun->shots[i].is_fired) {
      for (int j = 0; j < spawned1; j++) {
        if (enemies1[j].isAlive &&
            collide(sp->gun->shots[i].x, sp->gun->shots[i].y,
                    sp->gun->shots[i].x + SHOT_WIDTH / 2,
                    sp->gun->shots[i].y + SHOT_HEIGHT / 2, enemies1[j].x,
                    enemies1[j].y, enemies1[j].x + ENEMY_WIDTH / 2,
                    enemies1[j].y + ENEMY_HEIGHT / 2)) {
          handleSpecialShotToEnemyCollision(&sp->gun->shots[i], &enemies1[j],
                                            sp->type);
        }
      }
    }
  }

  for (int i = 0; i < MAX_SHOTS; i++) {
    if (sp->gun->shots[i].is_fired) {
      for (int j = 0; j < spawned2; j++) {
        if (enemies2[j].isAlive &&
            collide(sp->gun->shots[i].x, sp->gun->shots[i].y,
                    sp->gun->shots[i].x + SHOT_WIDTH / 2,
                    sp->gun->shots[i].y + SHOT_HEIGHT / 2, enemies2[j].x,
                    enemies2[j].y, enemies2[j].x + ENEMY_WIDTH / 2,
                    enemies2[j].y + ENEMY_HEIGHT / 2)) {
          handleSpecialShotToEnemyCollision(&sp->gun->shots[i], &enemies2[j],
                                            sp->type);
        }
      }
    }
  }
}

static void handleShotToPlayerCollision(Shot *shot, Player *player) {
  player->health--;
  player->invincible_timer = 180;
  player->respawn_timer = 90;
  shot->is_fired = 0;
}

void check_enemy_shots(Enemy *enemies1, int spawned1, Enemy *enemies2,
                       int spawned2, Player *player) {
  for (int i = 0; i < spawned1; i++) {
    for (int j = 0; j < MAX_SHOTS; j++) {
      if (enemies1[i]._gun->shots[j].is_fired &&
          collide(player->x, player->y, player->x + PLAYER_WIDTH / 2,
                  player->y + PLAYER_HEIGHT / 2, enemies1[i]._gun->shots[j].x,
                  enemies1[i]._gun->shots[j].y,
                  enemies1[i]._gun->shots[j].x + ENEMY_SHOT_WIDTH / 4,
                  enemies1[i]._gun->shots[j].y + ENEMY_SHOT_HEIGHT / 4)) {
        handleShotToPlayerCollision(&enemies1[i]._gun->shots[j], player);
      }
    }
  }

  for (int i = 0; i < spawned2; i++) {
    for (int j = 0; j < MAX_SHOTS; j++) {
      if (enemies2[i]._gun->shots[j].is_fired &&
          collide(player->x, player->y, player->x + PLAYER_WIDTH / 2,
                  player->y + PLAYER_HEIGHT / 2, enemies2[i]._gun->shots[j].x,
                  enemies2[i]._gun->shots[j].y,
                  enemies2[i]._gun->shots[j].x + ENEMY_SHOT_WIDTH / 4,
                  enemies2[i]._gun->shots[j].y + ENEMY_SHOT_HEIGHT / 4)) {
        handleShotToPlayerCollision(&enemies2[i]._gun->shots[j], player);
      }
    }
  }
}

void check_player_enemy_collision(Player *player, Enemy *enemies1,
                                  int spawned_enemies1, Enemy *enemies2,
                                  int spawned_enemies2) {
  int damaged = 0;  // Evita mútiplas colisões
  for (int i = 0; i < spawned_enemies1; i++) {
    if (enemies1[i].isAlive &&
        collide(player->x, player->y, player->x + PLAYER_WIDTH / 2,
                player->y + PLAYER_HEIGHT / 2, enemies1[i].x, enemies1[i].y,
                enemies1[i].x + ENEMY_WIDTH / 2,
                enemies1[i].y + ENEMY_HEIGHT / 2)) {
      damaged = 1;
      enemies1[i].life--;
      if (enemies1[i].life == 0)
        enemies1[i].isAlive = DEAD;
    }
  }

  if (!damaged) {
    for (int i = 0; i < spawned_enemies2; i++) {
      if (!damaged && enemies2[i].isAlive &&
          collide(player->x, player->y, player->x + PLAYER_WIDTH / 2,
                  player->y + PLAYER_HEIGHT / 2, enemies2[i].x, enemies2[i].y,
                  enemies2[i].x + ENEMY_WIDTH / 2,
                  enemies2[i].y + ENEMY_HEIGHT / 2)) {
        damaged = 1;
        enemies2[i].life--;
        if (enemies2[i].life == 0)
          enemies2[i].isAlive = DEAD;
      }
    }
  }

  if (damaged) {
    player->health--;
    player->respawn_timer = 90;
    player->invincible_timer = 180;
  }
}

void check_boss_collision(Player *player, Boss *boss) {
  int damaged = 0;

  // Colisao entre jogador e Boss
  if (boss->spawned &&
      collide(player->x, player->y, player->x + PLAYER_WIDTH / 2,
              player->y + PLAYER_HEIGHT / 2, boss->x, boss->y,
              boss->x + BOSS_WIDTH / 2, boss->y + BOSS_HEIGHT / 2)) {
    player->health = 0;
  }

  // Colisao dos disparos do jogador ao Boss
  Gun *g = player->_gun;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (g->shots[i].is_fired &&
        collide(g->shots[i].x, g->shots[i].y, g->shots[i].x + 40 / 2,
                g->shots[i].y + 40 / 2, boss->x, boss->y,
                boss->x + BOSS_WIDTH / 2, boss->y + BOSS_HEIGHT / 2)) {
      boss->life--;
      g->shots[i].is_fired = 0;
      if (boss->life <= 0)
        boss->state = BOSS_STATE_DEAD;
    }
  }

  Gun *sg = player->special_attack->gun;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (sg->shots[i].is_fired &&
        collide(sg->shots[i].x, sg->shots[i].y, sg->shots[i].x + 40,
                sg->shots[i].y + 40, boss->x, boss->y, boss->x + BOSS_WIDTH,
                boss->y + BOSS_HEIGHT)) {
      boss->life -= player->special_attack->damage;
      sg->shots[i].is_fired = 0;
      if (boss->life <= 0)
        boss->state = BOSS_STATE_DEAD;
    }
  }
  // Colisao entre disparos do boss no jogador
  Weapon *w = boss->weapon;
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (w->shots[i].is_fired &&
        collide(w->shots[i].x, w->shots[i].y, w->shots[i].x + w->width / 2,
                w->shots[i].y + w->height / 2, player->x, player->y,
                player->x + PLAYER_WIDTH / 2, player->y + PLAYER_HEIGHT / 2)) {
      damaged = 1;
      break;
    }
  }

  if (damaged) {
    player->health -= boss->weapon->damage;
    player->respawn_timer = 90;
    player->invincible_timer = 180;
    printf("life: %d\n", player->health);
  }
}

void check_all_collisions(Player *player, Level *l) {
  if (player->invincible_timer > 0) {
    player->invincible_timer--;
  } else {
    check_player_enemy_collision(player, l->sp1->enemies, l->sp1->spawned,
                                 l->sp2->enemies, l->sp2->spawned);
    check_boss_collision(player, l->boss);

    // disparos dos inimigos no jogador
    check_enemy_shots(l->sp1->enemies, l->sp1->spawned, l->sp2->enemies,
                      l->sp2->spawned, player);
  }
  check_special_item_collision(player);

  // disparos do jogador no inimigo
  check_player_shots(player->_gun, l->sp1->enemies, l->sp1->spawned,
                     l->sp2->enemies, l->sp2->spawned);

  check_player_special_shots(player->special_attack, l->sp1->enemies,
                             l->sp1->spawned, l->sp2->enemies, l->sp2->spawned);
}