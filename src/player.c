#include "player.h"

static GshmupPlayer *current_player = NULL;
SCM_VARIABLE_INIT (s_lives_per_credit, "lives-per-credit", scm_from_int (3));
SCM_VARIABLE_INIT (s_num_credits, "num-credits", scm_from_int (3));
SCM_VARIABLE_INIT (s_player_speed, "player-speed", scm_from_double (6));

GshmupPlayer *
gshmup_create_player (GshmupAnimation *anim)
{
    GshmupPlayer *player = (GshmupPlayer *) scm_gc_malloc (sizeof (GshmupPlayer),
                                                           "player");

    player->entity.position = gshmup_create_vector2 (0, 0);
    player->entity.agenda = gshmup_create_agenda ();
    player->shooting = false;
    player->lives = scm_to_int (scm_variable_ref (s_lives_per_credit));
    player->credits = scm_to_int (scm_variable_ref (s_num_credits));
    player->speed = scm_to_double (scm_variable_ref (s_player_speed));
    player->score = 0;
    gshmup_init_animated_sprite (&player->entity.sprite, anim);
    gshmup_play_animation (anim);

    for (int i = 0; i < 4; ++i) {
        player->dir[i] = false;
    }

    return player;
}

void
gshmup_destroy_player (GshmupPlayer *player)
{
    scm_gc_free (player, sizeof (GshmupPlayer), "player");
}

void
gshmup_draw_player (GshmupPlayer *player)
{
    player->entity.sprite.position = player->entity.position;
    gshmup_draw_sprite (&player->entity.sprite);
}

void
gshmup_update_player (GshmupPlayer *player)
{
    GshmupVector2 v;

    gshmup_update_animation (player->entity.sprite.anim);
    /* Transform movement flags into a direction vector. */
    v.x = player->dir[GSHMUP_PLAYER_RIGHT] - player->dir[GSHMUP_PLAYER_LEFT];
    v.y = player->dir[GSHMUP_PLAYER_DOWN] - player->dir[GSHMUP_PLAYER_UP];
    /* Calculate new position. */
    v = gshmup_vector2_norm (v);
    v = gshmup_vector2_scale (v, player->speed);
    v = gshmup_vector2_add (v, player->entity.position);
    /* Clamp position within screen bounds. */
    v.x = gshmup_clamp (v.x, 0, GAME_WIDTH);
    v.y = gshmup_clamp (v.y, 0, GAME_HEIGHT);
    player->entity.position = v;

    gshmup_update_agenda (player->entity.agenda);
}

void
gshmup_player_set_direction (GshmupPlayer *player, int dir, bool flag)
{
    player->dir[dir] = flag;
}

void
gshmup_set_current_player (GshmupPlayer *player)
{
    current_player = player;
}

void
gshmup_player_init_scm (void)
{
#include "player.x"

    scm_c_export ("lives-per-credit",
                  "num-credits",
                  "player-speed",
                  NULL);
}
