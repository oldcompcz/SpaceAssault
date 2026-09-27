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

// fired while diving, as fast relative to the diving stinger as the sting is
#define STINGER_DIVE_SPEED              14
static const sTurret turret_grchkrx_sting_dive = TURRET_GRID(1, 2, 0, STINGER_DIVE_SPEED + 16, &ot_foe_laser);

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

// grchkrx empress - huge queen with a crown and antennae flashing before her
// big moves; tears her wings off halfway through, getting down to business
static const sPhysical phy_grchkrx_empress = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x04,   '\0',   0x00,   '\\',   0x0e,   '/',    0x0e,   '^',    0x0e,   '^',    0x0e,   '\\',   0x0e,   '/',    0x0e,   '\0',   0x00,   '/',    0x04,   '\0',   0x00,
        '\0',   0x00,   '_',    0x04,   '/',    0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x04,   '_',    0x04,   '\0',   0x00,
        '#',    0x04,   '=',    0x04,   '#',    0x04,   ' ',    0x04,   '_',    0x04,   '_',    0x04,   '_',    0x04,   '_',    0x04,   ' ',    0x04,   '#',    0x04,   '=',    0x04,   '#',    0x04,
        '|',    0x04,   ' ',    0x04,   '|',    0x04,   ' ',    0x04,   '|',    0x04,   '!',    0x09,   '!',    0x09,   '|',    0x04,   ' ',    0x04,   '|',    0x04,   ' ',    0x04,   '|',    0x04,
        '\0',   0x00,   '\\',   0x04,   '/',    0x04,   '\0',   0x00,   '\\',   0x04,   'V',    0x09,   'V',    0x09,   '/',    0x04,   '\0',   0x00,   '\\',   0x04,   '/',    0x04,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_empress_hit = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x0c,   '\0',   0x00,   '\\',   0x0e,   '/',    0x0e,   '^',    0x0e,   '^',    0x0e,   '\\',   0x0e,   '/',    0x0e,   '\0',   0x00,   '/',    0x0c,   '\0',   0x00,
        '\0',   0x00,   '_',    0x0c,   '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,   '_',    0x0c,   '\0',   0x00,
        '#',    0x0c,   '=',    0x0c,   '#',    0x0c,   ' ',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   ' ',    0x0c,   '#',    0x0c,   '=',    0x0c,   '#',    0x0c,
        '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   '!',    0x09,   '!',    0x09,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,
        '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   'V',    0x09,   'V',    0x09,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_empress_flash = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x0c,   '\0',   0x00,   '\\',   0x0f,   '/',    0x0f,   '^',    0x0f,   '^',    0x0f,   '\\',   0x0f,   '/',    0x0f,   '\0',   0x00,   '/',    0x0c,   '\0',   0x00,
        '\0',   0x00,   '_',    0x0c,   '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,   '_',    0x0c,   '\0',   0x00,
        '#',    0x0c,   '=',    0x0c,   '#',    0x0c,   ' ',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   ' ',    0x0c,   '#',    0x0c,   '=',    0x0c,   '#',    0x0c,
        '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   '!',    0x0f,   '!',    0x0f,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,
        '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   'V',    0x0f,   'V',    0x0f,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_empress_torn = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x04,   '\0',   0x00,   '\\',   0x0e,   '/',    0x0e,   '^',    0x0e,   '^',    0x0e,   '\\',   0x0e,   '/',    0x0e,   '\0',   0x00,   '/',    0x04,   '\0',   0x00,
        '\0',   0x00,   '_',    0x04,   '/',    0x04,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x04,   '_',    0x04,   '\0',   0x00,
        '\'',   0x08,   ',',    0x08,   '.',    0x08,   ' ',    0x04,   '_',    0x04,   '_',    0x04,   '_',    0x04,   '_',    0x04,   ' ',    0x04,   '.',    0x08,   ',',    0x08,   '\'',   0x08,
        ':',    0x08,   ' ',    0x04,   '|',    0x04,   ' ',    0x04,   '|',    0x04,   '!',    0x09,   '!',    0x09,   '|',    0x04,   ' ',    0x04,   '|',    0x04,   ' ',    0x04,   ':',    0x08,
        '\0',   0x00,   '\\',   0x04,   '/',    0x04,   '\0',   0x00,   '\\',   0x04,   'V',    0x09,   'V',    0x09,   '/',    0x04,   '\0',   0x00,   '\\',   0x04,   '/',    0x04,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_empress_torn_hit = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x0c,   '\0',   0x00,   '\\',   0x0e,   '/',    0x0e,   '^',    0x0e,   '^',    0x0e,   '\\',   0x0e,   '/',    0x0e,   '\0',   0x00,   '/',    0x0c,   '\0',   0x00,
        '\0',   0x00,   '_',    0x0c,   '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,   '_',    0x0c,   '\0',   0x00,
        '\'',   0x08,   ',',    0x08,   '.',    0x08,   ' ',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   ' ',    0x0c,   '.',    0x08,   ',',    0x08,   '\'',   0x08,
        ':',    0x08,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   '!',    0x09,   '!',    0x09,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   ':',    0x08,
        '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   'V',    0x09,   'V',    0x09,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_empress_torn_flash = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x0c,   '\0',   0x00,   '\\',   0x0f,   '/',    0x0f,   '^',    0x0f,   '^',    0x0f,   '\\',   0x0f,   '/',    0x0f,   '\0',   0x00,   '/',    0x0c,   '\0',   0x00,
        '\0',   0x00,   '_',    0x0c,   '/',    0x0c,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   'o',    0x06,   '\\',   0x0c,   '_',    0x0c,   '\0',   0x00,
        '\'',   0x08,   ',',    0x08,   '.',    0x08,   ' ',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   '_',    0x0c,   ' ',    0x0c,   '.',    0x08,   ',',    0x08,   '\'',   0x08,
        ':',    0x08,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   '!',    0x0f,   '!',    0x0f,   '|',    0x0c,   ' ',    0x0c,   '|',    0x0c,   ' ',    0x0c,   ':',    0x08,
        '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   'V',    0x0f,   'V',    0x0f,   '/',    0x0c,   '\0',   0x00,   '\\',   0x0c,   '/',    0x0c,   '\0',   0x00
    }
};
static const sPhysical phy_grchkrx_empress_dying = {
    { 12, 5 },
    {
        '\0',   0x00,   '\\',   0x08,   '\0',   0x00,   '\\',   0x08,   '/',    0x08,   '.',    0x08,   '.',    0x08,   '\\',   0x08,   '/',    0x08,   '\0',   0x00,   '/',    0x08,   '\0',   0x00,
        '\0',   0x00,   '_',    0x08,   '/',    0x08,   '*',    0x08,   '*',    0x08,   '*',    0x08,   '*',    0x08,   '*',    0x08,   '*',    0x08,   '\\',   0x08,   '_',    0x08,   '\0',   0x00,
        '\'',   0x08,   ',',    0x08,   '.',    0x08,   ' ',    0x08,   '_',    0x08,   '_',    0x08,   '_',    0x08,   '_',    0x08,   ' ',    0x08,   '.',    0x08,   ',',    0x08,   '\'',   0x08,
        ':',    0x08,   ' ',    0x08,   '|',    0x08,   ' ',    0x08,   '|',    0x08,   ':',    0x08,   ':',    0x08,   '|',    0x08,   ' ',    0x08,   '|',    0x08,   ' ',    0x08,   ':',    0x08,
        '\0',   0x00,   '\\',   0x08,   '/',    0x08,   '\0',   0x00,   '\\',   0x08,   'v',    0x08,   'v',    0x08,   '/',    0x08,   '\0',   0x00,   '\\',   0x08,   '/',    0x08,   '\0',   0x00
    }
};

