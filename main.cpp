#include <bits/stdc++.h>
#include <chrono>
using namespace std;

/*------------------------------- Functions for file handling --------------------------------------*/

vector<vector<string>> data;

void readfile(string file_name)
{
    vector<string> line;
    string stream, word;
    fstream csv(file_name, ios::in);

    if (csv.is_open())
    {
        while (getline(csv, stream))
        {
            line.clear();
            stringstream str(stream);
            while (getline(str, word, ','))
                line.push_back(word);
            data.push_back(line);
        }
    }
}
void write(vector<vector<string>> data, string file_name)
{
    fstream csv(file_name, ios::out);
    for (auto a : data)
    {
        for (auto b : a)
        {
            csv << b;
            if (b != a.back())
                csv << ",";
        }
        csv << "\n";
    }
}
void append(vector<string> par, string fname)
{
    fstream fout(fname, ios::out | ios::app);
    for (auto x : par)
    {
        fout << x;
        if (x != par.back())
            fout << ",";
    }
    fout << "\n";
}

void printdata(const vector<vector<string>> &par)
{
    // Find the maximum width of any word in the data
    size_t max_width = 0;
    for (const auto &row : par)
    {
        for (const auto &word : row)
        {
            max_width = std::max(max_width, word.size());
        }
    }

    // Print header row with column dividers
    for (size_t i = 0; i < max_width + 2; ++i)
    {
        cout << "-";
    }
    cout << endl;

    // Print each row with consistent formatting
    int row_num = 1;
    for (const auto &row : par)
    {
        cout << std::setw(2) << row_num << " | ";
        for (const auto &word : row)
        {
            cout << std::left << std::setw(max_width) << word << " | ";
        }
        cout << endl;
        row_num++;
    }

    // Print footer row with column dividers
    for (size_t i = 0; i < max_width + 2; ++i)
    {
        cout << "-";
    }
    cout << endl;
}

void print_user_info(const vector<vector<string>> &par)
{
    // Find the maximum width of each column (excluding password)
    size_t max_widths[2] = {0, 0};
    for (const auto &row : par)
    {
        max_widths[0] = std::max(max_widths[0], row[0].size());
        max_widths[1] = std::max(max_widths[1], row[1].size());
    }

    // Print header row with column dividers
    for (size_t i = 0; i < max_widths[0] + 1 + max_widths[1] + 5; ++i)
    {
        cout << "-";
    }
    cout << endl;

    // Print column headers
    cout << std::left << std::setw(max_widths[0]) << "Username"
         << " | ";
    cout << std::left << std::setw(max_widths[1]) << "userid"
         << " | ";
    cout << "Type of user" << endl;

    // Print header row divider
    for (size_t i = 0; i < max_widths[0] + 1 + max_widths[1] + 5; ++i)
    {
        cout << "-";
    }
    cout << endl;

    // Print each row with consistent formatting
    for (const auto &row : par)
    {
        cout << std::left << std::setw(max_widths[0]) << row[0] << " | ";
        cout << std::left << std::setw(max_widths[1]) << row[1] << " | ";
        cout << std::left << std::setw(max_widths[3]) << row[3] << endl;
    }

    // Print footer row with column dividers
    for (size_t i = 0; i < max_widths[0] + 1 + max_widths[1] + 5; ++i)
    {
        cout << "-";
    }
    cout << endl;
}

/*---------------------------------------------------------------------------------------------------------*/

/*------------------------------- Declaring all the classes and their fields --------------------------------------*/
class Car
{
public:
    string model;
    string condition;
    string reg_no;
    int is_rented;
    void Rent_request(string id, string carname, string user_type);
    void Show_duedate(string reg_no);
    string get_car_condition(string reg_no);
    void Car_add(string id);
    void Car_update(string id);
    void Car_delete(string id);
    void Car_search(string id);
};

class User
{

private:
    string password;
    string userRecord;

public:
    string name;
    string id;
    vector<string> cars_rented;
    void display_menu();
    void login();
    void see_all_cars(string id);
    void see_rented_cars(string id);
    void logout();
    void rent_car(string id, string car_name, string type_user, string userRecord);
    string get_userRecord(string id);
    void update_userRecord(string id, string car_condition, string user_type);
    void return_car(string id, string reg_number);
    void check_available(string id, string car_name);
    int calc_fine(string id, string type_user);
    void clear_fine_amount(string id, string type_user);
    void User_add(string id);
    void User_update(string id);
    void User_delete(string id);
    void User_search(string id);
};

class Customer : public User
{
public:
    int Fine_amount;
    void display_Customer_menu(string id);
};

