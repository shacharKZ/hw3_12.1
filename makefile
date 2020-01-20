CC = g++
PROJECT_DEBUG_FLAGS = -DNDEBUG
CC_FLAGS = -std=c++11 -Wall -Werror -pedantic-errors
OBJS_VEHICLE = Vehicle.o Time.o
OBJS_PL = ParkingLot.o MtmParkingLot.o Time.o ParkingSpot.o\
 ParkingLotPrinter.o Vehicle.o
EXE = MtmParkingLot

# builds all the project exe
$(EXE): $(OBJS_UA) $(OBJS_PL)
	$(CC) $(PROJECT_DEBUG_FLAGS) $(CC_FLAGS) $(OBJS_PL) -o $@

# build all the files for ParkingLot
ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h \
 ParkingSpot.h UniqueArray.h UniqueArrayImp.h Vehicle.h \
 ParkingLotPrinter.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h \
 ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h \
 UniqueArrayImp.h Vehicle.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

# build Vehicle ADT for the use of MtmParkingLot
Vehicle.o: Vehicle.cpp Vehicle.h ParkingLotTypes.h Time.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

# build ParkingLot_printer
ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h \
 ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

# build ParkingSpot ADT
ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

# build Time ADT
Time.o: Time.cpp Time.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

#build Vehicle (ADT for MtmParking lot)
#Vehicle: $(OBJS_VEHICLE)
#	$(CC) -c $(CC_FLAGS) $(OBJS_VEHICLE) -o $.o

# clean working directory
clean:
	rm -f $(OBJS_UA) $(OBJS_PL) $(EXE)



