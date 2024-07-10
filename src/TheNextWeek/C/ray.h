#pragma once

#include "aabb.h"
#include "camera.h"
#include "color.h"
#include "interval.h"

// minimum t value (see 9.3 Fixing Shadow Acne)
extern double min_t;

typedef struct ray
{
  point3_t origin;    // origin of ray
  vec3_t   direction; // direction of ray
  double   tm;        // randomly chosen time: 0 (start time)<= tm < 1 (end time)
} ray_t;

typedef enum
{
  SPHERE,
  HITTABLE_LIST,
  BVH_NODE,
} hit_type_t;

struct hit_record;
typedef bool (*hit_fn_t) (ray_t const r, interval_t intvl, struct hit_record *rec);

// Every struct with first members `hit_type`, `hit_fn` and `*aabb_t` is a `hittable_t` (sphere, hittable_list, ...)
typedef struct hittable
{
  hit_type_t hit_type;
  hit_fn_t   hit;
  aabb_t    *bbox;
} hittable_t;

// `object` must be set before calling hit functions.
// All other members are return values from hit functions.
typedef struct hit_record
{
  hittable_t *object;      // the object being hit (to be set before callling hit functions)
  point3_t    p;           // hit point
  vec3_t      unit_normal; // normals always point against the ray and are unit vectors
  double      t;           // ray = ray.origin + t * ray.direction
  bool        front_face;  // needed b/c we can't use dot product of ray and unit_normal
} hit_record_t;

// struct hittable_list;
point3_t point_at (ray_t r, double t);
color_t  ray_color (ray_t const ray, int depth, hittable_t *world);
ray_t    random_ray (camera_t c, int row, int col);
void     set_face_normal (hit_record_t *rec, ray_t const r, vec3_t const outward_unit_normal);
