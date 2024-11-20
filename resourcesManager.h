#ifndef __RESOURCES_MANAGER__
#define __RESOURCES_MANAGER__

#include <allegro5/allegro5.h>

typedef enum {
    IDLE = 0,
    MOVE,
    

} Player_Sprite;

typedef struct Resources_Manager {
    ALLEGRO_BITMAP *player_sprites[];
} Resources_Manager;

#endif // __RESOURCES_MANAGER__