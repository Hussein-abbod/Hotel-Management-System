// windows.h MUST come first to avoid 'byte' ambiguity with std::byte
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Utils.h"
#include "colors.h"
#include "Invoice.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <regex>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// =============================================================
// DATE / TIME
// =============================================================

// Returns the current date and time as "YYYY-MM-DD HH:MM:SS"
string getCurrentDateTime() {
    time_t now = time(0);
    char dt[100];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(dt);
}

// =============================================================
// VALIDATION
// =============================================================

// Returns true only if date matches DD/MM/YYYY with valid ranges
bool isValidDate(const string& date) {
    regex datePattern(R"((\d{2})/(\d{2})/(\d{4}))");
    smatch match;
    if (!regex_match(date, match, datePattern)) return false;

    int day   = stoi(match[1].str());
    int month = stoi(match[2].str());

    if (month < 1 || month > 12) return false;
    if (day   < 1 || day   > 31) return false;
    return true;
}

// Returns true if every character in str is a letter or space
bool isAlphabetic(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// =============================================================
// UI HELPERS
// =============================================================

// Pauses execution until the user presses Enter
void waitForUser() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nPress Enter to return to the main menu...";
    cin.get();
}

// Clears screen and renders the main menu
void welcomePage(int& option, int& cost) {
    system("cls");
    string dt = getCurrentDateTime();
    cout << endl << endl;
    cout << "                       System Time: " << dt << endl;

    system("Color B5");
    cout << "                       ==========================================================================================================================================" << endl;
    cout << "                      ||                                                                                                                                         ||" << endl;
    cout << "                      ||  *******   *******             *****          *******             *******    ***************                *****               ******  ||" << endl;
    cout << "                      ||   *   *     *   *             *     *           *   *             *   *      *             *               *     *              *  *    ||" << endl;
    cout << "                      ||   *   *     *   *            *   *   *           *   *           *   *       *     *********              *   *   *            *  *     ||" << endl;
    cout << "                      ||   *   *     *   *           *   * *   *           *   *         *   *        *     *                     *   * *   *          *  *      ||" << endl;
    cout << "                      ||   *   *     *   *          *   *   *   *           *   *       *   *         *     *********            *   *   *   *        *  *       ||" << endl;
    cout << "                      ||   *   *******   *         *   *******   *           *   *     *   *          *             *           *   *     *   *      *  *        ||" << endl;
    cout << "                      ||   *   *******   *        *   *********   *           *   *   *   *           *     *********          *   *       *   *    *  *         ||" << endl;
    cout << "                      ||   *   *     *   *       *   *         *   *           *   * *   *            *     *                 *   *         *   *  *  *          ||" << endl;
    cout << "                      ||   *   *     *   *      *   *           *   *           *   *   *             *     *********        *   *           *   *   *           ||" << endl;
    cout << "                      ||   *   *     *   *     *   *             *   *           *     *              *             *       *   *             *     *            ||" << endl;
    cout << "                      ||  *******   *******  *******             *******         *******              ***************     *******              *****             ||" << endl;
    cout << "                      ||                                                                                                                                         ||" << endl;
    cout << "                       ==========================================================================================================================================" << endl;
    system("Color 00");

    cout << endl;
    cout << "                                                                             Hotel Management System\n" << endl;
    cout << "                                                                1. Display All Rooms          2. Display Available Rooms\n";
    cout << "                                                                3. Book a Room                4. Checkout\n";
    cout << "                                                                5. Get Invoice                6. Display All Customers\n";
    cout << "                                                                7. Search for customer        8. Edit Room details\n";
    cout << "                                                                              9. Exit The system \n" << endl;
    cout << "                                                                                " << COLOR_YELLOW << "Enter your choice: " << COLOR_RESET;
}

// Animated loading bar shown after a successful login (Sleep = milliseconds on Windows)
void startUp() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n  Account is loading. Please do not press any keys\n";
    cout << "[" "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "]0%";
    Sleep(1000);

    system("cls");
    cout << "\n  Account is loading. Please do not press any keys\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90" "] 25%";
    Sleep(1000);

    system("cls");
    cout << "\n  Account is loading. Please do not press any keys\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90" "] 50%";
    Sleep(1000);

    system("cls");
    cout << "\n  Account is loading. Please do not press any keys\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90" "] 75%";
    Sleep(1000);

    system("cls");
    cout << "\n  Account is loading. Please do not press any keys\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0" "] 100%\n";
    cout << COLOR_GREEN << "Login successful! Welcome." << COLOR_RESET << endl;
    Sleep(1000);
}

