#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Some sample first and last names
vector<string> first_names = {
    "Alice","Bob","Charlie","Diana","Ethan","Fiona","George","Hannah",
    "Ian","Julia","Kevin","Laura","Michael","Nina","Oscar","Paula","Quincy",
    "Rachel","Sam","Tina","Umar","Vera","William","Xavier","Yara","Zane",
    "Adam","Bella","Caleb","Daisy","Eli","Faith","Gavin","Hailey","Isaac",
    "Jade","Kyle","Lily","Mason","Nora","Owen","Piper","Quinn","Riley",
    "Sophia","Tyler","Uma","Victor","Wendy","Ximena"
};

vector<string> last_names = {
    "Johnson","Smith","Brown","Prince","Hunt","Davis","Miller","Wilson",
    "Clark","Roberts","Adams","Martinez","Jordan","Thomas","Wright","Scott",
    "Allen","Evans","Taylor","Lewis","Khan","Lopez","King","Lee","Gomez",
    "Harris","Parker","Carter","Green","White","Turner","Brooks","Hughes",
    "Barnes","Cook","Collins","Reed","Stewart","Price","Rogers","Russell",
    "Wood","Bell","Ward","Gray","Diaz","Patel","Ross","Fisher","Stone"
};

int main() {
    srand(time(0)); // Seed random numbers
    
    ofstream file("sample_bank_data.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return 1;
    }

    int total_entries = 500; // You can change this number as needed
    int start_account_number = 100; // So it doesn't overlap with your old file

    for (int i = 0; i < total_entries; i++) {
        string first = first_names[rand() % first_names.size()];
        string last = last_names[rand() % last_names.size()];
        int acc_num = start_account_number + i;
        int pin = 1000 + rand() % 9000; // random 4-digit PIN
        double balance = (100.0 + (rand() % 990000) / 100.0); // between 100 and 10,000

        file << first << "," << last << "," << acc_num << "," << pin 
             << "," << fixed << setprecision(6) << balance << "\n"; // double newline for gap
    }

    file.close();
    cout << "Generated " << total_entries << " entries in generated_bank_data.csv" << endl;
    return 0;
}