static const sPhysical phy_grchkrx_honey = PHYSICAL_1X1('\x07', 0x0e);

static const sObjType ot_grchkrx_honey = {
    &phy_grchkrx_honey,
    OBJTYPE_NAT_FOE_BULLET,
    OBJTYPE_FLG_NONE,
    5,
    NULL,
    NULL,
    NULL,
    cb_deal_die
};

// royal fan - pairs spreading wider and wider
static const sTurret turret_grchkrx_empress_fan[5][2] = {
    { TURRET_GRID(5, 5, -1, 10, &ot_foe_ball), TURRET_GRID(6, 5, +1, 10, &ot_foe_ball) },
    { TURRET_GRID(5, 5, -2,  9, &ot_foe_ball), TURRET_GRID(6, 5, +2,  9, &ot_foe_ball) },
    { TURRET_GRID(5, 5, -3,  9, &ot_foe_ball), TURRET_GRID(6, 5, +3,  9, &ot_foe_ball) },
    { TURRET_GRID(5, 5, -4,  8, &ot_foe_ball), TURRET_GRID(6, 5, +4,  8, &ot_foe_ball) },
    { TURRET_GRID(5, 5, -5,  7, &ot_foe_ball), TURRET_GRID(6, 5, +5,  7, &ot_foe_ball) },
};

// honey drops, horizontal speed gets aimed at the player
#define EMPRESS_HONEY_SPEED             8
static const sTurret turret_grchkrx_empress_honey = TURRET_GRID(5, 5, 0, EMPRESS_HONEY_SPEED, &ot_grchkrx_honey);

// royal sting - spread of lasers from right above the player
static const sTurret turret_grchkrx_empress_sting[5] = {
    TURRET_GRID(5, 5, -6, 14, &ot_foe_laser),
    TURRET_GRID(5, 5, -3, 14, &ot_foe_laser),
    TURRET_GRID(5, 5,  0, 16, &ot_foe_laser),
    TURRET_GRID(6, 5, +3, 14, &ot_foe_laser),
    TURRET_GRID(6, 5, +6, 14, &ot_foe_laser),
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

// brood pod - a floating chunk of honeycomb, it's cells full of honey; the
// brood cells and the heart hang under it as separate objects
// e - edges color; h - honey char; c - honey color
#define PHY_POD(e, h, c) { \
    { 19, 3 }, \
    { \
        '\0', 0x00, '_',  (e),  '\0', 0x00, '\0', 0x00, '\0', 0x00, '_',  (e),  '\0', 0x00, '\0', 0x00, '\0', 0x00, '_',  (e),  '\0', 0x00, '\0', 0x00, '\0', 0x00, '_',  (e),  '\0', 0x00, '\0', 0x00, '\0', 0x00, '_',  (e),  '\0', 0x00, \
        '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  \
        '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e),  (h),  (c),  '\\', (e),  '_',  (e),  '/',  (e)   \
    } \
}

static const sPhysical phy_grchkrx_pod          = PHY_POD(0x0e, '\xb0', 0x06);
static const sPhysical phy_grchkrx_pod_cracked  = PHY_POD(0x06, ',', 0x0e);
static const sPhysical phy_grchkrx_pod_dying    = PHY_POD(0x08, '.', 0x08);

