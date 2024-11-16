#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// Abstract base class for energy simulation strategies
class EnergySimulationStrategy {
public:
    virtual ~EnergySimulationStrategy() = default;
    virtual double calculateEnergyEfficiency(double area) const = 0;
    virtual void displayEnergyEfficiency(double area) const = 0;
};

// Concrete implementation for basic energy simulation
class BasicEnergySimulation : public EnergySimulationStrategy {
private:
    double energyConsumption;

public:
    BasicEnergySimulation(double consumption = 0.0) : energyConsumption(consumption) {}

    double calculateEnergyEfficiency(double area) const override {
        return energyConsumption * area;
    }

    void displayEnergyEfficiency(double area) const override {
        double totalEnergy = calculateEnergyEfficiency(area);
        cout << "Total Energy Consumption: " << totalEnergy << " kWh for " << area << " sqm" << endl;
    }
};

// Statistics tracker interface for modular statistics
class StatisticsTracker {
public:
    virtual ~StatisticsTracker() = default;
    virtual void update(double value) = 0;
    virtual void display() const = 0;
};

// Concrete tracker for building statistics
class BuildingStatisticsTracker : public StatisticsTracker {
private:
    static int buildingCount;
    static double totalEnergyConsumption;

public:
    void update(double energy) override {
        totalEnergyConsumption += energy;
    }

    void display() const override {
        cout << "\nTotal Buildings Created: " << buildingCount << endl;
        cout << "Total Energy Consumption for All Buildings: " << totalEnergyConsumption << " kWh" << endl;
    }

    static void incrementBuildingCount() {
        buildingCount++;
    }

    static int getBuildingCount() {
        return buildingCount;
    }

    static double getTotalEnergyConsumption() {
        return totalEnergyConsumption;
    }
};
int BuildingStatisticsTracker::buildingCount = 0;
double BuildingStatisticsTracker::totalEnergyConsumption = 0.0;

// Base class for user roles
class UserRole {
public:
    virtual ~UserRole() = default;
    virtual void accessBuildingDetails() const = 0;
};

// Admin role with full access
class AdminRole : public UserRole {
public:
    void accessBuildingDetails() const override {
        cout << "Admin Access: Full details available." << endl;
    }
};

// Guest role with limited access
class GuestRole : public UserRole {
public:
    void accessBuildingDetails() const override {
        cout << "Guest Access: Limited details available." << endl;
    }
};

// UserDetail class supporting roles
class UserDetail {
private:
    string name;
    string companyName;
    string password;
    shared_ptr<UserRole> role;

public:
    UserDetail(string name = "Unknown", string companyName = "Unknown", string password = "", shared_ptr<UserRole> role = nullptr)
        : name(name), companyName(companyName), password(password), role(role) {}

    bool checkPassword(const string& enteredPassword) const {
        return password == enteredPassword;
    }

    void displayRoleAccess() const {
        if (role) {
            role->accessBuildingDetails();
        }
    }
};

// Base class for buildings
class Building {
private:
    string name;
    double area;

public:
    Building(string name, double area) : name(name), area(area) {
        BuildingStatisticsTracker::incrementBuildingCount();
    }

    virtual ~Building() = default;

    double getArea() const {
        return area;
    }

    virtual void displayInfo() const {
        cout << "Building Name: " << name << endl;
        cout << "Building Area: " << area << " sqm" << endl;
    }
};

// Derived class for residential buildings
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

// Main function
int main() {
    vector<unique_ptr<Building>> buildings;
    buildings.push_back(make_unique<ResidentialBuilding>("Residential Apartment 1", 500.0, 10));
    buildings.push_back(make_unique<ResidentialBuilding>("Residential Apartment 2", 300.0, 5));
    buildings.push_back(make_unique<ResidentialBuilding>("Residential Apartment 3", 800.0, 15));

    BuildingStatisticsTracker statsTracker;

    shared_ptr<EnergySimulationStrategy> energySim = make_shared<BasicEnergySimulation>(12.5);

    UserDetail user("Alice", "GreenTech Builders", "securePass123", make_shared<AdminRole>());

    cout << "Welcome, " << "Alice from GreenTech Builders!" << endl;

    string enteredPassword;
    cout << "Enter your password: ";
    cin >> enteredPassword;

    if (user.checkPassword(enteredPassword)) {
        cout << "Authentication successful! Proceeding to building details...\n" << endl;
        user.displayRoleAccess();

        for (size_t i = 0; i < buildings.size(); ++i) {
            cout << "\nDetails for Building " << (i + 1) << ":\n";
            buildings[i]->displayInfo();
            energySim->displayEnergyEfficiency(buildings[i]->getArea());
        }

        statsTracker.display();
    } else {
        cout << "Authentication failed! Access denied." << endl;
    }

    return 0;
}
