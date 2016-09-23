cmake_minimum_required(VERSION 3.5)
project(BioSimCppQT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    biosim.cpp
    biosim.hpp
    creature.cpp
    creature.hpp
    exceptions.hpp
    gamemodel.cpp
    gamemodel.hpp
    imagetga.cpp
    imagetga.hpp
    landscape.cpp
    landscape.hpp
    main.cpp
    textfilereader.cpp
    textfilereader.hpp
    util.hpp)

add_executable(BioSimCppQT ${SOURCE_FILES})