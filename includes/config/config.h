#ifndef __CONFIGURATION__
#define __CONFIGURATION__

// ------------- GENERAL ----------------
#define BACKGROUND_LEVEL_ONE "assets/background/background_#1.jpg"
#define BACKGROUND_LEVEL_TWO "assets/background/background_#2.jpeg"
#define BACKGROUND_COMMON "assets/background/background_common.jpg"
#define BACKGROUND_SPEED 0.75
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

#define ISPLAYER 1
#define ISENEMY 0

// ------------- Enemies ----------------
#define ENEMY_ONE_SPRITE "assets/enemies/enemy_one/enemy_one.png"
#define ENEMY_TWO_SPRITE "assets/enemies/enemy_two/enemy_two.png"

#define ENEMY_WIDTH 64
#define ENEMY_HEIGHT 64

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
#define SPECIAL_ITEM_SPEED 1.0f
// ------------- PLAYER ----------------

// ------------- SHOT ----------------
#define NORMAL_SHOT_SPRITE "assets/shot/normal_shot.png"
#define ENEMY_SHOT_SPRITE "assets/shot/enemy_shot.png"

#define ENEMY_SHOT_WIDTH 72
#define ENEMY_SHOT_HEIGHT 27
#define SHOT_WIDTH 64
#define SHOT_HEIGHT 64
#define SHOT_COOLDOWN 10
#define MAX_SHOTS 256
#define SHOT_SPEED 3
// ------------- SHOT ----------------

// ------------- BOSS ----------------
#define BOSS_WIDTH 100
#define BOSS_HEIGHT 100
#define BOSS_SPEED 2.5f
#define BOSS_TIME_SPAWN 10
#define BOSS_LIFE 100
#define DOWN 1
#define UP -1
// ------------- BOSS ----------------

#endif  // __CONFIGURATION__