#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <ctime>

using namespace std;

// --- Utility Functions ---
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// --- Classes ---

class MenuItem {
public:
    int itemNo;
    string itemName;
    float price;

    MenuItem(int id, string name, float p) : itemNo(id), itemName(name), price(p) {}
};

class OrderItem {
public:
    int itemNo;
    string itemName;
    int quantity;
    float totalPrice;

    OrderItem(int id, string name, int qty, float total) 
        : itemNo(id), itemName(name), quantity(qty), totalPrice(total) {}
};

class MenuManager {
private:
    vector<MenuItem> menu;
    const string filename = "menu.txt";

public:
    MenuManager() {
        initializeMenu();
        loadMenu();
    }

    void initializeMenu() {
        ifstream file(filename);
        if (!file || file.peek() == EOF) {
            ofstream outFile(filename);
            outFile << "111 Plain Egg| 1.45\n";
            outFile << "112 Bacon and Egg| 2.45\n";
            outFile << "113 Muffin| 0.99\n";
            outFile << "114 French Toast| 1.99\n";
            outFile << "115 Fruit Basket| 2.49\n";
            outFile << "116 Cereal| 0.69\n";
            outFile << "117 Coffee| 0.50\n";
            outFile << "118 Tea| 0.75\n";
            outFile.close();
        }
        file.close();
    }

    void loadMenu() {
        menu.clear();
        ifstream file(filename);
        if (!file) {
            cout << "No menu file found. Starting with empty menu." << endl;
            return;
        }
        int id;
        string name;
        float price;
        while (file >> id) {
            file.ignore(); // ignore space
            getline(file, name, '|');
            file >> price;
            menu.push_back(MenuItem(id, name, price));
        }
        file.close();
    }

    void saveMenu() {
        ofstream file(filename, ios::trunc); // Overwrite the file
        for (const auto& item : menu) {
            file << item.itemNo << " " << item.itemName << "| " << fixed << setprecision(2) << item.price << endl;
        }
        file.close();
    }

    bool isDuplicateItemNo(int itemNo) {
        for (const auto& item : menu) {
            if (item.itemNo == itemNo) return true;
        }
        return false;
    }

    void addItem() {
        int id;
        cout << "Enter item number: ";
        cin >> id;
        if (cin.fail()) {
            cout << "Invalid input. Item number must be an integer." << endl;
            clearInputBuffer();
            return;
        }
        if (isDuplicateItemNo(id)) {
            cout << "Error: Item number already exists in the menu." << endl;
            return;
        }
        clearInputBuffer();
        
        cout << "Enter item name: ";
        string name;
        getline(cin, name);
        if (name.empty()) {
            cout << "Error: Item name cannot be empty." << endl;
            return;
        }
        
        cout << "Enter item price: ";
        float price;
        cin >> price;
        if (cin.fail() || price <= 0) {
            cout << "Error: Item price must be a positive number." << endl;
            clearInputBuffer();
            return;
        }
        
        menu.push_back(MenuItem(id, name, price));
        saveMenu();
        cout << "Item added successfully!" << endl;
    }

    void updateItem() {
        int id;
        cout << "Enter item number to update: ";
        cin >> id;
        if (cin.fail()) {
            cout << "Invalid input. Item number must be an integer." << endl;
            clearInputBuffer();
            return;
        }
        
        for (auto& item : menu) {
            if (item.itemNo == id) {
                cout << "Current price: $" << fixed << setprecision(2) << item.price << endl;
                cout << "Enter new price: ";
                float newPrice;
                cin >> newPrice;
                if (cin.fail() || newPrice <= 0) {
                    cout << "Invalid price. Must be a positive number." << endl;
                    clearInputBuffer();
                    return;
                }
                item.price = newPrice;
                saveMenu();
                cout << "Price updated successfully!" << endl;
                return;
            }
        }
        cout << "Item not found in the menu." << endl;
    }

