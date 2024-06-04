#include "camera.h"
#include "world.h"

void
init (void)
{
  world_init ();
  camera_init ();
}

void
cleanup (void)
{
  g_array_free (world, FALSE);
}
