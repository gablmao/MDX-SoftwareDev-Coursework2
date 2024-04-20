#include <iostream>
#include <vector>
#include <string>

// Different types of units defined
enum class UnitType {
    Studio,
    OneBedroom,
    TwoBedroom
};

// Class for properties
class Property {
public:
    int id; // Unique ID for the property
    std::string address; // Address 
    UnitType unitType; // Type of unit
    double rentAmount; // Monthly rent amount
    bool leased; // Flag indicating if the property is leased
    int tenantId; // ID of the tenant who leased the property

    // Constructor to initialize property attributes
    Property(int id, const std::string& address, UnitType unitType, double rentAmount) :
        id(id), address(address), unitType(unitType), rentAmount(rentAmount), leased(false), tenantId(-1) {}
};

// Class for tenants
class Tenant {
public:
    int id; // Unique ID for the tenant
    std::string name; // Name of the tenant
    double salary; // Monthly salary 

    // Constructor to initialize tenant attributes
    Tenant(int id, const std::string& name, double salary) :
        id(id), name(name), salary(salary) {}
};

// Class for main
class PropertyManagementSystem {
private:
    std::vector<Property> properties; // Vector to store properties
    std::vector<Tenant> tenants; // Vector to store tenants
    int propertyIdCounter = 1; // Counter for assigning property IDs
    int tenantIdCounter = 1; // Counter for assigning tenant IDs

public:
    // Function for adding a property to the system
    void addProperty(const Property& property) {
        Property prop = property;
        prop.id = propertyIdCounter++; // Assigns a unique ID to the property
        properties.push_back(prop); // Adds the property to the vector
    }

    // Function to add a tenant to the system
    void addTenant(const Tenant& tenant) {
        // Checks if the tenant's salary meets the minimum requirement
        if (tenant.salary >= 1000) {
            Tenant ten = tenant;
            ten.id = tenantIdCounter++; // Assigns a unique ID to the tenant
            tenants.push_back(ten); // Adds the tenant to the vector
        } else {
            std::cout << "Tenant's salary is below the minimum required (£1000/month). Unable to add tenant.\n";
        }
    }

    // Function to lease a property to a tenant
    void leaseProperty(int propertyId, int tenantId) {
        // Goes through properties to find the one with the given ID
        for (auto& property : properties) {
            if (property.id == propertyId && !property.leased) {
                // Goes through tenants to find the one with the given ID
                for (const auto& tenant : tenants) {
                    if (tenant.id == tenantId) {
                        // Checks if tenant's salary meets the minimum requirement
                        if (tenant.salary >= 1000) {
                            // Marks the property as leased and assign tenant ID
                            property.leased = true;
                            property.tenantId = tenantId;
                            std::cout << "Property leased successfully.\n";
                            return;
                        } else {
                            std::cout << "Tenant's salary is below the minimum required (£1000/month). Property cannot be leased.\n";
                            return;
                        }
                    }
                }
                std::cout << "Tenant not found.\n";
                return;
            }
        }
        std::cout << "Property not found or already leased.\n";
    }

    // Function to repossess a property
    void repossessProperty(int propertyId) {
        // Goes through properties to find the one with the given ID
        for (auto& property : properties) {
            if (property.id == propertyId && property.leased) {
                // Marks the property as not leased and remove tenant ID
                property.leased = false;
                property.tenantId = -1;
                std::cout << "Property repossessed successfully.\n";
                return;
            }
        }
        std::cout << "Property not found or not leased.\n";
    }

    // Function to display all properties
    void displayProperties() const {
        std::cout << "Properties:\n";
        for (const auto& property : properties) {
            std::string unitType;
            // Converts unit type to string
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
            // Displays property details
            std::cout << "ID: " << property.id << ", Address: " << property.address << ", Unit Type: " << unitType 
                 << ", Rent: £" << property.rentAmount; 
            if (property.leased) {
                std::cout << ", Leased: Yes, Tenant ID: " << property.tenantId;
            } else {
                std::cout << ", Leased: No";
            }
            std::cout << std::endl;
        }
    }

    // Function to display all tenants
    void displayTenants() const {
        std::cout << "Tenants:\n";
        for (const auto& tenant : tenants) {
            // Displays tenant details
            std::cout << "ID: " << tenant.id << ", Name: " << tenant.name << ", Salary: £" << tenant.salary << "/month\n";
        }
    }
};

// Main function for PMS
int main() {
    PropertyManagementSystem pms;

    // Dummy info for tenants
    pms.addTenant(Tenant(1, "Nouar", 1200));
    pms.addTenant(Tenant(3, "Gabs", 1300));

    // Dummy info for properties
    pms.addProperty(Property(1, "123 Main St", UnitType::Studio, 1000));
    pms.addProperty(Property(2, "456 Elm St", UnitType::OneBedroom, 1500));
    pms.addProperty(Property(3, "789 Oak St", UnitType::TwoBedroom, 2000));

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Property\n";
        std::cout << "2. Add Tenant\n";
        std::cout << "3. Lease Property\n";
        std::cout << "4. Repossess Property\n";
        std::cout << "5. Display Properties\n";
        std::cout << "6. Display Tenants\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "\nEnter Property Details:\n";
                int id;
                std::string address;
                int unitType;
                double rentAmount;

                std::cout << "Enter Property ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Address: ";
                std::getline(std::cin, address); 
                std::cout << "Enter Unit Type (0 for Studio, 1 for One Bedroom, 2 for Two Bedroom): ";
                std::cin >> unitType;
                std::cout << "Enter Rent Amount: £";
                std::cin >> rentAmount;

                pms.addProperty(Property(id, address, static_cast<UnitType>(unitType), rentAmount));
                break;
            }
            case 2: {
                std::cout << "\nEnter Tenant Details:\n";
                int id;
                std::string name;
                double salary;

                std::cout << "Enter Tenant ID: ";
                std::cin >> id;
                std::cin.ignore(); 
                std::cout << "Enter Name: ";
                std::getline(std::cin, name); 
                std::cout << "Enter Monthly Salary: £";
                std::cin >> salary;

                pms.addTenant(Tenant(id, name, salary));
                break;
            }
            case 3: {
                std::cout << "\nEnter Property ID to Lease: ";
                int propertyId;
                std::cin >> propertyId;
                std::cout << "Enter Tenant ID: ";
                int tenantId;
                std::cin >> tenantId;
                pms.leaseProperty(propertyId, tenantId);
                break;
            }
            case 4: {
                std::cout << "\nEnter Property ID to Repossess: ";
                int propertyId;
                std::cin >> propertyId;
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
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