    void deleteItem() {
        int id;
        cout << "Enter item number to delete: ";
        cin >> id;
        if (cin.fail()) {
            cout << "Invalid input. Item number must be an integer." << endl;
            clearInputBuffer();
            return;
        }
        
        for (auto it = menu.begin(); it != menu.end(); ++it) {
            if (it->itemNo == id) {
                cout << "Deleting " << it->itemName << " from the menu..." << endl;
                menu.erase(it);
                saveMenu();
                cout << "Item deleted successfully!" << endl;
                return;
            }
        }
        cout << "Item not found in the menu." << endl;
    }

    void showMenu() {
        if (menu.empty()) {
            cout << "\nMenu is empty. Please add items to the menu first." << endl;
            return;
        }
        cout << "\n********** Welcome to Meal Hut **********" << endl;
        cout << "******** Breakfast Billing Menu ********\n" << endl;
        cout << setw(10) << left << "Item No" << setw(20) << left << "Menu Item" << setw(10) << "Price" << endl;
        cout << "------------------------------------------" << endl;
        for (const auto& item : menu) {
            cout << setw(10) << left << item.itemNo
                 << setw(20) << left << item.itemName
                 << "$" << fixed << setprecision(2) << item.price << endl;
        }
    }

    MenuItem* getItem(int id) {
        for (auto& item : menu) {
            if (item.itemNo == id) return &item;
        }
        return nullptr;
    }

    bool isEmpty() const {
        return menu.empty();
    }
};

class OrderManager {
private:
    vector<OrderItem> order;
    
    int generateOrderId() {
        srand(time(0));
        return (rand() % 9000) + 1000; // Returns random 4 digit number
    }

public:
    void processOrder(MenuManager& menuManager) {
        if (menuManager.isEmpty()) {
            cout << "\nThe menu is currently empty. Please ask an administrator to add items." << endl;
            return;
        }
        
        order.clear(); // Reset order for new customer
        char anotherOrder = 'Y';
        while (toupper(anotherOrder) == 'Y') {
            int itemNo, quantity;
            cout << "\nEnter the item number you wish to order: ";
            cin >> itemNo;
            
            if (cin.fail()) {
                cout << "Invalid input. Item number must be an integer." << endl;
                clearInputBuffer();
                continue;
            }
            
            MenuItem* item = menuManager.getItem(itemNo);
            if (item == nullptr) {
                cout << "Invalid item number. Please try again." << endl;
                continue;
            }
            
            cout << "Enter the quantity: ";
            cin >> quantity;
            if (cin.fail() || quantity <= 0) {
                cout << "Invalid quantity. Please enter a positive number." << endl;
                clearInputBuffer();
                continue;
            }
            
            order.push_back(OrderItem(item->itemNo, item->itemName, quantity, quantity * item->price));
            
            cout << "Would you like to order another item? (Y/N): ";
            cin >> anotherOrder;
            if (cin.fail()) {
                clearInputBuffer();
                anotherOrder = 'N'; // Safe default
            }
        }
        
        generateBill();
    }

