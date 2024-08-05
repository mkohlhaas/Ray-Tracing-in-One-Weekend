#include "world.h"
#include "bounding_spheres.h"
#include "bvh_node.h"
#include "checkered_spheres.h"
#include "cornell_box.h"
#include "cornell_box_real.h"
#include "cornell_box_smoke.h"
#include "cornell_box_with_blocks.h"
#include "earth.h"
#include "error.h"
#include "final.h"
#include "globals.h"
#include "hittable_list.h"
#include "perlin_freq_spheres.h"
#include "perlin_hermitian_spheres.h"
#include "perlin_lattice_spheres.h"
#include "perlin_phase_spheres.h"
#include "perlin_smooth_spheres.h"
#include "perlin_spheres.h"
#include "perlin_turb_spheres.h"
#include "quads.h"
#include "simple_light.h"
#include "stb_ds.h"
#include "triangles.h"

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
  switch (18)
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
    case 5:
      perlin_smooth_spheres ();
      break;
    case 6:
      perlin_hermitian_spheres ();
      break;
    case 7:
      perlin_freq_spheres ();
      break;
    case 8:
      perlin_lattice_spheres ();
      break;
    case 9:
      perlin_turb_spheres ();
      break;
    case 10:
      perlin_phase_spheres ();
      break;
    case 11:
      quads ();
      break;
    case 12:
      triangles ();
      break;
    case 13:
      simple_light ();
      break;
    case 14:
      cornell_box ();
      break;
    case 15:
      cornell_box_with_boxes ();
      break;
    case 16:
      cornell_box_real ();
      break;
    case 17:
      cornell_box_smoke ();
      break;
    case 18:
      final ();
      break;
    }

  create_bvh ();
  // print_bvh (world);
}
