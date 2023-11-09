cmake_minimum_required(VERSION 3.14)

project(MyEndianLib VERSION 1.0 DESCRIPTION "My Endian Library")

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Uncomment the following line if your project requires a source file
# target_sources(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp)

# Install and export steps
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT MyEndianLibTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT MyEndianLibTargets
    FILE MyEndianLibTargets.cmake
    NAMESPACE MyEndianLib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyEndianLib
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
