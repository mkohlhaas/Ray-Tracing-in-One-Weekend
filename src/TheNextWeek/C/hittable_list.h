#pragma once

#include "ray.h"
#include "stb_ds.h"

typedef struct hittable_list
{
  hit_type_t   type; // LIST
  hit_fn       hit_fn;
  hittable_t **hittables;
} hittable_list_t;

hittable_list_t *hittable_list_new ();
