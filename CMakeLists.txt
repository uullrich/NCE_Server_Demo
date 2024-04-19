cmake_minimum_required(VERSION 3.26)
project(clion_playground)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS  OFF)
set(Boost_USE_RELEASE_LIBS ON)

find_package(Boost)

if(Boost_FOUND)
    message("Boost found!")
    message(${Boost_INCLUDE_DIRS} )
    include_directories( ${Boost_INCLUDE_DIRS} )
    link_directories(${Boost_LIBRARY_DIRS})
endif()

add_subdirectory(libs/NetCommandExecutor)
include_directories(libs/NetCommandExecutor/include)

set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" )

message( "SourceDir: ${PROJECT_SOURCE_DIR}" )
set(SRC_FILES ${PROJECT_SOURCE_DIR}/main.cpp)

add_executable(clion_playground ${SRC_FILES})
target_link_libraries(clion_playground ${Boost_LIBRARIES} NetCommandExecutor)