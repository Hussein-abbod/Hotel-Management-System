# 🏨 Hotel Management System

A console-based **Hotel Management System** written in **C++17**, featuring room booking, customer management, invoice generation, and file persistence.

---

## ✨ Features

| Feature | Description |
|---|---|
| 🔐 Login System | Secure login with 3-attempt lockout |
| 🛏️ Room Management | View all rooms / available rooms, edit price, beds, availability |
| 📋 Booking | Book a room with customer details and date validation |
| 🚪 Checkout | Check out a customer and free the room |
| 🧾 Invoice | Auto-generate numbered invoices with stay duration & total cost |
| 👥 Customer List | View all current guests in a formatted table |
| 🔍 Search | Search for a customer booking by name |
| 💾 Persistence | All data saved to `data/rooms.txt` and `data/bookings.txt` |

---

## 🗂️ Project Structure

```
hotel-management-system/
├── include/
│   ├── colors.h      ← ANSI colour constants
│   ├── Room.h        ← Room class declaration
│   ├── Booking.h     ← Booking class declaration
│   ├── Invoice.h     ← Invoice class declaration
│   └── Utils.h       ← All free function declarations
├── src/
│   ├── main.cpp      ← Entry point (main)
│   ├── Room.cpp      ← Room implementation
│   ├── Booking.cpp   ← Booking implementation
│   ├── Invoice.cpp   ← Invoice implementation
│   └── Utils.cpp     ← All system functions
├── data/             ← Auto-created at runtime
│   ├── rooms.txt
│   └── bookings.txt
├── .gitignore
├── Makefile
└── README.md
```

---

## 🔨 Build Instructions

### Prerequisites
- **g++** with C++17 support (MinGW on Windows, or GCC on Linux/macOS)
- **make** utility

### Build

```bash
make
```

This will:
1. Create the `obj/` and `data/` directories automatically
2. Compile all source files in `src/`
3. Output the `hotel_management.exe` binary

### Run

```bash
./hotel_management
```

### Clean build artefacts

```bash
make clean
```

### Manual compile (without make)

```bash
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o hotel_management
```

---

## 🔑 Default Login Credentials

> [!WARNING]  
> Change these before any real deployment. Credentials are stored in `src/Utils.cpp` inside the `login()` function.

| Field | Value |
|---|---|
| Username | `HAVEN` |
| Password | `321` |

---

## 🏠 Default Rooms

The system seeds 10 rooms on first run if no data file exists:

| Room No. | Type | Beds | Price/Night |
|---|---|---|---|
| 101, 104, 107, 110 | Standard | 2 | RM 100 |
| 102, 105, 108 | Deluxe | 3 | RM 150 |
| 103, 106, 109 | Suite | 4 | RM 200 |

---

## 🎨 Colour System

All console colours are defined as constants in `include/colors.h`:

| Constant | Colour | Usage |
|---|---|---|
| `COLOR_GREEN` | 🟢 Green | Success messages, available rooms |
| `COLOR_RED` | 🔴 Red | Error messages, unavailable rooms |
| `COLOR_YELLOW` | 🟡 Yellow | Input prompts |
| `COLOR_BOLD_RED` | 🔴 Bold Red | Critical errors |
| `COLOR_RESET` | — | Reset terminal colour |

---

## 📝 Notes

- This project is **Windows-only** due to use of `<windows.h>` and `system("cls")`.
- Data files are stored in the `data/` folder and are excluded from version control via `.gitignore`.

---

## 👤 Author

Hussein Abbod
