#include "Booking.h"
#include <iostream>
#include <sstream>

using namespace std;

// ---------------------------------------------------------------
// Booking — parameterised constructor
// ---------------------------------------------------------------
Booking::Booking(string name, int roomNum, int persons,
                 string contact, string date)
    : customerName(name), roomNumber(roomNum), numberOfPersons(persons),
      customerContactNumber(contact), bookingDate(date) {}

// ---------------------------------------------------------------
// Booking — deserialisation constructor (CSV line from bookings.txt)
// Format: customerName,roomNumber,numberOfPersons,contactNumber,bookingDate
// ---------------------------------------------------------------
Booking::Booking(const string& serialized) {
    stringstream ss(serialized);
    string item;
    vector<string> tokens;

    // Split the serialized string by commas
    while (getline(ss, item, ',')) {
        tokens.push_back(item);
    }

    // Populate fields only if the correct number of tokens is present
    if (tokens.size() == 5) {
        customerName          = tokens[0];           // Customer name
        roomNumber            = stoi(tokens[1]);     // Room number
        numberOfPersons       = stoi(tokens[2]);     // Number of guests
        customerContactNumber = tokens[3];           // Contact number
        bookingDate           = tokens[4];           // Booking date
    }
}

// ---------------------------------------------------------------
// displayBooking — prints a brief booking summary
// ---------------------------------------------------------------
void Booking::displayBooking() const {
    cout << "Customer Name: " << customerName << "\n"
         << "Room Number:   " << roomNumber   << "\n"
         << "Booking Date:  " << bookingDate  << "\n";
}

// ---------------------------------------------------------------
// serialize — converts Booking to a CSV string for file storage
// ---------------------------------------------------------------
string Booking::serialize() const {
    return customerName          + "," +
           to_string(roomNumber) + "," +
           to_string(numberOfPersons)  + "," +
           customerContactNumber + "," +
           bookingDate;
}