// pod's hanging parts, 3x1
#define PHY_POD_PART(a, ac, b, bc, c, cc) { { 3, 1 }, { (a), (ac), (b), (bc), (c), (cc) } }

// brood cell - grub wriggling inside, bulging and flashing just before it
// drops out; sealed with wax when shot, the grub peeking through the wax
// while chewing it's way out again
static const sPhysical phy_grchkrx_cell_0       = PHY_POD_PART('(', 0x06, 'o', 0x0e, ')', 0x06);
static const sPhysical phy_grchkrx_cell_1       = PHY_POD_PART('(', 0x06, 'O', 0x0e, ')', 0x06);
static const sPhysical phy_grchkrx_cell_full    = PHY_POD_PART('(', 0x0e, '@', 0x0e, ')', 0x0e);
static const sPhysical phy_grchkrx_cell_hit     = PHY_POD_PART('(', 0x0c, 'o', 0x0c, ')', 0x0c);
static const sPhysical phy_grchkrx_cell_sealed  = PHY_POD_PART('[', 0x0e, '\xb1', 0x06, ']', 0x0e);
static const sPhysical phy_grchkrx_cell_chewed  = PHY_POD_PART('[', 0x0e, 'o', 0x0e, ']', 0x0e);
static const sPhysical phy_grchkrx_cell_dying   = PHY_POD_PART('.', 0x08, ',', 0x08, '.', 0x08);

// heart - plugged with wax, the plug flashing before it opens; open it beats;
// 5x2 heart shape filling the gaps between the inner cells and hanging below
// them; l, r - top corners; m - middle char; e, c - edges and middle colors
#define PHY_POD_HEART(l, r, m, e, c) { \
    { 5, 2 }, \
    { \
        (l),  (e),  (m),  (c),  (m),  (c),  (m),  (c),  (r),  (e),  \
        '\0', 0x00, '\\', (e),  (m),  (c),  '/',  (e),  '\0', 0x00  \
    } \
}

static const sPhysical phy_grchkrx_heart_plug   = PHY_POD_HEART('{', '}', '=', 0x06, 0x0e);
static const sPhysical phy_grchkrx_heart_flash  = PHY_POD_HEART('{', '}', '\x03', 0x0c, 0x0c);
static const sPhysical phy_grchkrx_heart_0      = PHY_POD_HEART('<', '>', '\x03', 0x04, 0x0c);
static const sPhysical phy_grchkrx_heart_1      = PHY_POD_HEART('<', '>', '\x03', 0x04, 0x04);
static const sPhysical phy_grchkrx_heart_hit    = PHY_POD_HEART('<', '>', '\x03', 0x0f, 0x0f);
static const sPhysical phy_grchkrx_heart_dying  = PHY_POD_HEART('.', '.', '*', 0x08, 0x08);

static const sTurret turret_grchkrx_heart_honey = TURRET_GRID(2, 2, 0, EMPRESS_HONEY_SPEED, &ot_grchkrx_honey);

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
#define WAX_MELT_HP                     2

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
// on the player's column and flashes, dives straight down firing lasers all
// the way, stings with a burst of lasers from right above the player and
// climbs back home
#define STINGER_ST_HOVER                1
#define STINGER_ST_AIM                  2
#define STINGER_ST_DIVE                 3
#define STINGER_ST_STING                4
#define STINGER_ST_RETURN               5

#define STINGER_TRACK_SPEED             4
#define STINGER_HOVER_TICKS             24      // plus up to 31 random
#define STINGER_AIM_TICKS               8
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
                obj->state[2] = 0;
                obj->speed.y = STINGER_DIVE_SPEED;
            }
            break;

        // down until stopped by the monsters' floor, laser on every other
        // tick (counted in state[2]) right from the start
        case STINGER_ST_DIVE:

            obj->physical = &phy_grchkrx_stinger_dive;

            if (!(obj->state[2]++ & 1))
                fire_turret(obj, &turret_grchkrx_sting_dive);

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

// empress drifts along the top, now and then pausing or turning back and
// flinching away when hit; her attack loop is royal fan, burst of aimed honey
// and laying a larva (antennae flash first); at half hp she tears her wings
// off, descends and sweeps side to side with the royal fan followed by a couple
// of laser spreads, laying stingers above herself, then hunts the player down for a royal sting - locks on (long flash), dives down
// to EMPRESS_STING_GAP rows above the player and stings with a laser spread,
// then slides after the player for another sting or two (short flash) and climbs
#define EMPRESS_ST_DRIFT                1
#define EMPRESS_ST_DESCEND              2
#define EMPRESS_ST_SWEEP                3
#define EMPRESS_ST_HUNT                 4
#define EMPRESS_ST_AIM                  5
#define EMPRESS_ST_DIVE                 6
#define EMPRESS_ST_STING                7
#define EMPRESS_ST_SLIDE                8
#define EMPRESS_ST_FLOOR_AIM            9
#define EMPRESS_ST_CLIMB                10

