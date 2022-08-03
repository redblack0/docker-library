cmake_minimum_required(VERSION 3.4.0)

project(docker-library CXX)


# ---


# SET DOCKER SOURCE FILES
set(DOCKER_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/docker.cpp"
        ## dependency layer
    "${CMAKE_CURRENT_SOURCE_DIR}/src/network.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/container.cpp"
        ## dependency layer
    "${CMAKE_CURRENT_SOURCE_DIR}/src/factory.cpp")


# ---


if(NOT DEFINED BOOST_ROOT)
    message(STATUS "Boost root was not defined from outside.")
    message(STATUS "Trying to use local boost directory ${CMAKE_CURRENT_SOURCE_DIR}/boost")
    set(BOOST_ROOT "boost")
else()
    message(STATUS "using defined boost root on ${BOOST_ROOT}")
endif()


find_package(Boost 1.79 REQUIRED)
message(STATUS "found valid boost headers")
message(STATUS "")
set(LIB_DOCKER _docker_library)
add_library(${LIB_DOCKER} SHARED ${DOCKER_SOURCES})
# DECLARE HEADER LIBRARY HEADER
target_include_directories(${LIB_DOCKER}    PUBLIC include/public
                                            PRIVATE include/private
                                            PRIVATE ${Boost_INCLUDE_DIRS})
# SET OPTIONAL COMPILE FLAGS
target_compile_options(${LIB_DOCKER} PRIVATE -Wno-narrowing)


# ---

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
