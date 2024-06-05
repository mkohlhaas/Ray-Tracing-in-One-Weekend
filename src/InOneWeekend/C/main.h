#pragma once

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
  for (int i = 0; i < arrlen (world); i++)
    {
      free (world[i]);
    }
  arrfree (world);
}
