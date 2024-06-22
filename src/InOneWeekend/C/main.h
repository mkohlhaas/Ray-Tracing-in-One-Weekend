#pragma once

#include "camera.h"
#include "world.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void
init (void)
{
  world_init ();
  camera_init ();
}

void
cleanup (void)
{
  for (int i = 0; i < arrlen (g_world); i++)
    {
      free (g_world[i]);
    }
  arrfree (g_world);
}
