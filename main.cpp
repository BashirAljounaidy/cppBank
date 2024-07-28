#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

enum enFields { AccountID = 0, FullName, PhoneNumber, PinCode, Balance,FiledsCount };

struct Client{
    string AccountID;
    string FullName;
    string PhoneNumber;
    string PinCode;
    double Balance;
};

//Intitations values
string filename="clients.csv";
vector<Client> vClients;
vector<string> vAccountIds;
double TotalBalances=0;

//Core functions Declaration
Client _ParseClientFromLineString(const string& line,char delimiter);
void LoadFileToVector(const string& filename,vector<Client>& vClients);
void _PrintSingleRecord(const Client& stClient);
void PrintAllRecords(vector<Client>& vClients);
// void AddNewClient(vector<Client>  vClients);


// Screens
void ClearScreen();
void ShowClientListScreen();
void AddNewClientScreen();
void ReadClientFromUser(Client& stClient);
void DeleteClientScreen();
void UpdateClientInfoScreen();
void FindClientScreen();
void TransactionsScreen();
void DepositScreen();
void WithdrawScreen();

void MainMenuScreen();
void ExitScreen();
void NumberToScreen(short ScreenNumber);
void ShowTotalBalancesScreen();
void UpdateAccountIdVector(const vector<Client>& vClients,vector<string>& vAccountIds){
    vAccountIds.clear();
    TotalBalances=0;
    for (short i = 0; i < vClients.size(); i++)
    {
        vAccountIds.push_back(vClients[i].AccountID);
        TotalBalances+=vClients[i].Balance;
    }
}

void clearScreen(){
#ifdef _WIN32 
    system("cls");
#else
    system("clear");
#endif
}

void cinflush(){
    cin.clear();
    cin.ignore(10000, '\n');
}

void backToMainMenu(string Message =""){
    cout <<"\n"<<Message;
    cout << "\n\nPress Enter to go back to Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    cin.get();
    MainMenuScreen();
}


void backToTransactionMenu(string Message =""){
    cout <<"\n"<<Message;
    cout << "\n\nPress Enter to go back to Main Menu...";
    cin.ignore(1000, '\n'); // Clear the input buffer
    cin.get();
    TransactionsScreen();
}

void MainMenuScreen() {
    clearScreen();
    UpdateAccountIdVector(vClients,vAccountIds);
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    short ScreenNumber;
    cin>>ScreenNumber;
    if (ScreenNumber>7 || ScreenNumber<1) {
        cinflush();
        MainMenuScreen();
    };
    NumberToScreen(ScreenNumber);

}

void NumberToScreen(short ScreenNumber){
    switch (ScreenNumber)
    {
    case 1:ShowClientListScreen();break;
    case 2:AddNewClientScreen();break;
    case 3:DeleteClientScreen();break;
    case 4:UpdateClientInfoScreen();break;
    case 5:FindClientScreen();break;
    case 6:TransactionsScreen();break;
    case 7:ExitScreen();break;
    default:backToMainMenu("Error , Please Enter a valid Option") ;break;
    }
}

// Screens

void PrintClientRecord(const Client& client) {
    cout << "| " << setw(15) << left << client.AccountID;
    cout << "| " << setw(30) << left << client.FullName;
    cout << "| " << setw(15) << left << client.PhoneNumber;
    cout << "| " << setw(15) << left << client.PinCode;
    cout << "| " << setw(12) << left << client.Balance;
}

void PrintAllClientsData(const vector<Client>& vClients) {
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Id";
    cout << "| " << left << setw(30) << "Full Name";
    cout << "| " << left << setw(15) << "Phone ";
    cout << "| " << left << setw(15) << "Pin Code";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (const Client& client : vClients) {
        PrintClientRecord(client);
        cout << endl;
    }

    cout << "_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintSingleClientInfo(const Client& client) {
    cout << "\nClient Data:\n" << endl;
    cout << "Account Number : " << client.AccountID << endl;
    cout << "Name           : " << client.FullName << endl;
    cout << "Phone          : " << client.PhoneNumber << endl;
    cout << "PinCode        : " << client.PinCode << endl;
    cout << "Account Balance: " << client.Balance << endl;
}

