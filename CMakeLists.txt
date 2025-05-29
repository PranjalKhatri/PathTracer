cmake_minimum_required(VERSION 3.27.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "To generate compile commands.json")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(PathTracer 
        VERSION 0.1.0 
        DESCRIPTION "A modern c++ PathTracer")

set(SRC_MATH 
src/math/vec3.h
src/math/color.h
)

set(SRC_CORE 
src/core/ray.h
src/core/camera.h
)

set(SRC_HITTABLE
src/hittable/hittable.h
src/hittable/sphere.h
src/hittable/hittable_list.h
)

set(SRC_UTIL
src/util/constants.h
src/util/rtweekend.h
src/util/interval.h
src/util/random_util.h
)

set(SRC_MAIN
src/main.cxx
)

set(SOURCES 
    ${SRC_MAIN}
    src/all_includes.cxx
)

set(SRC_MATERIAL
src/materials/material.h
src/materials/lambertian.h
src/materials/metal.h
src/materials/dielectric.h
)

add_executable(pathTracer ${SOURCES})

target_sources(pathTracer PUBLIC
    ${SRC_MATH}
    ${SRC_CORE}
    ${SRC_HITTABLE}
    ${SRC_UTIL}
    ${SRC_MATERIAL}
    # You don't usually add headers here unless you have header-only files or want them listed for IDEs
)
target_include_directories(pathTracer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
