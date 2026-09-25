#include "data.h"
#include <stdlib.h>

// ---------------------------------------------------------------------------
// phantom - cloaks (invisible and unhittable, as blank cells don't make it
// into the damage map), teleports, flickers back into existence, drifts
// towards the player firing aimed sparks, then fades away again
// ---------------------------------------------------------------------------

#define PHANTOM_ST_CLOAKED              0
#define PHANTOM_ST_EMERGE               1
#define PHANTOM_ST_VISIBLE              2
#define PHANTOM_ST_FADE                 3

#define PHANTOM_SPARK_SPEED             10

// ---------------------------------------------------------------------------
// images
// ---------------------------------------------------------------------------

static const sPhysical phy_phantom = {
    { 5, 3 },
    {
        '\0',   0x00,   '/',    0x03,   '~',    0x0b,   '\\',   0x03,   '\0',   0x00,
        '(',    0x03,   '<',    0x0b,   '@',    0x0d,   '>',    0x0b,   ')',    0x03,
        '\0',   0x00,   '~',    0x03,   'v',    0x0b,   '~',    0x03,   '\0',   0x00
    }
};
static const sPhysical phy_phantom_hit = {
    { 5, 3 },
    {
        '\0',   0x00,   '/',    0x0f,   '~',    0x0f,   '\\',   0x0f,   '\0',   0x00,
        '(',    0x0f,   '<',    0x0f,   '@',    0x0d,   '>',    0x0f,   ')',    0x0f,
        '\0',   0x00,   '~',    0x0f,   'v',    0x0f,   '~',    0x0f,   '\0',   0x00
    }
};
static const sPhysical phy_phantom_shimmer = {
    { 5, 3 },
    {
        '\0',   0x00,   '.',    0x08,   '\0',   0x00,   '.',    0x08,   '\0',   0x00,
        ':',    0x08,   '\0',   0x00,   '@',    0x05,   '\0',   0x00,   ':',    0x08,
        '\0',   0x00,   '.',    0x08,   '\0',   0x00,   '.',    0x08,   '\0',   0x00
    }
};
static const sPhysical phy_phantom_cloaked = {
    { 5, 3 },
    { '\0' }
};
static const sPhysical phy_phantom_dying = {
    { 5, 3 },
    {
        '\0',   0x00,   '.',    0x08,   '*',    0x08,   '.',    0x08,   '\0',   0x00,
        '*',    0x08,   '\0',   0x00,   '*',    0x05,   '\0',   0x00,   '*',    0x08,
        '\0',   0x00,   '.',    0x08,   '\0',   0x00,   '.',    0x08,   '\0',   0x00
    }
};

static const sPhysical phy_phantom_spark = PHYSICAL_1X1('o', 0x0d);

// ---------------------------------------------------------------------------
// object types
// ---------------------------------------------------------------------------

static const sObjType ot_phantom_spark = {
    &phy_phantom_spark,
    OBJTYPE_NAT_FOE_BULLET,
    6,
    NULL,
    NULL,
    NULL,
    cb_deal_die
};

static const sTurret turret_phantom_eye = TURRET_GRID(2, 3, 0, PHANTOM_SPARK_SPEED, &ot_phantom_spark);

// fire spark aimed at the player's current position, "spread" is added to
// the aimed horizontal speed (for fans of sparks around the aimed one)
static void phantom_aim(hsObject obj, hcsTurret turret, int spread) {

    hsObject spark;
    int dx, dy;

    if ((spark = fire_turret(obj, turret)) == NULL)
        return;

    dx = (int)world2grid(player->pos.x) + player->physical->dim.x / 2 - (int)world2grid(spark->pos.x);
    dy = (int)world2grid(player->pos.y) - (int)world2grid(spark->pos.y);
    if (dy < 1)
        dy = 1;

    spark->speed.x = adjust(dx * PHANTOM_SPARK_SPEED / dy + spread, -PHANTOM_SPARK_SPEED, PHANTOM_SPARK_SPEED);
}

