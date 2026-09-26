#include "data.h"
#include <stdlib.h>

// ---------------------------------------------------------------------------
// mitosis family - living cells, which divide instead of dying: a blob
// splits into two smaller blobs (big -> medium -> small, only the small ones
// really die); a fuser splits the same way, but it's halves crawl back to
// each other and fuse into the bigger (and fully healed) cell again, unless
// shot first; the mother cell is the boss, budding new cells off whenever
// it gets wounded and bursting into a last handful of blobs when killed
// ---------------------------------------------------------------------------

#define CELL_CEILING                    1       // cells bounce between these rows
#define CELL_FLOOR                      30
#define CELL_SPLIT_TICKS                4       // pinching animation before the split
#define CELL_POP_TICKS                  3       // small cell bursting animation
#define CELL_SPLIT_COOLDOWN             40      // split halves fly apart before seeking each other
#define CELL_FUSE_COOLDOWN              16      // freshly fused cell shows up before seeking again
#define CELL_GOO_SPEED                  5       // slow, so the drops pile up on the screen

// ---------------------------------------------------------------------------
// images
// ---------------------------------------------------------------------------

// l, r - side walls; m - membrane color; c - cytoplasm color; n - nucleus color
#define PHY_CELL_BIG(l, r, m, c, n) { { 7, 3 }, {                                                               \
    '\0',   0x00,   '/',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '\\',   (m),    '\0',   0x00,   \
    (l),    (m),    '\xb0', (c),    '\xb0', (c),    'O',    (n),    '\xb0', (c),    '\xb0', (c),    (r),    (m),    \
    '\0',   0x00,   '\\',   (m),    '~',    (m),    '~',    (m),    '~',    (m),    '/',    (m),    '\0',   0x00    \
} }

// big cell pinched in two halves, just before the split
#define PHY_CELL_BIG_SPLIT(l, r, m, n) { { 7, 3 }, {                                                            \
    '/',    (m),    '~',    (m),    '\\',   (m),    '\0',   0x00,   '/',    (m),    '~',    (m),    '\\',   (m),    \
    (l),    (m),    'O',    (n),    (r),    (m),    '\0',   0x00,   (l),    (m),    'O',    (n),    (r),    (m),    \
    '\\',   (m),    '~',    (m),    '/',    (m),    '\0',   0x00,   '\\',   (m),    '~',    (m),    '/',    (m)     \
} }

#define PHY_CELL_MEDIUM(l, r, m, c, n) { { 5, 2 }, {                                    \
    (l),    (m),    '\xb0', (c),    'O',    (n),    '\xb0', (c),    (r),    (m),        \
    '\\',   (m),    '~',    (m),    '~',    (m),    '~',    (m),    '/',    (m)         \
} }

#define PHY_CELL_MEDIUM_SPLIT(l, r, m, n) { { 5, 2 }, {                                 \
    (l),    (m),    'o',    (n),    '|',    (m),    'o',    (n),    (r),    (m),        \
    '\\',   (m),    '~',    (m),    '|',    (m),    '~',    (m),    '/',    (m)         \
} }

#define PHY_CELL_SMALL(l, r, m, n)  { { 3, 1 }, { (l), (m), 'o', (n), (r), (m) } }
#define PHY_CELL_POP(m, n)          { { 3, 1 }, { '.', (m), '*', (n), '.', (m) } }

static const sPhysical phy_blob_big             = PHY_CELL_BIG('(', ')', 0x0c, 0x04, 0x0e);
static const sPhysical phy_blob_big_hit         = PHY_CELL_BIG('(', ')', 0x0f, 0x0f, 0x0e);
static const sPhysical phy_blob_big_split       = PHY_CELL_BIG_SPLIT('(', ')', 0x0c, 0x0e);
static const sPhysical phy_blob_medium          = PHY_CELL_MEDIUM('(', ')', 0x0c, 0x04, 0x0e);
static const sPhysical phy_blob_medium_hit      = PHY_CELL_MEDIUM('(', ')', 0x0f, 0x0f, 0x0e);
static const sPhysical phy_blob_medium_split    = PHY_CELL_MEDIUM_SPLIT('(', ')', 0x0c, 0x0e);
static const sPhysical phy_blob_small           = PHY_CELL_SMALL('(', ')', 0x0c, 0x0e);
static const sPhysical phy_blob_small_hit       = PHY_CELL_SMALL('(', ')', 0x0f, 0x0e);
static const sPhysical phy_blob_small_pop       = PHY_CELL_POP(0x04, 0x0c);

