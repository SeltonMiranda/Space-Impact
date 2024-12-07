#include "../../includes/frontend/graphics.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "../../includes/backend/boss.h"
#include "../../includes/config/config.h"

// void render_background(ALLEGRO_BITMAP *background, float bg_x) {
//   al_clear_to_color(al_map_rgb(0, 0, 0));
//   al_draw_bitmap(background, bg_x, 0, 0);
//   al_draw_bitmap(background, bg_x + SCREEN_WIDTH, 0, 0);
// }

void render_background(Resources_Manager *r, int state) {
  al_clear_to_color(al_map_rgb(0, 0, 0));
  switch (state) {
    case 1:
      al_draw_bitmap(r->background.bg_one, r->background.x, 0, 0);
      al_draw_bitmap(r->background.bg_one, r->background.x + SCREEN_WIDTH, 0,
                     0);
      break;
  }
}

void render_menu() {
  al_clear_to_color(al_map_rgb(0, 0, 0));  // Fundo preto

  // Exibir o texto no centro da tela
  ALLEGRO_FONT *font = al_create_builtin_font();
  char *text = "Pressione Enter para começcar o jogo ou Q para sair";
  if (font) {
    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, text);
    al_destroy_font(font);
  }

  al_flip_display();  // Atualiza a tela
}

void render_gameover() {
  al_clear_to_color(al_map_rgb(0, 0, 0));  // Tela preta

  // Exibir mensagem "Game Over"
  ALLEGRO_FONT *font = al_create_builtin_font();
  char *text =
      "GAME OVER\nPressione Enter para recomeçcar o jogo ou Q para sair";
  if (font) {
    al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2,
                 SCREEN_HEIGHT / 2 - 20, ALLEGRO_ALIGN_CENTRE, text);
  }

  al_flip_display();  // Atualizar a tela
}

void draw_player(Player *_player, Resources_Manager *_resources) {
  // if (_player->health <= 0) return;

  if (_player->respawn_timer) return;

  if (((_player->invincible_timer / 2) % 3) == 1) return;

  if (_player->_state == MOVEMENT) {
    int frame = (_player->current_frame / 15) % 12 + 1;
    al_draw_bitmap(_resources->player.sprites[frame], _player->x, _player->y,
                   0);
  }

  al_draw_bitmap(_resources->player.sprites[0], _player->x, _player->y, 0);
}

void draw_enemies(Enemy *enemies, int spawned) {
  ALLEGRO_COLOR color;
  switch (enemies[0]._type) {
    case ENEMY_1:
      color = al_map_rgb(255, 0, 0);
      break;
    case ENEMY_2:
      color = al_map_rgb(0, 0, 255);
      break;
    case ENEMY_3:
      color = al_map_rgb(255, 0, 0);
      break;
    case ENEMY_4:
      color = al_map_rgb(0, 0, 255);
      break;
  }

  for (int i = 0; i < spawned; i++) {
    if (enemies[i].isAlive) {
      al_draw_filled_rectangle(enemies[i].x, enemies[i].y,
                               enemies[i].x + ENEMY_WIDTH,
                               enemies[i].y + ENEMY_HEIGHT, color);
    }
  }
}

void draw_shots(Gun *_gun, int isPlayer) {
  for (int i = 0; i < MAX_SHOTS; i++) {
    if (_gun->shots[i].is_fired == 1) {
      if (isPlayer)
        al_draw_filled_circle(_gun->shots[i].x, _gun->shots[i].y, 20,
                              al_map_rgb(0, 255, 0));
      else
        al_draw_filled_circle(_gun->shots[i].x, _gun->shots[i].y, 20,
                              al_map_rgb(0, 255, 255));
    }
  }
}

void draw_enemies_shots(Enemy *enemies, int spawned) {
  for (int i = 0; i < spawned; i++) {
    draw_shots(enemies[i]._gun, ISENEMY);
  }
}

void draw_boss(Boss *boss) {
  if (boss->state == BOSS_STATE_NOT_SPAWNED || boss->state == BOSS_STATE_DEAD)
    return;
  al_draw_filled_rectangle(boss->x, boss->y, boss->x + BOSS_WIDTH,
                           boss->y + BOSS_HEIGHT, al_map_rgb(255, 150, 250));
}

void draw_special(Special *sp) {
  if (!sp->on_map) return;

  switch (sp->type) {
    case SPECIAL_GUN_ONE:
      al_draw_filled_circle(sp->x, sp->y, 10, al_map_rgb(255, 131, 25));
      break;

    case SPECIAL_GUN_TWO:
      al_draw_filled_circle(sp->x, sp->y, 10, al_map_rgb(156, 255, 133));
      break;
  }
}