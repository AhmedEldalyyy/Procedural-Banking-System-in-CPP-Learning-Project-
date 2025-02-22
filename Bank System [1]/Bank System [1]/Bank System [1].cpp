#include<fstream>
#include <iomanip>
#include <iostream>
#include<limits>
#include <string>
#include<vector>

using namespace std;

const string ClientsFileName = "ClientsRecord.txt";
const string UsersFileName = "Users.txt";
vector<string> vMainMenuOptions = {"Show Client List","Add New Client","Delete Client","Update Client","Find Client","Transactions","Manage Users","Logout","Exit"};
vector<string> vTransactionsMenuOptions = {"Deposit","Withdraw","Total Balances","Main Menu"};
vector <string> vManageUsersMenuOptions = {"List Users", "Add New User","Delete User","Update User","Find User","Main Menu"};

enum enMainMenu {

    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClientInfo = 4,
    FindClient = 5,
    Transactions = 6,
    ManageUsers = 7,
    Logout = 8 ,
    Exit = 9

};

void OperationCancelMessage()
{

    cout << "\n Operation Cancelled...\n";
}

enum enTransactions {

    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

enum enManageUsersMenu {
    ListUsers = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUser = 4,
    FindUser = 5,
    Menu = 6
};

struct stClients {
    string accountNumber = "";
    string pinCode = "";
    string Name = "";
    string phoneNumber = "";
    double accountBalance = 0.0f;
    bool Delete = false;
};

struct stPermissions
{
    bool ShowClientList = 0;
    bool AddNewClient = 0;
    bool DeleteClient = 0;
    bool UpdateClientInfo = 0;
    bool FindClient = 0;
    bool Transactions = 0;
    bool ManageUsers = 0;
};

struct stUsers {
    string Username = "";
    string Password = "";
    bool Delete = false;
    stPermissions HasPermissionTo;
    vector<string> vPermissions;
};

void ClearScreen() {

    system("cls");
}

void GoBackToMenu(string Message = "Press any key to go back to main menu.....")
{
    cout << "\n " << Message;
    system("pause>0");
}

void ShowAccessDeniedMessage(string Message = "You dont have permission to do this!")
{
    cout << " Access Denied!\n";
    cout <<" " << Message << "\n\a";
}

short GetUserChoice(short From, short To)
{

    short choice = 0;
    cout << " \n Choose what do you want to do [ " << From << " to " << To << " ] : ";
    cin >> choice;

    while (choice > To || choice < From || cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n Invalid input !\a\n";
        cout << " \n Choose what do you want to do [ " << From << " to " << To << " ] : ";
        cin >> choice;

    }

    return choice;
}

// Sub Screens Template
void ScreensDefaultTemplate(string Screen)
{
    cout << " ____________________________\n\n";
    
    cout << "     " << Screen << "  \n";
    cout << " ____________________________\n\n";
}

// Main Menus Template
short ShowMenu(string Title, vector<string> Options)
{
    ClearScreen();

    short userChoice = 0;
    cout << " \n ___________________________________________\n\n";
    cout << "              " << Title << endl;;
    cout << " ___________________________________________\n\n";
    for (short i = 0; i < Options.size(); i++)
    {
        cout << "        [" << i + 1 << "] - " << Options.at(i) << endl;
    }
    cout << " ___________________________________________\n";
    userChoice = GetUserChoice(1, Options.size());

    return userChoice;
}

vector<string> SplitWords(string Sent, string delim = "#//#")
{
    vector<string> words;

    short pos = 0;

    string subRec;

    while ((pos = Sent.find(delim)) != string::npos)
   
   
   
    {
        // Extract substring from start to delimiter position
        subRec = Sent.substr(0, pos);
        // Trim spaces from the beginning and end of the substring

        if (subRec != "")
        {
            words.push_back(subRec);
        }
        Sent.erase(0, pos + delim.length());
    }
    if (Sent != "")
    {
        words.push_back(Sent);
    }

    return words;
}

stClients ClientRecordToStruct(string Record)
{
    stClients sClients;
    vector<string> vWords = SplitWords(Record, "#//#");
    sClients.accountNumber = vWords.at(0);
    sClients.pinCode = vWords.at(1);
    sClients.Name = vWords.at(2);
    sClients.phoneNumber = vWords.at(3);
    sClients.accountBalance = stod(vWords.at(4));

    return sClients;
}

vector<stClients> ClientsFileToClientsVector(string FileName)
{

    vector<stClients> vClients;
    stClients sClient;
    string Record;
    fstream clientsFile;
    clientsFile.open(FileName, ios::in);
    if (clientsFile.is_open())
    {
        while (getline(clientsFile, Record))
        {
            sClient = ClientRecordToStruct(Record);
            vClients.push_back(sClient);
        }
    }
    clientsFile.close();

    return vClients;
}

void PrintClientRecord(stClients Client)
{

    cout << " | " << setw(15) << left << Client.accountNumber;
    cout << " | " << setw(10) << left << Client.pinCode;
    cout << " | " << setw(40) << left << Client.Name;
    cout << " | " << setw(12) << left << Client.phoneNumber;
    cout << " | " << fixed << setw(12) << setprecision(1) << left << Client.accountBalance;

}

void PrintClients(vector<stClients>& Clients)
{
    cout << "\n\t\t\t\t\tClient List (" << Clients.size() << ") Clients(s).";
    cout << "\n ______________________________________________________________________________________________________________\n\n";

    cout << " | " << left << setw(15) << "Accout Number";
    cout << " | " << left << setw(10) << "Pin Code";
    cout << " | " << left << setw(40) << "Client Name";
    cout << " | " << left << setw(12) << "Phone";
    cout << " | " << left << setw(12) << "Balance";
    cout << "\n ______________________________________________________________________________________________________________\n\n";




    for (stClients& Client : Clients)
    {


        PrintClientRecord(Client);
        cout << endl;


    }

    cout << "\n ______________________________________________________________________________________________________________\n\n";
}

void PrintClientCard(stClients Client)
{
    ClearScreen();
    cout << "\n\n";
    cout << setw(26) << right << " [Client Card]\n";
    cout << "\n ______________________________________\n\n\n";

    cout << " | Account Number  : " << Client.accountNumber << endl;
    cout << " | Pin Code        : " << Client.pinCode << endl;
    cout << " | Name            : " << Client.Name << endl;
    cout << " | Phone           : " << Client.phoneNumber << endl;
    cout << " | Account Balance : " << fixed<< setprecision(1)<<Client.accountBalance << endl;
    cout << " \n ______________________________________\n";
}

bool IsCurrentClient(string accountNumber, stClients& sClient )
{
    vector<stClients> vClients = ClientsFileToClientsVector(ClientsFileName);
    for (stClients& S : vClients)
    {
        if (S.accountNumber == accountNumber)
        {
            sClient = S;
            return true;
        }
    }
    return false;
}

bool ConfirmationMessage()
{
    char choice;
    cout << "\n Are you sure you want to peform this operation ? [Y] - Yes / [Other] - No : ";
    cin >> choice;

    return toupper(choice) == 'Y';
}

string ReadAccountNumber(stClients &sClient)
{
    
    string accNumber;
    cout << " Please Enter Account Number : ";
    getline(cin>>ws, accNumber);
    while (!IsCurrentClient(accNumber, sClient))
    {
        cout << " \n Client is NOT found!\a\n\n";
        
        cout << " Please Enter Account Number : ";
        getline(cin>>ws, accNumber);
    }
    return accNumber;
}

void SuccesfullTransactionMessage()
{
    cout << "\n Transaction was done successfully!\n";
    
}

stClients ReadClient()
{

    stClients sClient;
   
    cout << " Enter Account Number : ";
    getline(cin >> ws, sClient.accountNumber);

    while (IsCurrentClient(sClient.accountNumber, sClient))
    {
        cout << "\n Client With Account Number [ " << sClient.accountNumber << " ] Exists ! \n\n\a Enter Another Account Number : ";

        getline(cin >> ws, sClient.accountNumber);
    }

    cout << " Enter Pin Code : ";
    getline(cin, sClient.pinCode);
    cout << " Enter Your Name : ";
    getline(cin, sClient.Name);
    cout << " Enter Phone Number : ";
    getline(cin, sClient.phoneNumber);
    cout << " Enter Account Balance : ";
    cin >> sClient.accountBalance;

    return sClient;
}

string ClientStructToRecord(stClients sClient, string delim = "#//#")
{
    string Record;

    Record += sClient.accountNumber + delim;
    Record += sClient.pinCode + delim;
    Record += sClient.Name + delim;
    Record += sClient.phoneNumber + delim;
    Record += to_string(sClient.accountBalance);

    return Record;
}

void AddRecordToFile(string FileName, string Record)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << Record << endl;
    }
    MyFile.close();
}

