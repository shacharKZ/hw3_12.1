#include "Vehicle.h"

namespace MtmParkingLot {

    Vehicle::Vehicle(VehicleType vehicleType, LicensePlate licensePlate,
            Time starting_time) :
            got_a_ticket(false), vehicleType(vehicleType),
            licensePlate(licensePlate), entrance_time(starting_time) {}

    Vehicle::Vehicle(const Vehicle &other) :
            got_a_ticket(other.got_a_ticket), vehicleType(other.vehicleType),
            licensePlate(other.licensePlate), entrance_time(other.entrance_time)
            {}

    void Vehicle::get_a_ticket() {
        this->got_a_ticket = true;
    }

    bool Vehicle::did_he_get_a_ticket() const {
        return got_a_ticket ? true : false;
    }
}

