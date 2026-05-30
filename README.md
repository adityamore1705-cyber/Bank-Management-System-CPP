# 🏦 Bank Management System (C++)

A console-based **Bank Management Application** built in C++ that simulates core banking operations using **Object-Oriented Programming** and **File Handling** for persistent storage.

> Submitted as part of my Internship Project.

---

## 📌 Features
- ✅ Create new customer accounts (auto-generated account number)
- 💰 Deposit money
- 💸 Withdraw money (with balance validation)
- 📊 Check account balance
- 📋 List all accounts
- ❌ Close account
- 🔐 Password-protected transactions
- 💾 Persistent storage using file handling (`accounts.dat`)

---

## 🛠️ Tech Stack
- **Language:** C++ (C++17)
- **Concepts Used:** Classes, Objects, Encapsulation, File I/O, STL (`vector`, `string`)
- **Storage:** Flat-file database (`accounts.dat`)

---

## 📂 Project Structure
```
Bank-Management-System-CPP/
├── src/
│   └── bank.cpp
├── .gitignore
├── LICENSE
└── README.md
```

---

## ⚙️ How to Compile & Run

### Prerequisites
- A C++ compiler (g++ / MinGW / clang)

### Steps
```bash
# Clone the repository
git clone https://github.com/adityamore1705-cyber/Bank-Management-System-CPP.git
cd Bank-Management-System-CPP/src

# Compile
g++ -std=c++17 -o bank bank.cpp

# Run
./bank        # Linux / Mac
bank.exe      # Windows
```

---

## 🖥️ Sample Output
```
========= BANK MANAGEMENT SYSTEM =========
1. Create New Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. List All Accounts
6. Close Account
0. Exit
==========================================
Enter your choice:
```

---

## 🧠 OOP Concepts Demonstrated

| Concept        | Where it's used                          |
|----------------|------------------------------------------|
| Class & Object | `Account`, `Bank` classes                |
| Encapsulation  | Private data members + public methods    |
| Abstraction    | User interacts only via menu             |
| File Handling  | `loadFromFile()`, `saveToFile()`         |

---

## 🚀 Future Enhancements
- Transaction history & mini-statement
- Interest calculation
- Admin login module
- Encryption for stored passwords
- GUI version using Qt

---

## 👨‍💻 Author
**Aditya More**  
- GitHub: [@adityamore1705-cyber](https://github.com/adityamore1705-cyber)

---

## 📄 License
This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.
