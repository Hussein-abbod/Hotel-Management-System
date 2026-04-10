// windows.h first to avoid 'byte' ambiguity
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <vector>
#include <limits>
#include "Room.h"
#include "Booking.h"
#include "Utils.h"
#include "colors.h"

using namespace std;

int main() {
    login(); // Authenticate before doing anything

    vector<Room>    rooms;    // All hotel rooms
    vector<Booking> bookings; // All active bookings

    // Load persisted data from the data/ directory
    loadRoomsFromFile(rooms);
    loadBookingsFromFile(bookings);

    // If no rooms were loaded, seed with the default room set
    if (rooms.empty()) {
        rooms = {
            Room(101, 100.0, 2, "Standard"),
            Room(102, 150.0, 3, "Deluxe"),
            Room(103, 200.0, 4, "Suite"),
            Room(104, 100.0, 2, "Standard"),
            Room(105, 150.0, 3, "Deluxe"),
            Room(106, 200.0, 4, "Suite"),
            Room(107, 100.0, 2, "Standard"),
            Room(108, 150.0, 3, "Deluxe"),
            Room(109, 200.0, 4, "Suite"),
            Room(110, 100.0, 2, "Standard")
        };
    }

    int invoiceCounter = 0; // Auto-incremented invoice ID
    int choice;             // User's menu selection

    // Main program loop — runs until the user chooses option 9 (Exit)
    do {
        welcomePage(choice, invoiceCounter);
        cin >> choice;

        // Handle non-numeric input gracefully
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << COLOR_RED << "Invalid choice, please enter a number." << COLOR_RESET << endl;
            Sleep(1000);
            continue;
        }

        switch (choice) {
            case 1: displayAllRooms(rooms);                              break;
            case 2: displayAvailableRooms(rooms);                        break;
            case 3: bookRoom(rooms, bookings);
                    saveRoomsToFile(rooms);
                    saveBookingsToFile(bookings);                         break;
            case 4: checkout(rooms, bookings);
                    saveRoomsToFile(rooms);
                    saveBookingsToFile(bookings);                         break;
            case 5: getInvoice(bookings, rooms, invoiceCounter);         break;
            case 6: displayAllCustomers(bookings, rooms);                break;
            case 7: searchCustomer(bookings, rooms);                     break;
            case 8: editRoom(rooms);
                    saveRoomsToFile(rooms);                              break;
            case 9: saveRoomsToFile(rooms);
                    saveBookingsToFile(bookings);
                    exitProgram();                                        break;
            default:
                cout << COLOR_BOLD_RED << "Invalid choice. Please wait one second and try again" << COLOR_RESET;
                Sleep(1000);
        }

    } while (choice != 9);

    return 0;
}
