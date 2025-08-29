#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <limits>

// --- Struct Definitions ---
// NOTE: Replaced C-style char arrays with std::string for safety and convenience.
struct Car {
    std::string plate_num;
    std::string brand;
    std::string model;
    float capacity;
    std::string colour;
    float rate_per_hour;
    float rate_per_half;
    float rate_per_day;
    std::string transmission;
};

struct Customer {
    int id;
    std::string name;
    std::string phone;
    std::string ic;
    std::string address;
};

struct UserPassword {
    int id;
    std::string password;
};


// --- Utility Functions ---

// Sets cursor position in the console (Windows specific)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Clears the console screen
void clear_screen() {
    system("cls");
}

// Pauses execution until a key is pressed
void press_any_key_to_continue() {
    std::cout << "\n\n\t | \t\t\tPress any key to continue...";
    _getch();
}

// Gets the current date and time as a string
std::string current_date_time() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%d/%m/%Y TIME: %X", &tstruct);
    return buf;
}

// Displays a border on the screen
void draw_border() {
    clear_screen();
    for (int i = 10; i < 140; i++) {
        gotoxy(i, 10); std::cout << "=";
        gotoxy(i, 58); std::cout << "=";
    }
    for (int i = 10; i < 58; i++) {
        gotoxy(10, i); std::cout << "|";
        gotoxy(140, i); std::cout << "|";
    }
}

// Displays a loading animation
void display_loading_bar(const std::string& message) {
    draw_border();
    int timer = 5 + rand() % 15;
    gotoxy(65, 34);
    std::cout << message;
    gotoxy(60, 36);
    for (int r = 1; r <= timer; r++) {
        for (long long q = 0; q <= 10000000; q++); // Slow down
        std::cout << (char)177;
    }
    Sleep(100);
    clear_screen();
}

// Displays ASCII art from a file
void display_art(const std::string& filename) {
    draw_border();
    gotoxy(0, 20);

    std::ifstream ifs(filename);
    if (ifs) {
        std::string line;
        while (std::getline(ifs, line)) {
            std::cout << line << std::endl;
        }
        gotoxy(20, 15);
        std::cout << "\t\t\t\tDATE: " << current_date_time() << std::endl;
    }
    ifs.close();
}


// --- Main Application Class ---

class RentalSystem {
private:
    std::vector<Car> all_cars;
    std::vector<Car> available_cars;
    std::vector<Customer> customers;
    std::vector<UserPassword> users;

    // --- Private Helper Methods ---

    // Safely reads an integer from input
    int get_numeric_input() {
        int choice;
        while (!(std::cin >> choice)) {
            std::cout << "\n\t | \t\tInvalid input. Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline
        return choice;
    }

    // Securely reads a password from input
    std::string get_password_input() {
        std::string password;
        char ch;
        ch = _getch();
        while (ch != 13) { // 13 is the ASCII for Enter
            if (ch == '\b') { // Backspace
                if (!password.empty()) {
                    password.pop_back();
                    std::cout << "\b \b";
                }
            } else {
                password.push_back(ch);
                std::cout << '*';
            }
            ch = _getch();
        }
        std::cout << std::endl;
        return password;
    }
    
    // Calculates rental price
    int calculate_rate(int hours, const Car& car) {
        int days = hours / 24;
        int half_days = (hours % 24) / 12;
        int remaining_hours = (hours % 24) % 12;
        return (days * car.rate_per_day) + (half_days * car.rate_per_half) + (remaining_hours * car.rate_per_hour);
    }
    
    // Displays a list of cars
    void display_car_list(const std::vector<Car>& car_list) {
        std::cout << "\t  |  Plate Number\tBrand\t Model\t\tCapacity   Colour\t Rate/Hr   Rate/12Hr   Rate/24Hr   Transmission" << std::endl;
        std::cout << "\t  |  ======================================================================================================================================" << std::endl;
        for (const auto& car : car_list) {
            printf("\t  |  %-15s\t%-8s\t %-15s %-10.1f %-10s\t %-10.2f %-10.2f %-10.2f %-10s\n",
                   car.plate_num.c_str(), car.brand.c_str(), car.model.c_str(), car.capacity,
                   car.colour.c_str(), car.rate_per_hour, car.rate_per_half, car.rate_per_day,
                   car.transmission.c_str());
        }
    }


public:
    RentalSystem() {
        // Seed random number generator
        srand(time(0));
    }

    // --- Data Loading and Saving ---

    void load_all_data() {
        load_cars();
        load_available_cars();
        load_customers();
        load_users();
    }

    void load_cars() {
        std::ifstream file("car rental.txt");
        all_cars.clear();
        Car temp_car;
        while (file >> temp_car.plate_num >> temp_car.brand >> temp_car.model >> temp_car.capacity >> temp_car.colour >> temp_car.rate_per_hour >> temp_car.rate_per_half >> temp_car.rate_per_day >> temp_car.transmission) {
            all_cars.push_back(temp_car);
        }
        file.close();
    }
    
    void load_available_cars() {
        std::ifstream file("available.txt");
        available_cars.clear();
        Car temp_car;
        while (file >> temp_car.plate_num >> temp_car.brand >> temp_car.model >> temp_car.capacity >> temp_car.colour >> temp_car.rate_per_hour >> temp_car.rate_per_half >> temp_car.rate_per_day >> temp_car.transmission) {
            available_cars.push_back(temp_car);
        }
        file.close();
    }
    
    void load_customers() {
        std::ifstream file("Customer.txt");
        customers.clear();
        Customer temp_cust;
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            size_t pos1 = line.find(';');
            size_t pos2 = line.find(';', pos1 + 1);
            size_t pos3 = line.find(';', pos2 + 1);
            size_t pos4 = line.find(';', pos3 + 1);
            
            temp_cust.id = std::stoi(line.substr(0, pos1));
            temp_cust.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            temp_cust.phone = line.substr(pos2 + 1, pos3 - pos2 - 1);
            temp_cust.ic = line.substr(pos3 + 1, pos4 - pos3 - 1);
            temp_cust.address = line.substr(pos4 + 1);
            customers.push_back(temp_cust);
        }
        file.close();
    }

