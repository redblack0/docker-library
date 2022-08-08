cmake_minimum_required(VERSION 3.17.0)

project(docker-library CXX)


# ---


message(STATUS "Check for Boost Library ...")
find_package(Boost 1.79 COMPONENTS filesystem REQUIRED QUIET)
list(APPEND CMAKE_MESSAGE_INDENT "-- ")
    message(STATUS "Using defined Boost Header at ${Boost_INCLUDE_DIRS}")
    message(STATUS "Using defined Boost Libraries at ${Boost_LIBRARY_DIRS}")
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(STATUS "Found valid Boost Sources")


# ---


if(NOT DEFINED LIB_DOCKER)
    set(LIB_DOCKER ${PROJECT_NAME})
endif()

set(DOCKER_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/docker.cpp"
        ## dependency layer
    "${CMAKE_CURRENT_SOURCE_DIR}/src/network.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/container.cpp"
        ## dependency layer
    "${CMAKE_CURRENT_SOURCE_DIR}/src/factory.cpp")

message(STATUS "Creating static Docker Library")
add_library(${LIB_DOCKER} SHARED ${DOCKER_SOURCES})
list(APPEND CMAKE_MESSAGE_INDENT "-- ")
    message(STATUS "Including Header ...")
    target_include_directories(${LIB_DOCKER}    PUBLIC include
                                                PRIVATE src
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
