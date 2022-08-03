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


#set(BOOST_ROOT "../dash-devnet-tool/boost")


# GET BOOST LIBRARY -> ONLY NEEDS PROCESS
# WILL INTERRUPT CMAKE ON NOT FOUND THROUGH REQUIRED
find_package(Boost 1.79 REQUIRED)


set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
# CONFIGURE AS LIBRARY
set(LIB_DOCKER _docker_library)
add_library(${LIB_DOCKER} SHARED ${DOCKER_SOURCES})
# DECLARE HEADER LIBRARY HEADER
target_include_directories(${LIB_DOCKER} PUBLIC include/public)
target_include_directories(${LIB_DOCKER} PRIVATE include/private)
# INCLUDE FOUND BOOST HEADER
target_include_directories(${LIB_DOCKER} PRIVATE ${BOOST_INCLUDE_DIRS})
# SET OPTIONAL COMPILE FLAGS
target_compile_options(${LIB_DOCKER} PRIVATE -Wno-narrowing)
