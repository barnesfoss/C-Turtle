project(
    'cturtle',
    'cpp',
    version: '1.0.5',
    meson_version: '>=1.1.0',
    default_options: [
        'cpp_std=c++17',
        'unity=on',
        'unity_size=8'
    ],
    license: 'MIT',
    license_files: 'LICENSE.txt',
)

cturtle_deps = [
  dependency('CImg'),
  dependency('giflib', default_options: ['tests=disabled','progs=disabled'])
]

if host_machine.system() == 'linux'
    cturtle_deps += dependency('x11')
endif

cturtle_sources = files(
    
    # Fonts
    'src/font/BitmapFont.cpp',
    # Geometry
    'src/geometry/Transform.cpp',
    'src/geometry/ivec2.cpp',
    # Shapes/Objects
    'src/objects/Circle.cpp',
    'src/objects/CompoundPolygon.cpp',
    'src/objects/Line.cpp',
    'src/objects/Polygon.cpp',
    'src/objects/SceneObject.cpp',
    'src/objects/Sprite.cpp',
    'src/objects/Text.cpp',
    # Turtle
    'src/turtle/AbstractTurtleScreen.cpp',
    'src/turtle/InteractiveTurtleScreen.cpp',
    'src/turtle/HeadlessTurtleScreen.cpp',
    'src/turtle/PenState.cpp',
    'src/turtle/draw.cpp',
    'src/turtle/math.cpp',
    'src/turtle/movement.cpp',
    'src/turtle/pen.cpp',
    'src/turtle/Turtle.cpp',
    # Types
    'src/types/Color.cpp',
    # Utilities
    'src/util/base64.cpp',
    'src/util/io.cpp',
    'src/util/CImgimpl.cpp',
)
cturtle_args = []

cturtle_lib = library(
    'cturtle',
    cturtle_sources,
    dependencies: cturtle_deps,
    include_directories: ['src/include','src/include/CTurtle'],
    cpp_args: cturtle_args,
)

cturtle_dep = declare_dependency(
    link_with: cturtle_lib,
    dependencies: cturtle_deps,
    include_directories: 'src/include',
    compile_args: cturtle_args,
)

meson.override_dependency('cturtle', cturtle_dep)