static void phantom_behave(hsObject obj) {

    int dx;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    if (obj->state[0] == PHANTOM_ST_CLOAKED) {

        obj->physical = &phy_phantom_cloaked;

        // reappear somewhere random in the upper part of the view
        if (obj->ttl == 0) {

            obj->pos.x      = grid2world(rand() % (VIEWGRID_WIDTH - obj->physical->dim.x));
            obj->pos.y      = grid2world(2 + rand() % 20);
            obj->speed.x    = 0;
            obj->speed.y    = 0;
            obj->state[0]   = PHANTOM_ST_EMERGE;
            obj->ttl        = 10;
        }
    }
    else
    if (obj->state[0] == PHANTOM_ST_EMERGE) {

        obj->physical = (obj->ttl & 2) ? &phy_phantom_shimmer : &phy_phantom_cloaked;

        if (obj->ttl == 0) {

            obj->state[0]   = PHANTOM_ST_VISIBLE;
            obj->ttl        = 40;
        }
    }
    else
    if (obj->state[0] == PHANTOM_ST_VISIBLE) {

        obj->physical = &phy_phantom;

        // slowly drift above the player
        dx = (int)world2grid(player->pos.x) + player->physical->dim.x / 2 - ((int)world2grid(obj->pos.x) + obj->physical->dim.x / 2);
        obj->speed.x = (dx > 0) ? 3 : ((dx < 0) ? -3 : 0);

        if (obj->ttl == 30 || obj->ttl == 20 || obj->ttl == 10)
            phantom_aim(obj, &turret_phantom_eye, 0);

        if (obj->ttl == 0) {

            obj->speed.x    = 0;
            obj->state[0]   = PHANTOM_ST_FADE;
            obj->ttl        = 8;
        }
    }
    else
    if (obj->state[0] == PHANTOM_ST_FADE) {

        obj->physical = (obj->ttl & 2) ? &phy_phantom_shimmer : &phy_phantom;

        if (obj->ttl == 0) {

            obj->state[0]   = PHANTOM_ST_CLOAKED;
            obj->ttl        = 16 + rand() % 24;
        }
    }

    // don't draw the blank frames, they would wipe out bullets flying through
    if (obj->physical == &phy_phantom_cloaked)
        obj->flags |= OBJ_FLG_HIDDEN;
    else
        obj->flags &= ~OBJ_FLG_HIDDEN;
}

static void phantom_die(hsObject obj) {

    obj->physical = &phy_phantom_dying;
    obj->speed.x = 0;
    obj->ttl = 4;
}

static void phantom_hit(hsObject obj) {

    obj->physical = &phy_phantom_hit;
}

// starts cloaked, so the emit position doesn't matter - it teleports
// somewhere random on it's first tick
const sObjType ot_phantom = {
    &phy_phantom_cloaked,
    OBJTYPE_NAT_FOE_OBJ,
    14,
    phantom_behave,
    phantom_die,
    phantom_hit,
    NULL
};

// ---------------------------------------------------------------------------
// mirage - phantom which never comes alone, every time it emerges it brings
// two illusions spread across the view; illusions are neutral (bullets fly
// right through them) and never fire, so the only way to tell the real one
// is to watch who shoots, or who flashes when hit; when the mirage dies, it's
// illusions shatter with it
// ---------------------------------------------------------------------------

static const sPhysical phy_mirage = {
    { 5, 3 },
    {
        '\0',   0x00,   '/',    0x02,   '=',    0x0a,   '\\',   0x02,   '\0',   0x00,
        '{',    0x02,   '(',    0x0a,   '@',    0x0d,   ')',    0x0a,   '}',    0x02,
        '\0',   0x00,   '~',    0x02,   'w',    0x0a,   '~',    0x02,   '\0',   0x00
    }
};
static const sPhysical phy_mirage_hit = {
    { 5, 3 },
    {
        '\0',   0x00,   '/',    0x0f,   '=',    0x0f,   '\\',   0x0f,   '\0',   0x00,
        '{',    0x0f,   '(',    0x0f,   '@',    0x0d,   ')',    0x0f,   '}',    0x0f,
        '\0',   0x00,   '~',    0x0f,   'w',    0x0f,   '~',    0x0f,   '\0',   0x00
    }
};

static const sTurret turret_mirage_eye = TURRET_GRID(2, 3, 0, PHANTOM_SPARK_SPEED, &ot_phantom_spark);

// id shared by mirage and it's illusions, so it shatters just it's own ones
static unsigned char mirage_next_id;

static void mirage_appear(hsObject obj);

