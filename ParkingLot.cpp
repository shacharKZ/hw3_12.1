#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"
#include <algorithm>
#include <vector>

using ParkingLotUtils::ParkingResult;
using ParkingLotUtils::ParkingSpot;
using ParkingLotUtils::ParkingLotPrinter;
using MtmParkingLot::parkingSection;
using std::vector;
using MtmParkingLot::Price;


namespace MtmParkingLot {
    Price PARKING_TICKET = 250;
    const unsigned int MAX_HOURS_MINUS_ONE = 5;
    Price BIKE_FIRST_HOUR = 10;
    Price BIKE_OTHER_HOURS = 5;
    Price HANDI_FIXED_PRICE = 15;
    Price CAR_FIRST_HOUR = 20;
    Price CAR_OTHER_HOUR = 10;
    const unsigned int HOURS_PER_DAY = 24;


    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            bike(parkingBlockSizes[0]), handi(parkingBlockSizes[1]),
            car(parkingBlockSizes[2]) {}


    ParkingResult ParkingLot::enterParkingAUX(Vehicle &current,
            parkingSection &park, unsigned int &index, VehicleType section) {
        try {
            index = park.insert(current);
            park.ptrForIndex(index)->setParkingSpot(index, section);
            current = *park[current];
            return SUCCESS;
        } catch (parkingSection::UniqueArrayIsFullException &e) {
            return NO_EMPTY_SPOT;
        }
        return ParkingResult::VEHICLE_NOT_FOUND; // def. will not be used
    }


    ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
        Vehicle current (vehicleType, licensePlate, entranceTime);
        unsigned int index = 0; // car parking num
        if (getVehicle(current,index)) {
            ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate,
                    current.getEntranceTime());
            ParkingLotPrinter::printEntryFailureAlreadyParked(cout,
                    current.getParkingSpot());
            return VEHICLE_ALREADY_PARKED;
        }
        ParkingResult printTemp = ParkingResult::VEHICLE_NOT_FOUND; // def
        if (vehicleType == MOTORBIKE) {
            printTemp = enterParkingAUX(current, bike, index, MOTORBIKE);
        } else if (vehicleType == CAR) {
            printTemp = enterParkingAUX(current, car, index, CAR);
        } else { // HANDICAPPED
            printTemp = enterParkingAUX(current, handi, index, HANDICAPPED);
            if (printTemp == NO_EMPTY_SPOT) {
                printTemp = enterParkingAUX(current, car, index, CAR);
            }
        }
        ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate,
                entranceTime);
        if (printTemp == SUCCESS) { // printing message and return according to enterParkingAUX result
            ParkingLotPrinter::printEntrySuccess(cout,
                    current.getParkingSpot());
            return SUCCESS;
        }
        ParkingLotPrinter::printEntryFailureNoSpot(cout);
        return NO_EMPTY_SPOT; // def return and only possible option
    }


    bool ParkingLot::getVehicleAUX(Vehicle& current, unsigned int &index,
                                   const parkingSection &park) const {
        if (park.getIndex(current, index)) {
            current = *park[current];
            return true;
        }
        return false;
    }

    bool ParkingLot::getVehicle(Vehicle& current, unsigned int& index) const {
        return getVehicleAUX(current, index, bike) ||
               getVehicleAUX(current, index, handi) ||
               getVehicleAUX(current, index, car);
    }


    bool ParkingLot::overStay(Time initial, Time final) {
        Time::Hour hoursPerDay = HOURS_PER_DAY;
        Time delta = (final - initial);
        return (delta.toHours() > hoursPerDay);
    }


    void ParkingLot::giveTicketIfNeeded (const parkingSection &x,
            Time inspectionTime, unsigned int &counter) {
        for (unsigned int i = 0; i < x.getSize(); ++i) {
            Vehicle *current = (x.ptrForIndex(i));

            if (current != nullptr && current->didHeGotATicket() == false
                && overStay(current->getEntranceTime(), inspectionTime)) {
                current->giveATicket();
                counter++;
            }
        }
    }


    void ParkingLot::inspectParkingLot(Time inspectionTime) {
        unsigned int counter = 0;
        giveTicketIfNeeded(bike, inspectionTime, counter);
        giveTicketIfNeeded(handi, inspectionTime, counter);
        giveTicketIfNeeded(car, inspectionTime, counter);
        ParkingLotPrinter::printInspectionResult(cout, inspectionTime, counter);
    }


    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const {
        Vehicle temp (CAR, licensePlate, Time());
        unsigned int index = 0;

        if (getVehicle(temp, index) == true) {
            parkingSpot = ParkingSpot(temp.getParkingSpot());
            return SUCCESS;
        }
        return VEHICLE_NOT_FOUND;
    }


     void ParkingLot::addParkToVector(const parkingSection& park, std::vector<Vehicle>& vec, VehicleType sector) {
        for (unsigned int i = 0; i < park.getSize(); ++i) {
            Vehicle *current = park.ptrForIndex(i);
            if (current != nullptr) {
                current->setParkingSpot(i, sector); // double check every vehicle holds its real parkingSpotS
                vec.push_back(*current);
            }
        }
    }


    ostream &operator<<(ostream &os, const ParkingLot &parkingLot) {

        vector<Vehicle> allVehicle;

        ParkingLot::addParkToVector(parkingLot.bike,allVehicle, MOTORBIKE);
        ParkingLot::addParkToVector(parkingLot.handi,allVehicle, HANDICAPPED);
        ParkingLot::addParkToVector(parkingLot.car,allVehicle, CAR);

        sort(allVehicle.begin(), allVehicle.end());

        ParkingLotPrinter::printParkingLotTitle(os);
        for (unsigned int i = 0; i < allVehicle.size(); ++i) {
            os << allVehicle[i];
        }
        return os;
    }


    unsigned int ParkingLot::min(unsigned int a, unsigned int b) {
        if (a < b) {
            return a;
        }
        return b;
    }


    unsigned int ParkingLot::handiBillCalculator (Time entrance, Time exit){
        Time delta = exit - entrance;
        if (delta.toHours() == 0) {
            return 0;
        }
        else {
            return HANDI_FIXED_PRICE;
        }
    }


    unsigned int ParkingLot::normalBillCalculator (Time entrance, Time exit,
            Price first_hour_rate, Price normal_hour_rate) {
        unsigned sum = 0;
        Time delta = exit - entrance;
        if (delta.toHours() == 0) {
            return sum;
        }
        if (delta.toHours() == 1) {
            return first_hour_rate;
        }
        sum += first_hour_rate;
        unsigned int hours_to_pay_for =
                ParkingLot::min(MAX_HOURS_MINUS_ONE, (delta.toHours() - 1));
        for (unsigned int i = 0; i < hours_to_pay_for; ++i) {
            sum += normal_hour_rate;
        }
        return sum;
    }


    void ParkingLot::payDay (unsigned int& the_bill , Time exitTime,
                             VehicleType vehicleType, VehicleType lot,
                             unsigned int parking_num, Time &X_entrance_time){
        if (vehicleType == MOTORBIKE) {
            X_entrance_time = bike.ptrForIndex(parking_num)->getEntranceTime();
            if (bike.ptrForIndex(parking_num)->didHeGotATicket()) {
                the_bill += PARKING_TICKET;
            }
            the_bill += normalBillCalculator
                    (X_entrance_time, exitTime, BIKE_FIRST_HOUR, BIKE_OTHER_HOURS);
        } else if (vehicleType == HANDICAPPED) {
            Vehicle *temp;
            if (lot == CAR){
                temp = car.ptrForIndex(parking_num);
            } else{
                temp = handi.ptrForIndex(parking_num);
            }
            X_entrance_time = temp->getEntranceTime();
            if (temp->didHeGotATicket()) {
                the_bill += PARKING_TICKET;
            }
            the_bill += handiBillCalculator(X_entrance_time, exitTime);
        } else if (vehicleType == CAR) {
            X_entrance_time = car.ptrForIndex(parking_num)->getEntranceTime();
            if (car.ptrForIndex(parking_num)->didHeGotATicket()) {
                the_bill += PARKING_TICKET;
            }
            the_bill += normalBillCalculator
                    (X_entrance_time, exitTime, CAR_FIRST_HOUR, CAR_OTHER_HOUR);
        }
    }


    void ParkingLot::removeVehicle (LicensePlate licensePlate){
        Vehicle current (CAR, licensePlate, Time());
        if (bike.remove(current) || handi.remove(current)
        || car.remove(current) ) {
            return;
        }
    }


    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime) {
        ParkingSpot exiting_vehicle_spot;
        if (getParkingSpot(licensePlate, exiting_vehicle_spot)
            == VEHICLE_NOT_FOUND) {
            ParkingLotPrinter::printExitFailure(cout, licensePlate);
            return VEHICLE_NOT_FOUND;
        }
        Time exiting_vehicle_entrance_time;
        Vehicle temp_vehicle =
                Vehicle(MOTORBIKE, licensePlate, exitTime);
        VehicleType vehicleType =
                CAR, block = exiting_vehicle_spot.getParkingBlock();
        if (block == CAR){
            vehicleType = car[temp_vehicle]->getVehicleType();
        } else{
            vehicleType = block;
        }
        unsigned int bill=0;
        payDay(bill, exitTime, vehicleType, block,
               exiting_vehicle_spot.getParkingNumber(),
               exiting_vehicle_entrance_time);
        ParkingLotPrinter::printVehicle(cout,
                vehicleType, licensePlate, exiting_vehicle_entrance_time);
        ParkingLotPrinter::printExitSuccess(cout,
                exiting_vehicle_spot, exitTime, bill);
        ParkingLot::removeVehicle(licensePlate);
        return SUCCESS;
    }

}
