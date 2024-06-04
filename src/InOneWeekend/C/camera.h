#pragma once

#include "point.h"
#include <glib.h>

typedef struct
{
  double aspect_ratio;
  int    image_width;
  int    image_height;
  double focal_length;
  point3 center;
  double viewport_width;
  double viewport_height;
  point3 viewport_upper_left;
  vec3   pixel_delta_u;
  vec3   pixel_delta_v;
  point3 pixel_origin;

} camera;

extern camera cam;
void          camera_init (void);
void          render (camera c, GArray *const world);
