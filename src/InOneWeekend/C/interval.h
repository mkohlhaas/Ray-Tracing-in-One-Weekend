#pragma once

#include <stdbool.h>

typedef struct interval
{
  double min, max;
} interval;

extern interval empty;
extern interval universe;

double itvl_size (interval i);
bool   itvl_contains (interval i, double x);
bool   itvl_surrounds (interval i, double x);
double itvl_clamp (interval i, double x);
