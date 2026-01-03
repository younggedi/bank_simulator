#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include<windows.h>
#include <iomanip>
using namespace std;


class Account{
	private:
		string first_name;
		string last_name;
		double account_balance;
		string pin;
		string account_number;
	public:
		void transfer_funds();
		void deposit_funds(unsigned int amount){
			account_balance+=amount;
		}
		void withdraw_funds(unsigned int amount){
			if(amount>account_balance){
				cout<<"insufficient funds";
			}
			else account_balance-=amount;
		}
		
		void allocate_information(vector<string> &words){
			first_name=words[0];
			last_name=words[1];
			account_number=words[2];
			pin=words[3];
			account_balance=stod(words[4]);

		}
		void display_funds() const{
			cout<<fixed<<setprecision(2);
			cout<<"your current account balance is:"<<account_balance<<endl;
		}
		bool check(const string &PIN) const{
			return PIN==pin;
		}
		void print(string &drop) const{
    		ostringstream oss;
			oss<<fixed<<setprecision(2)<<account_balance;
			drop+=first_name+" "+last_name+" "+account_number+" "+pin+" "+oss.str()+"\n";
		}
};



enum choices{
	deposit, withdraw, transfers, balance, exits, unknown
};

// added: admin choices for administrative operations
enum adminchoices{
	create_account,
	delete_account,
	change_password,
	admin_exit,
	admin_unknown
};

choices stringToEnum(const std::string& input) {
	static std::unordered_map<std::string, choices> choicesMap = {
		{"deposit", choices::deposit},
		{"withdraw", choices::withdraw},
		{"transfers", choices::transfers},
		{"balance", choices::balance},
		{"exit", choices::exits}
	};

	auto it = choicesMap.find(input);
	return (it != choicesMap.end()) ? it->second : choices::unknown;
}
adminchoices stringToEnums(const std::string& input) {
	static std::unordered_map<std::string, adminchoices> adminchoicesMap = {
		{"create_account", adminchoices::create_account},
		{"delete_account", adminchoices::delete_account},
		{"change_password", adminchoices::change_password},
		{"admin_exit", adminchoices::admin_exit}
	};

	auto it = adminchoicesMap.find(input);
	return (it != adminchoicesMap.end()) ? it->second : adminchoices::admin_unknown;
}

void transfer(int &i,unsigned int&amount, vector<string>&customer_account_number ,vector<Account>&customers){
	cout<<"enter the account number of the recipient:";
	string account_number_recipient;
    cin>>account_number_recipient;
	auto abcd = find(customer_account_number.begin(), customer_account_number.end(), account_number_recipient);
	if (abcd == customer_account_number.end()){
		cout<<"no account found"<<endl;
		return ;
	}
    int recipient_id=distance(customer_account_number.begin(), abcd);
	customers[i].withdraw_funds(amount);
	customers[recipient_id].deposit_funds(amount);
	return ;
}

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

void change_password_function(string password){
	string new_password;
	cout<<"enter new password:";
	cin>>new_password;
	password=new_password;
	cout<<"password changed successfully."<<endl;

}