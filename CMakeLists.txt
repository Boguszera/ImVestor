cmake_minimum_required(VERSION 3.20)


project(ImVestor
    VERSION 1.0.0
    DESCRIPTION "ImVestor"
    LANGUAGES CXX
)

# configuration options
# option(USE_SYSTEM_SFML ON)
option(ENABLE_SANITIZERS OFF)

# compiler configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if(ENABLE_SANITIZERS AND NOT MSVC)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# dependency (SFML 3.0.0)
# if(USE_SYSTEM_SFML)
    find_package(SFML 3.0 REQUIRED COMPONENTS 
        Graphics
        Window
        System
        Audio
    )
    
    message(STATUS "Found SFML version: ${SFML_VERSION}")
# else()
#    include(FetchContent)
#    FetchContent_Declare(
#        sfml
#        GIT_REPOSITORY https://github.com/SFML/SFML.git
#        GIT_TAG 3.0.0
#    )
#    FetchContent_MakeAvailable(sfml)
# endif()

# project structure
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/gui/*.cpp")
file(GLOB_RECURSE APP_HEADERS CONFIGURE_DEPENDS "src/*.hpp" "src/gui/*.hpp")

# copy assets (font)
file(COPY ${CMAKE_SOURCE_DIR}/src/assets
     DESTINATION ${CMAKE_BINARY_DIR})
message(STATUS "Kopiowanie zasobów: ${CMAKE_SOURCE_DIR}/assets do ${CMAKE_BINARY_DIR}/assets")

add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# link with SFML 3.0.0
target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# installation of resources
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    file(GLOB_RECURSE ASSET_FILES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
    foreach(ASSET ${ASSET_FILES})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                ${ASSET}
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/"
        )
    endforeach()
endif()

# organization for IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source" FILES ${APP_SOURCES} ${APP_HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Application")