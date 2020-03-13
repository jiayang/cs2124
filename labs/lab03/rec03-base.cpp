/*
  rec03-base.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Client {
    friend ostream& operator<<(ostream& os, const Client& client) {
        cout << "Client: " << client.name
             << ", " << client.SSN;
        return os;
    }
public:
    Client(const string& aName, const string& aSSN)
        : name(aName), SSN(aSSN) {};

    string getName() const {
        return name;
    }
    string getSSN() const {
        return SSN;
    }
private:
    string name;
    string SSN;

};


//
// Task 1: The Account struct. Call it AccountS
//
struct AccountS {
    string name;
    int accountNumber;
};

//
// Task 2: The Account class. Call it AccountC
//
class AccountC {
    friend ostream& operator<<(ostream& os, const AccountC& account);
private:    
    string name;
    int accountNumber;
public:
    AccountC(const string& aName, int accNum) : name(aName), accountNumber(accNum) {};
    string getName() const {
        return name;
    }
    int getNum() const {
        return accountNumber;
    }
};


// 2.b: AccountC output operator, not a friend.
/*ostream& operator<<(ostream& os, const AccountC& account) {
    //cout << "Account: " << account.getName()
    //   << ", " << account.getNum();

    return os;
    }*/
// 2.2: AccountC output operator, reimplemented as a friend.

ostream& operator<<(ostream& os, const AccountC& account) {
    cout << "Account: " << account.name
         << ", " << account.accountNumber;
    return os;
}

//
// Task 3
//
// Transaction class definition
class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& trans);
public:
    Transaction(bool isDepo, int amt) {
        isDeposit = isDepo;
        val = amt;
    }
private:
    bool isDeposit;
    int val;
};

// Account class definition
class Account {
   friend ostream& operator<<(ostream& os, const Account& account);
private:    
    string name;
    int accountNumber;
    vector<Transaction> transactions;
    int balance;
public:
    Account(const string& aName, int accNum) : name(aName), accountNumber(accNum) {};
    string getName() const {
        return name;
    }
    int getNum() const {
        return accountNumber;
    }

    void deposit(int amt) {
        Transaction trans(true, amt);
        balance += amt;
        transactions.push_back(trans);
    }

    void withdrawal(int amt) {
        Transaction trans(false, amt);
        if (balance - amt < 0) {
            cout << "The account can not go negative"
                 << " Withdrawal of: " << amt << " was rejected." << endl;
        } else {
            balance -= amt;
            transactions.push_back(trans);
        }
    }
    

};


//
// Task 4
//
// Transaction class definition with embedded Account class
class AccountE {
    friend ostream& operator<<(ostream& os, const AccountE& account) {
        cout << "Account: " << account.client
             << ", " << account.accountNumber << endl;
        for (const AccountE::PrivateTransaction& trans : account.transactions) {
            cout << trans << endl;
        }
        return os;
    }
private:
    class PrivateTransaction {
    public:
        friend ostream& operator<<(ostream& os,
                                   const PrivateTransaction& trans) {
            cout << "Transaction: ";
            if (trans.isDeposit) {
                cout << "Deposit of ";
            } else {
                cout << "Withdrawal of ";
            }
            cout << trans.val;
            return os;
        }
        PrivateTransaction(bool isDepo, int amt) {
            isDeposit = isDepo;
            val = amt;
        }
    
    private:
        bool isDeposit;
        int val;
    };
    Client client;
    int accountNumber;
    vector<PrivateTransaction> transactions;
    int balance;
public:
    AccountE(const string& aName, const string& SSN, int accNum)
        : client(aName,SSN), accountNumber(accNum) {};
    string getName() const {
        return client.getName();
    }
    int getNum() const {
        return accountNumber;
    }

    void deposit(int amt) {
        PrivateTransaction trans(true, amt);
        balance += amt;
        transactions.push_back(trans);
    }

    void withdrawal(int amt) {
        PrivateTransaction trans(false, amt);
        if (balance - amt < 0) {
            cout << "The account can not go negative"
                 << " Withdrawal of: " << amt << " was rejected." << endl;
        } else {
            balance -= amt;
            transactions.push_back(trans);
        }
    }
    

};



