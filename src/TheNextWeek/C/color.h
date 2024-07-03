#pragma once

#include "vec3.h"
#include <stdio.h>

typedef vec3_t color_t;

// global colors
extern color_t blue;
extern color_t light_blue;
extern color_t red;
extern color_t white;
extern color_t black;
extern color_t yellow;

void write_color (FILE *out, const color_t pixel_color);
