#ifndef __PLAYER__
#define __PLAYER__

#include "gun.h";
#include "joystick.h"

typedef struct Player {
    float x, y; // Posicao do jogador
    Joystick _joystick; // Movimentacao do jogador
    Gun _gun; // Arma do jogador
    int health; // Vida do jogador
} Player;


#endif // __PLAYER__