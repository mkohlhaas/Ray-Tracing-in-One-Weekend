#include "globals/globals.h"

// global world
hittable_list_t *g_world_list = NULL;
bvh_node_t      *g_world_bvh  = NULL;

color_t const g_background = (color_t){
  .r = 0.7,
  .g = 0.8,
  .b = 1.0,
};

// Global camera.
camera_t g_camera;

// Global minimum `t` value.
double g_min_t = 0.001;

// camera settings
double const   g_defocus_angle     = 0.0;                        /* defocus blur = depth of field */
double const   g_focus_dist        = 20.0;                       /* focus distance = focus length (in our model) */
double const   g_vfov              = 80.0;                       /* vertical field of view in degrees (edge to edge) */
vec3_t const   g_vup               = { .x = 0, .y = 1, .z = 0 }; /* view up */
point3_t const g_lookfrom          = { .x = 0, .y = 0, .z = 9 }; /* eye/camera */
point3_t const g_lookat            = { .x = 0, .y = 0, .z = 0 }; /* look at vector */
int const      g_samples_per_pixel = 100;
int const      g_max_depth         = 50;
