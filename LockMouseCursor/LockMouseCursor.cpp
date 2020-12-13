// LockMouseCursor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleTitleA("Cursor Lock");

    std::cout << "Your cursor is now locked to GD when you have it selected!" << std::endl;

    RECT previous;
    GetClipCursor(&previous);

    while (true) {
        TCHAR windowTxt;
        HWND window = GetForegroundWindow();

        std::string windowStr(&windowTxt);

        if (GetWindowTextA(window, &windowTxt, 18)) {
            if (windowStr == "Geometry Dash") {
                RECT rect;
                GetWindowRect(window, &rect);

                rect.left += 7;
                rect.right -= 14;
                rect.bottom -= 7;

                ClipCursor(&rect);
            }
            else {
                ClipCursor(&previous);
            }
        }
    }
}
