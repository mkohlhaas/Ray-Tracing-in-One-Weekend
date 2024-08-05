#pragma once

#include "args.h"
#include "camera.h"
#include "error.h"
#include "world.h"
#include <stdio.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

static FILE *output_file = NULL;

static void
open_output_file ()
{
  if (args.output_file == NULL)
    {
      output_file = stdout;
    }
  else
    {
      output_file = fopen (args.output_file, "w");
      if (!output_file)
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
  // print_global_camera ();
}

void
cleanup (void)
{
  fclose (output_file);

  for (int i = 0; i < arrlen (g_world_list->hittables); i++)
    {
      free (g_world_list->hittables[i]);
    }
  free (g_world_list);
}
