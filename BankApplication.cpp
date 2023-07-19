#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <stdlib.h>

// Function to validate email address
bool isValidEmail(const std::string& email) {
    // Regular expression pattern for email validation
    std::regex emailPattern("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    return std::regex_match(email, emailPattern);
}

// Function to validate phone number
bool isValidPhoneNumber(const std::string& phoneNumber) {
    // Regular expression pattern for phone number validation
    std::regex phonePattern("\\d{10}");
    return std::regex_match(phoneNumber, phonePattern);
}

// Function to validate password
bool isValidPassword(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    for (char ch : password) {
        if (std::isupper(ch)) {
            hasUppercase = true;
        } else if (std::islower(ch)) {
            hasLowercase = true;
        } else if (std::isdigit(ch)) {
            hasDigit = true;
        }
        // If all criteria are met, no need to check further
        if (hasUppercase && hasLowercase && hasDigit) {
            return true;
        }
    }
    return false;
}

// Function to check if a file exists
bool fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}

// Customer Class
class Customer{
private:
    int userID;
    std::string name;
    int age;
    std::string gender;
    std::string address;
    std::string email;
    std::string phoneNumber;
    double accountBalance;
    std::string Password;

public:
    // Constructor
    Customer(){}

    Customer(int userId, const std::string& n, int a, const std::string& g, const std::string& addr,
             const std::string& e, const std::string& phone, double balance, const std::string& Pwd) {
        userID = userId;
        name = n;
        age = a;
        gender = g;
        address = addr;
        email = e;
        phoneNumber = phone;
        accountBalance = balance;
        Password = Pwd;
    }

    // Setter Functions

    void setName(std::string& newName) {
        this->name = newName;
    }

    void setAge(int newAge) {
        this->age = newAge;
    }

    void setGender(std::string& newGender) {
        this->gender = newGender;
    }

    void setAddress(std::string& newAddress) {
        this->address = newAddress;
    }

    void setEmail(std::string& newEmail) {
        this->email = newEmail;
    }

    void setPhoneNo(std::string& newPhoneNo) {
        this->phoneNumber = newPhoneNo;
    }

    void setAccountBalance(double newAccountBalance) {
        this->accountBalance = newAccountBalance;
    }

    void setPwd(std::string& newPwd) {
        this->Password = newPwd;
    }

    // Getter functions
    int getUserId() const {
        return userID;
    }

    std::string getName() const {
        return name;
    }

    std::string getPassword() const {
        return Password;
    }

    // Getter for account balance
    double getAccountBalance() const {
        return accountBalance;
    }

    // Credit money to account
    bool creditMoney(double amount) {
        accountBalance += amount;
        return true;
    }

    // Debit money from account
    bool debitMoney(double amount) {
        if (accountBalance >= amount) {
            accountBalance -= amount;
            return true;
        }
        return false;
    }

    // displays account details
    void display_details() {
        std::cout << "user ID : " << userID << std::endl;
        std::cout << "name : " << name << std::endl;
        std::cout << "age : " << age << std::endl;
        std::cout << "gender : " << gender << std::endl;
        std::cout << "address : " << address << std::endl;
        std::cout << "email : " << email << std::endl;
        std::cout << "phone number : " << phoneNumber << std::endl;
        std::cout << "account balance : " << accountBalance << std::endl;
    }

    // gives menu to credit money
    void creditMenu() {
        system("cls");
        std::cout << "\n*********** Credit Money ***********" << std::endl;
        double amount;
        std::cout << "Your current balance: $" << getAccountBalance() << std::endl;
        std::cout << "Enter the amount to be credited: ";
        std::cin >> amount;

        // Confirm with password
        std::string confirmPwd;
        std::cout << "Confirm with your password: ";
        std::cin >> confirmPwd;

        if (confirmPwd == getPassword()) {
            if (creditMoney(amount)) {
                saveCustomerToFile(getUserId());
                std::cout << "Amount credited successfully." << std::endl;
            } else {
                std::cout << "Error: Unable to credit amount. Operation aborted." << std::endl;
            }
        } else {
            std::cout << "Error: Invalid password. Operation aborted." << std::endl;
        }
        return;
    }

