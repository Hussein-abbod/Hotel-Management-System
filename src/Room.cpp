#include "Room.h"
#include "colors.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// ---------------------------------------------------------------
// Room — parameterised constructor
// ---------------------------------------------------------------
Room::Room(int num, double pr, int beds, string type)
    : roomNumber(num), price(pr), numberOfBeds(beds),
      roomType(type), isAvailable(true) {}

// ---------------------------------------------------------------
// Room — deserialisation constructor (CSV line from rooms.txt)
// Format: roomNumber,price,numberOfBeds,roomType,isAvailable
// ---------------------------------------------------------------
Room::Room(const string& serialized) {
    stringstream ss(serialized);
    string item;
    vector<string> tokens;

    // Split the serialized string by commas
    while (getline(ss, item, ',')) {
        tokens.push_back(item);
    }

    // Populate fields only if the correct number of tokens is present
    if (tokens.size() == 5) {
        roomNumber    = stoi(tokens[0]);         // Convert string to int
        price         = stod(tokens[1]);         // Convert string to double
        numberOfBeds  = stoi(tokens[2]);         // Convert string to int
        roomType      = tokens[3];               // Assign room type string
        isAvailable   = (tokens[4] == "1");      // "1" = available
    }
}

// ---------------------------------------------------------------
// displayRoom — prints a single formatted table row
// ---------------------------------------------------------------
void Room::displayRoom() const {
    string status = isAvailable
        ? COLOR_GREEN  + "Available."     + COLOR_RESET
        : COLOR_RED    + "Not Available." + COLOR_RESET;

    cout << left
         << setw(12) << roomType
         << setw(15) << numberOfBeds
         << setw(10) << ("Rm" + to_string((int)price))
         << setw(12) << roomNumber
         << setw(12) << status
         << "\n";
}

// ---------------------------------------------------------------
// serialize — converts Room to a CSV string for file storage
// ---------------------------------------------------------------
string Room::serialize() const {
    return to_string(roomNumber) + "," +
           to_string(price)      + "," +
           to_string(numberOfBeds) + "," +
           roomType               + "," +
           (isAvailable ? "1" : "0");
}
