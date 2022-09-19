cmake_minimum_required(VERSION 3.23)
project(untitled26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(glm)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(raytracer main.cpp
        scenes/FirefliesApp.cpp
        raytracing/object/Sphere.cpp
        raytracing/scene/Scene.cpp
        raytracing/scene/Camera.cpp
        raytracing/object/Plane.cpp
        raytracing/object/Cylinder.cpp
        raytracing/light/DirectionalLight.cpp
        raytracing/light/PointLight.cpp
        raytracing/tools/Math.cpp
        scenes/Firefly.cpp)

target_compile_options(raytracer PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic>)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(raytracer PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>: /arch:AVX2 /fp:fast>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -march=native -ffast-math>)
endif ()

target_include_directories(raytracer SYSTEM PRIVATE extern raytracing)

target_link_libraries(raytracer PRIVATE
        Threads::Threads
        glm
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:tbb>
        $<$<PLATFORM_ID:Windows>:user32 gdi32 opengl32 gdiplus Shlwapi dwmapi>
        $<$<PLATFORM_ID:Linux>:X11 GL png>)

target_compile_definitions(raytracer PRIVATE
        __TBB_show_deprecation_message_task_H
        LOGGING)


include(CheckIPOSupported)
check_ipo_supported(RESULT LTO_SUPPORTED OUTPUT error)
set_property(TARGET raytracer PROPERTY INTERPROCEDURAL_OPTIMIZATION ${LTO_SUPPORTED})

set(FETCHCONTENT_FULLY_DISCONNECTED ON CACHE BOOL "This has been reset to ON (set to OFF to download again)" FORCE)
