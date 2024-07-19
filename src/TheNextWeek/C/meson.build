project(
  'raytracer',
  'c',
  version: '0.1',
  default_options: ['warning_level=3', 'werror=false', 'c_std=gnu2x'],
)

# filesystem module
fs = import('fs')
fs.copyfile('earthmap.jpg')
fs.copyfile('earthmap.png')
fs.copyfile('world-map.jpg')
fs.copyfile('HR-World-Map.jpg')

# math library
cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

source_files = files(
  'aabb.c',
  'args.c',
  'bounding_spheres_scene.c',
  'bvh_node.c',
  'camera.c',
  'checker_texture.c',
  'checkered_spheres_scene.c',
  'color.c',
  'dielectric.c',
  'earth_scene.c',
  'globals.c',
  'hittable_list.c',
  'image.c',
  'image_texture.c',
  'interval.c',
  'lambertian.c',
  'main.c',
  'material.c',
  'metal.c',
  'noise_texture.c',
  'perlin.c',
  'perlin_spheres_scene.c',
  'point.c',
  'ray.c',
  'solid_color.c',
  'sphere.c',
  'sphere.c',
  'utils.c',
  'vec3.c',
  'world.c',
)

executable('raytracer', source_files, dependencies: [m_dep], install: false)
