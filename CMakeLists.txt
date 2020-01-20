cmake_minimum_required(VERSION 3.15)
project(ex3_6_1)

#set(CMAKE_CXX_STANDARD 14)
#set(g++ -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror -pedantic-errors")
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

link_directories(.)

add_executable(ParkingMain_metargelim MtmParkingLot.cpp UniqueArrayImp.h UniqueArray.h Time.h Time.cpp ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.cpp ParkingSpot.h Vehicle.cpp Vehicle.h ParkingLot.cpp)
add_executable(ex3_6_1 main.cpp UniqueArrayImp.h UniqueArray.h)
add_executable(uaTestFromMETARGELIM tests/UniqueArrayTest.cpp UniqueArrayImp.h UniqueArray.h)
add_executable(ex3_part_gimel MtmParkingLot.cpp UniqueArrayImp.h UniqueArray.h Time.h ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.cpp ParkingSpot.h Vehicle.cpp Vehicle.h)
add_executable(first_test_parking main.cpp UniqueArrayImp.h UniqueArray.h Time.h Time.cpp ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.cpp ParkingSpot.h Vehicle.cpp Vehicle.h ParkingLot.cpp)
add_executable(FBtest1 testFB1.cpp UniqueArrayImp.h UniqueArray.h Time.h ParkingLot.h ParkingLotTypes.h ParkingLotPrinter.h ParkingSpot.h Vehicle.h)

