#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <stdbool.h>
#include <ctime>
#include <locale.h>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int safeInputInt(const char* prompt = "") {
    int value;
    while (true) {
        if (prompt[0] != '\0') {
            printf("%s", prompt);
        }

        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &value) == 1) {
                return value;
            }
        }
        printf("Неверный ввод! Введите целое число.\n");
    }
}

void safeInputTwoInts(int* x, int* y, const char* prompt = "") {
    while (true) {
        if (prompt[0] != '\0') {
            printf("%s", prompt);
        }

        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d %d", x, y) == 2) {
                return;
            }
        }
        printf("Неверный ввод! Введите два числа через пробел.\n");
    }
}

class Coordinate {
private:
    int x;
    int y;

public:
    Coordinate(int xCoord = 0, int yCoord = 0) : x(xCoord), y(yCoord) {}

    void print() const {
        printf("Координаты: (%d, %d)\n", x, y);
    }

    void input() {
        printf("Введите координаты X Y: ");
        scanf("%d %d", &x, &y);
        clearInputBuffer();
    }

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    bool isValid(int maxX, int maxY) const {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

class Cell {
private:
    int isBomb;
    int isOpen;
    int isFlag;
    int countBomb;
    int coordinateX;
    int coordinateY;

public:
    Cell(int x = 0, int y = 0) : isBomb(0), isOpen(0), isFlag(0), countBomb(0), coordinateX(x), coordinateY(y) {}
    Cell(int x, int y, int isBomb, int isOpen, int isFlag, int BombCount) : coordinateX(x), coordinateY(y), isBomb(isBomb), isOpen(isOpen), isFlag(isFlag), countBomb(BombCount) {}
    void print() const {
        printf("Клетка [%d,%d]: ", coordinateX, coordinateY);
        if (isOpen) {
            if (isBomb) {
                printf("Бомба");
            }
            else {
                printf("Бомб вокруг: %d", countBomb);
            }
        }
        else if (isFlag) {
            printf("Флаг");
        }
        else {
            printf("Закрыта");
        }
        printf("\n");
    }

    void inputFromUser() {
        printf("Введите состояние клетки [%d,%d] (0-закрыта, 1-открыта, 2-флаг): ", coordinateX, coordinateY);
        int state;
        scanf("%d", &state);
        clearInputBuffer();
        if (state == 1) {
            open();
        }
        else if (state == 2) {
            toggleFlag();
        }
    }

    void open() {
        if (!isOpen) {
            isOpen = 1;
            isFlag = 0;
        }
    }

    void toggleFlag() {
        if (!isOpen) {
            isFlag = !isFlag;
        }
    }

    void setBomb() {
        isBomb = 1;
    }

    void setCountBomb(int count) {
        countBomb = count;
    }

    int getIsBomb() const { return isBomb; }
    int getIsOpen() const { return isOpen; }
    int getIsFlag() const { return isFlag; }
    int getCountBomb() const { return countBomb; }
    int getX() const { return coordinateX; }
    int getY() const { return coordinateY; }
    void setIsOpen(bool open) { isOpen = open; }
    void setIsFlag(bool flag) { isFlag = flag; }
    void setIsBomb(bool bomb) { isBomb = bomb; }
};

class Board {
private:
    int width;
    int height;
    int totalBombs;
    int safeCellsLeft;
    vector<Cell> cells;
    bool bombsPlaced;

public:
    Board(int w = 9, int h = 9, int bombs = 10) : width(w), height(h), totalBombs(bombs),
        safeCellsLeft(w* h - bombs), bombsPlaced(false) {
        initializeCells();
    }
    void printdata() {
        printf("Информация о доске\n");
        printf("width - %d\nheight - %d\ntotalBombs - %d\nsafeCellsleft - %d\nbombsplaced - %d\n,sizecells - %d", width, height, totalBombs, safeCellsLeft, bombsPlaced, cells.size());
    }
    void initializeCells() {
        cells.clear();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells.emplace_back(x, y);
            }
        }
    }

    void print(char cellClosed = '#', char bomb = '*') {
        printf("   ");
        for (int x = 0; x < width; x++) {
            printf("%2d ", x);
        }
        printf("\n");

        for (int y = 0; y < height; y++) {
            printf("%2d ", y);
            for (int x = 0; x < width; x++) {
                const Cell& cell = cells[y * width + x];
                if (cell.getIsOpen()) {
                    if (cell.getIsBomb()) {
                        printf(" %c ", bomb);
                    }
                    else {
                        int count = cell.getCountBomb();
                        if (count == 0) {
                            printf(" . ");
                        }
                        else {
                            printf(" %d ", count);
                        }
                    }
                }
                else if (cell.getIsFlag()) {
                    printf(" F ");
                }
                else {
                    printf(" %c ", cellClosed);
                }
            }
            printf("\n");
        }
        int flags = countFlags();
        printf("Бомб: %d, Флагов: %d\n", totalBombs, flags);
        printf("Безопасных клеток осталось: %d\n", safeCellsLeft);
    }

    int countFlags() const {
        int count = 0;
        for (const auto& cell : cells) {
            if (cell.getIsFlag()) count++;
        }
        return count;
    }

    Cell* getCell(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return &cells[y * width + x];
        }
        return nullptr;
    }

    void decreaseSafeCells() {
        if (safeCellsLeft > 0) {
            safeCellsLeft--;
        }
    }

    bool isGameWon() const {
        return safeCellsLeft == 0;
    }

    void placeBombs(int firstX, int firstY) {
        if (bombsPlaced) return;

        int bombsPlacedCount = 0;
        while (bombsPlacedCount < totalBombs) {
            int x = rand() % width;
            int y = rand() % height;

            if ((abs(x - firstX) <= 1 && abs(y - firstY) <= 1) ||
                getCell(x, y)->getIsBomb()) {
                continue;
            }

            getCell(x, y)->setBomb();
            bombsPlacedCount++;
        }
        bombsPlaced = true;
        calculateBombCounts();
    }

    void calculateBombCounts() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Cell* cell = getCell(x, y);
                if (!cell->getIsBomb()) {
                    int count = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            Cell* neighbor = getCell(x + dx, y + dy);
                            if (neighbor && neighbor->getIsBomb()) {
                                count++;
                            }
                        }
                    }
                    cell->setCountBomb(count);
                }
            }
        }
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTotalBombs() const { return totalBombs; }
    int getSafeCellsLeft() const { return safeCellsLeft; }
    bool areBombsPlaced() const { return bombsPlaced; }

    void openAllCells() {
        for (auto& cell : cells) {
            cell.open();
        }
    }

    void revealBombs() {
        for (auto& cell : cells) {
            if (cell.getIsBomb()) {
                cell.open();
            }
        }
    }
    void reset() {
        bombsPlaced = false;
        safeCellsLeft = width * height - totalBombs;
        initializeCells();
    }

    string serialize() const {
        string data;
        data += to_string(width) + " " + to_string(height) + " " +
            to_string(totalBombs) + " " + to_string(safeCellsLeft) + " " +
            to_string(bombsPlaced) + "\n";

        for (const auto& cell : cells) {
            data += to_string(cell.getX()) + " " + to_string(cell.getY()) + " " +
                to_string(cell.getIsBomb()) + " " + to_string(cell.getIsOpen()) + " " +
                to_string(cell.getIsFlag()) + " " + to_string(cell.getCountBomb()) + "\n";
        }
        return data;
    }

    bool deserialize(istream& ss) {
        ss >> width >> height >> totalBombs >> safeCellsLeft >> bombsPlaced;

        cells.clear();
        for (int i = 0; i < width * height; i++) {
            int x, y, bomb, open, flag, count;
            if (!(ss >> x >> y >> bomb >> open >> flag >> count)) {
                return false;
            }
            Cell cell(x, y, bomb, open, flag, count);
            cells.push_back(cell);
        }
        return true;
    }
};

