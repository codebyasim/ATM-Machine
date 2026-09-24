cmake_minimum_required(VERSION 3.15)

project(ATM_Machine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sqlite3 sqlite3.c)

add_executable(atm
    simple_atm.cpp
    Account.cpp
    Transaction.cpp
    Bank.cpp
    SavingsAccount.cpp
    Database.cpp
)

target_include_directories(atm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(atm PRIVATE
    sqlite3
)