#define EMPRESS_HP                      280
#define EMPRESS_DRIFT_SPEED             2
#define EMPRESS_FLINCH_SPEED            5       // wings on, a hit makes her dart away from the player's side
#define EMPRESS_FLINCH_TICKS            12
#define EMPRESS_FLINCH_COOLDOWN         48      // counted from the flinch start, in ttl
#define EMPRESS_CYCLE                   64      // wings on attack loop, in ticks, royal fan starting it
#define EMPRESS_HONEY_AT                24      // loop tick starting the honey burst
#define EMPRESS_HONEY_BURST             5       // drops, 3 ticks apart
#define EMPRESS_EGG_AT                  52      // loop tick laying a larva, antennae flash for 8 ticks before
#define EMPRESS_MAX_LARVAE              4
#define EMPRESS_TORN_ROW                24      // row she sweeps along with wings torn off, below the wax barrier
#define EMPRESS_DESCEND_SPEED           3
#define EMPRESS_SWEEP_SPEED             4
#define EMPRESS_SWEEP_FAN_AT            8       // sweep loop tick starting the royal fan
#define EMPRESS_LASERS_AT               28      // sweep loop ticks firing laser spreads after the fan
#define EMPRESS_LASERS_AT2              31
#define EMPRESS_BROOD_AT                34      // sweep loop tick laying a stinger, antennae flash for 8 ticks before
#define EMPRESS_MAX_STINGERS            2
#define EMPRESS_HUNT_AT                 38      // sweep loop tick to start hunting
#define EMPRESS_HUNT_SPEED              5
#define EMPRESS_HUNT_TICKS              32      // gives up aligning and stings anyway
#define EMPRESS_AIM_TICKS               16
#define EMPRESS_DIVE_SPEED              10
#define EMPRESS_STING_GAP               3       // free rows kept between her and the player when stinging
#define EMPRESS_STING_TICKS             6       // resting at the floor after each sting
#define EMPRESS_STING_CHAIN             2       // extra stings along the floor, 1 to this many
#define EMPRESS_SLIDE_SPEED             6
#define EMPRESS_SLIDE_TICKS             16      // gives up aligning and stings anyway
#define EMPRESS_FLOOR_AIM_TICKS         8
#define EMPRESS_CLIMB_SPEED             5

#define EMPRESS_FRM_NORMAL              0
#define EMPRESS_FRM_HIT                 1
#define EMPRESS_FRM_FLASH               2

// by wings (state[3] - 0 on, 1 torn off) and EMPRESS_FRM_*
static const hcsPhysical phy_grchkrx_empress_frames[2][3] = {
    { &phy_grchkrx_empress, &phy_grchkrx_empress_hit, &phy_grchkrx_empress_flash },
    { &phy_grchkrx_empress_torn, &phy_grchkrx_empress_torn_hit, &phy_grchkrx_empress_torn_flash },
};

static void empress_frame(hsObject obj, unsigned char frame) {

    obj->physical = phy_grchkrx_empress_frames[obj->state[3]][frame];
}

// royal fan fires its pairs one by one, every 4 ticks from its "step" 0
static void empress_fan(hsObject obj, int step) {

    if (step < 0 || step >= 4 * (int)dimof(turret_grchkrx_empress_fan) || (step & 3))
        return;

    fire_turret(obj, &turret_grchkrx_empress_fan[step / 4][0]);
    fire_turret(obj, &turret_grchkrx_empress_fan[step / 4][1]);
}

// honey drop from the turret aimed at the player's current position
static void honey_aimed(hsObject obj, hcsTurret turret) {

    hsObject drop;
    int dx, dy;

    if (player == NULL || (drop = fire_turret(obj, turret)) == NULL)
        return;

    dx = (int)world2grid(player->pos.x) + player->physical->dim.x / 2 - (int)world2grid(drop->pos.x);
    dy = (int)world2grid(player->pos.y) - (int)world2grid(drop->pos.y);
    if (dy < 1)
        dy = 1;

    drop->speed.x = adjust(dx * EMPRESS_HONEY_SPEED / dy, -EMPRESS_HONEY_SPEED, EMPRESS_HONEY_SPEED);
}

// brood of given type centered on her, "dy" grid rows from her top, unless
// there's plenty of them already
static void empress_lay(hsObject obj, hcsObjType type, unsigned char max, int dy) {

    hsObject brood = NULL;
    unsigned char count = 0;

    while ((brood = objpool_next(brood)) != NULL)
        if (brood->type == type && !(brood->flags & OBJ_FLG_DYING))
            count++;

    if (count >= max)
        return;

    // added inactive, as it's spawned from within the objects' tick loop
    if ((brood = objpool_alloc_inactive(type)) == NULL)
        return;

    brood->pos.x = obj->pos.x + grid2world((obj->physical->dim.x - type->physical->dim.x) / 2);
    brood->pos.y = adjust((int)obj->pos.y + grid2world(dy), 0, grid2world(VIEWGRID_HEIGHT - 9));
}

// horizontal distance from her middle to the player's middle
static int empress_to_player(hsObject obj) {

    if (player == NULL)
        return 0;

    return ((int)player->pos.x + grid2world(player->physical->dim.x) / 2) - ((int)obj->pos.x + grid2world(obj->physical->dim.x) / 2);
}

// her top row when diving down to sting
static t_pos_world empress_floor(hsObject obj) {

    if (player == NULL)
        return grid2world(VIEWGRID_HEIGHT - 9);

    return grid2world(world2grid(player->pos.y) - EMPRESS_STING_GAP - obj->physical->dim.y);
}

static void empress_lasers(hsObject obj) {

    unsigned char i;

    for (i = 0; i < dimof(turret_grchkrx_empress_sting); i++)
        fire_turret(obj, &turret_grchkrx_empress_sting[i]);
}

static void empress_sting(hsObject obj) {

    empress_lasers(obj);

    obj->state[0] = EMPRESS_ST_STING;
    obj->ttl = EMPRESS_STING_TICKS;
    obj->speed.x = 0;
    obj->speed.y = 0;
}