class Player {
private:
    string name;
    int timeSpent;
    int openedCells;
    int mistakes;
    int bestTime;

public:
    Player(const string& playerName = "") : name(playerName), timeSpent(0), openedCells(0), mistakes(0), bestTime(0) {}
    void print() const {
        printf("Игрок: %s\n", name.c_str());
        printf("Время: %d сек, Открыто: %d, Ошибок: %d, Лучшее время: %d сек\n",
            timeSpent, openedCells, mistakes, bestTime);
    }

    void inputPlayerInfo() {
        printf("Введите имя игрока: ");
        char buffer[50];
        scanf("%49s", buffer);
        name = buffer;
        clearInputBuffer();

        printf("Введите текущее время игры (сек): ");
        scanf("%d", &timeSpent);
        clearInputBuffer();
    }

    void addMistake() {
        mistakes++;
        printf("Ошибка! Всего ошибок: %d\n", mistakes);
    }

    void addOpenedCell() {
        openedCells++;
    }

    void updateBestTime() {
        if (bestTime == 0 || timeSpent < bestTime) {
            bestTime = timeSpent;
            printf("Новый рекорд: %d сек!\n", bestTime);
        }
    }

    void addTime(int seconds) {
        timeSpent += seconds;
    }
    void print() {
        printf("Информация об игроке\n");
        printf("name - %s\ntimeSpent - %d\nopenedCells - %d\nmistakes - %d\nbesttime - %d\n", name.c_str(), timeSpent, openedCells, mistakes, bestTime);
    }

    string getName() const { return name; }
    int getTimeSpent() const { return timeSpent; }
    int getOpenedCells() const { return openedCells; }
    int getMistakes() const { return mistakes; }
    int getBestTime() const { return bestTime; }

    void setTimeSpent(int time) { timeSpent = time; }
    void setName(const string& newName) { name = newName; }
    void resetStats() {
        openedCells = 0;
        mistakes = 0;
        timeSpent = 0;
    }

    string serialize() const {
        return name + " " + to_string(timeSpent) + " " +
            to_string(openedCells) + " " + to_string(mistakes) + " " +
            to_string(bestTime) + "\n";
    }

    bool deserialize(istream& ss) {
        ss >> name >> timeSpent >> openedCells >> mistakes >> bestTime;
        return true;
    }
};

class Timer {
private:
    time_t startTime;
    time_t pausedTime;
    bool isRunning;
public:
    Timer() : startTime(0), pausedTime(0), isRunning(false) {}

    void print() const {
        printf("Таймер: %d секунд, статус: %s\n", getElapsedTime(), isRunning ? "работает" : "на паузе");
    }

    void start() {
        startTime = time(NULL);
        isRunning = true;
    }

    void pause() {
        if (isRunning) {
            pausedTime = time(NULL);
            isRunning = false;
        }
    }

    void resume() {
        if (!isRunning) {
            startTime += (time(NULL) - pausedTime);
            isRunning = true;
        }
    }
    int getElapsedTime() const {
        if (isRunning) {
            return (int)(time(NULL) - startTime);
        }
        return (int)(pausedTime - startTime);
    }

    void reset() {
        startTime = 0;
        pausedTime = 0;
        isRunning = false;
    }

    bool getIsRunning() const { return isRunning; }

    string serialize() const {
        return to_string(startTime) + " " + to_string(pausedTime) + " " +
            to_string(isRunning) + "\n";
    }

    bool deserialize(istream& ss) {
        ss >> startTime >> pausedTime >> isRunning;
        return true;
    }
};

class Game {
private:
    Board* board;
    Player* player;
    int state;
    Timer timer;

public:
    Game(Board* b = nullptr, Player* p = nullptr) : board(b), player(p), state(0) {
        timer.start();
    }

    void print() const {
        printf("=== СОСТОЯНИЕ ИГРЫ ===\n");
        printf("Статус: ");
        switch (state) {
        case 0: printf("В процессе\n"); break;
        case 1: printf("ПОБЕДА!\n"); break;
        case 2: printf("ПРОИГРЫШ\n"); break;
        }
        printf("Время игры: %d сек\n", getGameTime());
        if (board) board->print();
        if (player) player->print();
    }

    void winGame() {
        state = 1;
        if (player) {
            player->updateBestTime();
        }
        printf("🎉 ПОБЕДА! 🎉\n");
    }

    void loseGame() {
        state = 2;
        if (player) {
            player->addMistake();
        }
        printf("💥 ПРОИГРЫШ! 💥\n");
    }

    bool isGameRunning() const {
        return state == 0;
    }

    int getGameTime() const {
        return timer.getElapsedTime();
    }

    void pauseGame() {
        timer.pause();
        printf("Игра на паузе\n");
    }

    void resumeGame() {
        timer.resume();
        printf("Игра продолжается\n");
    }

    void makeMove(int x, int y, bool open = true) {
        if (!isGameRunning()) return;

        Cell* cell = board->getCell(x, y);
        if (!cell || cell->getIsOpen()) return;

        if (open) {
            if (!board->areBombsPlaced()) {
                board->placeBombs(x, y);
            }

            if (cell->getIsFlag()) {
                printf("Клетка помечена флагом! Сначала уберите флаг.\n");
                return;
            }

            cell->open();
            board->decreaseSafeCells();
            if (player) player->addOpenedCell();

            if (cell->getIsBomb()) {
                board->revealBombs();
                loseGame();
            }
            else if (board->isGameWon()) {
                winGame();
            }
        }
        else {
            cell->toggleFlag();
        }
    }

    int getState() const { return state; }
    Board* getBoard() const { return board; }
    Player* getPlayer() const { return player; }
    Timer& getTimer() { return timer; }

    void setBoard(Board* b) { board = b; }
    void setPlayer(Player* p) { player = p; }
    void setState(int s) { state = s; }

    void reset() {
        state = 0;
        timer.reset();
        timer.start();
        if (player) player->resetStats();
        if (board) board->reset();
    }

    string serialize() {
        string data;
        if (timer.getIsRunning()) {
            timer.pause();
        }
        data += timer.serialize();
        if (player) {
            data += player->serialize();
        }
        if (board) {
            data += board->serialize();
        }
        return data;
    }

    void deserialize(const string& data) {
        stringstream ss(data);
        timer.deserialize(ss);
        player->deserialize(ss);
        board->deserialize(ss);
    }
};

class Settings {
private:
    int autoBombs;
    int sounds;
    int difficulty;
    string themeName;

public:
    Settings() : autoBombs(1), sounds(1), difficulty(0), themeName("classic") {}

    void print() const {
        printf("=== НАСТРОЙКИ ===\n");
        printf("Авторасстановка бомб: %s\n", autoBombs ? "Вкл" : "Выкл");
        printf("Звуки: %s\n", sounds ? "Вкл" : "Выкл");
        printf("Сложность: ");
        switch (difficulty) {
        case 0: printf("Легко\n"); break;
        case 1: printf("Средне\n"); break;
        case 2: printf("Сложно\n"); break;
        }
        printf("Тема: %s\n", themeName.c_str());
    }

    void inputSettings() {
        printf("=== ВВОД НАСТРОЕК ===\n");
        printf("Авторасстановка бомб (0-Выкл, 1-Вкл): ");
        autoBombs = safeInputInt();

        printf("Звуки (0-Выкл, 1-Вкл): ");
        sounds = safeInputInt();

        printf("Сложность (0-Легко, 1-Средне, 2-Сложно): ");
        difficulty = safeInputInt();

        printf("Тема (1-classic, 2-simple): ");
        int themeChoice = safeInputInt();
        themeName = (themeChoice == 2) ? "simple" : "classic";
    }

