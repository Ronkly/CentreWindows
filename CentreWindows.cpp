#include <windows.h> // Now we interact wiht WINDOWS
#include <iostream> // This one is created for interacting with the console
// space...
HHOOK keyboardHook;         // This thing exists so I... We could track your RIGHT SHIFT
int spaceCount = 0;         // Just counting shifts
DWORD lastPressTime = 0;    // We gotta track time, right?
// Space?
// The core function
void CenterActiveWindow() { // The name
    HWND hwnd = GetForegroundWindow(); // We find the active window
    if (!hwnd) return; // If we don't find it, we ignore shifts
    // space......
    RECT rect; // Creating a variable/structure for our window dimensions
    if (!GetWindowRect(hwnd, &rect)) return; // If we can't get the dimensions, we GET OUT
    // mmmm, space
    int width = rect.right - rect.left;                 // The window has a width
    int height = rect.bottom - rect.top;                // and a height, right?
    // SPACEEEEE
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);    // The screen does so
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);   // too
    // how did I scream the silent e last time?
    int x = (screenWidth - width) / 2;                  // Then we find the perfect point for the left
    int y = (screenHeight - height) / 2;                // bottom corner of the window?
    // spa ce
    MoveWindow(hwnd, x, y, width, height, TRUE);        // THE PROGRAM WORKS (but only for 1 screen I guess)
} // The end of the core function
// Space!
// Checking if the shift is actually a shift and waiting for other shifts or activating the core function
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) { // Read above
    if (nCode == HC_ACTION) { // Is there are press?
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam; // I don't understand this one. Actually, I like C# more but C++ is faster so here we are
        if (wParam == WM_KEYDOWN && p->vkCode == VK_RSHIFT) { // Btw, I'm going to track if the key was lifted later
            DWORD currentTime = GetTickCount64();  // We gotta track time, right?
            if (currentTime - lastPressTime < 500) // Checking if it's a series of shifts
                spaceCount++;           // Just counting shifts
            else                        // Oh no, the previous time we pressed right shift (it's not pressed often) was looong ago so...
                spaceCount = 1;         // ...now the last time we pressed Shift is just 1!
            lastPressTime = currentTime;// We gotta track time, right?
            // Space... Space? SPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACE! I'M IN SPACE
            if (spaceCount == 3) {      // Oh, we got 3 shifts?
                CenterActiveWindow();   // Now we're cetring
                spaceCount = 0;         // Now we're finished with this centring!
            } // cLosIng if
        } // closinG iF
    } // closing if
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam); // Waiting for the next shift
} // Stops checking if the shift is actu... You got it
// SPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACE
// Program headquarters
int main() { // Yeah, it's just a console program that needs the black rectangle running, I'm going to change that.
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0); // This thing tracks right Shift press, I guess
    if (!keyboardHook) {  // The previous line fails
        std::cout << "Error setting the hook!\n"; // Console out
        return 1; // Bye bye
    } // Closing if
    // spaces exist to be filled, right?
    std::cout << "The program is running and you can easily close it closing the console."; // Giving you the info
    // and I'm in space
    #pragma region idk
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
             TranslateMessage(&msg);
             DispatchMessage(&msg);
         }
    #pragma endregion
    UnhookWindowsHookEx(keyboardHook); // The program stops checking the Shift key
    return 0; // THE END
} // Closing main
// Nice