cmake_minimum_required(VERSION 3.6)
project(PropertiesManager)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(../Logger/include)

include_directories(googletest/googlemock/include)
include_directories(googletest/googletest/include)

add_library(PropertiesManager
        src/Property.cpp
        src/Properties.cpp)
