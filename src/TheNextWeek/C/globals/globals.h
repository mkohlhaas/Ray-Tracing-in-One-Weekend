#pragma once

#include "camera/camera.h"
#include "hittables/bvh_node.h"
#include "hittables/hittable_list.h"
#include "math/color.h"
#include "math/vec3.h"

// global world
extern hittable_list_t *g_world_list;
extern bvh_node_t      *g_world_bvh;

// scene background color
extern color_t const g_background;

// global camera
extern camera_t g_camera;

// minimum `t` value (see 9.3 Fixing Shadow Acne)
extern double g_min_t;

// camera settings
extern const double   g_defocus_angle; /* defocus blur = depth of field */
extern const double   g_focus_dist;    /* focus distance = focus length (in our model) */
extern const double   g_vfov;          /* vertical field of view in degrees (edge to edge) */
extern const vec3_t   g_vup;           /* view up */
extern const point3_t g_lookfrom;      /* eye/camera */
extern const point3_t g_lookat;
extern const int      g_samples_per_pixel;
extern const int      g_max_depth;
