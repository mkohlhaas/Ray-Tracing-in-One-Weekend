#include "args.h"

const char *argp_program_version = "raytracer 1.0";

static char doc[] = "Raytracer based on \"Raytracer in a Weekend 1\"";

static struct argp_option options[] = { {
                                            .name = "output",
                                            .key  = 'o',
                                            .arg  = "FILE",
                                            .doc  = "Output to FILE instead of standard output",
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