class Employee : public User
{
public:
    int Fine_amount;
    void display_Employee_menu(string id);
};

class Manager : public User
{
public:
    void display_manager_menu(string id);
    void see_all_users(string id);
    void see_all_cars(string id);
    void add_user(string id);
    void update_user(string id);
    void delete_user(string id);
    void Search_user(string id);
    void add_car(string id);
    void update_car(string id);
    void delete_car(string id);
    void Search_car(string reg_no);
    void see_rented_to_user(string id, string uid);
    void see_rented_car(string id, string reg_no);
};

/*------------------------------- End of declarations ------------------------------------------------------------*/

/*------------------------ login, registration and Display menus for different types of users--------------------*/

void User ::display_menu()
{
    char c;
    cout << "---------------------------------------------------------------------\n";
    cout << "\n\n\t\tWelcome to the IIT Kanpur's Garage!\n\n";
    cout << "1. Enter 1 to log in : \n";
    cout << "2. Enter 2 to register\n";
    cout << "3. Enter 3 to exit\n";
    cout << "---------------------------------------------------------------------\n";
    cin >> c;
    if (c == '1')
    { // logs in a user
        User u;
        u.login();
    }
    else if (c == '2')
    {
        cout << "Please enter the details of the new user : \n";
        string _name, _id, _password, _type, user_record;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter id (userid should be unique):  ";
        cin >> _id;
        cout << "Enter password : ";
        cin >> _password;
        cout << "Enter type of the user : 1 if Customer, 2 if Employee, 3 if Manager : \n";
        cout << "Enter your choice: ";
        cin >> _type;
        user_record = "100"; // initially 100 is the user record for all users

        if (_type == "1")
        {
            fstream fout("Customers.csv", ios::app);
            fout << name << "," << _id << "," << _password << "," << user_record << '\n';
            cout << "New user has been added.\n";
        }
        if (_type == "2")
        {
            fstream fout("Employee.csv", ios::app);
            fout << name << "," << _id << "," << _password << "," << user_record << '\n';
            cout << "New user has been added.\n";
        }
        if (_type == "3")
        {
            fstream fout("Manager.csv", ios::app);
            fout << name << "," << _id << "," << _password << "," << user_record << '\n';
            cout << "New user has been added.\n";
        }
        if (_type == "1" || "2" || "3")
        {
            fstream fout("Users_info.csv", ios::app);
            fout << name << "," << _id << "," << _password << "," << _type << "," << user_record << '\n';
        }
        User u;
        u.login();
    }
    else
    {
        cout << "Thanks for using the system !";
        exit(1);
    }
}

