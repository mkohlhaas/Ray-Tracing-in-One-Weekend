#pragma once

#include "aabb.h"
#include "interval.h"
#include "vec3.h"

typedef enum
{
  SPHERE,
  HITTABLE_LIST,
  BVH_NODE,
  TRIANGLE,
  QUAD,
  TRANSLATE,
  ROTATE,
  VOLUME,
} hit_type_t;

struct hit_record;
struct hittable;
struct ray;
typedef bool (*hit_fn_t) (struct ray const r, struct hittable *object, interval_t intvl, struct hit_record *rec);

// Every struct with first members `hit_type`, `hit_fn` and `*aabb_t` is a `hittable_t`
typedef struct hittable
{
  hit_type_t hit_type;
  hit_fn_t   hit;
  aabb_t     bbox;
} hittable_t;

// Return values from hit functions.
typedef struct hit_record
{
  hittable_t *object;      // the object being hit (sphere, quads, triangles,... NOT bvh_nodes, hittable_lists, ...)
  point3_t    p;           // hit point
  double      t;           // ray = ray.origin + t * ray.direction
  double      u;           // texture coordinate
  double      v;           // texture coordinate
  vec3_t      unit_normal; // normals always point against the ray and are unit vectors
  bool        front_face;  // needed b/c we can't use dot product of ray and unit_normal
} hit_record_t;
