# Copyright by Michal Majczak, 2016
# Licensed under the MIT license:
# http://www.opensource.org/licenses/mit-license.php
#
# Author: Michal Majczak <michal.majczak92@gmail.com>

cmake_minimum_required (VERSION 3.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

##########################################
## Project info
##########################################

set( PROJECT_NAME space-rush )
set( TARGET_NAME "${PROJECT_NAME}.out" )
project( ${PROJECT_NAME} )

##########################################
## EXE info
##########################################

file(GLOB_RECURSE TARGET_SRC src/*.cpp)
file(GLOB_RECURSE TARGET_HEADERS src/*.h src/*.hpp )
file(GLOB_RECURSE TARGET_SHADERS res/*.fsh  res/*.vsh)

include_directories( src/ )

# compiler specific flags
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    # using clang
	add_definitions( -Wall  -Wextra )
	add_definitions( -std=c++11 )
	add_definitions( -O2 )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
    # using gcc
	add_definitions( -Wall  -Wextra )
	add_definitions( -std=c++11 )
	add_definitions( -O2 )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    # using msvc
	#add_definitions( -std=c++11 )
endif()

# Windows workarounds
if( WIN32 )
  # location of master lib folder
  set( WIN_LIB_DIR "${CMAKE_SOURCE_DIR}/libs" )
  # lib locations
  set( CMAKE_PREFIX_PATH "${WIN_LIB_DIR}/glew")
  set( GLM_ROOT_DIR "${WIN_LIB_DIR}/glm")
  set( ENV{SDL2DIR} "${WIN_LIB_DIR}/SDL2")
  set( ASSIMP_ROOT_DIR "${WIN_LIB_DIR}/assimp")
  set( SOIL_ROOT_DIR "${WIN_LIB_DIR}/soil")
  set( BULLET_ROOT  "${WIN_LIB_DIR}/bullet")
  set( ENV{SDL2TTFDIR}  "${WIN_LIB_DIR}/SDL2_ttf")
  SET( ENV{FREETYPE_DIR} "${WIN_LIB_DIR}/Freetype" )
  SET( FREETYPE_BIN "${WIN_LIB_DIR}/Freetype/bin" )
  # libraries needed when linking SDL2 statically
  set( LIBRARIES "version.lib;imm32.lib;winmm.lib;")
endif( WIN32 )

##########################################
## Linking dynamic libraries
##########################################

# Find SDL2
find_package(SDL2 REQUIRED)
if( SDL2_FOUND )
  include_directories( ${SDL2_INCLUDE_DIR} )
  set( LIBRARIES ${LIBRARIES} ${SDL2_LIBRARY} )
endif( SDL2_FOUND )

# Find SDL2 TTF
find_package(SDL2TTF REQUIRED)
if( SDL2TTF_FOUND )
  include_directories( ${SDL2TTF_INCLUDE_DIR} )
  set( LIBRARIES ${LIBRARIES} ${SDL2TTF_LIBRARY} )
endif( SDL2TTF_FOUND )

# Find GLEW
set(GLEW_USE_STATIC_BUILDS ON)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories( ${GLEW_INCLUDE_DIRS} )
    set( LIBRARIES ${LIBRARIES} ${GLEW_LIBRARIES} )
endif(GLEW_FOUND)

# Find GLM
find_package(GLM REQUIRED)
if( GLM_FOUND )
  include_directories( ${GLM_INCLUDE_DIRS} )
  set( LIBRARIES ${LIBRARIES} ${GLM_LIBRARIES} )
endif( GLM_FOUND )

# Find OpenGL
find_package( OpenGL 3.3 REQUIRED )
if( OPENGL_FOUND )
  set( LIBRARIES ${LIBRARIES} ${OPENGL_LIBRARIES} )
  include_directories( ${OPENGL_INCLUDE_DIR} )
endif( OPENGL_FOUND )

# Find assimp
find_package( ASSIMP REQUIRED )
if( ASSIMP_FOUND )
  set( LIBRARIES ${LIBRARIES} ${ASSIMP_LIBRARIES} )
  include_directories( ${ASSIMP_INCLUDE_DIR} )
endif( ASSIMP_FOUND )

# Find SOIL
find_package( SOIL REQUIRED )
if( SOIL_FOUND )
  set( LIBRARIES ${LIBRARIES} ${SOIL_LIBRARIES} )
  include_directories( ${SOIL_INCLUDE_DIR} )
endif( SOIL_FOUND )

# Find bullet
find_package( BULLET REQUIRED )
if( BULLET_FOUND )
  set( LIBRARIES ${LIBRARIES} ${BULLET_LIBRARIES} )
  include_directories( ${BULLET_INCLUDE_DIRS} )
endif( BULLET_FOUND )

if( WIN32 )
  # Find bullet
  find_package( FREETYPE REQUIRED )
  if( FREETYPE_FOUND )
    set( LIBRARIES ${LIBRARIES} ${FREETYPE_LIBRARIES} )
    include_directories( ${FREETYPE_INCLUDE_DIRS} )
  endif( FREETYPE_FOUND )
endif( WIN32 )

##########################################
## Add Executable
##########################################

if( WIN32 )
  add_custom_target(copy-resource-files ALL
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/Release/res
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/Debug/res
    DEPENDS ${TARGET_NAME})

  add_custom_target(copy-dll-files ALL
    COMMAND cmake -E copy ${FREETYPE_BIN}/freetype6.dll ${CMAKE_BINARY_DIR}/Release/
	  COMMAND cmake -E copy ${FREETYPE_BIN}/zlib1.dll ${CMAKE_BINARY_DIR}/Release/
    DEPENDS ${TARGET_NAME})
else( WIN32 )
  add_custom_target(copy-resource-files ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
	DEPENDS ${TARGET_NAME})
endif( WIN32 )

add_executable(${TARGET_NAME} ${TARGET_SRC} ${TARGET_HEADERS} ${TARGET_SHADERS})
target_link_libraries(${TARGET_NAME} ${LIBRARIES})
