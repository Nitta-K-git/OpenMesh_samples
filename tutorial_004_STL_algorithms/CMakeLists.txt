cmake_minimum_required( VERSION 3.6 )
option(USE_QT_SYSTEM "Use Qt system" OFF) # https://www.wagavulin.jp/entry/2011/11/27/222650
set(USE_QT_SYSTEM OFF)

# Create Project
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME) # https://stackoverflow.com/questions/12344368/automatically-use-the-directory-as-the-project-name-in-cmake
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)
message(${ProjectId})

if(MSVC)
   # add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>") # これ単体でも同様
   add_compile_options("/utf-8")
   # project()の後でないとコンパイラの判定ができない
   # target設定の前に実行する必要がある https://stackoverflow.com/questions/40516794/cmake-not-applying-compile-option-using-add-compile-options
endif()

if(POLICY CMP0074) # https://github.com/PointCloudLibrary/pcl/issues/2425
   cmake_policy(SET CMP0074 NEW)
endif()
# Find OpenMesh Package
set( OpenMesh_ROOT "C:/Program Files/OpenMesh")
find_package( OpenMesh REQUIRED )
# if(OpenMesh_FOUND)
#    message("OpenMesh Found")
#    get_target_property(V OpenMeshCore INTERFACE_INCLUDE_DIRECTORIES) 
#    message(${V})
# else()
#    message("OpenMesh not Found")
# endif()

if(USE_QT_SYSTEM)
   # set(Qt5_DIR $ENV{QTDIR})
   set(Qt5_DIR C:/Qt2/5.12.3/msvc2017_64)
   list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})
   find_package(Qt5 COMPONENTS Widgets REQUIRED)

   # Set Automatic MOC
   set(CMAKE_AUTOMOC ON)
   set(CMAKE_AUTORCC ON)
   set(CMAKE_AUTOUIC ON)
   if(CMAKE_VERSION VERSION_LESS "3.7.0")
      set(CMAKE_INCLUDE_CURRENT_DIR ON)
   endif()
endif()

set(SOURCE_FILES
   main.cpp
   smooth_algo.hh
)
set(TARGET_LINK_LIBRARIES
   OpenMeshCore
   OpenMeshTools
)
if(USE_QT_SYSTEM)
   set(TARGET_LINK_LIBRARIES
      ${TARGET_LINK_LIBRARIES}
      Qt5::Widgets
      Qt5::Core
   )
endif()

# Add Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Additional Include Directories
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Preprocessor Definitions
add_definitions(-D_USE_MATH_DEFINES) # Core/System/compiler.hhで定義が無いとエラーになる
# Additional Library Directories

# Additional Dependencies

target_link_libraries(${PROJECT_NAME} ${TARGET_LINK_LIBRARIES})
