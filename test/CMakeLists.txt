cmake_minimum_required(VERSION 3.4.0)

project(docker-library-tests CXX)


# ---


# CREATE TEST EXECUTABLE
set(DOCKER_TEST docker_test)
message(STATUS "Creating Test Executable")
add_executable(${DOCKER_TEST} test_docker.cpp)
# ADD DEPENDENT LIBRARY
message(STATUS "Including Docker Library ...")
target_link_libraries(${DOCKER_TEST} PRIVATE ${LIB_DOCKER})
message(STATUS "Declaring Test ...")
add_test(NAME DockerLibraryTest COMMAND ${DOCKER_TEST})
