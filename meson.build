
project(
  'cturtle',
  'cpp',
  version: '1.0.5',
  meson_version: '>=1.1.0',
  default_options: [
    'cpp_std=c++17',
  ],
)


cturtle_deps = []

if host_machine.system() == 'linux'
  cturtle_deps += dependency('x11')
endif

cturtle_inc = include_directories('src', 'CImg/')

cturtle_dep = declare_dependency(
  include_directories: cturtle_inc,
  dependencies: cturtle_deps,
)

meson.override_dependency('cturtle', cturtle_dep)