// Animated exit bar
void exitProgram() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    cout << "\n  Exiting... please don't press any key\n";
    cout << "[" "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "]0%";
    Sleep(1000);

    system("cls");
    cout << "\n  Exiting... please don't press any key\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90" "] 25%";
    Sleep(1000);

    system("cls");
    cout << "\n  Exiting... please don't press any key\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90" "] 50%";
    Sleep(1000);

    system("cls");
    cout << "\n  Exiting... please don't press any key\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90"
             "\xE2\x98\x90\xE2\x98\x90\xE2\x98\x90" "] 75%";
    Sleep(1000);

    system("cls");
    cout << "\n  Exiting.. please don't press any key\n";
    cout << "[" "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0"
             "\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0\xe2\x96\xa0" "] 100%\n";
    Sleep(1000);
    cout << "\n\n  " << COLOR_GREEN << "Exiting the system successfully." << COLOR_RESET << endl;
    exit(EXIT_SUCCESS);
}

// =============================================================
// AUTHENTICATION
// =============================================================

// Prompts for username/password; allows 3 attempts before exit
void login() {
    cout << "                                   -----------------Welcome to Hotel System Management-----------------" << endl << endl;

    // Hardcoded credentials (change these before deployment)
    const string ADMIN_USER = "HAVEN";
    const string ADMIN_PASS = "321";

    string username, password;
    int attempts = 3;

    cout << "                                      Please Log in using hotel account. You have three attempts." << endl;

    do {
        cout << "                                                      " << COLOR_YELLOW << "Enter username for hotel: " << COLOR_RESET;
        cin >> username;
        cout << "                                                      " << COLOR_YELLOW << "Enter password: " << COLOR_RESET;
        cin >> password;

        if (username == ADMIN_USER && ADMIN_PASS == password) {
            startUp();
            return;
        }

        attempts--;
        if (attempts > 0) {
            cout << "                                                      "
                 << COLOR_RED << "Incorrect username or password. You have "
                 << attempts << " attempt(s) remaining." << COLOR_RESET << endl;
        } else {
            cout << "                                                         "
                 << COLOR_RED << "Too many failed attempts. Exiting program." << COLOR_RESET << endl;
            exit(0);
        }
    } while (true);
}

// =============================================================
// ROOM OPERATIONS
// =============================================================

void displayAllRooms(const vector<Room>& rooms) {
    system("cls");
    cout << left
         << setw(12) << "Room Type"
         << setw(15) << "Number of Beds"
         << setw(10) << "Rent"
         << setw(12) << "Room Number"
         << setw(12) << "Status" << "\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& room : rooms) room.displayRoom();
    waitForUser();
}

void displayAvailableRooms(const vector<Room>& rooms) {
    system("cls");
    cout << left
         << setw(12) << "Room Type"
         << setw(15) << "Number of Beds"
         << setw(10) << "Rent"
         << setw(12) << "Room Number"
         << setw(12) << "Status" << "\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& room : rooms) if (room.isAvailable) room.displayRoom();
    waitForUser();
}

void bookRoom(vector<Room>& rooms, vector<Booking>& bookings) {
    system("cls");
    int roomNum;
    do {
        cout << "Enter Room Number: ";
        cin >> roomNum;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
        } else break;
    } while (true);

    for (auto& room : rooms) {
        if (room.roomNumber == roomNum && room.isAvailable) {
            string name, contact, date;
            int persons;

            do {
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);
                if (!isAlphabetic(name))
                    cout << COLOR_RED << "Error: Name can only contain letters and spaces. Please try again." << COLOR_RESET << endl;
            } while (!isAlphabetic(name));

            do {
                cout << "Enter Number of people: ";
                cin >> persons;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
                } else break;
            } while (true);

            cout << "Enter Customer Contact Number: ";
            cin.ignore();
            getline(cin, contact);

            cout << "Enter Booking Date (DD/MM/YYYY): ";
            getline(cin, date);
            while (!isValidDate(date)) {
                cout << COLOR_RED << "Error: Invalid date format. Please enter a valid date (DD/MM/YYYY)" << COLOR_RESET << endl;
                cout << "Enter Booking Date (DD/MM/YYYY): ";
                getline(cin, date);
            }

            bookings.push_back(Booking(name, roomNum, persons, contact, date));
            room.isAvailable = false;
            cout << COLOR_GREEN << "Room booked successfully!" << COLOR_RESET;
            waitForUser();
            return;
        }
    }
    cout << COLOR_RED << "Room not available or does not exist.\n" << COLOR_RESET;
    waitForUser();
}

