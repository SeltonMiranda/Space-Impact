#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "graphics.h"
#include "player.h"

#define BACKGROUND_IMAGE "assets/background/background_#1.jpg"

#define BACKGROUND_SPEED 2

// Valores em pixels
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

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
  //ALLEGRO_BITMAP *player_sprites[1];
  //player_sprites[0] = al_load_bitmap("assets/player/player_base.png");

  Player *player = create_player();
  Resources_Manager *resources = create_resources();
  
  while (1) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
      case ALLEGRO_EVENT_TIMER:
        bg_x -= BACKGROUND_SPEED;
        if (bg_x <= -width) {
          bg_x = 0;
        }
        update_player(player);
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
      draw_player(player, resources);
      //al_draw_bitmap(player_sprites[0], player->x, player->y, 0);
      draw_shots(player->_gun);
      al_flip_display();
      redraw = false;
    }
  }

  destroy_player(player);

  // ALLEGRO
  al_destroy_font(font);
  al_destroy_bitmap(background);
  al_destroy_bitmap(buffer);
  //al_destroy_bitmap(player_sprites[0]);
  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  return 0;
}