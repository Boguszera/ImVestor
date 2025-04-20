cmake_minimum_required(VERSION 3.10)

project(ImVestor)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# add all .cpp files 
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# create executable file
add_executable(ImVestor ${SOURCES})