static const sPhysical phy_fuser_big            = PHY_CELL_BIG('{', '}', 0x0a, 0x02, 0x0e);
static const sPhysical phy_fuser_big_hit        = PHY_CELL_BIG('{', '}', 0x0f, 0x0f, 0x0e);
static const sPhysical phy_fuser_big_split      = PHY_CELL_BIG_SPLIT('{', '}', 0x0a, 0x0e);
static const sPhysical phy_fuser_medium         = PHY_CELL_MEDIUM('{', '}', 0x0a, 0x02, 0x0e);
static const sPhysical phy_fuser_medium_hit     = PHY_CELL_MEDIUM('{', '}', 0x0f, 0x0f, 0x0e);
static const sPhysical phy_fuser_medium_split   = PHY_CELL_MEDIUM_SPLIT('{', '}', 0x0a, 0x0e);
static const sPhysical phy_fuser_small          = PHY_CELL_SMALL('{', '}', 0x0a, 0x0e);
static const sPhysical phy_fuser_small_hit      = PHY_CELL_SMALL('{', '}', 0x0f, 0x0e);
static const sPhysical phy_fuser_small_pop      = PHY_CELL_POP(0x02, 0x0a);

static const sPhysical phy_cell_goo             = PHYSICAL_1X1('\x07', 0x0e);

// ---------------------------------------------------------------------------
// object types
// ---------------------------------------------------------------------------

static const sObjType ot_cell_goo = {
    &phy_cell_goo,
    OBJTYPE_NAT_FOE_BULLET,
    OBJTYPE_FLG_NONE,
    6,
    NULL,
    NULL,
    NULL,
    cb_deal_die
};

static const sTurret turret_cell_big_0      = TURRET_GRID(1, 3, 0, CELL_GOO_SPEED, &ot_cell_goo);
static const sTurret turret_cell_big_1      = TURRET_GRID(5, 3, 0, CELL_GOO_SPEED, &ot_cell_goo);
static const sTurret turret_cell_medium     = TURRET_GRID(2, 2, 0, CELL_GOO_SPEED, &ot_cell_goo);
static const sTurret turret_cell_small      = TURRET_GRID(1, 1, 0, CELL_GOO_SPEED, &ot_cell_goo);

// fire goo drop, falling a bit faster or slower than the turret says, so
// the drops spread out instead of raining in neat rows
static void cell_goo(hsObject obj, hcsTurret turret) {

    hsObject goo;

    if ((goo = fire_turret(obj, turret)) != NULL)
        goo->speed.y += rand() % 3 - 1;
}

// all the cells share the callbacks, the differences are in the stage table
static void cell_behave(hsObject obj);
static void cell_die(hsObject obj);
static void cell_hit(hsObject obj);

const sObjType ot_blob = {
    &phy_blob_big,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    24,
    cell_behave,
    cell_die,
    cell_hit,
    NULL
};

static const sObjType ot_blob_medium = {
    &phy_blob_medium,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    12,
    cell_behave,
    cell_die,
    cell_hit,
    NULL
};

const sObjType ot_blob_small = {
    &phy_blob_small,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    6,
    cell_behave,
    cell_die,
    cell_hit,
    NULL
};

const sObjType ot_fuser = {
    &phy_fuser_big,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    30,
    cell_behave,
    cell_die,
    cell_hit,
    NULL
};

static const sObjType ot_fuser_medium = {
    &phy_fuser_medium,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    18,
    cell_behave,
    cell_die,
    cell_hit,
    NULL
};

const sObjType ot_fuser_small = {
    &phy_fuser_small,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    6,
    cell_behave,
    cell_die,
    cell_hit,
    NULL
};

// ---------------------------------------------------------------------------
// cell stages
// ---------------------------------------------------------------------------

