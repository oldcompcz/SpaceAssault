#ifndef __DATA_H
#define __DATA_H

#include "objpool.h"

#define dimof(x) (sizeof(x) / sizeof(x[0]))

#define TURRET_NONE                     { { 0, 0 }, { 0, 0 }, NULL }
#define TURRETS_NONE                    { TURRET_NONE, TURRET_NONE, TURRET_NONE, TURRET_NONE }
#define TURRET_GRID(x, y, dx, dy, t)    { { grid2world(x), grid2world(y) }, { (dx), (dy) }, (t) }

hsObject fire_turret(hsObject obj, hcsTurret turret);
int adjust(int value, int min, int max);
void cb_deal_die(hsObject bullet, hsObject target);

extern const sTurret turret_player_bullet;
extern const sTurret turret_player_megablast;
extern const sTurret turret_player_lleft;
extern const sTurret turret_player_lright;
extern const sTurret turret_player_llleft;
extern const sTurret turret_player_llright;

extern const sObjType ot_player;
extern const sObjType ot_btn_hitme;
extern const sObjType ot_supply;
extern const sObjType ot_foe_bullet;
extern const sObjType ot_foe_laser;
extern const sObjType ot_foe_ball;
extern const sObjType ot_octo;
extern const sObjType ot_flank;
extern const sObjType ot_grchkrx_bee;
extern const sObjType ot_grchkrx_queen;
extern const sObjType ot_alien_bible;

#define OCTO_ST_CLW_GO_RIGHT            0
#define OCTO_ST_CLW_GO_DOWN             1
#define OCTO_ST_CLW_GO_LEFT             2
#define OCTO_ST_CLW_GO_UP               3

#define FLANK_GO_LEFT_DOWN              0
#define FLANK_GO_RIGHT_UP               1
#define FLANK_GO_RIGHT_DOWN             2
#define FLANK_GO_LEFT_UP                3

#define PHYSICAL_1X1(ascii, attr)       { { 1, 1 }, { (ascii), (attr) } }

// ---------------------------------------------------------------------------
// scenario helpers
// ---------------------------------------------------------------------------

void scpt_emit_at_pos(hcsScenarioPoint scpoint, unsigned char repeat);

#define SCPOINT_SUB_TEXT(t, c)      (t), (c)
#define SCPOINT_SUB_TEXT_NONE       NULL, 0

//                                          type,                       delay,  repeat, tick,   text,                   emit,   pos
#define SCPOINT_MACRO_TEXT(t, c, d)         { SCPOINT_TYPE_NONE,        (d),    0,      NULL,   SCPOINT_SUB_TEXT(t, c), NULL,   { 0, 0 } }
#define SCPOINT_MACRO_DELAY(d)              { SCPOINT_TYPE_NONE,        (d),    0,      NULL,   SCPOINT_SUB_TEXT_NONE,  NULL,   { 0, 0 } }
#define SCPOINT_MACRO_WAIT_DEAD(d)          { SCPOINT_TYPE_WAIT_DEAD,   (d),    1,      NULL,   SCPOINT_SUB_TEXT_NONE,  NULL,   { 0, 0 } }
#define SCPOINT_MACRO_WAIT_DEAD_TEXT(t, c)  { SCPOINT_TYPE_WAIT_DEAD,   1,      1,      NULL,   SCPOINT_SUB_TEXT(t, c), NULL,   { 0, 0 } }
#define SCPOINT_MACRO_END                   { SCPOINT_TYPE_END,         1,      1,      NULL,   SCPOINT_SUB_TEXT_NONE,  NULL,   { 0, 0 } }

#define SCPOINT_EPOS(x, y)                  { grid2world(x), grid2world(y) }
#define SCPOINT_EPOS_LEFT(y)                { 0, grid2world(y) }
#define SCPOINT_EPOS_RIGHT(y)               { -1, grid2world(y) }

#endif