// sideways direction (state[2]) turned back at the view's edges
static void empress_bounce(hsObject obj) {

    if (OBJ_IS_LEFT(obj) && obj->state[2] < 0)
        obj->state[2] = 1;
    else
    if (OBJ_IS_RIGHT(obj) && obj->state[2] > 0)
        obj->state[2] = -1;
}

void cb_empress_behave(hsObject obj) {

    unsigned char t;
    int dx;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    if (obj->state[0] == 0) {

        obj->state[0] = EMPRESS_ST_DRIFT;
        obj->state[2] = (rand() & 1) ? 1 : -1;
    }

    // wings torn off at half hp - drop whatever she's doing and go down
    if (obj->state[3] == 0 && obj->damage_total * 2 >= obj->type->hp) {

        obj->state[3] = 1;
        obj->state[0] = EMPRESS_ST_DESCEND;
    }

    // attack loop tick
    t = (unsigned char)obj->state[1];

    empress_frame(obj, EMPRESS_FRM_NORMAL);

    switch (obj->state[0]) {

        case EMPRESS_ST_DRIFT:

            empress_bounce(obj);
            obj->speed.y = 0;

            // flinching - darting away, still red from the hit
            if (obj->ttl > EMPRESS_FLINCH_COOLDOWN - EMPRESS_FLINCH_TICKS) {

                empress_frame(obj, EMPRESS_FRM_HIT);
                obj->speed.x = obj->state[2] * EMPRESS_FLINCH_SPEED;
            }
            else {

                // now and then pause or change her mind
                if ((rand() & 31) == 0)
                    obj->state[2] = 1 - (rand() % 3);

                obj->speed.x = obj->state[2] * EMPRESS_DRIFT_SPEED;
            }

            empress_fan(obj, t);

            if (t >= EMPRESS_HONEY_AT && t < EMPRESS_HONEY_AT + 3 * EMPRESS_HONEY_BURST && (t - EMPRESS_HONEY_AT) % 3 == 0)
                honey_aimed(obj, &turret_grchkrx_empress_honey);
            else
            if (t >= EMPRESS_EGG_AT - 8 && t < EMPRESS_EGG_AT && (t & 1))
                empress_frame(obj, EMPRESS_FRM_FLASH);
            else
            if (t == EMPRESS_EGG_AT)
                empress_lay(obj, &ot_grchkrx_larva, EMPRESS_MAX_LARVAE, phy_grchkrx_empress.dim.y);

            obj->state[1] = (t + 1 >= EMPRESS_CYCLE) ? 0 : t + 1;
            break;

        // flashing while tearing her wings off and sinking to the sweep row
        case EMPRESS_ST_DESCEND:

            if (t & 1)
                empress_frame(obj, EMPRESS_FRM_FLASH);
            obj->state[1] = t + 1;

            obj->speed.x = 0;
            obj->speed.y = EMPRESS_DESCEND_SPEED;

            if (obj->pos.y >= grid2world(EMPRESS_TORN_ROW)) {

                obj->pos.y = grid2world(EMPRESS_TORN_ROW);
                obj->speed.y = 0;
                obj->state[0] = EMPRESS_ST_SWEEP;
                obj->state[1] = 0;
                if (obj->state[2] == 0)
                    obj->state[2] = 1;
            }
            break;

        // side to side with the royal fan and laser spreads after
        // it, laying a stinger, then
        // off hunting; from here till climbing back state[1] counts the stings
        // left to chain along the floor
        case EMPRESS_ST_SWEEP:

            empress_bounce(obj);
            obj->speed.x = obj->state[2] * EMPRESS_SWEEP_SPEED;

            empress_fan(obj, t - EMPRESS_SWEEP_FAN_AT);

            if (t == EMPRESS_LASERS_AT || t == EMPRESS_LASERS_AT2)
                empress_lasers(obj);
            else
            if (t >= EMPRESS_BROOD_AT - 8 && t < EMPRESS_BROOD_AT && (t & 1))
                empress_frame(obj, EMPRESS_FRM_FLASH);
            else
            if (t == EMPRESS_BROOD_AT)
                empress_lay(obj, &ot_grchkrx_stinger, EMPRESS_MAX_STINGERS, -3);

            if (t >= EMPRESS_HUNT_AT) {

                obj->state[0] = EMPRESS_ST_HUNT;
                obj->state[1] = 1 + rand() % EMPRESS_STING_CHAIN;
                obj->ttl = EMPRESS_HUNT_TICKS;
            }
            else
                obj->state[1] = t + 1;
            break;

        case EMPRESS_ST_HUNT:

            dx = empress_to_player(obj);

            if (abs(dx) < grid2world(1) || obj->ttl == 0) {

                obj->state[0] = EMPRESS_ST_AIM;
                obj->ttl = EMPRESS_AIM_TICKS;
                obj->speed.x = 0;
            }
            else
                obj->speed.x = adjust(dx / 4, -EMPRESS_HUNT_SPEED, EMPRESS_HUNT_SPEED);
            break;

        // column locked, long warning flash
        case EMPRESS_ST_AIM:

            if (obj->ttl & 1)
                empress_frame(obj, EMPRESS_FRM_FLASH);

            if (obj->ttl == 0) {

                obj->state[0] = EMPRESS_ST_DIVE;
                obj->speed.y = EMPRESS_DIVE_SPEED;
            }
            break;

        case EMPRESS_ST_DIVE:

            if (obj->pos.y >= empress_floor(obj)) {

                obj->pos.y = empress_floor(obj);
                empress_sting(obj);
            }
            break;

        // rest after the sting, then chain another one or climb back
        case EMPRESS_ST_STING:

            if (obj->ttl == 0) {

                if (obj->state[1] > 0) {

                    obj->state[1]--;
                    obj->state[0] = EMPRESS_ST_SLIDE;
                    obj->ttl = EMPRESS_SLIDE_TICKS;
                }
                else {

                    obj->state[0] = EMPRESS_ST_CLIMB;
                    obj->speed.y = -EMPRESS_CLIMB_SPEED;
                }
            }
            break;

        // sideways after the player, keeping the height
        case EMPRESS_ST_SLIDE:

            dx = empress_to_player(obj);

            if (abs(dx) < grid2world(1) || obj->ttl == 0) {

                obj->state[0] = EMPRESS_ST_FLOOR_AIM;
                obj->ttl = EMPRESS_FLOOR_AIM_TICKS;
                obj->speed.x = 0;
            }
            else
                obj->speed.x = adjust(dx / 4, -EMPRESS_SLIDE_SPEED, EMPRESS_SLIDE_SPEED);
            break;

        // column locked again, short warning flash
        case EMPRESS_ST_FLOOR_AIM:

            if (obj->ttl & 1)
                empress_frame(obj, EMPRESS_FRM_FLASH);

            if (obj->ttl == 0)
                empress_sting(obj);
            break;

        case EMPRESS_ST_CLIMB:

            if (obj->pos.y <= grid2world(EMPRESS_TORN_ROW)) {

                obj->pos.y = grid2world(EMPRESS_TORN_ROW);
                obj->speed.y = 0;
                obj->state[0] = EMPRESS_ST_SWEEP;
                obj->state[1] = 0;
            }
            break;
    }
}