typedef struct sCellStage {

    hcsObjType              type;
    hcsObjType              child;          // splits into two of these when killed (NULL - just pops)
    hcsObjType              fused;          // two of these touching fuse into one (NULL - never fuses)
    hcsPhysical             phy;
    hcsPhysical             phy_hit;
    hcsPhysical             phy_dying;      // pinched in two halves, or popping
    hcsTurret               turret[2];      // goo dripping turrets, one random fires (NULL - unused)
    char                    speed_x;
    char                    speed_y;
    unsigned char           reload;         // ticks between goo drops

} sCellStage, *hsCellStage;
typedef const sCellStage *hcsCellStage;

static const sCellStage cell_stages[] = {
    {
        &ot_blob,           &ot_blob_medium,    NULL,
        &phy_blob_big,      &phy_blob_big_hit,      &phy_blob_big_split,
        { &turret_cell_big_0, &turret_cell_big_1 },
        2, 1, 12
    },
    {
        &ot_blob_medium,    &ot_blob_small,     NULL,
        &phy_blob_medium,   &phy_blob_medium_hit,   &phy_blob_medium_split,
        { &turret_cell_medium, NULL },
        3, 2, 20
    },
    {
        &ot_blob_small,     NULL,               NULL,
        &phy_blob_small,    &phy_blob_small_hit,    &phy_blob_small_pop,
        { &turret_cell_small, NULL },
        5, 2, 28
    },
    {
        &ot_fuser,          &ot_fuser_medium,   NULL,
        &phy_fuser_big,     &phy_fuser_big_hit,     &phy_fuser_big_split,
        { &turret_cell_big_0, &turret_cell_big_1 },
        2, 1, 11
    },
    {
        &ot_fuser_medium,   &ot_fuser_small,    &ot_fuser,
        &phy_fuser_medium,  &phy_fuser_medium_hit,  &phy_fuser_medium_split,
        { &turret_cell_medium, NULL },
        3, 2, 24
    },
    {
        &ot_fuser_small,    NULL,               &ot_fuser_medium,
        &phy_fuser_small,   &phy_fuser_small_hit,   &phy_fuser_small_pop,
        { NULL, NULL },
        4, 2, 0
    },
};

static hcsCellStage cell_stage(hcsObjType type) {

    hcsCellStage stage;

    for (stage = &cell_stages[0]; stage < &cell_stages[dimof(cell_stages)]; stage++)
        if (stage->type == type)
            return stage;

    return NULL;
}

// ---------------------------------------------------------------------------
// cell behaviour
// ---------------------------------------------------------------------------

// world coordinates of the cell's center
#define CELL_CENTER_X(obj)              ((int)(obj)->pos.x + grid2world((obj)->physical->dim.x) / 2)
#define CELL_CENTER_Y(obj)              ((int)(obj)->pos.y + grid2world((obj)->physical->dim.y) / 2)

// spawn already initialized cell at the world position (clamped to the view),
// added inactive, as it's spawned from within the objects' tick loop
static hsObject cell_spawn(hcsObjType type, int x, int y, int speed_x, int speed_y, char cooldown) {

    hsObject cell;

    if ((cell = objpool_alloc_inactive(type)) == NULL)
        return NULL;

    cell->pos.x     = adjust(x, 0, grid2world(VIEWGRID_WIDTH - cell->physical->dim.x));
    cell->pos.y     = adjust(y, 0, grid2world(CELL_FLOOR - cell->physical->dim.y));
    cell->speed.x   = speed_x;
    cell->speed.y   = speed_y;
    cell->ttl       = 8 + rand() % 16;
    cell->state[0]  = 1;
    cell->state[2]  = cooldown;

    return cell;
}

// two halves popping out to the sides (and a bit up) of the dying cell
static void cell_split(hsObject obj, hcsCellStage stage) {

    hcsCellStage half;
    int y;

    half = cell_stage(stage->child);
    y = (int)obj->pos.y + grid2world(obj->physical->dim.y - half->phy->dim.y) / 2;

    cell_spawn(stage->child, (int)obj->pos.x - grid2world(1), y, -half->speed_x, -half->speed_y, CELL_SPLIT_COOLDOWN);
    cell_spawn(stage->child, (int)obj->pos.x + grid2world(obj->physical->dim.x - half->phy->dim.x + 1), y, half->speed_x, -half->speed_y, CELL_SPLIT_COOLDOWN);
}