void MarkClientForDelete(string accountNumber ,vector<stClients>& vClient)
{
    for (stClients& C : vClient)
    {
        if (C.accountNumber == accountNumber)
        {
            C.Delete = true;
            break;
        }
    }
    return;
}

void UpdateClientStruct(stClients& sClient)
{
    cout << " \n Enter Pin Code : ";
    getline(cin >> ws, sClient.pinCode);
    cout << " Enter Your Name : ";
    getline(cin, sClient.Name);
    cout << " Enter Phone Number : ";
    getline(cin, sClient.phoneNumber);
    cout << " Enter Account Balance : ";
    cin >> sClient.accountBalance;
    
}

void DeleteClientFromFile(string FileName, vector<stClients> vClient)
{
    fstream ClientsFile;
    string Record = "";
    ClientsFile.open(ClientsFileName, ios::out);
    if (ClientsFile.is_open())
    {
        for (stClients& C : vClient)
        {
            if (!C.Delete)
            {
                Record = ClientStructToRecord(C);
            ClientsFile << Record << endl;
            }
            

        }
    }
    ClientsFile.close();

}

void UpdateClientsFile(string FileName, vector<stClients> vClient)
{
    fstream ClientsFile;
    string Record = "";
    ClientsFile.open(ClientsFileName, ios::out);
    if (ClientsFile.is_open())
    {
        for (stClients& C : vClient)
        {
            
                Record = ClientStructToRecord(C);
                ClientsFile << Record << endl;
            
        }
    }
    ClientsFile.close();

}

