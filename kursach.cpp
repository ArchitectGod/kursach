#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{

}

typedef struct {
    bool isBomb;        // есть ли бомба
    bool isRevealed;    // открыта ли клетка
    bool isFlagged;     // стоит ли флажок
    int adjacentBombs;  // число бомб вокруг
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
//Вспомогательная функция для доступа к клетке
Cell* getCell(Board* board, int x, int y) {
    if (x < 0 || x >= board->width || y < 0 || y >= board->height) {
        return NULL; // выход за пределы
    }
    return &board->cells[y * board->width + x];
}

//Инициализация игрового поля
Board* initBoard(int width, int height, int bombs) {
    Board* board = malloc(sizeof(Board));
    if (!board) return NULL;

    board->width = width;
    board->height = height;
    board->totalBombs = bombs;
    board->safeCellsLeft = width * height - bombs;

    board->cells = calloc(width * height, sizeof(Cell));
    if (!board->cells) {
        free(board);
        return NULL;
    }

    //все клетки по умолчанию пустые
    for (int i = 0; i < width * height; i++) {
        board->cells[i].isBomb = false;
        board->cells[i].isRevealed = false;
        board->cells[i].isFlagged = false;
        board->cells[i].adjacentBombs = 0;
    }

    return board;
}

//Освобождение памяти
void freeBoard(Board* board) {
    if (!board) return;
    free(board->cells);
    free(board);
}