// both cells melt into a bigger one right between them
static void cell_fuse(hsObject obj, hsObject partner, hcsCellStage stage) {

    hcsPhysical phy;
    int x, y;

    phy = cell_stage(stage->fused)->phy;
    x = (CELL_CENTER_X(obj) + CELL_CENTER_X(partner)) / 2 - grid2world(phy->dim.x) / 2;
    y = (CELL_CENTER_Y(obj) + CELL_CENTER_Y(partner)) / 2 - grid2world(phy->dim.y) / 2;

    if (cell_spawn(stage->fused, x, y, 0, 0, CELL_FUSE_COOLDOWN) == NULL)
        return;

    obj->flags      |= OBJ_FLG_DESTROY;
    partner->flags  |= OBJ_FLG_DESTROY;
}

// crawl towards the nearest cell of the same kind (also ready to fuse) and
// fuse with it once close enough; returns zero if there is no such cell
static unsigned char cell_seek(hsObject obj, hcsCellStage stage) {

    hsObject other, partner;
    int dx, dy, dist, best;

    partner = NULL;
    best = 0;

    other = NULL;
    while ((other = objpool_next(other)) != NULL) {

        if (other == obj || other->type != obj->type || other->state[2] > 0 || (other->flags & (OBJ_FLG_DYING | OBJ_FLG_DESTROY | OBJ_FLG_INACTIVE)))
            continue;

        dist = abs(CELL_CENTER_X(other) - CELL_CENTER_X(obj)) + abs(CELL_CENTER_Y(other) - CELL_CENTER_Y(obj));
        if (partner == NULL || dist < best) {

            partner = other;
            best    = dist;
        }
    }

    if (partner == NULL)
        return 0;

    dx = world2grid(CELL_CENTER_X(partner)) - world2grid(CELL_CENTER_X(obj));
    dy = world2grid(CELL_CENTER_Y(partner)) - world2grid(CELL_CENTER_Y(obj));

    if (abs(dx) <= 2 && abs(dy) <= 1) {

        cell_fuse(obj, partner, stage);
        return 1;
    }

    obj->speed.x = (dx > 1) ? stage->speed_x : ((dx < -1) ? -stage->speed_x : 0);
    obj->speed.y = (dy > 0) ? stage->speed_y : ((dy < 0) ? -stage->speed_y : 0);

    return 1;
}

// wander diagonally, bouncing off the view sides, ceiling and cell "floor"
static void cell_bounce(hsObject obj, hcsCellStage stage) {

    if (obj->speed.x == 0)
        obj->speed.x = (rand() & 1) ? stage->speed_x : -stage->speed_x;

    if (obj->speed.y == 0)
        obj->speed.y = stage->speed_y;

    if (OBJ_IS_LEFT(obj) && obj->speed.x < 0)
        obj->speed.x = stage->speed_x;
    else
    if (OBJ_IS_RIGHT(obj) && obj->speed.x > 0)
        obj->speed.x = -stage->speed_x;

    if (obj->pos.y < grid2world(CELL_CEILING) && obj->speed.y < 0)
        obj->speed.y = stage->speed_y;
    else
    if (world2grid(obj->pos.y) + obj->physical->dim.y >= CELL_FLOOR && obj->speed.y > 0)
        obj->speed.y = -stage->speed_y;
}

