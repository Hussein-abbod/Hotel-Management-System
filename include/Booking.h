#pragma once
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// =============================================================
// Booking Class
// Represents a customer's booking for a specific room.
// =============================================================
class Booking {
public:
    string customerName;          // Full name of the customer
    int    roomNumber;            // Room number reserved
    int    numberOfPersons;       // Number of guests
    string customerContactNumber; // Customer phone / contact
    string bookingDate;           // Check-in date (DD/MM/YYYY)

    // Construct a Booking with all fields
    Booking(string name, int roomNum, int persons, string contact, string date);

    // Deserialise a Booking from a comma-separated string (file persistence)
    explicit Booking(const string& serialized);

    // Print a summary of this booking
    void displayBooking() const;

    // Serialise to a comma-separated string for file persistence
    string serialize() const;
};
