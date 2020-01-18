#include "Vehicle.h"
#include "ParkingLotPrinter.h"
#include <ostream>

namespace MtmParkingLot {
    using ParkingLotUtils::ParkingLotPrinter;
    using std::ostream;

    Vehicle::Vehicle(VehicleType vehicleType, LicensePlate licensePlate,
            Time starting_time) :
            vehicleType(vehicleType), licensePlate(licensePlate),
            entrance_time(starting_time), got_a_ticket(false),
            whereIPark(vehicleType, 0){}

    Vehicle::Vehicle(const Vehicle &other) :
            vehicleType(other.vehicleType), licensePlate(other.licensePlate),
            entrance_time(other.entrance_time),
            got_a_ticket(other.got_a_ticket), whereIPark(other.whereIPark) {}


    void Vehicle::giveATicket() {
        this->got_a_ticket = true;
    }

    bool Vehicle::didHeGotATicket() const {
        return got_a_ticket ? true : false;
    }

    bool operator<(const Vehicle& v1, const Vehicle& v2) {
        return (v1.whereIPark < v2.whereIPark);
    }

    ostream& operator<<(ostream &os, const Vehicle &v) {
        ParkingLotPrinter::printVehicle(os, v.vehicleType,
                                              v.licensePlate, v.entrance_time);
        return ParkingLotPrinter::printParkingSpot(os,
                                            v.whereIPark);
    }


    const Time Vehicle::getEntranceTime() {
        return entrance_time;
    }

    const VehicleType Vehicle::getVehicleType() const {
        return vehicleType;
    }

    const LicensePlate Vehicle::getLicensePlate() {
        return licensePlate;
    }

    void Vehicle::setParkingSpot(unsigned int index,
            VehicleType section) {
        whereIPark = ParkingSpot(section, index);
    }

    ParkingSpot Vehicle::getParkingSpot() {
        return whereIPark;
    }

}

