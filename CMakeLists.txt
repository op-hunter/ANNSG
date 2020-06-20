cmake_minimum_required(VERSION 3.12)

project(annsg)
include_directories(${PROJECT_SOURCE_DIR}/include)
message(${PROJECT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(src srcs)

set(alg_src
    ${srcs}
    )

add_executable(test_annsg tests/test_annsg.cpp src/ANNSG.cpp)
target_link_libraries(test_annsg
                      pthread)
#add_subdirectory(src)
#add_subdirectory(tests)