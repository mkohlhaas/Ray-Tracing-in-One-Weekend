#pragma once

#include <math.h>
#include <stdbool.h>

typedef struct interval
{
  double min, max;
} interval;

extern interval empty;
extern interval universe;

double size (interval i);
bool   contains (interval i, double x);
bool   surrounds (interval i, double x);
