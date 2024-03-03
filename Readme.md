
# CS253 : Car Rental System Documentation
This document outlines the data structure and functionalities of a Car Rental System implemented in C++ using object oriented programming paradigms. The code is present in [main.cpp](/main.cpp).

## Data Files
The system utilizes six CSV files to store car and user information:

### 1.all_cars_data.csv:
####Columns: 
model_of_car (string): Name of the car model.
rent_per_day (float): Daily rental fee.
car_condition (string): Condition of the car (3 types - Bad, Good, Excellent).
reg_no (string): Registration number of the car (unique identifier of  a car).
is_rented (boolean): Indicates whether the car is currently rented (1) or available (0).

### 2.user_info.csv:
Columns:
name (string): User's full name.
id (string): Unique user ID (unique identifier of  a user).
password (string): User's password for login.
type_of_user (string): User type ( 1 ="Customer", 2 = "Employee", 3 = "Manager").
user_record (string): Users record based on his maintenance of rented cars.

### 3.Customers.csv: 
Columns:
name (string): Customer's full name .
id (string): Unique customer ID .
pwd (string): Customer's password .
record (string): Customers record based on his maintenance of rented cars.

### 4.Employee.csv:
Columns:
Employee (string): Employee name.
Employee_id (string): Unique employee ID.
password (string): Employee's password for login.
record (string): Employee record based on his maintenance of rented cars.

### 5.Manager.csv:
Columns:
Manager_name (string): Manager's name.
Manager_id (string): Unique manager ID.
pwd (string): Manager's password for login.
record (string): Additional manager-specific data.

### 6.rented_cars_data.csv:
Columns:
user id(string): user id is the id of the user who issued the car.
name of car :  Model name of the rented car.
reg_no (string): Registration number of the rented car (unique identifier of  a car).
timestamp: timestamp stores the time when the user issued which will help us in calculating the total price to be payed by users.



To run the system, type the following commands in the console:
``` 
g++ main.cpp -o main
.\main
```
The system will run on the console. The data modified throughout the program run will be reflected in the csv files.<br>
<br>
