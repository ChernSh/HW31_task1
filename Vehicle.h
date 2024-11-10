#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Vehicle {
protected:
    string number;
    string color;
    double price;
    int maxSpeed;
    int year;

public:
    Vehicle(string number, string color, double price, int maxSpeed, int year)
    {
        this->number = number;
        this->color = color;
        this->price = price;
        this->maxSpeed = maxSpeed;
        this->year = year;
    };
    virtual void show() const = 0;

    string getNumber()const { return number; }
    double getPrice() const { return price; }
    int getMaxSpeed() const { return maxSpeed; }
    int getYear() const { return year; }
    string getColor() const { return color; }
    void setPrice(double price) { this->price = price; }
    void setColor(string color) { this->color = color; }

    virtual string getType() const = 0 {};
};

class Car : public Vehicle {
    int numDoors;
public:
    Car(string number, string color, double price, int maxSpeed, int year, int numDoors)
        : Vehicle(number, color, price, maxSpeed, year)
    {
        this->numDoors = numDoors;
    };
    string getType()const override {
        return "Car";
    }
    void show() const override {
        cout << "Car:\nNumber: " << number << "\nColor: " << color << "\nPrice : " << price
            << "\nMax Speed: " << maxSpeed << " km/h \nYear: " << year
            << "\nDoors: " << numDoors << endl;
    };
};

class Bicycle : public Vehicle {
    bool hasGear;

public:
    Bicycle(string number, string color, double price, int maxSpeed, int year, bool hasGear)
        : Vehicle(number, color, price, maxSpeed, year)
    {
        this->hasGear = hasGear;
    };
    string getType()const override {
        return "Bicycle";
    }
    void show() const override {
        cout << "Bicycle:\nNumber: " << number << "\nColor: " << color << "\nPrice : " << price
            << "\nMax Speed: " << maxSpeed << " km/h\nYear: " << year
            << "\nHas Gear: " << (hasGear ? "Yes" : "No") << endl;
    };
};

class Lorry : public Vehicle {
    int loadCapacity;
public:
    Lorry(string number, string color, double price, int maxSpeed, int year, int loadCapacity)
        : Vehicle(number, color, price, maxSpeed, year)
    {
        this->loadCapacity = loadCapacity;
    };
    string getType()const override {
        return "Lorry";
    }
    void show() const override {
        cout << "Lorry:\nNumber: " << number << "\nColor: " << color << "\nPrice : " << price
            << "\nMax Speed: " << maxSpeed << " km/h\nYear: " << year
            << "\nLoad Capacity: " << loadCapacity << " kg" << endl;
    };
};

class Garage {
    vector<Vehicle*> vehicles;
public:
    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }
    void removeVehicle(int index) {
        if (index >= 0 && index < vehicles.size()) {
            delete vehicles[index];
            vehicles.erase(vehicles.begin() + index);
        }
        else {
            cout << "Invalid index.\n";
        }
    }
    void show() const {
        for (int i = 0; i < vehicles.size(); i++) {
            vehicles[i]->show();
            cout << endl;
        }
    }
    void findVehicleByType(string type) const {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i]->getType() == type) {
                vehicles[i]->show();
                cout << "-----------------------------\n\n";
            }
        }
    }
    void findVehicleByNumber(string num) const {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i]->getNumber() == num) {
                vehicles[i]->show();
                cout << "-----------------------------\n\n";
            }
        }
    }

    void findVehicleBySpeedAndType(int speed, string type) const {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i]->getMaxSpeed() == speed && vehicles[i]->getType() == type) {
                vehicles[i]->show();
                cout << "-----------------------------\n\n";
            }
        }
    }

    void editVehicle(int index, double newPrice, string newColor) {
        if (index >= 0 && index < vehicles.size()) {
            vehicles[index]->setPrice(newPrice);
            vehicles[index]->setColor(newColor);
        }
        else {
            cout << "Invalid index.\n";
        }
    }

    void sortBySpeed() {
        sort(vehicles.begin(), vehicles.end(), [](Vehicle* a, Vehicle* b) {
            return a->getMaxSpeed() < b->getMaxSpeed();
            });
    }

    void load(string filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string type, color, number; double price;
            int maxS, year, numD, loadC;
            bool hasG;
            while (!file.eof())
            {
                getline(file, type);
                if (type == "Car") {
                    getline(file, number);
                    getline(file, color);
                    file >> price >> maxS >> year >> numD;
                    Vehicle* obj = new Car(number, color, price, maxS, year, numD);
                    vehicles.push_back(obj);
                }
                else if (type == "Bicycle") {
                    getline(file, number);
                    getline(file, color);
                    file >> price >> maxS >> year >> hasG;
                    Vehicle* obj = new Bicycle(number, color, price, maxS, year, hasG);
                    vehicles.push_back(obj);
                }
                else if (type == "Lorry") {
                    getline(file, number);
                    getline(file, color);
                    file >> price >> maxS >> year >> loadC;
                    Vehicle* obj = new Lorry(number, color, price, maxS, year, loadC);
                    vehicles.push_back(obj);
                }
            }
            file.close();
        }
    }
};