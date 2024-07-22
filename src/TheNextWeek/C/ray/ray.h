#pragma once

#include "bbox/aabb.h"
#include "camera/camera.h"
#include "hittables/hittable.h"
#include "math/color.h"

typedef struct ray
{
  point3_t origin;    // origin of ray
  vec3_t   direction; // direction of ray
  double   tm;        // randomly chosen time: 0 (start time)<= tm < 1 (end time)
} ray_t;

// struct hittable_list;
point3_t point_at (ray_t r, double t);
color_t  ray_color (ray_t const ray, int depth, hittable_t *world);
ray_t    random_ray (camera_t c, int row, int col);
void     set_face_normal (hit_record_t *rec, ray_t const r, vec3_t const outward_unit_normal);
