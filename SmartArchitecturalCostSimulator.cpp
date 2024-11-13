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

    // Getter method for cost per sqm
    double getCostPerSqm() const {
        return this->costPerSqm;
    }
};

int main() {

    Building myBuilding("Office Complex", 500.0);
    Material concrete("Concrete", 150.0);

    myBuilding.displayInfo();
    concrete.displayInfo();

 
    double totalCost = myBuilding.calculateCost(concrete.getCostPerSqm());
    cout << "Total Construction Cost: $" << totalCost << endl;


    myBuilding.setArea(600.0).displayInfo();
    concrete.setCostPerSqm(160.0).displayInfo();

    return 0;
}
