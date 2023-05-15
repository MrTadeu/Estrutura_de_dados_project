/* #include <windows.h>
#include <stdio.h>

int main() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    printf("Rows: %d, Cols: %d\n", rows, cols);
    return 0;
} */
#include <stdio.h>
#include <windows.h>

/* struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};

void adjustWindowSize()
{
    HANDLE hStdout;
    COORD coord;
    BOOL ok;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 4;
    coord.Y = 10;
    ok = SetConsoleScreenBufferSize(hStdout, coord);

    struct SMALL_RECT test = { 0, 0, coord.X - 1, coord.Y - 1 };
    SetConsoleWindowInfo(hStdout, ok, (const SMALL_RECT*)&test);

    getchar();
} //end adjustWindowSize 

void main()
{
    adjustWindowSize();
} //end main */

/* int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT WindowSize = {0, 0, 80, 25}; // aumenta a largura para 100 e altura para 50

    SetConsoleWindowInfo(hConsole, TRUE, &WindowSize); // redimensiona a janela
    Sleep(3000); // espera 3 segundos
    printf("Era para ter mudado!!!");
    Sleep(1000);
    system("cls");
    WindowSize = (SMALL_RECT){0, 0, 120, 75}; // volta para a largura de 80 e altura de 25
    SetConsoleWindowInfo(hConsole, TRUE, &WindowSize); // redimensiona a janela novamente

    getchar();
    return 0;
} */
BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) {
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid)) {
        printf("LookupPrivilegeValue error: %u\n", GetLastError());
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {
        printf("AdjustTokenPrivileges error: %u\n", GetLastError());
        return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        printf("The token does not have the specified privilege. \n");
        return FALSE;
    }

    return TRUE;
}

int getprev(HANDLE hConsole, COORD bufferSize, SMALL_RECT windowSize) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        if (SetPrivilege(hToken, SE_DEBUG_NAME, TRUE)) { // altera o privilégio para depuração (DEBUG)
            // O restante do código aqui

            if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) { // ajusta o tamanho do buffer
                printf("Erro ao ajustar o tamanho do buffer: %u\n", GetLastError());
                return 1;
            }

            if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) { // redimensiona a janela
                printf("Erro ao redimensionar a janela: %u\n", GetLastError());
                return 1;
            }

            // O restante do código aqui

            if (!SetPrivilege(hToken, SE_DEBUG_NAME, FALSE)) { // restaura o privilégio
                printf("Erro ao restaurar o privilégio: %u\n", GetLastError());
                return 1;
            }
        } else {
            printf("Não foi possível ajustar o privilégio para depuração.\n");
            return 1;
        }
        CloseHandle(hToken);
    } else {
        printf("Erro ao abrir o token do processo: %u\n", GetLastError());
        return 1;
    }

    return 0;
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {100, 50}; // aumenta a largura para 100 e altura para 50
    SMALL_RECT windowSize = {0, 0, 99, 49};
    getprev(hConsole, bufferSize, windowSize);

    SetConsoleScreenBufferSize(hConsole, bufferSize); // ajusta o tamanho do buffer
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize); // redimensiona a janela

    Sleep(3000); // espera 3 segundos
    printf("Era para ter mudado!!!");
    Sleep(1000);
    system("cls");

    bufferSize = (COORD){80, 25}; // volta para a largura de 80 e altura de 25
    windowSize = (SMALL_RECT){0, 0, 79, 24};

    SetConsoleScreenBufferSize(hConsole, bufferSize); // ajusta o tamanho do buffer novamente
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize); // redimensiona a janela novamente

    getchar();
    return 0;
}