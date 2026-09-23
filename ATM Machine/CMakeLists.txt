cmake_minimum_required(VERSION 3.15)

project(ATM_Machine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(atm
    simple_atm.cpp
    Account.cpp
    Transaction.cpp
    Bank.cpp
    SavingsAccount.cpp
    Database.cpp
)

target_include_directories(atm PRIVATE
    "C:/Users/iasim/anaconda3/Library/include"
)

target_link_directories(atm PRIVATE
    "C:/Users/iasim/anaconda3/Library/lib"
)

target_link_libraries(atm PRIVATE
    sqlite3
)