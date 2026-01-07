Banking System Simulator
========================
Simple console-based banking simulator written in C++.
Supports admin operations (create/delete/list accounts) and customer operations
(deposit, withdraw, transfer, check balance). Data is stored in CSV files.

Quick Start (Windows)
---------------------
1. Build:
   g++ -std=c++17 "Banking_System_Simulator.cpp" -o bank_simulator

2. Run:
   .\bank_simulator.exe

Files
-----
- Banking_System_Simulator.cpp: main program and console UI.
- banking system simulator headerfile.h: Account class, helpers, and IO functions.
- unique_entry_generator.cpp: optional helper to generate sample data.
- sample_bank_data.csv: initial account data read at startup.
- customer_log.csv: append-only transaction log created during runtime.
- README.txt: this file.

Usage
-----
- On start, choose "admin" or "customer".
- Admin menu: create_account, delete_account, display_accounts, admin_exit.
  (Numeric shortcuts like 1,2,3,4 are accepted.)
- Customer flow: authenticate with account number and PIN, then choose
  deposit, withdraw, transfers, balance, or exit (numeric shortcuts supported).

Data format
-----------
CSV columns: first_name,last_name,account_number,pin,account_balance

Notes
-----
- Default admin password is "younggedi123" (stored in-memory only).
- Changes to the admin password are not persisted.
- On exit, sample_bank_data.csv is overwritten with in-memory account state.

License
-------
Use for personal/educational purposes. No warranty.