    void load_users() {
        std::ifstream file("UserPass.txt");
        users.clear();
        UserPassword temp_user;
        while(file >> temp_user.id >> temp_user.password) {
            users.push_back(temp_user);
        }
        file.close();
    }
    
    void save_data_to_file(const std::string& filename, const std::vector<Car>& car_list) {
        std::ofstream file(filename);
        for(size_t i = 0; i < car_list.size(); ++i) {
            file << car_list[i].plate_num << " " << car_list[i].brand << " " << car_list[i].model << " "
                 << car_list[i].capacity << " " << car_list[i].colour << " " << car_list[i].rate_per_hour << " "
                 << car_list[i].rate_per_half << " " << car_list[i].rate_per_day << " " << car_list[i].transmission
                 << (i == car_list.size() - 1 ? "" : "\n");
        }
        file.close();
    }
    
    // --- Menus ---

    void main_menu() {
        int choice;
        do {
            display_art("art.txt");
            std::cout << "\n\n\t |\t\t\t\t\t\t\t  1. ADMIN";
            std::cout << "\n\t |\t\t\t\t\t\t\t  2. USER";
            std::cout << "\n\t |\t\t\t\t\t\t\t  3. TERMS & CONDITIONS";
            std::cout << "\n\t |\t\t\t\t\t\t\t  4. EXIT" << std::endl;
            std::cout << "\n\n\t |\t\t\t\t\t\t\tINPUT : ";
            choice = get_numeric_input();
            clear_screen();

            switch (choice) {
                case 1: admin_login(); break;
                case 2: user_menu(); break;
                case 3: show_terms_and_conditions(); break;
                case 4: 
                    display_art("exit art.txt");
                    Sleep(2000);
                    break;
                default:
                    std::cout << "\n\t | \t\tInvalid choice. Please try again.";
                    press_any_key_to_continue();
            }
        } while (choice != 4);
    }
    
    void admin_login() {
        draw_border();
        gotoxy(40, 20);
        std::cout << "\n\n\n\n\t | \t\t\tEnter Password: ";
        std::string password = get_password_input();

        bool logged_in = false;
        if (password == "a") { // Default/master password
            logged_in = true;
        } else {
            for(const auto& user : users) {
                if (user.password == password) {
                    logged_in = true;
                    break;
                }
            }
        }
        
        if (logged_in) {
            display_loading_bar("LOGGING IN...");
            admin_menu();
        } else {
            std::cout << "\n\t | \t\t\tWrong Password... Returning to Main Menu.";
            Sleep(2000);
            clear_screen();
        }
    }
    
    void admin_menu() {
         int choice;
        do {
            display_art("art.txt");
            std::cout << "\n\t |\t\t\t\t\t\t\t  1. ADD NEW ADMIN";
            std::cout << "\n\t |\t\t\t\t\t\t\t  2. SHOW ALL CAR DATA";
            std::cout << "\n\t |\t\t\t\t\t\t\t  3. ADD NEW CAR";
            std::cout << "\n\t |\t\t\t\t\t\t\t  4. DELETE CAR";
            std::cout << "\n\t |\t\t\t\t\t\t\t  5. RESET AVAILABLE CARS";
            std::cout << "\n\t |\t\t\t\t\t\t\t  6. LOG OFF" << std::endl;
            std::cout << "\n\n\t |\t\t\t\t\t\t\tINPUT : ";
            choice = get_numeric_input();

            clear_screen();
            switch(choice) {
                case 1: add_new_user(); break;
                case 2: show_all_car_data(); break;
                case 3: add_new_car(); break;
                case 4: delete_car(); break;
                case 5: reset_available_cars(); break;
                case 6: display_loading_bar("LOGGING OFF..."); break;
                default: std::cout << "\n\t | \t\tInvalid choice."; press_any_key_to_continue();
            }
        } while(choice != 6);
    }
    
