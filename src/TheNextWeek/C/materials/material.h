#pragma once

#include "color.h"
#include "point.h"
#include "ray/ray.h"
#include <stdbool.h>

// Returns `true` if this is a proper material, `false` if it's a light-emitting material = light source.
// Returns `attenuation` and `scattered` ray.
typedef bool (*scatter_fn) (ray_t const r_in, hit_record_t const *rec, color_t *attenuation, ray_t *scattered);

typedef color_t (*emit_fn) (hit_record_t const *rec);

// A material (lambertian, metal, dielectric,...) is every struct with scatter_fn as first entry.
typedef struct material
{
  scatter_fn scatter;
  emit_fn    emit;
} material_t;

typedef material_t mat_t;

material_t *get_material (hittable_t *object);
