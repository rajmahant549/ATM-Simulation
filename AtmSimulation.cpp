#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class ATM {
private:
    int pin;
    int enteredPin;
    double balance;

public:
    ATM() {
        pin = 1234;
        balance = 0;
    }

    void login() {
        cout << "\n        ATM SIMULATION SYSTEM";
        cout << "\n====================================";

        cout << "\nEnter Your PIN: ";
        cin >> enteredPin;

        if (enteredPin == pin) {
            cout << "\nLogin Successful!";
            menu();
        } else {
            cout << "\nIncorrect PIN!";
            cout << "\nAccess Denied!";
        }
    }

    void menu() {
        int choice;

        do {
            cout << "\n\n= MAIN MENU =";
            cout << "\n1. Balance Inquiry";
            cout << "\n2. Cash Withdrawal";
            cout << "\n3. Deposit Money";
            cout << "\n4. Transaction Report";
            cout << "\n5. Exit";
            cout << "\nEnter Your Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    checkBalance();
                    break;

                case 2:
                    withdrawMoney();
                    break;

                case 3:
                    depositMoney();
                    break;

                case 4:
                    transactionReport();
                    break;

                case 5:
                    cout << "\nThank You For Using ATM!";
                    cout << "\nPlease Collect Your Card.\n";
                    break;

                default:
                    cout << "\nInvalid Choice!";
            }

        } while (choice != 5);
    }

    void checkBalance() {
        cout << "\nCurrent Balance: Rs. " << fixed << setprecision(2) << balance;

        saveTransaction("Balance Inquiry", 0);
    }

    void withdrawMoney() {
        double amount;

        cout << "\nEnter Amount to Withdraw: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "\nInvalid Amount!";
        }
        else if (amount > balance) {
            cout << "\nInsufficient Balance!";
        }
        else {
            balance -= amount;

            cout << "\nPlease Collect Your Cash.";
            cout << "\nRemaining Balance: Rs. " << balance;

            saveTransaction("Withdrawal", amount);
        }
    }

    void depositMoney() {
        double amount;

        cout << "\nEnter Amount to Deposit: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "\nInvalid Amount!";
        }
        else {
            balance += amount;

            cout << "\nAmount Deposited Successfully!";
            cout << "\nUpdated Balance: Rs. " << balance;

            saveTransaction("Deposit", amount);
        }
    }

    void saveTransaction(string type, double amount) {
        ofstream file("transactions.txt", ios::app);

        file << "\nTransaction Type : " << type;
        file << "\nAmount           : Rs. " << amount;
        file << "\nAvailable Balance: Rs. " << balance;
        file << "\n-----------------------------------";

        file.close();
    }

    void transactionReport() {
        ifstream file("transactions.txt");

        string line;

        cout << "\n========== TRANSACTION REPORT ==========\n";

        if (!file) {
            cout << "No Transaction Records Found!\n";
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

int main() {
    ATM user;

    user.login();

    return 0;
}