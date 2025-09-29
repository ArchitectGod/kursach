#include <iostream>

int main()
{

}

typedef struct {
    char name[50];       // имя игрока (строка, максимум 49 символов + '\0')
    int timeSpent;       // время игры в секундах
    int openedCells;     // количество открытых клеток
    int mistakes;        // число ошибок (например, неверные флаги или взрывы)
    int bestTime;        // лучшая попытка (время в секундах, меньше — лучше)
} Player;

int toggleFlag(Board board, int x, int y, Player player)
{
    int index = y * board.width + x; // Вычисление индекса клетки в массиве
    if (x < 0 || x >= board.width || y < 0 || y >= board.height) // Проверка, корректны ли координаты
    {
        return -1; // Ошибка! координаты вне поля
    }
    Cell cell = board.cells[index]; // Получаем клетку
    if (cell.isOpen == 1) // Если клетка открыта
    {
        return 0; // Флаг на открытую клетку нельзя поставить
    }
    if (cell.isFlag == 0) // Если на клетке нет флага
    {
        board.cells[index].isFlag = 1; // Устанавливаем флаг
        if (cell.isBomb == 0) // Если на клетке нет бомбы
        {
            player.mistakes = player.mistakes + 1; // +ошибка из-за неправильного отмеченного флага
        }
    }
    else // Если на клетке есть флаг
    {
        board.cells[index].isFlag = 0; // Снимаем флаг
        if (cell.isBomb == 0)
        {
            player.mistakes = player.mistakes - 1; // Убираем ошибку, если флаг был неверный
        }
    }
    return 0; // Всё прошло успешно, игра продолжается
}


typedef struct {
    char name[50];//Имя
    int time; //Потраченное время
    int height;//Высота поля
    int width;//Ширина поля
    int bombs;//Количество бомб
    int day;//день
    int month;//Месяц
    int age;//Год
    int win;//Победа ли 1- да 2 - взрыв
}leaderboard;

// В разработке
int printleaderboard() 
{
//    FILE* fptr; // Создание указателя на файл
//    fptr = fopen("Gamefile.txt", "r"); // Открытие файла
//    // Проверка на открытие
//    leaderboard leaderboard; // Структура для временного хранения
//    printf(); //Шапка
//    while (fscanf() != EOF) // Чтение из файла
//    {
//        printf(); // Печать
//    }
//    // При успехе возвращает 0 при неудаче ( Не открылся файл ) 1
}

// В разработке
int saveleaderboard(leaderboard leaderboard)
{
//    FILE fptr    Создание указателя на файл
//        fptr = fopen   Открытие файла
//        ..Обработка открытия файла
//        fprintf Сохранение в файл
//        При удаче возвращает 0 при неудаче 1
}