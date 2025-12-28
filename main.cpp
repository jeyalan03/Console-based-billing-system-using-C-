#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_ITEMS = 10; // Maximum number of menu items.

struct MenuItem {
    int itemNo;
    string itemName;
    float price;
};

struct OrderItem {
    int itemNo;
    string itemName;
    int quantity;
    float totalPrice;
};

MenuItem menu[MAX_ITEMS];
int menuCount = 0; // To track the number of menu items
OrderItem order[MAX_ITEMS];
int orderCount = 0; // To track the number of ordered items

// For admin-added items
MenuItem adminAddedItems[MAX_ITEMS];
int adminAddedCount = 0; // To track the number of admin-added items

// Predefined food items
MenuItem predefinedMenu[] = {
    {111, "Plain Egg", 1.45},
    {112, "Bacon and Egg", 2.45},
    {113, "Muffin", 0.99},
    {114, "French Toast", 1.99},
    {115, "Fruit Basket", 2.49},
    {116, "Cereal", 0.69},
    {117, "Coffee", 0.50},
    {118, "Tea", 0.75}
};

// initialize predefined menu if not already in the file,
void initializeMenuFile() {
    ifstream file("menu.txt");
    if (!file || file.peek() == EOF) { // File doesn't exist or is empty
        ofstream outFile("menu.txt");  //If the file doesn't exist, it creates one.
        for (auto &item : predefinedMenu) {
            outFile << item.itemNo << " " << item.itemName << "| " << item.price << endl;
        }
        outFile.close();
    }
    file.close();
}

// load menu from file
void loadMenuFromFile() {
    ifstream file("menu.txt");    //reads, if not open print a message.
    if (!file) {
        cout << "No menu file found. Starting with an empty menu." << endl;
        return;
    }

    menuCount = 0;
    while (file >> menu[menuCount].itemNo) {
        file.ignore(); // Ignore the space, Reads the itemNo into the menu array's current index.
        getline(file, menu[menuCount].itemName, '|');
        file >> menu[menuCount].price;
        menuCount++;
    }
    file.close();
}

// save menu to file
void saveMenuToFile() {
    ofstream file("menu.txt", ios::trunc); // Overwrite the file, clear.
    for (int i = 0; i < menuCount; i++) {
        file << menu[i].itemNo << " " << menu[i].itemName << "| " << menu[i].price << endl;
    }
    file.close();
}

//check if an item number already exists, duplication detection. true.
bool isDuplicateItemNo(int itemNo) {
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].itemNo == itemNo) {
            return true;
        }
    }
    return false;
}

// clear input buffer,enter letters when num is expected.
void clearInputBuffer() {
    cin.clear();
    cin.ignore(1000, '\n'); // Clear up to 1000 characters or until a newline
}

// display the menu
void showMenu() {
    if (menuCount == 0) {
        cout << "\nMenu is empty. Please add items to the menu first." << endl;
        return;
    }

    cout << "\n********** Welcome to Meal Hut **********" << endl;
    cout << "******** Breakfast Billing System ********\n" << endl;
    cout << setw(10) << left << "Item No" << setw(20) << left << "Menu Item" << setw(10) << "Price" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < menuCount; i++) {
        cout << setw(10) << menu[i].itemNo
             << setw(20) << menu[i].itemName
             << "$" << fixed << setprecision(2) << menu[i].price << endl;
    }
}

// add a new menu item
void addMenuItem() {
    if (menuCount >= MAX_ITEMS) {
        cout << "Menu is full! Cannot add more items." << endl;
        return;
    }

    MenuItem newItem;
    cout << "Enter item number: ";
    cin >> newItem.itemNo;

    // Input validation
    if (cin.fail()) {
        cout << "Invalid input. Item number must be an integer." << endl;
        clearInputBuffer();
        return;
    }

    // Check for duplicate item number
    if (isDuplicateItemNo(newItem.itemNo)) {
        cout << "Error: Item number already exists in the menu." << endl;
        return;
    }

    clearInputBuffer();
    cout << "Enter item name: ";
    getline(cin, newItem.itemName);

    if (newItem.itemName.empty()) {
        cout << "Error: Item name cannot be empty." << endl;
        return;
    }

    cout << "Enter item price: ";
    cin >> newItem.price;

    if (cin.fail() || newItem.price <= 0) {
        cout << "Error: Item price must be a positive number." << endl;
        clearInputBuffer();
        return;
    }

    menu[menuCount++] = newItem; // Add to the array
    adminAddedItems[adminAddedCount++] = newItem; // Track admin-added items
    saveMenuToFile(); // Save menu to file

    cout << "Item added successfully!" << endl;
}

