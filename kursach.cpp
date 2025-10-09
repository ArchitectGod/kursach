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