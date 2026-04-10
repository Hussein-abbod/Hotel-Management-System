#pragma once
#include <string>

using namespace std;

// =============================================================
// Invoice Class
// Represents a generated invoice for a completed hotel stay.
// =============================================================
class Invoice {
public:
    int    invoiceNumber;   // Auto-incremented unique invoice ID
    string customerName;    // Customer full name
    string email;           // Customer email address
    string contactNumber;   // Customer phone / contact
    string roomType;        // Room type booked
    int    roomNumber;      // Room number booked
    int    durationOfStay;  // Length of stay in days
    double totalPrice;      // Total charge (price/night × duration)

    // Construct an Invoice with all fields
    Invoice(int invNum, string name, string mail, string contact,
            string type, int roomNum, int duration, double price);

    // Print a formatted invoice receipt to the console
    void displayInvoice() const;
};