void ShowClientListScreen(){
    clearScreen();
    cout<<"\nShowClientListScreen\n";
    PrintAllClientsData(vClients);
    backToMainMenu();
}

void AppendClientToVectorClients(vector<Client>&  vClients ,Client& stClient ){
    char addOrNot;
    cout<<"\nAre you sure to add this client (Y / N) ? ";
    cin>>addOrNot;
    if (addOrNot == 'y' || addOrNot == 'Y')
    {
        vClients.push_back(stClient);
        cout<<"\n Added Successfully ! ";
    }
}

void AddNewClient(vector<Client>&  vClients){
    Client stClient;
    ReadClientFromUser(stClient);
    PrintSingleClientInfo(stClient);
    AppendClientToVectorClients(vClients,stClient);
    backToMainMenu();

}


//single client
void ReadClientFromUser(Client& stClient){
    cout << "Please Enter Client Data" << endl;
    cout << "Enter Account Id? ";
    cin >> stClient.AccountID;
    cinflush();
    
    cout << "Enter Full Name? ";
    getline(cin,stClient.FullName);
    // cinflush();

    cout << "Enter PhoneNumber? ";
    getline(cin, stClient.PhoneNumber);
    // cinflush();
    
    cout << "Enter Pin Code? ";
    cin >> stClient.PinCode;
    // cinflush();
    
    cout << "Enter Account Balance? ";
    cin >> stClient.Balance;
    // cinflush();
    

}

void AddNewClientScreen() {
    clearScreen();
    AddNewClient(vClients);
    backToMainMenu();
}

string ReadClientAccountId(){
    string AccountID;
    cout<<"Please Enter Account ID ";
    cin>>AccountID;
    return AccountID;
}

short FindByAccountNumber(const string& AccountNumber, const vector<Client>& vClients) {
    for (size_t i = 0; i < vClients.size(); ++i) {
        if (vClients[i].AccountID == AccountNumber) {
            return i; // Return the Location if account number matches
        }
    }
    return -1; // Return -1 if no match is found
}

Client retriveAccountByLocation(const vector<Client>& vClients, short ClientLocation){
    return vClients[ClientLocation];
}

void DeleteClientScreen() {
    string AccountID;
    clearScreen();
    AccountID=ReadClientAccountId();
    short ClientLocation = FindByAccountNumber(AccountID,vClients);
    if (ClientLocation == -1)  {
        cout <<AccountID<< " Client not found.\n" ;
        backToMainMenu(); 
    }
    vClients.erase(vClients.begin() + ClientLocation);
    cout <<AccountID<<" Client removed.\n";
    backToMainMenu();
}

void UpdateClientInfoScreen() {
    string AccountID;
    Client stClient;
    clearScreen();
    AccountID=ReadClientAccountId();
    short ClientLocation = FindByAccountNumber(AccountID,vClients);
    if (ClientLocation == -1)  {
        cout <<AccountID<< "Client not found.\n" ;
        backToMainMenu();
    }
    cout<<"\nClient with ID "<<AccountID<<" Founded \n";
    PrintSingleClientInfo(vClients[ClientLocation]);
    cout<<"\nUpdate Client\n";
    ReadClientFromUser(vClients[ClientLocation]);
    PrintSingleClientInfo(vClients[ClientLocation]);
    cout <<AccountID<<" Client Added Successfully.\n";
    backToMainMenu();
}

void FindClientScreen() {
    clearScreen();
    string AccountID=ReadClientAccountId();
    short ClientLocation = FindByAccountNumber(AccountID,vClients);
    if (ClientLocation == -1)  {
        cout <<AccountID<< "Client not found.\n" ;
        backToMainMenu();
    }
    cout<<"\nClient with ID "<<AccountID<<" Founded \n";
    PrintSingleClientInfo(vClients[ClientLocation]);
    backToMainMenu();
}

void NumberToTransactionsScreens(short& ScreenNumber){
    switch (ScreenNumber)
    {
    case 1:DepositScreen();break;
    case 2:WithdrawScreen();break;
    case 3:ShowTotalBalancesScreen();break;
    case 4:MainMenuScreen();break;
    default:backToMainMenu("Error , Please Enter a valid Option") ;break;
    }
}