void checkout(vector<Room>& rooms, vector<Booking>& bookings) {
    system("cls");
    int roomNum;
    do {
        cout << "Enter Room Number: ";
        cin >> roomNum;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
        } else break;
    } while (true);

    for (auto& room : rooms) {
        if (room.roomNumber == roomNum && !room.isAvailable) {
            room.isAvailable = true;
            for (auto it = bookings.begin(); it != bookings.end(); ++it) {
                if (it->roomNumber == roomNum) { bookings.erase(it); break; }
            }
            cout << COLOR_GREEN << "Checkout successful!\n" << COLOR_RESET;
            waitForUser();
            return;
        }
    }
    cout << COLOR_RED << "Room not found or already available.\n" << COLOR_RESET;
    waitForUser();
}

void editRoom(vector<Room>& rooms) {
    system("cls");
    int roomNum;
    do {
        cout << "Enter the room number you want to edit: ";
        cin >> roomNum;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
        } else break;
    } while (true);

    for (auto& room : rooms) {
        if (room.roomNumber == roomNum) {
            int choice;
            do {
                cout << "\nEditing Room " << room.roomNumber << " (" << room.roomType << ")\n"
                     << "------------------------------------\n"
                     << "1. Update Price\n2. Update Number of Beds\n3. Change Availability\n4. Cancel\n"
                     << "Choose an option: ";
                cin >> choice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << COLOR_RED << "Invalid choice, please enter a number." << COLOR_RESET;
                    continue;
                }
                switch (choice) {
                    case 1:
                        endl(cout);
                        cout << "Current price: Rm" << room.price << "\n";
                        do {
                            cout << "Enter new price: Rm";
                            cin >> room.price;
                            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
                            } else break;
                        } while (true);
                        cout << COLOR_GREEN << "Price updated successfully!\n" << COLOR_RESET;
                        break;
                    case 2:
                        endl(cout);
                        cout << "Current number of beds: " << room.numberOfBeds << "\n";
                        do {
                            cout << "Enter new number of beds: ";
                            cin >> room.numberOfBeds;
                            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
                            } else break;
                        } while (true);
                        cout << COLOR_GREEN << "Number of beds updated successfully!\n" << COLOR_RESET;
                        break;
                    case 3: {
                        cout << "Room is currently " << (room.isAvailable ? "Available" : "Not Available") << ".\n"
                             << "Enter 1 for Available, 0 for Not Available: ";
                        int status; cin >> status;
                        room.isAvailable = (status == 1);
                        cout << COLOR_GREEN << "Availability updated successfully!\n" << COLOR_RESET;
                        break;
                    }
                    case 4:
                        cout << "No changes made.";
                        waitForUser();
                        return;
                    default:
                        system("cls");
                        cout << COLOR_RED << "Invalid choice. Please try again." << COLOR_RESET;
                }
            } while (choice < 1 || choice > 4);
            waitForUser();
            return;
        }
    }
    cout << COLOR_RED << "Sorry, no room found with this number." << COLOR_RESET << endl;
    waitForUser();
}

// =============================================================
// CUSTOMER / INVOICE OPERATIONS
// =============================================================

void searchCustomer(const vector<Booking>& bookings, const vector<Room>& rooms) {
    system("cls");
    string name;
    cout << "Enter Customer Name to search: ";
    cin.ignore();
    getline(cin, name);

    for (const auto& booking : bookings) {
        if (booking.customerName == name) {
            string roomType;
            for (const auto& room : rooms)
                if (room.roomNumber == booking.roomNumber) { roomType = room.roomType; break; }

            cout << "\nCustomer Information:\n"
                 << "Name:           " << booking.customerName         << "\n"
                 << "Room Number:    " << booking.roomNumber            << "\n"
                 << "Room Type:      " << roomType                      << "\n"
                 << "Booking Date:   " << booking.bookingDate           << "\n"
                 << "Contact Number: " << booking.customerContactNumber << "\n";
            waitForUser();
            return;
        }
    }
    cout << COLOR_RED << "No booking found for the given customer name." << COLOR_RESET;
    waitForUser();
}

