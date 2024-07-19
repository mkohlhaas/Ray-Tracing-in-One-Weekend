#include "world.h"
#include "bounding_spheres_scene.h"
#include "bvh_node.h"
#include "checkered_spheres_scene.h"
#include "earth_scene.h"
#include "error.h"
#include "hittable_list.h"
#include "perlin_spheres_scene.h"
#include "stb_ds.h"
#include <stdio.h>

// global world
hittable_list_t *g_world_list = NULL;
bvh_node_t      *g_world_bvh  = NULL;

static void
init_g_world ()
{
  g_world_list = hittable_list_new ();
  if (!g_world_list)
    {
      logExit ("Out of memory");
    }
}

static void
create_bvh ()
{
  g_world_bvh = bvh_node_new (g_world_list->hittables);
}

void
world_init (void)
{
  init_g_world ();

  // choose scene
  switch (4)
    {
    case 1:
      bouncing_spheres ();
      break;
    case 2:
      checkered_spheres ();
      break;
    case 3:
      earth ();
      break;
    case 4:
      perlin_spheres ();
      break;
    }

  create_bvh ();
  // print_bvh (world);
}
