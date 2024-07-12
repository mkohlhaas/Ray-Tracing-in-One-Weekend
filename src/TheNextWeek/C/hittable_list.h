#pragma once

#include "aabb.h"
#include "ray.h"
#include "stb_ds.h"

// `hittable_list_t` is a `hittable_t`
typedef struct hittable_list
{
  hit_type_t   hit_type; // LIST
  hit_fn_t     hit;
  aabb_t      *bbox;
  hittable_t **hittables;
} hittable_list_t;

hittable_list_t *hittable_list_new ();
void             hittable_list_add (hittable_list_t *l, hittable_t *h);
void             hittable_list_print (hittable_list_t *l, int indent_lvl);