void User ::login()
{
    cout << "======================================================================";
    cout << "\n|                                                                    |";
    cout << "\n|                               LOGIN                                |";
    cout << "\n|                                                                    |";
    cout << "\n======================================================================";
    cout << endl;

    string id, password;
    cout << "Enter your id : ";
    cin >> id;
    cout << "Enter the password : ";
    cin >> password;
    vector<string> words_in_a_row;
    string line_in_csv, word;
    fstream file("Users_info.csv", ios::in);
    int count = 0;
    if (file.is_open())
    {
        while (getline(file, line_in_csv))
        {
            words_in_a_row.clear();
            stringstream str(line_in_csv);
            while (getline(str, word, ','))
                words_in_a_row.push_back(word);
            if (words_in_a_row[1] == id)
            {
                count = 1;
                if (words_in_a_row[2] == password)
                {
                    count++;
                    break;
                }
                else
                {
                    while (password != words_in_a_row[2])
                    {
                        cout << "You entered the wrong password. Enter 1 to reenter the password and 2 to exit\n";
                        char c;
                        cin >> c;
                        if (c == '1')
                        {
                            cout << "Enter the password : ";
                            cin >> password;
                            if (password == words_in_a_row[2])
                                count++;
                        }
                        else if (c == '2')
                        {
                            cout << "Exiting...";
                            return;
                        }
                        else
                        {
                            cout << "Please enter a valid input.\n";
                        }
                    }
                    if (count == 2)
                        break;
                }
            }
            if (count == 2)
                break;
        }
        if (count == 0)
        {
            cout << "User not found\n";
            User u;
            u.display_menu();
        }
        if (count == 2)
        {

            Customer s;
            Employee p;
            Manager l;

            if (words_in_a_row[3] == "1")
            {
                s.display_Customer_menu(words_in_a_row[1]);
            }
            else if (words_in_a_row[3] == "2")
            {
                p.display_Employee_menu(words_in_a_row[1]);
            }
            else
            {
                l.display_manager_menu(words_in_a_row[1]);
            }
        }
    }
}
void Customer ::display_Customer_menu(string id)
{

    cout << "---------------------------------------------------------------------\n";
    cout << "\nYou have been logged in as Customer\n";
    cout << "Enter 1 to view all the cars\n";
    cout << "Enter 2 to view cars rented by you\n";
    cout << "Enter 3 to check if a car is available for rent or not\n";
    cout << "Enter 4 to view the fine\n";
    cout << "Enter 5 to rent a car\n";
    cout << "Enter 6 to return a car\n";
    cout << "Enter 7 to clear your fine\n";
    cout << "Enter l to logout\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Enter your choice: ";
    char c;
    cin >> c;
    string car_name, reg_no;
    Customer customer;
    Car C;
    switch (c)
    {
    case '1':
        customer.see_all_cars(id);
        customer.display_Customer_menu(id);
        break;
    case '2':
        customer.see_rented_cars(id);
        customer.display_Customer_menu(id);
        break;
    case '3':
        cout << "Enter the name of the car you want to check : ";
        cin.ignore();
        getline(cin, car_name);
        customer.check_available(id, car_name);
        customer.display_Customer_menu(id);
        break;
    case '4':
        customer.calc_fine(id, "1");
        customer.display_Customer_menu(id);
        break;
    case '5':
        cout << "Enter the name of the car you want to rent : ";
        cin.ignore();
        getline(cin, car_name);
        C.Rent_request(id, car_name, "1");
        customer.display_Customer_menu(id);
        break;
    case '6':
        cout << "Enter the reg_no code of the car you want to return : ";
        cin >> reg_no;
        customer.return_car(id, reg_no);
        customer.display_Customer_menu(id);
        break;
    case '7':
        customer.clear_fine_amount(id, "1");
        customer.display_Customer_menu(id);
        break;
    case 'd':
        cout << "Enter the registration number of the Car : ";
        cin >> reg_no;
        C.Show_duedate(reg_no);
        customer.display_Customer_menu(id);
        break;
    case 'l':
        logout();
        break;
    case 'e':
        exit(1);
        break;
    default:
        cout << "Invalid choice. Retry!" << endl;
        customer.display_Customer_menu(id);
    }
}
void Employee ::display_Employee_menu(string id)
{
    cout << "---------------------------------------------------------------------\n";
    cout << "\nYou have been logged in as Employee\n";
    cout << "Enter 1 to see all the cars\n";
    cout << "Enter 2 to view cars rented by you\n";
    cout << "Enter 3 to check if a car is available for rented or not\n";
    cout << "Enter 4 to view the fine\n";
    cout << "Enter 5 to rent a car\n";
    cout << "Enter 6 to return a car\n";
    cout << "Enter 7 to clear your fine\n";
    cout << "Enter d to view the due date of a car\n";
    cout << "Enter l to logout\n";
    cout << "Enter e to exit\n";
    cout << "---------------------------------------------------------------------\n";
    char c;
    cin >> c;
    string car_name, reg_no;
    Employee Ep;
    Car x;
    switch (c)
    {
    case '1':
        Ep.see_all_cars(id);
        Ep.display_Employee_menu(id);
        break;
    case '2':
        Ep.see_rented_cars(id);
        Ep.display_Employee_menu(id);
        break;
    case '3':
        cout << "Enter the name of the car you want to check : ";
        cin >> car_name;
        Ep.check_available(id, car_name);
        Ep.display_Employee_menu(id);
        break;
    case '4':
        Ep.calc_fine(id, "2");
        Ep.display_Employee_menu(id);
        break;
    case '5':
        cout << "Enter the name of the car you want to rent: ";
        cin >> car_name;
        Ep.rent_car(id, car_name, "2", get_userRecord(id));
        Ep.display_Employee_menu(id);
        break;
    case '6':
        cout << "Enter the reg_no code of the car you want to return : ";
        cin >> reg_no;
        Ep.return_car(id, reg_no);
        Ep.display_Employee_menu(id);
        break;
    case '7':
        Ep.clear_fine_amount(id, "2");
        Ep.display_Employee_menu(id);
        break;
    case 'd':
        cout << "Enter the registration number of the Car : ";
        cin >> reg_no;
        x.Show_duedate(reg_no);
        Ep.display_Employee_menu(id);
        break;
    case 'l':
        logout();
        break;
    case 'e':
        exit(1);
        break;
    default:
        cout << "Invalid choice. Retry!" << endl;
        Ep.display_Employee_menu(id);
    }
}

