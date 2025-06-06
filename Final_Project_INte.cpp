#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Vehicle {
public:
    string id, name, type;
    double rate;
    bool available;
    
    Vehicle(string i, string n, string t, double r) 
        : id(i), name(n), type(t), rate(r), available(true) {}
    
    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nType: " << type 
             << "\nRate/Day: PHP " << fixed << setprecision(2) << rate 
             << "\nAvailable: " << (available ? "Yes" : "No") 
             << "\n----------------------------------------\n";
    }
    
    double calculateCharge(int days) {
        return days * rate;
    }
};

// Simple User class
class User {
public:
    string username, password, role;
    
    User(string u, string p, string r) : username(u), password(p), role(r) {}
    
    bool authenticate(string pass) { return password == pass; }
};

// Main System
class VehicleRentalSystem {
private:
    vector<User> users;
    vector<Vehicle> vehicles;
    User* loggedUser = nullptr;
    
    User* findUser(string username) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].username == username) return &users[i];
        }
        return nullptr;
    }
    
    Vehicle* findVehicle(string id) {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i].id == id) return &vehicles[i];
        }
        return nullptr;
    }
    
    string getStringInput(string prompt) {
        string input;
        cout << prompt;
        cin.ignore();
        getline(cin, input);
        return input;
    }

