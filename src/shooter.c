#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "shooter.h"
#include "screen.h"
#include "input.h"
#include "objpool.h"

// too lazy to learn TLINK :-)
//#include "screen.c"
//#include "input.c"
//#include "objpool.c"
//#include "d_gen.c"
//#include "d_grch.c"
//#include "d_octo.c"
//#include "d_bible.c"
//#include "d_supply.c"
//#include "d_flank.c"
//#include "data.c"

#define VIEWGRID_SCREEN_X               1
#define VIEWGRID_SCREEN_Y               0

#define BAR_LEFT                        (VIEWGRID_WIDTH + 3)

// player's hp bar on the bottom screen line, spanning the playfield under the ship
#define HPBAR_Y                         49
#define HPBAR_LABEL_WIDTH               3       // "HP "
#define HPBAR_LEFT                      (VIEWGRID_SCREEN_X + HPBAR_LABEL_WIDTH)
#define HPBAR_WIDTH                     (VIEWGRID_WIDTH - HPBAR_LABEL_WIDTH)
#define HPBAR_FLASH_FRAMES              6       // white flash after taking a hit

extern const sScenarioPoint g_scenario_original[];

hsObject g_map[VIEWGRID_HEIGHT][VIEWGRID_WIDTH][2]; // 0 is ally, 1 is foe
hsObject player, shield;
unsigned char player_weapon_delay;
hcsScenarioPoint scpoint;
unsigned char scpoint_timer;
unsigned char scpoint_repeat;
hcsDisplayText show_text_first;
unsigned char show_text_count;
unsigned char paused;

typedef struct sScenarioInfo {

    const char *alias;
    hcsScenarioPoint entry;

} sScenarioInfo, *hsScenarioInfo;
typedef const sScenarioInfo *hcsScenarioInfo;

// scenarios selectable by the command line argument (case insensitive),
// "start.exe" alone (or with unknown argument) plays the main one
static const sScenarioInfo scenarios[] = {
    { "1",      g_scenario_original },
};

/*
static FILE *fp = NULL;

void xlog(char *msg) {

    if (fp == NULL)
        fp = fopen("./log.txt", "w");
        
    if (fp != NULL) {
    
        fprintf(fp, "%s\n", msg);
        fflush(fp);
    }
}
*/
#define xlog(x)

static const sDisplayText text_fail[] = {
    { { 26, 10 }, 0x07, "YOU FAILED" },
};

int adjust(int value, int min, int max) {

    if (value < min)
        return min;
        
    if (value > max)
        return max;
        
    return value;
}

hsObject fire_turret(hsObject obj, hcsTurret turret) {

    hsObject bullet;
            
    if ((bullet = objpool_alloc(turret->type)) != NULL) {
    
        bullet->pos.x = obj->pos.x + turret->pos.x;
        bullet->pos.y = obj->pos.y + turret->pos.y;
        bullet->speed.x = turret->speed.x;
        bullet->speed.y = turret->speed.y;
    }

    return bullet;
}

#define PERIOD_1PERSEC          (!(cycle & 63))
#define PERIOD_2PERSEC          (!(cycle & 31))
#define PERIOD_4PERSEC          (!(cycle & 15))
#define PERIOD_8PERSEC          (!(cycle & 7))
#define PERIOD_16PERSEC         (!(cycle & 3))

// whole object lies within the playfield; objects spawned during the tick
// (turret shots, megablast fragments, summoned minions) weren't clamped yet
// and may be off the grid, even wrapped around to huge unsigned positions
static unsigned char obj_in_view(hsObject obj) {

    return (world2grid(obj->pos.x) + obj->physical->dim.x) <= VIEWGRID_WIDTH && (world2grid(obj->pos.y) + obj->physical->dim.y) <= VIEWGRID_HEIGHT;
}

// hp bar in the row above objects of types asking for it by OBJTYPE_FLG_HPBAR;
// missing hp is dark, any hp left shows at least a bit
static void draw_hpbar(hsObject obj) {

    hcsObjType otype = obj->type;
    unsigned int left, start;
    unsigned char w, filled, color;

    if (!(otype->flags & OBJTYPE_FLG_HPBAR))
        return;

    if (obj->flags & (OBJ_FLG_HIDDEN | OBJ_FLG_DYING) || obj->damage_total >= otype->hp)
        return;

    if (world2grid(obj->pos.y) == 0 || !obj_in_view(obj))
        return;

    w       = obj->physical->dim.x;
    left    = otype->hp - obj->damage_total;
    filled  = (unsigned char)(((unsigned long)left * w + otype->hp - 1) / otype->hp);
    start   = screen_offset_xy(world2grid(obj->pos.x) + VIEWGRID_SCREEN_X, world2grid(obj->pos.y) - 1 + VIEWGRID_SCREEN_Y);

    if (left * 2 > otype->hp)
        color = 0x0a;
    else
    if (left * 4 > otype->hp)
        color = 0x0e;
    else
        color = 0x0c;

    screen_fill_region('-', color, start, filled, 1);
    if (filled < w)
        screen_fill_region('-', 0x08, start + filled * 2, w - filled, 1);
}

