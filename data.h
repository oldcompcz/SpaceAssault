#ifndef __DATA_H
#define __DATA_H

/*

object type's param         object                          bullet
-------------------------------------------------------------------------------
nature                      OBJTYPE_NAT_*_OBJ               OBJTYPE_NAT_*_BULLET
physical dimensions         -                               must be always 1x1    
type->hp                    how much damage can take        how much damage deals

*/

#define TURRET_NONE                     { { 0, 0 }, { 0, 0 }, NULL }
#define TURRETS_NONE                    { TURRET_NONE, TURRET_NONE, TURRET_NONE, TURRET_NONE }
#define TURRET_GRID(x, y, dx, dy, t)    { { grid2world(x), grid2world(y) }, { (dx), (dy) }, (t) }

hsObject fire_turret(hsObject obj, hcsTurret turret);
int adjust(int value, int min, int max);

#define PHYSICAL_1X1(ascii, attr)       { { 1, 1 }, { (ascii), (attr) } }

#endif
