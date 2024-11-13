#include <iostream>
#include <string>
using namespace std;

class Building {
private:
    string name;
    double area;

public:

    Building(string n, double a) : name(n), area(a) {}

    double calculateCost(double costPerSqm) {
        return area * costPerSqm;
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
 
    Material(string t, double cost) : type(t), costPerSqm(cost) {}


    void displayInfo() {
        cout << "Material Type: " << type << endl;
        cout << "Cost per sqm: $" << costPerSqm << endl;
    }


    double getCostPerSqm() {
        return costPerSqm;
    }
};

int main() {

    Building myBuilding("Office Complex", 500.0);

    Material concrete("Concrete", 150.0);


    myBuilding.displayInfo();
    concrete.displayInfo();

    double totalCost = myBuilding.calculateCost(concrete.getCostPerSqm());
    cout << "Total Construction Cost: $" << totalCost << endl;

    return 0;
}
