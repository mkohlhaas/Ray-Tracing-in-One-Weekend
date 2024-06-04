#pragma once

#include "hittable.h"
#include "interval.h"
#include "ray.h"
#include <stdbool.h>

typedef struct
{
  point3 center;
  double radius;
} sphere;

bool    hit_sphere (void *sphere, ray const r, interval i, hit_record *rec);
sphere *sphere_new (point3 center, double radius);
