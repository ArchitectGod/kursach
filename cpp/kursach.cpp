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