static void cell_behave(hsObject obj) {

    hcsCellStage stage;

    // already melted into another cell
    if (obj->flags & OBJ_FLG_DESTROY)
        return;

    stage = cell_stage(obj->type);

    // split right before the pinched cell disappears
    if (obj->flags & OBJ_FLG_DYING) {

        if (obj->ttl == 1 && stage->child != NULL)
            cell_split(obj, stage);

        return;
    }

    obj->physical = stage->phy;

    // first tick of a cell emitted by the scenario
    if (obj->state[0] == 0) {

        obj->state[0]   = 1;
        obj->speed.x    = (rand() & 1) ? stage->speed_x : -stage->speed_x;
        obj->speed.y    = stage->speed_y;
        obj->ttl        = 8 + rand() % 16;
    }

    if (obj->state[2] > 0)
        obj->state[2]--;

    // fusers look for a partner, the rest (or lonely fusers) just wander
    if (stage->fused == NULL || obj->state[2] > 0 || !cell_seek(obj, stage))
        cell_bounce(obj, stage);

    if (stage->turret[0] != NULL && obj->ttl == 0) {

        obj->ttl = stage->reload + rand() % 8;

        // cells with two turrets drip from a random one of them
        cell_goo(obj, stage->turret[(stage->turret[1] != NULL) ? (rand() & 1) : 0]);
    }
}

static void cell_die(hsObject obj) {

    hcsCellStage stage;

    stage = cell_stage(obj->type);

    obj->physical   = stage->phy_dying;
    obj->speed.x    = 0;
    obj->speed.y    = 0;
    obj->ttl        = (stage->child != NULL) ? CELL_SPLIT_TICKS : CELL_POP_TICKS;
}

static void cell_hit(hsObject obj) {

    obj->physical = cell_stage(obj->type)->phy_hit;
}

// ---------------------------------------------------------------------------
// mother cell - boss, slowly drifting at the top and spraying fans of goo;
// every time it takes MOTHER_BUD_DAMAGE, it swells and buds off a new cell
// (big blob and pair of small fusers in turns), when killed it ruptures
// and releases the last four small blobs
// ---------------------------------------------------------------------------

#define MOTHER_ST_DRIFT                 0
#define MOTHER_ST_BUD                   1

#define MOTHER_BUD_DAMAGE               24
#define MOTHER_MAX_CELLS                6       // no budding while there are more cells around
#define MOTHER_DEATH_TICKS              24
#define MOTHER_SPORE_SPEED              8

// m - membrane color; c - cytoplasm color; v - vacuoles color; n - nucleus color
#define PHY_MOTHER(m, c, v, n) { { 11, 5 }, {                                                                                                                                   \
    '\0',   0x00,   '\0',   0x00,   '.',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '.',    (m),    '\0',   0x00,   '\0',   0x00,   \
    '\0',   0x00,   '/',    (m),    '\xb0', (c),    'o',    (v),    '\xb0', (c),    '\xb0', (c),    '\xb0', (c),    'o',    (v),    '\xb0', (c),    '\\',   (m),    '\0',   0x00,   \
    '(',    (m),    '\xb0', (c),    '\xb0', (c),    '\xb0', (c),    '{',    (n),    '@',    0x0e,   '}',    (n),    '\xb0', (c),    '\xb0', (c),    '\xb0', (c),    ')',    (m),    \
    '\0',   0x00,   '\\',   (m),    '\xb0', (c),    'o',    (v),    '\xb0', (c),    '\xb0', (c),    '\xb0', (c),    'o',    (v),    '\xb0', (c),    '/',    (m),    '\0',   0x00,   \
    '\0',   0x00,   '\0',   0x00,   '`',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '~',    (m),    '\'',   (m),    '\0',   0x00,   '\0',   0x00    \
} }

static const sPhysical phy_mother       = PHY_MOTHER(0x0c, 0x04, 0x06, 0x0d);
static const sPhysical phy_mother_hit   = PHY_MOTHER(0x0f, 0x0f, 0x0f, 0x0f);
static const sPhysical phy_mother_swell = PHY_MOTHER(0x0e, 0x04, 0x0c, 0x0d);