    void toggleAutoBombs() {
        autoBombs = !autoBombs;
        printf("Авторасстановка бомб: %s\n", autoBombs ? "ВКЛ" : "ВЫКЛ");
    }

    void toggleSounds() {
        sounds = !sounds;
        printf("Звуки: %s\n", sounds ? "ВКЛ" : "ВЫКЛ");
    }

    void setDifficulty(int level) {
        if (level >= 0 && level <= 2) {
            difficulty = level;
            const char* levels[] = { "Легко", "Средне", "Сложно" };
            printf("Сложность установлена: %s\n", levels[level]);
        }
    }

    void setTheme(const string& theme) {
        themeName = theme;
        printf("Тема установлена: %s\n", theme.c_str());
    }

    Board* createBoardByDifficulty() const {
        switch (difficulty) {
        case 0: return new Board(9, 9, 10);
        case 1: return new Board(16, 16, 40);
        case 2: return new Board(30, 16, 99);
        default: return new Board(9, 9, 10);
        }
    }

    int getAutoBombs() const { return autoBombs; }
    int getSounds() const { return sounds; }
    int getDifficulty() const { return difficulty; }
    string getTheme() const { return themeName; }
};

class Logger {
private:
    string filename;
    FILE* file;

public:
    Logger(const string& fname = "game_log.txt") : filename(fname) {
        file = fopen(filename.c_str(), "a");
        if (!file) {
            printf("Не удалось открыть файл лога: %s\n", filename.c_str());
        }
    }

    ~Logger() {
        if (file) {
            fclose(file);
        }
    }

    void print() const {
        printf("Логгер: файл %s\n", filename.c_str());
    }

    void logMessage(const string& message) {
        if (file) {
            time_t now = time(NULL);
            fprintf(file, "[%s] %s\n", ctime(&now), message.c_str());
            fflush(file);
        }
        printf("[LOG] %s\n", message.c_str());
    }

    void logGameStart(const string& playerName) {
        logMessage("Игра начата игроком: " + playerName);
    }

    void logGameEnd(const string& playerName, bool won) {
        logMessage("Игра завершена игроком: " + playerName + " Результат: " + (won ? "ПОБЕДА" : "ПОРАЖЕНИЕ"));
    }

    void logMove(const string& playerName, int x, int y, const string& action) {
        logMessage("Игрок " + playerName + ": " + action + " на [" + to_string(x) + "," + to_string(y) + "]");
    }
};

class Menu {
public:
    int showMainMenu() {
        printf("=== САПЕР ===\n");
        printf("1. Новая игра\n");
        printf("2. Продолжить\n");
        printf("3. Загрузить\n");
        printf("4. Настройки\n");
        printf("5. Таблица лидеров\n");
        printf("6. Достижения\n");
        printf("7. Статистика\n");
        printf("8. Профиль игрока\n");
        printf("9. История игр\n");
        printf("10. Помощь\n");
        printf("11. Выход\n");
        return safeInputInt("Выберите: ");
    }

    int showGameMenu() {
        printf("=== ИГРОВОЕ МЕНЮ ===\n");
        printf("1. Продолжить\n");
        printf("2. Сохранить\n");
        printf("3. В меню\n");
        return safeInputInt("Выберите: ");
    }
};

class GameStats {
private:
    int gamesPlayed;
    int gamesWon;
    int totalTime;
    int bestTime;

public:
    GameStats() : gamesPlayed(0), gamesWon(0), totalTime(0), bestTime(0) {}

    void print() const {
        printf("=== СТАТИСТИКА ===\n");
        printf("Игр сыграно: %d\n", gamesPlayed);
        printf("Побед: %d\n", gamesWon);
        printf("Процент побед: %.1f%%\n", gamesPlayed > 0 ? (float)gamesWon / gamesPlayed * 100 : 0);
        printf("Лучшее время: %d сек\n", bestTime);
        printf("Среднее время: %.1f сек\n", gamesPlayed > 0 ? (float)totalTime / gamesPlayed : 0);
    }

    void addGame(bool won, int time) {
        gamesPlayed++;
        if (won) {
            gamesWon++;
            totalTime += time;
            if (time < bestTime || bestTime == 0) {
                bestTime = time;
            }
        }
    }

    void reset() {
        gamesPlayed = 0;
        gamesWon = 0;
        totalTime = 0;
        bestTime = 0;
    }

    void saveToFile(const string& filename) {
        FILE* file = fopen(filename.c_str(), "a");
        if (file) {
            time_t now = time(NULL);
            fprintf(file, "Статистика от %s", ctime(&now));
            fprintf(file, "Игр сыграно: %d\n", gamesPlayed);
            fprintf(file, "Побед: %d\n", gamesWon);
            fprintf(file, "Лучшее время: %d сек\n", bestTime);
            fprintf(file, "-----------------\n");
            fclose(file);
        }
    }
};

class RandomGenerator {
private:
    int seed;

public:
    RandomGenerator() {
        seed = time(NULL);
        srand(seed);
    }

    RandomGenerator(int s) : seed(s) {
        srand(seed);
    }

    void print() const {
        printf("Генератор случайных чисел, seed: %d\n", seed);
    }

    int getRandom(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    Coordinate getRandomCoordinate(int maxX, int maxY) {
        return Coordinate(getRandom(0, maxX - 1), getRandom(0, maxY - 1));
    }
};

class Renderer {
private:
    char cellClosed;
    char bombChar;

public:
    Renderer(char closed = '#', char bomb = '*') : cellClosed(closed), bombChar(bomb) {}

    void setTheme(char closed, char bomb) {
        cellClosed = closed;
        bombChar = bomb;
    }

    void renderBoard(Board& board) {
        board.print(cellClosed, bombChar);
    }

    void renderPlayer(const Player& player) {
        player.print();
    }

    void renderGame(const Game& game) {
        game.print();
    }

    void renderGameState(const Game& game, const string& playerName) {
        printf("=== САПЕР ===\n");
        printf("Время: %d сек\n", game.getGameTime());
        printf("Игрок: %s\n", playerName.c_str());
        printf("\n");
        if (game.getBoard()) {
            renderBoard(*game.getBoard());
        }
        printf("\n");
    }
};

class InputHandler {
public:
    Coordinate getCellCoordinates() {
        int x, y;
        safeInputTwoInts(&x, &y, "Введите координаты X Y: ");
        return Coordinate(x, y);
    }

    string getPlayerName() {
        string name;
        printf("Введите имя игрока: ");
        char buffer[50];
        scanf("%49s", buffer);
        clearInputBuffer();
        name = buffer;
        return name;
    }
    int getMenuChoice(int min, int max) {
        while (true) {
            int choice = safeInputInt("Выберите действие: ");
            if (choice >= min && choice <= max) {
                return choice;
            }
            printf("Неверный выбор! Введите число от %d до %d.\n", min, max);
        }
    }

    char getAction() {
        char action;
        printf("Выберите действие (o-открыть, f-флаг, h-помощь, m-меню, q-выход): ");
        scanf(" %c", &action);
        clearInputBuffer();
        return action;
    }
};

class Validator {
public:
    bool isValidCoordinate(const Coordinate& coord, int maxX, int maxY) {
        bool valid = coord.getX() >= 0 && coord.getX() < maxX &&
            coord.getY() >= 0 && coord.getY() < maxY;
        if (!valid) {
            printf("Неверные координаты! Допустимый диапазон: X:0-%d, Y:0-%d\n", maxX - 1, maxY - 1);
        }
        return valid;
    }

    bool isValidName(const string& name) {
        bool valid = !name.empty() && name.length() <= 49;
        if (!valid) {
            printf("Неверное имя! Длина должна быть 1-49 символов\n");
        }
        return valid;
    }

