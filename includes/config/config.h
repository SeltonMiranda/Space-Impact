#ifndef __CONFIGURATION__
#define __CONFIGURATION__

// ------------- GENERAL ----------------
#define BACKGROUND_IMAGE "assets/background/background_#1.jpg"
#define BACKGROUND_SPEED 0.75
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

#define ISPLAYER 1
#define ISENEMY 0

// ------------- Enemies ----------------
#define ENEMY_WIDTH 30
#define ENEMY_HEIGHT 30
#define DEAD 0
#define ALIVE 1
#define ENEMY_PADDING 50

#define BATCH 5

// ----- shot timer
#define MIN_TIME 100
#define MAX_TIME 600
// ------------- Enemies ----------------

// ------------- PLAYER ----------------
#define PLAYER_SPEED 5.0
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define PLAYER_PADDING 15
#define SPATTACK_TIME 5
// ------------- PLAYER ----------------

// ------------- SHOT ----------------
#define SHOT_COOLDOWN 10
#define MAX_SHOTS 256
#define SHOT_SPEED 3
// ------------- SHOT ----------------

// ------------- BOSS ----------------
#define BOSS_WIDTH 100
#define BOSS_HEIGHT 100
#define BOSS_SPEED 2.5f
#define BOSS_TIME_SPAWN 10
#define DOWN 1
#define UP -1
// ------------- BOSS ----------------

#endif  // __CONFIGURATION__