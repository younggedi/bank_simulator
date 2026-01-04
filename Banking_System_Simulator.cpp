#include"banking system simulator headerfile.h"
using namespace std;
vector<string> customer_account_number;
string drop;


vector<Account> customers;
Account user;
int main () {
	string line;
	cout<<"loading data... \n";
	// Open sample data file and load accounts into memory
	ifstream myfile;
	myfile.open ("sample_bank_data.csv",ifstream::in);
	if (!myfile.is_open()) {
        cout<< "Error: Unable to open file!" << endl;
        return 1;
	}
	while (getline(myfile, line)){
		if (line.empty()) {
		cout << "Error: Failed to read data" << endl;
		return 1;}
		stringstream ss(line);
		string word;
		vector<string> words;
		while(getline(ss, word, ','))words.push_back(word);
		user.allocate_information(words);
		customers.push_back(user);
		customer_account_number.push_back(words[2]);
	}
	myfile.close();
	// admin password kept in memory; can be changed via admin menu (current change function doesn't persist)
	string admin_password="younggedi123";
	string responce;
	l:;
	cout<<"are you accessing admin or customer account \n";
	cin>>responce;
	if(responce=="admin"){
		cout<<"please enter the admin password:";
		string admin_test;cin>>admin_test;
		if(admin_test==admin_password){
			cout<<"WELCOME ADMIN"<<endl;
		while(true){
			cout<<"select one of the following \n 1.) create_account \n 2.) delete_account \n 3.) display_accounts \n 4.) admin_exit \n";
			string admin_input;
			cin>>admin_input;
			adminchoices admin_process=stringToEnums(admin_input);
    		switch(admin_process){
    			case create_account:
					create_account_function(customer_account_number,customers);
    				break;
    			case delete_account:
					delete_account_function(customer_account_number,customers);
    				break;
    			case display_accounts:
					system ("cls"); //ascii escape sequence to clear screen
					display_accounts_function(customers);
    				break;
    			case admin_exit:
    				goto l;
    				break;
    			default:
    				cout<<"process not found"<<endl;
			}
		}
	}
	}
	else if (responce=="customer"){
		while(true){
			string account_number,PIN;
			cout<<"input account number:";
			cin>>account_number;
			cout<<endl;
			if(account_number=="exit")goto l;
			auto abc = find(customer_account_number.begin(), customer_account_number.end(), account_number);
			if (abc == customer_account_number.end()){
				cout<<"no account found"<<endl;
				continue;
			}
    		int customer_id=distance(customer_account_number.begin(), abc);
    		cout<<"enter your PIN:";
    		cin>>PIN;
    		cout<<endl;
    		if(customers[customer_id].check(PIN)){
    			while(true){
    				unsigned int amount;
    				cout<<"select one of the following \n 1.) deposit \n 2.) withdraw \n 3.) transfers \n 4.) balance \n 5.) exit \n";
    				string userInput;
					cin>>userInput;
    				choices process=stringToEnum(userInput);
    				switch(process){
    					case deposit:
    						cout<<"enter amount:";
    						cin>>amount;
    						cout<<endl;
    						customers[customer_id].deposit_funds(amount);
    						customers[customer_id].display_funds();
    						break;
    					case withdraw:
    						cout<<"enter amount:";
    						cin>>amount;
    						cout<<endl;
    						customers[customer_id].withdraw_funds(amount);
    						customers[customer_id].display_funds();
    						break;
    					case balance:
    						customers[customer_id].display_funds();
    						break;
    					case exits:
    						cout<<"THANK YOU FOR USING OUR BANK"<<endl;
    						Sleep(2000);
    						goto p;
    						break;
    					case transfers:
    						cout<<"enter amount:";
    						cin>>amount;
    						cout<<endl;
    						transfer(customer_id,amount,customer_account_number,customers);
    						customers[customer_id].display_funds();
    						break;
    					default:
    						cout<<"process not found"<<endl;
					}
				}
			}
			else cout<<"PIN is wrong";
			p:;
			std::cout << "\e[1;1H\e[2J"; //ascii escape sequence to clear screen
		}
	}
	else if(responce=="exit"){
		goto h;
	}
	else{
		goto l;
	}
	h:;
	// Save updated accounts to temporary file, replace original file
	ofstream mfile ("bank_data2.csv");
	for(int i=0;i<customer_account_number.size();i++){
		customers[i].print(drop);
	}
	mfile<<drop;
	mfile.close();
	remove("sample_bank_data.csv");
	rename("bank_data2.csv","sample_bank_data.csv");
	return 0;
}

