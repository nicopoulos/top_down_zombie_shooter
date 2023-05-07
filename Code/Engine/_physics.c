#include "_physics.h"


bool collision_detected(const circle_collider_t* c1, const transform_t* t1, const circle_collider_t* c2, const transform_t* t2)
{
    bool collision_status = false;

    double contact_point_distance = c1->radius + c2->radius;
    double dx = t2->position.x - t1->position.x;
    double dy = t2->position.y - t1->position.y;
    double distance = sqrt(pow(dx, 2) + pow(dy, 2));
    if (distance <= contact_point_distance)
        collision_status = true;


    return collision_status;
}