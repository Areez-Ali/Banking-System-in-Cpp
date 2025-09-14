#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_ACCOUNTS = 100;
struct Account {
    int accountNumber;
    string name;
    double balance; };
Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;
int findAccountIndex(int accNo) {
    for (int i = 0; i < totalAccounts; ++i) {
        if (accounts[i].accountNumber == accNo) return i;
    }
    return -1;
}
int promptForAccountIndexWithRetry() {
    while (true) {
        cout << "Enter Account Number (or 0 to cancel): ";
        int accNo;
        if (!(cin >> accNo)) {
            cout << "Invalid input. Please enter digits only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (accNo == 0) return -1; // cancel
        int idx = findAccountIndex(accNo);
        if (idx != -1) return idx;
        cout << "❌ Account not found. Try again or enter 0 to cancel.\n";
    }}
void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        cout << "Sorry, maximum number of accounts reached.\n";
        return; }
    int accNo;
    while (true) {
        cout << "\nEnter Account Number: ";
        if (!(cin >> accNo)) {
            cout << "Invalid input. Enter digits only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (findAccountIndex(accNo) != -1) {
            cout << "That account number already exists. Choose a different number.\n";
            continue;
        }
        break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Account newAcc;
    newAcc.accountNumber = accNo;
    cout << "Enter Account Holder Name: ";
    getline(cin, newAcc.name);

    cout << "Enter Initial Deposit: ";
    while (!(cin >> newAcc.balance) || newAcc.balance < 0) {
        cout << "Enter a valid non-negative amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    accounts[totalAccounts++] = newAcc;
    cout << "✅ Account Created Successfully!\n";
}
void depositMoney() {
    int idx = promptForAccountIndexWithRetry();
    if (idx == -1) { cout << "Operation cancelled.\n"; return; }

    double amount;
    cout << "Enter Amount to Deposit: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Enter a valid positive amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    accounts[idx].balance += amount;
    cout << "✅ Deposit Successful! New Balance: " << accounts[idx].balance << endl;
}
void withdrawMoney() {
    int idx = promptForAccountIndexWithRetry();
    if (idx == -1) { cout << "Operation cancelled.\n"; return; }

    double amount;
    cout << "Enter Amount to Withdraw: ";
    while (!(cin >> amount) || amount <= 0) {
        cout << "Enter a valid positive amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (amount <= accounts[idx].balance) {
        accounts[idx].balance -= amount;
        cout << "✅ Withdrawal Successful! Remaining Balance: " << accounts[idx].balance << endl;
    } else {
        cout << "❌ Insufficient Balance! Current Balance: " << accounts[idx].balance << endl;
    }
}
void checkBalance() {
    int idx = promptForAccountIndexWithRetry();
    if (idx == -1) { cout << "Operation cancelled.\n"; return; }
    cout << "Account Holder: " << accounts[idx].name << endl;
    cout << "Balance: " << accounts[idx].balance << endl;
}



int main() {
    int choice;
    do {
        cout << "\n====== Banking System Menu ======\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number 1-5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: cout << "Exiting... Thank you!\n"; break;
            default: cout << "❌ Invalid Choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}
