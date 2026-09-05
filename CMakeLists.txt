cmake_minimum_required(VERSION 3.10)
project(Discord VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_executable(Send src/main.cpp src/send.cpp)
target_include_directories(Send PUBLIC include)
target_link_libraries(Send PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libWebHook.a)
target_link_libraries(Send PRIVATE curl)