public:
    void signup() {
        string username, password, role;
        cout << "Enter username: "; cin >> username;
        cout << "Enter password: "; cin >> password;
        cout << "Enter role (admin/client): "; cin >> role;
        
        // Validation
        if (username.length() < 3) {
            cout << "Error: Invalid username. Minimum 3 characters required.\n";
            return;
        }
        if (password.length() < 5) {
            cout << "Error: Invalid password. Minimum 5 characters required.\n";
            return;
        }
        if (findUser(username)) {
            cout << "Error: Username already exists.\n";
            return;
        }
        if (role != "admin" && role != "client") {
            cout << "Error: Invalid role. Choose 'admin' or 'client'.\n";
            return;
        }
        
        users.push_back(User(username, password, role));
        cout << "Signup successful for " << role << "!\n";
    }
    
    void login() {
        string username, password;
        cout << "Enter username: "; cin >> username;
        cout << "Enter password: "; cin >> password;
        
        User* user = findUser(username);
        if (!user || !user->authenticate(password)) {
            cout << "Error: Invalid login credentials.\n";
            return;
        }
        
        loggedUser = user;
        cout << "Login successful as " << loggedUser->role << "!\n";
    }
    
    void logout() {
        loggedUser = nullptr;
        cout << "Logged out successfully.\n";
    }
    
    void addVehicle() {
        if (!loggedUser || loggedUser->role != "admin") {
            cout << "Error: Only admin can add vehicles.\n";
            return;
        }
        
        string id, name, type;
        double rate;
        
        cout << "Enter vehicle ID: "; cin >> id;
        if (findVehicle(id)) {
            cout << "Error: Vehicle ID already exists.\n";
            return;
        }
        
        name = getStringInput("Enter vehicle name: ");
        if (name.length() < 2) {
            cout << "Error: Invalid vehicle name. Minimum 2 characters required.\n";
            return;
        }
        
        cout << "Enter vehicle type (standard/premium): "; cin >> type;
        if (type != "standard" && type != "premium") {
            cout << "Error: Invalid vehicle type. Choose 'standard' or 'premium'.\n";
            return;
        }
        
        cout << "Enter rate per day (PHP): "; cin >> rate;
        if (rate <= 0 || rate > 10000) {
            cout << "Error: Invalid rate. Must be between 1 and 10000.\n";
            return;
        }
        
        vehicles.push_back(Vehicle(id, name, type, rate));
        
        cout << "\n=== Vehicle Added Successfully ===\n";
        cout << "Vehicle ID: " << id << "\nVehicle Name: " << name 
             << "\nType: " << type << "\nRate per Day: PHP " 
             << fixed << setprecision(2) << rate << "\n==============================\n\n";
    }
    
    void deleteVehicle() {
        if (!loggedUser || loggedUser->role != "admin") {
            cout << "Error: Only admin can delete vehicles.\n";
            return;
        }
        
        if (vehicles.empty()) {
            cout << "No vehicles available to delete.\n";
            return;
        }
        
        string id;
        cout << "Enter vehicle ID to delete: "; cin >> id;
        
        Vehicle* vehicle = findVehicle(id);
        if (!vehicle) {
            cout << "Error: Vehicle not found.\n";
            return;
        }
        
        cout << "\n=== Vehicle to be deleted ===\n";
        vehicle->display();
        
        char confirm;
        cout << "Are you sure you want to delete this vehicle? (y/n): ";
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            for (int i = 0; i < vehicles.size(); i++) {
                if (vehicles[i].id == id) {
                    vehicles.erase(vehicles.begin() + i);
                    break;
                }
            }
            cout << "Vehicle deleted successfully.\n";
        } else {
            cout << "Deletion cancelled.\n";
        }
    }
    
    void displayVehicles() {
        if (vehicles.empty()) {
            cout << "No vehicles available.\n";
            return;
        }
        
        cout << "\n";
        cout << "+-----+------------------+-------------+------------+-----------+\n";
        cout << "| ID  | Vehicle Name     | Type        | Rate/Day   | Status    |\n";
        cout << "+-----+------------------+-------------+------------+-----------+\n";
        
        for (int i = 0; i < vehicles.size(); i++) {
            cout << "| " << left << setw(3) << (i + 1) 
                 << " | " << left << setw(16) << vehicles[i].name
                 << " | " << left << setw(11) << vehicles[i].type
                 << " | PHP " << left << setw(7) << fixed << setprecision(2) << vehicles[i].rate
                 << " | " << left << setw(9) << (vehicles[i].available ? "Available" : "Rented")
                 << " |\n";
        }
        
        cout << "+-----+------------------+-------------+------------+-----------+\n";
    }
    
    void bookVehicle() {
        if (!loggedUser || loggedUser->role != "client") {
            cout << "Error: Only clients can book vehicles.\n";
            return;
        }
        
        if (vehicles.empty()) {
            cout << "No vehicles available for booking.\n";
            return;
        }
        
        // Show available vehicles
        cout << "\n=== AVAILABLE VEHICLES ===\n";
        bool hasAvailable = false;
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i].available) {
                vehicles[i].display();
                hasAvailable = true;
            }
        }
        
        if (!hasAvailable) {
            cout << "No vehicles currently available for booking.\n";
            return;
        }
        
        string id;
        int days;
        cout << "Enter vehicle ID to book: "; cin >> id;
        cout << "Enter number of days: "; cin >> days;
        
        Vehicle* vehicle = findVehicle(id);
        if (!vehicle) {
            cout << "Error: Vehicle not found.\n";
            return;
        }
        if (!vehicle->available) {
            cout << "Error: Vehicle is not available.\n";
            return;
        }
        if (days <= 0) {
            cout << "Error: Days must be greater than 0.\n";
            return;
        }
        
        double totalCharge = vehicle->calculateCharge(days);
        
        cout << "\n=== BOOKING CONFIRMATION ===\n";
        cout << "Vehicle ID: " << vehicle->id << "\nVehicle Name: " << vehicle->name 
             << "\nType: " << vehicle->type << "\nRate per Day: PHP " 
             << fixed << setprecision(2) << vehicle->rate << "\nNumber of Days: " << days 
             << "\nTotal Charge: PHP " << totalCharge << "\nClient: " << loggedUser->username 
             << "\n===========================\n";
        
        char confirm;
        cout << "Confirm booking? (y/n): ";
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            vehicle->available = false;
            cout << "Vehicle booked successfully!\n";
        } else {
            cout << "Booking cancelled.\n";
        }
    }
    
    void returnVehicle() {
        if (!loggedUser || loggedUser->role != "client") {
            cout << "Error: Only clients can return vehicles.\n";
            return;
        }
        
        // Show rented vehicles
        cout << "\n=== RENTED VEHICLES ===\n";
        bool hasRented = false;
        for (int i = 0; i < vehicles.size(); i++) {
            if (!vehicles[i].available) {
                vehicles[i].display();
                hasRented = true;
            }
        }
        
        if (!hasRented) {
            cout << "No vehicles currently rented.\n";
            return;
        }
        
        string id;
        cout << "Enter vehicle ID to return: "; cin >> id;
        
        Vehicle* vehicle = findVehicle(id);
        if (!vehicle) {
            cout << "Error: Vehicle not found.\n";
            return;
        }
        if (vehicle->available) {
            cout << "Error: Vehicle is not currently rented.\n";
            return;
        }
        
        cout << "\n=== RETURN CONFIRMATION ===\n";
        cout << "Vehicle ID: " << vehicle->id << "\nVehicle Name: " << vehicle->name 
             << "\nReturned by: " << loggedUser->username << "\n==========================\n";
        
        vehicle->available = true;
        cout << "Vehicle returned successfully.\n";
    }
};

int main() {
    VehicleRentalSystem system;
    int choice;
    
    cout << "=== WELCOME TO VEHICLE RENTAL SYSTEM ===\n";
    cout << "=========================================\n";
    
    do {
        cout << "\n=== VEHICLE RENTAL SYSTEM MENU ===\n";
        cout << "1. Signup\n2. Login\n3. Add Vehicle (Admin Only)\n";
        cout << "4. Delete Vehicle (Admin Only)\n5. View All Vehicles\n";
        cout << "6. Book Vehicle (Client Only)\n7. Return Vehicle (Client Only)\n";
        cout << "8. Logout\n9. Exit\n=================================\n";
        cout << "Enter your choice (1-9): ";
        cin >> choice;
        
        switch (choice) {
            case 1: system.signup(); break;
            case 2: system.login(); break;
            case 3: system.addVehicle(); break;
            case 4: system.deleteVehicle(); break;
            case 5: system.displayVehicles(); break;
            case 6: system.bookVehicle(); break;
            case 7: system.returnVehicle(); break;
            case 8: system.logout(); break;
            case 9: cout << "Thank you for using Vehicle Rental System. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please enter a number between 1-9.\n";
        }
    } while (choice != 9);
    
    return 0;
}