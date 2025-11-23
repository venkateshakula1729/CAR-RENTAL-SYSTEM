# **CS 253 — Car Rental System**

# **Overview**

This project is a command-line **Car Rental System** developed as part of the **CS253** course for the 2023–24 (II) semester. The application is fully implemented in **C++**, using **file handling** to maintain a persistent CSV-based database. Through a simple terminal interface, users perform **CRUD operations** on cars, user accounts, and rental records, along with renting, returning, and fine-related workflows. The repository showcases a complete, functional implementation of core **object-oriented programming principles**, including class design, inheritance, and modular functionality.

---

# ** Running the System**

### **1. Clone/Download**

Clone this repository using the below command in terminal.

```bash
git clone https://github.com/venkateshakula1729/CAR-RENTAL-SYSTEM.git
```

### **2. Compile**

Run the following command in your terminal:

```bash
g++ main.cpp -o main
```

### **3. Execute**

Run the created executable file by running below code.

```bash
./main
```

All changes made during program execution will automatically update the corresponding **CSV files**.

---

# **📁 Database Files Overview**

This folder acts as the database and contains six comma-separated values files to store all user and car information.

---

**Database Folder:** 
**all_cars_data.csv:** This file contains information about all cars in the system. It includes the columns model_of_car, rent_per_day, car_condition, reg_no and is_rented.
**Users_info.csv:** This file stores general login information of all users. It contains name, id, password, type_of_user and user_record.
**Customers.csv:** This file contains information about customers. It includes name, id, pwd and record.
**Employee.csv:** This file contains information about employees. It includes Employee, Employee_id, password and record.
**Manager.csv:** This file stores manager details. It includes Manager_name, Manager_id, pwd and record.
**rented_cars_data.csv:** This file records all active rentals. It contains user_id, name_of_car, reg_no and timestamp to track when a car was issued.

---


# **Features**

### **Customer / Employee**

Users can **log in or register** using their name, ID, and password. Registration updates the CSV files; invalid login credentials bring errors.
After logging in, they can:

* **View all cars** with model, condition, rent, reg_no, and rental status.
* **View their rented cars**, along with issue dates.
* **Check availability** of a car by model name.
* **Rent cars** if their record score is sufficient and they haven't crossed their rental limits

  * Customers: max 10
  * Employees: max 15
    The system updates both `all_cars_data.csv` and `rented_cars_data.csv`.
* **Check dues**: fines are calculated from timestamp.

  * Customer: 10 free days, then ₹100/day
  * Employee: 20 free days, then ₹50/day
    Both pay rent cost; employees get discounted effective rent.
* **Return cars**: updates rental DB, frees the car, and updates user record based on late return + car condition.
* **Clear dues**: displays and clears total fine.
* **Logout** back to home menu.

---

### **Manager**

Manager logs in the same way, then can:

* **View all cars** with complete info.
* **View all users** and their record scores.
* **Add / update / delete users** (name, password, record).
* **Add / update / delete cars** (model, rent, condition).
* **Search users or cars** by ID or registration number.
* **See all cars rented by a specific user.**
* **See which user has a particular car.**
* **Show due date** for any rented car.
* Logout back to main screen.

---

# **How the System Works**

At startup, a welcome banner from `Hello.txt` is shown.
The user enters the main menu and chooses to **log in**, **register**, or **exit**.

Login credentials are checked against `Users_info.csv`.
Depending on the user type (Customer, Employee, Manager), the corresponding menu is shown.

All data operations use CSV files as a simple database:

1. The code **reads** a CSV into a global vector (`data`).
2. Applies updates (rent, return, delete, etc.).
3. **Writes** the modified vector back to the CSV.
4. Clears the vector and continues.

Renting stores a **timestamp** and all fines/due dates are computed from differences between current time and the stored timestamp.

Menus are recursive — after each action, the system returns to the same menu until the user logs out.

---


