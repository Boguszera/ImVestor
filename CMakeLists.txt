cmake_minimum_required(VERSION 3.10)

project(ImVestor)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# SFML - manually add directories
set(SFML_DIR "D:/SFML/SFML-3.0.0/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "D:/SFML/SFML-3.0.0/include")
set(SFML_LIB_DIR "D:/SFML/SFML-3.0.0/lib")

# Add SFML to the include directories
include_directories(${SFML_INCLUDE_DIR})

# Add the SFML libraries manually
link_directories(${SFML_LIB_DIR})

# Add all .cpp files
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Create executable
add_executable(ImVestor ${SOURCES})

# Link SFML libraries manually
target_link_libraries(ImVestor PRIVATE sfml-system sfml-window sfml-graphics)
