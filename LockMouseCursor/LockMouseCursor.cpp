#include <iostream>
#include <windows.h>

// Totally not from stack overflow
inline int get_title_bar_thickness(const HWND window_handle)
{
    RECT window_rectangle, client_rectangle;
    int height, width;
    GetWindowRect(window_handle, &window_rectangle);
    GetClientRect(window_handle, &client_rectangle);
    height = (window_rectangle.bottom - window_rectangle.top) -
        (client_rectangle.bottom - client_rectangle.top);
    width = (window_rectangle.right - window_rectangle.left) -
        (client_rectangle.right - client_rectangle.left);
    return height - (width / 2);
}

// Also totally not from stack overflow
bool isFullscreen(HWND window)
{
    RECT a, b;
    GetWindowRect(window, &a);
    GetWindowRect(GetDesktopWindow(), &b);
    return (a.left == b.left &&
        a.top == b.top &&
        a.right == b.right &&
        a.bottom == b.bottom);
}

int main()
{
    SetConsoleTitleA("Cursor Lock by Figment (FigmentBoy)");

    std::cout << "Your cursor is now locked to GD when you have it selected! If you want to move your mouse outside of the GD window, you can press alt and it will unlock your mouse! Also, you can alt+tab to move to another program." << std::endl << std::endl << "Made by Figment (FigmentBoy)" << std::endl;

    RECT full, prev;
    GetClipCursor(&full);
    prev = full;

    while (true) {
        TCHAR windowTxt;
        HWND window = GetForegroundWindow();

        std::string windowStr(&windowTxt);


        if (GetWindowTextA(window, &windowTxt, 18)) {
            if (windowStr == "Geometry Dash" && !(GetKeyState(VK_LMENU) & 0x8000 || GetKeyState(VK_RMENU) & 0x8000)) {
                RECT rect;
                GetWindowRect(window, &rect);

                if (!isFullscreen(window)) {
                    rect.left += 8;
                    rect.top += get_title_bar_thickness(window);
                    rect.right -= 8;
                    rect.bottom -= 8;
                }
                
                ClipCursor(&rect);
                prev = rect;
            }
            else {
                if (prev.left != full.left && prev.top != full.top && prev.right != full.right && prev.bottom != full.bottom) {
                    ClipCursor(&full);
                    prev = full;
                }
            }
        }
    }
}

