#pragma once
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// =============================================================
// Room Class
// Represents a hotel room with its number, type, price, beds
// and availability status.
// =============================================================
class Room {
public:
    int    roomNumber;    // Unique identifier for the room
    double price;         // Price per night (in RM)
    int    numberOfBeds;  // Number of beds in the room
    string roomType;      // Room type ("Standard", "Deluxe", "Suite")
    bool   isAvailable;   // true = available, false = booked

    // Construct a new Room with all fields
    Room(int num, double pr, int beds, string type);

    // Deserialise a Room from a comma-separated string (file persistence)
    explicit Room(const string& serialized);

    // Print a single formatted row for the room listing table
    void displayRoom() const;

    // Serialise to a comma-separated string for file persistence
    string serialize() const;
};
