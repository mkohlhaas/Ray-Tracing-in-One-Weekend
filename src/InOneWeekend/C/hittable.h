#pragma once

#include "interval.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>

typedef struct
{
  point3 p;
  vec3   normal; // normals always point against the ray
  double t;
  bool   front_face;
} hit_record;

typedef bool (*hit_fn) (void *self, ray const r, interval i, hit_record *rec);

typedef struct
{
  hit_fn hit;
  void  *object;
} hittable;

// dummy code:
// for_each(hittable in hittables) {
//   hittable->hit(hittable->object, r, ray_min, ray_max, *rec);
// }

void      set_face_normal (hit_record *rec, ray const r, vec3 const outward_normal);
hittable *hittable_new (hit_fn hit, void *object);