// the same cycle for both the mirage and it's illusions, just the real one
// fires and cloaks again, while illusions vanish after fading out
static void mirage_cycle(hsObject obj, unsigned char real) {

    if (obj->flags & OBJ_FLG_DYING)
        return;

    if (obj->state[0] == PHANTOM_ST_CLOAKED) {

        obj->physical = &phy_phantom_cloaked;

        if (obj->ttl == 0)
            mirage_appear(obj);
    }
    else
    if (obj->state[0] == PHANTOM_ST_EMERGE) {

        obj->physical = (obj->ttl & 2) ? &phy_phantom_shimmer : &phy_phantom_cloaked;

        if (obj->ttl == 0) {

            obj->state[0]   = PHANTOM_ST_VISIBLE;
            obj->ttl        = 64;
        }
    }
    else
    if (obj->state[0] == PHANTOM_ST_VISIBLE) {

        obj->physical = &phy_mirage;

        if (real && (obj->ttl == 56 || obj->ttl == 40 || obj->ttl == 24))
            phantom_aim(obj, &turret_mirage_eye, 0);

        if (obj->ttl == 0) {

            obj->state[0]   = PHANTOM_ST_FADE;
            obj->ttl        = 8;
        }
    }
    else
    if (obj->state[0] == PHANTOM_ST_FADE) {

        obj->physical = (obj->ttl & 2) ? &phy_phantom_shimmer : &phy_mirage;

        if (obj->ttl == 0) {

            if (real) {

                obj->state[0]   = PHANTOM_ST_CLOAKED;
                obj->ttl        = 16 + rand() % 24;
            }
            else
                obj->flags |= OBJ_FLG_DESTROY;
        }
    }

    // don't draw the blank frames, they would wipe out bullets flying through
    if (obj->physical == &phy_phantom_cloaked)
        obj->flags |= OBJ_FLG_HIDDEN;
    else
        obj->flags &= ~OBJ_FLG_HIDDEN;
}

static void mirage_behave(hsObject obj) {

    mirage_cycle(obj, 1);
}

static void mirage_illusion_behave(hsObject obj) {

    mirage_cycle(obj, 0);
}

static const sObjType ot_mirage_illusion = {
    &phy_phantom_cloaked,
    OBJTYPE_NAT_NEUTRAL,
    1,
    mirage_illusion_behave,
    NULL,
    NULL,
    NULL
};

// emerge in one of three thirds of the view, illusions take the other two
static void mirage_appear(hsObject obj) {

    hsObject emit;
    unsigned char real, i;

    if (obj->state[1] == 0) {

        if (++mirage_next_id == 0)
            mirage_next_id = 1;

        obj->state[1] = mirage_next_id;
    }

    real = rand() % 3;

    for (i = 0; i < 3; i++) {

        if (i == real) {

            emit = obj;
            emit->ttl = 10;
        }
        else {

            // added inactive, so it misses this frame's tick countdown
            // just like the mirage itself does and both flicker in sync
            if ((emit = objpool_alloc_flags(&ot_mirage_illusion, OBJ_FLG_INACTIVE | OBJ_FLG_HIDDEN)) == NULL)
                continue;

            emit->ttl       = 9;
            emit->state[1]  = obj->state[1];
        }

        emit->pos.x     = grid2world(i * (VIEWGRID_WIDTH / 3) + rand() % (VIEWGRID_WIDTH / 3 - obj->physical->dim.x));
        emit->pos.y     = grid2world(2 + rand() % 20);
        emit->speed.x   = 0;
        emit->speed.y   = 0;
        emit->state[0]  = PHANTOM_ST_EMERGE;
    }
}

static void mirage_die(hsObject obj) {

    hsObject illusion;

    obj->physical = &phy_phantom_dying;
    obj->ttl = 4;

    // shatter own illusions
    illusion = NULL;
    while ((illusion = objpool_next(illusion)) != NULL) {

        if (illusion->type != &ot_mirage_illusion || illusion->state[1] != obj->state[1] || (illusion->flags & OBJ_FLG_DYING))
            continue;

        illusion->flags     |= OBJ_FLG_DYING;
        illusion->flags     &= ~OBJ_FLG_HIDDEN;
        illusion->physical  = &phy_phantom_dying;
        illusion->ttl       = 4;
    }
}

static void mirage_hit(hsObject obj) {

    obj->physical = &phy_mirage_hit;
}

// starts cloaked, it's first tick places it and summons the illusions
const sObjType ot_mirage = {
    &phy_phantom_cloaked,
    OBJTYPE_NAT_FOE_OBJ,
    12,
    mirage_behave,
    mirage_die,
    mirage_hit,
    NULL
};