void Manager ::display_manager_menu(string id)
{
    cout << "---------------------------------------------------------------------\n";
    cout << "\nWelcome ! You are logged in as Manager.\n\n";
    cout << "Enter 1 to add a user\n";
    cout << "Enter 2 to update a user\n";
    cout << "Enter 3 to delete a user\n";
    cout << "Enter 4 to add a Car\n";
    cout << "Enter 5 to update a Car\n";
    cout << "Enter 6 to delete a Car\n";
    cout << "Enter 7 to view all Cars rented to a particular user\n";
    cout << "Enter 8 to view which Car is rented to which user\n";
    cout << "Enter 9 to view all users\n";
    cout << "Enter 0 to view all Cars\n";
    cout << "Enter s to search a particular user\n";
    cout << "Enter v to search a particular car\n";
    cout << "Enter d to show due date of a Car\n";
    cout << "Enter l to logout\n";
    cout << "Enter e to exit\n";
    cout << "---------------------------------------------------------------------\n";
    char c;
    cin >> c;
    Manager M;
    Car C;
    User U;
    string reg_no, uid;
    switch (c)
    {
    case '1':
        U.User_add(id);
        M.display_manager_menu(id);
        break;
    case '2':
        U.User_update(id);
        M.display_manager_menu(id);
        break;
    case '3':
        U.User_delete(id);
        M.display_manager_menu(id);
        break;
    case '4':
        C.Car_add(id);
        M.display_manager_menu(id);
        break;
    case '5':
        C.Car_update(id);
        M.display_manager_menu(id);
        break;
    case '6':
        C.Car_delete(id);
        M.display_manager_menu(id);
        break;
    case '7':
        cout << "Enter the id of the user : ";
        cin >> uid;
        M.see_rented_to_user(id, uid);
        M.display_manager_menu(id);
        break;
    case '8':
        cout << "Enter the registration number  of the Car : ";
        cin >> reg_no;
        M.see_rented_car(id, reg_no);
        M.display_manager_menu(id);
        break;
    case '9':
        M.see_all_users(id);
        M.display_manager_menu(id);
        break;
    case '0':
        M.see_all_cars(id);
        M.display_manager_menu(id);
        break;
    case 'd':
        cout << "Enter the registration number of the Car : ";
        cin >> reg_no;
        C.Show_duedate(reg_no);
        M.display_manager_menu(id);
        break;
    case 's':
        M.Search_user(id);
        M.display_manager_menu(id);
        break;
    case 'v':
        M.Search_car(id);
        M.display_manager_menu(id);
        break;
    case 'l':
        logout();
        M.display_manager_menu(id);
        break;
    case 'e':
        exit(1);
        break;
    default:
        cout << "\nInvalid choice. Retry!" << endl;
        M.display_manager_menu(id);
    }
}

/*------------------------------- End of Display menus --------------------------------------------------*/

void Car ::Show_duedate(string reg_no)
{
    int flag = 0;
    data.clear();

    readfile("all_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][3] == reg_no)
        {
            flag = 1;

            break;
        }
    }
    if (flag == 0)
    {
        cout << "ERROR: No car with such registration number exist!\n";
        return;
    }
    data.clear();
    string uid;
    time_t stamp;
    readfile("rented_cars_data.csv");
    int f = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == reg_no)
        {
            f = 1;
            uid = data[i][0];
            stamp = stoi(data[i][3]);
            break;
        }
    }
    if (f == 0)
    {
        cout << "Car was not rented!\n";
        return;
    }
    data.clear();
    int days = 30;
    readfile("all_users_info.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == uid)
        {
            if (data[i][3] == "1")
                days = 10; // Customer can rent a car for a max of 10 days
            else
                days = 20; // Employee can rent a car for a max of 20 days
            break;
        }
    }
    stamp += days * 86400;
    tm *due_time = localtime(&stamp);
    if (flag == 0)
        cout << "Car was not rented!\n";
    else
    {
        cout << "Due date of the car is : ";
        cout << due_time->tm_mday << "/" << 1 + due_time->tm_mon << "/" << 1900 + due_time->tm_year << "\n";
    }
}
string Car ::get_car_condition(string reg_no)
{

    data.clear();
    string car_condition = "";

    readfile("all_cars_data.csv");
    int flag = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][3] == reg_no)
        {
            flag = 1;
            car_condition = data[i][2];

            break;
        }
    }
    if (flag)
        cout << "No car with such registration number found ";
    return car_condition;
}
void Car ::Rent_request(string id, string car_name, string type_user)
{
    User u;
    u.rent_car(id, car_name, type_user, u.get_userRecord(id));
}
void Car ::Car_add(string id)
{
    Manager l;
    l.add_car(id);
}
void Car ::Car_delete(string id)
{
    Manager l;
    l.delete_car(id);
}
void Car ::Car_update(string id)
{
    Manager l;
    l.update_car(id);
}
void Car ::Car_search(string id)
{
    Manager l;
    l.Search_car(id);
}

