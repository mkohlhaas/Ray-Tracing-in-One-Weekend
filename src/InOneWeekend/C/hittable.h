#pragma once

#include "interval.h"
#include "point.h"
#include <stdbool.h>

typedef struct hit_record
{
  point3 p;
  vec3   normal; // normals always point against the ray
  double t;
  bool   front_face;
} hit_record;

struct ray;
typedef bool (*hit_fn) (void *self, struct ray const r, interval i, hit_record *rec);

typedef struct hittable
{
  hit_fn hit;
  void  *object;
} hittable;

void      set_face_normal (hit_record *rec, struct ray const r, vec3 const outward_normal);
hittable *hittable_new (hit_fn hit, void *object);
