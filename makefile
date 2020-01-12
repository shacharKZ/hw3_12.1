CC = g++
DEBUG_FLAGS = -g -DNDEBUG
CC_FLAGS = -std=c++11 -Wall -Werror -pedantic-errors
OBJS_UA = UniqueArrayTest.o
OBJS_VEHICLE = Vehicle.o Time.o
OBJS_PL = ParkigLot.o MtmParkingLot.o Time.o ParkingSpot.o\
 ParkingLotPrinter.o Vehicle.o
EXE = MtmParkingLot
LIBS = -L. -lm -lmtm

# builds all the project exe
$(EXE): $(OBJS_UA) $(OBJS_PL)
	$(CC) $(DEBUG_FLAGS) $(CC_FLAGS) $(OBJS_PL) -o $@ $(LIBS)

# build UniqueArray (ADT for first part of this assignment)
UniqueArray: $(OBJS_UA)
	$(CC) $(DEBUG_FLAGS) $(CC_FLAGS) $(OBJS_UA) -o $@

# build Vehicle (ADT for MtmParking lot)
Vehicle: $(OBJS_VEHICLE)
	$(CC) $(DEBUG_FLAGS) $(CC_FLAGS) $(OBJS_VEHICLE) -o $@

# build UniqueArray_test
UniqueArrayTest.o: tests/UniqueArrayTest.cpp UniqueArray.h UniqueArrayImp.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) tests/$*.cpp

MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h \
 ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h \
 UniqueArrayImp.h Vehicle.h
	$(CC) -c $(DEBUG_FLAGS) $(CC_FLAGS) $*.cpp

# build all the files for ParkingLot
ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h \
 ParkingSpot.h UniqueArray.h UniqueArrayImp.h Vehicle.h \
 ParkingLotPrinter.h
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


# clean working directory
clean:
	rm -f $(OBJS_UA) $(OBJS_PL) $(EXE)


