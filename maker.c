#include <windows.h>
#include <stdio.h>

int main() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    printf("Rows: %d, Cols: %d\n", rows, cols);
    return 0;
}