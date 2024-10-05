#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  void _Login()
    {
        bool LoginFaild = false;
        short FailCount = 0;
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                FailCount++;

                cout << "\nInvlaid Username/Password!";
                cout << "\nYou have " << (3 - FailCount)
                    << " Trial(s) to login.\n\n";
            }

            if (FailCount>=3)
            {
                
                cout << "\nSystem Locked" << endl;
                system("pause>0");
                exit(0);
            }
            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);


    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();

    }

    static void Logout() {
        CurrentUser = clsUser::Find("", "");
    }

};