void PrintClientBalance(stClients sClient)
{
    cout << " | " << left << setw(15) << sClient.accountNumber;
    cout << " | " << left << setw(40) << sClient.Name;
    cout << " | " << fixed << left << setw(12) << setprecision(0) << sClient.accountBalance;
}

bool ValidateTransaction(double withdraw , stClients sClient , bool isWithdraw)

{
    if (isWithdraw)
    {
        return !((withdraw <= 0) || (sClient.accountBalance < withdraw));
    }
    return withdraw > 0;
}

void GiveUserFullPermissions(stUsers& sUser)
{
    sUser.HasPermissionTo.ShowClientList = true;
    sUser.HasPermissionTo.AddNewClient = true;
    sUser.HasPermissionTo.DeleteClient = true;
    sUser.HasPermissionTo.UpdateClientInfo = true;
    sUser.HasPermissionTo.FindClient = true;
    sUser.HasPermissionTo.Transactions = true;
    sUser.HasPermissionTo.ManageUsers = true;
    
}

void SetUserPermissions(stUsers& sUser)
{
    char choice = 'N';

    cout << "\n Do you want to give permission to [ Show Client List ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.ShowClientList = (toupper(choice) == 'Y');

    cout << "\n Do you want to give permission to [ Add New Client ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.AddNewClient = (toupper(choice) == 'Y');

    cout << "\n Do you want to give permission to [ Delete Client ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.DeleteClient = (toupper(choice) == 'Y');

    cout << "\n Do you want to give permission to [ Update Client Info ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.UpdateClientInfo = (toupper(choice) == 'Y');

    cout << "\n Do you want to give permission to [ Find Client ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.FindClient = (toupper(choice) == 'Y');

    cout << "\n Do you want to give permission to [ Transactions ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.Transactions = (toupper(choice) == 'Y');

    cout << "\n Do you want to give permission to [ Manage Users ] ? [Y] - Yes / [Other] - No : ";
    cin >> choice;
    sUser.HasPermissionTo.ManageUsers = (toupper(choice) == 'Y');
}

string UserStructToRecord(stUsers sUser, string delim = "#//#")
{
    string record = "";
    record += sUser.Username + delim;
    record += sUser.Password + delim;
    record += to_string(sUser.HasPermissionTo.ShowClientList) + delim;
    record += to_string(sUser.HasPermissionTo.AddNewClient) + delim;
    record += to_string(sUser.HasPermissionTo.DeleteClient) + delim;
    record += to_string(sUser.HasPermissionTo.UpdateClientInfo) + delim;
    record += to_string(sUser.HasPermissionTo.FindClient) + delim;
    record += to_string(sUser.HasPermissionTo.Transactions) + delim;
    record += to_string(sUser.HasPermissionTo.ManageUsers);


    return record;
    
}

bool IsTrueOrFalseString(string word)
{
    return word == "1";
}

stUsers UserRecordToStruct( string Record)
{
    stUsers sUser;
    vector<string> tempWords = SplitWords(Record); 
    sUser.Username = tempWords.at(0);
    sUser.Password = tempWords.at(1);
    sUser.HasPermissionTo.ShowClientList = IsTrueOrFalseString(tempWords.at(2));
    sUser.HasPermissionTo.AddNewClient = IsTrueOrFalseString(tempWords.at(3));
    sUser.HasPermissionTo.DeleteClient = IsTrueOrFalseString(tempWords.at(4));
    sUser.HasPermissionTo.UpdateClientInfo = IsTrueOrFalseString(tempWords.at(5));
    sUser.HasPermissionTo.FindClient = IsTrueOrFalseString(tempWords.at(6));
    sUser.HasPermissionTo.Transactions = IsTrueOrFalseString(tempWords.at(7));
    sUser.HasPermissionTo.ManageUsers = IsTrueOrFalseString(tempWords.at(8));

    return sUser;
    
}

