#ifndef EX3_6_1_VEHICLE_H
#define EX3_6_1_VEHICLE_H

#include "ParkingLotTypes.h"
#include "ParkingSpot.h"
#include "Time.h"
#include <ostream>

namespace MtmParkingLot {

    using ParkingLotUtils::LicensePlate;
    using ParkingLotUtils::VehicleType;
    using ParkingLotUtils::Time;
    using ParkingLotUtils::ParkingSpot;
    using std::ostream;


    /**
     * @brief Represents a vehicle parking inside the ParkingLot
     *
     */
    class Vehicle {
        enum VehicleType vehicleType;
        LicensePlate licensePlate; // unique id
        Time entrance_time; // when the vehicle enter the ParkingLot
        bool got_a_ticket; // if an inspection gave the car a ticket
        ParkingSpot whereIPark; // literally

    public:
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
        struct areVehicleTheSame {
            bool operator()(const Vehicle &v1, const Vehicle &v2) const {
                return (v1.licensePlate == v2.licensePlate);
            }
        };


        /**
         * @brief Compares given ParkingSpot objects (sort AUX)
         *
         * @param v1
         * @param v2
         * @return true If v1.parkingSpot < v2.parkingSpot
         * @return false otherwise
         */
        friend bool operator<(const Vehicle& v1, const Vehicle& v2);


        /**
         * @brief Print operator for Vehicle object
         *
         * @param os output stream to print into
         * @param time vehicle object to print
         * @return ostream& output stream after the print
         */
        friend ostream& operator<<(ostream &os, const Vehicle &v);

        /**
         * @brief set a ps to whereIPark
         *
         * @param ps where the vehicle parks
         */
        void setParkingSpot(unsigned int index, VehicleType section);

        /**
        * @brief get the vehicle's whereIPark
        *
        * @return whereIPark
        */
        ParkingSpot getParkingSpot();

        /**
         * @brief get the vehicle's entrance time
         *
         * @return entrance_time
         */
        const Time getEntranceTime();

        /**
         * @brief get the vehicle's type
         *
         * @return vehicleType
         */
        const VehicleType getVehicleType() const;

        /**
         * @brief get the vehicle's type
         *
         * @return vehicleType
         */
        const LicensePlate getLicensePlate();


        /**
         * @brief change got_a_ticket to True, representing inspection gave the car a ticket
         */
        void giveATicket();

        /**
         * @brief return the value of got_a_ticket
         *
         * @return the value of got_a_ticket
         */
        bool didHeGotATicket() const;
    };
}

#endif //EX3_6_1_VEHICLE_H
