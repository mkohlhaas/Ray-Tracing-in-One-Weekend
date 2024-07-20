#pragma once

#include "args/args.h"
#include "camera/camera.h"
#include "error/error.h"
#include "globals/globals.h"
#include "world/world.h"
#include <stdio.h>
#define STB_DS_IMPLEMENTATION
#include "3rd_party/stb_ds.h"

static void
open_output_file ()
{
  if (args.output_file == NULL)
    {
      g_output_file = stdout;
    }
  else
    {
      g_output_file = fopen (args.output_file, "w");
      if (!g_output_file)
        {
          logExit ("Couldn't open file %s", args.output_file);
        }
    }
}

void
init (void)
{
  open_output_file ();
  world_init ();
  camera_init ();
}

void
cleanup (void)
{
  fclose (g_output_file);

  for (int i = 0; i < arrlen (g_world_list->hittables); i++)
    {
      free (g_world_list->hittables[i]);
    }
  free (g_world_list);
}