vector<stUsers> UsersFileToUsersVector(const string& FileName) {

    vector<stUsers> vUsers;
    fstream UsersFile;
    string Record;

    UsersFile.open(FileName, ios::in);

    if (UsersFile.is_open())
    {
        while (getline(UsersFile, Record)) {

            stUsers tempUser = UserRecordToStruct(Record);
            vUsers.push_back(tempUser);
        }
        UsersFile.close();
    }
    return vUsers;
}

bool IsUsernameExists(string userName, vector<stUsers> vUsers)
{
     
    for (stUsers& U : vUsers)
    {
        if (U.Username == userName)
        {
            
            return true;
            
        }
    }
    return false;
}

stUsers ReadUser(vector<stUsers> vUsers)
{
    stUsers sUser;
    cout << " \n Enter Username : ";
    getline(cin >> ws, sUser.Username);
    while (IsUsernameExists(sUser.Username, vUsers))
    {
        cout << "\n Username already exists ! \a\n";
        cout << " Try another username : ";
        getline(cin >> ws, sUser.Username);
    }

    cout << " Enter Password : ";
    getline(cin, sUser.Password);
    char choice = 'N';
    cout << " Do you want to give full access ? [Y] - Yes / [Other] - No : ";
    cin >> choice;

    (toupper(choice) == 'Y')? GiveUserFullPermissions(sUser) : SetUserPermissions(sUser);
    
    return sUser;
}

bool VerifyUserByUsernameAndPassword(string userName , string passWord , vector<stUsers> vUsers , stUsers &sUser)
{
    for (stUsers& U : vUsers)
    {
        if (U.Password == passWord && U.Username == userName)
        {
            sUser = U;
            return true;
        }
   }
    return false;
}

void FillUserPermissionsVector(stUsers &sUser)
{
    if (sUser.HasPermissionTo.ShowClientList)
    {
        sUser.vPermissions.push_back("Show Client");
    }
    if (sUser.HasPermissionTo.AddNewClient)
    {
        sUser.vPermissions.push_back("Add Client");
    }
    if (sUser.HasPermissionTo.DeleteClient)
    {
        sUser.vPermissions.push_back("Delete Client");
    }
    if (sUser.HasPermissionTo.UpdateClientInfo)
    {
        sUser.vPermissions.push_back("Update Client");
    }
    if (sUser.HasPermissionTo.FindClient)
    {
        sUser.vPermissions.push_back("Find Client");
    }
    if (sUser.HasPermissionTo.Transactions)
    {
        sUser.vPermissions.push_back("Transactions");
    }
    if (sUser.HasPermissionTo.ManageUsers)
    {
        sUser.vPermissions.push_back("Manage Users");
    }

}

string UserPermsToString(stUsers &sUser)
{
    FillUserPermissionsVector(sUser);

    string Permissions = "";

    if (sUser.vPermissions.empty())
    {
        return "No Permissions!";
    }

    else if (sUser.vPermissions.size() == 7)
    {
        return "Full Permission";
    }

    for (string& S : sUser.vPermissions)
    {
        Permissions += S + '-';
    }

    Permissions.erase(Permissions.size() - 1, 1);

    return Permissions;
}

void PrintUserInfoTemplate()
{
    cout << "\n ___________________________________________________________________________________________________________________\n\n";
    cout << " | " << left << setw(20) << "User Name";
    cout << " | " << left << setw(12) << "Password";
    cout << " | " << left << "Permissions";
    cout << "\n ___________________________________________________________________________________________________________________\n\n";


}

void PrintUserInfo(stUsers &sUser)
{
    cout << " | " << left << setw(20) << sUser.Username;
    cout << " | " << left << setw(12) << sUser.Password;
    cout << " | " << left << UserPermsToString(sUser);

}

void MarkUserForDelete(string userName, vector<stUsers>& vUsers)
{
    for (stUsers& U : vUsers)
    {
        if (U.Username == userName)
        {
            U.Delete = true;
            break;
        }
    }
}

void DeleteFromUsersFile(string FileName, vector<stUsers>& vUsers)
{
    fstream UsersFile;
    string Record = "";
    UsersFile.open(FileName, ios::out);

    if (UsersFile.is_open())
    {
        for (stUsers& U : vUsers)
        {
            if (!U.Delete)
            {
                Record = UserStructToRecord(U);
                UsersFile << Record << endl;
            }
        }
        UsersFile.close();
    }
}

string ReadUsername()
{
    string userName = "";
    cout << " Enter Username : ";
    getline(cin >> ws, userName);

    return userName;
}

