#include <iostream>
#include <string>
using namespace std;

class Building {
private:
    string name;
    double area;
    static int buildingCount;     
    static double totalConstructionCost; 

public:
    Building() {
        name = "Unknown Building";
        area = 0.0;
        buildingCount++;
        cout << "Default constructor for Building called!" << endl;
    }

    Building(string name, double area) {
        this->name = name;
        this->area = area;
        buildingCount++; 
        cout << "Parameterized constructor for Building called!" << endl;
    }

    virtual ~Building() {
        cout << "Destructor for Building '" << name << "' called!" << endl;
    }

    static int getBuildingCount() {
        return buildingCount;
    }

    static double getTotalConstructionCost(double costPerSqm) {
        return buildingCount * costPerSqm;
    }

    Building& setArea(double newArea) {
        this->area = newArea;
        return *this;
    }

    double calculateCost(double costPerSqm) {
        return this->area * costPerSqm;
    }

    virtual void displayInfo() = 0;

    double getArea() const {
        return this->area;
    }
};

int Building::buildingCount = 0;
double Building::totalConstructionCost = 0.0;

class Material {
private:
    string type;
    double costPerSqm;

public:
    Material() {
        type = "Generic Material";
        costPerSqm = 0.0;
        cout << "Default constructor for Material called!" << endl;
    }

    Material(string type, double costPerSqm) {
        this->type = type;
        this->costPerSqm = costPerSqm;
        cout << "Parameterized constructor for Material called!" << endl;
    }

    ~Material() {
        cout << "Destructor for Material '" << type << "' called!" << endl;
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
    static double totalEnergyConsumption;  

    EnergySimulationEngine() {
        energyConsumption = 0.0;
        cout << "Default constructor for EnergySimulationEngine called!" << endl;
    }

    EnergySimulationEngine(double consumption) {
        this->energyConsumption = consumption;
        cout << "Parameterized constructor for EnergySimulationEngine called!" << endl;
    }

    ~EnergySimulationEngine() {
        cout << "Destructor for EnergySimulationEngine called!" << endl;
    }

    double calculateEnergyEfficiency(double area) {
        return energyConsumption * area;
    }

    double calculateEnergyEfficiency(int numApartments) { 
        return energyConsumption * numApartments * 10;  
    }

    void displayEnergyEfficiency(double area) {
        double totalEnergy = calculateEnergyEfficiency(area);
        totalEnergyConsumption += totalEnergy; 
        cout << "Total Energy Consumption: " << totalEnergy << " kWh for " << area << " sqm" << endl;
    }

    void displayEnergyEfficiency(int numApartments) {
        double totalEnergy = calculateEnergyEfficiency(numApartments);
        totalEnergyConsumption += totalEnergy; 
        cout << "Total Energy Consumption: " << totalEnergy << " kWh for " << numApartments << " apartments" << endl;
    }

    static double getTotalEnergyConsumption() {
        return totalEnergyConsumption;
    }
};

double EnergySimulationEngine::totalEnergyConsumption = 0.0;

class UserDetail {
private:
    string name;
    string companyName;
    string password;

public:
    UserDetail() {
        name = "Unknown";
        companyName = "Unknown";
        password = "";
        cout << "Default constructor for UserDetail called!" << endl;
    }

    UserDetail(string name, string companyName, string password) {
        this->name = name;
        this->companyName = companyName;
        this->password = password;
        cout << "Parameterized constructor for UserDetail called!" << endl;
    }

    ~UserDetail() {
        cout << "Destructor for UserDetail '" << name << "' called!" << endl;
    }

    string getName() const {
        return name;
    }

    string getCompanyName() const {
        return companyName;
    }

    void setPassword(string newPassword) {
        password = newPassword;
    }

    bool checkPassword(string enteredPassword) {
        return enteredPassword == password;
    }
};


class ResidentialBuilding : public Building {
private:
    int numApartments;

public:
    ResidentialBuilding(string name, double area, int numApartments)
        : Building(name, area), numApartments(numApartments) {
        cout << "ResidentialBuilding constructor called!" << endl;
    }

    void displayInfo() override { 
        Building::displayInfo();  
        cout << "Number of Apartments: " << numApartments << endl;
    }
};

class SolarPoweredBuilding : public ResidentialBuilding {
private:
    double solarPanelArea;

public:
    SolarPoweredBuilding(string name, double area, int numApartments, double solarPanelArea)
        : ResidentialBuilding(name, area, numApartments), solarPanelArea(solarPanelArea) {
        cout << "SolarPoweredBuilding constructor called!" << endl;
    }

    double calculateSolarEnergy(double energyPerSqm) {
        return solarPanelArea * energyPerSqm;
    }

    void displayInfo() override {
        ResidentialBuilding::displayInfo(); 
        cout << "Solar Panel Area: " << solarPanelArea << " sqm" << endl;
    }
};

int main() {
    Building* buildings[3];
    buildings[0] = new ResidentialBuilding("Residential Apartment 1", 500.0, 10);
    buildings[1] = new ResidentialBuilding("Residential Apartment 2", 300.0, 5);
    buildings[2] = new ResidentialBuilding("Residential Apartment 3", 800.0, 15);

    Material* concrete = new Material("Concrete", 150.0);
    EnergySimulationEngine* energySim = new EnergySimulationEngine(12.5);
    UserDetail* users[3];
    users[0] = new UserDetail("Alice", "ABC Corp", "password123");
    users[1] = new UserDetail("Bob", "XYZ Ltd", "pass456");
    users[2] = new UserDetail("Charlie", "LMN Inc", "charlie789");

    concrete->displayInfo();

    string enteredUser;
    cout << "Is your user in this list? (yes/no): ";
    cin >> enteredUser;

    if (enteredUser == "yes" || enteredUser == "YES") {
        cout << "Enter your name: ";
        string userName;
        cin >> userName;

        bool userFound = false;
        for (int i = 0; i < 3; ++i) {
            if (users[i]->getName() == userName) {
                userFound = true;
                string enteredPassword;
                cout << "Enter your password: ";
                cin >> enteredPassword;

                if (users[i]->checkPassword(enteredPassword)) {
                    cout << "Password correct!" << endl;
                    cout << "User Name: " << users[i]->getName() << endl;
                    cout << "Company: " << users[i]->getCompanyName() << endl;
                } else {
                    cout << "Incorrect password!" << endl;
                }
                break;
            }
        }

        if (!userFound) {
            cout << "User not found!" << endl;
            return 0;
        }
    } else {
        cout << "Exiting..." << endl;
        return 0;
    }

    for (int i = 0; i < 3; ++i) {
        cout << "\nDetails for Building " << (i + 1) << ":\n";
        buildings[i]->displayInfo();
        double totalCost = buildings[i]->calculateCost(concrete->getCostPerSqm());
        cout << "Total Construction Cost: $" << totalCost << endl;
        energySim->displayEnergyEfficiency(buildings[i]->getArea());
    }

    cout << "\nTotal Buildings Created: " << Building::getBuildingCount() << endl;
    cout << "Total Energy Consumption for All Buildings: " << EnergySimulationEngine::getTotalEnergyConsumption() << " kWh" << endl;

    delete concrete;
    delete energySim;
    for (int i = 0; i < 3; ++i) {
        delete buildings[i];
        delete users[i];
    }

    return 0;
}
