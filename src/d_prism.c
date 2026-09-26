#include "data.h"
#include <stdlib.h>

// ---------------------------------------------------------------------------
// prism family - crystal cores hiding behind mirrors; mirrors are separate
// indestructible objects, which reflect every shot back at the player (one
// reflection per PRISM_MIRROR_COOLDOWN, so the spam doesn't turn into a
// wall); the prism hides inside a mirror shell of two halves shaped like
// a fortune cookie, rattles it just before opening it to fire - the only
// moment the core is out and can be hit; the splitter prism reflects shots
// back as fans of three
// ---------------------------------------------------------------------------

#define PRISM_ST_CLOSED                 0
#define PRISM_ST_OPENING                1
#define PRISM_ST_OPEN                   2
#define PRISM_ST_CLOSING                3

#define PRISM_SHELL_OPEN                3       // halves slid apart fully open
#define PRISM_MARGIN                    (2 + PRISM_SHELL_OPEN)  // space for open halves at the sides (their outer part + slide)
#define PRISM_STEP                      3       // drift per tick, in world units
#define PRISM_MIRROR_COOLDOWN           6       // ticks between reflections of one mirror
#define PRISM_GLINT_SPEED               10
#define PRISM_RAY_SPEED                 9

// ---------------------------------------------------------------------------
// images
// ---------------------------------------------------------------------------

// e - edges color; g - glass color; d - diamonds color
#define PHY_PRISM(e, g, d) { { 4, 3 }, {                                        \
    '/',    (e),    '^',    (g),    '^',    (g),    '\\',   (e),                \
    '<',    (e),    '\x04', (d),    '\x04', (d),    '>',    (e),                \
    '\\',   (e),    'v',    (g),    'v',    (g),    '/',    (e)                 \
} }

#define PHY_PRISM_SHARDS(g, d) { { 4, 3 }, {                                    \
    '\'',   (g),    '*',    (d),    '\0',   0x00,   '`',    (g),                \
    '\0',   0x00,   '\x04', (d),    '*',    (g),    '\0',   0x00,               \
    ',',    (g),    '\0',   0x00,   '.',    (d),    '.',    (g)                 \
} }

// fortune cookie halves, closed around the core they make
//
//    .-~~-.
//   (##\/##)
//    `-..-'
//
// e - edges color; s - shell (shading) color
#define PHY_SHELL_LEFT(e, s) { { 4, 3 }, {                                      \
    '\0',   0x00,   '.',    (e),    '-',    (e),    '~',    (e),                \
    '(',    (e),    '\xb1', (s),    '\xb1', (s),    '\\',   (e),                \
    '\0',   0x00,   '`',    (e),    '-',    (e),    '.',    (e)                 \
} }

#define PHY_SHELL_RIGHT(e, s) { { 4, 3 }, {                                     \
    '~',    (e),    '-',    (e),    '.',    (e),    '\0',   0x00,               \
    '/',    (e),    '\xb1', (s),    '\xb1', (s),    ')',    (e),                \
    '.',    (e),    '-',    (e),    '\'',   (e),    '\0',   0x00                \
} }

#define PHY_SHELL_SHARDS(e) { { 4, 3 }, {                                       \
    '\0',   0x00,   '.',    (e),    '\0',   0x00,   '`',    (e),                \
    '\'',   (e),    '\0',   0x00,   ',',    (e),    '\0',   0x00,               \
    '\0',   0x00,   '.',    (e),    '\0',   0x00,   '.',    (e)                 \
} }

static const sPhysical phy_prism                = PHY_PRISM(0x03, 0x0b, 0x0d);
static const sPhysical phy_prism_hit            = PHY_PRISM(0x0f, 0x0f, 0x0d);
static const sPhysical phy_prism_dying          = PHY_PRISM_SHARDS(0x0b, 0x0d);
static const sPhysical phy_prism_none           = { { 4, 3 }, { '\0' } };
static const sPhysical phy_prism_shell_left         = PHY_SHELL_LEFT(0x07, 0x08);
static const sPhysical phy_prism_shell_right        = PHY_SHELL_RIGHT(0x07, 0x08);
static const sPhysical phy_prism_shell_left_flash   = PHY_SHELL_LEFT(0x0f, 0x07);
static const sPhysical phy_prism_shell_right_flash  = PHY_SHELL_RIGHT(0x0f, 0x07);
static const sPhysical phy_prism_shell_dying        = PHY_SHELL_SHARDS(0x07);

