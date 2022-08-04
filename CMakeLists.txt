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


message(STATUS "Check for Boost Root ...")
list(APPEND CMAKE_MESSAGE_INDENT "-- ")
if(NOT DEFINED BOOST_ROOT)
    message(STATUS "Boost root was not defined from outside.")
    message(STATUS "Trying to use local boost directory ${CMAKE_CURRENT_SOURCE_DIR}/boost")
    set(BOOST_ROOT "boost")
else()
    message(STATUS "Using defined Boost Root at ${BOOST_ROOT}")
endif()
list(POP_BACK CMAKE_MESSAGE_INDENT)


find_package(Boost 1.79 COMPONENTS filesystem REQUIRED)
message(STATUS "Found valid Boost Sources")
set(LIB_DOCKER _docker_library)
message(STATUS "Creating static Docker Library")
add_library(${LIB_DOCKER} STATIC ${DOCKER_SOURCES})
# DECLARE HEADER LIBRARY HEADER
list(APPEND CMAKE_MESSAGE_INDENT "-- ")
message(STATUS "Including Header ...")
target_include_directories(${LIB_DOCKER}    PUBLIC include/public
                                            PRIVATE include/private
                                            PRIVATE ${Boost_INCLUDE_DIRS})
message(STATUS "Including Boost Sources ...")
target_link_libraries(${LIB_DOCKER}         PRIVATE ${BOOST_LIBRARIES})
list(POP_BACK CMAKE_MESSAGE_INDENT)  


# ---


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if(BUILD_TESTING)
    message(STATUS "Creating Tests ...")
    list(APPEND CMAKE_MESSAGE_INDENT "-- ")
    add_subdirectory(test)
    list(POP_BACK CMAKE_MESSAGE_INDENT) 
endif()
