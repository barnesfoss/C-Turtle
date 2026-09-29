project(
  'cturtle',
  'cpp',
  version: '1.0.5',
  meson_version: '>=1.1.0',
  default_options: [
    'cpp_std=c++17',
  ],
  license: 'MIT',
  license_files: 'LICENSE.txt'
)

CImg = subproject('CImg')
cturtle_deps = [
  dependency('CImg')
]

if host_machine.system() == 'linux'
  cturtle_deps += dependency('x11')
endif

cturtle_inc = include_directories('src')

cturtle_dep = declare_dependency(
  dependencies: cturtle_deps,
  include_directories: cturtle_inc,
)

meson.override_dependency('cturtle', cturtle_dep)
