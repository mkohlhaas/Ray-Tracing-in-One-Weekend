#pragma once

#include "point.h"

typedef struct camera
{
  double aspect_ratio;
  int    image_width;
  int    image_height;
  double vfov;
  double focal_length;
  point3 center;
  double viewport_width;
  double viewport_height;
  point3 viewport_upper_left;
  vec3   pixel_delta_u;
  vec3   pixel_delta_v;
  point3 pixel_origin;
  int    samples_per_pixel;
  double pixel_samples_scale;
  int    max_depth;
} camera;

extern camera cam;

struct hittable;
void camera_init (void);
void render (camera c, struct hittable **world);
