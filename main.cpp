#include <iostream>
#include <ctime>
#include <optional>
#include <limits>
#include <variant>
#include <sstream>

using namespace std;

variant<string, float> getUserInput(){
    string enter;
    getline(cin, enter);

    istringstream iss(enter);
    float number;

    if(iss >> number && iss.eof()){
        return number;
    }

    return enter;
}

void deposit(float &bankBalance){
    cout << endl << "Enter the amount you wish to deposit: ";

    variant<string, float> valDeposit = getUserInput();

    while(holds_alternative<string>(valDeposit) && get<string>(valDeposit).empty()){
        cout << endl << "If you want to exit, type 'exit'" << endl;
        cout << endl << "Please enter a valid number: ";
        valDeposit = getUserInput();
    }

    string input = holds_alternative<string>(valDeposit) ? get<string>(valDeposit) : "";

    for(char& c : input) c = tolower(c);

    while(holds_alternative<string>(valDeposit) && input != "exit"){
        cout << endl << "If you want to exit, type 'exit'" << endl;
        cout << endl << "Please enter a valid number: ";

        valDeposit = getUserInput();
        input = get<string>(valDeposit);
    }

    if(input == "exit"){
        return;
    }

    if(holds_alternative<float>(valDeposit)){
        float depositAmount = get<float>(valDeposit);

        if(depositAmount < 0){
            cout << endl << "If you want to withdraw an amount, type 'exit' and then type 3." << endl;
            valDeposit = getUserInput();

            return;
        }

        bankBalance += depositAmount;

        cout << endl << "Deposited successfully!" << endl;
        cout << endl << "New balance: " << bankBalance << endl;
        return;
    }
}

namespace DVariable{
    string optSelec;
}

int main(){
    float bankBalance = 9.35f;
    float compoundInterest;

    int optSelec;

    //* Variable to check if the user who withdraws money with a negative balance
    float pauseBankBalence;

    char exit = 'n';

    bool BBIsPositive = true;

    string options[] = {"Current balance", "deposit", "withdraw", "pay (compound) interest", "Exit"};

    do{
        BBIsPositive = (bool)(bankBalance > 0);

        cout << endl << "=== ATM ===" << endl << endl;

        //* Check if the user has a negative balance. If so, remove item number 3 (compound interest)
        for(int i = 0; i < sizeof(options) / sizeof(options[0]); i++){
            if(BBIsPositive && i == 3){
                cout << "";
            }else{
                if(BBIsPositive && i == sizeof(options) / sizeof(options[0]) - 1){
                    cout << i << '.' << options[i] << endl;
                }else{
                    cout << i + 1 << '.' << options[i] << endl;
                }
            }
        }

        istringstream iss(DVariable::optSelec);

        cout << endl << "Select an option: ";
        getline(cin, DVariable::optSelec);
        iss.clear();
        iss.str(DVariable::optSelec);
        iss >> optSelec;

        while(iss.fail() || optSelec < 1 || optSelec > 5){
            cout << "Please enter a valid number (1-4): ";
            getline(cin, DVariable::optSelec);
            iss.clear();
            iss.str(DVariable::optSelec);
            iss >> optSelec;
        }

        switch(optSelec){
            case 1:
                cout << endl << "Current balance: " << bankBalance << endl;
                continue;
            case 2:
                deposit(bankBalance);
                continue;
        }
    }while(exit == 'n');

    return 0;
}