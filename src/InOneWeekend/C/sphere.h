#pragma once

#include "interval.h"
#include "point.h"
#include <stdbool.h>

typedef struct
{
  point3 center;
  double radius;
} sphere;

struct hit_record;
struct ray;
bool    hit_sphere (void *sphere, struct ray const r, interval i, struct hit_record *rec);
sphere *sphere_new (point3 center, double radius);
