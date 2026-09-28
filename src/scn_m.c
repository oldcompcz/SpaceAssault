#include <stdlib.h>

#include "shooter.h"
#include "objpool.h"
#include "data.h"
#include "scenario.h"

// ---------------------------------------------------------------------------
// scenario selection menu - a "hit me" button under the name of each
// scenario, the one shot down gets played
// ---------------------------------------------------------------------------

extern const sScenarioPoint g_scenario_original[];
extern const sScenarioPoint g_scenario_honey[];

// scenario picked in the menu, main loop jumps to it (and clears it)
hcsScenarioPoint g_scenario_next = NULL;

typedef struct sMenuEntry {

    hcsScenarioPoint        entry;
    t_pos_grid              x;              // button position in the view

} sMenuEntry;

#define MENU_BUTTON_Y                   30

// buttons line up with the names in text_menu (screen x is view x + 1)
static const sMenuEntry menu_entries[] = {
    { g_scenario_original,  12 },
    { g_scenario_honey,     41 },
};

static const sDisplayText text_menu[] = {
    { { 6, 6 },   0x01, "   __  __  __  __  __     __  __  __  __         __ " },
    { { 6, 7 },   0x09, "  /_  /_/ /_/ /   /_     /_/ /_  /_  /_/ / / /   /  " },
    { { 6, 8 },   0x08, " __/ /   / / /_  /_     / / __/ __/ / / /_/ /_  /   " },
    { { 18, 14 }, 0x07, "Roman Hocke (c) 2017-2026" },
    { { 23, 22 }, 0x07, "Select scenario" },
    { { 12, 27 }, 0x0c, "ORIGINAL" },
    { { 41, 27 }, 0x0e, "HONEYCOMB" },
};

static void cb_die_menu_button(hsObject obj) {

    // a single laser volley may take down more buttons at once
    if (g_scenario_next == NULL)
        g_scenario_next = menu_entries[obj->state[0]].entry;
}

static const sObjType ot_btn_menu = {
    &phy_hitme,
    OBJTYPE_NAT_FOE_OBJ,
    OBJTYPE_FLG_NONE,
    1,
    NULL,
    cb_die_menu_button,
    NULL,
    NULL
};

#pragma argsused
static void scpt_emit_menu(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject emit;
    unsigned char i;

    for (i = 0; i < dimof(menu_entries); i++) {

        if ((emit = objpool_alloc(&ot_btn_menu)) == NULL)
            return;

        emit->pos.x     = grid2world(menu_entries[i].x);
        emit->pos.y     = grid2world(MENU_BUTTON_Y);
        emit->state[0]  = i;
    }
}

// logo lit or dark for d + 1 frames
#define LOGO_ON(d)                      SCPOINT_MACRO_TEXT_FRAMES(text_menu, 3, (d))
#define LOGO_OFF(d)                     SCPOINT_MACRO_TEXT_FRAMES(text_menu, 0, (d))

const sScenarioPoint g_scenario_menu[] = {

    SCPOINT_MACRO_DELAY(1),

    // logo flashes in like a starting strip light - one decent on-off,
    // few quick flickers, then on with a single short outage and on for good
    LOGO_ON(8),
    LOGO_OFF(23),
    LOGO_ON(2),
    LOGO_OFF(3),
    LOGO_ON(1),
    LOGO_OFF(5),
    LOGO_ON(2),
    LOGO_OFF(2),
    LOGO_ON(1),
    LOGO_OFF(8),
    LOGO_ON(29),
    LOGO_OFF(3),
    LOGO_ON(50),

    SCPOINT_MACRO_TEXT_FRAMES(text_menu, 4, 100),
    SCPOINT_MACRO_TEXT_FRAMES(text_menu, 5, 80),

    // stays here until a button is shot, then the main loop jumps away
    { SCPOINT_TYPE_NONE, 1, 0, scpt_emit_menu, SCPOINT_SUB_TEXT(text_menu, dimof(text_menu)), NULL, { 0, 0 } },
    SCPOINT_MACRO_WAIT_DEAD_TEXT(text_menu, dimof(text_menu)),
    SCPOINT_MACRO_END
};
