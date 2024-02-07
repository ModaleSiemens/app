# Project description
project(
    'Modale\'s "app"',
    'cpp',
    version: '1.0.0',

    default_options: [
        'cpp_std=c++23'
    ] 
)

# All necessary things to build TGUI as a subproject
cmake = import('cmake')

cmake_proj_opts = cmake.subproject_options()

cmake_proj_opts.add_cmake_defines({'TGUI_BACKEND' : 'SFML_GRAPHICS'})
cmake_proj_opts.add_cmake_defines({'CMAKE_BUILD_TYPE' : 'Release'})
cmake_proj_opts.add_cmake_defines({'TGUI_BUILD_GUI_BUILDER' : 'true'})
cmake_proj_opts.add_cmake_defines({'CMAKE_UNITY_BUILD' : 'false'})


tgui_proj   = cmake.subproject(
    'tgui',
    options: cmake_proj_opts
)

# Parse source directory
subdir('src')

# Create dependencies
deps = [
    dependency('tgui')
]

# Set include directories
inc = include_directories('include')

# Declare library
lib_app = library(
    'app',
    src,

    include_directories: inc,
    dependency         : deps
)

# Declare dependency
lib_app_dep = declare_dependency(
    include_directories: inc,
    link_with          : lib_app,
    dependencies       : deps
)