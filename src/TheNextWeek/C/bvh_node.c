#include "bvh_node.h"
#include "aabb.h"
#include "error.h"
#include "hittable_list.h"
#include "interval.h"
#include "ray.h"
#include "sphere.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Returns `true` if ray hits an object.
// Return values are in `rec`.
static bool
bvh_node_hit (ray_t const r, interval_t intvl, hit_record_t *rec)
{
  bvh_node_t *bvh_node = (bvh_node_t *)rec->object;

  if (!aabb_hit (bvh_node->bbox, &r, intvl))
    {
      return false;
    }

  // recurse left
  rec->object   = bvh_node->left;
  auto hit_left = bvh_node->left->hit (r, intvl, rec);

  // recurse right
  rec->object    = bvh_node->right;
  auto intvl_tmp = (interval_t){ intvl.low, hit_left ? rec->t : intvl.high };
  auto hit_right = bvh_node->right->hit (r, intvl_tmp, rec);

  return hit_left || hit_right;
}

// Compare Functions

static int
box_compare (hittable_t const **a, hittable_t const **b, int axis_index)
{
  auto a_axis_interval = aabb_axis_interval ((*a)->bbox, axis_index);
  auto b_axis_interval = aabb_axis_interval ((*b)->bbox, axis_index);
  return a_axis_interval.low - b_axis_interval.low;
}

static int
box_x_compare (const void *a, const void *b)
{
  return box_compare ((hittable_t const **)a, (hittable_t const **)b, 0);
}

static int
box_y_compare (const void *a, const void *b)
{
  return box_compare ((hittable_t const **)a, (hittable_t const **)b, 1);
}

static int
box_z_compare (const void *a, const void *b)
{
  return box_compare ((hittable_t const **)a, (hittable_t const **)b, 2);
}

// Builds BVH (Boundary Volume Hierarchy).
static bvh_node_t *
bvh_node_new_hierarchy (hittable_t **objects, size_t start, size_t end)
{
  int axis = random_int_min_max (0, 2);

  auto comparator = (axis == 0) ? box_x_compare : (axis == 1) ? box_y_compare : box_z_compare;

  size_t object_span = end - start;

  bvh_node_t *bvh_node = malloc (sizeof *bvh_node);
  if (!bvh_node)
    {
      logExit ("Not enough memory");
    }

  bvh_node->hit_type = BVH_NODE;
  bvh_node->hit      = bvh_node_hit;

  switch (object_span)
    {
    case 1:
      bvh_node->left  = objects[start];
      bvh_node->right = objects[start];
      break;
    case 2:
      bvh_node->left  = objects[start];
      bvh_node->right = objects[start + 1];
      break;
    default:
      qsort (objects + start, object_span, sizeof (hittable_t *), comparator);
      auto mid        = start + object_span / 2;
      bvh_node->left  = (hittable_t *)bvh_node_new_hierarchy (objects, start, mid);
      bvh_node->right = (hittable_t *)bvh_node_new_hierarchy (objects, mid, end);
    }

  bvh_node->bbox = aabb_from_aabbs (bvh_node->left->bbox, bvh_node->right->bbox);
  return bvh_node;
}

// Builds a BVH from hittable `objects`.
bvh_node_t *
bvh_node_new (hittable_t **objects)
{
  return bvh_node_new_hierarchy (objects, 0, arrlen (objects));
}

void
print_bvh (bvh_node_t *node, int indent_lvl)
{
  switch (node->hit_type)
    {
    case SPHERE:
      print_sphere ((sphere_t *)node, indent_lvl + 2);
      break;
    case HITTABLE_LIST:
      print_hittable_list ((hittable_list_t *)node, indent_lvl + 2);
      break;
    case BVH_NODE:
      fprintf (stderr, "%*sBVH (%f %f) (%f %f) (%f %f)\n", indent_lvl, "", node->bbox->x_intvl.low,
               node->bbox->x_intvl.high, node->bbox->z_intvl.low, node->bbox->z_intvl.high, node->bbox->z_intvl.low,
               node->bbox->z_intvl.high);
      print_bvh ((bvh_node_t *)node->left, indent_lvl + 2);
      print_bvh ((bvh_node_t *)node->right, indent_lvl + 2);
      break;
    }
}