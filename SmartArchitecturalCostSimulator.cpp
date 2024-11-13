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


    double getArea() const {
        return this->area;
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

class EnergySimulationEngine {
private:
    double energyConsumption; 

public:

    EnergySimulationEngine(double consumption) {
        this->energyConsumption = consumption;
    }


    double calculateEnergyEfficiency(double area) {
        return energyConsumption * area; 
    }


    void displayEnergyEfficiency(double area) {
        double totalEnergy = calculateEnergyEfficiency(area);
        cout << "Total Energy Consumption: " << totalEnergy << " kWh for " << area << " sqm" << endl;
    }
};

int main() {


    Building* buildings[3];
    buildings[0] = new Building("Office Complex", 500.0);
    buildings[1] = new Building("Residential Apartment", 300.0);
    buildings[2] = new Building("Shopping Mall", 800.0);

   
    Material* concrete = new Material("Concrete", 150.0);
    EnergySimulationEngine* energySim = new EnergySimulationEngine(12.5); 


    concrete->displayInfo();


    for (int i = 0; i < 3; ++i) {
        cout << "\nDetails for Building " << (i + 1) << ":\n";
        buildings[i]->displayInfo();
        

        double totalCost = buildings[i]->calculateCost(concrete->getCostPerSqm());
        cout << "Total Construction Cost: $" << totalCost << endl;


        energySim->displayEnergyEfficiency(buildings[i]->getArea());  
    }

    delete concrete;
    delete energySim;
    for (int i = 0; i < 3; ++i) {
        delete buildings[i];
    }

    return 0;
}
