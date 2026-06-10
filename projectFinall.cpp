#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Loan {
    string name;
    double intr_rate; // annual %
    int minYears;
    int maxYears;
    long minloan;
    long maxloan;
    long minincome;
};

//=========================BASE CLASS : BANK==============================
class Bank {
protected:
    string custName;
    string accountNo;
    double income;
    double amount;
    int duration;
    Loan loans[3];

public:
    Bank() { income = 0; amount = 0; duration = 0; }

    void setdata(int loanIndex, const string& name, const string& acc) {
        custName = name;
        accountNo = acc;

        cout << "\nMonthly average income (min required: " << loans[loanIndex].minincome << "): ";
        cin >> income;
        while (income < loans[loanIndex].minincome) {
            cout << "Income too low! Enter again: ";
            cin >> income;
        }

        cout << "Amount (" << loans[loanIndex].minloan << " - " << loans[loanIndex].maxloan << "): ";
        cin >> amount;
        while (amount < loans[loanIndex].minloan || amount > loans[loanIndex].maxloan) {
            cout << "Invalid amount. Enter again: ";
            cin >> amount;
        }

        cout << "Duration (" << loans[loanIndex].minYears << "-" << loans[loanIndex].maxYears << "): ";
        cin >> duration;
        while (duration < loans[loanIndex].minYears || duration > loans[loanIndex].maxYears) {
            cout << "Invalid duration. Enter again: ";
            cin >> duration;
        }

        double emi = calculateEMI(loanIndex);
        double remaining = amount;

        // Save to file using '|' delimiter
        ofstream fout("loans.txt", ios::app);
        fout << custName << "|" << accountNo << "|" << loans[loanIndex].name << "|"
             << amount << "|" << duration << "|" << emi << "|" << remaining << "\n";
        fout.close();
    }

    double calculateEMI(int loanIndex) {
        double R = loans[loanIndex].intr_rate / (12 * 100);
        int N = duration * 12;
        return (amount * R * pow(1 + R, N)) / (pow(1 + R, N) - 1);
    }

    virtual void displayLoans() = 0;
    virtual int getLoanChoice() = 0;

    void showSummary(int loanIndex) {
        double emi = calculateEMI(loanIndex);
        cout << "\n=============== LOAN SUMMARY ===============\n";
        cout << "Loan Type        : " << loans[loanIndex].name << endl;
        cout << "Customer Name    : " << custName << endl;
        cout << "Account Number   : " << accountNo << endl;
        cout << "Monthly Income   : " << income << " PKR\n";
        cout << "Requested Amount : " << amount << " PKR\n";
        cout << "Interest Rate    : " << loans[loanIndex].intr_rate << "%\n";
        cout << "Duration         : " << duration << " years\n";
        cout << "Calculated EMI   : " << emi << " PKR / month\n";
        cout << "===========================================\n";
    }
};

//=========================DERIVED CLASSES==============================
class UBLbank : public Bank {
public:
    UBLbank() {
        loans[0] = {"Car Loan", 13.0, 1, 5, 200000, 3000000, 40000};
        loans[1] = {"Home Loan", 11.0, 5, 25, 200000, 2000000, 60000};
        loans[2] = {"Personal Loan", 18.0, 1, 4, 10000, 600000, 30000};
    }
    void displayLoans() override {
        cout << "======UBL-BANK======\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << loans[i].name << " | " << loans[i].intr_rate << "% | Amount: "
                 << loans[i].minloan << "-" << loans[i].maxloan << " | Duration: "
                 << loans[i].minYears << "-" << loans[i].maxYears << " years | Min Income: "
                 << loans[i].minincome << "\n";
        }
        cout << "4. Go back\n";
    }
    int getLoanChoice() override {
        int choice;
        cout << "Enter loan choice (1-4): ";
        cin >> choice;
        while (choice < 1 || choice > 4) {
            cout << "Invalid choice. Enter again: ";
            cin >> choice;
        }
        return choice;
    }
};

class MCBbank : public Bank {
public:
    MCBbank() {
        loans[0] = {"Agriculture Loan", 14.0, 1, 6, 200000, 1500000, 35000};
        loans[1] = {"Home Loan", 10.9, 5, 25, 800000, 20000000, 70000};
        loans[2] = {"Travel Loan", 16.5, 1, 3, 100000, 700000, 30000};
    }
    void displayLoans() override {
        cout << "======MCB-BANK======\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << loans[i].name << " | " << loans[i].intr_rate << "% | Amount: "
                 << loans[i].minloan << "-" << loans[i].maxloan << " | Duration: "
                 << loans[i].minYears << "-" << loans[i].maxYears << " years | Min Income: "
                 << loans[i].minincome << "\n";
        }
        cout << "4. Go back\n";
    }
    int getLoanChoice() override {
        int choice;
        cout << "Enter loan choice (1-4): ";
        cin >> choice;
        while (choice < 1 || choice > 4) {
            cout << "Invalid choice. Enter again: ";
            cin >> choice;
        }
        return choice;
    }
};

