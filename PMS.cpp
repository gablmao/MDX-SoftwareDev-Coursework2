#include <iostream>
#include <vector>
#include <limits> // for clearing input buffer

using namespace std;

enum class UnitType {
    Studio,
    OneBedroom,
    TwoBedroom
};

class Property {
public:
    int id;
    string address;
    UnitType unitType;
    double rentAmount;
    bool leased;
    int tenantId; // ID of the tenant who leased the property, -1 if not leased

    Property(int id, const string& address, UnitType unitType, double rentAmount) :
        id(id), address(address), unitType(unitType), rentAmount(rentAmount), leased(false), tenantId(-1) {}
};

class Tenant {
public:
    int id;
    string name;
    double salary; // Monthly salary in GBP

    Tenant(int id, const string& name, double salary) :
        id(id), name(name), salary(salary) {}
};

class PropertyManagementSystem {
private:
    vector<Property> properties;
    vector<Tenant> tenants;
    int propertyIdCounter = 1;
    int tenantIdCounter = 1;

public:
    void addProperty(const Property& property) {
        Property prop = property;
        prop.id = propertyIdCounter++;
        properties.push_back(prop);
    }

    void addTenant(const Tenant& tenant) {
        if (tenant.salary >= 1000) {
            Tenant ten = tenant;
            ten.id = tenantIdCounter++;
            tenants.push_back(ten);
        } else {
            cout << "Tenant's salary is below the minimum required (£1000/month). Unable to add tenant.\n";
        }
    }

    void leaseProperty(int propertyId, int tenantId) {
        for (auto& property : properties) {
            if (property.id == propertyId && !property.leased) {
                for (const auto& tenant : tenants) {
                    if (tenant.id == tenantId) {
                        if (tenant.salary >= 1000) {
                            property.leased = true;
                            property.tenantId = tenantId;
                            cout << "Property leased successfully.\n";
                            return;
                        } else {
                            cout << "Tenant's salary is below the minimum required (£1000/month). Property cannot be leased.\n";
                            return;
                        }
                    }
                }
                cout << "Tenant not found.\n";
                return;
            }
        }
        cout << "Property not found or already leased.\n";
    }

    void repossessProperty(int propertyId) {
        for (auto& property : properties) {
            if (property.id == propertyId && property.leased) {
                property.leased = false;
                property.tenantId = -1;
                cout << "Property repossessed successfully.\n";
                return;
            }
        }
        cout << "Property not found or not leased.\n";
    }

    void displayProperties() const {
        cout << "Properties:\n";
        for (const auto& property : properties) {
            string unitType;
            switch (property.unitType) {
                case UnitType::Studio:
                    unitType = "Studio";
                    break;
                case UnitType::OneBedroom:
                    unitType = "One Bedroom";
                    break;
                case UnitType::TwoBedroom:
                    unitType = "Two Bedroom";
                    break;
            }
            cout << "ID: " << property.id << ", Address: " << property.address << ", Unit Type: " << unitType 
                 << ", Rent: £" << property.rentAmount;  // GBP currency symbol added here
            if (property.leased) {
                cout << ", Leased: Yes, Tenant ID: " << property.tenantId;
            } else {
                cout << ", Leased: No";
            }
            cout << endl;
        }
    }

    void displayTenants() const {
        cout << "Tenants:\n";
        for (const auto& tenant : tenants) {
            cout << "ID: " << tenant.id << ", Name: " << tenant.name << ", Salary: £" << tenant.salary << "/month\n";
        }
    }
};

int main() {
    PropertyManagementSystem pms;

    // Added dummy info for tenets
    pms.addTenant(Tenant(1, "Nouar", 1200));
    pms.addTenant(Tenant(3, "Gabs", 1300));

    // Added dummy info for properties
    pms.addProperty(Property(1, "123 Main St", UnitType::Studio, 1000));
    pms.addProperty(Property(2, "456 Elm St", UnitType::OneBedroom, 1500));
    pms.addProperty(Property(3, "789 Oak St", UnitType::TwoBedroom, 2000));

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Property\n";
        cout << "2. Add Tenant\n";
        cout << "3. Lease Property\n";
        cout << "4. Repossess Property\n";
        cout << "5. Display Properties\n";
        cout << "6. Display Tenants\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter Property Details:\n";
                int id;
                string address;
                int unitType;
                double rentAmount;

                cout << "Enter Property ID: ";
                cin >> id;
                cin.ignore(); // Clear input buffer
                cout << "Enter Address: ";
                getline(cin, address); // Read address with spaces
                cout << "Enter Unit Type (0 for Studio, 1 for One Bedroom, 2 for Two Bedroom): ";
                cin >> unitType;
                cout << "Enter Rent Amount: £";
                cin >> rentAmount;

                pms.addProperty(Property(id, address, static_cast<UnitType>(unitType), rentAmount));
                break;
            }
            case 2: {
                cout << "\nEnter Tenant Details:\n";
                int id;
                string name;
                double salary;

                cout << "Enter Tenant ID: ";
                cin >> id;
                cin.ignore(); // Clear input buffer
                cout << "Enter Name: ";
                getline(cin, name); // Read name with spaces
                cout << "Enter Monthly Salary: £";
                cin >> salary;

                pms.addTenant(Tenant(id, name, salary));
                break;
            }
            case 3: {
                cout << "\nEnter Property ID to Lease: ";
                int propertyId;
                cin >> propertyId;
                cout << "Enter Tenant ID: ";
                int tenantId;
                cin >> tenantId;
                pms.leaseProperty(propertyId, tenantId);
                break;
            }
            case 4: {
                cout << "\nEnter Property ID to Repossess: ";
                int propertyId;
                cin >> propertyId;
                pms.repossessProperty(propertyId);
                break;
            }
            case 5:
                pms.displayProperties();
                break;
            case 6:
                pms.displayTenants();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
