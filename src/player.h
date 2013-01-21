/* Make sure GshmupEntity is defined first. */
#include "entity.h"

#ifndef GSHMUP_PLAYER_H
#define GSHMUP_PLAYER_H

#include "common.h"
#include "sprite.h"
#include "game.h"

enum {
    GSHMUP_PLAYER_UP,
    GSHMUP_PLAYER_DOWN,
    GSHMUP_PLAYER_LEFT,
    GSHMUP_PLAYER_RIGHT,
};

typedef struct {
    _GSHMUP_ENTITY_HEADER
    GshmupSprite sprite;
    bool shooting;
    bool dir[4]; /* 4 directional movement. */
    float speed;
    int lives;
    int credits;
    int score;
} GshmupPlayer;

GshmupEntity *gshmup_create_player (GshmupAnimation *anim);
void gshmup_draw_player (GshmupPlayer *player);
void gshmup_update_player (GshmupPlayer *player);
void gshmup_player_set_direction (GshmupPlayer *player, int dir, bool flag);

#endif