void cb_empress_die(hsObject obj) {

    obj->physical = &phy_grchkrx_empress_dying;
    obj->ttl = 10;
    obj->speed.x = 0;
    obj->speed.y = 1;
}

void cb_empress_hit(hsObject obj) {

    empress_frame(obj, EMPRESS_FRM_HIT);

    // wings on and flinch cooled down - start darting away from the player's side
    if (obj->state[0] == EMPRESS_ST_DRIFT && obj->ttl == 0) {

        obj->ttl = EMPRESS_FLINCH_COOLDOWN;
        if (player != NULL)
            obj->state[2] = (player->pos.x + grid2world(player->physical->dim.x) / 2 < obj->pos.x + grid2world(obj->physical->dim.x) / 2) ? 1 : -1;
    }
}

// brood pod drifts from side to side, sinking and rising as it pleases
// (lower once cracked), the comb itself is armour soaking up shots;
// only it's heart takes damage (passed on to the pod, showing the hp bar),
// but it's plugged with wax most of the time - the longer the more brood
// cells are open; it opens to spit a burst of aimed honey and closes again;
// open cells drop larvae, shot ones get sealed with wax, but the grub chews
// it's way out again after a while; at half hp the comb cracks, all cells
// burst open at once and everything gets faster
#define POD_HP                          160
#define POD_DRIFT_SPEED                 6       // world units per behaviour tick
#define POD_RAGE_SPEED                  10
#define POD_RISE_SPEED                  3       // up and down, world units per behaviour tick
#define POD_RAGE_RISE_SPEED             5
#define POD_TOP_ROW                     1       // leaving the row above for the hp bar
#define POD_BOTTOM_ROW                  14      // lowest top row, cells hanging 3 rows lower
#define POD_RAGE_BOTTOM_ROW             22
#define POD_MAX_BROOD                   8       // larvae and bees around, cells hold back beyond this
#define POD_CELL_HP                     18
#define POD_CELL_BROOD_TICKS            72      // between larvae from an open cell, plus up to 31 random
#define POD_RAGE_BROOD_TICKS            48
#define POD_CELL_FULL_TICKS             8       // bulging and flashing before dropping a larva
#define POD_CELL_SEALED_TICKS           160
#define POD_CELL_CHEW_TICKS             24      // grub peeking through the wax before breaking out
#define POD_HEART_PLUG_TICKS            40      // plugged, plus POD_HEART_PLUG_PER_CELL for every open cell
#define POD_HEART_PLUG_PER_CELL         12
#define POD_RAGE_PLUG_TICKS             24
#define POD_RAGE_PLUG_PER_CELL          8
#define POD_HEART_OPENING_TICKS         8
#define POD_HEART_OPEN_TICKS            40
#define POD_HONEY_BURST                 3       // drops, 4 ticks apart right after opening
#define POD_RAGE_HONEY_BURST            5

#define POD_ST_CALM                     1
#define POD_ST_RAGE                     2

#define POD_CELL_ST_OPEN                0
#define POD_CELL_ST_SEALED              1

#define POD_HEART_ST_PLUGGED            0
#define POD_HEART_ST_OPENING            1
#define POD_HEART_ST_OPEN               2

// parts' columns under the pod by slot (state[2]) - four cells and the heart
#define POD_SLOT_HEART                  4
static const unsigned char pod_slot_x[5] = { 0, 4, 12, 16, 7 };

// parts never die on their own, cells get sealed and the heart plugged
#define POD_PART_HP                     1000

// cells and heart: [0] - POD_CELL_ST_* / POD_HEART_ST_*, [1] - pod's id, [2] - slot
void cb_pod_cell_hit(hsObject obj) {

    if (obj->state[0] == POD_CELL_ST_SEALED)
        obj->damage_now = 0;
    else
        obj->physical = &phy_grchkrx_cell_hit;
}

