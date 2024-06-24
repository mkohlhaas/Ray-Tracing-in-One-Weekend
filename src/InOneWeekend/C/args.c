#include "args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "raytracer 1.0";

static char doc[] = "Raytracer based on \"Raytracer in a Weekend\"";

static struct argp_option options[] = { {
                                            .key   = 'o',
                                            .arg   = "FILE",
                                            .doc   = "Output to FILE (default=stdout)",
                                            .group = 0,
                                        },
                                        {
                                            .key   = 'w',
                                            .arg   = "WIDTH",
                                            .doc   = "Image width (required)",
                                            .group = 1,
                                        },
                                        {
                                            .key = 'h',
                                            .arg = "HEIGHT",
                                            .doc = "Image height (required)",
                                        },
                                        {
                                            .key = 's',
                                            .arg = "START",
                                            .doc = "Starting scanline (required)",
                                        },
                                        {
                                            .key = 'n',
                                            .arg = "NUM",
                                            .doc = "Number of scanlines (required)",
                                        },
                                        { 0 } };

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'o':
      arguments->output_file = arg;
      break;
    case 'w':
      arguments->image_width = atoi (arg);
      if (!arguments->image_width)
        {
          fprintf (stderr, "Image width must be a valid integer value.\n");
          argp_usage (state);
        }
      break;
    case 'h':
      arguments->image_height = atoi (arg);
      if (!arguments->image_height)
        {
          fprintf (stderr, "Image height must be a valid integer value.\n");
          argp_usage (state);
        }
      break;
    case 's':
      arguments->start_scanline = atoi (arg);
      if (!arguments->start_scanline && strcmp (arg, "0"))
        {
          fprintf (stderr, "Starting scanline must be a valid integer value.\n");
          argp_usage (state);
        }
      break;
    case 'n':
      arguments->num_scanlines = atoi (arg);
      if (!arguments->num_scanlines)
        {
          fprintf (stderr, "Number of scanlines must be a valid integer value.\n");
          argp_usage (state);
        }
      break;
    case ARGP_KEY_END:
      if (!arguments->image_height || !arguments->image_width || !arguments->num_scanlines)
        {
          fprintf (stderr, "Required argument missing.\n");
          argp_usage (state);
        }

      if (arguments->image_height - 1 < arguments->start_scanline)
        {
          fprintf (stderr, "Starting scanline bigger than image.\n");
          argp_usage (state);
        }
      if (arguments->start_scanline + arguments->num_scanlines > arguments->image_height)
        {
          fprintf (stderr, "Starting scanline and number of scanlines bigger than image.\n");
          argp_usage (state);
        }
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
struct argp argp = {
  .options = options,
  .parser  = parse_opt,
  .doc     = doc,
};

/* Default values. */
arguments_t args = { 0 };