void User ::see_all_cars(string id)
{

    data.clear();
    cout << "In the data below, 0 signifies that the car is not rented and 1 means that the car is rented.\n";
    readfile("all_cars_data.csv");
    printdata(data);
    data.clear();
}

void User ::rent_car(string id, string car_name, string type_user, string user_record)
{
    if (stoi(get_userRecord(id)) < 35)
    {
        cout << "Sorry! You cant rent a car due to poor record score!\n\n";
    }

    else if (type_user == "1")
    {
        int flag = 0;
        int count = 0;

        data.clear();
        readfile("rented_cars_data.csv");
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i][0] == id)
            {
                count++;
            }
        }
        data.clear();
        if (count == 10)
            cout << "Maximum limit reached, you cant rent more than 10 cars !\n\n";
        // threshold score represents the minimum acceptable record for renting more than x number of cars
        if (count > 4 && stoi(get_userRecord(id)) < 75) // threshold score = 75 for renting more than 5 cars
        {
            cout << "You cant rent more than 5 cars as your record score is less than 75 !\n\n";
        }

        else
        {
            readfile("all_cars_data.csv");
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i][0] == car_name && data[i][4] == "0")
                {
                    flag = 1;
                    cout << "car is available!\n";
                    data[i][4] = "1";
                    vector<string> upd;

                    upd.clear();
                    upd.push_back(id);
                    upd.push_back(car_name);
                    upd.push_back(data[i][3]);
                    upd.push_back(to_string(time(0)));
                    append(upd, "rented_cars_data.csv");
                    cout << "car succesfully rented\n";
                    break;
                }
            }
            if (flag == 0)
                cout << "car not available\n";
            write(data, "all_cars_data.csv");
            data.clear();
        }
    }
    else if (type_user == "2")
    {
        int flag = 0;
        int count = 0;

        data.clear();
        readfile("rented_cars_data.csv");
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i][0] == id)
            {
                count++;
            }
        }
        data.clear();
        if (count == 15)
            cout << "Maximum limit reached, you cant rent more than 15 cars !\n\n";
        // threshold score represents the minimum acceptable record for renting more than x number of cars
        if (count > 7 && stoi(get_userRecord(id)) < 80) // threshold score = 80 for renting more than 5 cars
        {
            cout << "You cant rent more than 7 cars as your record score is less than 80 !\n\n";
        }

        else
        {
            readfile("all_cars_data.csv");
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i][0] == car_name && data[i][4] == "0")
                {
                    flag = 1;
                    cout << "car is available!\n";
                    data[i][4] = "1";
                    vector<string> upd;

                    upd.clear();
                    upd.push_back(id);
                    upd.push_back(car_name);
                    upd.push_back(data[i][3]);
                    upd.push_back(to_string(time(0)));
                    append(upd, "rented_cars_data.csv");
                    cout << "car succesfully rented\n";
                    break;
                }
            }
            if (flag == 0)
                cout << "car not available\n";
            write(data, "all_cars_data.csv");
            data.clear();
        }
    }
}

