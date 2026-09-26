#include "data.h"
#include <stdlib.h>

// ---------------------------------------------------------------------------
// images
// ---------------------------------------------------------------------------

static const sPhysical phy_grchkrx_bee = {
    { 5, 2 },
    {
        '/',    0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x04,
        '\\',   0x04,   '|',    0x04,   '!',    0x09,   '|',    0x04,   '/',    0x04
    }
};
static const sPhysical phy_grchkrx_bee_hit = {
    { 5, 2 },
    {
        '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,
        '\\',   0x0c,   '|',    0x0c,   '!',    0x09,   '|',    0x0c,   '/',    0x0c
    }
};
static const sPhysical phy_grchkrx_bee_dying = {
    { 5, 2 },
    {
        '\0',   0x07,   'o',    0x08,   'o',    0x08,   'o',    0x08,   '\0',   0x07,
        '\0',   0x08,   '|',    0x08,   ' ',    0x07,   '|',    0x08,   '\0',   0x08
    }
};

static const sTurret turret_grchkrx_bee = TURRET_GRID(1, 2, 0, 8, &ot_foe_bullet);

// larva wriggles while crawling, then settles into a trembling pupa and just
// before hatching flashes the bee's wings (it's top row)
static const sPhysical phy_grchkrx_larva_0 = {
    { 5, 1 },
    {
        '~',    0x06,   'o',    0x0e,   'O',    0x0e,   'o',    0x0e,   '-',    0x06
    }
};
static const sPhysical phy_grchkrx_larva_1 = {
    { 5, 1 },
    {
        '-',    0x06,   'o',    0x0e,   'O',    0x0e,   'o',    0x0e,   '~',    0x06
    }
};
static const sPhysical phy_grchkrx_larva_hit = {
    { 5, 1 },
    {
        '~',    0x0c,   'o',    0x0c,   'O',    0x0c,   'o',    0x0c,   '~',    0x0c
    }
};
static const sPhysical phy_grchkrx_larva_dying = {
    { 5, 1 },
    {
        '\0',   0x07,   '.',    0x08,   'o',    0x08,   '.',    0x08,   '\0',   0x07
    }
};
static const sPhysical phy_grchkrx_pupa_0 = {
    { 5, 1 },
    {
        '(',    0x06,   'O',    0x0e,   'o',    0x0e,   'o',    0x0e,   ')',    0x06
    }
};
static const sPhysical phy_grchkrx_pupa_1 = {
    { 5, 1 },
    {
        '{',    0x06,   'o',    0x06,   'o',    0x0e,   'O',    0x06,   '}',    0x06
    }
};
static const sPhysical phy_grchkrx_pupa_wings = {
    { 5, 1 },
    {
        '/',    0x0c,   'o',    0x06,   'O',    0x06,   'o',    0x06,   '\\',   0x0c
    }
};