class HBLbank : public Bank {
public:
    HBLbank() {
        loans[0] = {"Business Loan", 12.5, 2, 7, 100000, 3000000, 45000};
        loans[1] = {"Home Loan", 10.5, 5, 20, 700000, 30000000, 65000};
        loans[2] = {"Education Loan", 9.0, 1, 5, 50000, 500000, 25000};
    }
    void displayLoans() override {
        cout << "======HBL-BANK======\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << loans[i].name << " | " << loans[i].intr_rate << "% | Amount: "
                 << loans[i].minloan << "-" << loans[i].maxloan << " | Duration: "
                 << loans[i].minYears << "-" << loans[i].maxYears << " years | Min Income: "
                 << loans[i].minincome << "\n";
        }
        cout << "4. Go back\n";
    }
    int getLoanChoice() override {
        int choice;
        cout << "Enter loan choice (1-4): ";
        cin >> choice;
        while (choice < 1 || choice > 4) {
            cin >> choice;
        }
        return choice;
    }
};

//=================== CHECK ACTIVE LOAN ===================
bool hasActiveLoan(const string& name, const string& acc) {
    ifstream fin("loans.txt");
    if (!fin) return false;

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string fileName, fileAcc, loanType;
        double amount, emi, remaining;
        int duration;

        getline(ss, fileName, '|');
        getline(ss, fileAcc, '|');
        getline(ss, loanType, '|');
        ss >> amount; ss.ignore();
        ss >> duration; ss.ignore();
        ss >> emi; ss.ignore();
        ss >> remaining;

        if (fileName == name && fileAcc == acc && remaining > 0) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

//=================== PAY INSTALLMENT FUNCTION ===================
void payInstallment() {
    cin.ignore();
    string inputName, inputAcc;
    cout << "Enter your full name: ";
    getline(cin, inputName);
    cout << "Enter your account number: ";
    cin >> inputAcc;

    ifstream fin("loans.txt");
    if (!fin) {
        cout << "No loans found.\n";
        return;
    }

    ofstream temp("temp.txt");
    bool found = false;
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        string fileName, fileAcc, loanType;
        double amount, emi, remaining;
        int duration;

        getline(ss, fileName, '|');
        getline(ss, fileAcc, '|');
        getline(ss, loanType, '|');
        ss >> amount; ss.ignore();
        ss >> duration; ss.ignore();
        ss >> emi; ss.ignore();
        ss >> remaining;

        if (!found && fileName == inputName && fileAcc == inputAcc) {
            found = true;
            cout << "Loan found: " << loanType << "\n";
            cout << "Remaining balance: " << remaining << " | EMI: " << emi << "\n";

            double pay;
            cout << "Enter installment to pay: ";
            cin >> pay;
            if (pay > remaining) pay = remaining;
            remaining -= pay;
            cout << "Remaining balance after payment: " << remaining << "\n";
        }

        temp << fileName << "|" << fileAcc << "|" << loanType << "|"
             << amount << "|" << duration << "|" << emi << "|" << remaining << "\n";
    }

    fin.close();
    temp.close();
    remove("loans.txt");
    rename("temp.txt", "loans.txt");

    if (!found)
        cout << "Loan not found for given name and account number.\n";
}

//=================== MAIN ===================
int main() {

    int choice;
    cout<<"\n_________BANK LOAN MANAGEMENT SYSTEM_____________\n";
    do {
        cout << "\n1. Get Loan\n2. Pay Installment\n3. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 3) break;

        if (choice == 2) {
            system("cls");
            payInstallment();
            continue;
        }

        if (choice == 1) {
            cin.ignore();
            string tempName, tempAcc;
            cout << "Enter your full name: ";
            getline(cin, tempName);
            cout << "Enter your account number: ";
            cin >> tempAcc;

            if (hasActiveLoan(tempName, tempAcc)) {
                cout << "\nYou already have an active loan! Cannot take another until previous is fully paid.\n";
                continue;
            }

            Bank* bank1;
            int Lindex = 0, banktype;

            do {
                cout << "_CHOOSE BANK FOR LOAN_\n1. UBL\n2. HBL\n3. MCB\nEnter choice: ";
                cin >> banktype;
                while (banktype < 1 || banktype > 3) {
                    cout << "Invalid choice. Enter again: ";
                    cin >> banktype;
                }
                system("cls");

                if (banktype == 1) bank1 = new UBLbank();
                else if (banktype == 2) bank1 = new HBLbank();
                else bank1 = new MCBbank();

                bank1->displayLoans();
                Lindex = bank1->getLoanChoice();
                if (Lindex == 4) delete bank1;
                system("cls");
            } while (Lindex == 4);

            --Lindex;
            bank1->setdata(Lindex, tempName, tempAcc);
            system("cls");
            bank1->showSummary(Lindex);
            delete bank1;
        }

    } while (true);

    return 0;
}
