cmake_minimum_required(VERSION 3.20)
project(rhomboid LANGUAGES CXX)

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find CGAL
find_package(CGAL REQUIRED COMPONENTS Core)

if(CGAL_FOUND)
    # Common sources
    set(DEPENDENCIES
        src/rhomboid.cpp
        src/utils.cpp
    )

    # Main executable
    add_executable(main src/main.cpp ${DEPENDENCIES})
    target_link_libraries(main CGAL::CGAL CGAL::CGAL_Core)

    # 2D tests
    add_executable(tests_2d src/tests_2d.cpp ${DEPENDENCIES})
    target_link_libraries(tests_2d CGAL::CGAL CGAL::CGAL_Core)
    target_include_directories(tests_2d PRIVATE ${CMAKE_SOURCE_DIR})

    # 3D tests
    add_executable(tests_3d src/tests_3d.cpp ${DEPENDENCIES})
    target_link_libraries(tests_3d CGAL::CGAL CGAL::CGAL_Core)
    target_include_directories(tests_3d PRIVATE ${CMAKE_SOURCE_DIR})

else()
    message(STATUS "NOTICE: This demo requires CGAL and will not be compiled.")
endif()

