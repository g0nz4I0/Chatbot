cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME Chatbot)
project(${PROJECT_NAME})
set(SOURCES_CPP 
    src/Models/EthernetNode.cpp
    src/Models/ServerSocket.cpp)
set(INCLUDES_HPP
    inc/)
add_executable(${PROJECT_NAME} ${SOURCES_CPP} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES_HPP})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wno-attributes -g3 -O0)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES_CPP})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${INCLUDES_HPP})
target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Werror -Wno-attributes -g3 -O0)
set_property(TARGET ${PROJECT_NAME}_lib PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME}_lib PROPERTY CXX_STANDARD 23)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)
# gtest 1.14 commit f8d7d77c06936315286eb55f8de22cd23c188571

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
set(UNIT_TEST ChatbotTests)
add_executable(${UNIT_TEST} 
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)
target_compile_options(${UNIT_TEST} PRIVATE -Wall -Werror -Wno-attributes)
set_property(TARGET ${UNIT_TEST} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${UNIT_TEST} PROPERTY CXX_STANDARD 23)
target_link_libraries(
    ${UNIT_TEST}
    ${PROJECT_NAME}_lib
  GTest::gtest_main
)
target_include_directories(${UNIT_TEST} PUBLIC ${INCLUDES_HPP})
include(GoogleTest)
gtest_discover_tests(${UNIT_TEST})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set_target_properties(${UNIT_TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")