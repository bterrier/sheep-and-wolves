cmake_minimum_required(VERSION 3.5)

project(loups-et-moutons LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLTK REQUIRED)

add_executable(loups-et-moutons WIN32
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

target_include_directories(loups-et-moutons PUBLIC ${FLTK_INCLUDE_DIR})

configure_file(mouton.gif mouton.gif COPYONLY)
configure_file(loup.gif loup.gif COPYONLY)
configure_file(debut.gif debut.gif COPYONLY)


target_link_libraries(loups-et-moutons ${FLTK_LIBRARIES})
