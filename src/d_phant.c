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