    bool isValidBombCount(int bombs, int width, int height) {
        bool valid = bombs > 0 && bombs < width * height;
        if (!valid) {
            printf("Неверное количество бомб! Должно быть от 1 до %d\n", width * height - 1);
        }
        return valid;
    }
};

class GameFactory {
public:
    void print() const {
        printf("Фабрика игр: готова создавать игры\n");
    }

    Game* createEasyGame(const string& playerName) {
        printf("Создаю лёгкую игру для %s\n", playerName.c_str());
        Board* board = new Board(9, 9, 10);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }

    Game* createMediumGame(const string& playerName) {
        printf("Создаю среднюю игру для %s\n", playerName.c_str());
        Board* board = new Board(16, 16, 40);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }

    Game* createHardGame(const string& playerName) {
        printf("Создаю сложную игру для %s\n", playerName.c_str());
        Board* board = new Board(30, 16, 99);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }

    Game* createCustomGame(const string& playerName, int width, int height, int bombs) {
        printf("Создаю пользовательскую игру для %s\n", playerName.c_str());
        Board* board = new Board(width, height, bombs);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }
};

class ScoringSystem {
private:
    int baseScore;
    int timeBonus;
    int mistakePenalty;

public:
    ScoringSystem() : baseScore(1000), timeBonus(50), mistakePenalty(100) {}

    void print() const {
        printf("Система подсчета очков\n");
        printf("Базовые очки: %d, Бонус за время: %d, Штраф за ошибку: %d\n",
            baseScore, timeBonus, mistakePenalty);
    }

    int calculateScore(const Player& player, int gameTime) {
        int score = baseScore;
        score += (3600 - gameTime) / 60 * timeBonus;
        score -= player.getMistakes() * mistakePenalty;
        return score > 0 ? score : 0;
    }

    int calculateWinScore(bool won, int time, int mistakes) {
        if (!won) return 0;
        int score = baseScore + (1800 - time) / 30 * timeBonus - mistakes * mistakePenalty;
        return score > 0 ? score : 0;
    }
};

class Notifier {
public:
    void showWinMessage() {
        printf("\n*************** ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ! ***************\n");
    }

    void showLoseMessage() {
        printf("\n* ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ! *\n");
    }

    void showErrorMessage(const string& message) {
        printf("X ОШИБКА: %s\n", message.c_str());
    }

    void showInfoMessage(const string& message) {
        printf("[i]  %s\n", message.c_str());
    }
};

class Difficulty {
private:
    string level;
    int width;
    int height;
    int bombs;
public:
    Difficulty(const string& lvl = "Легко", int w = 9, int h = 9, int b = 10) : level(lvl), width(w), height(h), bombs(b) {}

    void print() const {
        printf("Уровень сложности: %s (%dx%d, %d бомб)\n", level.c_str(), width, height, bombs);
    }

    void inputDifficulty() {
        printf("Выберите сложность:\n");
        printf("1. Легко (9x9, 10 бомб)\n");
        printf("2. Средне (16x16, 40 бомб)\n");
        printf("3. Сложно (30x16, 99 бомб)\n");
        printf("4. Пользовательская\n");

        int choice = safeInputInt("Выберите: ");

        switch (choice) {
        case 1: level = "Легко"; width = 9; height = 9; bombs = 10; break;
        case 2: level = "Средне"; width = 16; height = 16; bombs = 40; break;
        case 3: level = "Сложно"; width = 30; height = 16; bombs = 99; break;
        case 4:
            level = "Пользовательская";
            width = safeInputInt("Введите ширину: ");
            height = safeInputInt("Введите высоту: ");
            bombs = safeInputInt("Введите количество бомб: ");
            break;
        default:
            level = "Легко"; width = 9; height = 9; bombs = 10;
        }
    }

    string getLevel() const { return level; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getBombs() const { return bombs; }
};

class Achievement {
private:
    string title;
    string description;
    bool unlocked;

public:
    Achievement(const string& t, const string& desc) : title(t), description(desc), unlocked(false) {}

    void print() const {
        printf("Достижение: %s - %s [%s]\n", title.c_str(), description.c_str(),
            unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }

    void unlock() {
        if (!unlocked) {
            unlocked = true;
        }
    }

    bool isUnlocked() const { return unlocked; }
};

class AchievementSystem {
private:
    vector<Achievement> achievements;
public:
    AchievementSystem() {
        achievements.emplace_back("Новичок", "Сыграйте первую игру");
        achievements.emplace_back("Сапер", "Выиграйте 10 игр");
        achievements.emplace_back("Эксперт", "Выиграйте игру на сложном уровне");
        achievements.emplace_back("Скоростник", "Выиграйте игру менее чем за 60 секунд");
        achievements.emplace_back("Безошибочный", "Выиграйте игру без ошибок");
    }

    void print() const {
        printf("=== СИСТЕМА ДОСТИЖЕНИЙ ===\n");
        for (size_t i = 0; i < achievements.size(); i++) {
            printf("%zu. ", i + 1);
            achievements[i].print();
        }
    }

    void checkAchievements(const Player& player, int gameTime, bool won, int difficulty) {
        if (!won) return;

        if (gameTime < 60) {
            achievements[3].unlock();
        }

        if (player.getMistakes() == 0) {
            achievements[4].unlock();
        }

        if (difficulty == 2) {
            achievements[2].unlock();
        }
    }

    int getUnlockedCount() const {
        int count = 0;
        for (const auto& achievement : achievements) {
            if (achievement.isUnlocked()) count++;
        }
        return count;
    }
};

class HighScore {
private:
    string playerName;
    int score;
    int time;
    string difficulty;

public:
    HighScore(const string& name = "", int s = 0, int t = 0, const string& diff = "Легко")
        : playerName(name), score(s), time(t), difficulty(diff) {}

    void print() const {
        printf("%s - %d очков, время: %d сек, сложность: %s\n",
            playerName.c_str(), score, time, difficulty.c_str());
    }

    int getScore() const { return score; }
    string getName() const { return playerName; }
    int getTime() const { return time; }
    string getDifficulty() const { return difficulty; }
};

class HighScoreManager {
private:
    vector<HighScore> highScores;
    const string filename = "highscores.txt";

public:
    HighScoreManager() {
        loadScores();
    }
    void print() const {
        printf("=== ТАБЛИЦА РЕКОРДОВ ===\n");
        if (highScores.empty()) {
            printf("Рекордов пока нет.\n");
            return;
        }

        for (size_t i = 0; i < highScores.size() && i < 10; i++) {
            printf("%zu. ", i + 1);
            highScores[i].print();
        }
    }

    void addScore(const HighScore& score) {
        highScores.push_back(score);
        sort(highScores.begin(), highScores.end(),
            [](const HighScore& a, const HighScore& b) {
                return a.getScore() > b.getScore();
            });

        if (highScores.size() > 10) {
            highScores.resize(10);
        }

        saveScores();
    }

    void addScore(const string& playerName, int score, int time, const string& difficulty) {
        addScore(HighScore(playerName, score, time, difficulty));
    }

    void clearScores() {
        highScores.clear();
        saveScores();
    }

private:
    void loadScores() {
        FILE* file = fopen(filename.c_str(), "r");
        if (!file) return;

        highScores.clear();
        char name[100], difficulty[100];
        int score, time;

        while (fscanf(file, "%s %d %d %s", name, &score, &time, difficulty) == 4) {
            highScores.emplace_back(name, score, time, difficulty);
        }
        fclose(file);
    }