    void user_menu() {
        int choice;
        display_art("art.txt");
        std::cout << "\n\t |\t\t\t\t\t\t\t  1. NEW CUSTOMER";
        std::cout << "\n\t |\t\t\t\t\t\t\t  2. EXISTING CUSTOMER";
        std::cout << "\n\t |\t\t\t\t\t\t\t  3. MAIN MENU" << std::endl;
        std::cout << "\n\n\t |\t\t\t\t\t\t\tINPUT : ";
        choice = get_numeric_input();
        clear_screen();
        
        switch(choice) {
            case 1: new_customer_rental(); break;
            case 2: existing_customer_rental(); break;
            case 3: break;
            default: std::cout << "\n\t | \t\tInvalid choice."; press_any_key_to_continue();
        }
    }

    // --- Admin Functions ---
    void add_new_user() {
        draw_border();
        gotoxy(40, 20);
        UserPassword new_user;
        new_user.id = users.empty() ? 1 : users.back().id + 1;
        
        std::cout << "\n\n\n\n\t | \t\t\tNew Admin ID (Default): " << new_user.id;
        std::cout << "\n\t | \t\t\tEnter New Password: ";
        new_user.password = get_password_input();
        users.push_back(new_user);

        std::ofstream ofs("UserPass.txt", std::ios::app);
        ofs << "\n" << new_user.id << " " << new_user.password;
        ofs.close();
        
        std::cout << "\n\t | \t\t\tNew admin added successfully!";
        press_any_key_to_continue();
    }
    
    void show_all_car_data() {
        display_art("art.txt");
        display_car_list(all_cars);
        press_any_key_to_continue();
    }

    void add_new_car() {
        display_art("art.txt");
        Car new_car;
        std::cout << "\n\t | \t\tPlease enter the car data below:" << std::endl;
        std::cout << "\n\t | \t\tPlate Number: "; std::getline(std::cin, new_car.plate_num);
        std::cout << "\t | \t\tBrand: "; std::getline(std::cin, new_car.brand);
        std::cout << "\t | \t\tModel: "; std::getline(std::cin, new_car.model);
        std::cout << "\t | \t\tCapacity: "; std::cin >> new_car.capacity; std::cin.ignore();
        std::cout << "\t | \t\tColour: "; std::getline(std::cin, new_car.colour);
        std::cout << "\t | \t\tRate Per Hour: "; std::cin >> new_car.rate_per_hour; std::cin.ignore();
        std::cout << "\t | \t\tRate Per 12 Hours: "; std::cin >> new_car.rate_per_half; std::cin.ignore();
        std::cout << "\t | \t\tRate Per 24 Hours: "; std::cin >> new_car.rate_per_day; std::cin.ignore();
        std::cout << "\t | \t\tTransmission (A/M): "; std::getline(std::cin, new_car.transmission);

        all_cars.push_back(new_car);
        save_data_to_file("car rental.txt", all_cars);
        
        std::cout << "\n\t | \t\tCar added successfully!";
        press_any_key_to_continue();
        load_cars(); // Refresh data
    }

    void delete_car() {
        display_art("art.txt");
        display_car_list(all_cars);
        std::string plate_to_delete;
        std::cout << "\n\n\t | \t\tEnter the plate number of the car to delete: ";
        std::getline(std::cin, plate_to_delete);
        
        std::vector<Car> updated_cars;
        bool found = false;
        for(const auto& car : all_cars) {
            if (car.plate_num != plate_to_delete) {
                updated_cars.push_back(car);
            } else {
                found = true;
            }
        }
        
        if (found) {
            all_cars = updated_cars;
            save_data_to_file("car rental.txt", all_cars);
            std::cout << "\n\t | \t\tCar deleted successfully!";
        } else {
            std::cout << "\n\t | \t\tCar not found.";
        }
        press_any_key_to_continue();
        load_cars(); // Refresh data
    }
    
    void reset_available_cars() {
        available_cars = all_cars;
        save_data_to_file("available.txt", available_cars);
        display_loading_bar("UPDATING DATABASE...");
        std::cout << "\n\t | \t\tAvailable car list has been reset to full stock.";
        press_any_key_to_continue();
    }
    
