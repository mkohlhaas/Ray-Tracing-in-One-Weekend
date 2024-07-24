#pragma once

#include "3rd_party/stb_ds.h"
#include "bbox/aabb.h"
#include "hittables/hittable.h"

// `hittable_list_t` is a `hittable_t`
typedef struct hittable_list
{
  hit_type_t   hit_type; // LIST
  hit_fn_t     hit;
  aabb_t       bbox;
  hittable_t **hittables;
} hittable_list_t;

hittable_list_t *hittable_list_new ();
void             hittable_list_add (hittable_list_t *l, hittable_t *h);
void             hittable_list_print (hittable_list_t *l, int indent_lvl);