    void saveScores() {
        FILE* file = fopen(filename.c_str(), "w");
        if (!file) return;

        for (const auto& score : highScores) {
            fprintf(file, "%s %d %d %s\n",
                score.getName().c_str(), score.getScore(),
                score.getTime(), score.getDifficulty().c_str());
        }
        fclose(file);
    }
};

class gamesboard {
private:
    vector<pair<string, pair<int, bool>>> games; 

public:
    void addGame(const string& playerName, int time, bool won) {
        games.emplace_back(playerName, make_pair(time, won));
        printf("Игра добавлена в историю: %s, %d сек, %s\n",
            playerName.c_str(), time, won ? "ПОБЕДА" : "ПОРАЖЕНИЕ");
    }

    void print() const {
        printf("=== ИСТОРИЯ ИГР ===\n");
        if (games.empty()) {
            printf("История игр пуста.\n");
            return;
        }

        int start = max(0, (int)games.size() - 10);
        for (size_t i = start; i < games.size(); i++) {
            printf("%zu. %s: %d сек, %s\n",
                i + 1,
                games[i].first.c_str(),
                games[i].second.first,
                games[i].second.second ? "ПОБЕДА" : "ПОРАЖЕНИЕ");
        }
    }

    void saveToFile() {
        FILE* file = fopen("game_history.txt", "a");
        if (!file) return;

        time_t now = time(NULL);
        fprintf(file, "История игр от %s", ctime(&now));
        for (const auto& game : games) {
            fprintf(file, "%s: %d сек, %s\n",
                game.first.c_str(),
                game.second.first,
                game.second.second ? "ПОБЕДА" : "ПОРАЖЕНИЕ");
        }
        fprintf(file, "-----------------\n");
        fclose(file);
    }
};

class PlayerSession {
private:
    Player* player;
    time_t startTime;
    int gamesPlayed;

public:
    PlayerSession(Player* p) : player(p), gamesPlayed(0) {
        startTime = time(NULL);
        printf("Сессия начата для игрока: %s\n", p->getName().c_str());
    }

    void print() const {
        printf("=== СЕССИЯ ИГРОКА ===\n");
        printf("Игрок: %s\n", player ? player->getName().c_str() : "нет игрока");
        printf("Начата: %s", ctime(&startTime));
        printf("Продолжительность: %d минут\n", (int)(time(NULL) - startTime) / 60);
        printf("Игр сыграно в сессии: %d\n", gamesPlayed);
    }

    void addGamePlayed() {
        gamesPlayed++;
        printf("Игрок %s сыграл %d игр в этой сессии\n",
            player->getName().c_str(), gamesPlayed);
    }
};

class PlayerProfile {
private:
    Player* player;
    string avatar;
    int level;
    int experience;
    int gamesWon;
    int totalGames;

public:
    PlayerProfile(Player* p, const string& av = "default") :
        player(p), avatar(av), level(1), experience(0), gamesWon(0), totalGames(0) {}

    void print() const {
        printf("=== ПРОФИЛЬ ИГРОКА ===\n");
        printf("Игрок: %s\n", player ? player->getName().c_str() : "нет игрока");
        printf("Аватар: %s\n", avatar.c_str());
        printf("Уровень: %d\n", level);
        printf("Опыт: %d/%d\n", experience, level * 100);
        printf("Игр сыграно: %d\n", totalGames);
        printf("Побед: %d (%.1f%%)\n", gamesWon, totalGames > 0 ? (float)gamesWon / totalGames * 100 : 0);
        printf("Лучшее время: %d сек\n", player->getBestTime());
    }

    void addGameResult(bool won, int timePlayed) {
        totalGames++;
        if (won) {
            gamesWon++;
            addExperience(50 + max(0, 100 - timePlayed / 10));
        }
        else {
            addExperience(10);
        }
    }

    void addExperience(int exp) {
        experience += exp;
        printf("Добавлено %d опыта. Всего опыта: %d/%d\n", exp, experience, level * 100);

        while (experience >= level * 100) {
            levelUp();
        }
    }

    void levelUp() {
        level++;
        experience = 0;
        printf("🎊 Уровень повышен! Текущий уровень: %d 🎊\n", level);
    }
};

class GameSave {
private:
    string saveName;
    time_t saveTime;
    string gameData;

public:
    GameSave(const string& name, const string& data) : saveName(name), gameData(data) {
        saveTime = time(NULL);
        printf("Создано сохранение: %s\n", name.c_str());
    }

    void print() const {
        printf("Сохранение: %s\n", saveName.c_str());
        printf("Время сохранения: %s", ctime(&saveTime));
    }

    string getName() const { return saveName; }
    string getData() const { return gameData; }
    time_t getTime() const { return saveTime; }
};

class SaveManager {
private:
    vector<GameSave> saves;
    const string saveDir = "saves/";

public:
    SaveManager() {
        CreateDirectoryA("saves", NULL);
        loadSaves();
    }
    void print() const {
        printf("=== СОХРАНЕНИЯ ИГР ===\n");
        if (saves.empty()) {
            printf("Сохранений нет.\n");
            return;
        }

        for (size_t i = 0; i < saves.size(); i++) {
            printf("%zu. ", i + 1);
            saves[i].print();
        }
    }
    bool saveGame(const string& saveName, const string& gameData) {
        string filename = saveDir + saveName + ".save";
        FILE* file = fopen(filename.c_str(), "w");
        if (!file) {
            printf("Ошибка сохранения!\n");
            return false;
        }

        fprintf(file, "%s", gameData.c_str());
        fclose(file);

        saves.emplace_back(saveName, gameData);
        printf("Игра сохранена: %s\n", saveName.c_str());
        return true;
    }

    string loadGame(const string& saveName) {
        string filename = saveDir + saveName + ".save";
        FILE* file = fopen(filename.c_str(), "r");
        if (!file) {
            printf("Сохранение не найдено: %s\n", saveName.c_str());
            return "";
        }

        char buffer[4096];
        string gameData;
        while (fgets(buffer, sizeof(buffer), file)) {
            gameData += buffer;
        }
        fclose(file);

        printf("Игра загружена: %s\n", saveName.c_str());
        return gameData;
    }

    vector<string> getSaveList() const {
        vector<string> names;
        for (const auto& save : saves) {
            names.push_back(save.getName());
        }
        return names;
    }

private:
    void loadSaves() {
        WIN32_FIND_DATAA findData;
        HANDLE hFind = FindFirstFileA("saves\\*.save", &findData);

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                string filename = findData.cFileName;
                string name = filename.substr(0, filename.find(".save"));
                saves.emplace_back(name, "");
            } while (FindNextFileA(hFind, &findData));
            FindClose(hFind);
        }
    }
};

class SoundSystem {
private:
    bool enabled;
    string soundDir;

public:
    SoundSystem() : enabled(true), soundDir("sounds/") {
        system("mkdir sounds 2>nul");
        printf("Звуковая система инициализирована\n");
    }

    void playClickSound() {
        if (playWAV("click.wav")) {
            Beep(500, 100);
        }
    }

    void playExplosionSound() {
        if (playWAV("explosion.wav")) {
            Beep(200, 300);
            Beep(150, 200);
        }
    }

    void playWinSound() {
        if (playWAV("Win.wav")) {
            Beep(523, 200);
            Beep(659, 200);
            Beep(784, 200);
            Beep(1046, 400);
        }
    }

    void stop() {
        PlaySoundA(NULL, NULL, 0);
    }
    void setEnabled(bool enable) {
        enabled = enable;
        printf("Звуки: %s\n", enabled ? "ВКЛ" : "ВЫКЛ");
    }

    bool isEnabled() const { return enabled; }

private:
    int playWAV(const string& filename) {
        string fullPath = soundDir + filename;

        FILE* test = fopen(fullPath.c_str(), "r");
        if (test == NULL)
        {
            return 1;
        }
        fclose(test);
        PlaySoundA(fullPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        return 0;
    }
};

class Theme {
private:
    string name;
    char cellClosed;
    char bombChar;

public:
    Theme() : cellClosed('#'), bombChar('*') {}

