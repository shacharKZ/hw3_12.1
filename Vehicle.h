#ifndef EX3_6_1_VEHICLE_H
#define EX3_6_1_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"

namespace MtmParkingLot {

    using ParkingLotUtils::LicensePlate;
    using ParkingLotUtils::VehicleType;
    using ParkingLotUtils::Time;

    /**
     * @brief Represents a vehicle parking inside the ParkingLot
     *
     */
    class Vehicle {
        bool got_a_ticket; // if an inspection gave the car a ticket

    public:
        const enum VehicleType vehicleType;
        const LicensePlate licensePlate;
        const Time entrance_time; // when the vehicle enter the ParkingLot

        /**
         * @brief Construct a new Vehicle object
         *
         * @param vehicleType MOTORBIKE\ HANDICAPPED\ CAR
         * @param licensePlate unique "id" for each car
         * @param starting_time Represents the enter time into ParkingLot
         */
        Vehicle(VehicleType vehicleType, LicensePlate licensePlate,
                Time starting_time);

        /**
         * @brief Construct (by copy) a new Vehicle object
         *
         * @param other an vehicle to copy
         */
        Vehicle(const Vehicle &other);

        // def destructor (nothing special)
        ~Vehicle() = default;

        /**
         * @brief Struct used as a compare function by overloading operator ()
         * the compartion been done by compare the vehicle's licensePlate
         * @param v1 a vehicle to compare
         * @param v2 a vehicle to compare
         */
        struct CompareVehicles {
            bool operator()(const Vehicle &v1, const Vehicle &v2) const {
                return (v1.licensePlate == v2.licensePlate);
            }
        };

        /**
         * @brief change got_a_ticket to True, represanting inspection gave the car a ticket
         */
        void get_a_ticket();

        /**
         * @brief return the value of got_a_ticket
         *
         * @return the value of got_a_ticket
         */
        bool did_he_get_a_ticket() const;
    };
}

#endif //EX3_6_1_VEHICLE_H
