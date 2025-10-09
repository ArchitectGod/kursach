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

typedef struct {
    Board* board;        // указатель на игровое поле
    Player* player;      // указатель на игрока
    int state;           // 0 - RUNNING, 1 - WON, 2 - LOST
    time_t startTime;    // время начала
    time_t pauseTime;    // время паузы
} Game;

typedef struct {
    int autoBombs;  // 1 - автоматически расставлять бомбы
    int sounds;     // 1 - звуки включены
    int difficulty; // 0 - легко, 1 - средне, 2 - сложно
} Settings;

typedef struct {
    char filename[100]; //имя файла для записи
    FILE* file; //указатель на файл
} Logger;

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

// Создание новой клетки
Cell createCell(int x, int y) {
    Cell cell;
    cell.isBomb = 0;
    cell.isOpen = 0;
    cell.isFlag = 0;
    cell.countBomb = 0;
    cell.coordinateX = x;
    cell.coordinateY = y;
    return cell;
}

// Вывод информации о клетке
void printCell(Cell cell) {
    printf("Клетка [%d,%d]: ", cell.coordinateX, cell.coordinateY);
    if (cell.isOpen) {
        if (cell.isBomb) {
            printf("Бомба");
        }
        else {
            printf("Бомб вокруг: %d", cell.countBomb);
        }
    }
    else if (cell.isFlag) {
        printf("Флаг");
    }
    else {
        printf("Закрыта");
    }
    printf("\n");
}

// Открыть клетку
void openCell(Cell* cell) {
    cell->isOpen = 1;
    cell->isFlag = 0;
}

// Поставить/убрать флаг
void toggleFlag(Cell* cell) {
    if (!cell->isOpen) {
        cell->isFlag = !cell->isFlag;
    }
}

// Установить бомбу
void setBomb(Cell* cell) {
    cell->isBomb = 1;
}


// Создание поля
Board* createBoard(int width, int height, int totalBombs) {
    Board* board = (Board*)malloc(sizeof(Board));
    board->width = width;
    board->height = height;
    board->totalBombs = totalBombs;
    board->safeCellsLeft = width * height - totalBombs;
    board->cells = (Cell*)malloc(width * height * sizeof(Cell));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            board->cells[y * width + x] = createCell(x, y);
        }
    }
    return board;
}

// Вывод поля
void printBoard(Board* board) {
    printf("   ");
    for (int x = 0; x < board->width; x++) {
        printf("%2d ", x);
    }
    printf("\n");

    for (int y = 0; y < board->height; y++) {
        printf("%2d ", y);
        for (int x = 0; x < board->width; x++) {
            Cell cell = board->cells[y * board->width + x];
            if (cell.isOpen) {
                if (cell.isBomb) {
                    printf(" * ");
                }
                else {
                    printf(" %d ", cell.countBomb);
                }
            }
            else if (cell.isFlag) {
                printf(" F ");
            }
            else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

// Получить клетку по координатам
Cell* getCell(Board* board, int x, int y) {
    if (x >= 0 && x < board->width && y >= 0 && y < board->height) {
        return &board->cells[y * board->width + x];
    }
    return NULL;
}

// Уменьшить счетчик безопасных клеток
void decreaseSafeCells(Board* board) {
    if (board->safeCellsLeft > 0) {
        board->safeCellsLeft--;
    }
}

// Проверить победу
int isGameWon(Board* board) {
    return board->safeCellsLeft == 0;
}

// Расставить бомбы
void placeBombs(Board* board, int firstX, int firstY) {
    int bombsPlaced = 0;
    while (bombsPlaced < board->totalBombs) {
        int x = rand() % board->width;
        int y = rand() % board->height;

        if ((abs(x - firstX) <= 1 && abs(y - firstY) <= 1) ||
            getCell(board, x, y)->isBomb) {
            continue;
        }

        setBomb(getCell(board, x, y));
        bombsPlaced++;
    }
}

// Посчитать бомбы вокруг
void calculateBombCounts(Board* board) {
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            Cell* cell = getCell(board, x, y);
            if (!cell->isBomb) {
                int count = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;
                        Cell* neighbor = getCell(board, x + dx, y + dy);
                        if (neighbor && neighbor->isBomb) {
                            count++;
                        }
                    }
                }
                cell->countBomb = count;
            }
        }
    }
}


// Создание игры
Game* createGame(Board* board, Player* player) {
    Game* game = (Game*)malloc(sizeof(Game));
    game->board = board;
    game->player = player;
    game->state = 0;
    game->startTime = time(NULL);
    game->pauseTime = 0;
    return game;
}

// Вывод состояния игры
void printGame(Game* game) {
    printf("=== ИГРА ===\n");
    printf("Статус: ");
    switch (game->state) {
        case 0: printf("В процессе\n"); break;
        case 1: printf("ПОБЕДА!\n"); break;
        case 2: printf("ПРОИГРЫШ\n"); break;
    }
}

// Победа
void winGame(Game* game) {
    game->state = 1;
}

// Проигрыш
void loseGame(Game* game) {
    game->state = 2;
}

// Проверить идет ли игра
int isGameRunning(Game* game) {
    return game->state == 0;
}

// Получить время игры
int getGameTime(Game* game) {
    return (int)(time(NULL) - game->startTime);
}