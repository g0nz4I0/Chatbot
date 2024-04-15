cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME Chatbot)
project(${PROJECT_NAME})
set(SOURCES_CPP 
    src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES_CPP})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")