void cb_pod_heart_hit(hsObject obj) {

    if (obj->state[0] != POD_HEART_ST_OPEN)
        obj->damage_now = 0;
    else
        obj->physical = &phy_grchkrx_heart_hit;
}

static const sObjType ot_grchkrx_pod_cell = {
    &phy_grchkrx_cell_0,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    POD_PART_HP,
    NULL,
    NULL,
    cb_pod_cell_hit,
    NULL
};

static const sObjType ot_grchkrx_pod_heart = {
    &phy_grchkrx_heart_plug,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    POD_PART_HP,
    NULL,
    NULL,
    cb_pod_heart_hit,
    NULL
};

#define POD_IS_PART(obj, p)             (((p)->type == &ot_grchkrx_pod_cell || (p)->type == &ot_grchkrx_pod_heart) && (p)->state[1] == (obj)->state[1] && !((p)->flags & OBJ_FLG_DYING))

// id shared by a pod and it's parts
static unsigned char pod_next_id;

static void pod_spawn_part(hsObject obj, hcsObjType type, unsigned char slot, unsigned int ttl) {

    hsObject part;

    // added inactive, as it's spawned from within the objects' tick loop
    if ((part = objpool_alloc_inactive(type)) == NULL)
        return;

    part->state[1]  = obj->state[1];
    part->state[2]  = slot;
    part->ttl       = ttl;
}

static void pod_init(hsObject obj) {

    unsigned char slot;

    if (++pod_next_id == 0)
        pod_next_id = 1;

    obj->state[0] = POD_ST_CALM;
    obj->state[1] = pod_next_id;
    obj->state[2] = obj->pos.x < grid2world(VIEWGRID_WIDTH / 2) ? 1 : -1;
    obj->state[3] = 1;

    // cells start dropping one after another
    for (slot = 0; slot < POD_SLOT_HEART; slot++)
        pod_spawn_part(obj, &ot_grchkrx_pod_cell, slot, 24 + slot * 20);

    pod_spawn_part(obj, &ot_grchkrx_pod_heart, POD_SLOT_HEART, POD_HEART_PLUG_TICKS);
}

// larvae and bees around, hatched or not
static unsigned char pod_brood(void) {

    hsObject obj = NULL;
    unsigned char count = 0;

    while ((obj = objpool_next(obj)) != NULL)
        if ((obj->type == &ot_grchkrx_larva || obj->type == &ot_grchkrx_bee) && !(obj->flags & OBJ_FLG_DYING))
            count++;

    return count;
}

static unsigned char pod_open_cells(hsObject obj) {

    hsObject cell = NULL;
    unsigned char count = 0;

    while ((cell = objpool_next(cell)) != NULL)
        if (POD_IS_PART(obj, cell) && cell->type == &ot_grchkrx_pod_cell && cell->state[0] == POD_CELL_ST_OPEN)
            count++;

    return count;
}

// slowly from side to side, now and then changing it's mind; up and down
// (state[3]) between the top and the bottom row, now and then hovering
static void pod_drift(hsObject obj) {

    int x, y, max;
    unsigned char rage = obj->state[0] == POD_ST_RAGE;

    max = grid2world(VIEWGRID_WIDTH - obj->physical->dim.x);

    if ((rand() & 63) == 0)
        obj->state[2] = -obj->state[2];

    x = (int)obj->pos.x + obj->state[2] * (rage ? POD_RAGE_SPEED : POD_DRIFT_SPEED);
    if (x <= 0) {

        x = 0;
        obj->state[2] = 1;
    }
    else
    if (x >= max) {

        x = max;
        obj->state[2] = -1;
    }

    obj->pos.x = x;

    if ((rand() & 31) == 0)
        obj->state[3] = 1 - (rand() % 3);

    max = grid2world(rage ? POD_RAGE_BOTTOM_ROW : POD_BOTTOM_ROW);

    y = (int)obj->pos.y + obj->state[3] * (rage ? POD_RAGE_RISE_SPEED : POD_RISE_SPEED);
    if (y <= grid2world(POD_TOP_ROW)) {

        y = grid2world(POD_TOP_ROW);
        obj->state[3] = 1;
    }
    else
    if (y >= max) {

        y = max;
        obj->state[3] = -1;
    }

    obj->pos.y = y;
}

static void pod_cell(hsObject obj, hsObject cell) {

    hsObject larva;

    switch (cell->state[0]) {

        case POD_CELL_ST_OPEN:

            // shot enough - sealed with wax
            if (cell->damage_total >= POD_CELL_HP) {

                cell->state[0]      = POD_CELL_ST_SEALED;
                cell->damage_total  = 0;
                cell->ttl           = POD_CELL_SEALED_TICKS;
                cell->physical      = &phy_grchkrx_cell_sealed;
                break;
            }

            if (cell->ttl <= POD_CELL_FULL_TICKS && (cell->ttl & 1))
                cell->physical = &phy_grchkrx_cell_full;
            else
                cell->physical = (cell->ttl & 4) ? &phy_grchkrx_cell_1 : &phy_grchkrx_cell_0;

            if (cell->ttl > 0)
                break;

            cell->ttl = (obj->state[0] == POD_ST_RAGE ? POD_RAGE_BROOD_TICKS : POD_CELL_BROOD_TICKS) + (rand() & 31);

            // drop a larva right under the cell, unless there's plenty of brood
            if (pod_brood() >= POD_MAX_BROOD || (larva = objpool_alloc_inactive(&ot_grchkrx_larva)) == NULL)
                break;

            larva->pos.x = cell->pos.x > grid2world(1) ? cell->pos.x - grid2world(1) : 0;
            larva->pos.y = cell->pos.y + grid2world(1);
            break;

        case POD_CELL_ST_SEALED:

            cell->physical = (cell->ttl <= POD_CELL_CHEW_TICKS && (cell->ttl & 2)) ? &phy_grchkrx_cell_chewed : &phy_grchkrx_cell_sealed;

            // chewed through, the grub drops out soon
            if (cell->ttl == 0) {

                cell->state[0]      = POD_CELL_ST_OPEN;
                cell->damage_total  = 0;
                cell->ttl           = POD_CELL_FULL_TICKS + 4;
            }
            break;
    }
}