static const sPhysical phy_splitter             = PHY_PRISM(0x05, 0x0d, 0x0e);
static const sPhysical phy_splitter_hit         = PHY_PRISM(0x0f, 0x0f, 0x0e);
static const sPhysical phy_splitter_dying       = PHY_PRISM_SHARDS(0x0d, 0x0e);
static const sPhysical phy_splitter_shell_left          = PHY_SHELL_LEFT(0x0d, 0x05);
static const sPhysical phy_splitter_shell_right         = PHY_SHELL_RIGHT(0x0d, 0x05);
static const sPhysical phy_splitter_shell_left_flash    = PHY_SHELL_LEFT(0x0f, 0x0d);
static const sPhysical phy_splitter_shell_right_flash   = PHY_SHELL_RIGHT(0x0f, 0x0d);
static const sPhysical phy_splitter_shell_dying         = PHY_SHELL_SHARDS(0x0d);


static const sPhysical phy_prism_glint_shot     = PHYSICAL_1X1('!', 0x0b);
static const sPhysical phy_prism_ray            = PHYSICAL_1X1('\x04', 0x0d);

// ---------------------------------------------------------------------------
// shots
// ---------------------------------------------------------------------------

// player's own shot, reflected
static const sObjType ot_prism_glint = {
    &phy_prism_glint_shot,
    OBJTYPE_NAT_FOE_BULLET,
    OBJTYPE_FLG_NONE,
    5,
    NULL,
    NULL,
    NULL,
    cb_deal_die
};

static const sObjType ot_prism_ray = {
    &phy_prism_ray,
    OBJTYPE_NAT_FOE_BULLET,
    OBJTYPE_FLG_NONE,
    6,
    NULL,
    NULL,
    NULL,
    cb_deal_die
};

static const sTurret turret_shell_glint     = TURRET_GRID(2, 3, 0, PRISM_GLINT_SPEED, &ot_prism_glint);
static const sTurret turret_prism_ray       = TURRET_GRID(2, 3, 0, PRISM_RAY_SPEED, &ot_prism_ray);

// fire shot aimed at the player's current position, "spread" is added to
// it's aimed horizontal speed (for fans around the aimed shot)
static void prism_aim(hsObject obj, hcsTurret turret, int spread) {

    hsObject shot;
    int dx, dy, speed;

    if ((shot = fire_turret(obj, turret)) == NULL)
        return;

    speed = turret->speed.y;
    dx = (int)world2grid(player->pos.x) + player->physical->dim.x / 2 - (int)world2grid(shot->pos.x);
    dy = (int)world2grid(player->pos.y) - (int)world2grid(shot->pos.y);
    if (dy < 1)
        dy = 1;

    shot->speed.x = adjust(dx * speed / dy + spread, -speed, speed);
}

// ---------------------------------------------------------------------------
// object types
// ---------------------------------------------------------------------------

// all the mirrors share the callbacks, differences are in the mirror table;
// mirror state: [0] - side at the owner (0 - left, 1 - right), [1] - owner's
// id, [2] - reflection cooldown
static void mirror_behave(hsObject obj);
static void mirror_hit(hsObject obj);

// both small prisms share the callbacks too, differences in the prism table
static void prism_behave(hsObject obj);
static void prism_die(hsObject obj);
static void prism_hit(hsObject obj);

static const sObjType ot_prism_shell = {
    &phy_prism_shell_left,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    1,
    mirror_behave,
    NULL,
    mirror_hit,
    NULL
};

static const sObjType ot_splitter_shell = {
    &phy_splitter_shell_left,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    1,
    mirror_behave,
    NULL,
    mirror_hit,
    NULL
};

const sObjType ot_prism = {
    &phy_prism,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    18,
    prism_behave,
    prism_die,
    prism_hit,
    NULL
};

const sObjType ot_splitter = {
    &phy_splitter,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    24,
    prism_behave,
    prism_die,
    prism_hit,
    NULL
};

// ---------------------------------------------------------------------------
// mirrors
// ---------------------------------------------------------------------------

typedef struct sMirrorKind {

    hcsObjType              type;
    hcsPhysical             phy[2];         // left and right one
    hcsPhysical             phy_flash[2];
    hcsPhysical             phy_dying;
    hcsTurret               turret;         // reflected shot turret
    unsigned char           fan;            // reflect as fan of three

} sMirrorKind, *hsMirrorKind;
typedef const sMirrorKind *hcsMirrorKind;

