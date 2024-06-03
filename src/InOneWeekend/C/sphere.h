#pragma once

#include "hittable.h"
#include "ray.h"
#include <stdbool.h>

typedef struct
{
  point3 center;
  double radius;
} sphere;

bool hit_sphere (void *sphere, ray const r, double ray_tmin, double ray_tmax, hit_record *rec);
