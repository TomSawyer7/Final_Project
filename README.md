# Final_Project
# Vehicle Rental System (C++)

A simple command-line based **Vehicle Rental System** developed in C++. This project includes user authentication, vehicle management, and rental charge calculation. It supports two types of users: **Admin** and **Client**.

## Members

- Thomas Alexandre S. Siman  
- Sean Calvin Theo Lirio

## Features

### User Roles
- **Admin**
  - Add and delete vehicles
  - View all vehicles
- **Client**
  - View available vehicles
  - Rent a vehicle
  - Calculate rental charges

### Authentication
- Sign up and login
- Role-based access (admin/client)
- Validates password and username

### Vehicle Management
- Add vehicles with ID, name, type, and rate
- Delete vehicles by ID
- Display vehicles and their status

### Rental Charges
- Calculates based on days × rate per day

## Tech Used

- C++ Standard Libraries:
  - `iostream`, `vector`, `string`, `iomanip`

## 💻 How to Run

```bash
g++ -o rental VehicleRental.cpp
./rental
