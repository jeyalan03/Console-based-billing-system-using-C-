# Console-based Billing System using C++

A text-based application designed to manage billing operations for a restaurant or cafe. This system enables administrators to manage the menu and allows customers to place orders, generating a detailed bill including tax calculations.

## Features

- **Administrator Module**:
  - Add new items to the menu (Item Number, Name, Price).
  - Data persistence ensures menu items are saved to `menu.txt`.

- **Buyer Module**:
  - View the complete menu.
  - Place orders by selecting item numbers and specifying quantities.
  - Automatic calculation of:
    - Subtotal
    - Tax (5%)
    - Total Amount Due
  - Generates a printed bill on the console.
  - Appends order details to `order.txt` for record-keeping.

- **Data Persistence**:
  - **Menu**: Loaded from and saved to `menu.txt`.
  - **Orders**: All transaction details are recorded in `order.txt`.

## Getting Started

### Prerequisites
- A C++ Compiler (e.g., GCC/MinGW).
- [Code::Blocks IDE](http://www.codeblocks.org/) (optional, but project files are included).

### How to Compile and Run

#### Option 1: Using Command Line
1. Open a terminal or command prompt.
2. Navigate to the project directory.
3. Compile the source code:
   ```bash
   g++ main.cpp -o billing_system
   ```
4. Run the executable:
   - Windows: `billing_system.exe`
   - Linux/Mac: `./billing_system`

#### Option 2: Using Code::Blocks
1. Open `Billing Sysytem.cbp` in Code::Blocks.
2. Click on **Build and Run** (or press F9).

## Usage

1. **Launch the Application**: You will be presented with a main menu.
2. **Select User Type**:
   - **1. Administrator**: Enter this mode to add new items to the food menu.
   - **2. Buyer**: Enter this mode to view the menu and place an order.
3. **Placing an Order**:
   - Enter the Item Number of the desired food.
   - Enter the Quantity.
   - Choose to add more items or finish.
   - The system will display the final bill on the screen and save the record.



## Screenshots

### Main Menu
![Main Menu](screenshots/Main%20menu.png)

### Admin: Add New Item
![Admin Add Food](screenshots/Admin%20add%20new%20foods.png)

### Buyer: View Menu
![Buyer View Menu](screenshots/Buyer%20view%20foods%20list.png)

### Buyer: Place Order
![Buyer Order](screenshots/Buyer%20order%20foods.png)


## File Structure
- `main.cpp`: The main source code file.
- `menu.txt`: Database file storing menu items (ItemNo Name| Price).
- `order.txt`: Log file for all generated orders.
- `Billing Sysytem.cbp`: Project file for Code::Blocks.

## Project Link
[GitHub Repository](https://github.com/jeyalan03/Console-based-billing-system-using-C-.git)
