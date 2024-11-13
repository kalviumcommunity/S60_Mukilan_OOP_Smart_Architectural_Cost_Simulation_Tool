#include <iostream>
#include <string>
using namespace std;

class Building {
private:
    string name;
    double area;

public:
   
    Building(string name, double area) {
        this->name = name;
        this->area = area;
    }

   
    Building& setArea(double newArea) {
        this->area = newArea;
        return *this;  
    }


    double calculateCost(double costPerSqm) {
        return this->area * costPerSqm;
    }


    void displayInfo() {
        cout << "Building Name: " << name << endl;
        cout << "Area: " << area << " sqm" << endl;
    }
};

class Material {
private:
    string type;
    double costPerSqm;  

public:

    Material(string type, double costPerSqm) {
        this->type = type;
        this->costPerSqm = costPerSqm;
    }


    Material& setCostPerSqm(double newCost) {
        this->costPerSqm = newCost;
        return *this;  
    }


    void displayInfo() {
        cout << "Material Type: " << type << endl;
        cout << "Cost per sqm: $" << costPerSqm << endl;
    }


    double getCostPerSqm() const {
        return this->costPerSqm;
    }
};

int main() {

    Building buildings[] = {
        Building("Office Complex", 500.0),
        Building("Residential Apartment", 300.0),
        Building("Shopping Mall", 800.0)
    };


    Material concrete("Concrete", 150.0);


    concrete.displayInfo();

    for (int i = 0; i < 3; ++i) {
        cout << "\nDetails for Building " << (i + 1) << ":\n";
        buildings[i].displayInfo();
        double totalCost = buildings[i].calculateCost(concrete.getCostPerSqm());
        cout << "Total Construction Cost: $" << totalCost << endl;
    }

    return 0;
}
