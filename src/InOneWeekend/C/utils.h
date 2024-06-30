#pragma once

#include "color.h"

double  degrees_to_radians (double degrees);
double  random_double (void);
double  random_double_min_max (double min, double max);
double  linear_to_gamma (double linear_component);
double  squared (double x);
char   *remove_leading_0s (char *s);
color_t lerp (color_t c1, color_t c2, double a);
