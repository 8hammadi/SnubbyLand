cmake_minimum_required(VERSION 3.7)

project(SnubbyLand)


file(GLOB SOURCES CONFIGURE_DEPENDS
src/main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
)


target_link_libraries(${PROJECT_NAME}
-SDL2_image 
-lSDL2_ttf 
-pthread
-lboost_serialization
)