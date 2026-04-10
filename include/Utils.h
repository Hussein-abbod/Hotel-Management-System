#pragma once
#include <string>
#include <vector>
#include "Room.h"
#include "Booking.h"

using namespace std;

// =============================================================
// Utils — Free Function Declarations
// All system-level functions used across the hotel system.
// =============================================================

// --- Date / Time ---
string getCurrentDateTime();

// --- Validation ---
bool isValidDate(const string& date);
bool isAlphabetic(const string& str);

// --- UI Helpers ---
void waitForUser();
void welcomePage(int& option, int& cost);
void startUp();
void exitProgram();

// --- Authentication ---
void login();

// --- Room Operations ---
void displayAllRooms(const vector<Room>& rooms);
void displayAvailableRooms(const vector<Room>& rooms);
void bookRoom(vector<Room>& rooms, vector<Booking>& bookings);
void checkout(vector<Room>& rooms, vector<Booking>& bookings);
void editRoom(vector<Room>& rooms);

// --- Customer / Invoice Operations ---
void searchCustomer(const vector<Booking>& bookings, const vector<Room>& rooms);
void getInvoice(const vector<Booking>& bookings, const vector<Room>& rooms, int& invoiceCounter);
void displayAllCustomers(const vector<Booking>& bookings, const vector<Room>& rooms);

// --- File Persistence ---
void saveRoomsToFile(const vector<Room>& rooms);
void loadRoomsFromFile(vector<Room>& rooms);
void saveBookingsToFile(const vector<Booking>& bookings);
void loadBookingsFromFile(vector<Booking>& bookings);