// process an order
void processOrder() {
    if (menuCount == 0) {
        cout << "\nThe menu is currently empty. Please add items to the menu first." << endl;
        return;
    }

    orderCount = 0; // Reset order count
    char anotherOrder = 'Y';
    while (toupper(anotherOrder) == 'Y') {
        int itemNo, quantity;
        cout << "\nEnter the item number you wish to order: ";
        cin >> itemNo;

        if (cin.fail()) {
            cout << "Invalid input. Item number must be an integer." << endl;
            clearInputBuffer();
            continue;  //skips the rest of the loop using continue.
        }

        bool found = false;
        for (int i = 0; i < menuCount; i++) {
            if (menu[i].itemNo == itemNo) {
                found = true;
                cout << "Enter the quantity: ";
                cin >> quantity;

                if (cin.fail() || quantity <= 0) {
                    cout << "Invalid quantity. Please enter a positive number." << endl;
                    clearInputBuffer();
                    continue;
                }

                order[orderCount].itemNo = menu[i].itemNo;
                order[orderCount].itemName = menu[i].itemName;
                order[orderCount].quantity = quantity;
                order[orderCount].totalPrice = quantity * menu[i].price;
                orderCount++;
                break;
            }
        }

        if (!found) {
            cout << "Invalid item number. Please try again." << endl;
            continue;
        }

        cout << "Would you like to order another item? (Y/N): ";
        cin >> anotherOrder;
        clearInputBuffer();
    }

    // Generate the bill
    float subtotal = 0.0;
    ofstream orderFile("order.txt", ios::app); // Append mode to save multiple orders

    orderFile << "\n********** Order Details **********" << endl;
    orderFile << setw(10) << left << "Item No" << setw(20) << left << "Menu Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    orderFile << "--------------------------------------------------" << endl;

    cout << "\n********** Your Order **********" << endl;
    cout << setw(10) << left << "Item No" << setw(20) << left << "Menu Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i < orderCount; i++) {
        cout << setw(10) << order[i].itemNo
             << setw(20) << order[i].itemName
             << setw(10) << order[i].quantity
             << "$" << fixed << setprecision(2) << order[i].totalPrice << endl;

        orderFile << setw(10) << order[i].itemNo
                  << setw(20) << order[i].itemName
                  << setw(10) << order[i].quantity
                  << "$" << fixed << setprecision(2) << order[i].totalPrice << endl;

        subtotal += order[i].totalPrice;
    }

    float tax = subtotal * 0.05;
    float total = subtotal + tax;

    cout << "--------------------------------------------------" << endl;
    cout << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    cout << "Tax (5%): $" << tax << endl;
    cout << "Total Amount Due: $" << total << endl;

    orderFile << "--------------------------------------------------" << endl;
    orderFile << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    orderFile << "Tax (5%): $" << tax << endl;
    orderFile << "Total Amount Due: $" << total << endl;
    orderFile << "*******************************\n" << endl;

    orderFile.close();
}

// Main menu
void mainMenu() {
    int choice;
    do {
        cout << "\n********** Welcome to Meal Hut **********" << endl;
        cout << "1. Administrator" << endl;
        cout << "2. Buyer" << endl;
        cout << "3. Exit" << endl;

        cout << "Please select: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid option." << endl;
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                int adminChoice;
                do {
                    cout << "\n********** Administrator Menu **********" << endl;
                    cout << "1. Add a product" << endl;
                    cout << "2. Back to main menu" << endl;
                    cout << "Please enter your choice: ";
                    cin >> adminChoice;

                    if (cin.fail()) {
                        cout << "Invalid input. Please enter a valid option." << endl;
                        clearInputBuffer();
                        continue;
                    }

                    switch (adminChoice) {
                        case 1:
                            addMenuItem();
                            break;
                        case 2:
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                    }
                } while (adminChoice != 2);
                break;
            }
            case 2:
                showMenu();
                processOrder();
                break;
            case 3:
                cout << "Thank you for using Meal Hut." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

// Main function
int main() {
    initializeMenuFile();
    loadMenuFromFile();
    mainMenu();
    return 0;
}
