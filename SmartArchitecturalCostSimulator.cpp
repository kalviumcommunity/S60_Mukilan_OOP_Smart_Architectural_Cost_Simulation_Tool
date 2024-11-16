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
        cout << "Basic Simulation - Total Energy Consumption: " << totalEnergy << " kWh for " << area << " sqm" << endl;
    }
};

// Concrete implementation for advanced energy simulation
class AdvancedEnergySimulation : public EnergySimulationStrategy {
private:
    double baseConsumption;
    double efficiencyFactor;

public:
    AdvancedEnergySimulation(double baseConsumption = 0.0, double efficiencyFactor = 1.0)
        : baseConsumption(baseConsumption), efficiencyFactor(efficiencyFactor) {}

    double calculateEnergyEfficiency(double area) const override {
        return (baseConsumption * area) / efficiencyFactor;
    }

    void displayEnergyEfficiency(double area) const override {
        double totalEnergy = calculateEnergyEfficiency(area);
        cout << "Advanced Simulation - Total Energy Consumption: " << totalEnergy << " kWh for " << area << " sqm" << endl;
    }
};

// Abstract base class for building types
class Building {
private:
    string name;
    double area;

public:
    Building(string name, double area) : name(name), area(area) {}

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

// Derived class for commercial buildings
class CommercialBuilding : public Building {
private:
    int numOffices;

public:
    CommercialBuilding(string name, double area, int numOffices)
        : Building(name, area), numOffices(numOffices) {}

    void displayInfo() const override {
        Building::displayInfo();
        cout << "Number of Offices: " << numOffices << endl;
    }
};

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

// Tracker for building statistics
class BuildingStatisticsTracker {
private:
    static int buildingCount;

public:
    static void incrementBuildingCount() {
        buildingCount++;
    }

    static void displayStats() {
        cout << "\nTotal Buildings Created: " << buildingCount << endl;
    }
};
int BuildingStatisticsTracker::buildingCount = 0;

// Main function
int main() {
    vector<unique_ptr<Building>> buildings;
    buildings.push_back(make_unique<ResidentialBuilding>("Residential Apartment 1", 500.0, 10));
    buildings.push_back(make_unique<CommercialBuilding>("Commercial Complex 1", 1200.0, 20));
    buildings.push_back(make_unique<ResidentialBuilding>("Residential Apartment 2", 700.0, 12));

    // Increment building count
    for (const auto& building : buildings) {
        BuildingStatisticsTracker::incrementBuildingCount();
    }


    vector<shared_ptr<EnergySimulationStrategy>> simulations;
    simulations.push_back(make_shared<BasicEnergySimulation>(12.5));
    simulations.push_back(make_shared<AdvancedEnergySimulation>(10.0, 1.5));


    UserDetail user("Alice", "GreenTech Builders", "securePass123", make_shared<AdminRole>());

    cout << "Welcome, Alice from GreenTech Builders!" << endl;

    string enteredPassword;
    cout << "Enter your password: ";
    cin >> enteredPassword;

    if (user.checkPassword(enteredPassword)) {
        cout << "\nAuthentication successful! Proceeding to building details...\n" << endl;
        user.displayRoleAccess();

        for (size_t i = 0; i < buildings.size(); ++i) {
            cout << "\nDetails for Building " << (i + 1) << ":\n";
            buildings[i]->displayInfo();

            for (const auto& simulation : simulations) {
                simulation->displayEnergyEfficiency(buildings[i]->getArea());
            }
        }

        BuildingStatisticsTracker::displayStats();
    } else {
        cout << "Authentication failed! Access denied." << endl;
    }

    return 0;
}