unsigned int d1[64], d2[64];
unsigned char dd;
unsigned char debug;
    
void progress(unsigned char cycle) {

    hsObject obj;
    hsObject target;
    hcsObjType otype;
    hcsPhysical otphy;
    sPosGrid pos;
    sVecGrid vec;
    unsigned char i;

    obj = NULL;
    
    // remove dead objects
    objpool_garbage();

    // clear damage map
    memset(g_map, 0, sizeof(g_map)); // TODO - asm...

    // status changes to objects (just the active, because new objects 
    // may be created in this loop and some of them would be handled now 
    // and some in the next iteration, creating uncertainity)
    while ((obj = objpool_next_active(obj)) != NULL) {

        otype = obj->type;
        otphy = obj->physical;

        // perform object's own behaviour
        if (PERIOD_16PERSEC && otype->cb_behave != NULL)
            otype->cb_behave(obj);
        
        // update object position
        obj->pos.x = adjust(obj->pos.x + obj->speed.x, 0, grid2world(VIEWGRID_WIDTH - otphy->dim.x));
        obj->pos.y = adjust(obj->pos.y + obj->speed.y, 0, grid2world(VIEWGRID_HEIGHT - otphy->dim.y));

        // don't allow monsters to get too close to player
        if (otype->nature == OBJTYPE_NAT_FOE_OBJ && obj->pos.y > grid2world(VIEWGRID_HEIGHT - 9))
            obj->pos.y = grid2world(VIEWGRID_HEIGHT - 9);
        
        // update object action
        if (PERIOD_16PERSEC) {

            if (obj->ttl > 0)
                obj->ttl--;
        
            if ((obj->flags & OBJ_FLG_DYING) && obj->ttl == 0)
                obj->flags |= OBJ_FLG_DESTROY;
        }
        
        // handle bullet
        if (otype->nature & OBJTYPE_NATMASK_BULLET) {
        
            // TODO - bullets are now harmless at the edges :-(

            pos.x = world2grid(obj->pos.x); 
            pos.y = world2grid(obj->pos.y);

            if (pos.y == 0 || (pos.y + otphy->dim.y) >= VIEWGRID_HEIGHT || pos.x == 0 || (pos.x + otphy->dim.x) >= VIEWGRID_WIDTH) {
            
                objpool_free(obj);
                continue;
            }
        }

        // handle "mortal" object
        if (otype->nature & OBJTYPE_NATMASK_OBJ) {

            // handle object's damage
            obj->damage_total += obj->damage_now;
            obj->damage_now = 0;
        
            if (obj->damage_total >= otype->hp) {

                obj->damage_total = otype->hp;
                
                // object has taken enough damage, let it die
                if (!(obj->flags & OBJ_FLG_DYING)) {
                
                    obj->flags |= OBJ_FLG_DYING;
                    obj->ttl = 1;
                    
                    if (otype->cb_die != NULL)
                        otype->cb_die(obj);
                }
            }
            else
            if (otype->nature & (OBJTYPE_NATMASK_ALLY | OBJTYPE_NATMASK_FOE)) {

                // TODO - tohle zkraslit...
                // add the object to the damage map
                char imgoff;
                unsigned char objindex;
                char xtype = (otype->nature & OBJTYPE_NATMASK_FOE) ? 1 : 0;
        
                otphy = obj->physical;

                pos.x = world2grid(obj->pos.x);
                pos.y = world2grid(obj->pos.y);

                // TODO - asm...
                imgoff = 0;
                for (vec.y = 0; vec.y < otphy->dim.y; vec.y++)
                    for (vec.x = 0; vec.x < otphy->dim.x; vec.x++, imgoff += 2)
                        if (otphy->image[imgoff] != 0)
                            g_map[vec.y + pos.y][vec.x + pos.x][xtype] = obj;
            }
        }
    }

    // go through bullets
    while ((obj = objpool_next_active(obj)) != NULL) {

        otype = obj->type;
        if (otype->nature & OBJTYPE_NATMASK_BULLET) {
        
            char imgoff;
            
            // g_map lookup would go out of bounds
            if (!obj_in_view(obj))
                continue;
            
            otphy = obj->physical;

            pos.x = world2grid(obj->pos.x);
            pos.y = world2grid(obj->pos.y);

            imgoff = 0;
            for (vec.y = 0; vec.y < otphy->dim.y; vec.y++) {
            
                for (vec.x = 0; vec.x < otphy->dim.x; vec.x++, imgoff += 2) {
                
                    if (otphy->image[imgoff] == 0)
                        continue;
                    
                    target = g_map[vec.y + pos.y][vec.x + pos.x][(otype->nature & OBJTYPE_NATMASK_FOE) ? 0 : 1];
                    if (target == NULL) 
                        continue;

                    if (otype->cb_deal != NULL)
                        otype->cb_deal(obj, target);
                    
                    if (target->type->cb_hit != NULL)
                        target->type->cb_hit(target);
                        
                    vec.y = otphy->dim.y;
                    break;
                }
            }
        }
    }

    // wait for screen's lunch time
    dd = (dd + 1) & 63;
    d1[dd] = 0;
    d2[dd] = 0;
    while((inp(0x03da) & 0x08))
        d1[dd]++;
    while(!(inp(0x03da) & 0x08))
        d2[dd]++;

    screen_fill_region(' ', 0, screen_offset_xy(VIEWGRID_SCREEN_X, VIEWGRID_SCREEN_Y), VIEWGRID_WIDTH, VIEWGRID_HEIGHT);

    // draw the hp bars first, so they don't cover objects flying around
    while ((obj = objpool_next(obj)) != NULL)
        draw_hpbar(obj);

    // draw the objects
    while ((obj = objpool_next(obj)) != NULL) {

        obj->flags &= ~OBJ_FLG_INACTIVE;

        if (obj->flags & OBJ_FLG_HIDDEN)
            continue;

        // would draw over the walls/sidebar, which aren't cleared every frame
        if (!obj_in_view(obj))
            continue;
    
        otype = obj->type;
        otphy = obj->physical;
        
        pos.x = world2grid(obj->pos.x);
        pos.y = world2grid(obj->pos.y);

        screen_blit(otphy->image, screen_offset_xy(pos.x + VIEWGRID_SCREEN_X, pos.y + VIEWGRID_SCREEN_Y), otphy->dim.x, otphy->dim.y);
    }

    // draw texts
    for (i = 0; i < show_text_count; i++) {
    
        hcsDisplayText dt = show_text_first + i;
        
        screen_color(dt->color);
        screen_print_text(dt->pos.x, dt->pos.y, dt->text);
    }
}

