cmake_minimum_required(VERSION 3.4.0)

project(docker-library-tests CXX)


# ---


include(CTest)
# CREATE TEST EXECUTABLE
set(DOCKER_TEST docker_test)
add_executable(${DOCKER_TEST} test_docker.cpp)
# ADD DEPENDENT LIBRARY
target_link_libraries(${DOCKER_TEST} PRIVATE ${LIB_DOCKER})
add_test(NAME DockerLibraryTest COMMAND ${DOCKER_TEST})
