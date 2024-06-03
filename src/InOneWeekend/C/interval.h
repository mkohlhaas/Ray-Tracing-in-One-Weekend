#pragma once

#include <stdbool.h>

typedef struct interval
{
  double min, max;
} interval;

double size (interval i);
bool   contains (interval i, double x);
bool   surrounds (interval i, double x);
