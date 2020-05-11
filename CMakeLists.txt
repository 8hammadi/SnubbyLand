cmake_minimum_required(VERSION 3.7)

project(SnubbyLand)

include_directories(SDL2)

include_directories(SDL2/include)

file(GLOB SOURCES CONFIGURE_DEPENDS
src/main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
)


target_link_libraries(${PROJECT_NAME}
SDL2
SDL2_image 
-lSDL2_ttf 
-pthread
-lboost_serialization
)