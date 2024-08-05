#include "globals.h"
#include "bvh_node.h"
#include "hittable_list.h"

// global world
hittable_list_t *g_world_list = NULL;
bvh_node_t      *g_world_bvh  = NULL;

color_t const g_background = (color_t){
  .r = 0.0,
  .g = 0.0,
  .b = 0.0,
};

// Global camera.
camera_t g_camera;

// Global minimum `t` value.
double g_min_t = 0.001;

bool const g_enableDebug = false;

// camera settings
double const   g_defocus_angle     = 0.0;                        /* defocus blur = depth of field */
double const   g_focus_dist        = 20.0;                       /* focus distance = focus length (in our model) */
double const   g_vfov              = 40.0;                       /* vertical field of view in degrees (edge to edge) */
vec3_t const   g_vup               = { .x = 0, .y = 1, .z = 0 }; /* view up */
point3_t const g_lookfrom          = { .x = 478, .y = 278, .z = -600 }; /* eye/camera */
point3_t const g_lookat            = { .x = 278, .y = 278, .z = 0 };    /* look at vector */
int const      g_samples_per_pixel = 1000;
int const      g_max_depth         = 140;
