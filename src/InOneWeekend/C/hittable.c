#include "hittable.h"

// The parameter `outward_normal` is assumed to have unit length.
void
set_face_normal (hit_record *rec, ray const r, vec3 const outward_normal)
{

  rec->front_face = vec3_dot_product (r.direction, outward_normal) < 0;
  rec->normal     = rec->front_face ? outward_normal : vec3_minus (outward_normal);
}
