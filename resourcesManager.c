#include "resourcesManager.h"

#include <allegro5/allegro_image.h>
#include <stdlib.h>

#define PLAYER_IDLE 0

Resources_Manager *create_resources() {
  Resources_Manager *r = (Resources_Manager *)malloc(sizeof(Resources_Manager));
	if (r == NULL)
		return NULL;
	load_player_sprites(r);
	return r;
}

void load_player_sprites(Resources_Manager *rm) {
	rm->player.sprites[PLAYER_IDLE] = al_load_bitmap("assets/player/player_base.png");

	rm->player.engine = al_load_bitmap("assets/player/player_engine.png");
	for (int i = 0; i < 12; i++) {
		rm->player.sprites[i + 1] = al_create_sub_bitmap(rm->player.engine, 0, i * 128, 128, 128);
	}

	//al_destroy_bitmap(_sprites);
}

void destroy_resources(Resources_Manager *_resources) {
	free(_resources->player.sprites[PLAYER_IDLE]);
	free(_resources->player.engine);

	free(_resources);
}