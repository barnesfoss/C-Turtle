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
cc = meson.get_compiler('cpp')

if cc.get_id() == 'msvc'
    add_project_arguments('/bigobj', language: 'cpp')
endif

cturtle_args = []

cturtle_deps = [
  dependency('CImg'),
  dependency('giflib', default_options: ['tests=disabled','progs=disabled'])
]

if host_machine.system() == 'linux' or host_machine.system() == 'darwin'

    # CImg either needs X11 or SDL3 for windowing
    # SDL3 is prefered as it would automatically pick a native display
    # We use X11 as a fallback here
    sdl = dependency('sdl3', required: false)
    if sdl.found()
      cturtle_deps += sdl
      cturtle_args += '-Dcimg_display=3' # Tells CImg to use SDL 
    else
      cturtle_deps += dependency('x11', required: true)
      cturtle_args += '-Dcimg_display=1' # Tells CImg to use X11
    endif

elif host_machine.system() == 'windows'

    cturtle_deps += cc.find_library('kernel32')
    cturtle_deps += cc.find_library('gdi32')

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

