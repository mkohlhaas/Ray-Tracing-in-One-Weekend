#pragma once

#include "hittable_list.h"

// global world
// extern hittable_t **g_world;
extern hittable_list_t *g_world;

void world_init (void);
