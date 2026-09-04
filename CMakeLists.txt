cmake_minimum_required(VERSION 3.10)
project(Send VERSION 0.1 LANGUAGES CXX)

add_library(WebHook ${CMAKE_CURRENT_SOURCE_DIR}/src/send.cpp)
target_include_directories(WebHook PUBLIC include)

add_library(WebHook::WebHook ALIAS WebHook)
