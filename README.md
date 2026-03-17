# Pro Console-based Billing System (OOP)

A high-quality, object-oriented C++ application designed for professional billing operations in restaurants or cafes. This system features a secure administrator dashboard, dynamic menu management, and a professional receipt generation system.

## 🚀 Key Features

- **Object-Oriented Architecture**: Built with modular classes (`MenuManager`, `OrderManager`, `AdminSystem`) for high scalability and clean code.
- **Secure Administrator Module**:
  - **Login Protection**: Secure access with a password system (Default: `admin`).
  - **Full CRUD Support**: Add, View, Update prices, and Delete menu items in real-time.
  - **Dynamic Scaling**: No limits on the number of menu items (uses `std::vector`).
- **Professional Customer Module**:
  - **Self-Service Kiosk Flow**: Clean interface for customers to browse and order.
  - **Automatic Calculations**: Real-time calculation of subtotal, 5% tax, and final amount.
- **Advanced Receipt System**:
  - **Unique Transaction IDs**: Every order generates a unique 4-digit order number.
  - **Timestamps**: Automatic date and time logging for every sale.
  - **Dual Logging**: Receipts are printed to the console and saved to `order.txt` for record-keeping.
- **Data Persistence**:
  - **Menu**: Persistently stored in and loaded from `menu.txt`.
  - **History**: Full transaction logs maintained in `order.txt`.

## 🛠 Prerequisites

- A C++11 (or higher) compatible compiler (e.g., GCC/MinGW).
- [Code::Blocks IDE](http://www.codeblocks.org/) (Recommended).

## 🚀 Getting Started

### Option 1: Using Code::Blocks (Recommended)
1. Open `Billing Sysytem.cbp` in Code::Blocks.
2. Ensure `main.cpp` is included in the project.
3. Click **Build and Run** (F9).

### Option 2: Command Line
1. Compile the source:
   ```bash
   g++ main.cpp -o billing_system
   ```
2. Run the executable:
   - Windows: `./billing_system.exe`
   - Linux/Mac: `./billing_system`

## 📖 Usage

### Administrator Access
- Select **1. Administrator Login** from the main menu.
- **Password**: `admin`
- Use the dashboard to manage your menu items (Add, Update, Delete).

### Customer Ordering
- Select **2. Customer (Self-Service Kiosk)**.
- Browse the menu and enter the **Item Number** and **Quantity**.
- Complete the order to generate a professional receipt.

## 📸 Screenshots

### Main Menu
![Main Menu](Screenshots/Strating%20main%20page.png)

### Administrator Dashboard
![Admin Dashboard](Screenshots/Admin%20options%20(login%20after).png)

### Customer Menu
![Customer Menu](Screenshots/Customer%20section%20(foods%20list%20shows%20).png)

### Receipt Generation
![Receipt](Screenshots/Order%20food%20and%20get%20bill.png)

## 📂 File Structure
- `main.cpp`: The core Object-Oriented source code.
- `menu.txt`: Dynamic database for menu items.
- `order.txt`: Historical log of all finalized receipts.
- `Billing Sysytem.cbp`: Optimized project file for Code::Blocks.

---
Developed with ❤️ to provide a perfect billing solution.
