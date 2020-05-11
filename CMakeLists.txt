cmake_minimum_required(VERSION 3.7)

project(SnubbyLand)

include_directories(/usr/include/SDL2)

file(GLOB SOURCES CONFIGURE_DEPENDS
src/main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
)


target_link_libraries(${PROJECT_NAME}
-lSDL2
-lSDL2_image 
-lSDL2_ttf 
-pthread
-lboost_serialization
)