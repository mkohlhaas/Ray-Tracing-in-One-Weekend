#pragma once

#include "vec3.h"
#include <stdio.h>

typedef vec3 color;

extern color blue;
extern color red;
extern color white;
extern color black;

void write_color (FILE *out, const color pixel_color);
