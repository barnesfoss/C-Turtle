project(
    'cturtle',
    'cpp',
    version: '1.0.5',
    meson_version: '>=1.1.0',
    default_options: [
        'cpp_std=c++17',
    ],
    license: 'MIT',
    license_files: 'LICENSE.txt',
)

CImg = subproject('CImg')

cturtle_deps = [dependency('CImg')]

if host_machine.system() == 'linux'
    cturtle_deps += dependency('x11')
endif

cturtle_inc = include_directories('src/include')

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
    'src/turtle/OfflineTurtleScreen.cpp',
    'src/turtle/PenState.cpp',
    'src/turtle/draw.cpp',
    # 'src/turtle/headless.cpp'
    'src/turtle/math.cpp',
    'src/turtle/movement.cpp',
    'src/turtle/pen.cpp',
    'src/turtle/turtle.cpp',
    # Types
    'src/types/Color.cpp',
    # Utilities
    'src/util/base64.cpp',
    'src/util/io.cpp',
)
cturtle_args = []

if get_option('headless').enabled()
  cturtle_args += '-DCTURTLE_HEADLESS'
endif

cturtle_lib = static_library(
    'cturtle',
    cturtle_sources,
    dependencies: cturtle_deps,
    include_directories: cturtle_inc,
)

cturtle_dep = declare_dependency(
    link_with: cturtle_lib,
    dependencies: cturtle_deps,
    include_directories: cturtle_inc,
)

meson.override_dependency('cturtle', cturtle_dep)