static const sPhysical phy_mother_rupture = {
    { 11, 5 },
    {
        '\0',   0x00,   '.',    0x0c,   '\0',   0x00,   '~',    0x0c,   ',',    0x04,   '\0',   0x00,   '~',    0x0c,   '*',    0x0e,   '\0',   0x00,   '.',    0x0c,   '\0',   0x00,
        '/',    0x0c,   '\0',   0x00,   'o',    0x06,   '\xb0', 0x04,   '*',    0x0e,   '\0',   0x00,   '\xb0', 0x04,   '(',    0x0c,   'O',    0x0e,   ')',    0x0c,   '\0',   0x00,
        '(',    0x0c,   '\xb0', 0x04,   '*',    0x0f,   '\0',   0x00,   '{',    0x0d,   '*',    0x0f,   '\0',   0x00,   '\xb0', 0x04,   '*',    0x0e,   '\0',   0x00,   ')',    0x0c,
        '\0',   0x00,   '(',    0x0c,   'O',    0x0e,   ')',    0x0c,   '\0',   0x00,   '\xb0', 0x04,   '*',    0x0e,   '\0',   0x00,   'o',    0x06,   '\0',   0x00,   '\\',   0x0c,
        '\0',   0x00,   '\0',   0x00,   '`',    0x0c,   '~',    0x0c,   '\0',   0x00,   ',',    0x04,   '~',    0x0c,   '\0',   0x00,   '\'',   0x0c,   '\0',   0x00,   '\0',   0x00
    }
};
static const sPhysical phy_mother_debris = {
    { 11, 5 },
    {
        '.',    0x04,   '\0',   0x00,   '\0',   0x00,   '*',    0x0c,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   ',',    0x04,   '\0',   0x00,   '\0',   0x00,   '.',    0x0c,
        '\0',   0x00,   ',',    0x0c,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   '.',    0x04,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   '*',    0x04,   '\0',   0x00,
        '*',    0x04,   '\0',   0x00,   '\0',   0x00,   '.',    0x0c,   '\0',   0x00,   'o',    0x0e,   '\0',   0x00,   '\0',   0x00,   '.',    0x0c,   '\0',   0x00,   '*',    0x04,
        '\0',   0x00,   '.',    0x0c,   '\0',   0x00,   '\0',   0x00,   ',',    0x04,   '\0',   0x00,   '\0',   0x00,   '*',    0x0c,   '\0',   0x00,   '.',    0x04,   '\0',   0x00,
        '.',    0x04,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   '.',    0x0c,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   '\0',   0x00,   ',',    0x0c
    }
};

// fan of goo drops, sprayed one by one from left to right
static const sTurret turret_mother_spore[] = {
    TURRET_GRID(5, 5, -6, MOTHER_SPORE_SPEED, &ot_cell_goo),
    TURRET_GRID(5, 5, -4, MOTHER_SPORE_SPEED, &ot_cell_goo),
    TURRET_GRID(5, 5, -2, MOTHER_SPORE_SPEED, &ot_cell_goo),
    TURRET_GRID(5, 5, 0, MOTHER_SPORE_SPEED, &ot_cell_goo),
    TURRET_GRID(5, 5, +2, MOTHER_SPORE_SPEED, &ot_cell_goo),
    TURRET_GRID(5, 5, +4, MOTHER_SPORE_SPEED, &ot_cell_goo),
    TURRET_GRID(5, 5, +6, MOTHER_SPORE_SPEED, &ot_cell_goo),
};

// count cells still alive, so the mother doesn't flood the view with them
static unsigned char mother_cells(void) {

    hsObject obj;
    unsigned char count;

    obj = NULL;
    count = 0;
    while ((obj = objpool_next(obj)) != NULL)
        if (cell_stage(obj->type) != NULL && !(obj->flags & OBJ_FLG_DYING))
            count++;

    return count;
}

// pinch off a new cell below the nucleus, odd buds are pairs of fusers
static void mother_bud(hsObject obj) {

    int x, y;

    if (mother_cells() >= MOTHER_MAX_CELLS)
        return;

    x = CELL_CENTER_X(obj);
    y = (int)obj->pos.y + grid2world(obj->physical->dim.y);

    if (obj->state[1] & 1) {

        cell_spawn(&ot_fuser_small, x - grid2world(5), y, -4, 2, CELL_FUSE_COOLDOWN);
        cell_spawn(&ot_fuser_small, x + grid2world(2), y, +4, 2, CELL_FUSE_COOLDOWN);
    }
    else
        cell_spawn(&ot_blob, x - grid2world(3), y, (rand() & 1) ? 2 : -2, 1, 0);
}

