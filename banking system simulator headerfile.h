#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include<windows.h>
#include <iomanip>
#include <chrono>
#include <ctime>
using namespace std;

string currentDateTime() {
	auto now = chrono::system_clock::now();
	time_t now_time_t = chrono::system_clock::to_time_t(now);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now_time_t));
	return string(buf);
}

// Account models a single customer's bank account and operations on it.
class Account{
	private:
		string first_name;
		string last_name;
		double account_balance;
		string pin;
		string account_number;
	public:
		void transfer_funds();
		// deposit_funds: increase balance by amount (unsigned int used for non-negative amounts)
		void deposit_funds(unsigned int amount,ostream &customerfile){
			account_balance+=amount;
			customerfile<<account_number<<","<<amount<<","<<"deposit,"<<currentDateTime()<<endl;
		}
		// withdraw_funds: subtract amount if sufficient balance, otherwise notify user
		void withdraw_funds(unsigned int amount,ostream &customerfile){
			if(amount>account_balance){
				cout<<"insufficient funds";
			}
			else account_balance-=amount;
			customerfile<<account_number<<","<<amount<<","<<"withdrawal,"<<currentDateTime()<<endl;
		}
		
		// allocate_information: initialize account fields from a vector of strings
		void allocate_information(vector<string> &words){
			first_name=words[0];
			last_name=words[1];
			account_number=words[2];
			pin=words[3];
			account_balance=stod(words[4]);

		}
		// display_funds: print balance with two decimal places
		void display_funds() const{
			cout<<fixed<<setprecision(2);
			cout<<"your current account balance is:"<<account_balance<<endl;
		}
		// check: verify provided PIN matches account PIN
		bool check(const string &PIN) const{
			return PIN==pin;
		}
		// print: append account data to a provided string (used when saving all accounts)
		void print(string &drop) const{
    		ostringstream oss;
			oss<<fixed<<setprecision(2)<<account_balance;
			drop+=first_name+","+last_name+","+account_number+","+pin+","+oss.str()+"\n";
		}
		// display_account: print account details (for admin use)
		void display_account() const{
			cout<<"Account Holder: "<<first_name<<" "<<last_name<<endl;
			cout<<"Account Number: "<<account_number<<endl;
			cout<<fixed<<setprecision(2)<<"Account Balance: "<<account_balance<<endl;
			cout<<"-----------------------------------"<<endl;
		}
};



// choices: operations available to customers
enum choices{
	deposit, withdraw, transfers, balance, exits, unknown
};

// adminchoices: operations available to admin
enum adminchoices{
	create_account,
	delete_account,
	display_accounts,
	admin_exit,
	admin_unknown
};

// stringToEnum: convert input string to customer choice enum (safe fallback to unknown)
choices stringToEnum(const std::string& input) {
	static std::unordered_map<std::string, choices> choicesMap = {
		{"deposit", choices::deposit},
		{"withdraw", choices::withdraw},
		{"transfers", choices::transfers},
		{"balance", choices::balance},
		{"exit", choices::exits},
		// numeric menu shortcuts
		{"1", choices::deposit},
		{"2", choices::withdraw},
		{"3", choices::transfers},
		{"4", choices::balance},
		{"5", choices::exits}
	};

	auto it = choicesMap.find(input);
	return (it != choicesMap.end()) ? it->second : choices::unknown;
}
// stringToEnums: convert admin input string to adminchoice enum
adminchoices stringToEnums(const std::string& input) {
	static std::unordered_map<std::string, adminchoices> adminchoicesMap = {
		{"create_account", adminchoices::create_account},
		{"delete_account", adminchoices::delete_account},
		{"display_accounts", adminchoices::display_accounts},
		{"admin_exit", adminchoices::admin_exit},
		// numeric menu shortcuts
		{"1", adminchoices::create_account},
		{"2", adminchoices::delete_account},
		{"3", adminchoices::display_accounts},
		{"4", adminchoices::admin_exit}
	};

	auto it = adminchoicesMap.find(input);
	return (it != adminchoicesMap.end()) ? it->second : adminchoices::admin_unknown;
}

// transfer: move funds from customer i to a recipient found by account number
void transfer(int &i,unsigned int&amount, vector<string>&customer_account_number ,vector<Account>&customers,ostream &customerfile){
	cout<<"enter the account number of the recipient:";
	string account_number_recipient;
    cin>>account_number_recipient;
	auto abcd = find(customer_account_number.begin(), customer_account_number.end(), account_number_recipient);
	if (abcd == customer_account_number.end()){
		cout<<"no account found"<<endl;
		return ;
	}
    int recipient_id=distance(customer_account_number.begin(), abcd);
	// withdraw from sender and deposit to recipient
	customers[i].withdraw_funds(amount, customerfile);
	customers[recipient_id].deposit_funds(amount, customerfile);
	return;
}

// create_account_function: gather input and create a new Account, ensuring unique account number
void create_account_function(vector<string>&customer_account_number,vector<Account>&customers){
	customers.push_back(Account());
	vector<string>create;
	string responses;
	cout<<"enter first name:";
	cin>>responses;
	create.push_back(responses);
	cout<<"enter last name:";
	cin>>responses;
	create.push_back(responses);
	z:;
	cout<<"enter account number:";
	cin>>responses;
	auto abc = find(customer_account_number.begin(), customer_account_number.end(), responses);
	if (abc != customer_account_number.end()){
		cout<<"account already exists"<<endl;
		goto z;
		}
	create.push_back(responses);
	customer_account_number.push_back(responses);
	cout<<"enter pin:";
	cin>>responses;
	create.push_back(responses);
	cout<<"enter initial deposit amount:";
	cin>>responses;
	create.push_back(responses);
	customers.back().allocate_information(create);
}	

// delete_account_function: remove account by account number if found
void delete_account_function(vector<string>&customer_account_number,vector<Account>&customers){
	string account_number;
	cout<<"enter the account number to delete:";
	cin>>account_number;
	auto it = find(customer_account_number.begin(), customer_account_number.end(), account_number);
	if (it != customer_account_number.end()) {
		int index = distance(customer_account_number.begin(), it);
		customer_account_number.erase(it);
		customers.erase(customers.begin() + index);
		cout<<"account deleted successfully."<<endl;
	}
	else{
		cout<<"account not found."<<endl;
	}
}

// change_password_function: change the admin password (note: current implementation modifies local copy)
void display_accounts_function(vector<Account>&customers){
	cout<<"-----------------------------------"<<endl;
	for(int i=0;i<customers.size();i++){
		customers[i].display_account();
	}
}

void read_csv_file(istream &myfile, vector<Account>&customers, vector<string>&customer_account_number, Account &user){
	string line;
	while (getline(myfile, line)) {
		vector<string> words;
		string word;
		istringstream s(line);
		while (getline(s, word, ',')) {
			words.push_back(word);
		}
		user.allocate_information(words);
		customers.push_back(user);
		customer_account_number.push_back(words[2]);
	}
}

void write_csv_file(ostream &mfile, vector<Account>&customers, string &drop){
	for(int i=0;i<customers.size();i++){
		customers[i].print(drop);
	}
	mfile<<drop;
	
}