#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "Vehicle.h"
#include "vector"

namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    /**
     * using for every time referencing to this type of template
     * section means a part of a parkingLot:
     * the MOTORBIKE section, the HANDICAPPED section or the CAR section
     */
    typedef UniqueArray<Vehicle, Vehicle::areVehicleTheSame> parkingSection;

    /**
     * @brief Represents parking lot divided to 3 section
     * every section represents by UniqueArray with given size
     * represnts its num of parking spots
     *
     */
    class ParkingLot {
        parkingSection bike; // MOTORBIKE section
        parkingSection handi; // HANDICAPPED section
        parkingSection car; // CAR (regular) section

        /**
         * @brief auxiliary func check if a given vehicle is parking inside given parking lot and insert it if not
         *
         * @param current a vehicle we want to check if inside the parking lot
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles>
         * @param index if current is inside park or if insert it assign its index (in UA) into index
         * @param section the section where the vehcile try to park bike/handi/car
         * @return ParkingResult: SUCCESS if insert, VEHICLE_ALREADY_PARKED if already in park,
         * and NO_EMPTY_SPOT if the park if full
         */
        ParkingResult enterParkingAUX(Vehicle& current, parkingSection& park,
                                      unsigned int& index, VehicleType section);

        /**
         * @brief auxiliary func check if a given vehicle is parking inside given parking lot and return it by ref
         *
         * @param current a vehicle we want to check if inside the parking lot. if is inside, the vehicle is also assign into the vehicle
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles>
         * @param index if current is inside park or if insert it assign its index (in UA) into index
         * @return  true if current is inside park, false otherwise
         */
        bool getVehicleAUX(Vehicle& current, unsigned int& index,
                           const parkingSection& park) const ;

        /**
         * @brief auxiliary func check if a given vehicle is parking inside ParkingLot
         *
         * @param current a vehicle we want to check if inside the parking lot. if is inside, the vehicle is also assign into the vehicle
         * @param index if current is inside park or if insert it assign its index (in UA) into index
         * @return  true if current is inside park, false otherwise
         */
        bool getVehicle(Vehicle& current, unsigned int& index) const ;


        /**
         * @brief auxiliary func calculate how much a vehicle need to pay when exiting
         *
         * @param the_bill the final sum to pay, for parking hours, includeing parking ticket
         * @param exitTime the time the vehicle leave the parking lot
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles> we want to print
         * @param vehicleType the type of the vehicle that exiting
         * @param parking_num the index of the vehicle inside its parking lot section
         * @param X_entrance_time the entrance time of the given vehicle
         * @return  sum that the given vehicle need to pay
         */
        void payDay (unsigned int& the_bill , Time exitTime, VehicleType vehicleType,
                     VehicleType lot, unsigned int parking_num,
                     Time &X_entrance_time);

        /**
         * @brief auxiliary func remove a given vehicle from a given parking represents by an int
         *
         * @param block the type of current vehicle we want to dele
         * @param parking_num represnts the index of the vehicle we want to delete inside its section
         */
        void removeVehicle (LicensePlate licensePlate);

    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot() = default;
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
