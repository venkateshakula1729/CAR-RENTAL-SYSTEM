# **CS 253 — Car Rental System**
This document outlines the data structure and functionalities of a Car Rental System implemented in C++ using object oriented programming paradigms. The code implementation is present in [main.cpp](/main.cpp).

---

# **📁 Data Files Overview**

The system manages data using **six CSV files**, each responsible for storing information about cars or users.

---

## **1. `all_cars_data.csv`**

**Columns**

* **model_of_car** *(string)* — Car model name
* **rent_per_day** *(float)* — Daily rental cost
* **car_condition** *(string)* — Condition of the car (**Bad / Good / Excellent**)
* **reg_no** *(string)* — Unique registration number
* **is_rented** *(boolean)* — `1` if rented, `0` if available

---

## **2. `user_info.csv`**

**Columns**

* **name** *(string)* — Full user name
* **id** *(string)* — Unique user ID
* **password** *(string)* — Login password
* **type_of_user** *(string)* — `1 = Customer`, `2 = Employee`, `3 = Manager`
* **user_record** *(string)* — Record of user's car maintenance behavior

---

## **3. `Customers.csv`**

**Columns**

* **name** *(string)*
* **id** *(string)*
* **pwd** *(string)*
* **record** *(string)* — Car maintenance history

---

## **4. `Employee.csv`**

**Columns**

* **Employee** *(string)* — Employee name
* **Employee_id** *(string)* — Unique ID
* **password** *(string)*
* **record** *(string)* — Maintenance/handling record

---

## **5. `Manager.csv`**

**Columns**

* **Manager_name** *(string)*
* **Manager_id** *(string)*
* **pwd** *(string)*
* **record** *(string)* — Additional manager-specific information

---

## **6. `rented_cars_data.csv`**

**Columns**

* **user_id** *(string)* — ID of the user who rented the car
* **name_of_car** *(string)* — Rented car model
* **reg_no** *(string)* — Unique registration number
* **timestamp** — Time of issue (used for billing calculations)

---

# **▶️ Running the System**

### **1. Download**

Download the ZIP file of the repository and extract it.

### **2. Compile**

Run the following command in your terminal:

```bash
g++ main.cpp -o main
```

### **3. Execute**

```bash
./main
```

All changes made during program execution will automatically update the corresponding **CSV files**.

---
