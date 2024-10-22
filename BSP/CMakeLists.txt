cmake_minimum_required(VERSION 3.25)

project(bsp)

add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE source CONFIGURE_DEPENDS src/*.cpp include/*.h)
target_sources(${PROJECT_NAME} PRIVATE ${source})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        stm32cubemx

        # Add user defined libraries
)