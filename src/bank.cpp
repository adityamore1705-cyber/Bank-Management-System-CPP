// Bank Management Application in C++
// Demonstrates OOP (classes, encapsulation) + file handling for persistence.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

const string DATA_FILE = "accounts.dat";

// ---------------- Account Class ----------------
class Account {
private:
    int accountNo;
    string name;
    string password;
    double balance;

public:
    Account() : accountNo(0), balance(0.0) {}
    Account(int accNo, const string& nm, const string& pwd, double bal)
        : accountNo(accNo), name(nm), password(pwd), balance(bal) {}

    // Getters
    int    getAccountNo() const { return accountNo; }
    string getName()      const { return name; }
    string getPassword()  const { return password; }
    double getBalance()   const { return balance; }

    // Operations
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        cout << "Deposited Rs. " << fixed << setprecision(2) << amount
             << " successfully.\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        cout << "Withdrawn Rs. " << fixed << setprecision(2) << amount
             << " successfully.\n";
        return true;
    }

    void display() const {
        cout << "-----------------------------------\n";
        cout << "Account No : " << accountNo << "\n";
        cout << "Name       : " << name << "\n";
        cout << "Balance    : Rs. " << fixed << setprecision(2) << balance << "\n";
        cout << "-----------------------------------\n";
    }

    // File I/O helpers
    string serialize() const {
        return to_string(accountNo) + "|" + name + "|" + password + "|" +
               to_string(balance);
    }

    static Account deserialize(const string& line) {
        Account a;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        a.accountNo = stoi(line.substr(0, p1));
        a.name      = line.substr(p1 + 1, p2 - p1 - 1);
        a.password  = line.substr(p2 + 1, p3 - p2 - 1);
        a.balance   = stod(line.substr(p3 + 1));
        return a;
    }
};

// ---------------- Bank Class ----------------
class Bank {
private:
    vector<Account> accounts;

    void loadFromFile() {
        accounts.clear();
        ifstream fin(DATA_FILE);
        if (!fin) return;
        string line;
        while (getline(fin, line)) {
            if (!line.empty()) accounts.push_back(Account::deserialize(line));
        }
        fin.close();
    }

    void saveToFile() const {
        ofstream fout(DATA_FILE, ios::trunc);
        for (const auto& a : accounts) fout << a.serialize() << "\n";
        fout.close();
    }

    int generateAccountNo() const {
        int maxNo = 1000;
        for (const auto& a : accounts)
            if (a.getAccountNo() > maxNo) maxNo = a.getAccountNo();
        return maxNo + 1;
    }

    Account* findAccount(int accNo) {
        for (auto& a : accounts)
            if (a.getAccountNo() == accNo) return &a;
        return nullptr;
    }

    bool authenticate(Account* acc) {
        if (!acc) return false;
        cout << "Enter password: ";
        string pwd; cin >> pwd;
        if (pwd != acc->getPassword()) {
            cout << "Authentication failed.\n";
            return false;
        }
        return true;
    }

public:
    Bank() { loadFromFile(); }

    void createAccount() {
        string name, pwd;
        double initial;
        cout << "Enter customer name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Set a password: ";
        cin >> pwd;
        cout << "Initial deposit amount: ";
        cin >> initial;
        if (initial < 0) initial = 0;

        int accNo = generateAccountNo();
        accounts.emplace_back(accNo, name, pwd, initial);
        saveToFile();
        cout << "\nAccount created successfully!\n";
        cout << "Your Account Number is: " << accNo << "\n";
    }

    void depositMoney() {
        int accNo; double amt;
        cout << "Enter account number: "; cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found.\n"; return; }
        if (!authenticate(acc)) return;
        cout << "Enter amount to deposit: "; cin >> amt;
        acc->deposit(amt);
        saveToFile();
    }

    void withdrawMoney() {
        int accNo; double amt;
        cout << "Enter account number: "; cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found.\n"; return; }
        if (!authenticate(acc)) return;
        cout << "Enter amount to withdraw: "; cin >> amt;
        if (acc->withdraw(amt)) saveToFile();
    }

    void checkBalance() {
        int accNo;
        cout << "Enter account number: "; cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found.\n"; return; }
        if (!authenticate(acc)) return;
        acc->display();
    }

    void listAccounts() const {
        if (accounts.empty()) { cout << "No accounts found.\n"; return; }
        cout << "\n=========== All Accounts ===========\n";
        for (const auto& a : accounts) a.display();
    }

    void closeAccount() {
        int accNo;
        cout << "Enter account number to close: "; cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found.\n"; return; }
        if (!authenticate(acc)) return;
        accounts.erase(remove_if(accounts.begin(), accounts.end(),
                       [accNo](const Account& a){ return a.getAccountNo()==accNo; }),
                       accounts.end());
        saveToFile();
        cout << "Account closed successfully.\n";
    }
};

// ---------------- Menu ----------------
void showMenu() {
    cout << "\n========= BANK MANAGEMENT SYSTEM =========\n";
    cout << "1. Create New Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. List All Accounts\n";
    cout << "6. Close Account\n";
    cout << "0. Exit\n";
    cout << "==========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Bank bank;
    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney();  break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.checkBalance();  break;
            case 5: bank.listAccounts();  break;
            case 6: bank.closeAccount();  break;
            case 0: cout << "Thank you for banking with us!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