// stinger - small fast bee flapping while it hovers, flashing when it locks
// on and folding it's wings for the dive
static const sPhysical phy_grchkrx_stinger_0 = {
    { 3, 2 },
    {
        '\\',   0x04,   'V',    0x06,   '/',    0x04,
        '\0',   0x00,   '!',    0x09,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_stinger_1 = {
    { 3, 2 },
    {
        '/',    0x04,   'V',    0x06,   '\\',   0x04,
        '\0',   0x00,   '!',    0x09,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_stinger_aim = {
    { 3, 2 },
    {
        '\\',   0x0c,   'V',    0x0e,   '/',    0x0c,
        '\0',   0x00,   '!',    0x0f,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_stinger_dive = {
    { 3, 2 },
    {
        '|',    0x04,   'V',    0x06,   '|',    0x04,
        '\0',   0x00,   'v',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_stinger_hit = {
    { 3, 2 },
    {
        '\\',   0x0c,   'V',    0x0c,   '/',    0x0c,
        '\0',   0x00,   '!',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_stinger_dying = {
    { 3, 2 },
    {
        '.',    0x08,   'v',    0x08,   '.',    0x08,
        '\0',   0x00,   ' ',    0x07,   '\0',   0x00
    }
};

static const sTurret turret_grchkrx_sting = TURRET_GRID(1, 2, 0, 16, &ot_foe_laser);

// wax builder - a bee with a wax gland instead of a stinger, squeezing the
// gland (sparkling) while repairing
static const sPhysical phy_grchkrx_builder = {
    { 5, 2 },
    {
        '/',    0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x04,
        '[',    0x04,   '=',    0x06,   '#',    0x0e,   '=',    0x06,   ']',    0x04
    }
};
static const sPhysical phy_grchkrx_builder_hit = {
    { 5, 2 },
    {
        '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,
        '[',    0x0c,   '=',    0x0c,   '#',    0x0e,   '=',    0x0c,   ']',    0x0c
    }
};
static const sPhysical phy_grchkrx_builder_repair_0 = {
    { 5, 2 },
    {
        '/',    0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x04,
        '[',    0x04,   '*',    0x0e,   '#',    0x0f,   '.',    0x06,   ']',    0x04
    }
};
static const sPhysical phy_grchkrx_builder_repair_1 = {
    { 5, 2 },
    {
        '\\',   0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '/',    0x04,
        '[',    0x04,   '.',    0x06,   '#',    0x0e,   '*',    0x0e,   ']',    0x04
    }
};
static const sPhysical phy_grchkrx_builder_dying = {
    { 5, 2 },
    {
        '\0',   0x07,   'o',    0x08,   'o',    0x08,   'o',    0x08,   '\0',   0x07,
        '\0',   0x08,   '=',    0x08,   '.',    0x06,   '=',    0x08,   '\0',   0x08
    }
};

// wax plate - a strip of honeycomb, honey (shaded) filling it's cells; it
// crumbles in three stages as it takes damage, flashing white when hit
static const sPhysical phy_grchkrx_wax_0 = {
    { 7, 2 },
    {
        '/',    0x0e,   '\xb0', 0x06,   '\\',   0x0e,   '_',    0x0e,   '/',    0x0e,   '\xb0', 0x06,   '\\',   0x0e,
        '\\',   0x0e,   '_',    0x0e,   '/',    0x0e,   '\xb0', 0x06,   '\\',   0x0e,   '_',    0x0e,   '/',    0x0e
    }
};
static const sPhysical phy_grchkrx_wax_0_hit = {
    { 7, 2 },
    {
        '/',    0x0f,   '\xb0', 0x0f,   '\\',   0x0f,   '_',    0x0f,   '/',    0x0f,   '\xb0', 0x0f,   '\\',   0x0f,
        '\\',   0x0f,   '_',    0x0f,   '/',    0x0f,   '\xb0', 0x0f,   '\\',   0x0f,   '_',    0x0f,   '/',    0x0f
    }
};
static const sPhysical phy_grchkrx_wax_1 = {
    { 7, 2 },
    {
        '/',    0x0e,   '\xb0', 0x06,   '\\',   0x06,   '_',    0x0e,   ',',    0x06,   '.',    0x06,   '\\',   0x0e,
        '\\',   0x06,   '_',    0x0e,   '/',    0x0e,   '\xb0', 0x06,   '.',    0x06,   '_',    0x06,   '/',    0x0e
    }
};
static const sPhysical phy_grchkrx_wax_1_hit = {
    { 7, 2 },
    {
        '/',    0x0f,   '\xb0', 0x0f,   '\\',   0x0f,   '_',    0x0f,   ',',    0x0f,   '.',    0x0f,   '\\',   0x0f,
        '\\',   0x0f,   '_',    0x0f,   '/',    0x0f,   '\xb0', 0x0f,   '.',    0x0f,   '_',    0x0f,   '/',    0x0f
    }
};
static const sPhysical phy_grchkrx_wax_2 = {
    { 7, 2 },
    {
        '/',    0x06,   '.',    0x08,   '\'',   0x06,   '_',    0x08,   ',',    0x08,   '.',    0x08,   '\\',   0x06,
        '\'',   0x08,   '_',    0x06,   '.',    0x08,   ':',    0x06,   '.',    0x08,   ',',    0x08,   '/',    0x06
    }
};
static const sPhysical phy_grchkrx_wax_2_hit = {
    { 7, 2 },
    {
        '/',    0x0f,   '.',    0x0f,   '\'',   0x0f,   '_',    0x0f,   ',',    0x0f,   '.',    0x0f,   '\\',   0x0f,
        '\'',   0x0f,   '_',    0x0f,   '.',    0x0f,   ':',    0x0f,   '.',    0x0f,   ',',    0x0f,   '/',    0x0f
    }
};
static const sPhysical phy_grchkrx_wax_dying = {
    { 7, 2 },
    {
        '.',    0x08,   '\0',   0x07,   '\'',   0x08,   '\0',   0x07,   ',',    0x08,   '\0',   0x07,   '.',    0x08,
        '\0',   0x07,   ',',    0x08,   '\0',   0x07,   '.',    0x08,   '\0',   0x07,   '\'',   0x08,   '\0',   0x07
    }
};

// plate appearance by damage stage, normal and hit
static const hcsPhysical phy_grchkrx_wax_stages[3][2] = {
    { &phy_grchkrx_wax_0, &phy_grchkrx_wax_0_hit },
    { &phy_grchkrx_wax_1, &phy_grchkrx_wax_1_hit },
    { &phy_grchkrx_wax_2, &phy_grchkrx_wax_2_hit },
};

static const sPhysical phy_grchkrx_queen = {
    { 8, 4 },
    {
        '\0',   0x00,   '/',    0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x04,   '\0',   0x00,
        '#',    0x04,   ' ',    0x04,   ' ',    0x04,   '_',    0x04,   '_',    0x04,   ' ',    0x04,   ' ',    0x04,   '#',    0x04, 
        '|',    0x04,   ' ',    0x04,   '|',    0x04,   '!',    0x09,   '!',    0x09,   '|',    0x04,   ' ',    0x04,   '|',    0x04, 
        '\0',   0x00,   '\\',   0x04,   '|',    0x04,   '\0',   0x09,   '\0',   0x09,   '|',    0x04,   '/',    0x04,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_queen_hit = {
    { 8, 4 },
    {
        '\0',   0x00,   '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,   '\0',   0x00,
        '#',    0x0c,   ' ',    0x0c,   ' ',    0x0c,   '_',    0x0c,   '_',    0x0c,   ' ',    0x0c,   ' ',    0x0c,   '#',    0x0c, 
        '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   '!',    0x09,   '!',    0x09,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c, 
        '\0',   0x00,   '\\',   0x0c,   '|',    0x0c,   '\0',   0x09,   '\0',   0x09,   '|',    0x0c,   '/',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_queen_dying = {
    { 8, 4 },
    {
        '\0',   0x00,   '/',    0x08,   '*',    0x08,   '*',    0x08,   '*',    0x08,   '*',    0x08,   '\\',   0x08,   '\0',   0x00,
        '#',    0x08,   ' ',    0x08,   ' ',    0x08,   '_',    0x08,   '_',    0x08,   ' ',    0x08,   ' ',    0x08,   '#',    0x08, 
        '|',    0x08,   ' ',    0x08,   '|',    0x08,   ':',    0x09,   ':',    0x09,   '|',    0x08,   ' ',    0x08,   '|',    0x08, 
        '\0',   0x00,   '\\',   0x08,   '|',    0x08,   '\0',   0x09,   '\0',   0x09,   '|',    0x08,   '/',    0x08,   '\0',   0x00
    }
};

static const sTurret turret_grchkrx_queen_0 = TURRET_GRID(3, 3, -1, 10, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_1 = TURRET_GRID(4, 3, +1, 10, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_2 = TURRET_GRID(3, 3, -2, 9, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_3 = TURRET_GRID(4, 3, +2, 9, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_4 = TURRET_GRID(3, 3, -3, 8, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_5 = TURRET_GRID(4, 3, +3, 8, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_6 = TURRET_GRID(3, 3, -4, 7, &ot_foe_ball);
static const sTurret turret_grchkrx_queen_7 = TURRET_GRID(4, 3, +4, 7, &ot_foe_ball);

// ---------------------------------------------------------------------------
// object types
// ---------------------------------------------------------------------------

void cb_bee_behave(hsObject obj) {

    if (obj->flags & OBJ_FLG_DYING)
        return;

    obj->physical = &phy_grchkrx_bee;

    if (obj->pos.x == grid2world(0) && obj->speed.x < 0)
        obj->speed.x = 6;
    else
    if (obj->pos.x >= grid2world(VIEWGRID_WIDTH - obj->physical->dim.x) && obj->speed.x > 0)
        obj->speed.x = -6;
    else
    if (obj->speed.x == 0)
        obj->speed.x = 6;

    obj->speed.y = 2 - (rand() % 5);
        
    if (obj->ttl == 0) {

        obj->ttl = (rand() & 3) + 20;
        fire_turret(obj, &turret_grchkrx_bee);
    }
}

void cb_bee_die(hsObject obj) {

    obj->physical = &phy_grchkrx_bee_dying;
    obj->ttl = 3;
}

void cb_bee_hit(hsObject obj) {

    obj->physical = &phy_grchkrx_bee_hit;
}

// larva lifetime in behaviour ticks (16/sec) - crawls, then pupates standing
// still for LARVA_PUPA_TICKS and flashes wings for the last LARVA_WINGS_TICKS
#define LARVA_HATCH_TICKS               160
#define LARVA_PUPA_TICKS                40
#define LARVA_WINGS_TICKS               12

void cb_larva_behave(hsObject obj) {

    hsObject bee;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    // first tick - start the hatching countdown and pick a crawling direction
    if (obj->state[0] == 0) {

        obj->state[0] = 1;
        obj->ttl = LARVA_HATCH_TICKS;
        obj->speed.x = (rand() & 1) ? 2 : -2;
        obj->speed.y = 1;
    }

    // hatch into a bee, one row up so it keeps the larva's bottom
    if (obj->ttl == 0) {

        if ((bee = objpool_alloc_inactive(&ot_grchkrx_bee)) == NULL)
            return;

        bee->pos.x = obj->pos.x;
        bee->pos.y = obj->pos.y > grid2world(1) ? obj->pos.y - grid2world(1) : 0;
        bee->ttl = 12;
        obj->flags |= OBJ_FLG_DESTROY;
        return;
    }

    // pupa - still, trembling and finally showing wings
    if (obj->ttl <= LARVA_PUPA_TICKS) {

        obj->speed.x = 0;
        obj->speed.y = 0;

        if (obj->ttl <= LARVA_WINGS_TICKS)
            obj->physical = (obj->ttl & 2) ? &phy_grchkrx_pupa_wings : &phy_grchkrx_pupa_0;
        else
            obj->physical = (obj->ttl & 2) ? &phy_grchkrx_pupa_1 : &phy_grchkrx_pupa_0;

        return;
    }

    obj->physical = (obj->ttl & 4) ? &phy_grchkrx_larva_1 : &phy_grchkrx_larva_0;

    // slow wandering, bouncing off the view's edges
    if (OBJ_IS_LEFT(obj) && obj->speed.x < 0)
        obj->speed.x = 2;
    else
    if (OBJ_IS_RIGHT(obj) && obj->speed.x > 0)
        obj->speed.x = -2;
    else
    if ((rand() & 31) == 0)
        obj->speed.x = -obj->speed.x;

    if (obj->pos.y == 0 && obj->speed.y < 0)
        obj->speed.y = 1;
    else
    if (obj->pos.y >= grid2world(VIEWGRID_HEIGHT - 9) && obj->speed.y > 0)
        obj->speed.y = -1;
    else
    if ((rand() & 15) == 0)
        obj->speed.y = 1 - (rand() % 3);
}

void cb_larva_die(hsObject obj) {

    obj->physical = &phy_grchkrx_larva_dying;
    obj->ttl = 3;
}

void cb_larva_hit(hsObject obj) {

    obj->physical = &phy_grchkrx_larva_hit;
}

// wax builder patrols side to side, lazily bobbing up to BUILDER_BOB rows
// around it's home row, laying BUILDER_PLATES plates below the lowest bob;
// passing over a damaged plate (up to BUILDER_REACH rows below) it stops
// and mends WAX_REPAIR_HP every WAX_REPAIR_PERIOD ticks until it's whole
#define BUILDER_SPEED                   3
#define BUILDER_BOB                     1
#define BUILDER_PLATES                  3
#define BUILDER_REACH                   4
#define BUILDER_LAY_COOLDOWN            24

// plates are sturdy, but melt WAX_MELT_HP every second once no builder is left
#define WAX_HP                          48
#define WAX_REPAIR_HP                   2
#define WAX_REPAIR_PERIOD               4       // power of 2
#define WAX_MELT_HP                     4

#define WAX_IS_LIVE(p)                  ((p)->type == &ot_grchkrx_wax && !((p)->flags & (OBJ_FLG_DYING | OBJ_FLG_DESTROY)))

static unsigned char builder_alive(void) {

    hsObject obj = NULL;

    while ((obj = objpool_next(obj)) != NULL)
        if (obj->type == &ot_grchkrx_builder && !(obj->flags & OBJ_FLG_DYING))
            return 1;

    return 0;
}

// damaged plate right below the builder's middle, if any
static hsObject builder_find_damaged(hsObject obj) {

    hsObject wax = NULL;
    int bx, by, px, py;

    bx = world2grid(obj->pos.x) + obj->physical->dim.x / 2;
    by = world2grid(obj->pos.y) + obj->physical->dim.y;

    while ((wax = objpool_next(wax)) != NULL) {

        if (!WAX_IS_LIVE(wax) || wax->damage_total == 0)
            continue;

        px = world2grid(wax->pos.x);
        py = world2grid(wax->pos.y);

        if (bx >= px && bx < px + phy_grchkrx_wax_0.dim.x && py >= by && py <= by + BUILDER_REACH)
            return wax;
    }

    return NULL;
}

// home row is kept in state[0] off by one, zero means not initialized yet
#define BUILDER_HOME(obj)               ((obj)->state[0] - 1)

// lay a plate centered under the builder's home, unless it'd touch another plate
static unsigned char builder_lay(hsObject obj) {

    hsObject wax = NULL;
    int x, y, w, h, px, py;

    w = phy_grchkrx_wax_0.dim.x;
    h = phy_grchkrx_wax_0.dim.y;
    x = adjust(world2grid(obj->pos.x) + obj->physical->dim.x / 2 - w / 2, 0, VIEWGRID_WIDTH - w);
    y = BUILDER_HOME(obj) + obj->physical->dim.y + BUILDER_BOB;

    // too low, would get clamped up into the builder
    if (y > VIEWGRID_HEIGHT - 9)
        return 0;

    while ((wax = objpool_next(wax)) != NULL) {

        if (!WAX_IS_LIVE(wax))
            continue;

        px = world2grid(wax->pos.x);
        py = world2grid(wax->pos.y);

        // keep a column of gap between plates
        if (px < x + w + 1 && x < px + w + 1 && py < y + h && y < py + h)
            return 0;
    }

    // added inactive, as it's spawned from within the objects' tick loop
    if ((wax = objpool_alloc_inactive(&ot_grchkrx_wax)) == NULL)
        return 0;

    wax->pos.x = grid2world(x);
    wax->pos.y = grid2world(y);
    return 1;
}

void cb_builder_behave(hsObject obj) {

    hsObject wax;
    int home;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    // first tick - remember home, load the plates and head away from the nearer side
    if (obj->state[0] == 0) {

        obj->state[0] = world2grid(obj->pos.y) + 1;
        obj->state[1] = BUILDER_PLATES;
        obj->state[2] = obj->pos.x < grid2world(VIEWGRID_WIDTH / 2) ? 1 : -1;
        obj->ttl = BUILDER_LAY_COOLDOWN / 2;
    }

    // hold still over the damaged plate and mend it
    if ((wax = builder_find_damaged(obj)) != NULL) {

        obj->speed.x = 0;
        obj->speed.y = 0;
        obj->state[3]++;
        obj->physical = (obj->state[3] & 2) ? &phy_grchkrx_builder_repair_1 : &phy_grchkrx_builder_repair_0;

        if ((obj->state[3] & (WAX_REPAIR_PERIOD - 1)) == 0)
            wax->damage_total = wax->damage_total > WAX_REPAIR_HP ? wax->damage_total - WAX_REPAIR_HP : 0;

        return;
    }

    obj->physical = &phy_grchkrx_builder;

    if (OBJ_IS_LEFT(obj) && obj->state[2] < 0)
        obj->state[2] = 1;
    else
    if (OBJ_IS_RIGHT(obj) && obj->state[2] > 0)
        obj->state[2] = -1;

    obj->speed.x = obj->state[2] * BUILDER_SPEED;

    // now and then drift a bit up or down, never straying far from home
    home = grid2world(BUILDER_HOME(obj));
    if ((int)obj->pos.y <= home - grid2world(BUILDER_BOB))
        obj->speed.y = 1;
    else
    if ((int)obj->pos.y >= home + grid2world(BUILDER_BOB))
        obj->speed.y = -1;
    else
    if ((rand() & 31) == 0)
        obj->speed.y = 1 - (rand() % 3);

    if (obj->state[1] > 0 && obj->ttl == 0 && builder_lay(obj)) {

        obj->state[1]--;
        obj->ttl = BUILDER_LAY_COOLDOWN + (rand() & 15);
    }
}

void cb_builder_die(hsObject obj) {

    obj->physical = &phy_grchkrx_builder_dying;
    obj->ttl = 3;
}

void cb_builder_hit(hsObject obj) {

    obj->physical = &phy_grchkrx_builder_hit;
}

// 0 - whole, 1 - cracked, 2 - crumbling
static unsigned char wax_stage(hsObject obj) {

    return obj->damage_total >= WAX_HP ? 2 : obj->damage_total * 3 / WAX_HP;
}

void cb_wax_behave(hsObject obj) {

    if (obj->flags & OBJ_FLG_DYING)
        return;

    obj->physical = phy_grchkrx_wax_stages[wax_stage(obj)][0];

    // once a second check for builders, nobody's tending the orphaned plate
    if (obj->ttl == 0) {

        obj->ttl = 16;
        if (!builder_alive())
            obj->damage_total += WAX_MELT_HP;
    }
}

void cb_wax_die(hsObject obj) {

    obj->physical = &phy_grchkrx_wax_dying;
    obj->ttl = 3;
}

void cb_wax_hit(hsObject obj) {

    obj->physical = phy_grchkrx_wax_stages[wax_stage(obj)][1];
}

// stinger hovers at it's home row trailing the player, after a while locks
// on the player's column and flashes, dives straight down, stings with a
// burst of lasers from right above the player and climbs back home
#define STINGER_ST_HOVER                1
#define STINGER_ST_AIM                  2
#define STINGER_ST_DIVE                 3
#define STINGER_ST_STING                4
#define STINGER_ST_RETURN               5

#define STINGER_TRACK_SPEED             4
#define STINGER_HOVER_TICKS             24      // plus up to 31 random
#define STINGER_AIM_TICKS               8
#define STINGER_DIVE_SPEED              14
#define STINGER_STING_TICKS             6       // laser on every odd tick
#define STINGER_RETURN_SPEED            6

void cb_stinger_behave(hsObject obj) {

    int dx;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    switch (obj->state[0]) {

        // first tick - remember home row
        case 0:

            obj->state[0] = STINGER_ST_HOVER;
            obj->state[1] = world2grid(obj->pos.y);
            obj->ttl = STINGER_HOVER_TICKS + (rand() & 31);
            break;

        // lag after the player, lock on once rested and roughly above the player
        case STINGER_ST_HOVER:

            obj->physical = (obj->ttl & 2) ? &phy_grchkrx_stinger_1 : &phy_grchkrx_stinger_0;
            obj->speed.y = 0;

            dx = 0;
            if (player != NULL)
                dx = ((int)player->pos.x + grid2world(player->physical->dim.x) / 2) - ((int)obj->pos.x + grid2world(obj->physical->dim.x) / 2);

            if (obj->ttl == 0 && abs(dx) < grid2world(1)) {

                obj->state[0] = STINGER_ST_AIM;
                obj->ttl = STINGER_AIM_TICKS;
                obj->speed.x = 0;
            }
            else
                obj->speed.x = adjust(dx / 4, -STINGER_TRACK_SPEED, STINGER_TRACK_SPEED);
            break;

        // column locked, flash the warning
        case STINGER_ST_AIM:

            obj->physical = (obj->ttl & 1) ? &phy_grchkrx_stinger_aim : &phy_grchkrx_stinger_0;

            if (obj->ttl == 0) {

                obj->state[0] = STINGER_ST_DIVE;
                obj->speed.y = STINGER_DIVE_SPEED;
            }
            break;

        // down until stopped by the monsters' floor
        case STINGER_ST_DIVE:

            obj->physical = &phy_grchkrx_stinger_dive;

            if (obj->pos.y >= grid2world(VIEWGRID_HEIGHT - 9)) {

                obj->state[0] = STINGER_ST_STING;
                obj->ttl = STINGER_STING_TICKS;
                obj->speed.y = 0;
            }
            break;

        case STINGER_ST_STING:

            obj->physical = &phy_grchkrx_stinger_dive;

            if (obj->ttl & 1)
                fire_turret(obj, &turret_grchkrx_sting);

            if (obj->ttl == 0) {

                obj->state[0] = STINGER_ST_RETURN;
                obj->speed.y = -STINGER_RETURN_SPEED;
            }
            break;

        case STINGER_ST_RETURN:

            obj->physical = (obj->pos.y & 32) ? &phy_grchkrx_stinger_1 : &phy_grchkrx_stinger_0;

            if (obj->pos.y <= grid2world(obj->state[1])) {

                obj->pos.y = grid2world(obj->state[1]);
                obj->speed.y = 0;
                obj->state[0] = STINGER_ST_HOVER;
                obj->ttl = STINGER_HOVER_TICKS + (rand() & 31);
            }
            break;
    }
}

void cb_stinger_die(hsObject obj) {

    obj->physical = &phy_grchkrx_stinger_dying;
    obj->ttl = 3;
}

void cb_stinger_hit(hsObject obj) {

    obj->physical = &phy_grchkrx_stinger_hit;
}

void cb_queen_behave(hsObject obj) {

    obj->speed.y = adjust(obj->speed.y + 1 - (rand() % 3), -3, 3);
    obj->speed.x = adjust(obj->speed.x + 3 - (rand() % 7), -5, 5);

    if (world2grid(obj->pos.y) > 10)
        obj->speed.y = -2;
    
    if (!(obj->flags & OBJ_FLG_DYING)) {
    
        obj->physical = &phy_grchkrx_queen;

        if (obj->ttl == 0) {

            obj->ttl = 50;
        }
        else
        if (obj->ttl == 16) {

            fire_turret(obj, &turret_grchkrx_queen_0);
            fire_turret(obj, &turret_grchkrx_queen_1);
        }
        else
        if (obj->ttl == 12) {

            fire_turret(obj, &turret_grchkrx_queen_2);
            fire_turret(obj, &turret_grchkrx_queen_3);
        }
        else
        if (obj->ttl == 8) {

            fire_turret(obj, &turret_grchkrx_queen_4);
            fire_turret(obj, &turret_grchkrx_queen_5);
        }
        else
        if (obj->ttl == 4) {

            fire_turret(obj, &turret_grchkrx_queen_6);
            fire_turret(obj, &turret_grchkrx_queen_7);
        }
    }
}

void cb_queen_die(hsObject obj) {

    obj->physical = &phy_grchkrx_queen_dying;
    obj->ttl = 7;
}

void cb_queen_hit(hsObject obj) {

    obj->physical = &phy_grchkrx_queen_hit;
}

const sObjType ot_grchkrx_bee = {
    &phy_grchkrx_bee,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    10,
    cb_bee_behave,
    cb_bee_die,
    cb_bee_hit,
    NULL
};

const sObjType ot_grchkrx_larva = {
    &phy_grchkrx_larva_0,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    6,
    cb_larva_behave,
    cb_larva_die,
    cb_larva_hit,
    NULL
};

const sObjType ot_grchkrx_builder = {
    &phy_grchkrx_builder,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    16,
    cb_builder_behave,
    cb_builder_die,
    cb_builder_hit,
    NULL
};

const sObjType ot_grchkrx_wax = {
    &phy_grchkrx_wax_0,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NOWAIT,
    WAX_HP,
    cb_wax_behave,
    cb_wax_die,
    cb_wax_hit,
    NULL
};

const sObjType ot_grchkrx_stinger = {
    &phy_grchkrx_stinger_0,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    12,
    cb_stinger_behave,
    cb_stinger_die,
    cb_stinger_hit,
    NULL
};

const sObjType ot_grchkrx_queen = {
    &phy_grchkrx_queen,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_HPBAR,
    50,
    cb_queen_behave,
    cb_queen_die,
    cb_queen_hit,
    NULL
};