ostream& operator<<(ostream& os, const Account& account) {
    cout << "Account: " << account.name
         << ", " << account.accountNumber << endl;
    for (const Transaction& trans : account.transactions) {
        cout << trans << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Transaction& trans) {
    cout << "Transaction: ";
    if (trans.isDeposit) {
        cout << "Deposit of ";
    } else {
        cout << "Withdrawal of ";
    }
    cout << trans.val;
    return os;
}

Account& findAccount(vector<Account>& accounts, int accNum) {
    for (Account& account : accounts) {
        if (account.getNum() == accNum) {
            return account;
        }
    }
    cerr << "Could not find the account with num: " << accNum;
}

AccountE& findAccount(vector<AccountE>& accounts, int accNum) {
    for (AccountE& account : accounts) {
        if (account.getNum() == accNum) {
            return account;
        }
    }
    cerr << "Could not find the account with num: " << accNum;
}
int main() {

    //
    // Task 1: account as struct
    //
    //      1a. Fill vector of account structs from file
    
    //cout << "Task1a:\n";
    // cout << "Filling vector of struct objects, define a local struct instance "
    //   << " and set fields explicitly:\n";

    ifstream ifs("accounts.txt");
    if (!ifs) {
        cerr << "Can't read accounts";
        exit(1);
    }
    ifs.close();
    /*vector<AccountS> accounts;
    string name;
    int accountNum;

    while(ifs >> name >> accountNum) {
        AccountS newAccount;
        newAccount.name = name;
        newAccount.accountNumber = accountNum;
        accounts.push_back(newAccount);
    }

    ifs.close();

    for (AccountS& account : accounts) {
        cout << "Account: " << account.name << ", "
             << account.accountNumber << endl;
    }
    
    
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";

    accounts.clear();
    ifs.open("accounts.txt");
    
    while(ifs >> name >> accountNum) {
        AccountS newAccount{name,accountNum};
        accounts.push_back(newAccount);
    }
    
    ifs.close();
    
    for (const AccountS& account : accounts) {
        cout << "Account: " << account.name << ", "
             << account.accountNumber << endl;
    }
    //==================================
    //
    // Task 2: account as class
    //

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    ifs.open("accounts.txt");
    vector<AccountC> accountsC;
    
    while(ifs >> name >> accountNum) {
        AccountC newAccount(name,accountNum);
        accountsC.push_back(newAccount);
    }
    
    ifs.close();
    
    for (const AccountC& account : accountsC) {
        cout << "Account: " << account.getName() << ", "
             << account.getNum() << endl;
    }

    cout << "---\n";
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    
    for (const AccountC& account : accountsC) {
        cout << account << endl;
    }
    
    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    // Note code here will be same as above.

    for (const AccountC& account : accountsC) {
        cout << account << endl;
    }
    
    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";

    accountsC.clear();
    ifs.open("accounts.txt");

    while(ifs >> name >> accountNum) {
        accountsC.push_back(AccountC(name,accountNum));
    }
    
    ifs.close();

    for (const AccountC& account : accountsC) {
        cout << account << endl;
    }
    
    cout << "\nTask2e:\n";
    cout << "\nFilling vector of class objects, using emplace_back:\n";

    accountsC.clear();
    ifs.open("accounts.txt");
    
    while(ifs >> name >> accountNum) {
        accountsC.emplace_back(name,accountNum);
    }
    
    ifs.close();
    
    for (const AccountC& account : accountsC) {
        cout << account << endl;
    }
    // Task 3
    cout << "==============\n";
    cout << "\nTask 3:\n\nAccounts and Transaction:\n";

    ifs.open("transactions.txt");
    vector<Account> accountsT;
    string command;

    while (ifs >> command) {
        if (command == "Account") {
            string name;
            int accNum;
            ifs >> name >> accNum;
            accountsT.emplace_back(name, accNum);
        }
        if (command == "Deposit") {
            int accNum;
            int amt;
            ifs >> accNum >> amt;
            Account& account = findAccount(accountsT, accNum);
            account.deposit(amt);
        }
        if (command == "Withdraw") {
            int accNum;
            int amt;
            ifs >> accNum >> amt;
            Account& account = findAccount(accountsT, accNum);
            account.withdrawal(amt);
        }



    }
    ifs.close();
    for (const Account& account : accountsT) {
        cout << account << endl;
    }

    // Task 4
    cout << "==============\n";
    cout << "\nTask 4:\n\nAccounts and Transaction:\n"
         << "Account class is nested inside Transaction class.\n";
    */
    ifs.open("transactions.txt");
    vector<AccountE> accountsE;
    string command;
    while (ifs >> command) {
        if (command == "Account") {
            string name;
            string SSN;
            int accNum;
            ifs >> name >> SSN >> accNum;
            accountsE.emplace_back(name, SSN, accNum);
        }
        if (command == "Deposit") {
            int accNum;
            int amt;
            ifs >> accNum >> amt;
            AccountE& account = findAccount(accountsE, accNum);
            account.deposit(amt);
        }
        if (command == "Withdraw") {
            int accNum;
            int amt;
            ifs >> accNum >> amt;
            AccountE& account = findAccount(accountsE, accNum);
            account.withdrawal(amt);
        }



    }
    
    for (const AccountE& account : accountsE) {
        cout << account << endl;
    }

    ifs.close();

}


