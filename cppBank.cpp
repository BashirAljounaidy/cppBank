#include <iostream>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
#include "Global.h"

int main()
{
    while (true) {
        if (CurrentUser.IsEmpty()) {
            clsLoginScreen::ShowLoginScreen();
        }
        else {
            clsMainScreen::ShowMainMenue();
        }
    }

    system("pause>0");
    return 0;
}