// start spraying the fan of goo drops, wider when angry; state[2] is the
// next drop to fire (+1, zero when not spraying), state[3] the last one
static void mother_spores(hsObject obj, unsigned char angry) {

    obj->state[2] = angry ? 1 : 2;
    obj->state[3] = angry ? (dimof(turret_mother_spore) - 1) : (dimof(turret_mother_spore) - 2);
}

// fire one drop of the fan per tick
static void mother_spray(hsObject obj) {

    if (obj->state[2] == 0)
        return;

    cell_goo(obj, &turret_mother_spore[obj->state[2] - 1]);

    if (obj->state[2] - 1 >= obj->state[3])
        obj->state[2] = 0;
    else
        obj->state[2]++;
}

// last gasp - four small blobs scattering from the ruptured membrane
static void mother_release(hsObject obj) {

    int x, y;

    x = CELL_CENTER_X(obj) - grid2world(1);
    y = CELL_CENTER_Y(obj);

    cell_spawn(&ot_blob_small, x - grid2world(4), y - grid2world(1), -5, -2, 0);
    cell_spawn(&ot_blob_small, x - grid2world(2), y + grid2world(1), -5, +2, 0);
    cell_spawn(&ot_blob_small, x + grid2world(2), y - grid2world(1), +5, -2, 0);
    cell_spawn(&ot_blob_small, x + grid2world(4), y + grid2world(1), +5, +2, 0);
}

static void mother_behave(hsObject obj) {

    unsigned char angry;

    // rupturing first, then falling apart
    if (obj->flags & OBJ_FLG_DYING) {

        if (obj->ttl > MOTHER_DEATH_TICKS / 2)
            obj->physical = (obj->ttl & 2) ? &phy_mother_rupture : &phy_mother_swell;
        else
            obj->physical = (obj->ttl & 2) ? &phy_mother_rupture : &phy_mother_debris;

        if (obj->ttl == 1)
            mother_release(obj);

        return;
    }

    angry = (obj->damage_total >= obj->type->hp / 2);

    // drift from side to side, slowly bobbing up and down
    if (obj->speed.x == 0 || (OBJ_IS_LEFT(obj) && obj->speed.x < 0))
        obj->speed.x = 2;
    else
    if (OBJ_IS_RIGHT(obj) && obj->speed.x > 0)
        obj->speed.x = -2;

    if (obj->speed.y == 0 || obj->pos.y <= grid2world(2))
        obj->speed.y = 1;
    else
    if (obj->pos.y >= grid2world(8))
        obj->speed.y = -1;

    if (obj->state[0] == MOTHER_ST_DRIFT) {

        obj->physical = &phy_mother;

        if (obj->damage_total >= (unsigned int)(obj->state[1] + 1) * MOTHER_BUD_DAMAGE) {

            obj->state[0]   = MOTHER_ST_BUD;
            obj->state[2]   = 0;
            obj->ttl        = 12;
        }
        else
        if (obj->ttl == 0) {

            mother_spores(obj, angry);
            obj->ttl = angry ? 24 : 40;
        }

        mother_spray(obj);
    }
    else
    if (obj->state[0] == MOTHER_ST_BUD) {

        // stop and swell, then pinch the bud off
        obj->physical   = (obj->ttl & 2) ? &phy_mother_swell : &phy_mother;
        obj->speed.x    = 0;
        obj->speed.y    = 0;

        if (obj->ttl == 0) {

            mother_bud(obj);

            obj->state[1]++;
            obj->state[0]   = MOTHER_ST_DRIFT;
            obj->ttl        = 16;
        }
    }
}

static void mother_die(hsObject obj) {

    obj->physical   = &phy_mother_rupture;
    obj->speed.x    = 0;
    obj->speed.y    = 0;
    obj->ttl        = MOTHER_DEATH_TICKS;
}

static void mother_hit(hsObject obj) {

    obj->physical = &phy_mother_hit;
}

const sObjType ot_mother_cell = {
    &phy_mother,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_HPBAR,
    120,
    mother_behave,
    mother_die,
    mother_hit,
    NULL
};