static const sMirrorKind mirror_kinds[] = {
    {
        &ot_prism_shell,
        { &phy_prism_shell_left, &phy_prism_shell_right },
        { &phy_prism_shell_left_flash, &phy_prism_shell_right_flash },
        &phy_prism_shell_dying,
        &turret_shell_glint,
        0
    },
    {
        &ot_splitter_shell,
        { &phy_splitter_shell_left, &phy_splitter_shell_right },
        { &phy_splitter_shell_left_flash, &phy_splitter_shell_right_flash },
        &phy_splitter_shell_dying,
        &turret_shell_glint,
        1
    },
};

static hcsMirrorKind mirror_kind(hcsObjType type) {

    hcsMirrorKind kind;

    for (kind = &mirror_kinds[0]; kind < &mirror_kinds[dimof(mirror_kinds)]; kind++)
        if (kind->type == type)
            return kind;

    return NULL;
}

// id shared by an owner and it's mirrors
static unsigned char prism_next_id;

static unsigned char prism_new_id(void) {

    if (++prism_next_id == 0)
        prism_next_id = 1;

    return prism_next_id;
}

// add the owner's mirrors, placed later by the owner itself
static void mirror_spawn(hsObject obj, hcsObjType type, unsigned char count) {

    hsObject mirror;
    unsigned char i;

    for (i = 0; i < count; i++) {

        // added inactive, as it's spawned from within the objects' tick loop
        if ((mirror = objpool_alloc_inactive(type)) == NULL)
            return;

        mirror->pos.x       = obj->pos.x;
        mirror->pos.y       = obj->pos.y;
        mirror->state[0]    = i;
        mirror->state[1]    = obj->state[1];
    }
}

// the owner is gone, it's mirrors shatter
static void mirror_shatter(hsObject obj, hcsObjType type) {

    hsObject mirror;

    mirror = NULL;
    while ((mirror = objpool_next(mirror)) != NULL) {

        if (mirror->type != type || mirror->state[1] != obj->state[1] || (mirror->flags & OBJ_FLG_DYING))
            continue;

        mirror->flags       |= OBJ_FLG_DYING;
        mirror->physical    = mirror_kind(type)->phy_dying;
        mirror->ttl         = 4;
    }
}

static void mirror_behave(hsObject obj) {

    hcsMirrorKind kind;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    kind = mirror_kind(obj->type);

    if (obj->state[2] > 0)
        obj->state[2]--;

    obj->physical = (obj->state[2] > PRISM_MIRROR_COOLDOWN - 3) ? kind->phy_flash[obj->state[0]] : kind->phy[obj->state[0]];
}

// mirrors can't be damaged, the hit is reflected back instead
static void mirror_hit(hsObject obj) {

    hcsMirrorKind kind;

    obj->damage_now = 0;

    if (obj->state[2] > 0)
        return;

    kind = mirror_kind(obj->type);

    obj->state[2]   = PRISM_MIRROR_COOLDOWN;
    obj->physical   = kind->phy_flash[obj->state[0]];

    prism_aim(obj, kind->turret, 0);
    if (kind->fan) {

        prism_aim(obj, kind->turret, -5);
        prism_aim(obj, kind->turret, +5);
    }
}

// place shell half around the owner, "slide" columns apart from closed; the
// halves are centered on the owner vertically and meet in it's middle
static void shell_place_half(hsObject obj, hsObject half, unsigned char slide) {

    int mid;

    mid = (int)obj->pos.x + grid2world(obj->physical->dim.x / 2);

    half->pos.y = obj->pos.y - grid2world((half->physical->dim.y - obj->physical->dim.y) / 2);

    if (half->state[0] == 0)
        half->pos.x = mid - grid2world(half->physical->dim.x + slide);
    else
        half->pos.x = mid + grid2world(slide);
}

// the core is hidden (and can't be hit) until the shell halves are slid
// apart far enough not to overlap it, as the blank cells would wipe out each
// other; "none" is a blank image of the core's dimensions
static void shell_hide_core(hsObject obj, unsigned char slide, hcsPhysical none) {

    if (slide < obj->physical->dim.x / 2) {

        obj->physical   = none;
        obj->flags      |= OBJ_FLG_HIDDEN;
    }
    else
        obj->flags      &= ~OBJ_FLG_HIDDEN;
}

// ---------------------------------------------------------------------------
// prism & splitter prism
// ---------------------------------------------------------------------------

typedef struct sPrismKind {

    hcsObjType              type;
    hcsObjType              shell;
    hcsPhysical             phy;
    hcsPhysical             phy_hit;
    hcsPhysical             phy_dying;
    unsigned char           fan;            // fire fans of three instead of pairs of aimed shots

} sPrismKind, *hsPrismKind;
typedef const sPrismKind *hcsPrismKind;

