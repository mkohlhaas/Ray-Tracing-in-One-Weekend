project(
  'raytracer',
  'c',
  version: '0.1',
  default_options: ['warning_level=3', 'werror=false', 'c_std=gnu23'],
)

# math library
cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

source_files = files('main.c', 'vec3.c', 'color.c')

executable('raytracer', source_files, dependencies: m_dep, install: false)
