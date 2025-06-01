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
src/math/noise/perlin.h
)

set(SRC_SCENES
src/scenes/scene.h
)

set(SRC_CORE 
src/core/ray.h
src/core/camera.h
)

set(SRC_HITTABLE
src/hittable/hittable.h
src/hittable/sphere.h
src/hittable/hittable_list.h
src/hittable/quad.h
src/hittable/transform.h
)

set(SRC_UTIL
src/util/constants.h
src/util/rtweekend.h
src/util/interval.h
src/util/random_util.h
)

set(SRC_MATERIAL
src/materials/material.h
src/materials/lambertian.h
src/materials/metal.h
src/materials/dielectric.h
)

set(SRC_LIGHTS
src/materials/lights/diffuse_light.h
)

set(SRC_TEXTURE
src/materials/textures/texture.h
src/materials/textures/solid_color.h
src/materials/textures/checker.h
src/materials/textures/image.h
)

set(SRC_ACCELERATION
src/acceleration/bvh/aabb.h
src/acceleration/bvh/bvh.h
)

set(SRC_MAIN
src/main.cxx
)

set(SOURCES 
    ${SRC_MAIN}
)

set(SRC_EXTERNAL
lib/external/stb/stb_image.h
lib/external/stb/rtw_stb_image.h
)

add_executable(pathTracer ${SOURCES})

target_sources(pathTracer PUBLIC
    ${SRC_MATH}
    ${SRC_CORE}
    ${SRC_HITTABLE}
    ${SRC_UTIL}
    ${SRC_MATERIAL}
    ${SRC_TEXTURE}
    ${SRC_SCENES}
    ${SRC_ACCELERATION}
    ${SRC_EXTERNAL}
    ${SRC_LIGHTS}
    # You don't usually add headers here unless you have header-only files or want them listed for IDEs
)

# Optimized release target with O3 and fast math
add_executable(pathTracerOptimized ${SOURCES})
target_sources(pathTracerOptimized PUBLIC
    ${SRC_MATH}
    ${SRC_CORE}
    ${SRC_HITTABLE}
    ${SRC_UTIL}
    ${SRC_MATERIAL}
    ${SRC_TEXTURE}
    ${SRC_SCENES}
    ${SRC_ACCELERATION}
    ${SRC_EXTERNAL}
    ${SRC_LIGHTS}
)

# Set optimization flags for the optimized target
target_compile_options(pathTracerOptimized PRIVATE
    -O3
    -ffast-math
    -march=native
    -DNDEBUG
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)
target_include_directories(pathTracer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)
