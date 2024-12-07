#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "../backend/enemies.h"
#include "../backend/gun.h"
#include "../backend/player.h"
#include "../backend/resourcesManager.h"
#include "../backend/special.h"
#include "../includes/backend/boss.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

// void render_background(ALLEGRO_BITMAP *background, float bg_x);
void render_background(Resources_Manager *r, int state);

void render_menu();

void render_gameover();

void draw_player(Player *_player, Resources_Manager *_resources);

void draw_enemies(Enemy *enemies, int spawned);

void draw_enemies_shots(Enemy *enemies, int spawned);

void draw_shots(Gun *_gun, int isPlayer);

void draw_boss(Boss *boss);

void draw_special(Special *sp);

#endif  // __GRAPHICS__