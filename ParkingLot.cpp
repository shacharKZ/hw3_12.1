//
// Created by eilon on 09/01/2020.
//

#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotTypes.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"
#include <algorithm>
#include <vector>


using ParkingLotUtils::ParkingResult;
using ParkingLotUtils::ParkingSpot;
using ParkingLotUtils::ParkingLotPrinter;
using MtmParkingLot::partial_parking_lot;
using std::vector;

namespace MtmParkingLot {
    const unsigned int PARKING_TICKET = 250;
    const unsigned int MAX_HOURS_TO_PAY_FOR_AFTER_DEDUCTION_OF_FIRST = 5;
    const unsigned int BIKE_FIRST_HOUR = 10;
    const unsigned int BIKE_OTHER_HOURS = 5;
    const unsigned int HANDI_FIXED_PRICE = 15;
    const unsigned int CAR_FIRST_HOUR = 20;
    const unsigned int CAR_OTHER_HOUR = 10;
    const unsigned int MINUTES_PER_HOUR = 60;





//typedef UniqueArray<Vehicle, Vehicle::areVehicleTheSame> partial_parking_lot; // i found the right way to do that ^^^ 666

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            bike(parkingBlockSizes[0]), handi(parkingBlockSizes[1]),
            car(parkingBlockSizes[2]) {}


    ParkingResult
    ParkingLot::enterParkingAUX(const Vehicle &current, partial_parking_lot &park, unsigned int &index, Time& timeIfAlreadyPark, VehicleType section) {
        if (park.getIndex(current, index) == true) {
            timeIfAlreadyPark = park.get_ptr_to_elem_for_index(index)->getEntranceTime();
            return ParkingResult::VEHICLE_ALREADY_PARKED;
        } else {
            try {
                index = park.insert(current);
                park.get_ptr_to_elem_for_index(index)->setParkingSpot(index, section);
                return ParkingResult::SUCCESS;
            } catch (partial_parking_lot::UniqueArrayIsFullException &e) {
                return ParkingResult::NO_EMPTY_SPOT;
            }
        }
        return ParkingResult::VEHICLE_NOT_FOUND; // def. will not be used
    }


    ParkingResult
    ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
        Vehicle current = Vehicle(vehicleType, licensePlate, entranceTime);
        unsigned int index = 0; // car parking num
        VehicleType psType = vehicleType; // used to indicate where HANDICAPPED
        // parked (two options) or else the print func might be wrong
        ParkingResult printTemp = ParkingResult::VEHICLE_NOT_FOUND; // def

        Time timeIfAlreadyPark = entranceTime;

        if (vehicleType == VehicleType::MOTORBIKE) {
            printTemp = enterParkingAUX(current, bike, index, timeIfAlreadyPark, MOTORBIKE);
        } else if (vehicleType == VehicleType::CAR) {
            printTemp = enterParkingAUX(current, car, index, timeIfAlreadyPark, CAR);
        } else { // HANDICAPPED
            // need to be check or else we could park in HANDICAPPED even we already parked in CAR
            if (car.getIndex(current, index)) {
                psType = VehicleType::CAR;
                printTemp = ParkingResult::VEHICLE_ALREADY_PARKED;
            } else {
                printTemp = enterParkingAUX(current, handi, index, timeIfAlreadyPark, HANDICAPPED);
                if (printTemp == ParkingResult::NO_EMPTY_SPOT) { // try Car instead
                    printTemp = enterParkingAUX(current, car, index,timeIfAlreadyPark, CAR);
                    psType = VehicleType::CAR;
                }
            }
        }