    void generateBill() {
        if (order.empty()) return;
        
        float subtotal = 0.0;
        int orderId = generateOrderId();
        
        time_t now = time(0);
        char* dt = ctime(&now); // Formats time easily
        
        // --- Output to Console --- //
        cout << "\n==================================================" << endl;
        cout << "                 MEAL HUT RECEIPT                  " << endl;
        cout << "==================================================" << endl;
        cout << "Order ID: #" << orderId << endl;
        cout << "Date: " << dt;
        cout << "--------------------------------------------------" << endl;
        cout << setw(10) << left << "Item No" << setw(20) << left << "Menu Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        cout << "--------------------------------------------------" << endl;
        
        for (const auto& item : order) {
            cout << setw(10) << left << item.itemNo
                 << setw(20) << left << item.itemName
                 << setw(10) << left << item.quantity
                 << "$" << fixed << setprecision(2) << item.totalPrice << endl;
            subtotal += item.totalPrice;
        }
        
        float tax = subtotal * 0.05;
        float total = subtotal + tax;
        
        cout << "--------------------------------------------------" << endl;
        cout << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
        cout << "Tax (5%): $" << fixed << setprecision(2) << tax << endl;
        cout << "Total Amount Due: $" << fixed << setprecision(2) << total << endl;
        cout << "==================================================\n" << endl;
        
        // --- Save to File --- //
        ofstream orderFile("order.txt", ios::app); // Append mode
        orderFile << "\n==================================================" << endl;
        orderFile << "                 MEAL HUT RECEIPT                  " << endl;
        orderFile << "==================================================" << endl;
        orderFile << "Order ID: #" << orderId << endl;
        orderFile << "Date: " << dt;
        orderFile << "--------------------------------------------------" << endl;
        orderFile << setw(10) << left << "Item No" << setw(20) << left << "Menu Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        orderFile << "--------------------------------------------------" << endl;
        for (const auto& item : order) {
            orderFile << setw(10) << left << item.itemNo
                      << setw(20) << left << item.itemName
                      << setw(10) << left << item.quantity
                      << "$" << fixed << setprecision(2) << item.totalPrice << endl;
        }
        orderFile << "--------------------------------------------------" << endl;
        orderFile << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
        orderFile << "Tax (5%): $" << fixed << setprecision(2) << tax << endl;
        orderFile << "Total Amount Due: $" << fixed << setprecision(2) << total << endl;
        orderFile << "==================================================\n" << endl;
        orderFile.close();
    }
};

class AdminSystem {
private:
    string adminPassword = "admin";
public:
    bool authenticate() {
        string inputPassword;
        cout << "Enter Administrator Password: ";
        cin >> inputPassword;
        if (inputPassword == adminPassword) {
            return true;
        }
        cout << "Incorrect Password! Access Denied." << endl;
        return false;
    }

    void adminMenu(MenuManager& menuManager) {
        if (!authenticate()) return;
        
        int choice;
        do {
            cout << "\n********** Administrator Dashboard **********" << endl;
            cout << "1. View All Menu Items" << endl;
            cout << "2. Add New Menu Item" << endl;
            cout << "3. Update Menu Item Price" << endl;
            cout << "4. Delete Menu Item" << endl;
            cout << "5. Logout (Return to Main Menu)" << endl;
            cout << "Please enter your choice: ";
            cin >> choice;
            
            if (cin.fail()) {
                cout << "Invalid input. Please enter a number from 1 to 5." << endl;
                clearInputBuffer();
                continue;
            }
            
            switch (choice) {
                case 1:
                    menuManager.showMenu();
                    break;
                case 2:
                    menuManager.addItem();
                    break;
                case 3:
                    menuManager.updateItem();
                    break;
                case 4:
                    menuManager.deleteItem();
                    break;
                case 5:
                    cout << "Logging out of Administrator Dashboard..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }
};

class BillingSystem {
private:
    MenuManager menuManager;
    OrderManager orderManager;
    AdminSystem adminSystem;

public:
    void start() {
        int choice;
        do {
            cout << "\n********** Welcome to Meal Hut **********" << endl;
            cout << "1. Administrator Login" << endl;
            cout << "2. Customer (Self-Service Kiosk)" << endl;
            cout << "3. Exit System" << endl;
            cout << "Please select a role: ";
            cin >> choice;
            
            if (cin.fail()) {
                cout << "Invalid input. Please enter a valid option (1-3)." << endl;
                clearInputBuffer();
                continue;
            }
            
            switch (choice) {
                case 1:
                    adminSystem.adminMenu(menuManager);
                    break;
                case 2:
                    menuManager.showMenu();
                    orderManager.processOrder(menuManager);
                    break;
                case 3:
                    cout << "Shutting down the Meal Hut System. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }
};

int main() {
    BillingSystem app;
    app.start();
    return 0;
}
