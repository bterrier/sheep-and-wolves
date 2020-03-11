cmake_minimum_required(VERSION 3.5)

project(sheep-and-wolves LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}" ) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}" )



find_package(FLTK REQUIRED)

add_executable(sheep-and-wolves WIN32
  main.cpp
  main.h
  unite1.cpp
  unite1.h
  unite2.cpp
  unite2.h
  unite3.cpp
  unite3.h
  unite4.cpp
  unite4.h
)

target_include_directories(sheep-and-wolves PUBLIC ${FLTK_INCLUDE_DIR})

set(IMAGE_TARGET_DIR ${EXECUTABLE_OUTPUT_PATH})

configure_file(mouton.gif ${IMAGE_TARGET_DIR}/mouton.gif COPYONLY)
configure_file(loup.gif ${IMAGE_TARGET_DIR}/loup.gif COPYONLY)
configure_file(debut.gif ${IMAGE_TARGET_DIR}/debut.gif COPYONLY)


target_link_libraries(sheep-and-wolves ${FLTK_LIBRARIES})

if(${VCPKG_TARGET_TRIPLET} MATCHES "static")
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

if(MSVC)
  target_compile_options(sheep-and-wolves PRIVATE /W4 /WX)
else()
  target_compile_options(sheep-and-wolves PRIVATE -Wall -Wextra -pedantic)
endif()