static void pod_heart(hsObject obj, hsObject heart) {

    unsigned char t, burst;

    switch (heart->state[0]) {

        case POD_HEART_ST_PLUGGED:

            heart->physical = &phy_grchkrx_heart_plug;

            if (heart->ttl == 0) {

                heart->state[0] = POD_HEART_ST_OPENING;
                heart->ttl      = POD_HEART_OPENING_TICKS;
            }
            break;

        case POD_HEART_ST_OPENING:

            heart->physical = (heart->ttl & 1) ? &phy_grchkrx_heart_flash : &phy_grchkrx_heart_plug;

            if (heart->ttl == 0) {

                heart->state[0] = POD_HEART_ST_OPEN;
                heart->ttl      = POD_HEART_OPEN_TICKS;
            }
            break;

        case POD_HEART_ST_OPEN:

            // the heart is the pod's only weak spot
            obj->damage_total += heart->damage_total;
            heart->damage_total = 0;

            heart->physical = (heart->ttl & 4) ? &phy_grchkrx_heart_1 : &phy_grchkrx_heart_0;

            // already counted down once since opening
            t       = POD_HEART_OPEN_TICKS - 1 - heart->ttl;
            burst   = obj->state[0] == POD_ST_RAGE ? POD_RAGE_HONEY_BURST : POD_HONEY_BURST;
            if (!(t & 3) && t / 4 < burst)
                honey_aimed(heart, &turret_grchkrx_heart_honey);

            // plugged the longer the more cells are open
            if (heart->ttl == 0) {

                heart->state[0] = POD_HEART_ST_PLUGGED;
                if (obj->state[0] == POD_ST_RAGE)
                    heart->ttl = POD_RAGE_PLUG_TICKS + POD_RAGE_PLUG_PER_CELL * pod_open_cells(obj);
                else
                    heart->ttl = POD_HEART_PLUG_TICKS + POD_HEART_PLUG_PER_CELL * pod_open_cells(obj);
            }
            break;
    }
}

void cb_pod_behave(hsObject obj) {

    hsObject part;

    if (obj->flags & OBJ_FLG_DYING)
        return;

    // first tick, spawn the parts
    if (obj->state[0] == 0)
        pod_init(obj);

    // comb cracks at half hp - every cell bursts open, one right after another
    if (obj->state[0] == POD_ST_CALM && obj->damage_total * 2 >= obj->type->hp) {

        obj->state[0] = POD_ST_RAGE;

        part = NULL;
        while ((part = objpool_next(part)) != NULL) {

            if (!POD_IS_PART(obj, part) || part->type != &ot_grchkrx_pod_cell)
                continue;

            part->state[0]      = POD_CELL_ST_OPEN;
            part->damage_total  = 0;
            part->ttl           = POD_CELL_FULL_TICKS + part->state[2] * 3;
        }
    }

    obj->physical = obj->state[0] == POD_ST_RAGE ? &phy_grchkrx_pod_cracked : &phy_grchkrx_pod;

    pod_drift(obj);

    // parts hang right under the comb
    part = NULL;
    while ((part = objpool_next(part)) != NULL) {

        if (!POD_IS_PART(obj, part))
            continue;

        part->pos.x = obj->pos.x + grid2world(pod_slot_x[part->state[2]]);
        part->pos.y = obj->pos.y + grid2world(obj->physical->dim.y);

        if (part->type == &ot_grchkrx_pod_heart)
            pod_heart(obj, part);
        else
            pod_cell(obj, part);
    }
}

void cb_pod_die(hsObject obj) {

    hsObject part;

    obj->physical = &phy_grchkrx_pod_dying;
    obj->ttl = 10;
    obj->speed.y = 1;

    // parts fall apart with it
    part = NULL;
    while ((part = objpool_next(part)) != NULL) {

        if (!POD_IS_PART(obj, part))
            continue;

        part->flags     |= OBJ_FLG_DYING;
        part->physical  = part->type == &ot_grchkrx_pod_heart ? &phy_grchkrx_heart_dying : &phy_grchkrx_cell_dying;
        part->ttl       = 4;
    }
}

// the comb is armour, only the heart's hits count
void cb_pod_hit(hsObject obj) {

    obj->damage_now = 0;
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
    18,
    cb_stinger_behave,
    cb_stinger_die,
    cb_stinger_hit,
    NULL
};

const sObjType ot_grchkrx_empress = {
    &phy_grchkrx_empress,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_HPBAR,
    EMPRESS_HP,
    cb_empress_behave,
    cb_empress_die,
    cb_empress_hit,
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

const sObjType ot_grchkrx_pod = {
    &phy_grchkrx_pod,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_HPBAR,
    POD_HP,
    cb_pod_behave,
    cb_pod_die,
    cb_pod_hit,
    NULL
};
