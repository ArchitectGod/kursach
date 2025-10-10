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

// Создание игрока
Player* createPlayer(const char* name) {
    Player* player = (Player*)malloc(sizeof(Player));
    strcpy(player->name, name);
    player->timeSpent = 0;
    player->openedCells = 0;
    player->mistakes = 0;
    player->bestTime = 0;
    return player;
}

// Вывод информации об игроке
void printPlayer(Player* player) {
    printf("Игрок: %s\n", player->name);
    printf("Время: %d сек, Открыто: %d, Ошибок: %d\n",
        player->timeSpent, player->openedCells, player->mistakes);
}

// Добавить ошибку
void addMistake(Player* player) {
    player->mistakes++;
}

// Добавить открытую клетку
void addOpenedCell(Player* player) {
    player->openedCells++;
}

// Обновить лучшее время
void updateBestTime(Player* player) {
    if (player->bestTime == 0 || player->timeSpent < player->bestTime) {
        player->bestTime = player->timeSpent;
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

// Создание настроек
Settings* createSettings() {
    Settings* settings = (Settings*)malloc(sizeof(Settings));
    settings->autoBombs = 1;
    settings->difficulty = 0;
    return settings;
}

// Вывод настроек
void printSettings(Settings* settings) {
    printf("=== НАСТРОЙКИ ===\n");
    printf("Авторасстановка бомб: %s\n", settings->autoBombs ? "Вкл" : "Выкл");
    printf("Сложность: ");
    switch (settings->difficulty) {
    case 0: printf("Легко\n"); break;
    case 1: printf("Средне\n"); break;
    case 2: printf("Сложно\n"); break;
    }
}

// Создать поле по сложности
Board* createBoardByDifficulty(Settings* settings) {
    switch (settings->difficulty) {
    case 0: return createBoard(9, 9, 10);
    case 1: return createBoard(16, 16, 40);
    case 2: return createBoard(30, 16, 99);
    default: return createBoard(9, 9, 10);
    }
}

// Создание логгера
Logger* createLogger(const char* filename) {
    Logger* logger = (Logger*)malloc(sizeof(Logger));
    strcpy(logger->filename, filename);
    logger->file = fopen(filename, "a");
    return logger;
}

// Запись в лог
void logMessage(Logger* logger, const char* message) {
    if (logger->file) {
        time_t now = time(NULL);
        fprintf(logger->file, "[%s] %s\n", ctime(&now), message);
        fflush(logger->file);
    }
}

// Закрыть логгер
void closeLogger(Logger* logger) {
    if (logger->file) {
        fclose(logger->file);
    }
}

// Создание записи
leaderboard* createLeaderboard(const char* name, int time, int width, int height, int bombs, int win) {
    leaderboard* lb = (leaderboard*)malloc(sizeof(leaderboard));
    strcpy(lb->name, name);
    lb->time = time;
    lb->width = width;
    lb->height = height;
    lb->bombs = bombs;
    lb->win = win;
    
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    lb->day = tm_info->tm_mday;
    lb->month = tm_info->tm_mon + 1;
    lb->age = tm_info->tm_year + 1900;
    
    return lb;
}

// Вывод записи
void printLeaderboard(leaderboard* lb) {
    printf("%s: %d сек, %dx%d, %s\n", 
           lb->name, lb->time, lb->width, lb->height,
           lb->win ? "ПОБЕДА" : "ПРОИГРЫШ");
}

// Сохранить запись
void saveLeaderboard(leaderboard* lb, const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                lb->name, lb->time, lb->height, lb->width, lb->bombs,
                lb->day, lb->month, lb->age, lb->win);
        fclose(file);
    }
}