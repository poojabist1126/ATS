# Aotearoa Treasures Inventory Management System

Aotearoa Treasures Ltd. is a boutique retailer specializing in New Zealand-made handicrafts and souvenirs, with stores in Wellington CBD, Christchurch, and Auckland. This project delivers a centralized inventory management system to streamline operations, optimize staff scheduling, and provide a seamless experience for both administrators and customers.

## Table of Contents

- [Features](#features)
- [User Stories](#user-stories)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Data Files](#data-files)
- [User Journey](#user-journey)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- **Centralized Inventory Management**: View and manage inventory levels across all stores in real-time
- **Product Management**: Add, update, and delete products. View products by category and price
- **Low Stock Alerts**: Instantly view items with stock less than five to enable timely reordering
- **Purchasing System**: Users can select a store, browse available products, and make purchases, which update inventory in real-time
- **Staff Roster Management**: Admins can view and edit weekly staff rosters for each store
- **Employee Management**: Add, update, and delete employee records
- **Role-Based Access**: Secure admin login for accessing privileged features
- **CSV-Based Data Storage**: All data is stored in CSV files for portability and ease of editing

---

## User Stories

### Admin
- Add, update, and remove items
- View items with stock less than five for proactive reordering
- Update the weekly staff roster for each store
- Log in securely using a registered admin username
- View inventory levels across all stores

### User
- Select a store (Wellington, Christchurch, or Auckland) to browse inventory
- View products by category and price
- Make purchases from a selected store, updating inventory in real-time

---

## Project Structure

```
ATS/
├── ATS.cpp                # Main application entry point
├── employee.cpp/hpp       # Employee logic and data handling
├── customer.cpp/hpp       # Customer logic and data handling
├── admin_.cpp/hpp         # Admin logic and data handling
├── product.cpp/hpp        # Product logic and data handling
├── commonfunc.cpp/hpp     # Common utility functions (validation, etc.)
├── modcsv.cpp/hpp         # CSV read/write utilities
├── admin_details.csv      # Admin user data
├── employee_details.csv   # Employee records
├── customer_details.csv   # Customer records
├── product_details.csv    # Product records
├── order_details.csv      # Purchase records
├── employee_roster.csv    # Staff rosters
└── help.csv               # Help and documentation
```

## Getting Started

### Prerequisites

- C++14 compatible compiler (e.g., MSVC, GCC, Clang)
- CMake or Visual Studio 2022 for building

### Build Instructions

#### Using Visual Studio:
1. Open the project folder in Visual Studio 2022
2. Build the solution (`Ctrl+Shift+B`)

#### Using Command Line:
```bash
g++ -std=c++14 -o ATS ATS.cpp employee.cpp customer.cpp admin_.cpp product.cpp commonfunc.cpp modcsv.cpp
./ATS
```

---

## Usage

- **Admin Login**: Log in with your admin credentials to access inventory and staff management features
- **Product Management**: Add, update, or delete products. View products filtered by category or price
- **Low Stock View**: Instantly see products with less than five items in stock
- **Purchasing**: Users select a store, browse available products, and make purchases. Inventory updates automatically
- **Roster Management**: Admins can view and edit the weekly staff roster for each store
- **Employee Management**: Add, update, or delete employee records

---

## Data Files

| File | Description |
|------|-------------|
| `admin_details.csv` | Admin user data |
| `employee_details.csv` | Employee records |
| `customer_details.csv` | Customer records |
| `product_details.csv` | Product records |
| `order_details.csv` | Purchase records |
| `employee_roster.csv` | Staff rosters |
| `help.csv` | Help and documentation |

---

## User Journey

```mermaid
journey
    title Aotearoa Treasures User Journey
    section Start
      User opens application: 5: User
      User selects role (Admin/User): 4: User
    section Admin Actions
      Admin logs in: 4: Admin
      View inventory across stores: 4: Admin
      View low stock items: 3: Admin
      Add/update/delete products: 4: Admin
      Add/update/delete employees: 3: Admin
      Update staff roster: 3: Admin
    section User Actions
      Select store: 4: User
      Browse products by category/price: 4: User
      Make purchase: 5: User
      Inventory updates in real-time: 5: System
```

---

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

---

## License

This project is licensed under the terms specified in the LICENSE file.

---

**Aotearoa Treasures Ltd.** — *Empowering authentic Kiwi retail with smart inventory and staff management.*
