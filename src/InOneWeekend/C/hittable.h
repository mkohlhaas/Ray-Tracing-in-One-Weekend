#pragma once

#include "hit_record.h"
#include "interval.h"
#include "ray.h"
#include <stdbool.h>

typedef bool (*hit_fn) (void *self, ray const r, interval i, hit_record *rec);

typedef struct hittable
{
  hit_fn hit;
  void  *object;
} hittable;

void      set_face_normal (hit_record *rec, ray const r, vec3 const outward_normal);
hittable *hittable_new (hit_fn hit, void *object);
