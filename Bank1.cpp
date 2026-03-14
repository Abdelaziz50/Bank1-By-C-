#include <iostream> 
#include <string> 
#include <cmath> 
#include <cstdlib> 
#include <ctime>
#include <cstdio> 
#include "MyInput.h"
#include "MyLib.h"
#include <iomanip> 
#include <vector> 
#include "MyPrint.h"
#include <cctype> // isupper charcter Fanction
#include <fstream>
#include "Arr2D.h"
#include "Corse7.h"
using namespace std;
//Function Declaration
void PrintMainMenueScreen();
bool ExisClientByAccountNumber(string AccountNumber);
void TrancactionsMinueScreen();
string FileName = "Client.txt";
string Separator = "#//#";
struct  stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string phone = "";
    long double AccountBalance = 0;
    bool Delete = false;

    
};
enum enMainMenueOptions
{
    ListClient = 1, enAddNewClient = 2, enDeleteClient = 3, Update = 4
    , FindClient = 5, Trancactions = 6, Exit = 7
};
enum enTrancActionMenueOptions
{
    Deposit = 1, WithDraw = 2, TotalBalance = 3, MainMenue = 4

};
stClient ReadClientData()
{
    stClient Client;

    cout << "\nPleas Enter Account Number  ";
    getline(cin >> ws, Client.AccountNumber);

    while (ExisClientByAccountNumber(Client.AccountNumber))
    {
        cout << "\nClient [" << Client.AccountNumber << "] Already Exists Enter Another Account Number  ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "\nPleas enter Pine Code  ";
    getline(cin, Client.PinCode);

    cout << "\nPleas Enter Name  ";
    getline(cin, Client.Name);

    cout << "\nPleas Enter Phone  ";
    getline(cin, Client.phone);

    cout << "\nPleas Enter Account Palance  ";
    cin >> Client.AccountBalance;

    return Client;
   


}
void PrintClientData(stClient Client)
{

    cout << "\n________________________________________________\n";
    cout << "\nAccount Number      :   " << Client.AccountNumber << endl;
    cout << "Pin Code            :   " << Client.PinCode << endl;
    cout << "Name                :   " << Client.Name << endl;
    cout << "Phone               :   " << Client.phone << endl;
    cout << "Account Balance     :   " << Client.AccountBalance << endl;
    cout << "\n________________________________________________\n";

   


}
vector <string> SplitString(string S1, string Delm)
{
    vector <string> vWord;
   
    string sWord = "";
   

    short Pos = 0;
    while ((Pos = S1.find(Delm))!= std::string::npos)
        
    {
        sWord = S1.substr(0, Pos);
        
        if (sWord != "")
        {
            vWord.push_back(sWord);
        }
        
      S1.erase(0, Pos + Delm.length());
      
    }

    if (S1 != "")
    {
        
        vWord.push_back(S1);
    }

    return vWord;

}
void SaveTxtInFile(string Txt)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app); //Append Mod

    if (MyFile.is_open())
    {

        MyFile << Txt << endl;
        MyFile.close();
    }


}
string ConvertRecordToline(stClient Client)
{
    string record = "";

    record += Client.AccountNumber + Separator;
    record += Client.PinCode + Separator;
    record += Client.Name + Separator;
    record += Client.phone + Separator;
    record += to_string(Client.AccountBalance);

    return record;

}
stClient FillStructOnLine(string Line)
{
    vector <string> vWord = SplitString(Line,Separator);
    stClient Client;

    Client.AccountNumber = vWord[0];
    Client.PinCode = vWord[1];
    Client.Name = vWord[2];
    Client.phone = vWord[3];
    Client.AccountBalance = stod(vWord[4]);


    return Client;

}
bool ExisClientByAccountNumber(string AccountNumber)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);//Read Mod
   
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = FillStructOnLine(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;

            }
            

        }

        MyFile.close();


    }

    return false;
       
}
vector <stClient> LoadDataFromFileToVector()
{

    fstream MyFile;
    vector <stClient> vClient;


    MyFile.open(FileName, ios::in); //ReadMod
    if (MyFile.is_open())
    {

        stClient Client;
        string Line;

        while (getline(MyFile, Line))
        {
            Client = FillStructOnLine(Line);
            vClient.push_back(Client);
        }

        MyFile.close();



    }


    return vClient;

}
void PrintHederAllClient(short ClientNumber)
{
    cout << "\n\t\t\t\t\tClient List (" << ClientNumber << ") Client(s).\n";
    cout << "\n________________________________________________________";
    cout << "_______________________________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Account Balance";

    cout << "\n________________________________________________________";
    cout << "_______________________________________________\n\n";

}
void PrintClientRecord(stClient Client)
{

  
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;


}
void PrintAllClientData()
{
    vector <stClient> vClient;
    vClient = LoadDataFromFileToVector();
    PrintHederAllClient(vClient.size());
    for (stClient& C : vClient)
    {
        PrintClientRecord(C);
        cout << endl;
    }

    cout << "\n________________________________________________________";
    cout << "_______________________________________________\n\n";

}
bool FindClientByAccountNumber(string AccountNumber, stClient& Client ,vector <stClient> &vClient)
{
    vClient = LoadDataFromFileToVector();

    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client.AccountNumber = C.AccountNumber;
            Client.PinCode = C.PinCode;
            Client.Name = C.Name;
            Client.phone = C.phone;
            Client.AccountBalance = C.AccountBalance;

            return true;
        }

    }




    return false;

}
void AddNewClient()
{
    stClient Client = ReadClientData();
    string S = ConvertRecordToline(Client);
    SaveTxtInFile(S);
    cout << "Customer data has been added successfully \n";

}
void ShowAddClientScreen()
{


    char AddMore = 'Y';
    do
    {
        cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
        cout << "\n\t\tAddNew Client\n";
        cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
        cout << "\nAdding New Client : \n";
        AddNewClient();
        cout << "Add New Client ? Y/N ?";
        cin >> AddMore;
        cout << endl;
        system("cls");


    } while (toupper(AddMore) == 'Y');
}
void SaveVectorToFileOutMod(vector <stClient> &vClient)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out); //out Mod
    
    if (MyFile.is_open())
    {
        for (stClient& C : vClient)
        {
            if (!(C.Delete))
            {
                MyFile << ConvertRecordToline(C) << endl;
            }
        }

        MyFile.close();
    }




}
bool DeleteClientByAccountNumber(string AccountNumber)
{
   
    vector <stClient> vClient;
    vClient = LoadDataFromFileToVector();
;
   
        for (stClient& C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {

                                        
                              
                C.Delete = true;
                SaveVectorToFileOutMod(vClient);
                return true;
                
            }
        }

       
       
        return false;


}
void FindClientScreen()
{

    cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "\n\t\tFind Client Screen \n";
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";

    string AccountNumber = MyInput::ReadText("\nEnter Account Number ?  ");
    vector <stClient> vClient;
    stClient Client;
    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientData(Client);
    }
    else
    {
        cout << "Account Number " << AccountNumber << "Not Fund .\n";
    }

}
void DeleteClientScreen()
{
    cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "\n\t\tDelete Client Screen\n";
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";

    string AccountNumber = MyInput::ReadText("\nPleas Enter Account Number ?  ");
    vector <stClient> vClient;
    stClient Client;
    char Delete = 'x';

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientData(Client);
       
        cout << "Do you really want to delete this Client ? Y/N ? ";
        cin >> Delete;
        cout << endl;
    }
    else
    {
        cout << "Account Number " << AccountNumber << "Not Fund .\n";

    }
     

    if (toupper(Delete) == 'Y')
    {
        
        if (DeleteClientByAccountNumber(AccountNumber))
        cout << "Delete Client\n";
        else
        cout << "Client Account Number \"" << AccountNumber << "\"is Not Fund\n";
        
    }
   


}
stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "Pleas enter Pine Code\n";
    getline(cin >> ws, Client.PinCode);

    cout << "Pleas Enter Name\n";
    getline(cin, Client.Name);

    cout << "Pleas Enter Phone\n";
    getline(cin, Client.phone);

    cout << "Pleas Enter Account Palance\n";
    cin >> Client.AccountBalance;

    return Client;




}
bool UpdateClientByAccountNumber(string AccountNumber,vector <stClient> &vClient)
{
    stClient Client;
    char Answer = 'Y';
    if (FindClientByAccountNumber(AccountNumber, Client,vClient))
    {
        PrintClientData(Client);
        cout << "Are You sure you want Update thes Client ? Y/N ?";
        cin >> Answer;
        cout << endl;

        if (toupper(Answer) == 'Y')
        {
            for (stClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    system("cls");
                  C = ChangeClientRecord(AccountNumber);
                    break;

                }
            }



        }



        SaveVectorToFileOutMod(vClient);
        vClient = LoadDataFromFileToVector();
        cout << "\n\nClient Updated successfully.\n";

        return true;



    }

    else
    {
        cout << "Client Account Number \"" << AccountNumber << "\"is Not Fund\n";
        return false;
    }


}
void UpdateClientScreen()
{
    cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "\n\t\tUpdate Client Info Screen \n";
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";

    string AccountNumber = MyInput::ReadText("\nEnter Account Number ?  ");
    vector <stClient> vClient = LoadDataFromFileToVector();

    UpdateClientByAccountNumber(AccountNumber, vClient);
   

}
void ExitScreen()
{
    cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "\n\t\tProgram End :-)\n";
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
}
enMainMenueOptions ReadOptionClient()
{
    short Choose;
    cout << "Choose What Do Want To Do ? [1 to 6]?  ";
    cin >> Choose;
    cout << endl;
    return (enMainMenueOptions)Choose;


}
enTrancActionMenueOptions ReadOptioninTrancActions()
{
    short Choose;
    cout << "Choose What Do Want To Do ? [1 to 4]?  ";
    cin >> Choose;
    cout << endl;
    return (enTrancActionMenueOptions)Choose;
}
void GoBackToTranceActionsMenueScreen()
{
    cout << "\n\n\nPress Any Key To Go Back To TranceActions Menue....";
    system("pause>0");
    TrancactionsMinueScreen();
}
void GoBackToMenueScreen()
{
    cout << "\n\n\nPress Any Key To Go Back To Main Menue....";
    system("pause>0");
    PrintMainMenueScreen();

}
void MainMenueBank(enMainMenueOptions Menue)
{
   
   switch (Menue)
   {
   case enMainMenueOptions::ListClient:
      system("cls");
      PrintAllClientData();
      GoBackToMenueScreen();


       break;

   case enAddNewClient :
       system("cls");
       ShowAddClientScreen();
       GoBackToMenueScreen();
       break;

   case enDeleteClient:
       system("cls");
       DeleteClientScreen();
       GoBackToMenueScreen();
       break;

   case Update:
       system("cls");
       UpdateClientScreen();
       GoBackToMenueScreen();
       break;

   case FindClient:
       system("cls");
       FindClientScreen();     
       GoBackToMenueScreen();
       break;

   case Trancactions:
       system("cls");
       TrancactionsMinueScreen();
       break;
   case Exit :
       system("cls");
       ExitScreen();
       break;

   default:
       system("cls");
       ExitScreen();
       break;

   }

   


}
bool Deposit_WithDrawClient(string AccountNumber ,double TheAmount)
{  

    vector <stClient> vClient = LoadDataFromFileToVector();      
    
        for (stClient&C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += TheAmount;
                SaveVectorToFileOutMod(vClient);
                return true;
                
            }
        }     
          

    return false;

}
void DepositScreen()
{

    cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "\n\t\tDeposit Screen\n";
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";


    vector <stClient> vClient;
    stClient Client;
    string AccountNumber = MyInput::ReadText("\nPleas Enter Account Number ?  ");



    while (!FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        cout << "\nClient Whth [" << AccountNumber << "] Dois Not exist.\n";
        cout << "\nPleas Enter Account Number ?  ";
        getline(cin , AccountNumber);
        cout << endl;


    }
   
    
        PrintClientData(Client);
        double TheAmound = MyInput::ReadNumberFloat("Pleas Enter Deposit Amount ? ");
        
        Deposit_WithDrawClient(AccountNumber, TheAmound);

        cout << "The Amunt of [" << TheAmound << "] Was Deposited\n";
        cout << "Your total Balance Now [" << Client.AccountBalance + TheAmound << "] ..." << endl;
        


    



   



}
void WithDrawScreen()
{

    cout << "\n_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "\n\t\tWithDraw Screen\n";
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";


    vector <stClient> vClient;
    stClient Client;
    string AccountNumber = MyInput::ReadText("\nPleas Enter Account Number ?  ");
    while (!FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        cout << "\nClient Whth [" << AccountNumber << "] Dois Not exist.\n";
        cout << "\nPleas Enter Account Number ?  ";
        getline(cin, AccountNumber);
        cout << endl;

    }
    PrintClientData(Client);
    double WithDraw = 0;
    cout << "Your Balance is [" << Client.AccountBalance << "] .. \n";
    WithDraw = MyInput::ReadNumberFloat("Pleas Enter With Draw Amount ? ");
    while (WithDraw > Client.AccountBalance)
    {
        cout << "Your Balance is insufficient,Pleas try again \n";
        cout << "Your Balance is [" << Client.AccountBalance << "] .. \n";
        cout << "Pleas Enter With Draw Amount ? ";
        cin >> WithDraw;
        cout << endl;

    }
    Deposit_WithDrawClient(AccountNumber, WithDraw * -1);

    cout << "The Amunt of [" << WithDraw << "] Was WithDraw\n";
    cout << "Your total Balance Now [" << Client.AccountBalance - WithDraw << "] ..." << endl;



}
void PrintHederTotalBalanceScreen(short BalanceList)
{
    cout << "\n\t\t\t\t Balance List (" << BalanceList << ") Client(s).\n";
    cout << "\n________________________________________________________";
    cout << "_______________________________________________\n\n";
    cout << "| " << left << setw(20) << "Account Number ";
    cout << "| " << left << setw(40) << "Client Name ";
    cout << "| " << left << setw(15) << "Balance ";
    cout << "\n________________________________________________________";
    cout << "_______________________________________________\n\n";

}
void PrintBalance(stClient Client)
{
    cout << "| " << left << setw(20) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(15) << Client.AccountBalance;
    cout << endl;
}
void TotalBalanceScreen()
{
    vector <stClient> vClient = LoadDataFromFileToVector();
    PrintHederTotalBalanceScreen(vClient.size());
    double TotalBalance = 0;
    for (stClient& C : vClient)
    {
        PrintBalance(C);
        TotalBalance += C.AccountBalance;

    }
    cout << "\n________________________________________________________";
    cout << "_______________________________________________\n\n";

    cout << "\n\t\t\tTotal Balance = " << TotalBalance << endl;




}
void TrancactionsMinue(enTrancActionMenueOptions Trancactions)
{
    switch (Trancactions)
    {
    case Deposit:
        system("cls");
        DepositScreen();
        GoBackToTranceActionsMenueScreen();
        break;
    case WithDraw:
        system("cls");
        WithDrawScreen();
        GoBackToTranceActionsMenueScreen();
        break;
    case TotalBalance:
        system("cls");
        TotalBalanceScreen();
        GoBackToTranceActionsMenueScreen();
        break;
    case MainMenue:
        system("cls");
        PrintMainMenueScreen();
        break;
    default:        
        system("cls");
        GoBackToTranceActionsMenueScreen();
        break;
    }




}
void TrancactionsMinueScreen()
{
    system("cls");
    cout << "\n=====================================================\n";
    cout << "\n\t\t TrancactionsMinueScreen\n";
    cout << "\n=====================================================\n";
    cout << "\n\t\t[1] Deposit.\n";
    cout << "\t\t[2] WithDraw.\n";
    cout << "\t\t[3] Total Balance.\n";
    cout << "\t\t[4] Main Minue.\n";
    cout << "\n=====================================================\n";

    enTrancActionMenueOptions Trancactions = ReadOptioninTrancActions();
    TrancactionsMinue(Trancactions);
}
void PrintMainMenueScreen()
{
    system("cls");
    cout << "\n=====================================================\n";
    cout << "\n\t\t  MainMenueScreen\n";
    cout << "\n=====================================================\n";
    cout << "\n\t\t[1] Show Client List.\n";
    cout << "\t\t[2] Add New Client.\n";
    cout << "\t\t[3] Delete Client.\n";
    cout << "\t\t[4] Update Client Info.\n";
    cout << "\t\t[5] Find Client.\n";
    cout << "\t\t[6] Trancactions.\n";
    cout << "\t\t[7] Exit.\n";

    cout << "\n=====================================================\n";
    enMainMenueOptions Menue = ReadOptionClient();
    MainMenueBank(Menue);


}

int main() {

  

    
    PrintMainMenueScreen();
  
    system("pause>0");

    return 0;

}










// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