    void select() {
        printf("Выберите тему:\n");
        printf("1. Classic (#, *)\n");
        printf("2. Simple (., X)\n");
        int choice = safeInputInt("Выбор: ");
        if (choice == 2) {
            cellClosed = '.';
            bombChar = 'X';
            printf("Тема: Simple\n");
            name = "Simple";
        }
        else {
            cellClosed = '#';
            bombChar = '*';
            printf("Тема: Classic\n");
            name = "Classic";
        }
    }
    string getName() const { return name; }
    char getCellClosed() const { return cellClosed; }
    char getBomb() const { return bombChar; }
};

class HintSystem {
private:
    int hintsAvailable;
    bool hintUsed;

public:
    HintSystem() : hintsAvailable(3), hintUsed(false) {}

    void print() const {
        printf("Доступно подсказок: %d\n", hintsAvailable);
    }

    Coordinate getHint(Board& board) {
        if (hintUsed) {
            printf("Подсказка уже использована в этом ходе.\n");
            return Coordinate(-1, -1);
        }

        if (hintsAvailable <= 0) {
            printf("Подсказки закончились!\n");
            return Coordinate(-1, -1);
        }

        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                Cell* cell = board.getCell(x, y);
                if (cell && !cell->getIsOpen() && !cell->getIsFlag() && !cell->getIsBomb()) {
                    hintsAvailable--;
                    hintUsed = true;
                    return Coordinate(x, y);
                }
            }
        }

        printf("Не найдено безопасных клеток для подсказки.\n");
        return Coordinate(-1, -1);
    }

    void addHints(int count) {
        hintsAvailable += count;
    }

    int getHintsAvailable() const { return hintsAvailable; }

    void resetHintUsed() {
        hintUsed = false;
    }
};
class HelpSystem {
public:
    void print() const {
        printf("=== СИСТЕМА ПОМОЩИ ===\n");
        printf("Цель игры: открыть все клетки без бомб\n");
        printf("Правила:\n");
        printf("1. Цифры показывают количество бомб вокруг клетки\n");
        printf("2. Если цифра 0, все соседние клетки безопасны\n");
        printf("3. Используйте флаги для отметки предполагаемых бомб\n");
        printf("\nУправление в игре:\n");
        printf("o - открыть клетку\n");
        printf("f - поставить/убрать флаг\n");
        printf("h - получить подсказку\n");
        printf("m - открыть игровое меню\n");
        printf("q - выйти в меню\n");
        printf("\nИгровое меню:\n");
        printf("1. Продолжить игру\n");
        printf("2. Сохранить игру\n");
        printf("3. Вернуться в главное меню\n");
    }
};

class GameAnalyzer {
public:
    void print() const {
        printf("Анализатор игрового процесса готов к работе\n");
    }

    void analyzeBoard(const Board& board) {
        int flaggedBombs = 0;
        int totalBombs = board.getTotalBombs();

        printf("Анализ поля: бомб %d, безопасных клеток осталось: %d\n",
            totalBombs, board.getSafeCellsLeft());
        printf("Рекомендация: сосредоточьтесь на областях с цифрами\n");
    }

    void analyzePlayer(const Player& player) {
        printf("Анализ игрока: %s\n", player.getName().c_str());
        printf("Эффективность: %.1f%%\n",
            player.getOpenedCells() > 0 ?
            (float)(player.getOpenedCells() - player.getMistakes()) / player.getOpenedCells() * 100 : 0);

        if (player.getMistakes() > 0) {
            printf("Совет: будьте внимательнее при установке флагов\n");
        }
    }
};

class GameController {
private:
    Game* currentGame;
    int movesCount;

public:
    GameController() : currentGame(nullptr), movesCount(0) {
        printf("Контроллер игры создан\n");
    }

    void print() const {
        printf("Контроллер игры, ходов сделано: %d\n", movesCount);
    }

    void setGame(Game* game) {
        currentGame = game;
        movesCount = 0;
        printf("Игра установлена в контроллере\n");
    }

    void processMove(const Coordinate& coord) {
        if (!currentGame) {
            printf("Нет активной игры!\n");
            return;
        }

        movesCount++;
        printf("Обработка хода #%d на (%d,%d)\n", movesCount, coord.getX(), coord.getY());
    }

    void pauseCurrentGame() {
        if (currentGame) {
            currentGame->pauseGame();
        }
    }

    void resumeCurrentGame() {
        if (currentGame) {
            currentGame->resumeGame();
            printf("Игра возобновлена\n");
        }
    }
};

class GameHistory {
private:
    vector<pair<string, Coordinate>> moves;

public:
    void print() const {
        printf("=== ИСТОРИЯ ХОДОВ ===\n");
        if (moves.empty()) {
            printf("История пуста.\n");
            return;
        }

        int start = max(0, (int)moves.size() - 10);
        for (size_t i = start; i < moves.size(); i++) {
            printf("Ход %zu: %s в (%d,%d)\n",
                i + 1, moves[i].first.c_str(),
                moves[i].second.getX(), moves[i].second.getY());
        }
    }

    void addMove(const string& move, const Coordinate& coord) {
        moves.emplace_back(move, coord);
    }

    void clear() {
        moves.clear();
    }

    int getMoveCount() const {
        return moves.size();
    }
};


class MoveCounter {
private:
    int totalMoves;
    int safeMoves;
    int flagMoves;
    int bombMoves;

public:
    MoveCounter() : totalMoves(0), safeMoves(0), flagMoves(0), bombMoves(0) {}

    void print() const {
        printf("=== СТАТИСТИКА ХОДОВ ===\n");
        printf("Всего ходов: %d\n", totalMoves);
        printf("Открытий клеток: %d\n", safeMoves);
        printf("Установок флагов: %d\n", flagMoves);
        printf("Ошибочных ходов: %d\n", bombMoves);
        if (totalMoves > 0) {
            printf("Процент безопасных: %.1f%%\n", (float)safeMoves / totalMoves * 100);
            printf("Процент ошибок: %.1f%%\n", (float)bombMoves / totalMoves * 100);
        }
    }

    void addSafeMove() {
        totalMoves++;
        safeMoves++;
    }

    void addFlagMove() {
        totalMoves++;
        flagMoves++;
    }

    void addBombMove() {
        totalMoves++;
        bombMoves++;
    }

    void reset() {
        totalMoves = 0;
        safeMoves = 0;
        flagMoves = 0;
        bombMoves = 0;
    }

    int getTotalMoves() const { return totalMoves; }
    float getSuccessRate() const {
        if (totalMoves == 0) return 0.0f;
        return (float)safeMoves / totalMoves * 100;
    }
};

class GameManager {
private:
    unique_ptr<Game> currentGame;
    unique_ptr<Settings> settings;
    unique_ptr<Logger> logger;
    unique_ptr<HighScoreManager> scoreManager;
    unique_ptr<AchievementSystem> achievementSystem;
    unique_ptr<SoundSystem> soundSystem;
    unique_ptr<HintSystem> hintSystem;
    unique_ptr<GameHistory> gameHistory;
    unique_ptr<MoveCounter> moveCounter;
    unique_ptr<GameStats> gameStats;
    unique_ptr<Renderer> renderer;
    unique_ptr<InputHandler> inputHandler;
    unique_ptr<Validator> validator;
    unique_ptr<Notifier> notifier;
    unique_ptr<HelpSystem> helpSystem;
    unique_ptr<Menu> menu;

