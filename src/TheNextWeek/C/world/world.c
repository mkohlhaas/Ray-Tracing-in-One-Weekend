#include "world.h"
#include "3rd_party/stb_ds.h"
#include "error/error.h"
#include "hittables/bvh_node.h"
#include "hittables/hittable_list.h"
#include "scenes/bounding_spheres.h"
#include "scenes/checkered_spheres.h"
#include "scenes/earth.h"
#include "scenes/perlin_spheres.h"
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