    // gives menu to debit money
    void debitMenu() {
        system("cls");
        std::cout << "\n*********** Debit Money ***********" << std::endl;
        double amount;
        std::cout << "Your current balance: $" << getAccountBalance() << std::endl;
        std::cout << "Enter the amount to be debited: ";
        std::cin >> amount;

        // Check if amount is greater than the current balance
        if (amount > getAccountBalance()) {
            std::cout << "Error: Insufficient funds." << std::endl;
            return;
        }

        // Confirm with password
        std::string confirmPwd;
        std::cout << "Confirm with your password: ";
        std::cin >> confirmPwd;

        if (confirmPwd == getPassword()) {
            if (debitMoney(amount)) {
                saveCustomerToFile(getUserId());
                std::cout << "Amount debited successfully." << std::endl;
            } else {
                std::cout << "Error: Unable to debit amount. Operation aborted." << std::endl;
            }
        } else {
            std::cout << "Error: Invalid password. Operation aborted." << std::endl;
        }
        return;
    }

    // gives menu to trasnfer money
    void transferMoneyMenu() {
        system("cls");
        int flag = 0;
        while (flag == 0){
            // Transfer Money page options
            int transferChoice;
            std::cout << "\n*********** Transfer Money ***********" << std::endl;
            std::cout << "1. Enter Recepient's user ID" << std::endl;
            std::cout << "2. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> transferChoice;

            switch (transferChoice) {
                case 1: {
                    int RecepientUserId;
                    double amount;
                    std::cout << "Your current balance: $" << getAccountBalance() << std::endl;
                    std::cout << "Enter the user ID of recepient: ";
                    std::cin >> RecepientUserId;
                    // Check if account file exists
                    std::string recepientAccountFile = "BankAccounts/Customer" + std::to_string(RecepientUserId) + ".txt";
                    if (!fileExists(recepientAccountFile)) {
                        std::cout << "Error: Recepient Account not found. Please check your user ID or sign up." << std::endl;
                        break;
                    }
                    // Read Recepient Customer object from file
                    std::ifstream inFile(recepientAccountFile);
                    Customer recepientUser;
                    if (inFile.is_open()) {
                        inFile >> recepientUser;
                        inFile.close();
                    }

                    std::string recepientname = recepientUser.getName();
                    double recepientbalance = recepientUser.getAccountBalance();

                    std::cout << "Enter the amount to be Transfered to " + recepientname + " : ";
                    std::cin >> amount;
                    // Check if amount is greater than the current balance
                    if (amount > getAccountBalance()) {
                        std::cout << "Error: Insufficient funds." << std::endl;
                        break;
                    }

                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;
                    double failSafecurrentUserBalance = getAccountBalance();
                    double failSaferecepientUserBalance = recepientUser.getAccountBalance();
                    if (confirmPwd == getPassword()) {
                        if (debitMoney(amount) && recepientUser.creditMoney(amount)) {
                            saveCustomerToFile(getUserId());
                            recepientUser.saveCustomerToFile(RecepientUserId);
                            std::cout << "Amount transferred successfully." << std::endl;
                        } else {
                            setAccountBalance(failSafecurrentUserBalance);
                            recepientUser.setAccountBalance(failSaferecepientUserBalance);
                            std::cout << "Error: Unable to trasnfer amount. Operation aborted." << std::endl;
                        }
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 2: {
                    flag = 1;
                    break;
                }
                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
            }
        }
    }

    // gives menu to display user details
    void displayDetailsMenu() {
        system("cls");
        std::cout << "\n*********** User Details ***********" << std::endl;
        display_details();
        int displayChoice;
        std::cout << "\n*********** User Details Menu ***********" << std::endl;
        std::cout << "1. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> displayChoice;

        switch (displayChoice) {
            case 1: {
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    }

    // gives menu to change user details
    void changeDetailsMenu() {
        system("cls");
        std::cout << "\n*********** Change User Details ***********\n" << std::endl;

        std::cout << "\n*********** User Details ***********" << std::endl;
        display_details();
        std::cout << "\n************************************" << std::endl;
        int flag = 0;
        while (flag == 0){
            // Transfer Money page options
            int ChangeChoice;
            std::cout << "1. Change Name" << std::endl;
            std::cout << "2. Change Age" << std::endl;
            std::cout << "3. Change Gender" << std::endl;
            std::cout << "4. Change Address" << std::endl;
            std::cout << "5. Change Email" << std::endl;
            std::cout << "6. Change Phone Number" << std::endl;
            std::cout << "7. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> ChangeChoice;

            switch (ChangeChoice) {
                case 1: {
                    std::string newName;
                    std::cout << "Enter your new name: ";
                    std::cin.ignore();
                    std::getline(std::cin, newName);
                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;

                    if (confirmPwd == getPassword()) {
                        setName(newName);
                        saveCustomerToFile(getUserId());
                        std::cout<< "User Name successfully Updated" << std::endl;
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 2: {
                    int newAge;
                    while (true) {
                        // Accept input from the user
                        std::string ageInput;
                        std::cout << "Enter your age: ";
                        std::getline(std::cin, ageInput);

                        // Check if the input is a number
                        std::stringstream ss(ageInput);
                        if (!(ss >> newAge)) {
                            std::cout << "Invalid input. Please enter a valid number for age.\n";
                            continue;
                        }

                        // Check if the age is greater than 18
                        if (newAge >= 18) {
                            break;
                        } else {
                            std::cout << "Enter age greater than 18.\n";
                        }
                    }
                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;

                    if (confirmPwd == getPassword()) {
                        setAge(newAge);
                        saveCustomerToFile(getUserId());
                        std::cout<< "User Age successfully Updated" << std::endl;
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::string newGender;
                    while (flag == 0) {
                        std::cout << "Choose your new gender : " << std::endl;
                        std::cout << "1. Male " << std::endl;
                        std::cout << "2. Female " << std::endl;
                        std::cout << "3. Others " << std::endl;
                        std::cout << "Enter your Choice : " << std::endl;
                        int genderChoice;
                        std::cin >> genderChoice;
                        switch (genderChoice) {
                            case 1: {
                                newGender = "Male";
                                flag = 1;
                                break;
                            }
                            case 2: {
                                newGender = "Female";
                                flag = 1;
                                break;
                            }
                            case 3: {
                                newGender = "Others";
                                flag = 1;
                                break;
                            }
                            default: {
                                std::cout << "Invalid choice. Please try again." << std::endl;
                                break;
                            }
                        }
                    }
                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;

                    if (confirmPwd == getPassword()) {
                        setGender(newGender);
                        saveCustomerToFile(getUserId());
                        std::cout<< "User Gender successfully Updated" << std::endl;
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 4: {
                    std::string newAddress;
                    std::cout << "Enter your new address: ";
                    std::cin.ignore();
                    std::getline(std::cin, newAddress);
                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;

                    if (confirmPwd == getPassword()) {
                        setAddress(newAddress);
                        saveCustomerToFile(getUserId());
                        std::cout<< "User Address successfully Updated" << std::endl;
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 5: {
                    std::string newEmail;
                    std::cout << "Enter your new email: ";
                    std::cin.ignore();
                    std::getline(std::cin, newEmail);

                    // Validate email
                    while (!isValidEmail(newEmail)) {
                        std::cout << "Invalid email. Please enter a valid email: ";
                        std::getline(std::cin, newEmail);
                    }
                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;

                    if (confirmPwd == getPassword()) {
                        setEmail(newEmail);
                        saveCustomerToFile(getUserId());
                        std::cout<< "User Email successfully Updated" << std::endl;
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 6: {
                    std::string newPhoneNumber;
                    std::cout << "Enter your new phone number : ";
                    std::cin.ignore();
                    std::getline(std::cin, newPhoneNumber);

                    // Validate phone number
                    while (!isValidPhoneNumber(newPhoneNumber)) {
                        std::cout << "Invalid phone number. Please enter a valid phone number: ";
                        std::cin >> newPhoneNumber;
                    }

                    // Confirm with password
                    std::string confirmPwd;
                    std::cout << "Confirm with your password: ";
                    std::cin >> confirmPwd;

                    if (confirmPwd == getPassword()) {
                        setPhoneNo(newPhoneNumber);
                        saveCustomerToFile(getUserId());
                    std::cout<< "User Phone Number successfully Updated" << std::endl;
                    } else {
                        std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                    }
                    break;
                }
                case 7: {
                    flag = 1;
                    break;
                }
                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
            }
        }
    }

    // gives menu to change password
    void changePassword() {
        system("cls");
        std::cout << "\n*********** Change Password ***********" << std::endl;
        std::string confirmPwd;
        std::cout << "Confirm with your password: ";
        std::cin >> confirmPwd;

        if (confirmPwd == getPassword()) {
            std::string newPwd, confirmNewPwd;
            std::cout << "Enter New password: ";
            std::cin >> newPwd;
            std::cout << "Enter your password: " << std::endl;
            std::getline(std::cin, newPwd);

            // Validate password
            while (!isValidPassword(newPwd)) {
                std::cout << "Invalid password." << std::endl;
                std::cout << "Password must be have a minimum length of 8 characters " << std::endl;
                std::cout << "and have atleast 1 upper case, 1 lower case alphabet and 1 number." << std::endl;
                std::cout << "please enter a valid password : " << std::endl;
                std::getline(std::cin, newPwd);
            }

            std::cout << "Confirm New password: ";
            std::cin >> confirmNewPwd;
            if (newPwd == confirmNewPwd) {
                setPwd(newPwd);
                saveCustomerToFile(getUserId());
                std::cout<< "User Password successfully Updated" << std::endl;
            }
            else{
                std::cout << "Passwords do not match. Operation aborted." << std::endl;
            }
        } else {
            std::cout << "Error: Invalid password. Operation aborted." << std::endl;
        }
    }

    // Write customer object to file
    void saveCustomerToFile(int nextUserId) {
        std::string fileName = "BankAccounts/Customer" + std::to_string(nextUserId) + ".txt";
        std::ofstream outFile(fileName);

        if (outFile.is_open()) {
            outFile << userID << std::endl;
            outFile << name << std::endl;
            outFile << age << std::endl;
            outFile << gender << std::endl;
            outFile << address << std::endl;
            outFile << email << std::endl;
            outFile << phoneNumber << std::endl;
            outFile << accountBalance << std::endl;
            outFile << Password << std::endl;

            outFile.close();
        } else {
            std::cout << "Error: Unable to create customer file." << std::endl;
        }
    }

    // Overload stream insertion operator to write Customer object to file
    friend std::ostream& operator<<(std::ostream& out, const Customer& customer) {
        out << customer.userID << std::endl;
        out << customer.name << std::endl;
        out << customer.age << std::endl;
        out << customer.gender << std::endl;
        out << customer.address << std::endl;
        out << customer.email << std::endl;
        out << customer.phoneNumber << std::endl;
        out << customer.accountBalance << std::endl;
        out << customer.Password << std::endl;
        return out;
    }

    // Overload stream extraction operator to read Customer object from file
    friend std::istream& operator>>(std::istream& in, Customer& customer) {
        in >> customer.userID;
        in >> customer.name;
        in >> customer.age;
        in >> customer.gender;
        in >> customer.address;
        in >> customer.email;
        in >> customer.phoneNumber;
        in >> customer.accountBalance;
        in >> customer.Password;
        return in;
    }
};

// bank Class
class Bank {
private:
    std::string bankName;
    int numAccountsOpened;
    int numAccountsClosed;
    int nextUserId;

public:
    // Constructor
    Bank() {
        bankName = "MyBank";
        numAccountsOpened = 0;
        numAccountsClosed = 0;
        nextUserId = 100001;
    }

    // Getter for bank name
    std::string getBankName() const {
        return bankName;
    }

    // Getter for next user ID
    int getNextUserId() const {
        return nextUserId;
    }

    // Increment next user ID
    void incrementNextUserId() {
        nextUserId++;
    }
    void incrementnumAccountsOpened() {
        numAccountsOpened++;
    }
    void incrementnumAccountsClosed() {
        numAccountsClosed++;
    }

    inline void signUp() {
        system("cls");
        std::cout << "\n*********** Sign-Up Page ***********" << std::endl;
        std::string name, gender, address, email, phoneNumber, password;
        int age;

        std::cout << "Enter your name: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, name);
        
        while (true) {
            // Accept input from the user
            std::string ageInput;
            std::cout << "Enter your age: " << std::endl;
            std::getline(std::cin, ageInput);

            // Check if the input is a number
            std::stringstream ss(ageInput);
            if (!(ss >> age)) {
                std::cout << "Invalid input. Please enter a valid number for age.\n";
                continue;
            }

            // Check if the age is greater than 18
            if (age >= 18) {
                break;
            } else {
                std::cout << "Enter age greater than 18.\n";
            }
        }

        int flag = 0;
        while (flag == 0) {
            std::cout << "Choose your gender : " << std::endl;
            std::cout << "1. Male " << std::endl;
            std::cout << "2. Female " << std::endl;
            std::cout << "3. Others " << std::endl;
            std::cout << "Enter your Choice : " << std::endl;
            int genderChoice;
            std::cin >> genderChoice;
            switch (genderChoice) {
                case 1: {
                    gender = "Male";
                    flag = 1;
                    break;
                }
                case 2: {
                    gender = "Female";
                    flag = 1;
                    break;
                }
                case 3: {
                    gender = "Others";
                    flag = 1;
                    break;
                }
                default: {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
                }
            }
        }

        std::cout << "Enter your address: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, address);

        std::cout << "Enter your email: " << std::endl;
        std::getline(std::cin, email);

        // Validate email
        while (!isValidEmail(email)) {
            std::cout << "Invalid email. Please enter a valid email: ";
            std::getline(std::cin, email);
        }

        std::cout << "Enter your phone number: " << std::endl;
        std::cin >> phoneNumber;

        // Validate phone number
        while (!isValidPhoneNumber(phoneNumber)) {
            std::cout << "Invalid phone number. Please enter a valid phone number: ";
            std::cin >> phoneNumber;
        }

        std::cout << "Enter your password: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, password);

        // Validate password
        while (!isValidPassword(password)) {
            std::cout << "Invalid password." << std::endl;
            std::cout << "Password must be have a minimum length of 8 characters " << std::endl;
            std::cout << "and have atleast 1 upper case, 1 lower case alphabet and 1 number." << std::endl;
            std::cout << "please enter a valid password : " << std::endl;
            std::getline(std::cin, password);
        }

        // Create a new Customer object
        Customer newCustomer(getNextUserId(), name, age, gender, address, email, phoneNumber, 0.0, password);

        // Save the new Customer object to file
        newCustomer.saveCustomerToFile(getNextUserId());
        
        //update bank details
        incrementnumAccountsOpened();
        incrementNextUserId();
        saveBankToFile();
        
        // confirmation message
        system("cls");
        std::cout << "\n************************************" << std::endl;
        std::cout << "User ID : " << getNextUserId() << std::endl;
        std::cout << "Note this User ID for future use." << std::endl;
        std::cout << "It will be used for all future logins." << std::endl;
        std::cout << "\n************************************" << std::endl;

        std::cout << "Account created successfully. Please log in to continue." << std::endl;
        return;
    }

    void saveBankToFile() {
        std::string fileName = "bank_obj.txt";
        std::ofstream outFile(fileName);

        if (outFile.is_open()) {
            outFile << bankName << std::endl;
            outFile << numAccountsOpened << std::endl;
            outFile << numAccountsClosed << std::endl;
            outFile << nextUserId << std::endl;

            outFile.close();
        } else {
            std::cout << "Error: Unable to create Bank file." << std::endl;
        }
    }

    // Overload stream insertion operator to write Bank object to file
    friend std::ostream& operator<<(std::ostream& out, const Bank& bank) {
        out << bank.bankName << std::endl;
        out << bank.numAccountsOpened << std::endl;
        out << bank.numAccountsClosed << std::endl;
        out << bank.nextUserId << std::endl;
        return out;
    }

    // Overload stream extraction operator to read Bank object from file
    friend std::istream& operator>>(std::istream& in, Bank& bank) {
        in >> bank.bankName;
        in >> bank.numAccountsOpened;
        in >> bank.numAccountsClosed;
        in >> bank.nextUserId;
        return in;
    }
};

int main() {
    // Check if bank object file exists
    std::string bankObjFile = "bank_obj.txt";
    Bank currentBank;

    if (fileExists(bankObjFile)) {
        std::ifstream inFile(bankObjFile);

        if (inFile.is_open()) {
            // Read bank object from file
            inFile >> currentBank;
            inFile.close();
        } else {
            std::cout << "Error: Unable to read bank object file." << std::endl;
            return 1;
        }
    } else {
        // Write bank object to file
        std::ofstream outFile(bankObjFile);

        if (outFile.is_open()) {
            outFile << currentBank;
            outFile.close();
        } else {
            std::cout << "Error: Unable to create bank object file." << std::endl;
            return 1;
        }
    }

    int choice;

    do {
        // Display homepage
        system("cls");
        std::cout << "*********** Welcome to " << currentBank.getBankName() << " ***********" << std::endl;
        std::cout << "1. Sign up" << std::endl;
        std::cout << "2. Log in" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                currentBank.signUp();
                break;
            }
            case 2: {
                system("cls");
                std::cout << "\n*********** Login Page ***********" << std::endl;
                int userId;
                std::string password;

                std::cout << "Enter your user ID: ";
                std::cin >> userId;

                std::cout << "Enter your password: ";
                std::cin >> password;

                // Check if account file exists
                std::string accountFile = "BankAccounts/Customer" + std::to_string(userId) + ".txt";

                if (!fileExists(accountFile)) {
                    std::cout << "Error: Account not found. Please check your user ID or sign up." << std::endl;
                    break;
                }

                // Read Customer object from file
                std::ifstream inFile(accountFile);

                Customer currentUser;
                if (inFile.is_open()) {
                    inFile >> currentUser;
                    inFile.close();
                    
                    // Check if passwords match
                    if (password != currentUser.getPassword()) {
                        std::cout << "Error: Invalid password. Please try again." << std::endl;
                        break;
                    }

                    // Create a Customer object for the current user
                    //Customer currentUser(name, age, gender, address, email, phoneNumber, balance, Pwd);

                    // Banking page options
                    int bankingChoice;

                    do {
                        system("cls");
                        std::cout << "\n*********** Banking Menu ***********" << std::endl;
                        std::cout << "1. Credit money" << std::endl;
                        std::cout << "2. Debit money" << std::endl;
                        std::cout << "3. Transfer money" << std::endl;
                        std::cout << "4. View user details" << std::endl;
                        std::cout << "5. Change user details" << std::endl;
                        std::cout << "6. Change Password" << std::endl;
                        std::cout << "7. Remove account" << std::endl;
                        std::cout << "8. Log out" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> bankingChoice;

                        switch (bankingChoice) {
                            case 1: {
                                currentUser.creditMenu();
                                break;
                            }
                            case 2: {
                                currentUser.debitMenu();
                                break;
                            }
                            case 3: {
                                currentUser.transferMoneyMenu();
                                break;
                            }
                            case 4: {
                                currentUser.displayDetailsMenu();
                                break;
                            }
                            case 5: {
                                currentUser.changeDetailsMenu();
                                break;
                            }
                            case 6: {
                                currentUser.changePassword();
                                break;
                            }
                            case 7: {
                                system("cls");
                                std::cout << "\n*********** Remove Account ***********" << std::endl;

                                std::cout << "\n*********** User Details ***********" << std::endl;
                                currentUser.display_details();
                                std::cout << "\n************************************" << std::endl;
                                std::cout << "\nThe Bank advices customers to transfer money to a separate account before deletion." << std::endl;
                                std::cout << "\n************************************" << std::endl;
                                int removeChoice;
                                std::cout << "\nAre you sure you want to delete your account ?" << std::endl;
                                std::cout << "1. Yes !" << std::endl;
                                std::cout << "2. No !" << std::endl;
                                std::cout << "Enter your choice: ";
                                std::cin >> removeChoice;

                                switch (removeChoice) {
                                    case 1: {
                                        // Confirm with password
                                        std::string confirmPwd;
                                        std::cout << "Confirm with your password: ";
                                        std::cin >> confirmPwd;

                                        if (confirmPwd == password) {
                                            // Move the account file to the deleted folder
                                            std::string deletedAccountFile = "DeletedAccounts/Customer" + std::to_string(userId) + ".txt";
                                            std::rename(accountFile.c_str(), deletedAccountFile.c_str());
                                            //update bank details
                                            currentBank.incrementnumAccountsClosed();
                                            currentBank.saveBankToFile();
                                            std::cout << "Account removed successfully." << std::endl;

                                            // Redirect to homepage
                                            bankingChoice = 8;
                                        } else {
                                            std::cout << "Error: Invalid password. Operation aborted." << std::endl;
                                        }
                                        break;
                                    }
                                    case 2: {
                                        break;
                                    }
                                    default: {
                                        std::cout << "Invalid choice. Please try again." << std::endl;
                                        break;
                                    }
                                }
                                break;
                            }
                            case 8: {
                                // Redirect to homepage
                                system("cls");
                                break;
                            }
                            default: {
                                std::cout << "Invalid choice. Please try again." << std::endl;
                                break;
                            }
                        }
                    } while (bankingChoice != 8);
                } else {
                    std::cout << "Error: Unable to read account file." << std::endl;
                    return 1;
                }

                break;
            }
            case 3: {
                system("cls");
                std::cout << "Thank you for using " << currentBank.getBankName() << ". Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    } while (choice != 3);

    return 0;
}