    unique_ptr<GameFactory> gameFactory;
    unique_ptr<GameController> gameController;
    unique_ptr<PlayerSession> playerSession;
    unique_ptr<PlayerProfile> playerProfile;
    unique_ptr<gamesboard> gamesBoard;
    unique_ptr<SaveManager> saveManager;
    unique_ptr<Theme> theme;
    unique_ptr<GameAnalyzer> gameAnalyzer;
    unique_ptr<RandomGenerator> randomGenerator;

    bool gameRunning;
    int currentDifficulty;
    string currentPlayerName;
    bool hasSavedGame;

public:
    GameManager() : gameRunning(false), currentDifficulty(0), hasSavedGame(false) {
        initializeSystems();
    }

    void run() {
        srand(time(NULL));
        showMainMenu();
    }

private:
    void initializeSystems() {
        settings = make_unique<Settings>();
        logger = make_unique<Logger>();
        scoreManager = make_unique<HighScoreManager>();
        achievementSystem = make_unique<AchievementSystem>();
        soundSystem = make_unique<SoundSystem>();
        hintSystem = make_unique<HintSystem>();
        gameHistory = make_unique<GameHistory>();
        moveCounter = make_unique<MoveCounter>();
        gameStats = make_unique<GameStats>();
        renderer = make_unique<Renderer>();
        inputHandler = make_unique<InputHandler>();
        validator = make_unique<Validator>();
        notifier = make_unique<Notifier>();
        helpSystem = make_unique<HelpSystem>();
        menu = make_unique<Menu>();

        gameFactory = make_unique<GameFactory>();
        gameController = make_unique<GameController>();
        gamesBoard = make_unique<gamesboard>();
        saveManager = make_unique<SaveManager>();
        theme = make_unique<Theme>();
        gameAnalyzer = make_unique<GameAnalyzer>();
        randomGenerator = make_unique<RandomGenerator>();

        printf("Все 35 систем инициализированы!\n");
    }

    void showMainMenu() {
        while (true) {
            system("cls");
            int choice = menu->showMainMenu();
            switch (choice) {
            case 1: startNewGame(); break;
            case 2: continueGame(); break;
            case 3: loadGame(); break;
            case 4: showSettings(); break;
            case 5: showHighScores(); break;
            case 6: showAchievements(); break;
            case 7: showStatistics(); break;
            case 8: showPlayerProfile(); break;
            case 9: showGamesHistory(); break;
            case 10: showHelp(); break;
            case 11: exitGame(); return;
            }
        }
    }

    void showPlayerProfile() {
        system("cls");
        if (playerProfile) {
            playerProfile->print();
        }
        else {
            printf("Профиль игрока не создан. Начните новую игру.\n");
        }
        system("pause");
    }

    void showGamesHistory() {
        system("cls");
        gamesBoard->print();
        system("pause");
    }

    void startNewGame() {
        system("cls");
        printf("=== НОВАЯ ИГРА ===\n");

        Difficulty difficulty;
        difficulty.inputDifficulty();
        currentDifficulty = getDifficultyLevel(difficulty.getLevel());

        string playerName;
        do {
            playerName = inputHandler->getPlayerName();
        } while (!validator->isValidName(playerName));

        currentPlayerName = playerName;

        theme->select();
        renderer->setTheme(theme->getCellClosed(), theme->getBomb());

        Player* player = new Player(playerName);

        playerSession = make_unique<PlayerSession>(player);
        playerProfile = make_unique<PlayerProfile>(player);

        playerSession->addGamePlayed();

        Game* newGame = nullptr;
        if (difficulty.getLevel() == "Пользовательская") {
            newGame = gameFactory->createCustomGame(playerName,
                difficulty.getWidth(), difficulty.getHeight(), difficulty.getBombs());
        }
        else {
            switch (currentDifficulty) {
            case 0: newGame = gameFactory->createEasyGame(playerName); break;
            case 1: newGame = gameFactory->createMediumGame(playerName); break;
            case 2: newGame = gameFactory->createHardGame(playerName); break;
            }
        }

        currentGame.reset(newGame);
        gameController->setGame(currentGame.get());

        logger->logGameStart(playerName);
        gameRunning = true;
        hasSavedGame = false;
        gameHistory->clear();
        moveCounter->reset();
        hintSystem = make_unique<HintSystem>();

        playGame();
    }

    void continueGame() {
        if (!currentGame || !gameRunning) {
            printf("Нет активной игры для продолжения.\n");
            system("pause");
            return;
        }
        if (!currentGame->getTimer().getIsRunning()) {
            currentGame->getTimer().resume();
        }
        playGame();
    }

    bool loadGame() {
        system("cls");
        printf("=== ЗАГРУЗКА ===\n");

        vector<string> saves = saveManager->getSaveList();
        if (saves.empty()) {
            printf("Сохранений нет\n");
            system("pause");
            return false;
        }

        for (int i = 0; i < saves.size(); i++) {
            printf("%d. %s\n", i + 1, saves[i].c_str());
        }
        printf("0. Отмена\n");

        int choice = safeInputInt("Выберите сохранение: ");
        if (choice == 0) return false;

        if (choice < 1 || choice > saves.size()) {
            printf("Неверный выбор\n");
            system("pause");
            return false;
        }

        string saveName = saves[choice - 1];
        string data = saveManager->loadGame(saveName);

        if (data.empty()) {
            printf("Ошибка загрузки\n");
            system("pause");
            return false;
        }
        currentGame = make_unique<Game>(new Board, new Player);
        currentGame->deserialize(data);
        printf("Игра '%s' загружена\n", saves[choice - 1].c_str());
        Player *pl = currentGame->getPlayer();
        currentPlayerName = pl->getName();
        gameRunning = true;
        system("pause");
        return true;
    }

    void saveCurrentGame() {
        if (!currentGame) {
            printf("Нет активной игры для сохранения.\n");
            return;
        }

        system("cls");
        printf("=== СОХРАНЕНИЕ ИГРЫ ===\n");
        printf("Введите имя сохранения: ");
        char saveName[100];
        scanf("%99s", saveName);
        clearInputBuffer();

        string gameData = currentGame->serialize();
        if (saveManager->saveGame(saveName, gameData)) {
            hasSavedGame = true;
            printf("Игра сохранена как: %s\n", saveName);
            system("pause");
        }
    }

    void playGame() {
        while (gameRunning && currentGame->isGameRunning()) {
            system("cls");
            renderer->renderGameState(*currentGame, currentPlayerName);
            printf("Тема: %s\n", theme->getName().c_str());
            printf("Подсказок: %d\n", hintSystem->getHintsAvailable());
            printf("\nКоманды: (o)открыть, (f)флаг, (h)подсказка, (m)меню, (p)пауза , (q)выход\n");
            printf("Выберите действие: ");

            char action;
            scanf(" %c", &action);
            clearInputBuffer();

            processAction(action);
        }

        if (currentGame && !currentGame->isGameRunning()) {
            showGameResult();
        }
    }

    void showGameMenu() {
        while (true) {
            system("cls");

            int choice = menu->showGameMenu();

            switch (choice) {
            case 1: return;
            case 2: saveCurrentGame(); break;
            case 3:
                gameRunning = false;
                printf("Возврат в главное меню...\n");
                system("pause");
                return;
            }
        }
    }

