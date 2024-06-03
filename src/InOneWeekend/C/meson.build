project(
  'raytracer',
  'c',
  version: '0.1',
  default_options: ['warning_level=3', 'werror=false', 'c_std=gnu23'],
)

glib_deb = dependency('glib-2.0')

# math library
cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

source_files = files(
  'color.c',
  'hittable.c',
  'interval.c',
  'main.c',
  'point.c',
  'ray.c',
  'sphere.c',
  'sphere.c',
  'utils.c',
  'vec3.c',
)

executable('raytracer', source_files, dependencies: [m_dep, glib_deb], install: false)
