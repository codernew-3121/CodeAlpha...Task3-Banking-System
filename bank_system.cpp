#include <bits/stdc++.h>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;       // Deposit, Withdrawal, Transfer
    double amount;
    string details;

    Transaction(string t, double a, string d)
        : type(t), amount(a), details(d) {}
};

// Account class
class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(string accNum) : accountNumber(accNum), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount, "Deposited"));
        cout << "₹" << amount << " deposited to " << accountNumber << ".\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance in " << accountNumber << ".\n";
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdrawal", amount, "Withdrawn"));
        cout << "₹" << amount << " withdrawn from " << accountNumber << ".\n";
        return true;
    }

    bool transfer(Account &to, double amount) {
        if (withdraw(amount)) {
            to.deposit(amount);
            history.push_back(Transaction("Transfer", amount, "To " + to.accountNumber));
            cout << "₹" << amount << " transferred to " << to.accountNumber << ".\n";
            return true;
        }
        return false;
    }

    void showRecentTransactions(int count = 5) const {
        cout << "\nRecent Transactions for " << accountNumber << ":\n";
        int start = max(0, (int)history.size() - count);
        for (int i = start; i < history.size(); ++i) {
            cout << history[i].type << " ₹" << fixed << setprecision(2) << history[i].amount
                 << " (" << history[i].details << ")\n";
        }
    }

    void displayInfo() const {
        cout << "\nAccount: " << accountNumber
             << "\nBalance: ₹" << fixed << setprecision(2) << balance << "\n";
        showRecentTransactions();
    }

    string getAccountNumber() const { return accountNumber; }
};

// Customer class
class Customer {
private:
    string name;
    string customerID;
    vector<Account> accounts;

public:
    Customer(string n, string id) : name(n), customerID(id) {}

    void createAccount(string accNum) {
        accounts.push_back(Account(accNum));
        cout << "Account " << accNum << " created for " << name << ".\n";
    }

    Account* getAccount(string accNum) {
        for (auto &acc : accounts)
            if (acc.getAccountNumber() == accNum)
                return &acc;
        cout << "Account " << accNum << " not found.\n";
        return nullptr;
    }

    void displayAccounts() const {
        cout << "\nCustomer: " << name << " (ID: " << customerID << ")\n";
        for (const auto &acc : accounts)
            acc.displayInfo();
    }
};

// Main function
int main() {
    Customer John("John", "C001");

    John.createAccount("A1001");
    John.createAccount("A1002");

    Account* acc1 = John.getAccount("A1001");
    Account* acc2 = John.getAccount("A1002");

    if (acc1 && acc2) {
        acc1->deposit(5000);
        acc1->withdraw(1200);
        acc1->transfer(*acc2, 1000);
    }

    John.displayAccounts();

    return 0;
}




