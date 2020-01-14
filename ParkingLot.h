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

    // using for every time referencing to this type of template
    typedef UniqueArray<Vehicle, Vehicle::areVehicleTheSame> partial_parking_lot;

    /**
     * @brief Represents parking lot divided to 3 section
     * every section represents by UniqueArray with given size
     * represnts its num of parking spots
     *
     */
    class ParkingLot {
        partial_parking_lot bike; // MOTORBIKE section
        partial_parking_lot handi; // HANDICAPPED section
        partial_parking_lot car; // CAR (regular) section

        /**
         * @brief auxiliary func check if a given vehicle is parking inside given parking lot and insert it if not
         *
         * @param current a vehicle we want to check if inside the parking lot
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles>
         * @param index if current is inside park or if insert it assign its index (in UA) into index
         * @param section the section where the vehcile try to park bike/handi/car
         * @param  timeIfAlreadyPark in case the vehcile is already parking we want to know when did it enter the park
         * @return ParkingResult: SUCCESS if insert, VEHICLE_ALREADY_PARKED if already in park,
         * and NO_EMPTY_SPOT if the park if full
         */
        ParkingResult enterParkingAUX(const Vehicle& current,
                                      partial_parking_lot& park,
                                      unsigned int& index,
                                      Time& timeIfAlreadyPark,
                                      VehicleType section);

        /**
         * @brief auxiliary func check if a given vehicle is parking inside given parking lot
         *
         * @param current a vehicle we want to check if inside the parking lot
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles>
         * @param index if current is inside park or if insert it assign its index (in UA) into index
         * @return  true if current is inside park, false otherwise
         */
        bool getParkingSpotAUX(Vehicle current, unsigned int& index,
                               const partial_parking_lot& park) const ;

        /**
         * @brief auxiliary func print all the cars parking inside given parking lot
         *
         * @param os
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles> we want to print
         * @param currentType the section park represents
         * @return  os
         */
        ostream& printParkingLotAux(ostream& os,
                                    const partial_parking_lot& park, VehicleType currentType) const;


        // TODO
        void addParkToVector(const partial_parking_lot& park, std::vector<Vehicle>& vec, VehicleType sector);


        /**
         * @brief auxiliary func calculate how much a vehicle need to pay when exiting
         *
         * @param exitTime the time the vehicle leave the parking lot
         * @param park an UniqueArray<Vehicle, Vehicle::CompareVehicles> we want to print
         * @param vehicleType the type of the vehicle that exiting
         * @param parking_num the index of the vehicle inside its parking lot section
         * @param exiting_car_entrance_time the entrance time of the given vehicle
         * @return  sum that the given vehicle need to pay
         */
        unsigned int pay_day(Time exitTime, ParkingLotUtils::
        VehicleType vehicleType, VehicleType lot, unsigned int parking_num,
                             Time& exiting_car_entrance_time);

        /**
         * @brief auxiliary func remove a given vehicle from a given parking represents by an int
         *
         * @param vehicleType the type of current vehicle we want to dele
         * @param parking_num represnts the index of the vehicle we want to delete inside its section
         */
        void remove_vehicle (VehicleType vehicleType, unsigned int parking_num);

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
