#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowATM_MainMenue();
void GoBackToMainMenue();
void Login();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;

};

sClient currentClient;

enum enATM_MainMenueOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposite = 3, CheckBalance = 4, eLogout = 5 };

enum enQuickWithdraw { e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5, e600 = 6, e800 = 7, e1000 = 8, eexit = 9 };

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadQuickWithdrawOption()
{
    cout << "Choose what do you want to do? [1 to 9]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowATM_MainMenue();

}

void showendscreen()
{
    cout << "======| End Screeen |=======\n\n";
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

string ReadClientPinCode()
{
    string Password = "";

    cout << "\n enter PinCode ? ";
    getline(cin >> ws, Password);

    return Password;

}

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}


bool FindClientByAccountNumberEndPincode(string AccountNumber, string PinCode, sClient& Client)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }

    }
    return false;

}
//==================================================//

void CalulateQuickWithdraw(int num)
{
    char answer = 'n';

    cout << "\n Are you sure, you want perform this transaction ? y/n ";
    cin >> answer;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    if (toupper(answer) == 'Y')
    {
        if (num > currentClient.AccountBalance)
        {
            cout << "\n the amount exceeds your Balance, Make another choise. \n";
            cout << " Perss anukey to continue ";
            system("pause>0");
            ShowATM_MainMenue();
        }

        else
        {
            for (sClient& c : vClients)
            {
                if (c.AccountNumber == currentClient.AccountNumber)
                {
                    c.AccountBalance += -num;
                    currentClient.AccountBalance = c.AccountBalance;
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n Don Successfuly. New Balance is : " << currentClient.AccountBalance << endl;
            GoBackToMainMenue();

        }
    }
}

void PerformQuickWithdrawScreen(enQuickWithdraw ClientOption)
{
    switch (ClientOption)
    {
    case enQuickWithdraw::e20:
    {
        CalulateQuickWithdraw(20);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e50:
    {
        CalulateQuickWithdraw(50);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e100:
    {
        CalulateQuickWithdraw(100);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e200:
    {
        CalulateQuickWithdraw(200);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e400:
    {
        CalulateQuickWithdraw(400);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e600:
    {
        CalulateQuickWithdraw(600);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e800:
    {
        CalulateQuickWithdraw(800);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::e1000:
    {
        CalulateQuickWithdraw(1000);
        GoBackToMainMenue();
        break;
    }

    case enQuickWithdraw::eexit:
    {
        ShowATM_MainMenue();
    }

    }

}

void ShowQuickWithDrawScreen()
{
    system("cls");

    cout << "\n|===========================================|\n" << endl;
    cout << "|\t\t Quick Withdraw" << endl;
    cout << "\n|===========================================|\n";
    cout << "| \n";
    cout << "|\t [1] 20 \t [2] 50 \n";
    cout << "|\t [3] 100 \t [4] 200 \n";
    cout << "|\t [5] 400 \t [6] 600 \n";
    cout << "|\t [7] 800 \t [8] 1000 \n";
    cout << "|\t [9] Exit \n";
    cout << "|\n";
    cout << "|===========================================|" << endl;
    cout << "| \n";
    cout << "|\t" << "    Your Balance Is : ";
    cout << currentClient.AccountBalance << setw(3) << endl;
    cout << "\n|===========================================|\n" << endl;

    PerformQuickWithdrawScreen((enQuickWithdraw)ReadQuickWithdrawOption());
}

//===================================================//

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                currentClient.AccountBalance = C.AccountBalance;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << currentClient.AccountBalance;

                return true;
            }

        }
        return false;
    }

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);


    double Amount = 0;

    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;


    DepositBalanceToClientByAccountNumber(currentClient.AccountNumber, Amount, vClients);

}

//=================================================//

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    int Amount = 0;

    do
    {
        cout << "\nPlease enter  amount multiple of 5`s ? ";
        cin >> Amount;

    } while ((Amount % 5) != 0);

    //Validate that the amount does not exceeds the balance
    while (Amount > currentClient.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << currentClient.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(currentClient.AccountNumber, Amount * -1, vClients);

}

//=============================================//
void ShowChackBalanceScreen()
{
    system("cls");

    cout << "\n\t|-----------------------------------|\n";
    cout << "\t\t Check Balance Screen";
    cout << "\n\t|-----------------------------------|\n\n";

    cout << "\t|" << setw(5) << "    Your Balance Is : ";
    cout << currentClient.AccountBalance << setw(3) << endl;

    cout << "\n\t|-----------------------------------|\n";
}

void PerfromATM_MainMenueOption(enATM_MainMenueOptions ATM_MainMenueOption)
{
    switch (ATM_MainMenueOption)
    {
    case enATM_MainMenueOptions::eQuickWithdraw:
    {
        system("cls");
        ShowQuickWithDrawScreen();
        GoBackToMainMenue();
        break;
    }
    case enATM_MainMenueOptions::eNormalWithdraw:
        system("cls");
        ShowWithDrawScreen();
        GoBackToMainMenue();
        break;

    case enATM_MainMenueOptions::eDeposite:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();
        break;

    case enATM_MainMenueOptions::CheckBalance:
        system("cls");
        ShowChackBalanceScreen();
        GoBackToMainMenue();
        break;


    case enATM_MainMenueOptions::eLogout:
        system("cls");
        Login();
        break;
    }

}

void ShowATM_MainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\t ATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposite.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromATM_MainMenueOption((enATM_MainMenueOptions)ReadMainMenueOption());
}

bool LoadClientInfo(string ClientNumber, string ClientPinCode)
{
    if (FindClientByAccountNumberEndPincode(ClientNumber, ClientPinCode, currentClient))
        return true;
    else
        return false;
}

void Login()
{
    bool LoginField = false;
    string ClientNumber, ClientPinCode;

    do
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\n\t  LogIn Screen";
        cout << "\n-----------------------------------\n";

        if (LoginField)
        {
            cout << "\n  Invalid UserName/Password! \n ";
        }

        ClientNumber = ReadClientAccountNumber();
        ClientPinCode = ReadClientPinCode();

        LoginField = !LoadClientInfo(ClientNumber, ClientPinCode);

    } while (LoginField);

    ShowATM_MainMenue();
}

int main()

{
    Login();

    system("pause>0");
    return 0;
}