void getInvoice(const vector<Booking>& bookings, const vector<Room>& rooms, int& invoiceCounter) {
    system("cls");
    string name;
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, name);

    for (const auto& booking : bookings) {
        if (booking.customerName == name) {
            string email, roomType;
            int    duration;
            double price     = 0.0;
            int    roomNumber = booking.roomNumber;

            cout << "Enter Email: ";
            getline(cin, email);

            for (const auto& room : rooms)
                if (room.roomNumber == roomNumber) { roomType = room.roomType; price = room.price; break; }

            do {
                cout << "Enter Duration of Stay (in days): ";
                cin >> duration;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << COLOR_RED << "Invalid, please enter a number." << COLOR_RESET << endl;
                } else break;
            } while (true);

            Invoice invoice(++invoiceCounter, booking.customerName, email,
                            booking.customerContactNumber, roomType, roomNumber,
                            duration, price * duration);
            invoice.displayInvoice();
            waitForUser();
            return;
        }
    }
    cout << COLOR_RED << "No booking found for the given name.\n" << COLOR_RESET;
    waitForUser();
}

void displayAllCustomers(const vector<Booking>& bookings, const vector<Room>& rooms) {
    system("cls");
    cout << left
         << setw(20) << "Customer Name"
         << setw(15) << "Room Number"
         << setw(15) << "Room Type"
         << setw(15) << "Booking Date" << "\n";
    cout << "------------------------------------------------------------\n";

    for (const auto& booking : bookings) {
        string roomType;
        for (const auto& room : rooms)
            if (room.roomNumber == booking.roomNumber) { roomType = room.roomType; break; }

        cout << left
             << setw(20) << booking.customerName
             << setw(15) << booking.roomNumber
             << setw(15) << roomType
             << setw(15) << booking.bookingDate << "\n";
    }
    waitForUser();
}

// =============================================================
// FILE PERSISTENCE
// =============================================================

void saveRoomsToFile(const vector<Room>& rooms) {
    ofstream file("data/rooms.txt");
    if (file.is_open()) {
        for (const auto& room : rooms)
            file << room.roomNumber << "," << room.price << ","
                 << room.numberOfBeds << "," << room.roomType << ","
                 << room.isAvailable << "\n";
        file.close();
    } else {
        cout << COLOR_RED << "Error: Unable to save rooms data" << COLOR_RESET << "\n";
    }
}

void loadRoomsFromFile(vector<Room>& rooms) {
    ifstream file("data/rooms.txt");
    string line;
    rooms.clear();
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> tokens;
            while (getline(ss, item, ',')) tokens.push_back(item);
            if (tokens.size() == 5) {
                Room room(stoi(tokens[0]), stod(tokens[1]), stoi(tokens[2]), tokens[3]);
                room.isAvailable = (tokens[4] == "1");
                rooms.push_back(room);
            }
        }
        file.close();
    }
}

void saveBookingsToFile(const vector<Booking>& bookings) {
    ofstream file("data/bookings.txt");
    if (file.is_open()) {
        for (const auto& booking : bookings)
            file << booking.customerName << "," << booking.roomNumber << ","
                 << booking.numberOfPersons << "," << booking.customerContactNumber << ","
                 << booking.bookingDate << "\n";
        file.close();
    } else {
        cout << COLOR_RED << "Error: Unable to save bookings data" << COLOR_RESET << "\n";
    }
}

void loadBookingsFromFile(vector<Booking>& bookings) {
    ifstream file("data/bookings.txt");
    string line;
    bookings.clear();
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> tokens;
            while (getline(ss, item, ',')) tokens.push_back(item);
            if (tokens.size() == 5)
                bookings.push_back(Booking(tokens[0], stoi(tokens[1]), stoi(tokens[2]), tokens[3], tokens[4]));
        }
        file.close();
    }
}
