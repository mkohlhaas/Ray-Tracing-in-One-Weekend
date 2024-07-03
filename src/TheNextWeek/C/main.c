#include "main.h"

int
main (int argc, char *argv[])
{
  argp_parse (&argp, argc, argv, 0, 0, &args);
  init ();
  render ();
  cleanup ();
}
