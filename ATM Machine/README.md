# 🏦 C++ ATM Banking System

**A multi-layer, console-based C++ banking application featuring object-oriented design, SQLite persistence, and TCP/IP client-server communication.**

This project simulates core ATM banking operations while exploring software architecture, data structures, database management, network programming, and concurrency in modern C++.

## ✨ Features

### Banking Operations
- **Balance Enquiry** — retrieve the current account balance.
- **Cash Deposit** — deposit money and persist updated account balances.
- **Cash Withdrawal** — withdraw money subject to account validation and available funds.
- **Transaction History** — view recorded transactions during the current application session.
- **Money Transfer** — transfer funds between accounts through the local ATM interface.
- **Account Search** — find accounts by minimum balance.
- **PIN Authentication** — authenticate customers before granting access, with a limited number of attempts.

### Technical Features
- **Object-Oriented Programming** — encapsulation, inheritance and polymorphism.
- **Efficient Account Lookup** — `std::unordered_map` with account numbers as keys.
- **Smart Pointers** — `std::unique_ptr` for account ownership in the `Bank` class.
- **Layered Architecture** — separates the client, server, banking logic, account management and persistence responsibilities.
- **TCP/IP Networking** — communication between the ATM client and banking server using Winsock.
- **Multithreading** — handles client connections using `std::thread`.
- **Thread Synchronisation** — uses `std::mutex` to protect shared banking data.
- **SQLite Database** — persists account records and balances across application restarts.
- **CMake Build System** — manages compilation and linking.

## 🏗️ Architecture

```text
             ATM Client
            ATMClient.cpp
                  |
               TCP/IP
                  |
                  v
           Banking Server
          BankingServer.cpp
                  |
                  v
             BankService
          Banking business logic
                  |
                  v
             Bank / Account
          Account management
                  |
                  v
             Database Layer
             Database.cpp
                  |
                  v
                SQLite
          Persistent account data
```

The project provides two interfaces:

- **Networked ATM:** The client communicates with the server over TCP/IP. The current network interface supports balance enquiries, deposits and withdrawals.
- **Local ATM:** The `main.cpp` interface calls the banking service directly and provides balance enquiries, deposits, withdrawals, transaction history, money transfers and account searches by minimum balance.


## 🛠️ Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Core application development |
| STL | Containers, algorithms and utilities |
| `std::unordered_map` | Account lookup by account number |
| `std::unique_ptr` | Account ownership and memory management |
| `std::thread` | Concurrent client handling |
| `std::mutex` | Synchronisation of shared data |
| Winsock / TCP/IP | Client-server networking |
| SQLite | Persistent account storage |
| CMake | Build configuration |
| Git and GitHub | Version control and source management |

## 📁 Project Structure

```text
ATM-Machine/
├── ATMClient.cpp
├── BankingServer.cpp
├── BankingServer.h
├── BankService.cpp
├── BankService.h
├── Bank.cpp
├── Bank.h
├── Account.cpp
├── Account.h
├── SavingsAccount.cpp
├── SavingsAccount.h
├── Transaction.cpp
├── Transaction.h
├── Database.cpp
├── Database.h
├── simple_atm.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```

*The structure above represents the main source files; exact filenames and additional files may vary.*

## ⚙️ Prerequisites

- Windows
- A C++17-compatible compiler, such as MinGW-w64
- CMake
- Ninja or another supported build tool
- SQLite source/header files or an available SQLite development package

## 🚀 Build and Run

### 1. Clone the repository

```bash
git clone:  https://github.com/codebyasim/ATM-Machine.git
cd ATM-Machine
```

### 2. Configure the project

```bash
cmake -S . -B build -G Ninja
```

Use the generator and compiler configuration appropriate for your installed tools.

### 3. Build

```bash
cmake --build build
```

### 4. Start the banking server

Open the first terminal:

```powershell
.\build\atm.exe
```

Keep the server running and wait for the message indicating that it is listening on port `8080`.

### 5. Start the network client

Open a second terminal in the project directory:

```powershell
.\build\atm_client.exe
```

The client connects to `127.0.0.1:8080`, so both programs currently run on the same computer.

## 🔑 Demo Account Credentials

Use the following demo accounts to test the local ATM interface.

| Account Number | Account Holder | PIN |
|---|---|---|
| `10001` | Asim | `1234` |
| `10002` | Ahmed | `5678` |
| `10003` | John | `4321` |
| `10004` | Savings User | `9999` |

**How to log in:**
1. Run the ATM application.
2. Enter one of the demo account numbers.
3. Enter its corresponding PIN.
4. Select an operation from the ATM menu.

**Important:** These credentials are for a demonstration environment only.

### 6. Use the local ATM interface

The `atm.exe` executable also starts the local ATM interface. It includes account authentication and a menu for banking operations. Because this executable also starts the server, it is not a separate server-only executable.

## 🗄️ Database and Persistence

The application uses SQLite to store account records, including account number, account holder, balance and PIN.

- Account records can be loaded when the application starts.
- Updated account balances can be saved to the database.
- Saved account records can survive application restarts.
- Transaction history is currently maintained in memory and is not guaranteed to survive a restart.

## 🧠 Data Structures and Complexity

The `Bank` class uses `std::unordered_map` to associate account numbers with account objects.

- **Average account lookup:** \(O(1)\)
- **Worst-case account lookup:** \(O(n)\)
- **Vector linear search:** \(O(n)\) in the worst case

This choice makes average-case account lookup efficient when retrieving an account by its number. The actual performance depends on the number of accounts, hash distribution and workload.

## 🔒 Concurrency and Networking

The banking server uses TCP sockets to receive requests from ATM clients. Client connections are handled using separate threads, and a mutex is used to synchronise access to shared banking data.

This project demonstrates basic client-server communication and concurrency concepts. It is an educational implementation and has not been designed or audited for production banking security.

## 🔮 Future Improvements

- Persist transaction history in a dedicated SQLite table.
- Add networked money transfers and transaction-history requests.
- Implement database transactions using `BEGIN`, `COMMIT` and `ROLLBACK`.
- Improve request validation, error handling and network protocol framing.
- Store PIN credentials securely using an appropriate password/PIN hashing approach.
- Add comprehensive unit and integration tests.
- Improve automated builds and testing through CI/CD.

## 🎯 Learning Outcomes

Through this project, I have explored:

- Designing a layered C++ application.
- Applying OOP principles and managing object lifetimes.
- Selecting data structures based on time complexity.
- Implementing database persistence with SQLite.
- Building a TCP/IP client-server application.
- Handling concurrent client connections and shared resources.
- Debugging, compiling and managing a multi-file C++ project with CMake.

## ⚠️ Disclaimer

This project is intended for educational and portfolio purposes only. It is not a production-ready banking system. Do not use real customer credentials, real financial data or this application for actual banking transactions.

## 👨‍💻 Author

**Asim Iqbal**

Software Engineering student | C++ | Object-Oriented Programming | Data Structures | SQLite | Networking

---

*Built as a practical project to develop software engineering skills through C++, data structures, database persistence and client-server architecture.*