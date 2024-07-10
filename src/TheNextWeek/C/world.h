#pragma once

#include "bvh_node.h"
#include "hittable_list.h"

// global world
extern hittable_list_t *g_world;
extern bvh_node_t      *world;

void world_init (void);
