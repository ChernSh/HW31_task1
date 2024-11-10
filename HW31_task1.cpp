#include <iostream>
#include "Vehicle.h"

int main() {
    Garage garage;

    garage.load("list.txt");
    garage.show();
    cout << "-----------------------------\n";
    garage.addVehicle(new Car("AX2059AA", "Black", 18000, 220, 2019, 2));
    garage.addVehicle(new Bicycle("AX2022AA", "Pink", 300, 28, 2024, true));
    garage.addVehicle(new Lorry("AX2015AA", "Yellow", 50000, 190, 2017, 3000));

    garage.show();
    cout << "-----------------------------\n";
    garage.removeVehicle(1);;
    garage.show();
    cout << "-----------------------------\n";
    garage.findVehicleByType("Car");
    garage.findVehicleByNumber("AX2015AA");
    garage.findVehicleBySpeedAndType(28, "Bicycle");
    cout << "-----------------------------\n";
    garage.editVehicle(0, 20000, "Black");
    garage.show();
    cout << "-----------------------------\n";
    garage.sortBySpeed();
    garage.show();

    return 0;
}