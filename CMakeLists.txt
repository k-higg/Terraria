cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    add_compile_options(/arch:AVX2) # Make sure SIMD optimizations take place
else()
    if(NOT APPLE)
        add_link_options(-static-libstdc++ -static-libgcc)
    endif()
    add_compile_options(-mavx2 -mfma) # Make sure SIMD optimizations take place
endif()

# Ensure Raylib is build as a static lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as a static lib" FORCE)

project(Terraria)

add_subdirectory(thirdParty/raylib-5.0)
add_subdirectory(thirdParty/imgui-docking)
add_subdirectory(thirdParty/rlimgui)

# define sources
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

message(STATUS "Sources: ${MY_SOURCES}")

add_executable("${CMAKE_PROJECT_NAME}")
set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

if(PRODUCTION_BUILD)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
    
    # Remove this to debug assets
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MSVC)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    
    if(PRODUCTION_BUILD)
        set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()

elseif(MINGW)
    if(PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -mwindows)
    endif()

elseif(APPLE OR UNIX)
    if(PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
    endif()
endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/platform"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/gameLayer"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/imguiLayer"
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib_static 
    imgui 
    rlimgui
)
