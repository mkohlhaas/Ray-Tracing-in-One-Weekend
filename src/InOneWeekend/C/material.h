#pragma once

#include "ray.h"
#include <stdbool.h>

struct hit_record;

typedef bool (*scatter_fn) (ray const r_in, struct hit_record const *rec, color *attenuation, ray *scattered);

typedef struct material
{
  scatter_fn scatter;
} material;
