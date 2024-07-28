project(
    'raytracer',
    'c',
    version: '0.1',
    default_options: ['warning_level=3', 'werror=false', 'c_std=gnu2x'],
)

# filesystem module
fs = import('fs')
fs.copyfile('make-it')
fs.copyfile('assets/earthmap.jpg')
fs.copyfile('assets/earthmap.png')
fs.copyfile('assets/world-map.jpg')
fs.copyfile('assets/HR-World-Map.jpg')

# math library
cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

source_files = files('main.c')

subdir('args')
subdir('bbox')
subdir('camera')
subdir('globals')
subdir('image')
subdir('hittables')
subdir('materials')
subdir('math')
subdir('noise')
subdir('ray')
subdir('scenes')
subdir('textures')
subdir('utils')
subdir('world')

incdir = include_directories(
    '3rd_party',
    'args',
    'bbox',
    'camera',
    'error',
    'globals',
    'hittables',
    'image',
    'materials',
    'math',
    'noise',
    'ray',
    'scenes',
    'textures',
    'utils',
    'world',
)

executable(
    'raytracer',
    source_files,
    dependencies: [m_dep],
    include_directories: incdir,
    install: false,
)
