cmake_minimum_required( VERSION 3.6 )

# option(USE_QT_SYSTEM "Use Qt system" OFF) # https://www.wagavulin.jp/entry/2011/11/27/222650
# set(USE_QT_SYSTEM OFF)

# Create Project
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME) # https://stackoverflow.com/questions/12344368/automatically-use-the-directory-as-the-project-name-in-cmake
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)
message(${ProjectId})

include(../general.cmake) # https://stackoverflow.com/questions/22804287/cmake-file-structure-how-to-split-a-cmakelists-txt-into-multiple-files

set(SOURCE_FILES
   main.cpp
)

# Add Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}) # https://stackoverflow.com/questions/28893450/how-to-get-debug-postfix-in-executable-name/29023980

# Additional Library Directories

# Additional Dependencies

target_link_libraries(${PROJECT_NAME} ${TARGET_LINK_LIBRARIES})
