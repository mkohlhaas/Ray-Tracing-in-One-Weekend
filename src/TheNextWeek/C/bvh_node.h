#pragma once

#include "aabb.h"
#include "ray.h"

// `bvh_node_t` is a `hittable_t`.
typedef struct bvh_node
{
  hit_type_t  hit_type; // BVH_NODE
  hit_fn_t    hit;
  aabb_t     *bbox;
  hittable_t *left;
  hittable_t *right;
} bvh_node_t;

bvh_node_t *bvh_node_new (hittable_t **objects);
void        print_bvh (bvh_node_t *bvh, int indent_lvl);
