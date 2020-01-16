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



    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
            bike(parkingBlockSizes[0]), handi(parkingBlockSizes[1]),
            car(parkingBlockSizes[2]) {}


    ParkingResult ParkingLot::enterParkingAUX(Vehicle &current,
            partial_parking_lot &park, unsigned int &index,
            VehicleType section) {
        try {
            index = park.insert(current);
            park.get_ptr_to_elem_for_index(index)->setParkingSpot(index, section);
            current = *park[current];
            return SUCCESS;
        } catch (partial_parking_lot::UniqueArrayIsFullException &e) {
            return NO_EMPTY_SPOT;
        }
        return ParkingResult::VEHICLE_NOT_FOUND; // def. will not be used
    }


    ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
            LicensePlate licensePlate, Time entranceTime) {
        Vehicle current (vehicleType, licensePlate, entranceTime);
        unsigned int index = 0; // car parking num
        if (getVehicle(current,index) == true) {
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
        // printing message and return arg according to enterParkingAUX result
        ParkingLotPrinter::printVehicle(cout, vehicleType, licensePlate, entranceTime);
        if (printTemp == SUCCESS) {
            ParkingLotPrinter::printEntrySuccess(cout, current.getParkingSpot());
            return SUCCESS;
        }
        ParkingLotPrinter::printEntryFailureNoSpot(cout);
        return NO_EMPTY_SPOT; // def return and only possible option
    }

    bool Over_Stay(Time initial, Time final) {
        using ParkingLotUtils::Time; // TODO no need
        static const Time::Hour HOURS_PER_DAY = 24; // TODO cant
        Time delta = (final - initial);
        return (delta.toHours() > HOURS_PER_DAY);
    }

    void Give_the_ticket_to_those_who_deserve_it
            (const partial_parking_lot &x, Time inspectionTime, unsigned int &counter) {

        for (unsigned int i = 0; i < x.getSize(); ++i) {
            Vehicle *current = const_cast<Vehicle *>(x.get_ptr_to_elem_for_index(i)); // TODO const_cast?

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

    bool ParkingLot::getVehicleAUX(Vehicle& current, unsigned int &index,
            const partial_parking_lot &park) const {
        if (park.getIndex(current, index) == true) {
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


    ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const {
        Vehicle temp (CAR, licensePlate, Time());
        unsigned int index = 0;

        if (getVehicle(temp, index) == true) {
            parkingSpot = ParkingSpot(temp.getParkingSpot());
            return SUCCESS;
        }
        return VEHICLE_NOT_FOUND;
    }


    void addParkToVector(const partial_parking_lot& park, std::vector<Vehicle>& vec, VehicleType sector) {
        for (unsigned int i = 0; i < park.getSize(); ++i) {
            Vehicle *current = park.get_ptr_to_elem_for_index(i);
            if (current != nullptr) {
                current->setParkingSpot(i, sector); // double check every vehicle holds its real parkingSpotS
                vec.push_back(*current);
            }
        }
    }


    ostream &operator<<(ostream &os, const ParkingLot &parkingLot) {

        vector<Vehicle> allVehicle;

        addParkToVector(parkingLot.bike,allVehicle, MOTORBIKE);
        addParkToVector(parkingLot.handi,allVehicle, HANDICAPPED);
        addParkToVector(parkingLot.car,allVehicle, CAR);

        sort(allVehicle.begin(), allVehicle.end());

        ParkingLotPrinter::printParkingLotTitle(os);
        for (unsigned  int i = 0; i < allVehicle.size(); ++i) {
            os << allVehicle[i];
        }

        return os;
    }

    static unsigned int min(unsigned int a, unsigned int b) { // TODO why?
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
            sum += BIKE_FIRST_HOUR; // TODO merge to a new func?
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

        // TODO why not using remove(element) when element is dummyVehicle with the same licensePlate?
        /*
        Vehicle current (CAR, licensePlate, Time());
        unsigned int index = 0;
        if (bike.remove(current) || handi.remove(current) || car.remove(current) ) {
            return;
        }
         */

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
        using ParkingLotUtils::ParkingSpot; // TODO cant
        ParkingSpot exiting_vehicle_spot;
        // TODO just use getVehicle

        /*
        Vehicle current (CAR, licensePlate, Time());
        unsigned int index = 0;
        if(getVehicle(current, index) == false) {
            ParkingLotPrinter::printExitFailure(cout, licensePlate);
            return ParkingResult::VEHICLE_NOT_FOUND;
        }
        ParkingSpot ps = current.getParkingSpot();
        if (ps.getParkingBlock() == MOTORBIKE) {

        }
        else if (ps.getParkingBlock() == HANDICAPPED) {

        }
        else {

        }

         */


        if (getParkingSpot(licensePlate, exiting_vehicle_spot) == ParkingResult::VEHICLE_NOT_FOUND) {
            ParkingLotUtils::ParkingLotPrinter::printExitFailure(cout, licensePlate); // TODO no need to _::_::_
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


