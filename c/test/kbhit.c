#include <stdio.h>
#include <conio.h>
#include <Windows.h>

int main()
{
    while (1)
    {
        if (_kbhit())
        {
            printf("getch()=%c", _getch());
        }
        Sleep(500);
        printf("Running");
    }
}