cmake_minimum_required(VERSION 3.7)

project(SnubbyLand)

include_directories(includes)



file(GLOB SOURCES CONFIGURE_DEPENDS
src/Main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
)

target_link_libraries(${PROJECT_NAME}

-lSDL2
-lSDL2_image 
-lboost_serialization
-lSDL2_ttf 
)