void User ::return_car(string id, string reg_no)
{

    data.clear();
    int f = 0;
    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == reg_no && data[i][0] == id)
        {
            f = 1;
            data.erase(data.begin() + i, data.begin() + i + 1);
            cout << "car was rented by you and is now being returned\n";
            write(data, "rented_cars_data.csv");
            data.clear();
            readfile("all_cars_data.csv");
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i][3] == reg_no)
                    data[i][4] = "0";
            }
            write(data, "all_cars_data.csv");
            break;
        }
    }
    if (f == 0)
        cout << "Invalid details!\n";

    data.clear();
}
string User ::get_userRecord(string id)
{
    int count = 1;
    string userRecord = "";

    data.clear();
    readfile("Users_info.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == id)
        {
            userRecord = data[i][4];
            break;
        }
    }

    data.clear();
    return userRecord;
}
void User ::update_userRecord(string id, string car_condition, string user_type)
{ // user_record varies from 0 and 100
  // larger the user_record, the better the user is eligible to rent a car
  // initially all users are given 100 as base record

    int curr_userRecord = stoi(get_userRecord(id));
    // Weight for late return (adjust as needed)
    const double w1 = 0.2;

    // Weight for car condition (adjust as needed)
    const double w2 = 0.5;

    data.clear();

    readfile("rented_cars_data.csv");
    int days_exceeded = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == id)
        {
            int cur_time = time(0);
            int rent_time = stoi(data[i][3]);
            days_exceeded = max((cur_time - rent_time) / 86400 - 10, 0);
            break;
        }
    }
    if (user_type == "2")
        days_exceeded = max(days_exceeded - 10, 0);
    // initially when giving for rent , the car is either good or excellent  in condition
    int damage_score = 0;

    if (car_condition == "Bad")
    {
        damage_score = 10;
    }
    if (car_condition == "Good" || car_condition == "Excellent")
    {
        damage_score = 0;
    }
    else
    {
        // Handle invalid car condition strings (e.g., log error)
        damage_score = 1;
    }

    int new_userRecord = curr_userRecord - (days_exceeded * w1 + damage_score * w2);
    // Ensure user record stays within valid range
    new_userRecord = max(new_userRecord, 0);
    data.clear();
    readfile("Users_info.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == id)
        {
            data[i][4] = to_string(new_userRecord);
            break;
        }
    }

    data.clear();
}
void User ::see_rented_cars(string id)
{
    int count = 1;

    data.clear();
    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == id)
        {
            cout << count << ". ";
            count++;
            for (int k = 0; k < data[i].size() - 1; k++)
                cout << data[i][k] << " | ";
            time_t stamp = stoi(data[i][3]);
            tm *dateformat = localtime(&stamp);
            cout << dateformat->tm_mday << "/" << 1 + dateformat->tm_mon << "/" << 1900 + dateformat->tm_year << "\n";
        }
    }
    if (count == 0)
        cout << "You haven't rented any cars as of now\n\n";
    data.clear();
}
void User ::check_available(string id, string carname)
{

    data.clear();
    int flag = 0;
    readfile("all_cars_data.csv");
    int count = 1;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == carname && data[i][4] == "0")
        {
            flag = 1;
            cout << count << ". ";
            count++;
            cout << "car is available!\n";
            for (auto j : data[i])
                cout << j << " | ";
            cout << "\n";
            break;
        }
    }
    if (flag == 0)
        cout << "car not available\n";
    data.clear();
}
int User ::calc_fine(string id, string type_user)
{

    data.clear();

    int fine = 0;
    vector<string> reg_nos;
    if (type_user == "1")
    {
        data.clear();
        readfile("rented_cars_data.csv");
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i][0] == id)
            {
                reg_nos.push_back(data[i][2]);
                int cur_time = time(0);
                int rent_time = stoi(data[i][3]);
                if ((cur_time - rent_time) / 86400 > 10)                 // customer can rent a car for a max of 10 days
                    fine += 100 * ((cur_time - rent_time) / 86400 - 10); // fine for customer is 100$ per day
            }
        }

        int rent_price = 0;

        vector<string> prices;
        data.clear();
        readfile("all_cars_data.csv");
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < reg_nos.size(); j++)
            {
                if (data[i][3] == reg_nos[j])
                {
                    rent_price += stoi(data[i][1]);
                }
            }
        }

        cout << "Your Total fine(i.e., fine + rent price) is : " << fine + rent_price << "\n";
        return fine + rent_price;
        data.clear();
    }
    if (type_user == "2")
    {
        data.clear();
        readfile("rented_cars_data.csv");
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i][0] == id)
            {
                int cur_time = time(0);
                int rent_time = stoi(data[i][3]);
                if ((cur_time - rent_time) / 86400 > 20)                // Employee can rent a car for a max of 20 days
                    fine += 50 * ((cur_time - rent_time) / 86400 - 20); // fine for employee is 50$ per day
            }
        }
        int rent_price = 0;

        vector<string> prices;
        data.clear();
        readfile("all_cars_data.csv");
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < reg_nos.size(); j++)
            {
                if (data[i][3] == reg_nos[j])
                {
                    rent_price += stoi(data[i][1]);
                }
            }
        }
        data.clear();
        cout << "Your fine is : " << fine + (0.85) * (rent_price) << "\n";

        return fine + (0.85) * (rent_price);
    }
}
void User ::logout()
{
    cout << "Logging out...\n";
    User u;
    u.display_menu();
}
void User ::clear_fine_amount(string id, string type_user)
{
    int a = calc_fine(id, type_user);
    if (a == 0)
        cout << "You have no pending dues\n";
    else
        cout << "Your fine of Rupees " << a << " is being cleared.\n";
}
void User ::User_add(string id)
{
    Manager l;
    l.add_user(id);
}
void User ::User_delete(string id)
{
    Manager l;
    l.delete_user(id);
}
void User ::User_update(string id)
{
    Manager l;
    l.update_user(id);
}
void User ::User_search(string id)
{
    Manager l;
    l.User_search(id);
}

