#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "../../includes/backend/enemies.h"
#include "../../includes/backend/player.h"
#include "../../includes/backend/spawnControl.h"
#include "../../includes/frontend/graphics.h"

// Configs
#include "../../includes/config/config.h"

int main() {
  al_init();
  al_install_keyboard();
  al_init_primitives_addon();
  al_init_image_addon();
  al_init_font_addon();

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
  ALLEGRO_FONT *font = al_create_builtin_font();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  al_start_timer(timer);
  ALLEGRO_EVENT event;
  bool redraw = true;
  bool done = false;

  /********************************************************/
  ALLEGRO_BITMAP *background = NULL;
  ALLEGRO_BITMAP *buffer = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

  background = al_load_bitmap(BACKGROUND_IMAGE);
  int width = al_get_bitmap_width(background);
  float bg_x = 0;
  /********************************************************/

  Player *player = create_player();
  Boss *boss = create_boss();
  Resources_Manager *resources = create_resources();
  SpawnControl *_SpawnControlEnemy1 = create_spawn_control(ENEMY_1, 200);
  SpawnControl *_SpawnControlEnemy2 = create_spawn_control(ENEMY_2, 100);

  while (1) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
      case ALLEGRO_EVENT_TIMER:
        bg_x -= BACKGROUND_SPEED;
        if (bg_x <= -width) {
          bg_x = 0;
        }
        update_spawn_control(_SpawnControlEnemy1);
        update_spawn_control(_SpawnControlEnemy2);
        update_enemies(_SpawnControlEnemy1->enemies,
                       _SpawnControlEnemy1->spawned);
        update_enemies(_SpawnControlEnemy2->enemies,
                       _SpawnControlEnemy2->spawned);

        update_boss(boss);
        update_player(player);

        if (boss_should_spawn(boss)) spawn_boss(boss);
        break;

      case ALLEGRO_EVENT_KEY_DOWN:
      case ALLEGRO_EVENT_KEY_UP:
        if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
          done = true;
          break;
        }
        update_joystick(player->_joystick, &event);
        break;

      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
    }

    redraw = true;
    if (done) break;

    if (redraw && al_is_event_queue_empty(queue)) {
      render_background(background, buffer, bg_x);
      draw_enemies(_SpawnControlEnemy1->enemies, _SpawnControlEnemy1->spawned);
      draw_enemies(_SpawnControlEnemy2->enemies, _SpawnControlEnemy2->spawned);

      draw_enemies_shots(_SpawnControlEnemy1->enemies,
                         _SpawnControlEnemy1->spawned);
      draw_enemies_shots(_SpawnControlEnemy2->enemies,
                         _SpawnControlEnemy2->spawned);
      draw_shots(player->_gun, ISPLAYER);
      draw_boss(boss);
      draw_player(player, resources);
      al_flip_display();
      redraw = false;
    }
  }

  destroy_boss(boss);
  destroy_spawn_control(_SpawnControlEnemy1);
  destroy_spawn_control(_SpawnControlEnemy2);
  destroy_player(player);
  destroy_resources(resources);
  // ALLEGRO
  al_destroy_font(font);
  al_destroy_bitmap(background);
  al_destroy_bitmap(buffer);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}