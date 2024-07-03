#pragma once

#include "ray.h"
#include <stdbool.h>

// Returns `attenuation` and `scattered` ray.
typedef void (*scatter_fn) (ray_t const r_in, hit_record_t const *rec, color_t *attenuation, ray_t *scattered);

// A material (lambertian, metal, dielectric,...) is every struct with scatter_fn as first entry.
typedef struct material
{
  scatter_fn scatter;
} material_t;

typedef material_t mat_t;

material_t *get_material (hittable_t *object);
