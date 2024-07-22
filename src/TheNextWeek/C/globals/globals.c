#include "globals/globals.h"

color_t const g_background = (color_t){
  .r = 0.7,
  .g = 0.8,
  .b = 1.0,
};

// global camera
camera_t g_camera;

// global camera
double g_min_t = 0.001;

// camera settings
double const   g_defocus_angle     = 0.9;                        /* defocus blur = depth of field */
double const   g_focus_dist        = 20.0;                       /* focus distance = focus length (in our model) */
double const   g_vfov              = 25;                         /* vertical field of view in degrees (edge to edge) */
vec3_t const   g_vup               = { .x = 0, .y = 1, .z = 0 }; /* view up */
point3_t const g_lookfrom          = (point3_t){ .x = 23, .y = 4, .z = 3 }; /* eye/camera */
point3_t const g_lookat            = { .x = 0, .y = 0, .z = 0 };            /* look at vector */
int const      g_samples_per_pixel = 100;
int const      g_max_depth         = 50;
