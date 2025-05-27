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
)

set(SRC_MAIN
src/main.cxx
)

set(SOURCES 
    ${SRC_MAIN}
)
add_executable(pathTracer ${SOURCES})

target_sources(pathTracer PUBLIC
    ${SRC_MATH}
    ${SRC_CORE}
    # You don't usually add headers here unless you have header-only files or want them listed for IDEs
)
target_include_directories(pathTracer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