void show_bar(char x, char y, char width, char total, char current) {

    screen_print_bar(x, y, width, (width * current + total / 2) / total);
}

int main(int argc, char *argv[]) {

    hsObject emit;
    hcsScenarioInfo scinfo;
    unsigned int cycle;
    unsigned int hp_left, hp_left_prev;
    unsigned char hp_flash;
    unsigned char event;

    xlog("start");
    
    srand(time(NULL));
    
    objpool_clear();

    if ((player = objpool_alloc(&ot_player)) == NULL)
        return 1;
        
    player->pos.x = grid2world(VIEWGRID_WIDTH / 2 - 2);
    player->pos.y = grid2world(VIEWGRID_HEIGHT - 1 - player->physical->dim.y);

    shield = NULL;
    hp_left_prev = player->type->hp;
    hp_flash = 0;
    
    // prepare playfield
    screen_init();
    screen_clear(0, 0);
    screen_fill_region('|', 8, screen_offset_xy(0, 0), 1, 50);
    screen_fill_region('|', 8, screen_offset_xy(VIEWGRID_WIDTH + 1, 0), 1, 50);

    // prepare hp bar
    screen_color(7);
    screen_print_text(VIEWGRID_SCREEN_X, HPBAR_Y, "HP");

    // add texts
    screen_color(8);
    screen_print_text(BAR_LEFT, 35, "Z - CANNON");
    screen_print_text(BAR_LEFT, 37, "X - LASER");
    screen_print_text(BAR_LEFT, 39, "C - LASER");
    screen_print_text(BAR_LEFT, 41, "V - MEGABLAST");
    screen_print_text(BAR_LEFT, 45, "P - PAUSE");
    screen_print_text(BAR_LEFT, 47, "Q - QUIT");
    
    input_init();

    // determine scenario to play
    scpoint = &g_scenario_original[0];
    if (argc > 1) {

        for (scinfo = &scenarios[0]; scinfo < &scenarios[dimof(scenarios)]; scinfo++) {

            if (stricmp(argv[1], scinfo->alias))
                continue;

            scpoint = scinfo->entry;
            break;
        }
    }

    // initialize scenario state
    scpoint_timer = 0;
    scpoint_repeat = 0;
    show_text_first = NULL;
    show_text_count = 0;
    paused = 0;
    
    while (!uifn_hold[UIFN_QUIT]) {

        event = input_pop_event();

        if (event == UIFN_PAUSE)
            paused = !paused;
        if (event == UIFN_DEBUG)
            debug = !debug;

        if (paused)
            continue;
    
        if (debug && PERIOD_4PERSEC) {
        
            unsigned int ad1, ad2;
            unsigned char i;
            
            ad1 = 0;
            ad2 = 0;
            for (i = 0; i < dimof(d1); i++) {
            
                ad1 += d1[i];
                ad2 += d2[i];
            }
        
            screen_color(0x07);
            screen_print_text(70, 20, "         ");
            screen_print_hex16(70, 20, ad1 >> 6);
            screen_print_hex16(75, 20, ad2 >> 6);
        }
            
        // handle scenario
        if (PERIOD_4PERSEC) {
        
            if (scpoint_timer > 0) {
            
                scpoint_timer--;
            }
            else {
            
                scpoint_timer = scpoint->delay;
                show_text_first = scpoint->ds_text;
                show_text_count = scpoint->ds_count;
                
                if (scpoint->cb_tick != NULL)
                    (scpoint->cb_tick)(scpoint, scpoint_repeat);
                
                switch (scpoint->type) {
                
                    case SCPOINT_TYPE_WAIT_DEAD:

                        emit = NULL;
                        while ((emit = objpool_next(emit)) != NULL) {
                        
                            if (emit->type->nature != OBJTYPE_NAT_FOE_OBJ || (emit->type->flags & OBJTYPE_FLG_NOWAIT))
                                continue;
                                
                            scpoint_timer = scpoint->delay;
                            scpoint_repeat = 0;
                            break;
                        }
                        break;
                        
                    case SCPOINT_TYPE_END:
                        
                        scpoint_repeat = 0;
                        break;
                }

                if (scpoint_repeat >= scpoint->repeat) {
                
                    scpoint_repeat = 0;
                    scpoint++;
                }
                else
                    scpoint_repeat++;
            }
        }
    
        if (player->flags & OBJ_FLG_DYING) {
        
            player->ttl = 255;
            player->speed.x = 0;
            player->speed.y = 0;

            show_text_first = text_fail;
            show_text_count = dimof(text_fail);
        }
        else {
        
            // handle movements
            player->speed.x = 0 + (uifn_hold[UIFN_LEFT] ? -8 : 0) + (uifn_hold[UIFN_RIGHT] ? 8 : 0);
            //player->speed.y = 0 + (uifn_hold[UIFN_UP] ? -8 : 0) + (uifn_hold[UIFN_DOWN] ? 8 : 0);

            // handle cannons and lasers
            if (player_weapon_delay > 0) {
            
                player_weapon_delay--;
            }
            else
            if (uifn_hold[UIFN_FIRE_CANNON]) {
            
                player_weapon_delay = 30;
                fire_turret(player, &turret_player_bullet);
            }
            else
            if (uifn_hold[UIFN_FIRE_LASER]) {

                player_weapon_delay = 12;
                fire_turret(player, &turret_player_lleft);
                fire_turret(player, &turret_player_lright);
            }
            else
            if (uifn_hold[UIFN_FIRE_SIDE_LASER]) {

                player_weapon_delay = 15;
                fire_turret(player, &turret_player_llleft);
                fire_turret(player, &turret_player_llright);
            }
            else
            if (uifn_hold[UIFN_FIRE_MEGABLAST]) {

                player_weapon_delay = 90;
                fire_turret(player, &turret_player_megablast);
            }
/*            
            else
            if (uifn_hold[UIFN_SHIELD] && shield == NULL) {

                if ((shield = objpool_alloc(&ot_shield)) != NULL) {

                    shield->pos.x = player->pos.x - grid2world(((signed int)shield->physical->dim.x - (signed int)player->physical->dim.x) / 2);
                    shield->pos.y = player->pos.y - grid2world(2);
                }
            }
*/            
        }
        
        // show hp bar; green over 2/3, yellow over 1/3, then light red,
        // blinking (hw blink is off, so toggled by hand) on the last 1/5
        // and flashing white for a moment whenever hp drops
        hp_left = player->type->hp - player->damage_total;
        if (hp_left < hp_left_prev)
            hp_flash = HPBAR_FLASH_FRAMES;
        hp_left_prev = hp_left;

        if (hp_flash) {

            hp_flash--;
            screen_color(15);
        }
        else
        if (hp_left * 3 > player->type->hp * 2)
            screen_color(2);
        else
        if (hp_left * 3 > player->type->hp)
            screen_color(14);
        else
        if (hp_left * 5 > player->type->hp || (cycle & 16))
            screen_color(12);
        else
            screen_color(4);

        show_bar(HPBAR_LEFT, HPBAR_Y, HPBAR_WIDTH, player->type->hp, hp_left);
        
        // handle objects and bullets
        progress(cycle++);
    }
    
    input_close();
    screen_close();
    return 0;
}
