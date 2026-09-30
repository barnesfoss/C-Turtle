project(
    'CImg',
    'c',
    license: ['CeCILL-C V1', 'CeCILL V2'],
    # license_files: ['License_CeCILL-C_V1-en.txt','License_CeCILL_V2-en.txt'],
    version: 'v.4.0.5',
)

cimg_dep = declare_dependency(
    include_directories: include_directories('.'),
)

meson.override_dependency('CImg', cimg_dep)
