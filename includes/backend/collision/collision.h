#ifndef __COLISION__
#define __COLISION__

#include "../boss.h"
#include "../enemies.h"
#include "../player.h"

void check_all_collisions(Player *player, Enemy *enemies1, int spawned_enemies1,
                          Enemy *enemies2, int spawned_enemies2, Boss *boss);

void check_player_shots(Gun *gun, Enemy *enemies1, int spawned1,
                        Enemy *enemies2, int spawned2);

void check_special_item_collision(Player *player);

void check_enemy_shots(Enemy *enemies1, int spawned1, Enemy *enemies2,
                       int spawned2, Player *player);

void check_player_enemy_collision(Player *player, Enemy *enemies1,
                                  int spawned_enemies1, Enemy *enemies2,
                                  int spawned_enemies2);

void check_boss_collision(Player *player, Boss *boss);
#endif  // __COLISION__