void PrintUserCard(stUsers sUser)
{
    ClearScreen();

    cout << "\n\n";
    cout << setw(26) << right << " [User Card]\n";
    cout << "\n ______________________________________\n\n\n";

    cout << " | Username        : " << sUser.Username << endl;
    cout << " | Password        : " << sUser.Password << endl;
    cout << " | Permissions     : " << UserPermsToString(sUser) << endl;

    cout << " \n ______________________________________\n";

}

void PrintPermissions(stUsers sUser)
{
    cout << "\n User Permissions:\n";
    cout << " - Show Client List: " << (sUser.HasPermissionTo.ShowClientList ? "Yes" : "No") << endl;
    cout << " - Add New Client: " << (sUser.HasPermissionTo.AddNewClient ? "Yes" : "No") << endl;
    cout << " - Delete Client: " << (sUser.HasPermissionTo.DeleteClient ? "Yes" : "No") << endl;
    cout << " - Update Client Info: " << (sUser.HasPermissionTo.UpdateClientInfo ? "Yes" : "No") << endl;
    cout << " - Find Client: " << (sUser.HasPermissionTo.FindClient ? "Yes" : "No") << endl;
    cout << " - Transactions: " << (sUser.HasPermissionTo.Transactions ? "Yes" : "No") << endl;
    cout << " - Manage Users: " << (sUser.HasPermissionTo.ManageUsers ? "Yes" : "No") << endl;
}

void UpdateUserInfoStruct(stUsers& sUser)
{


    cout << "\n Enter Password : ";
    getline(cin >> ws, sUser.Password);
    char choice = 'N';
    cout << "\n Do you want to give full access ? [Y] - Yes / [Other] - No : ";
    cin >> choice;

    if (toupper(choice) == 'Y') {

        GiveUserFullPermissions(sUser);
    }

    else
    {
        SetUserPermissions(sUser);
    }


}

void UpdateUsersFile(string FileName, vector<stUsers>& vUsers)
{
    fstream UsersFile;
    string Record;
    UsersFile.open(FileName, ios::out);
    if (UsersFile.is_open())
    {
        for (stUsers& U : vUsers)
        {
            Record = UserStructToRecord(U);
            UsersFile << Record << endl;
        }
        UsersFile.close();
    }

}

// Permission Check
bool CheckPermission(stUsers& CurrentUser, enMainMenu Permission) {
    switch (Permission) {
    case ShowClientList: return CurrentUser.HasPermissionTo.ShowClientList;
    case AddNewClient: return CurrentUser.HasPermissionTo.AddNewClient;
    case DeleteClient: return CurrentUser.HasPermissionTo.DeleteClient;
    case UpdateClientInfo: return CurrentUser.HasPermissionTo.UpdateClientInfo;
    case FindClient: return CurrentUser.HasPermissionTo.FindClient;
    case Transactions: return CurrentUser.HasPermissionTo.Transactions;
    case ManageUsers: return CurrentUser.HasPermissionTo.ManageUsers;
    default: return false;
    }
}

// Update Users PRIMARY function
void UpdateUsersScreen(vector<stUsers> &vUsers )
{
    ClearScreen();

    ScreensDefaultTemplate("Update User Screen");

    string userName = ReadUsername();
    if (!IsUsernameExists(userName, vUsers))
    {
        cout << "\n User wasn't found! ";
    }
    else
    {
 
            for (stUsers& U : vUsers)
            {
                if (U.Username == userName)
                {
                    PrintUserCard(U);
                    
                    if ( ConfirmationMessage() ) {
                        UpdateUserInfoStruct(U);
                        PrintPermissions(U);
                        UpdateUsersFile(UsersFileName, vUsers);
                        cout << " \n Client Updated Successfully! \n\n";
                    }
                    else
                    {
                        OperationCancelMessage();
                    }
                    
                    break;
                }
            }
   
    }

    GoBackToMenu("Press any key to go back to manage user menu screen......");
    
}

