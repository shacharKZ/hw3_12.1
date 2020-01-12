cmake_minimum_required(VERSION 3.15)
project(ex3_6_1)

set(CMAKE_CXX_STANDARD 14)
set(g++ -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG)

link_directories(.)

add_executable(ParkingMain_metargelim MtmParkingLot.cpp UniqueArrayImp.h UniqueArray.h Time.h Time.cpp ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.cpp ParkingSpot.h Vehicle.cpp Vehicle.h ParkingLot.cpp)
add_executable(ex3_6_1 main.cpp UniqueArrayImp.h UniqueArray.h)
add_executable(uaTestFromMETARGELIM tests/UniqueArrayTest.cpp UniqueArrayImp.h UniqueArray.h)
add_executable(ex3_part_gimel MtmParkingLot.cpp UniqueArrayImp.h UniqueArray.h Time.h ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.cpp ParkingSpot.h Vehicle.cpp Vehicle.h)
add_executable(first_test_parking main.cpp UniqueArrayImp.h UniqueArray.h Time.h Time.cpp ParkingLot.h ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.cpp ParkingSpot.h Vehicle.cpp Vehicle.h ParkingLot.cpp)