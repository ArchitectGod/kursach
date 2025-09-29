#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{

}

typedef struct {
    int isBomb; //1 yes or 0 no
    int isOpen; //1 yes or 0 no
    int isFlag; //1 yes or 0 no
    int countBomb; //количество бомб вокруг
    int coordinateX; //координата клетки по Х
    int coordinateY; //координата клетки по У
} Cell;

typedef struct {
    int width;          // ширина поля
    int height;         // высота поля
    int totalBombs;     // общее количество бомб
    int safeCellsLeft;  // количество закрытых безопасных клеток
    Cell* cells;        // массив клеток
} Board;

typedef struct {
    char name[50];       // имя игрока (строка, максимум 49 символов + '\0')
    int timeSpent;       // время игры в секундах
    int openedCells;     // количество открытых клеток
    int mistakes;        // число ошибок (например, неверные флаги или взрывы)
    int bestTime;        // лучшая попытка (время в секундах, меньше — лучше)
} Player;

typedef struct Menu {
    char** items; // массив строк пунктов меню
    int itemCount; // количество пунктов
    int selectedIndex; // выбранный пункт
    int menuType;// тип меню (0-главное, 1-сложность, и т.д.)
    void (*displayFunc)(struct Menu*); // функция отображения
    void (*handleInputFunc)(struct Menu*, char); // функция обработки ввода
    void* userData; // пользовательские данные (для игры, настроек и т.д.)
} Menu;

int openCell(Board board, int x, int y, Player player)
{
    int index = y * board.width + x; // вычисление индекса клетки в одномерном массиве
    if (x < 0 || x >= board.width || y < 0 || y >= board.height) //проверка координат
        return -1; // ошибка: координаты вне поля
    Cell cell = board.cells[index];
    if (cell.isOpen == 1 || cell.isFlag == 1) // проверка состояния клетки
        return 0; // клетка не может быть открыта
    board.cells[index].isOpen = 1; //открытие клетки
    player.openedCells = player.openedCells + 1;
    if (cell.isBomb == 1) // в случае, если в клетке скрывается бомба
    {
        player.mistakes = player.mistakes + 1;
        return 1; // проигрыш (взрыв)
    }
    if (cell.isBomb == 0) // в случае, если клетка безопасная
    {
        board.closedSafeCells = board.closedSafeCells - 1;
        if (cell.countBomb == 0) // в случае, если вокруг нет бомб
        {
            (алгоритм для открытия всех клеток вокруг)
        }
    }
    if (board.closedSafeCells == 0)  // в случае, если все безопасные клетки открыты
        return 2;
    return 0; // игра продолжается
}

int toggleFlag(Board board, int x, int y, Player player)
{
    int index = y * board.width + x; //Вычисление индекса клетки в массиве
    if (x < 0 || x >= board.width || y < 0 || y >= board.height) //Проверка, корректны ли координаты
    {
        return -1; //Ошибка! координаты вне поля
    }
    Cell cell = board.cells[index]; //Получаем клетку
    if (cell.isOpen == 1) //Если клетка открыта
    {
        return 0; //Флаг на открытую клетку нельзя поставить
    }
    if (cell.isFlag == 0) //Если на клетке нет флага
    {
        board.cells[index].isFlag = 1; // Устанавливаем флаг
        if (cell.isBomb == 0) //Если на клетке нет бомбы
        {
            player.mistakes = player.mistakes + 1; //+ошибка из-за неправильного отмеченного флага
        }
    }
    else //Если на клетке есть флаг
    {
        board.cells[index].isFlag = 0; //Снимаем флаг
        if (cell.isBomb == 0)
        {
            player.mistakes = player.mistakes - 1; //Убираем ошибку, если флаг был неверный
        }
    }
    return 0; //Всё прошло успешно, игра продолжается
}

Board* createBoard(int width, int height, int bombsTotal) {
    // Проверка валидности параметров
    if (width <= 0 height <= 0 bombsTotal <= 0) {
        printf("Ошибка: недопустимые параметры поля\n");
        return NULL;
    }
    if (bombsTotal >= width * height) {
        printf("Ошибка: слишком много бомб для данного размера поля\n");
        return NULL;
    }
    // Выделение памяти для структуры Board
    Board* board = (Board*)malloc(sizeof(Board));
    if (board == NULL) {
        printf("Ошибка выделения памяти для поля\n");
        return NULL;
    }
    // Инициализация параметров поля
    board->width = width;
    board->height = height;
    board->bombsTotal = bombsTotal;
    board->closedSafeCells = (width * height) - bombsTotal;
    //Здесь необходимо добавить выделение памяти для массива клеток
    for (int i = 0; i < totalCells; i++) {
          // Инициализация всех клеток здесь.
    }
    return board;
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