// Add Users PRIMARY function
void AddUsersScreen(vector<stUsers>& vUsers)
{
    ClearScreen();

    ScreensDefaultTemplate("Add New User Screen");

    stUsers sUser;
    char choice = 'Y';
    do {
        sUser = ReadUser(vUsers);
        AddRecordToFile(UsersFileName, UserStructToRecord(sUser));
        vUsers.push_back(sUser);

        cout << " \n User added successfully! Do you want to add more users ? [Y] - Yes / [Other] - No : ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    GoBackToMenu("Press any key to go back to manage user menu screen......");

}

// Delete Users PRIMARY function
void DeleteUsersScreen(vector<stUsers>& vUsers)
{
    ClearScreen();

    string userName = "";
    ScreensDefaultTemplate("Delete User Screen");

    userName = ReadUsername();

    if (userName == "Admin")
    {
        cout << " You cant delete this user!\a\n";
    }
    else if (!IsUsernameExists(userName, vUsers))
    {
        cout << "\n User wasn't found! \n\a";
    }
    else
    {
       
        if (ConfirmationMessage())
        {
            MarkUserForDelete(userName, vUsers);
            DeleteFromUsersFile(UsersFileName, vUsers);
            vUsers = UsersFileToUsersVector(UsersFileName);
            cout << "\n User deleted successfully! ";
        }
        else
        {
            OperationCancelMessage();
        }
        
    }

    GoBackToMenu("Press any key to go back to manage user menu screen......");
}

// List Users PRIMARY function
void ListUsersScreen(vector<stUsers> vUsers)
{
    ClearScreen();

    cout << endl;
    cout << "                                             Users List (" << vUsers.size() << ") User(s).";
    PrintUserInfoTemplate();
    if (vUsers.size() == 0)
    {
        cout << "\t\t\t\t No Users Availabe In The System!";
    }
    else
    {
        for (stUsers& U : vUsers)
        {
            PrintUserInfo(U);
            cout << endl;
        }
        cout << " ___________________________________________________________________________________________________________________\n\n";
    }


    GoBackToMenu("Press any key to go back to manage users menu screen......");
}

// Find Users PRIMARY function
void FindUsersScreen(vector<stUsers> vUsers)
{
    ClearScreen();

    cout << " ___________________________\n\n";
    cout << "     Find User Screen  \n";
    cout << " ___________________________\n\n";
    string userName = ReadUsername();
    if (!IsUsernameExists(userName, vUsers))
    {
        cout << "\n User wasn't found! ";
    }
    else
    {
        for (stUsers& U : vUsers)
        {
            if (U.Username == userName)
            {
                PrintUserCard(U);
                break;
            }
        }
    }

    GoBackToMenu("Press any key to go back to manage user menu screen......");
}

// Deposit PRIMARY function
void DepositScreen(vector<stClients>& vClients, stClients& sClient)
{
    ClearScreen();

    string accountNumber;
    ScreensDefaultTemplate("Deposit Screen");
    accountNumber = ReadAccountNumber(sClient);
    PrintClientCard(sClient);


    double deposit = 0;
    char choice = 'Y';
    cout << " \n Please Enter Deposit Amount : ";
    cin >> deposit;
    while (!ValidateTransaction(deposit, sClient, false))
    {
        cout << "\n Depost must be greater than 0 ! try again.\n\a";

        cout << " \n Please Enter Deposit Amount : ";
        cin >> deposit;
    }

    

    if (ConfirmationMessage())
    {
        for (stClients& C : vClients)
        {
            if (C.accountNumber == accountNumber)
            {
                C.accountBalance += deposit;

                break;
            }
        }
        UpdateClientsFile(ClientsFileName, vClients);
        SuccesfullTransactionMessage();

    }

    else
    {
        OperationCancelMessage();

    }
    GoBackToMenu("Press any key to go back to transaction menu screen....");
}

// Withdraw PRIMARY function
void WithdrawScreen(vector<stClients>& vClients, stClients& sClient)
{
    ClearScreen();
    string accountNumber;
    ScreensDefaultTemplate("Withdraw Screen");
    accountNumber = ReadAccountNumber(sClient);
    PrintClientCard(sClient);


    double withdraw = 0;
    char choice = 'Y';
    cout << " \n Please Enter Withdraw Amount : ";
    cin >> withdraw;

    while (!ValidateTransaction(withdraw, sClient,true))
    {
        cout << " \n\a The amount exceeds your balance OR invalid input , you can withdraw up to : " << sClient.accountBalance << endl;
        cout << " \n Please enter another amount : ";
        cin >> withdraw;

    }

    
    if (ConfirmationMessage())
    {
        for (stClients& C : vClients)
        {
            if (C.accountNumber == accountNumber)
            {
                C.accountBalance -= withdraw;
                UpdateClientsFile(ClientsFileName, vClients);
                break;
            }
        }
        SuccesfullTransactionMessage();
    }
    else
    {
        OperationCancelMessage();
    }

    GoBackToMenu("Press any key to go back to transaction menu screen....");
}

// Total Balances PRIMARY function
void TotalBalancesScreen(vector<stClients> vClients)
{
    ClearScreen();

    double totalBalance = 0.0f;
    cout << '\n';
    cout << "                               Balance List [" << vClients.size() << "]\n";
    cout << " ____________________________________________________________________________\n\n";
    cout << " | " << left << setw(15) << "Account Number";
    cout << " | " << left << setw(40) << "Client Name";
    cout << " | " << left << setw(12) << "Balance";
    cout << "\n ____________________________________________________________________________\n\n";
    for (stClients& C : vClients)
    {
        totalBalance += C.accountBalance;
        PrintClientBalance(C);
        cout << endl;
    }
    cout << " ____________________________________________________________________________\n\n";
    cout << "                         Total Balances = " << totalBalance << endl << endl;
    GoBackToMenu("Press any key to go back to transactions menu screen.....");
}

// Show Clients PRIMARY function
void ShowClientsListScreen(vector<stClients>& vClients ,stUsers CurrentUser)
{

    ClearScreen();

    if (!CheckPermission(CurrentUser, enMainMenu::ShowClientList))
    {
        ShowAccessDeniedMessage("You don't have permission to show clients list. Contact an administrator.");
    }

    else
    {
        PrintClients(vClients);
    }

    GoBackToMenu();
}

// Add Clients PRIMARY function
void AddClientScreen(vector<stClients>& vClients ,stUsers CurrentUser)
{
    ClearScreen();

    if (!CheckPermission(CurrentUser, enMainMenu::AddNewClient))
    {
        ShowAccessDeniedMessage("You don't have permission to add new clients. Contact an administrator.");
    }

    else
    {
        ScreensDefaultTemplate("Add Client Screen");

        stClients sClient = ReadClient();
        string clientRecord = ClientStructToRecord(sClient);
        AddRecordToFile(ClientsFileName, clientRecord);
        vClients.push_back(sClient);
       
        cout << " _______________________________\n";
        cout << "\n  | Client Added Successully! |\n";
        cout << " _______________________________\n\n";
        
    }

    GoBackToMenu();
}

// Delete Clients PRIMARY function
void DeleteClientScreen(vector<stClients>& vClient, stClients& sClient , stUsers CurrentUser)
{
    ClearScreen();

    if (!CheckPermission(CurrentUser, enMainMenu::DeleteClient))
    {
        ShowAccessDeniedMessage("You don't have permission to delete clients. Contact an administrator.");
    }

    else
    {
        ScreensDefaultTemplate("Delete Client Screen");

        string accountNumber = "";
        accountNumber = ReadAccountNumber(sClient);
        PrintClientCard(sClient);
        
        if (ConfirmationMessage())
        {
            MarkClientForDelete(accountNumber, vClient);
            DeleteClientFromFile(ClientsFileName, vClient);

            vClient = ClientsFileToClientsVector(ClientsFileName);
            cout << "\n Client Deleted Successfully!\n\n";
        }
        else
        {
            OperationCancelMessage();
        }
    }

    GoBackToMenu();

}

// Update Clients PRIMARY function
void UpdateClientScreen(stClients& sClient, vector<stClients>& vClients , stUsers CurrentUser)
{
    ClearScreen();
    
    if (!CheckPermission(CurrentUser, enMainMenu::UpdateClientInfo))
    {
        ShowAccessDeniedMessage("You don't have permission to update clients. Contact an administrator.");
    }

    else
    {
        ScreensDefaultTemplate("Update Client Screen");
       
        string accountNumber = "";
        accountNumber = ReadAccountNumber(sClient);
        PrintClientCard(sClient);
        
        if (ConfirmationMessage())
        {
            for (stClients& S : vClients)
            {
                if (S.accountNumber == accountNumber)
                {
                    UpdateClientStruct(S);
                    break;
                }
            }
            UpdateClientsFile(ClientsFileName, vClients);
            cout << " \n Client Updated Successfully! \n\n";
        }

        else
        {
            OperationCancelMessage();
        }
    }


    GoBackToMenu();
}

// Find Clients PRIMARY function
void FindClientScreen(stClients& sClient, stUsers CurrentUser)
{
    ClearScreen();

    if (!CheckPermission(CurrentUser, enMainMenu::FindClient))
    {
        ShowAccessDeniedMessage("You don't have permission to find clients. Contact an administrator.");
    }

    else
    {
        ScreensDefaultTemplate("Find Client Screen");
        string accountNumber = "";
        accountNumber = ReadAccountNumber(sClient);
        PrintClientCard(sClient);

    }
    GoBackToMenu();
}

// Transactions PRIMARY function
void TransactionsScreen(vector<stClients>& vClients, stClients& sClient , stUsers CurrentUser)
{
     ClearScreen();

    if (!CheckPermission(CurrentUser, enMainMenu::Transactions))
    {
        ShowAccessDeniedMessage("You don't have permission to perform transactions operations . Contact an administrator.");
    }

    else
    {
        bool TransactionsScreen = true;
        while (TransactionsScreen)
        {
            enTransactions TransactionType;
            
            TransactionType = enTransactions(ShowMenu("Transactions Menu Screen",vTransactionsMenuOptions));
            switch (TransactionType)
            {
            case enTransactions::Deposit:
                DepositScreen(vClients, sClient);
                break;
            case enTransactions::Withdraw:
                WithdrawScreen(vClients, sClient);
                break;
            case enTransactions::TotalBalances:
                TotalBalancesScreen(vClients);
                break;
            case enTransactions::MainMenu :
                TransactionsScreen = false;
                return;

            default:
                cout << "\n Invalid Input!\n";
                break;
            }
        }
        
    }
    GoBackToMenu();
}

// Manage Users PRIMARY function
void ManageUsersScreen(vector<stUsers>&vUsers, stUsers& currentUser)
{
    
    ClearScreen();

    if (!CheckPermission(currentUser,enMainMenu::ManageUsers))
    {
        ShowAccessDeniedMessage("You don't have permission to manage users . Contact an administrator.");
        GoBackToMenu();
    }

    else
    {
        enManageUsersMenu enUsersMenuOption;

        bool transactionsMenu = true;

        while (transactionsMenu)
        {
            enUsersMenuOption = enManageUsersMenu(ShowMenu("Manage Users Menu",vManageUsersMenuOptions));

            switch (enUsersMenuOption)
            {
            case enManageUsersMenu::ListUsers:
                ListUsersScreen(vUsers);
                break;

            case enManageUsersMenu::AddNewUser:
                AddUsersScreen(vUsers);
                break;
            
            case enManageUsersMenu::DeleteUser:
                DeleteUsersScreen(vUsers);
                break;

            case enManageUsersMenu::FindUser:
                FindUsersScreen(vUsers);
                break;

            case enManageUsersMenu::UpdateUser:
                UpdateUsersScreen(vUsers);
                break;

            case enManageUsersMenu::Menu:
                transactionsMenu = false;
                break;
            }
            
        } 
    }
   
}

// Login Screen
void Login(vector<stUsers> vUsers, stUsers& CurrentUser, bool& LoggedIn)
{
    ClearScreen();

    string userName;
    string passWord;
    ScreensDefaultTemplate("    Login Screen");
    cout << " Username : ";
    getline(cin >> ws, userName);
    cout << " Password : ";
    getline(cin, passWord);
    while (!VerifyUserByUsernameAndPassword(userName, passWord, vUsers, CurrentUser))
    {
        cout << "\n\a Wrong username or password .. try again  \n\n";
        cout << " Username : ";
        getline(cin, userName);
        cout << " Password : ";
        getline(cin, passWord);
    }
    LoggedIn = true;

}

void StartProgram()
{
  
    bool Running = true; 
    bool LoggedIn = false;
    
    stClients sClient;
    stUsers CurrentUser;
    vector<stUsers> vUsers = UsersFileToUsersVector(UsersFileName);
    vector<stClients> vClients = ClientsFileToClientsVector(ClientsFileName);
    enMainMenu enMainMenuOptions;
   
    

    while (Running)
    {
          Login(vUsers, CurrentUser, LoggedIn);

        while (LoggedIn)
        {
            ClearScreen();

            // Show Main Menu Options
            enMainMenuOptions = enMainMenu(ShowMenu("Main Menu",vMainMenuOptions));

            
            switch (enMainMenuOptions)
            {
            case enMainMenu::ShowClientList:
                ShowClientsListScreen(vClients, CurrentUser);              
                break;

            case enMainMenu::AddNewClient:
                AddClientScreen(vClients, CurrentUser);         
                break;

            case enMainMenu::DeleteClient:
                
                DeleteClientScreen(vClients, sClient, CurrentUser);
                break;

            case enMainMenu::UpdateClientInfo:
                UpdateClientScreen(sClient, vClients, CurrentUser);
                break;

            case enMainMenu::FindClient:
                FindClientScreen(sClient, CurrentUser);               
                break;

            case enMainMenu::Transactions:
                TransactionsScreen(vClients, sClient, CurrentUser);
                break;

            case enMainMenu::ManageUsers:
                ManageUsersScreen(vUsers, CurrentUser);              
                break;

            case enMainMenu::Logout:
                
                LoggedIn = false; // logout
                cout << " \n logged out...\n" << endl;
                break;

            case enMainMenu::Exit:
                
                LoggedIn = false;
                Running = false; // Exit the program

                ClearScreen();
                cout << " \n Exiting the program...\n" << endl;
                break;

            default:
                
                cout << "Invalid choice! Please try again." << endl;
                
                break;
            }

        }
    }

    exit(0);
}

int main() {

    StartProgram();
   
   
    return 0;
}