#ifndef PHYSICS_H
#define PHYSICS_H

#include "_components.h"
#include <stdbool.h>
#include <math.h>

bool collision_detected(const circle_collider_t* c1, const transform_t* t1, const circle_collider_t* c2, const transform_t* t2);


#endif