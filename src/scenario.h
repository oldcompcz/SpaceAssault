#ifndef __SCENARIO_H
#define __SCENARIO_H

#include "shooter.h"

// ---------------------------------------------------------------------------
// scenario helpers
// ---------------------------------------------------------------------------

void scpt_emit_at_pos(hcsScenarioPoint scpoint, unsigned char repeat);
void scpt_emit_random_x(hcsScenarioPoint scpoint, unsigned char repeat);
void scpt_emit_octo(hcsScenarioPoint scpoint, unsigned char repeat);
void scpt_emit_flank_left(hcsScenarioPoint scpoint, unsigned char repeat);
void scpt_emit_flank_right(hcsScenarioPoint scpoint, unsigned char repeat);
void scpt_emit_octo_right(hcsScenarioPoint scpoint, unsigned char repeat);
void scpt_emit_mirrored(hcsScenarioPoint scpoint, unsigned char repeat);

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
