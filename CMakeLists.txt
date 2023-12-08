cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDART 17)

project(best_tcp)


add_executable(best_tcp_client src/client.cpp)
add_executable(best_tcp_server src/server.cpp)
add_executable(best_tcp src/main.cpp)

#ADD boost
set(BOOST_ROOT "../../libs/boost_1_83_0")
find_package(Boost)

IF (Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
    link_libraries(${Boost_LIBRARIES})
ENDIF()

#ADD modbus
include_directories(../../libs/libmodbus-3.1.10/src)
link_libraries("${CMAKE_CURRENT_SOURCE_DIR}/../../libs/libmodbus-3.1.10/src/.libs/libmodbus.so") 

