cmake_minimum_required(VERSION 3.0.0)

project(dash-devnet-tool)


# ---


# SET BOOST PATHS
set(BOOST_ROOT "boost")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
find_package(Boost 1.79 COMPONENTS filesystem REQUIRED)


# ---


# SET DOCKER SOURCE FILES
set(DOCKER_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/docker/docker.cpp"
        ## dependency layer
    "${CMAKE_CURRENT_SOURCE_DIR}/docker/network.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/docker/container.cpp"
        ## dependency layer
    "${CMAKE_CURRENT_SOURCE_DIR}/docker/factory.cpp")
# CONFIGURE AS LIBRARY
set(LIB_DOCKER _docker_library)
add_library(${LIB_DOCKER} SHARED ${DOCKER_SOURCES})
target_include_directories(${LIB_DOCKER} PUBLIC docker/include/public)
target_include_directories(${LIB_DOCKER} PRIVATE docker/include/private)
target_include_directories(${LIB_DOCKER} PRIVATE ${BOOST_INCLUDE_DIRS})
target_link_directories(${LIB_DOCKER} PRIVATE ${BOOST_LIBRARY_DIRS})
# LINK TO FILESYSTEM
target_link_libraries(${LIB_DOCKER} PRIVATE ${Boost_LIBRARIES})
# AS TO CURRENT DEVELOPMENT POINT BOOST/PROCESS THROWS THIS
target_compile_options(${LIB_DOCKER} PRIVATE -Wno-narrowing -lboost_system -lboost_filesystem)


# ---


# SET DASH SOURCE FILES
set(DASH_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/dash/dash-container.cpp")
# CONFIGURE AS LIBRARY
set(LIB_DASH _dash_library)
#add_library(${LIB_DASH} SHARED ${DASH_SOURCES})
#target_include_directories(${LIB_DASH} PUBLIC dash/include/public)
#target_include_directories(${LIB_DASH} PRIVATE dash/include/private)
#target_link_libraries(${LIB_DASH} ${LIB_DOCKER})
# ---
#target_include_directories(${LIB_DASH} PRIVATE ${BOOST_INCLUDE_DIRS})
#target_link_directories(${LIB_DASH} PRIVATE ${BOOST_LIBRARY_DIRS})
# AS TO CURRENT DEVELOPMENT POINT BOOST/PROCESS THROWS THIS
#target_compile_options(${LIB_DASH} PRIVATE -Wno-narrowing)


# --- #


include(CTest)
# CREATE TEST EXECUTABLE
set(DOCKER_TEST docker_test)
add_executable(${DOCKER_TEST} test/test_docker.cpp)
# ADD DEPENDENT LIBRARY
target_link_libraries(${DOCKER_TEST} PRIVATE ${LIB_DOCKER})
# INCLUDE BOOST SOURCES AND HEADER
#target_include_directories(${DOCKER_TEST} PRIVATE ${BOOST_INCLUDE_DIRS})
#target_link_directories(${DOCKER_TEST} PRIVATE ${BOOST_LIBRARY_DIRS})
# AS TO CURRENT DEVELOPMENT POINT BOOST/PROCESS THROWS THIS
#target_compile_options(${DOCKER_TEST} PRIVATE -Wno-narrowing)
# ADD TEST TO CTEST ENVIROMENT
enable_testing()
add_test(NAME DockerLibraryTest COMMAND ${DOCKER_TEST})
