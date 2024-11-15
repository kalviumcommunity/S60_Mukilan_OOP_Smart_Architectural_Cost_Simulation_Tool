#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BuildingStatistics {
private:
    static int buildingCount;
    static double totalEnergyConsumption;

public:
    static void incrementBuildingCount() {
        buildingCount++;
    }

    static void addEnergyConsumption(double energy) {
        totalEnergyConsumption += energy;
    }

    static int getBuildingCount() {
        return buildingCount;
    }

    static double getTotalEnergyConsumption() {
        return totalEnergyConsumption;
    }
};
int BuildingStatistics::buildingCount = 0;
double BuildingStatistics::totalEnergyConsumption = 0.0;


class Building {
private:
    string name;
    double area;

public:
    Building() : name("Unknown Building"), area(0.0) {
        BuildingStatistics::incrementBuildingCount();
    }

    Building(string name, double area) : name(name), area(area) {
        BuildingStatistics::incrementBuildingCount();
    }

    virtual ~Building() {
        cout << "Destructor for Building '" << name << "' called!" << endl;
    }

    double getArea() const {
        return area;
    }

    virtual void displayInfo() const {
        cout << "Building Name: " << name << endl;
        cout << "Building Area: " << area << " sqm" << endl;
    }
};


class Material {
private:
    string type;
    double costPerSqm;

public:
    Material(string type = "Generic Material", double costPerSqm = 0.0) 
        : type(type), costPerSqm(costPerSqm) {}

    ~Material() {
        cout << "Destructor for Material '" << type << "' called!" << endl;
    }

    double getCostPerSqm() const {
        return costPerSqm;
    }

    void displayInfo() const {
        cout << "Material Type: " << type << endl;
        cout << "Cost per sqm: $" << costPerSqm << endl;
    }
};


class EnergySimulationEngine {
private:
    double energyConsumption;

public:
    EnergySimulationEngine(double consumption = 0.0) 
        : energyConsumption(consumption) {}

    ~EnergySimulationEngine() {
        cout << "Destructor for EnergySimulationEngine called!" << endl;
    }

    double calculateEnergyEfficiency(double area) const {
        return energyConsumption * area;
    }

    void displayEnergyEfficiency(double area) const {
        double totalEnergy = calculateEnergyEfficiency(area);
        BuildingStatistics::addEnergyConsumption(totalEnergy);
        cout << "Total Energy Consumption: " << totalEnergy << " kWh for " << area << " sqm" << endl;
    }
};


class UserDetail {
private:
    string name;
    string companyName;
    string password;

public:
    UserDetail(string name = "Unknown", string companyName = "Unknown", string password = "") 
        : name(name), companyName(companyName), password(password) {}

    ~UserDetail() {
        cout << "Destructor for UserDetail '" << name << "' called!" << endl;
    }

    string getName() const {
        return name;
    }

    bool checkPassword(const string& enteredPassword) const {
        return password == enteredPassword;
    }
};


class ResidentialBuilding : public Building {
private:
    int numApartments;

public:
    ResidentialBuilding(string name, double area, int numApartments) 
        : Building(name, area), numApartments(numApartments) {}

    void displayInfo() const override {
        Building::displayInfo();
        cout << "Number of Apartments: " << numApartments << endl;
    }
};


class SolarPoweredBuilding : public ResidentialBuilding {
private:
    double solarPanelArea;

public:
    SolarPoweredBuilding(string name, double area, int numApartments, double solarPanelArea) 
        : ResidentialBuilding(name, area, numApartments), solarPanelArea(solarPanelArea) {}

    void displayInfo() const override {
        ResidentialBuilding::displayInfo();
        cout << "Solar Panel Area: " << solarPanelArea << " sqm" << endl;
    }
};

// Main function
int main() {
    vector<Building*> buildings;
    buildings.push_back(new ResidentialBuilding("Residential Apartment 1", 500.0, 10));
    buildings.push_back(new ResidentialBuilding("Residential Apartment 2", 300.0, 5));
    buildings.push_back(new ResidentialBuilding("Residential Apartment 3", 800.0, 15));

    Material concrete("Concrete", 150.0);
    EnergySimulationEngine energySim(12.5);

    // Create a user and simulate login
    UserDetail user("Alice", "GreenTech Builders", "securePass123");
    cout << "Welcome, " << user.getName() << " from " << "GreenTech Builders!" << endl;

    // Simulate user authentication
    string enteredPassword;
    cout << "Enter your password: ";
    cin >> enteredPassword;

    if (user.checkPassword(enteredPassword)) {
        cout << "Authentication successful! Proceeding to building details...\n" << endl;

       
        concrete.displayInfo();

    
        for (size_t i = 0; i < buildings.size(); ++i) {
            cout << "\nDetails for Building " << (i + 1) << ":\n";
            buildings[i]->displayInfo();
            energySim.displayEnergyEfficiency(buildings[i]->getArea());
        }

        cout << "\nTotal Buildings Created: " << BuildingStatistics::getBuildingCount() << endl;
        cout << "Total Energy Consumption for All Buildings: " << BuildingStatistics::getTotalEnergyConsumption() << " kWh" << endl;
    } else {
        cout << "Authentication failed! Access denied." << endl;
    }


    for (Building* b : buildings) {
        delete b;
    }

    return 0;
}