static const sPrismKind prism_kinds[] = {
    { &ot_prism,    &ot_prism_shell,    &phy_prism,     &phy_prism_hit,     &phy_prism_dying,       0 },
    { &ot_splitter, &ot_splitter_shell, &phy_splitter,  &phy_splitter_hit,  &phy_splitter_dying,    1 },
};

static hcsPrismKind prism_kind(hcsObjType type) {

    hcsPrismKind kind;

    for (kind = &prism_kinds[0]; kind < &prism_kinds[dimof(prism_kinds)]; kind++)
        if (kind->type == type)
            return kind;

    return NULL;
}

// prism state: [0] - PRISM_ST_*, [1] - id, [2] - how far are the shell halves
// slid apart, [3] - drift direction
static void prism_init(hsObject obj, hcsPrismKind kind) {

    obj->state[0]   = PRISM_ST_CLOSED;
    obj->state[1]   = prism_new_id();
    obj->state[2]   = 0;
    obj->state[3]   = (rand() & 1) ? 1 : -1;
    obj->ttl        = 24 + rand() % 16;

    // keep space for the open shell at both sides
    obj->pos.x = adjust(obj->pos.x, grid2world(PRISM_MARGIN), grid2world(VIEWGRID_WIDTH - obj->physical->dim.x - PRISM_MARGIN));

    mirror_spawn(obj, kind->shell, 2);
}

// slowly drift from side to side, leaving space for the open shell
static void prism_drift(hsObject obj) {

    int x, min, max;

    min = grid2world(PRISM_MARGIN);
    max = grid2world(VIEWGRID_WIDTH - obj->physical->dim.x - PRISM_MARGIN);
    x = (int)obj->pos.x + obj->state[3] * PRISM_STEP;

    if (x <= min) {

        x = min;
        obj->state[3] = 1;
    }
    else
    if (x >= max) {

        x = max;
        obj->state[3] = -1;
    }

    obj->pos.x = x;
}

// shell halves closed around the core, sliding apart to the sides when opening
static void prism_place_shell(hsObject obj, hcsObjType type) {

    hsObject half;

    half = NULL;
    while ((half = objpool_next(half)) != NULL)
        if (half->type == type && half->state[1] == obj->state[1] && !(half->flags & OBJ_FLG_DYING))
            shell_place_half(obj, half, obj->state[2]);

    shell_hide_core(obj, obj->state[2], &phy_prism_none);
}

static void prism_fire(hsObject obj, hcsPrismKind kind) {

    if (kind->fan) {

        if (obj->ttl == 16) {

            prism_aim(obj, &turret_prism_ray, -5);
            prism_aim(obj, &turret_prism_ray, 0);
            prism_aim(obj, &turret_prism_ray, +5);
        }
    }
    else
    if (obj->ttl == 20 || obj->ttl == 10)
        prism_aim(obj, &turret_prism_ray, 0);
}

static void prism_behave(hsObject obj) {

    hcsPrismKind kind;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    kind = prism_kind(obj->type);

    // first tick, spawn the shell
    if (obj->state[1] == 0)
        prism_init(obj, kind);

    obj->physical = kind->phy;

    if (obj->state[0] == PRISM_ST_CLOSED) {

        // rattling the shell just before opening
        obj->state[2] = (obj->ttl < 8 && (obj->ttl & 2)) ? 1 : 0;

        prism_drift(obj);

        if (obj->ttl == 0)
            obj->state[0] = PRISM_ST_OPENING;
    }
    else
    if (obj->state[0] == PRISM_ST_OPENING) {

        if (++obj->state[2] >= PRISM_SHELL_OPEN) {

            obj->state[0]   = PRISM_ST_OPEN;
            obj->ttl        = 24;
        }
    }
    else
    if (obj->state[0] == PRISM_ST_OPEN) {

        // stands still while open, firing
        prism_fire(obj, kind);

        if (obj->ttl == 0)
            obj->state[0] = PRISM_ST_CLOSING;
    }
    else
    if (obj->state[0] == PRISM_ST_CLOSING) {

        if (--obj->state[2] <= 0) {

            obj->state[0]   = PRISM_ST_CLOSED;
            obj->ttl        = 40 + rand() % 24;
        }
    }

    prism_place_shell(obj, kind->shell);
}

static void prism_die(hsObject obj) {

    hcsPrismKind kind;

    kind = prism_kind(obj->type);

    obj->physical   = kind->phy_dying;
    obj->flags      &= ~OBJ_FLG_HIDDEN;
    obj->ttl        = 6;

    mirror_shatter(obj, kind->shell);
}

static void prism_hit(hsObject obj) {

    obj->physical = prism_kind(obj->type)->phy_hit;
}
