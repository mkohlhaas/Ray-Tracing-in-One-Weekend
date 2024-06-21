#pragma once

#include "ray.h"
#include <stdbool.h>

// Returns `attenuation` and `scattered` ray.
typedef void (*scatter_fn) (ray_t const r_in, hit_record_t const *rec, color_t *attenuation, ray_t *scattered);

// Just for reference.
// Every struct with scatter_fn as first entry is a material (lambertian, metal, dielectric,...).
typedef struct material_t
{
  scatter_fn scatter;
} material_t;

material_t *get_material (hit_able_t *object);
