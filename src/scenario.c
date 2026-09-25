#include <stdlib.h>

#include "shooter.h"
#include "objpool.h"
#include "data.h"
#include "scenario.h"

// ---------------------------------------------------------------------------
// scenario callbacks
// ---------------------------------------------------------------------------

#pragma argsused
void scpt_emit_at_pos(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject emit;
    t_pos_world x;

    if ((emit = objpool_alloc(scpoint->emit_objtype)) == NULL)
        return;
        
    emit->pos.x = scpoint->emit_pos.x;
    emit->pos.y = scpoint->emit_pos.y;
    
    x = grid2world(VIEWGRID_WIDTH - emit->physical->dim.x);
    if (emit->pos.x > x)
        emit->pos.x = x;
}

#pragma argsused
void scpt_emit_random_x(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject emit;

    if ((emit = objpool_alloc(scpoint->emit_objtype)) == NULL)
        return;
        
    emit->pos.x = grid2world(rand() % (VIEWGRID_WIDTH - emit->physical->dim.x));
    emit->pos.y = scpoint->emit_pos.y;
}

#pragma argsused
void scpt_emit_octo(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject obj;

    if ((obj = objpool_alloc(&ot_octo)) == NULL)
        return;
    
    obj->pos.x = scpoint->emit_pos.x;
    obj->pos.y = scpoint->emit_pos.y;
    
    octo_init(obj, OCTO_ST_CLW_GO_RIGHT);
}

#pragma argsused
void scpt_emit_flank_left(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject obj;

    if ((obj = objpool_alloc(&ot_flank)) == NULL)
        return;
    
    obj->pos.x = scpoint->emit_pos.x;
    obj->pos.y = scpoint->emit_pos.y;
    
    flank_init(obj, FLANK_GO_LEFT_DOWN);
}

#pragma argsused
void scpt_emit_flank_right(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject obj;

    if ((obj = objpool_alloc(&ot_flank)) == NULL)
        return;
    
    obj->pos.x = scpoint->emit_pos.x;
    obj->pos.y = scpoint->emit_pos.y;
    
    flank_init(obj, FLANK_GO_RIGHT_DOWN);
}

// octo entering from the right side, starting at the bottom edge of it's
// clockwise loop (so it forms a second "carousel" above the emit position)
#pragma argsused
void scpt_emit_octo_right(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject obj;

    if ((obj = objpool_alloc(&ot_octo)) == NULL)
        return;

    octo_init(obj, OCTO_ST_CLW_GO_LEFT);

    obj->pos.x      = OBJ_POS_RIGHT(obj);
    obj->pos.y      = scpoint->emit_pos.y;
    obj->speed.x    = -5;
}

// emits pair of objects, second one mirrored around vertical axis of the view
#pragma argsused
void scpt_emit_mirrored(hcsScenarioPoint scpoint, unsigned char repeat) {

    hsObject emit;
    unsigned char i;

    for (i = 0; i < 2; i++) {

        if ((emit = objpool_alloc(scpoint->emit_objtype)) == NULL)
            return;

        emit->pos.y = scpoint->emit_pos.y;

        if (i == 0)
            emit->pos.x = scpoint->emit_pos.x;
        else
            emit->pos.x = grid2world(VIEWGRID_WIDTH - emit->physical->dim.x) - scpoint->emit_pos.x;
    }
}