void Manager ::see_all_users(string id)
{

    data.clear();
    readfile("Users_info.csv");
    cout << "Below are all the users. 1 at the end signifies a Customer, 2 means a Employee and 3 means a Manager \n\n";
    cout << "The data is given in the form of Customer, username, type of user.\n\n";
    print_user_info(data);
    data.clear();
}
void Manager ::see_all_cars(string id)
{

    data.clear();
    readfile("all_cars_data.csv");
    cout << "Below are all the cars. 1 at the end signifies a Customer, 2 means a Employee and 3 means a Manager \n\n";
    cout << "The data is given in the form of car name, car rent price, car condition, registration number, and is_rented(1 if car is rented).\n\n";
    printdata(data);
    data.clear();
}
void Manager ::add_user(string id)
{
    cout << "Please enter the details of the new user : \n";
    string _name, _id, _password, _type;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter id : ";
    cin >> _id;
    cout << "Enter password : ";
    cin >> _password;
    cout << "Enter type of the user : 1 if Customer, 2 if Employee, 3 if Manager : \n";
    cin >> _type;
    fstream fout("Users_info.csv", ios::out | ios::app);
    fout << name << "," << _id << "," << _password << "," << _type << '\n';
    cout << "New user has been added.\n";
}
void Manager ::add_car(string id)
{
    cout << "Please enter the details of the new car : \n";
    string car_name, rent_price, car_condition, reg_no;

    cout << "Enter car Name: ";
    cin.ignore();
    getline(cin, car_name);
    cout << "Enter rent price(in $) : ";
    cin >> rent_price;
    cout << "Enter Car condition(i.e.,Bad/Good/Excellent) : ";
    cin >> car_condition;
    cout << "Enter reg_no : ";
    cin >> reg_no;
    fstream fout("all_cars_data.csv", ios::out | ios::app);
    fout << car_name << "," << rent_price << "," << car_condition << "," << reg_no << ",0" << '\n';
    cout << "New car has been added.\n";
}
void Manager ::delete_car(string id)
{
    string reg_no;
    cout << "Enter the registration number of the car : ";
    cin >> reg_no;

    data.clear();
    int found = 0;
    readfile("all_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][3] == reg_no)
        {
            found = 1;
            data.erase(data.begin() + i, data.begin() + i + 1);
            break;
        }
    }
    write(data, "all_cars_data.csv");
    data.clear();
    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == reg_no)
        {
            data.erase(data.begin() + i, data.begin() + i + 1);
            break;
        }
    }
    write(data, "rented_cars_data.csv");
    data.clear();
    if (found == 0)
        cout << "car not found.\n";
}
void Manager ::delete_user(string id)
{
    string uid;
    cout << "Enter the user id of the user : ";
    cin >> uid;

    data.clear();
    int found = 0;
    readfile("Users_info.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == uid)
        {
            found = 1;
            data.erase(data.begin() + i, data.begin() + i + 1);
            break;
        }
    }
    write(data, "Users_info.csv");
    data.clear();
    vector<string> reg_nos;
    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == uid)
        {
            reg_nos.push_back(data[i][2]);
            data.erase(data.begin() + i, data.begin() + i + 1);
            break;
        }
    }
    write(data, "rented_cars_data.csv");
    data.clear();

    readfile("all_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < reg_nos.size(); j++)
        {
            if (reg_nos[j] == data[i][3])
            {
                data[i][4] = "0";
            }
        }
    }
    write(data, "all_cars_data.csv");
    if (found == 0)
        cout << "User not found.\n";
}
void Manager ::Search_user(string id)
{
    string uid;
    cout << "Enter the id of the user you want to search : ";
    cin >> uid;
    data.clear();
    int flag = 0;
    readfile("Users_info.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == uid)
        {
            flag = 1;

            cout << "User Name :" << data[i][0] << endl;
            cout << "User Record :" << data[i][4] << endl;

            break;
        }
    }
    if (flag == 0)
        cout << "No user with the given user id exists.\n"
             << endl;
}
void Manager ::update_user(string id)
{
    string new_id;
    cout << "Enter the id of the user you want to update : ";
    cin >> new_id;
    cout << "Enter the serial number of the field you want to update : \n";
    cout << "1. Password\n";
    cout << "2. Name of the User\n";
    cout << "3. User Record\n";
    cout << " Enter your choice: ";

    char c;
    cin >> c;

    data.clear();
    int flag = 0;
    readfile("Users_info.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][1] == new_id)
        {
            flag = 1;
            string new_field;
            cout << "Enter the new value of the field : ";
            cin.ignore();
            getline(cin, new_field);
            if (c == '1')
            {
                data[i][2] = new_field;
            }
            else if (c == '2')
            {
                data[i][0] = new_field;
            }
            else
            {
                cout << "Invalid input!\n\n";
            }
            break;
        }
    }
    cout << "User updated\n";
    write(data, "Users_info.csv");
    data.clear();
    if (flag == 0)
        cout << "User was not found.\n\n";
}
void Manager ::Search_car(string id)
{
    string reg_no;
    cout << "Enter the registration number of the car you want to search : ";
    cin >> reg_no;
    data.clear();
    int flag = 0;
    string new_field;
    readfile("all_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][3] == reg_no)
        {
            flag = 1;
            cout << "car name :  " << data[i][0] << endl;
            cout << "car rent :  " << data[i][1] << endl;
            cout << "car Condition :  " << data[i][2] << endl;
            if (data[i][3] == "0")
                cout << "Rent status : Available " << endl;
            else
                cout << "Rent status : Not Available " << endl;
        }
    }

    if (flag == 0)
        cout << "No car was found with the provided registration number.\n\n";
}
void Manager ::update_car(string id)
{
    string reg_no;
    cout << "Enter the registration number of the car you want to update : ";
    cin >> reg_no;
    cout << "Enter the serial number of the field you want to update : \n";
    cout << "1. Name of the car\n";
    cout << "2. Rent price of the car\n";
    cout << "3. Condition of the car\n";
    char c;
    cin >> c;

    data.clear();
    int flag = 0;
    string new_value;
    readfile("all_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][3] == reg_no)
        {
            flag = 1;
            cout << "Enter the new value of the field : ";
            cin.ignore();
            getline(cin, new_value);
            if (c == '1')
            {
                data[i][0] = new_value;
            }
            else if (c == '2')
            {
                data[i][1] = new_value;
            }
            else if (c == '3')
            {
                data[i][2] = new_value;
            }
            else
            {
                cout << "Invalid input!\n\n";
            }
            break;
        }
    }
    if (flag == 0)
    {
        cout << "Car was not found.\n\n";
        return;
    }
    write(data, "all_cars_data.csv");
    data.clear();

    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == reg_no)
        {
            flag = 1;
            if (c == '1')
            {
                data[i][1] = new_value;
            }
            break;
        }
    }
    cout << "Car updated. \n";
    write(data, "rented_cars_data.csv");
}
void Manager ::see_rented_to_user(string id, string uid)
{
    vector<string> reg_nos;

    data.clear();
    int count = 1;
    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][0] == uid)
        {
            reg_nos.push_back(data[i][2]);
        }
    }
    data.clear();
    if (reg_nos.size() == 0)
        cout << "No car is rented to this user.\n\n";
    else
    {
        readfile("all_cars_data.csv");
        for (int d = 0; d < reg_nos.size(); d++)
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i][3] == reg_nos[d])
                {
                    cout << count << ". ";
                    count++;
                    for (auto y : data[i])
                    {
                        if (y != data[i].back())
                            cout << y << " | ";
                        else
                            cout << y << "\n";
                    }
                }
            }
        }
        data.clear();
    }
}
void Manager ::see_rented_car(string id, string reg_no)
{

    data.clear();
    int count = 0;
    readfile("rented_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][2] == reg_no)
        {
            cout << "car with id " << reg_no << " and name " << data[i][1] << " is rented to user with id : " << data[i][0] << "\n";
            count = 1;
            return;
        }
    }
    readfile("all_cars_data.csv");
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i][3] == reg_no)
        {
            cout << "car has not been rented to anyone."
                 << "\n";
            count = 2;
            return;
        }
    }

    if (count == 0)
        cout << "No car with such registration number exists.\n\n";
}
void Hello()
{
    fstream wel;
    wel.open("Hello.txt", ios ::in); // open the welcome.txt file to read
    if (wel.is_open())               // if the welcome.txt file is open
    {
        string str;
        while (getline(wel, str))
        {
            cout << str << "\n";
        }
        wel.close();
    }
}

int main()
{
    system("CLS");
    Hello();
    User U;
    U.display_menu();
    return 0;
}