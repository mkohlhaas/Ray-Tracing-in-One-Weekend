#pragma once

#include "args.h"
#include "camera.h"
#include "error.h"
#include "globals.h"
#include "world.h"
#include <stdio.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

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