        // printing message and return arg according to enterParkingAUX result
        ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate, timeIfAlreadyPark);
        if (printTemp == ParkingResult::SUCCESS) {
            ParkingSpot sp(psType, index);
            ParkingLotPrinter::printEntrySuccess(cout, sp);
            return ParkingResult::SUCCESS;
        } else if (printTemp == ParkingResult::VEHICLE_ALREADY_PARKED) {
            ParkingSpot sp(psType, index);
            ParkingLotPrinter::printEntryFailureAlreadyParked(cout, sp);
            return ParkingResult::VEHICLE_ALREADY_PARKED;
        } else { // only possible: ParkingResult::NO_EMPTY_SPOT
            ParkingLotPrinter::printEntryFailureNoSpot(cout);
        }
        return ParkingResult::NO_EMPTY_SPOT; // def return and only possible option
    }


    bool Over_Stay(Time initial, Time final) {
        using ParkingLotUtils::Time;
        static const Time::Hour HOURS_PER_DAY = 24;
        Time delta = (final - initial);
        return (delta.toHours() > HOURS_PER_DAY);
    }

    void Give_the_ticket_to_those_who_deserve_it
            (const partial_parking_lot &x, Time inspectionTime, unsigned int &counter) {

        for (unsigned int i = 0; i < x.getSize(); ++i) {
            Vehicle *current = const_cast<Vehicle *>(x.get_ptr_to_elem_for_index(i));

            if (current != nullptr && current->did_he_get_a_ticket() == false &&
                Over_Stay(current->getEntranceTime(), inspectionTime)) {
                current->get_a_ticket();
                counter++;
            }
        }
    }

    void ParkingLot::inspectParkingLot(Time inspectionTime) {

        unsigned int counter = 0;
        Give_the_ticket_to_those_who_deserve_it(bike, inspectionTime, counter);
        Give_the_ticket_to_those_who_deserve_it(handi, inspectionTime, counter);
        Give_the_ticket_to_those_who_deserve_it(car, inspectionTime, counter);
        ParkingLotPrinter::printInspectionResult(cout, inspectionTime, counter);
    }

    bool ParkingLot::getParkingSpotAUX(Vehicle current,
                                       unsigned int &index, const partial_parking_lot &park) const {
        return park.getIndex(current, index);
    }


    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const {
        Vehicle tempSerch = Vehicle(VehicleType::CAR, licensePlate, Time());
        unsigned int index = 0;
        VehicleType psType = VehicleType::MOTORBIKE;
        ParkingResult flag = ParkingResult::VEHICLE_NOT_FOUND;
        if (getParkingSpotAUX(tempSerch, index, bike)) {
            flag = ParkingResult::SUCCESS;
        } else if (getParkingSpotAUX(tempSerch, index, handi)) {
            psType = VehicleType::HANDICAPPED;
            flag = ParkingResult::SUCCESS;
        } else if (getParkingSpotAUX(tempSerch, index, car)) {
            psType = VehicleType::CAR;
            flag = ParkingResult::SUCCESS;
        }

        if (flag == ParkingResult::SUCCESS) {
            parkingSpot = ParkingSpot(psType, index);
        }
        return flag;
    }


    void addParkToVector(const partial_parking_lot& park, std::vector<Vehicle>& vec, VehicleType sector) {
        for (unsigned int i = 0; i < park.getSize(); ++i) {
            Vehicle *current = park.get_ptr_to_elem_for_index(i);
            if (current != nullptr) {
                current->setParkingSpot(i, sector);
                vec.push_back(*current);
            }
        }
    }


    ostream &operator<<(ostream &os, const ParkingLot &parkingLot) {

        vector<Vehicle> allVehicle;

        addParkToVector(parkingLot.bike,allVehicle, MOTORBIKE);
        addParkToVector(parkingLot.handi,allVehicle, HANDICAPPED);
        addParkToVector(parkingLot.car,allVehicle, CAR);

        sort(allVehicle.begin(), allVehicle.end()); // TODO

        ParkingLotPrinter::printParkingLotTitle(os);
        for (unsigned  int i = 0; i < allVehicle.size(); ++i) {
            os << allVehicle[i];
        }

        return os;
    }

    static unsigned int min(unsigned int a, unsigned int b) {
        if (a < b) {
            return a;
        }
        return b;
    }

    static unsigned int bill_calculator(Time entrance, Time exit, VehicleType vehicleType) {

        unsigned sum = 0;
        ParkingLotUtils::Time delta = exit - entrance;

        if (delta.toHours() == 0) {
            return sum;
        }
        if (vehicleType == VehicleType::MOTORBIKE) {
            if (delta.toHours() == 1) {
                return BIKE_FIRST_HOUR;
            }
            sum += BIKE_FIRST_HOUR;
            unsigned int hours_to_pay_for = min(MAX_HOURS_TO_PAY_FOR_AFTER_DEDUCTION_OF_FIRST, (delta.toHours() - 1));
            for (unsigned int i = 0; i < hours_to_pay_for; ++i) {
                sum += BIKE_OTHER_HOURS;
            }
        }
        if (vehicleType == VehicleType::HANDICAPPED) {
            sum = HANDI_FIXED_PRICE;
        }
        if (vehicleType == VehicleType::CAR) {
            if (delta.toHours() == 1) {
                return CAR_FIRST_HOUR;
            }
            sum += CAR_FIRST_HOUR;
            unsigned int hours_to_pay_for = min(MAX_HOURS_TO_PAY_FOR_AFTER_DEDUCTION_OF_FIRST, (delta.toHours() - 1));
            for (unsigned int i = 0; i < hours_to_pay_for; ++i) {
                sum += CAR_OTHER_HOUR;
            }
        }
        return sum;
    }


    unsigned int ParkingLot::pay_day(Time exitTime, VehicleType vehicleType, VehicleType lot,
                                     unsigned int parking_num, Time &exiting_car_entrance_time) {
        unsigned int the_bill = 0;
        if (vehicleType == MOTORBIKE) {
            exiting_car_entrance_time = bike.get_ptr_to_elem_for_index(parking_num)->getEntranceTime();
            if (bike.get_ptr_to_elem_for_index(parking_num)->did_he_get_a_ticket()) {
                the_bill += PARKING_TICKET;
            }
        } else if (vehicleType == HANDICAPPED) {
            Vehicle *temp;
            if (lot == CAR){
                temp = car.get_ptr_to_elem_for_index(parking_num);
            } else{
                temp = handi.get_ptr_to_elem_for_index(parking_num);
            }
            exiting_car_entrance_time = temp->getEntranceTime();
            if (temp->did_he_get_a_ticket()) {
                the_bill += PARKING_TICKET;
            }

        } else if (vehicleType == CAR) {
            exiting_car_entrance_time = car.get_ptr_to_elem_for_index(parking_num)->getEntranceTime();
            if (car.get_ptr_to_elem_for_index(parking_num)->did_he_get_a_ticket()) {
                the_bill += PARKING_TICKET;
            }
        }
        the_bill += bill_calculator(exiting_car_entrance_time, exitTime, vehicleType);
        return the_bill;
    }

    void ParkingLot::remove_vehicle(VehicleType vehicleType, unsigned int parking_num) {

        if (vehicleType == MOTORBIKE) {
            bike.remove(*(bike.get_ptr_to_elem_for_index(parking_num)));
        }
        if (vehicleType == HANDICAPPED) {
            handi.remove(*(handi.get_ptr_to_elem_for_index(parking_num)));
        }
        if (vehicleType == CAR) {
            car.remove(*(car.get_ptr_to_elem_for_index(parking_num)));
        }
    }


    ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime) {
        using ParkingLotUtils::ParkingSpot;
        ParkingSpot exiting_vehicle_spot;

        if (getParkingSpot(licensePlate, exiting_vehicle_spot) == ParkingResult::VEHICLE_NOT_FOUND) {
            ParkingLotUtils::ParkingLotPrinter::printExitFailure(cout, licensePlate);
            return ParkingResult::VEHICLE_NOT_FOUND;
        }
        Time exiting_vehicle_entrance_time;
        Vehicle temp_vehicle = Vehicle(MOTORBIKE, licensePlate, exitTime);
        VehicleType vehicleType = CAR, block = exiting_vehicle_spot.getParkingBlock();
        if (block == CAR){
            vehicleType = car[temp_vehicle]->getVehicleType();
        } else if (block == MOTORBIKE){
            vehicleType = MOTORBIKE;
        } else if (block == HANDICAPPED){
            vehicleType = HANDICAPPED;
        }
        unsigned int bill = pay_day(exitTime, vehicleType, block,
                                    exiting_vehicle_spot.getParkingNumber(),
                                    exiting_vehicle_entrance_time);
        ParkingLotUtils::ParkingLotPrinter::printVehicle(cout,
                                                         vehicleType, licensePlate, exiting_vehicle_entrance_time);
        ParkingLotUtils::ParkingLotPrinter::printExitSuccess(cout,
                                                             exiting_vehicle_spot, exitTime, bill);
        ParkingLot::remove_vehicle(exiting_vehicle_spot.getParkingBlock(),
                                   exiting_vehicle_spot.getParkingNumber());
        return ParkingLotUtils::ParkingResult::SUCCESS;

    }

}


