#pragma once

#include "bvh_node.h"
#include "hittable_list.h"

// global world
extern hittable_list_t *g_world_list;
extern bvh_node_t      *g_world_bvh;

void world_init (void);