    // --- User Functions ---
    void new_customer_rental() {
        display_art("art.txt");
        Customer new_cust;
        new_cust.id = customers.empty() ? 1001 : customers.back().id + 1;

        std::cout << "\n\t | \t\tPlease enter your details:" << std::endl;
        std::cout << "\n\t | \t\tYour Customer ID will be: " << new_cust.id << std::endl;
        std::cout << "\t | \t\tName: "; std::getline(std::cin, new_cust.name);
        std::cout << "\t | \t\tPhone Number: "; std::getline(std::cin, new_cust.phone);
        std::cout << "\t | \t\tIC: "; std::getline(std::cin, new_cust.ic);
        std::cout << "\t | \t\tAddress: "; std::getline(std::cin, new_cust.address);
        
        customers.push_back(new_cust);

        std::ofstream ofs("Customer.txt", std::ios::app);
        ofs << (customers.size() == 1 ? "" : "\n") << new_cust.id << ";" << new_cust.name << ";" << new_cust.phone << ";" << new_cust.ic << ";" << new_cust.address;
        ofs.close();
        
        std::cout << "\n\t | \t\tCustomer added successfully!";
        press_any_key_to_continue();
        
        // Proceed to rental process
        rent_a_car(new_cust);
    }
    
    void existing_customer_rental() {
        display_art("art.txt");
        std::cout << "\n\t | \t\tPlease enter your Customer ID: ";
        int user_id = get_numeric_input();
        
        bool found = false;
        for(const auto& cust : customers) {
            if (cust.id == user_id) {
                std::cout << "\n\t | \t\tWelcome back, " << cust.name << "!";
                press_any_key_to_continue();
                rent_a_car(cust);
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "\n\t | \t\tCustomer ID not found.";
            press_any_key_to_continue();
        }
    }

    void rent_a_car(const Customer& cust) {
        clear_screen();
        display_art("art.txt");
        std::cout << "\n\t | \t\tAvailable Cars for Rent:" << std::endl;
        display_car_list(available_cars);
        
        std::string plate_to_rent;
        std::cout << "\n\n\t | \t\tEnter the plate number of the car you want to rent: ";
        std::getline(std::cin, plate_to_rent);

        Car selected_car;
        bool car_found = false;
        std::vector<Car> updated_available_cars;

        for (const auto& car : available_cars) {
            if (car.plate_num == plate_to_rent) {
                selected_car = car;
                car_found = true;
            } else {
                updated_available_cars.push_back(car);
            }
        }

        if (!car_found) {
            std::cout << "\n\t | \t\tInvalid plate number or car is not available.";
            press_any_key_to_continue();
            return;
        }

        std::cout << "\t | \t\tEnter hours of rent: ";
        int hours = get_numeric_input();
        
        int total_cost = calculate_rate(hours, selected_car);
        std::cout << "\n\t | \t\tTotal rental price for " << hours << " hours is: RM " << total_cost;

        // Update available cars file
        available_cars = updated_available_cars;
        save_data_to_file("available.txt", available_cars);

        // Log the transaction
        std::ofstream log("Log.txt", std::ios::app);
        log << "\n==========================================================";
        log << "\nDATE: " << current_date_time();
        log << "\nCUSTOMER: " << cust.name << " (ID: " << cust.id << ")";
        log << "\nCAR: " << selected_car.plate_num << " (" << selected_car.brand << " " << selected_car.model << ")";
        log << "\nHOURS: " << hours;
        log << "\nPAYMENT: RM " << total_cost;
        log.close();

        press_any_key_to_continue();
    }


    // --- Other Functions ---
    void show_terms_and_conditions() {
        display_art("art.txt");
        std::cout << "\n\t |\t\t\t1. MINIMUM RENT TIME IS 3 HOURS";
        std::cout << "\n\t |\t\t\t2. RENT AT YOUR OWN RISK";
        std::cout << "\n\t |\t\t\t3. IN CASE OF AN ACCIDENT, ALL COSTS ARE BORNE BY THE DRIVER";
        std::cout << "\n\t |\t\t\t4. PLEASE PREPARE THE FOLLOWING ITEMS:";
        std::cout << "\n\t |\t\t\t     - COPY OF IC, LICENSE";
        std::cout << "\n\t |\t\t\t     - DEPOSIT (BASED ON CAR TYPE)";
        std::cout << "\n\t |\t\t\t5. ADDITIONAL CHARGES WILL APPLY FOR LATE RETURNS";
        std::cout << "\n\t |\t\t\t6. DRIVE SAFELY!";
        press_any_key_to_continue();
    }
    
    void run() {
        display_art("welcome.txt");
        Sleep(1000);
        display_loading_bar("BOOTING UP...");
        load_all_data();
        main_menu();
    }
};


int main() {
    // This Windows-specific function can be used to attempt to set fullscreen.
    // May not work on all systems.
    // keybd_event(VK_MENU, 0x38, 0, 0);
    // keybd_event(VK_RETURN, 0x1c, 0, 0);
    // keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    // keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

    RentalSystem app;
    app.run();

    return 0;
}