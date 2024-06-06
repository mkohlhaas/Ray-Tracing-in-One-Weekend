#pragma once

#include "interval.h"
#include "material.h"
#include "point.h"
#include <stdbool.h>

typedef struct
{
  point3    center;
  double    radius;
  material *mat;
} sphere;

struct hit_record;
struct ray;
bool    sphere_hit (struct ray const r, interval i, struct hit_record *rec);
sphere *sphere_new (point3 center, double radius, material *mat);
