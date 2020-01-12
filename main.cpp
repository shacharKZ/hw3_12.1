#include <iostream>
#include "UniqueArray.h"
#include "Vehicle.h"
#include "ParkingLotTypes.h"
#include "ParkingLot.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "ParkingLotPrinter.h"

using std::cout;

using ParkingLotUtils::LicensePlate;
using ParkingLotUtils::VehicleType;
using ParkingLotUtils::Time;
using ParkingLotUtils::MOTORBIKE;
using ParkingLotUtils::HANDICAPPED;
using ParkingLotUtils::CAR;
using MtmParkingLot::ParkingLot;
using MtmParkingLot::ParkingSpot;
using MtmParkingLot::ParkingLotPrinter;

int main(){
    Time initial(0,0,0);
    unsigned int arr2[] = {5, 5, 5};
    ParkingLot pl (arr2);

    cout << "------------ enetering vehicles -------------" << std::endl << std::endl;


    pl.enterParking(MOTORBIKE, "bike1", initial);
    pl.enterParking(HANDICAPPED, "handi1", initial);
    pl.enterParking(CAR, "car1", initial);

    pl.enterParking(MOTORBIKE, "bike2", initial);
    pl.enterParking(HANDICAPPED, "handi2", initial);
    pl.enterParking(CAR, "car2", initial);

    pl.enterParking(MOTORBIKE, "bike3", initial);
    pl.enterParking(HANDICAPPED, "handi3", initial);
    pl.enterParking(CAR, "car3", initial);

    pl.enterParking(MOTORBIKE, "bike4", initial);
    pl.enterParking(HANDICAPPED, "handi4", initial);
    pl.enterParking(CAR, "car4", initial);

    pl.enterParking(MOTORBIKE, "bike5", initial);
    pl.enterParking(HANDICAPPED, "handi5", initial);
    pl.enterParking(CAR, "car5", initial);

    cout << "------------ exiting after 0 time -------------" << std::endl << std::endl;


    pl.exitParking("bike1", initial);
    pl.exitParking("handi1", initial);
    pl.exitParking("car1", initial);


    cout << "------------ exiting after 1 minute -------------"<< std::endl << std::endl;

    initial+=1;
    pl.exitParking("bike2", initial);
    pl.exitParking("handi2", initial);
    pl.exitParking("car2", initial);

    cout << "------------ exiting after 3.5 hours -------------" << std::endl << std::endl;

    initial+=209;
    pl.exitParking("bike3", initial);
    pl.exitParking("handi3", initial);
    pl.exitParking("car3", initial);

    cout << "------------ exiting after 8 hours -------------" << std::endl << std::endl;

    initial+=270;
    pl.exitParking("bike4", initial);
    pl.exitParking("handi4", initial);
    pl.exitParking("car4", initial);

    cout << "------------ exiting after 30 hours with a ticket -------------"<< std::endl << std::endl;

    initial+=1320;
    pl.inspectParkingLot(initial);
    pl.exitParking("bike5", initial);
    pl.exitParking("handi5", initial);
    pl.exitParking("car5", initial);









    /*
    Vehicle car1(MOTORBIKE , "first", initial);
    initial+=1000;
    Vehicle car2(HANDICAPPED, "second", initial);
    cout << car1.entrance_time << " " << car1.licensePlate << " " << car1.vehicleType << std::endl;
    cout << car2.entrance_time << " " << car2.licensePlate << " " << car2.vehicleType << std::endl;
    cout << "now testing the inspection code" <<std::endl;
    initial +=1500;
    cout << "current time is " << initial <<std::endl;
    unsigned int arr[] = {10, 2, 3};
    ParkingLot my_parking(arr);
    my_parking.inspectParkingLot(initial);

    cout << "<--------------Test enterParking func:-------------->" << std::endl;
    unsigned int arr2[] = {5, 3, 5};
    ParkingLot pl (arr2);
    pl.enterParking(MOTORBIKE, "1", initial);
    pl.enterParking(MOTORBIKE, "2", initial);
    pl.enterParking(MOTORBIKE, "3", initial);
    pl.enterParking(MOTORBIKE, "3", initial); // already in spot 2
    pl.enterParking(MOTORBIKE, "4", initial);
    pl.enterParking(MOTORBIKE, "5", initial);
    pl.enterParking(MOTORBIKE, "5", initial);// already in spot 4. not FULL!!
    pl.enterParking(MOTORBIKE, "6", initial); // FULL

    pl.enterParking(HANDICAPPED, "a", initial);
    pl.enterParking(HANDICAPPED, "b", initial);
    pl.enterParking(HANDICAPPED, "c", initial);
    pl.enterParking(HANDICAPPED, "d", initial); // 666 there is a test we need to run whene exit func be writen
    pl.enterParking(MOTORBIKE, "FULL", initial); // FULL
    pl.enterParking(CAR, "e", initial);
    pl.enterParking(CAR, "f", initial);
    pl.enterParking(CAR, "g", initial);
    pl.enterParking(HANDICAPPED, "f", initial);
    cout << "<--------------Finish testing enterParking func-------------->" << std::endl;



    cout << "<--------------Test getParkingSpot func:-------------->" << std::endl;
    ParkingSpot ps = ParkingSpot(VehicleType::CAR, 0);
    cout << "need to be MOTORBIKE-4: ";
    pl.getParkingSpot("5", ps);
    ParkingLotPrinter::printEntryFailureAlreadyParked(cout, ps);

    cout << "need to be Car(Vehicle)-0: ";
    pl.getParkingSpot("d", ps);
    ParkingLotPrinter::printEntryFailureAlreadyParked(cout, ps);

    cout << "need to beCar(Vehicle)-0 because should not be found: ";
    pl.getParkingSpot("NOOOOOOOOOOOOOOOOOOO", ps);
    ParkingLotPrinter::printEntryFailureAlreadyParked(cout, ps);

    cout << "need to beCar(Vehicle)-1: ";
    pl.getParkingSpot("e", ps);
    ParkingLotPrinter::printEntryFailureAlreadyParked(cout, ps);
    cout << "<--------------Finish testing getParkingSpot func-------------->" << std::endl;

    cout << "<--------------Test print operator << :-------------->" << std::endl;
    cout << pl;
    pl.enterParking(CAR, "LAST PLACE", initial);
    pl.enterParking(CAR, "should be FULL", initial);
    cout << pl;
    cout << "<--------------Finish testing print operator << -------------->" << std::endl;

    cout << "@@@@@@@@@@@@@@@@@@    EILON testing beging here @@@@@@@@@@@@@@@@" << std::endl;

    cout << pl;

    cout << "------------ test first inspection -------------" << std::endl;


    initial+=700;
    pl.inspectParkingLot(initial);

    cout << "------------ first test exit -------------" << std::endl;


    pl.exitParking("1", initial);
    pl.exitParking("a", initial);
    pl.exitParking("e", initial);

    cout << "------------ print the lot again after exit -------------" << std::endl;

    cout << pl;

    cout << "------------ test second inspection -------------" << std::endl;

    initial+=800;
    pl.inspectParkingLot(initial);

    cout << "------------ test second exit -------------" << std::endl;

    pl.exitParking("3", initial);
    pl.exitParking("d", initial);
    pl.exitParking("f", initial);

    cout << "------------ enter vehicles after exit -------------" << std::endl;

    pl.enterParking(MOTORBIKE, "eilon1", initial);
    pl.enterParking(MOTORBIKE, "eilon2", initial);
    cout << "------------ after this should show that eilon2 is already in -------------" << std::endl;

    pl.enterParking(MOTORBIKE, "eilon2", initial);

    cout << "------------ after this should show that there is no place for eilon 3 -------------" << std::endl;

    pl.enterParking(MOTORBIKE, "eilon3", initial);

    pl.enterParking(HANDICAPPED, "shachar1", initial);
    pl.enterParking(CAR, "holder", initial);
    pl.enterParking(HANDICAPPED, "shachar2", initial);

    cout << "------------ print lot after entering after exit -------------" << std::endl;

    cout << pl;
*/

    return 0;
}