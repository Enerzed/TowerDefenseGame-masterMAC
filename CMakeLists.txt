CMAKE_MINIMUM_REQUIRED(VERSION 3.13.4)
PROJECT(main.out)

SET(CMAKE_CXX_STANDART 17)

INCLUDE_DIRECTORIES(project/include)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(tinyxml2 REQUIRED)
include_directories(Texture sounds images tinyxml2 TinyXML)
add_executable(${PROJECT_NAME} main.cpp)
#target_include_directories(${PROJECT_NAME} PUBLIC tinyxml2)
target_link_libraries(main.out sfml-graphics sfml-audio)