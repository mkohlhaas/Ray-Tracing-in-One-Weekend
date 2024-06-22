#pragma once

#include "camera.h"
#include "color.h"
#include "interval.h"

typedef struct ray
{
  point3 origin;
  vec3_t direction;
} ray_t;

typedef enum
{
  SPHERE,
  LIST,
} hit_type_t;

struct hit_record;
typedef bool (*hit_fn) (ray_t const r, interval_t i, struct hit_record *rec);

// Just for reference.
// Every struct with first members hit_type and hit_fn is a hit_able (sphere, list, ...)
typedef struct hit_able
{
  hit_type_t type;
  hit_fn     hit_fn;
} hit_able_t;

typedef struct hit_record
{
  hit_able_t *object;
  point3      p;
  vec3_t      normal; // normals always point against the ray
  double      t;      // TODO: comment?
  bool        front_face;
} hit_record_t;

ray_t  *ray_new (point3 origin, vec3_t direction);
point3  point_at (ray_t r, double t);
color_t ray_color (ray_t const r, int depth, hit_able_t *world[]);
ray_t   random_ray (camera_t c, int row, int col);
void    set_face_normal (hit_record_t *rec, ray_t const r, vec3_t const outward_unit_normal);