void TransactionsScreen() {
    clearScreen();
    UpdateAccountIdVector(vClients,vAccountIds);
    cout << "===========================================\n";
    cout << "\t\tTransactions Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "===========================================\n";
    short ScreenNumber;
    cin>>ScreenNumber;
    if (ScreenNumber>4 || ScreenNumber<1) {
        cinflush();
        TransactionsScreen();
    };
    NumberToTransactionsScreens(ScreenNumber);

}

void ReadDepositFromUser(Client& stClient){
    double amount=0;
    cout << "Enter Ammount to deposit Balance? ";
    cin >> amount;
    stClient.Balance += amount;
}

void ReadWithdrawFromUser(Client& stClient){
    double amount=0;
    cout << "Enter Ammount to Withdraw Balance? ";
    cin >> amount;
    stClient.Balance -= amount;
}

void DepositScreen() {
    string AccountID;
    Client stClient;
    clearScreen();
    AccountID=ReadClientAccountId();
    short ClientLocation = FindByAccountNumber(AccountID,vClients);
    if (ClientLocation == -1)  {
        cout <<AccountID<< "Client not found.\n" ;
        backToTransactionMenu();
    }
    cout<<"\nClient with ID "<<AccountID<<" Founded \n";
    PrintSingleClientInfo(vClients[ClientLocation]);
    cout<<"\nUpdate Client\n";
    ReadDepositFromUser(vClients[ClientLocation]);
    PrintSingleClientInfo(vClients[ClientLocation]);
    cout <<AccountID<<" Money Added Successfully.\n";
    backToTransactionMenu();
}

void WithdrawScreen() {
    string AccountID;
    Client stClient;
    clearScreen();
    AccountID=ReadClientAccountId();
    short ClientLocation = FindByAccountNumber(AccountID,vClients);
    if (ClientLocation == -1)  {
        cout <<AccountID<< "Client not found.\n" ;
        backToTransactionMenu();
    }
    cout<<"\nClient with ID "<<AccountID<<" Founded \n";
    PrintSingleClientInfo(vClients[ClientLocation]);
    cout<<"\nUpdate Client\n";
    ReadWithdrawFromUser(vClients[ClientLocation]);
    cout <<AccountID<<" Money Withdrawl Successfully.\n";
    backToTransactionMenu();
}

void ShowTotalBalancesScreen(){
    clearScreen();
    cout<<"\nShowClientListScreen\n";
    PrintAllClientsData(vClients);
    cout<<setw(50)<<left<<" Total Balances = "<< TotalBalances;
    backToTransactionMenu();
}

void ExitScreen() {
    exit(0); // Terminate the application
}


//Core Functions implemetatoin

vector <string> _ParseTokensFromLineString(const string& line,short NumberOfFileds,char delimiter=','){
    short i=0,start=0;
    Client stClient;
    vector <string> tokens;

    for (size_t incrementer = 0; incrementer < NumberOfFileds; incrementer++)
    {
        i=line.find(delimiter,start);
        tokens.push_back(line.substr(start,i-start));
        start=i+1;
    }
    return tokens;
}

Client _TokenstoClient(vector <string> tokens){
    Client stClient;
    stClient.AccountID   =tokens[enFields::AccountID];
    stClient.FullName    =tokens[enFields::FullName];
    stClient.PhoneNumber =tokens[enFields::PhoneNumber];
    stClient.PinCode     =tokens[enFields::PinCode];
    stClient.Balance     =stod(tokens[enFields::Balance]);
    return stClient;
}

void LoadFileToVector(const string& filename,vector<Client>& vClients){
    fstream fsFile;
    string line;
    fsFile.open(filename,ios::in);
    if(!fsFile.is_open())
    {
        cout<<"File not found";
        return ;
    }
    while (getline(fsFile,line) && line != "")
    {
        vClients.push_back(_TokenstoClient(_ParseTokensFromLineString(line,enFields::FiledsCount)));
    }
    
    fsFile.close();
}


int main() {
    LoadFileToVector(filename,vClients);
    MainMenuScreen();
    return 0;
}