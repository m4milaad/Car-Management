# Car Rental Management System

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

A feature-rich, console-based car rental management system developed in C++. This application provides a complete solution for managing a car rental business, with separate interfaces for administrators and users. It uses a text-based UI enhanced with ASCII art and direct console manipulation for a retro feel. All data is persistently stored in local text files.

---

## 🚀 Features

This system is divided into two main roles, each with a specific set of functionalities:

* **👑 Admin Panel (Password Protected)**
    * **Secure Login**: Access to the admin panel is protected by a password system.
    * **Car Fleet Management**:
        * **Add New Cars**: Easily add new vehicles to the rental fleet with detailed information (plate number, brand, model, color, rates, etc.).
        * **Delete Cars**: Remove vehicles from the fleet.
        * **View All Cars**: Display a comprehensive, formatted list of all cars in the system.
    * **System Management**:
        * **Add New Admins**: Create new administrator accounts with unique passwords.
        * **Reset Availability**: Instantly reset the list of available cars to the full fleet, useful for clearing all rental records.

* **👤 User Panel**
    * **Customer Profiles**:
        * **New Customer Registration**: A simple process for new customers to register their details.
        * **Existing Customer Login**: Registered customers can access the system using their unique Customer ID.
    * **Rental Process**:
        * **View Available Cars**: Users can see a list of all currently available cars for rent.
        * **Book a Car**: Select a car, specify the rental duration in hours, and get an instant price calculation.
    * **Transaction Logging**: Every rental transaction is automatically recorded in a `Log.txt` file with customer and car details, rental duration, total payment, and a timestamp.

* **🖥️ User Interface**
    * **ASCII Art**: Custom ASCII art for welcome screens, menus, and exit screens to enhance user experience.
    * **Console GUI**: Uses Windows-specific console functions (`gotoxy`) to create structured, screen-based menus and borders.

---

## 🛠️ Tech Stack

* **Language**: **C++**
* **Core Libraries**: `<iostream>`, `<fstream>`, `<string>`, `<vector>`
* **Platform-Specific APIs**:
    * **`<windows.h>`**: For console manipulation functions like `gotoxy` and `system("cls")`.
    * **`<conio.h>`**: For `_getch()`, used to create password fields and "press any key" prompts.
* **Data Persistence**: All data is stored and retrieved from local `.txt` files.

**Note**: This project is designed for the **Windows operating system** due to its reliance on Windows-specific libraries.

---

## ⚙️ Getting Started

Follow these instructions to get a local copy of the project up and running.

### Prerequisites

You will need a C++ compiler that supports the Windows API, such as:
* **MinGW-w64** (provides `g++`)
* **Microsoft Visual C++ (MSVC)** (included with Visual Studio)

### Installation & Compilation

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/m4milaad/Car_Management.git](https://github.com/m4milaad/Car_Management.git)
    ```

2.  **Navigate to the project directory:**
    ```sh
    cd Car_Management
    ```

3.  **Compile the source code:**
    Open a terminal (like Command Prompt or PowerShell) and use your compiler.

    * **Using g++ (MinGW):**
        ```sh
        g++ main.cpp -o car_rental_system -static-libgcc -static-libstdc++
        ```

    * **Using MSVC (from a Developer Command Prompt):**
        ```sh
        cl main.cpp
        ```

### Running the Application

After successful compilation, an executable file will be created. Run it from the terminal:
```sh
./car_rental_system.exe
```
or simply:
```sh
car_rental_system
```
The program requires several `.txt` files to be in the same directory to function correctly. Make sure you have them before running.

---

## 📂 Project File Structure

The project relies on several external files for its operation:

```
.
├── main.cpp              # All C++ source code for the application.
|
├── car rental.txt        # Database of all cars in the fleet.
├── available.txt         # Database of currently available cars for rent.
├── Customer.txt          # Database of all registered customers.
├── UserPass.txt          # Stores IDs and passwords for admin users.
├── Log.txt               # Records all rental transactions.
|
├── art.txt               # ASCII art for the main menu header.
├── welcome.txt           # ASCII art for the initial welcome screen.
└── exit art.txt          # ASCII art for the exit screen.
```

---

## 🤝 How to Contribute

Contributions are welcome! If you have suggestions for improving the project, please feel free to fork the repository and submit a pull request.

1.  **Fork the Project**
2.  **Create your Feature Branch** (`git checkout -b feature/NewFeature`)
3.  **Commit your Changes** (`git commit -m 'Add some NewFeature'`)
4.  **Push to the Branch** (`git push origin feature/NewFeature`)
5.  **Open a Pull Request**

---

## 📄 License

This project is distributed under the MIT License.

---

## 👨‍💻 Author

**Milad Ajaz Bhat** - [m4milaad](https://github.com/m4milaad)

Project Link: [https://github.com/m4milaad/Car_Management](https://github.com/m4milaad/Car_Management)