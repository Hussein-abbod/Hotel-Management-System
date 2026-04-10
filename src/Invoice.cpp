#include "Invoice.h"
#include "colors.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ---------------------------------------------------------------
// Invoice — parameterised constructor
// ---------------------------------------------------------------
Invoice::Invoice(int invNum, string name, string mail, string contact,
                 string type, int roomNum, int duration, double price)
    : invoiceNumber(invNum), customerName(name), email(mail),
      contactNumber(contact), roomType(type), roomNumber(roomNum),
      durationOfStay(duration), totalPrice(price) {}

// ---------------------------------------------------------------
// displayInvoice — prints a formatted receipt to the console
// ---------------------------------------------------------------
void Invoice::displayInvoice() const {
    cout << "---------------------------------------------\n"
         << "| Invoice Number:    " << invoiceNumber   << "\n"
         << "|   Customer Name:   " << customerName    << "\n"
         << "|   Email:           " << email           << "\n"
         << "|   Contact Number:  " << contactNumber   << "\n"
         << "|   Room Type:       " << roomType        << "\n"
         << "|   Room Number:     " << roomNumber      << "\n"
         << "|   Duration:        " << durationOfStay  << " days\n"
         << "| Total Price:       Rm" << fixed << setprecision(2)
         << totalPrice << "\n"
         << "---------------------------------------------\n";
}
