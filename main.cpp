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

void verifyInputValid(variant<string, float> &val){
    bool valValid = false;

    do{
        while(holds_alternative<string>(val) && get<string>(val).empty()){
            cout << endl << "If you want to exit, type 'exit'" << endl;
            cout << endl << "Please enter a valid number: ";
            val = getUserInput();
        }

        string inputSt = holds_alternative<string>(val) ? get<string>(val) : "";
        float inputInt = holds_alternative<float>(val) ? get<float>(val) : 0;


        for(char& c : inputSt) c = tolower(c);

        while(holds_alternative<string>(val) && inputSt != "exit"){
            cout << endl << "If you want to exit, type 'exit'" << endl;
            cout << endl << "Please enter a valid number: ";

            val = getUserInput();
            inputSt = holds_alternative<string>(val) ? get<string>(val) : "";
            inputInt = holds_alternative<float>(val) ? get<float>(val) : 0;
        }

        while(holds_alternative<float>(val) && inputInt < 0){
            cout << endl << "If you want to exit, type 'exit'" << endl;
            cout << endl << "Please enter a number positive: ";

            val = getUserInput();
            inputInt = holds_alternative<float>(val) ? get<float>(val) : 0;
            inputSt = holds_alternative<string>(val) ? get<string>(val) : "";
        }

        if(holds_alternative<float>(val) && inputInt > 0){
            valValid = true;
        }

        if(inputSt == "exit"){
            break;
            return;
        }
    }while(!valValid);
}

void deposit(float &bankBalance){
    cout << endl << "Enter the amount you wish to deposit: ";

    variant<string, float> valDeposit = getUserInput();

    verifyInputValid(valDeposit);

    float depositAmount = holds_alternative<float>(valDeposit) ? get<float>(valDeposit) : 0;

    bankBalance += depositAmount;

    cout << endl << "Deposited successfully!" << endl;
    cout << endl << "New balance: " << bankBalance << endl;
}

void withdraw(float &bankBalance){
    cout << endl << "enter the amount you wish to withdraw: ";

    variant<string, float> valWithdraw = getUserInput();
    
    verifyInputValid(valWithdraw);

    float withdrawAmount = holds_alternative<float>(valWithdraw) ? get<float>(valWithdraw) : 0;

    bankBalance -= withdrawAmount;

    cout << endl << "Withdrawn successfully!" << endl;
    cout << endl << "New balance: " << bankBalance << endl;
}

namespace DVariable{
    string optSelec;
}

int main(){
    float bankBalance = 9.35f;
    float compoundInterest;

    int optSelec;

    char exit = 'n';

    bool BBIsPositive = true;

    string options[] = {"Current balance", "deposit", "withdraw", "pay (compound) interest", "Exit"};

    do{
        BBIsPositive = (bool)(bankBalance > 0);

        cout << endl << "=== ATM ===" << endl << endl;

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
            case 3:
                withdraw(bankBalance);
                continue;
        }
    }while(exit == 'n');

    return 0;
}