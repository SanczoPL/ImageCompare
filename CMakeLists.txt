cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(ImageCompare
  VERSION 0.0.1
  DESCRIPTION "ImageCompare"
  LANGUAGES C CXX)

set(DEFAULT_BUILD_TYPE "Release")

#STNDARD STUFF
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")


set(TARGET_NAME "ImageCompare")
include_directories("${PROJECT_SOURCE_DIR}/../IncludeSpdlog/include")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(OpenCV REQUIRED)
#include fix for OpenCV
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)


set(SRC
    src/main.cc
    ../../IncludeSpdlog/spdlog.cc
    ../../IncludeSpdlog/spdlog.h
    src/comparemethod/basecompare.h
    src/comparemethod/basecompare.cc
    src/comparemethod/codestats_2014.cc
    src/comparemethod/codestats_2014.h
    src/comparemethod/none.cc
    src/comparemethod/none.h
    src/imagecompare.cc
    src/compare.h

)

set(HEADERS
    src/imagecompare.h
)

add_executable(${TARGET_NAME}
    ${SRC}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME} Qt5::Core ${OpenCV_LIBS} Threads::Threads )