    void processAction(char action) {
        hintSystem->resetHintUsed();

        switch (tolower(action)) {
        case 'o': {
            int x, y;
            safeInputTwoInts(&x, &y, "Введите координаты для открытия (X Y): ");
            handleOpenCell(x, y);
            break;
        }
        case 'f': {
            int x, y;
            safeInputTwoInts(&x, &y, "Введите координаты для флага (X Y): ");
            handleFlagCell(x, y);
            break;
        }
        case 'h': {
            handleHint();
            break;
        }
        case 'm': {
            showGameMenu();
            break;
        }
        case 'p': {
            handlePause();
            break;
        }
        case 'q': {
            if (hasSavedGame) {
                printf("Игра сохранена. Выход в меню...\n");
            }
            else {
                printf("Игра не сохранена. Сохранить перед выходом? (y/n): ");
                char saveChoice;
                scanf(" %c", &saveChoice);
                clearInputBuffer();
                if (tolower(saveChoice) == 'y') {
                    saveCurrentGame();
                }
            }
            gameRunning = false;
            system("pause");
            break;
        }
        default:
            printf("Неверная команда!\n");
            system("pause");
        }
    }
    void handlePause() {
        gameController->pauseCurrentGame();
        printf("\nИгра на паузе. Нажмите любую клавишу для продолжения...\n");
        _getch();
        gameController->resumeCurrentGame();
    }

    void handleOpenCell(int x, int y) {
        if (!validator->isValidCoordinate(Coordinate(x, y),
            currentGame->getBoard()->getWidth(),
            currentGame->getBoard()->getHeight())) {
            system("pause");
            return;
        }

        Cell* cell = currentGame->getBoard()->getCell(x, y);
        if (!cell) return;

        if (cell->getIsOpen()) {
            notifier->showInfoMessage("Клетка уже открыта!");
            system("pause");
            return;
        }
        if (cell->getIsFlag()) {
            notifier->showInfoMessage("Сначала уберите флаг!");
            system("pause");
            return;
        }

        soundSystem->playClickSound();
        currentGame->makeMove(x, y);
        gameHistory->addMove("Открытие", Coordinate(x, y));
        logger->logMove(currentGame->getPlayer()->getName(), x, y, "Открытие");

        if (cell->getIsBomb()) {
            moveCounter->addBombMove();
            soundSystem->playExplosionSound();
        }
        else {
            moveCounter->addSafeMove();
            if (cell->getCountBomb() == 0) {
                openAdjacentCells(x, y);
            }
        }

        checkGameEnd();
    }

    void handleFlagCell(int x, int y) {
        if (!validator->isValidCoordinate(Coordinate(x, y),
            currentGame->getBoard()->getWidth(),
            currentGame->getBoard()->getHeight())) {
            system("pause");
            return;
        }

        Cell* cell = currentGame->getBoard()->getCell(x, y);
        if (!cell || cell->getIsOpen()) return;

        int flags = currentGame->getBoard()->countFlags();
        if (!cell->getIsFlag() && flags >= currentGame->getBoard()->getTotalBombs()) {
            notifier->showInfoMessage("Нельзя поставить больше флагов чем бомб!");
            system("pause");
            return;
        }

        cell->toggleFlag();
        soundSystem->playClickSound();
        moveCounter->addFlagMove();
        string action = cell->getIsFlag() ? "Поставлен флаг" : "Убран флаг";
        gameHistory->addMove(action, Coordinate(x, y));
        logger->logMove(currentGame->getPlayer()->getName(), x, y, action);
    }

    void handleHint() {
        Coordinate hint = hintSystem->getHint(*currentGame->getBoard());
        if (hint.getX() != -1) {
            notifier->showInfoMessage("Подсказка: безопасная клетка [" +
                to_string(hint.getX()) + "," + to_string(hint.getY()) + "]");
            system("pause");
        }
    }

    void openAdjacentCells(int x, int y) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;

                int newX = x + dx;
                int newY = y + dy;

                if (newX >= 0 && newX < currentGame->getBoard()->getWidth() &&
                    newY >= 0 && newY < currentGame->getBoard()->getHeight()) {

                    Cell* cell = currentGame->getBoard()->getCell(newX, newY);
                    if (cell && !cell->getIsOpen() && !cell->getIsFlag() && !cell->getIsBomb()) {
                        currentGame->makeMove(newX, newY);
                        gameHistory->addMove("Автооткрытие", Coordinate(newX, newY));
                        moveCounter->addSafeMove();

                        if (cell->getCountBomb() == 0) {
                            openAdjacentCells(newX, newY);
                        }
                    }
                }
            }
        }
    }

    void checkGameEnd() {
        if (!currentGame->isGameRunning()) {
            if (currentGame->getState() == 1) {
                soundSystem->playWinSound();
                handleWin();
            }
            else if (currentGame->getState() == 2) {
                handleLoss();
            }
        }
    }

    void handleWin() {
        Player* player = currentGame->getPlayer();
        int gameTime = currentGame->getGameTime();

        gameStats->addGame(true, gameTime);
        gameStats->saveToFile("statistics.txt");

        achievementSystem->checkAchievements(*player, gameTime, true, currentDifficulty);

        ScoringSystem scoring;
        int score = scoring.calculateScore(*player, gameTime);
        scoreManager->addScore(player->getName(), score, gameTime,
            getDifficultyString(currentDifficulty));

        gamesBoard->addGame(player->getName(), gameTime, true);
        gamesBoard->saveToFile();

        if (playerProfile) {
            playerProfile->addGameResult(true, gameTime);
        }
        notifier->showWinMessage();
        logger->logGameEnd(player->getName(), true);
        showGameSummary(true);
    }

    void handleLoss() {
        Player* player = currentGame->getPlayer();
        notifier->showLoseMessage();
        logger->logGameEnd(player->getName(), false);
        gameStats->addGame(false, currentGame->getGameTime());

        gamesBoard->addGame(player->getName(), currentGame->getGameTime(), false);
        gamesBoard->saveToFile();

        if (playerProfile) {
            playerProfile->addGameResult(false, currentGame->getGameTime());
        }

        showGameSummary(false);
    }

    void showGameResult() { 
    }

    void showGameSummary(bool won) {
        system("cls");
        printf("=== ИГРА ОКОНЧЕНА ===\n");
        printf("Результат: %s\n", won ? "ПОБЕДА!" : "ПОРАЖЕНИЕ");
        printf("Время: %d сек\n", currentGame->getGameTime());

        if (currentGame->getPlayer()) {
            printf("Игрок: %s\n", currentGame->getPlayer()->getName().c_str());
            printf("Ошибок: %d\n", currentGame->getPlayer()->getMistakes());
        }

        printf("\n");
        moveCounter->print();
        printf("\n");
        gameHistory->print();
        printf("\nНажмите любую клавишу для продолжения...");
        _getch();
        soundSystem->stop();
        gameRunning = false;
    }

    void showSettings() {
        system("cls");
        settings->inputSettings();
        soundSystem->setEnabled(settings->getSounds() == 1);
        system("pause");
    }

    void showHighScores() {
        system("cls");
        scoreManager->print();
        system("pause");
    }

    void showAchievements() {
        system("cls");
        achievementSystem->print();
        printf("\nРазблокировано: %d/%d достижений\n",
            achievementSystem->getUnlockedCount(), 5);
        system("pause");
    }

    void showStatistics() {
        system("cls");
        gameStats->print();
        printf("\n");
        moveCounter->print();
        system("pause");
    }

    void showHelp() {
        system("cls");
        helpSystem->print();
        system("pause");
    }

    void exitGame() {
        printf("Спасибо за игру!\n");
        system("pause");
    }

    int getDifficultyLevel(const string& difficulty) {
        if (difficulty == "Легко") return 0;
        if (difficulty == "Средне") return 1;
        if (difficulty == "Сложно") return 2;
        return 0;
    }

    string getDifficultyString(int level) {
        switch (level) {
        case 0: return "Легко";
        case 1: return "Средне";
        case 2: return "Сложно";
        default: return "Легко";
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(NULL)));

    try {
        GameManager gameManager;
        gameManager.run();
    }
    catch (const exception& e) {
        printf("Ошибка: %s\n", e.what());
        system("pause");
    }

    return 0;
}
