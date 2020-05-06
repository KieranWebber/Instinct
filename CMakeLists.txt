cmake_minimum_required(VERSION 3.10)
project(instinct)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

## Install library headers
file(GLOB HEADERS include/*.h)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
install(TARGETS
        ${PROJECT_NAME}
        EXPORT InstinctTargets
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

include ( CMakePackageConfigHelpers )

set(CONF_INCLUDE_DIRS "\${Instinct_CMAKE_DIR}/${REL_INCLUDE_DIR}")
set(CMAKE_CONFIG_DEST "${CMAKE_INSTALL_DATADIR}/Instinct/cmake")


export(TARGETS
    ${PROJECT_NAME}
    NAMESPACE Instinct::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/InstinctTargets.cmake"
    )

configure_package_config_file(
        "Instinct.cmake.in"
        "${CMAKE_BINARY_DIR}/InstinctConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_CONFIG_DEST}"
        PATH_VARS
        CONF_INCLUDE_DIRS
)
install (EXPORT
        InstinctTargets
        DESTINATION ${CMAKE_CONFIG_DEST}
        NAMESPACE Instinct::
        )

install (FILES
        "${CMAKE_BINARY_DIR}/InstinctConfig.cmake"
        DESTINATION "${CMAKE_CONFIG_DEST}")