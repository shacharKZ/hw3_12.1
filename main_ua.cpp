//
// Created by shach on 07/01/2020.
//
#include "UniqueArray.h"
#include "Vehicle.h"
#include <stdio.h>
#include <iostream>


int main(){
    int size = 5;
    UniqueArray<int> ua1 (size);
    ua1.insert(10);
    ua1.insert(15);
    ua1.insert(20);
    ua1.printTest();
    ua1.remove(15);
    ua1.printTest();
    ua1.insert(333);
    ua1.printTest();
    ua1.insert(333);
    ua1.printTest();

    cout << "pass all int tests" << std::endl;

    Car c1 ("mazda", 2004);
    Car c2 ("bmw", 1990);
    Car c3 ("volvo", 2011);
    Car c4 ("ferrari", 2019);

    int size2 = 5;
    UniqueArray<Car, CompareCars> ua2 (size2);
    ua2.insert(c1);
    ua2.insert(c2);
    ua2.insert(c3);
    ua2.printTest();
    ua2.remove(c2);
    ua2.printTest();
    ua2.insert(c3);
    ua2.printTest();
    ua2.insert(c4);
    ua2.printTest();



    return 0;
}