#include <iostream>

int main()
{
    printf("Привет, Мир!");

    typedef struct {
        char name[50];       // имя игрока (строка, максимум 49 символов + '\0')
        int timeSpent;       // время игры в секундах
        int openedCells;     // количество открытых клеток
        int mistakes;        // число ошибок (например, неверные флаги или взрывы)
        int bestTime;        // лучшая попытка (время в секундах, меньше — лучше)
    } Player;

}

