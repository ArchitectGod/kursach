#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctime>
#include <locale.h>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <algorithm>


class Coordinate { // Класс координат
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


class Cell { //Класс клетки
private:
    int isBomb;
    int isOpen;
    int isFlag;
    int countBomb;
    int coordinateX;
    int coordinateY;

public:
    Cell(int x = 0, int y = 0) : isBomb(0), isOpen(0), isFlag(0), countBomb(0), coordinateX(x), coordinateY(y) {}

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
        if (state == 1) {
            open();
        }
        else if (state == 2) {
            toggleFlag();
        }
    }

    void open() {
        isOpen = 1;
        isFlag = 0;
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
};


class Board { //  Класс игрового поля
private:
    int width;
    int height;
    int totalBombs;
    int safeCellsLeft;
    std::vector<Cell> cells;

public:
    Board(int w, int h, int bombs) : width(w), height(h), totalBombs(bombs), safeCellsLeft(w* h - bombs) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells.emplace_back(x, y);
            }
        }
    }

    void print() {
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
                        printf(" * ");
                    }
                    else {
                        printf(" %d ", cell.getCountBomb());
                    }
                }
                else if (cell.getIsFlag()) {
                    printf(" F ");
                }
                else {
                    printf(" . ");
                }
            }
            printf("\n");
        }
    }

    void inputBoardSize() {
        printf("Введите размеры поля (ширина высота): ");
        scanf("%d %d", &width, &height);
        printf("Введите количество бомб: ");
        scanf("%d", &totalBombs);

        cells.clear();
        safeCellsLeft = width * height - totalBombs;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells.emplace_back(x, y);
            }
        }
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
        int bombsPlaced = 0;
        while (bombsPlaced < totalBombs) {
            int x = rand() % width;
            int y = rand() % height;

            if ((abs(x - firstX) <= 1 && abs(y - firstY) <= 1) ||
                getCell(x, y)->getIsBomb()) {
                continue;
            }

            getCell(x, y)->setBomb();
            bombsPlaced++;
        }
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
};


class Player {// Класс игрока
private:
    std::string name;
    int timeSpent;
    int openedCells;
    int mistakes;
    int bestTime;

public:
    Player(const std::string& playerName = "") : name(playerName), timeSpent(0), openedCells(0), mistakes(0), bestTime(0) {}

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

        printf("Введите текущее время игры (сек): ");
        scanf("%d", &timeSpent);
    }

    void addMistake() {
        mistakes++;
        printf("Ошибка! Всего ошибок: %d\n", mistakes);
    }

    void addOpenedCell() {
        openedCells++;
        printf("Открыта клетка! Всего открыто: %d\n", openedCells);
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

    std::string getName() const { return name; }
    int getTimeSpent() const { return timeSpent; }
    int getOpenedCells() const { return openedCells; }
    int getMistakes() const { return mistakes; }
    int getBestTime() const { return bestTime; }

    void setTimeSpent(int time) { timeSpent = time; }
    void setName(const std::string& newName) { name = newName; }
};


class Timer {// Класс таймера
private:
    time_t startTime;
    time_t pausedTime;
    bool isRunning;
public:
    Timer() : startTime(0), pausedTime(0), isRunning(false) {}

    void print() const {
        printf("Таймер: %d секунд, статус: %s\n", getElapsedTime(), isRunning ? "работает" : "на паузе");
    }

    void inputStart() {
        printf("Запустить таймер? (1-да, 0-нет): ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            start();
        }
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
};


class Game {//  Класс игры
private:
    Board* board;
    Player* player;
    int state;
    Timer* timer;

public:
    Game(Board* b, Player* p) : board(b), player(p), state(0) {
        timer = new Timer();
        timer->start();
    }

    ~Game() {
        delete timer;
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

    void inputGameSettings() {
        printf("=== НАСТРОЙКИ ИГРЫ ===\n");
        if (board) {
            board->inputBoardSize();
        }
        if (player) {
            player->inputPlayerInfo();
        }
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
        return timer->getElapsedTime();
    }

    void pauseGame() {
        timer->pause();
        printf("Игра на паузе\n");
    }

    void resumeGame() {
        timer->resume();
        printf("Игра продолжается\n");
    }

    void makeMove(int x, int y) {
        if (!isGameRunning()) return;

        Cell* cell = board->getCell(x, y);
        if (cell && !cell->getIsOpen()) {
            cell->open();
            board->decreaseSafeCells();
            player->addOpenedCell();

            if (cell->getIsBomb()) {
                loseGame();
            }
            else if (board->isGameWon()) {
                winGame();
            }
        }
    }

    int getState() const { return state; }
    Board* getBoard() const { return board; }
    Player* getPlayer() const { return player; }
};


class Settings {// Класс настроек
private:
    int autoBombs;
    int sounds;
    int difficulty;

public:
    Settings() : autoBombs(1), sounds(1), difficulty(0) {}

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
    }

    void inputSettings() {
        printf("=== ВВОД НАСТРОЕК ===\n");
        printf("Авторасстановка бомб (0-Выкл, 1-Вкл): ");
        scanf("%d", &autoBombs);

        printf("Звуки (0-Выкл, 1-Вкл): ");
        scanf("%d", &sounds);

        printf("Сложность (0-Легко, 1-Средне, 2-Сложно): ");
        scanf("%d", &difficulty);
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
};


class Logger {// Класс логгера
private:
    std::string filename;
    FILE* file;

public:
    Logger(const std::string& fname) : filename(fname) {
        file = fopen(filename.c_str(), "a");
    }

    ~Logger() {
        if (file) {
            fclose(file);
        }
    }

    void print() const {
        printf("Логгер: файл %s\n", filename.c_str());
    }

    void inputFilename() {
        printf("Введите имя файла для лога: ");
        char buffer[100];
        scanf("%99s", buffer);
        filename = buffer;
        if (file) fclose(file);
        file = fopen(filename.c_str(), "a");
    }

    void logMessage(const std::string& message) {
        if (file) {
            time_t now = time(NULL);
            fprintf(file, "[%s] %s\n", ctime(&now), message.c_str());
            fflush(file);
        }
    }

    void logGameStart(const std::string& playerName) {
        logMessage("Игра начата игроком: " + playerName);
    }

    void logGameEnd(const std::string& playerName, bool won) {
        logMessage("Игра завершена игроком: " + playerName + " Результат: " + (won ? "ПОБЕДА" : "ПОРАЖЕНИЕ"));
    }
};


class gamesboard {// Класс таблицы игр
private:
    std::string name;
    int time;
    int height;
    int width;
    int bombs;
    int day;
    int month;
    int age;
    int win;

public:
    gamesboard(const std::string& playerName, int t, int w, int h, int b, int victory)
        : name(playerName), time(t), width(w), height(h), bombs(b), win(victory) {

        time_t t_now = ::time(NULL);
        struct tm* tm_info = localtime(&t_now);
        day = tm_info->tm_mday;
        month = tm_info->tm_mon + 1;
        age = tm_info->tm_year + 1900;
    }

    void print() const {
        printf("%s: %d сек, %dx%d, %s\n", name.c_str(), time, width, height,
            win ? "ПОБЕДА" : "ПРОИГРЫШ");
    }

    void inputData() {
        printf("Введите данные для таблицы игр:\n");
        printf("Имя: ");
        char buffer[50];
        scanf("%49s", buffer);
        name = buffer;

        printf("Время (сек): ");
        scanf("%d", &time);

        printf("Размеры поля (ширина высота): ");
        scanf("%d %d", &width, &height);

        printf("Количество бомб: ");
        scanf("%d", &bombs);

        printf("Результат (1-победа, 0-поражение): ");
        scanf("%d", &win);
    }

    void saveToFile(const std::string& filename) {
        FILE* file = fopen(filename.c_str(), "a");
        if (file) {
            fprintf(file, "%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                name.c_str(), time, height, width, bombs,
                day, month, age, win);
            fclose(file);
        }
    }

    std::string getName() const { return name; }
    int getTime() const { return time; }
    bool isWin() const { return win; }
};


class Menu {// Класс меню
public:
    void print() const {
        printf("=== ГЛАВНОЕ МЕНЮ ===\n");
        printf("1. Новая игра\n");
        printf("2. Загрузить игру\n");
        printf("3. Настройки\n");
        printf("4. Таблица лидеров\n");
        printf("5. Выход\n");
    }

    int getChoice() const {
        int choice;
        printf("Выберите вариант: ");
        scanf("%d", &choice);
        return choice;
    }
};


class GameStats { // класс статистики игр
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
        printf("Лучшее время: %d сек\n", bestTime);
        printf("Среднее время: %.1f сек\n", gamesPlayed > 0 ? (float)totalTime / gamesPlayed : 0);
    }

    void inputReset() {
        printf("Сбросить статистику? (1-да, 0-нет): ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) reset();
    }

    void addGame(bool won, int time) {
        gamesPlayed++;
        if (won) gamesWon++;
        totalTime += time;
        if (won && (time < bestTime || bestTime == 0)) {
            bestTime = time;
        }
    }

    void reset() {
        gamesPlayed = 0;
        gamesWon = 0;
        totalTime = 0;
        bestTime = 0;
    }
};

class RandomGenerator { //рандомайзер
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

    void inputSeed() {
        printf("Введите seed для генератора: ");
        scanf("%d", &seed);
        srand(seed);
    }

    int getRandom(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    Coordinate getRandomCoordinate(int maxX, int maxY) {
        return Coordinate(getRandom(0, maxX - 1), getRandom(0, maxY - 1));
    }
};

class Renderer { //отображение
public:
    void print() const {
        printf("Рендерер для отображения игры\n");
    }

    void renderBoard(Board& board) {
        board.print();
    }

    void renderPlayer(const Player& player) {
        player.print();
    }

    void renderGame(const Game& game) {
        game.print();
    }
};

class InputHandler { // ввод
public:
    void print() const {
        printf("Обработчик ввода пользователя\n");
    }

    Coordinate getCellCoordinates() {
        int x, y;
        printf("Введите координаты X Y: ");
        scanf("%d %d", &x, &y);
        return Coordinate(x, y);
    }

    std::string getPlayerName() {
        std::string name;
        printf("Введите имя игрока: ");
        char buffer[50];
        scanf("%49s", buffer);
        return std::string(buffer);
    }

    int getMenuChoice() {
        int choice;
        printf("Выберите действие: ");
        scanf("%d", &choice);
        return choice;
    }
};

class GameController { //контролёр игры
private:
    Game* currentGame;

public:
    GameController() : currentGame(nullptr) {}

    void print() const {
        printf("Контроллер игры, игра %s\n", currentGame ? "активна" : "не активна");
    }

    void inputNewGame() {
        printf("Создание новой игры...\n");
        // Логика создания новой игры
    }

    void setGame(Game* game) {
        currentGame = game;
    }

    void processMove(const Coordinate& coord) {
        if (!currentGame) return;
        currentGame->makeMove(coord.getX(), coord.getY());
    }

    void pauseCurrentGame() {
        if (currentGame) currentGame->pauseGame();
    }

    void resumeCurrentGame() {
        if (currentGame) currentGame->resumeGame();
    }
};

class Validator { // ввод проверка
public:
    void print() const {
        printf("Валидатор входных данных\n");
    }

    bool isValidCoordinate(const Coordinate& coord, int maxX, int maxY) {
        bool valid = coord.getX() >= 0 && coord.getX() < maxX &&
            coord.getY() >= 0 && coord.getY() < maxY;
        if (!valid) {
            printf("Неверные координаты! Допустимый диапазон: X:0-%d, Y:0-%d\n", maxX - 1, maxY - 1);
        }
        return valid;
    }

    bool isValidName(const std::string& name) {
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

class GameFactory { // создание игры
public:
    void print() const {
        printf("Фабрика создания игр\n");
    }

    Game* createEasyGame(const std::string& playerName) {
        Board* board = new Board(9, 9, 10);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }

    Game* createMediumGame(const std::string& playerName) {
        Board* board = new Board(16, 16, 40);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }

    Game* createHardGame(const std::string& playerName) {
        Board* board = new Board(30, 16, 99);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }

    Game* createCustomGame(const std::string& playerName, int width, int height, int bombs) {
        Board* board = new Board(width, height, bombs);
        Player* player = new Player(playerName);
        return new Game(board, player);
    }
};

class ScoringSystem { //система очков
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

    void inputScoringParams() {
        printf("Введите параметры подсчета очков:\n");
        printf("Базовые очки: ");
        scanf("%d", &baseScore);
        printf("Бонус за время: ");
        scanf("%d", &timeBonus);
        printf("Штраф за ошибку: ");
        scanf("%d", &mistakePenalty);
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

class PlayerSession { // сессия игрока
private:
    Player* player;
    GameStats stats;

public:
    PlayerSession(Player* p) : player(p) {}
    void print() const {
        printf("Сессия игрока: %s\n", player ? player->getName().c_str() : "нет игрока");
        stats.print();
    }

    void inputSessionData() {
        printf("Ввод данных сессии...\n");
        if (player) {
            player->inputPlayerInfo();
        }
    }

    void addGameResult(bool won, int time) {
        stats.addGame(won, time);
    }

    Player* getPlayer() const { return player; }
    GameStats getStats() const { return stats; }
};

class Notifier { //уведомления
public:
    void print() const {
        printf("Система уведомлений\n");
    }

    void showWinMessage() {
        printf("🎉 ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ! 🎉\n");
    }

    void showLoseMessage() {
        printf("💥 ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ! 💥\n");
    }

    void showErrorMessage(const std::string& message) {
        printf("❌ ОШИБКА: %s\n", message.c_str());
    }

    void showInfoMessage(const std::string& message) {
        printf("ℹ️  ИНФО: %s\n", message.c_str());
    }
};

class Difficulty { //сложность
private:
    std::string level;
    int width;
    int height;
    int bombs;

public:
    Difficulty(const std::string& lvl, int w, int h, int b) : level(lvl), width(w), height(h), bombs(b) {}

    void print() const {
        printf("Уровень сложности: %s (%dx%d, %d бомб)\n", level.c_str(), width, height, bombs);
    }

    void inputDifficulty() {
        printf("Выберите сложность (0-Легко, 1-Средне, 2-Сложно, 3-Пользовательская): ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 0: level = "Легко"; width = 9; height = 9; bombs = 10; break;
        case 1: level = "Средне"; width = 16; height = 16; bombs = 40; break;
        case 2: level = "Сложно"; width = 30; height = 16; bombs = 99; break;
        case 3:
            level = "Пользовательская";
            printf("Введите ширину, высоту и количество бомб: ");
            scanf("%d %d %d", &width, &height, &bombs);
            break;
        }
    }

    std::string getLevel() const { return level; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getBombs() const { return bombs; }
};

class PlayerProfile { //профиль игрока
private:
    Player* player;
    std::string avatar;
    int level;

public:
    PlayerProfile(Player* p, const std::string& av = "default") : player(p), avatar(av), level(1) {}

    void print() const {
        printf("Профиль игрока: %s\n", player ? player->getName().c_str() : "нет игрока");
        printf("Аватар: %s, Уровень: %d\n", avatar.c_str(), level);
    }

    void inputProfile() {
        printf("Настройка профиля:\n");
        printf("Введите имя аватара: ");
        char buffer[50];
        scanf("%49s", buffer);
        avatar = buffer;
    }

    void levelUp() {
        level++;
        printf("Уровень повышен! Текущий уровень: %d\n", level);
    }

    void setAvatar(const std::string& av) {
        avatar = av;
    }
};

class Achievement { // достижения
private:
    std::string title;
    std::string description;
    bool unlocked;

public:
    Achievement(const std::string& t, const std::string& desc) : title(t), description(desc), unlocked(false) {}

    void print() const {
        printf("Достижение: %s - %s [%s]\n", title.c_str(), description.c_str(),
            unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }

    void inputUnlock() {
        printf("Разблокировать достижение '%s'? (1-да, 0-нет): ", title.c_str());
        int choice;
        scanf("%d", &choice);
        if (choice == 1) unlock();
    }

    void unlock() {
        unlocked = true;
        printf("🎊 Достижение разблокировано: %s! 🎊\n", title.c_str());
    }

    bool isUnlocked() const { return unlocked; }
};

class AchievementSystem { //система достижений
private:
    std::vector<Achievement> achievements;
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
        for (const auto& achievement : achievements) {
            achievement.print();
        }
    }

    void inputUnlockAchievement() {
        printf("Выберите достижение для разблокировки (1-%zu): ", achievements.size());
        int choice;
        scanf("%d", &choice);
        if (choice >= 1 && choice <= achievements.size()) {
            achievements[choice - 1].inputUnlock();
        }
    }

    void checkAchievements(const PlayerSession& session) {
        // Логика проверки достижений
    }

    int getUnlockedCount() const {
        int count = 0;
        for (const auto& achievement : achievements) {
            if (achievement.isUnlocked()) count++;
        }
        return count;
    }
};

class GameSave { // сохранение игры
private:
    std::string saveName;
    time_t saveTime;

public:
    GameSave(const std::string& name) : saveName(name) {
        saveTime = time(NULL);
    }

    void print() const {
        printf("Сохранение: %s, время: %s", saveName.c_str(), ctime(&saveTime));
    }

    void inputSaveData() {
        printf("Введите имя сохранения: ");
        char buffer[50];
        scanf("%49s", buffer);
        saveName = buffer;
        saveTime = time(NULL);
    }

    std::string getName() const { return saveName; }
    time_t getSaveTime() const { return saveTime; }
};

class SaveManager { // менеджер сохранения
private:
    std::vector<GameSave> saves;

public:
    void print() const {
        printf("Менеджер сохранений, сохранений: %zu\n", saves.size());
        for (const auto& save : saves) {
            save.print();
        }
    }

    void inputCreateSave() {
        GameSave save("");
        save.inputSaveData();
        saves.push_back(save);
    }

    void createSave(const std::string& name) {
        saves.emplace_back(name);
    }

    bool loadSave(const std::string& name) {
        for (const auto& save : saves) {
            if (save.getName() == name) {
                printf("Загружаем сохранение: %s\n", name.c_str());
                return true;
            }
        }
        return false;
    }

    void deleteSave(const std::string& name) {
        saves.erase(std::remove_if(saves.begin(), saves.end(),
            [&](const GameSave& save) { return save.getName() == name; }),
            saves.end());
    }
};

class SoundSystem { //звук
private:
    bool enabled;

public:
    SoundSystem() : enabled(true) {}

    void print() const {
        printf("Звуковая система: %s\n", enabled ? "включена" : "выключена");
    }

    void inputToggle() {
        printf("Переключить звук? (1-вкл, 0-выкл): ");
        int choice;
        scanf("%d", &choice);
        enabled = (choice == 1);
    }

    void playClickSound() {
        if (enabled) {
            printf("[ЗВУК] Клик!\n");
        }
    }

    void playExplosionSound() {
        if (enabled) {
            printf("[ЗВУК] БУМ!\n");
        }
    }

    void playWinSound() {
        if (enabled) {
            printf("[ЗВУК] Победа!\n");
        }
    }

    void setEnabled(bool enable) { enabled = enable; }
};

class Theme { // тема
private:
    std::string name;
    std::string cellClosed;
    std::string cellOpen;
    std::string bomb;

public:
    Theme(const std::string& themeName = "classic") : name(themeName) {
        if (themeName == "classic") {
            cellClosed = ".";
            cellOpen = " ";
            bomb = "*";
        }
        else if (themeName == "modern") {
            cellClosed = "■";
            cellOpen = "□";
            bomb = "💣";
        }
        else if (themeName == "simple") {
            cellClosed = "#";
            cellOpen = " ";
            bomb = "X";
        }
    }

    void print() const {
        printf("Тема: %s\n", name.c_str());
        printf("Закрытая клетка: %s, Открытая клетка: %s, Бомба: %s\n",
            cellClosed.c_str(), cellOpen.c_str(), bomb.c_str());
    }

    void inputSelectTheme() {
        printf("Выберите тему (1-classic, 2-modern, 3-simple): ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
        case 1: name = "classic"; cellClosed = "."; cellOpen = " "; bomb = "*"; break;
        case 2: name = "modern"; cellClosed = "■"; cellOpen = "□"; bomb = "💣"; break;
        case 3: name = "simple"; cellClosed = "#"; cellOpen = " "; bomb = "X"; break;
        }
    }

    std::string getCellClosed() const { return cellClosed; }
    std::string getCellOpen() const { return cellOpen; }
    std::string getBomb() const { return bomb; }
};

class HelpSystem { // система помощи
public:
    void print() const {
        printf("=== СИСТЕМА ПОМОЩИ ===\n");
        printf("Цель игры: открыть все клетки без бомб\n");
        printf("Управление:\n");
        printf("- ЛКМ: открыть клетку\n");
        printf("- ПКМ: поставить/убрать флаг\n");
        printf("Цифры показывают количество бомб вокруг клетки\n");
    }

    void showRules() {
        print();
    }

    void showTips() {
        printf("=== СОВЕТЫ ===\n");
        printf("1. Начинайте с углов\n");
        printf("2. Используйте флаги для отметки бомб\n");
        printf("3. Анализируйте цифры для определения безопасных клеток\n");
        printf("4. Если вокруг клетки 0 бомб, она откроет область автоматически\n");
    }

    void showControls() {
        printf("=== УПРАВЛЕНИЕ ===\n");
        printf("WASD/Стрелки - перемещение\n");
        printf("Пробел - открыть клетку\n");
        printf("F - поставить/убрать флаг\n");
        printf("P - пауза\n");
        printf("H - помощь\n");
    }
};

class GameAnalyzer { // анализатор игры
public:
    void print() const {
        printf("Анализатор игрового процесса\n");
    }

    void analyzeBoard(const Board& board) {
        int flaggedBombs = 0;
        int totalBombs = board.getTotalBombs();

        printf("Анализ поля: бомб %d, безопасных клеток осталось: %d\n",
            totalBombs, board.getSafeCellsLeft());
    }

    void analyzePlayer(const Player& player) {
        printf("Анализ игрока: %s\n", player.getName().c_str());
        printf("Эффективность: %.1f%%\n",
            player.getOpenedCells() > 0 ?
            (float)(player.getOpenedCells() - player.getMistakes()) / player.getOpenedCells() * 100 : 0);
    }

    void analyzeGame(const Game& game) {
        printf("Анализ игры:\n");
        printf("Статус: %s\n", game.isGameRunning() ? "в процессе" : (game.getState() == 1 ? "победа" : "поражение"));
        printf("Время: %d сек\n", game.getGameTime());
    }
};

class HighScore { //высочайшие очки
private:
    std::string playerName;
    int score;
    int time;
    std::string difficulty;

public:
    HighScore(const std::string& name, int s, int t, const std::string& diff)
        : playerName(name), score(s), time(t), difficulty(diff) {}
    HighScore() : playerName(""), score(0), time(0), difficulty("") {}
    void print() const {
        printf("Рекорд: %s - %d очков, время: %d сек, сложность: %s\n",
            playerName.c_str(), score, time, difficulty.c_str());
    }

    void inputHighScore() {
        printf("Введите данные рекорда:\n");
        printf("Имя: ");
        char buffer[50];
        scanf("%49s", buffer);
        playerName = buffer;

        printf("Очки: ");
        scanf("%d", &score);

        printf("Время (сек): ");
        scanf("%d", &time);

        printf("Сложность: ");
        scanf("%49s", buffer);
        difficulty = buffer;
    }

    int getScore() const { return score; }
};

class HighScoreManager { //менеджер высочаших очков
private:
    std::vector<HighScore> highScores;

public:
    void print() const {
        printf("=== ТАБЛИЦА РЕКОРДОВ ===\n");
        for (size_t i = 0; i < highScores.size(); i++) {
            printf("%zu. ", i + 1);
            highScores[i].print();
        }
    }

    void inputAddScore() {
        HighScore score("", 0, 0, "");
        score.inputHighScore();
        addScore(score);
    }

    void addScore(const HighScore& score) {
        highScores.push_back(score);
        std::sort(highScores.begin(), highScores.end(),
            [](const HighScore& a, const HighScore& b) {
                return a.getScore() > b.getScore();
            });

        if (highScores.size() > 10) {
            highScores.resize(10);
        }
    }

    void clearScores() {
        highScores.clear();
    }
};

class HintSystem { // система подсказок
private:
    int hintsAvailable;

public:
    HintSystem() : hintsAvailable(3) {}

    void print() const {
        printf("Система подсказок, доступно подсказок: %d\n", hintsAvailable);
    }

    void inputUseHint() {
        printf("Использовать подсказку? (1-да, 0-нет): ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1 && hintsAvailable > 0) {
            hintsAvailable--;
            printf("Подсказка использована! Осталось: %d\n", hintsAvailable);
        }
    }

    Coordinate getHint(const Board& board) {
        if (hintsAvailable > 0) {
            hintsAvailable--;

            for (int y = 0; y < board.getHeight(); y++) {
                for (int x = 0; x < board.getWidth(); x++) {
                    Cell* cell = const_cast<Board&>(board).getCell(x, y);
                    if (cell && !cell->getIsOpen() && !cell->getIsBomb()) {
                        printf("Подсказка: безопасная клетка [%d,%d]\n", x, y);
                        return Coordinate(x, y);
                    }
                }
            }
        }
        else {
            printf("Подсказки закончились!\n");
        }
        return Coordinate(-1, -1);
    }

    void addHints(int count) {
        hintsAvailable += count;
        printf("Добавлено %d подсказок. Всего: %d\n", count, hintsAvailable);
    }
};

class GameHistory { // история игры
private:
    std::vector<std::string> moves;
    std::vector<Coordinate> positions;

public:
    void print() const {
        printf("=== ИСТОРИЯ ХОДОВ ===\n");
        for (size_t i = 0; i < moves.size(); i++) {
            printf("Ход %zu: %s в (%d,%d)\n",
                i + 1, moves[i].c_str(),
                positions[i].getX(), positions[i].getY());
        }
    }

    void inputClearHistory() {
        printf("Очистить историю? (1-да, 0-нет): ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) clearHistory();
    }

    void addMove(const std::string& move, const Coordinate& coord) {
        moves.push_back(move);
        positions.push_back(coord);
    }

    void clearHistory() {
        moves.clear();
        positions.clear();
        printf("История очищена!\n");
    }

    int getMoveCount() const {
        return moves.size();
    }

    void printLastMoves(int count) const {
        int start = std::max(0, ((int)moves.size() - count));
        printf("Последние %d ходов:\n", count);
        for (size_t i = start; i < moves.size(); i++) {
            printf("Ход %zu: %s в (%d,%d)\n",
                i + 1, moves[i].c_str(),
                positions[i].getX(), positions[i].getY());
        }
    }
};

class MoveCounter { //счётчик ходов
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
        printf("Безопасных ходов: %d\n", safeMoves);
        printf("Установок флагов: %d\n", flagMoves);
        printf("Ходов на бомбах: %d\n", bombMoves);

        if (totalMoves > 0) {
            printf("Процент безопасных: %.1f%%\n", (float)safeMoves / totalMoves * 100);
            printf("Процент ошибок: %.1f%%\n", (float)bombMoves / totalMoves * 100);
        }
    }

    void inputReset() {
        printf("Сбросить статистику? (1-да, 0-нет): ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            reset();
            printf("Статистика сброшена!\n");
        }
    }

    void addSafeMove() {
        totalMoves++;
        safeMoves++;
        printf("+1 безопасный ход\n");
    }

    void addFlagMove() {
        totalMoves++;
        flagMoves++;
        printf("+1 установка флага\n");
    }

    void addBombMove() {
        totalMoves++;
        bombMoves++;
        printf("+1 ход на бомбе (ОШИБКА!)\n");
    }

    void reset() {
        totalMoves = 0;
        safeMoves = 0;
        flagMoves = 0;
        bombMoves = 0;
    }

    int getTotalMoves() const { return totalMoves; }
    int getSafeMoves() const { return safeMoves; }
    int getFlagMoves() const { return flagMoves; }
    int getBombMoves() const { return bombMoves; }

    float getSuccessRate() const {
        if (totalMoves == 0) return 0.0f;
        return (float)safeMoves / totalMoves * 100;
    }
};


void demonstrateGame() { // Демонстрационная функция
    printf("=== ДЕМОНСТРАЦИЯ САПЕРА ===\n\n");

    // Создаем основные объекты
    Player player("Тестовый Игрок");
    Board board(8, 8, 10);
    Game game(&board, &player);

    // Демонстрация работы
    printf("1. Начальное состояние:\n");
    game.print();

    printf("\n2. Делаем несколько ходов:\n");
    game.makeMove(0, 0);
    game.makeMove(1, 1);
    game.makeMove(2, 2);

    printf("\n3. Состояние после ходов:\n");
    game.print();

    printf("\n4. Демонстрация других систем:\n");
    Settings settings;
    settings.print();

    MoveCounter counter;
    counter.addSafeMove();
    counter.addFlagMove();
    counter.addBombMove();
    counter.print();

    HelpSystem help;
    help.showTips();

    printf("\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n");
}

//Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    printf("=== САПЕР НА C++ ===\n");
    printf("35 классов, полная объектно-ориентированная реализация\n\n");

    demonstrateGame();

    // Простое меню для взаимодействия
    Menu menu;
    menu.print();
    int choice = menu.getChoice();

    printf("Выбран вариант: %d\n", choice);
    // В зависимости от выбора можно реализовать полную логику игры
    switch (choice) {
    case 1: {
        Player player("Игрок");
        Board board(9, 9, 10);
        Game game(&board, &player);
        game.print();
        break;
    }
    case 2:
        printf("Загрузка игры...\n");
        break;
    case 3: {
        Settings settings;
        settings.inputSettings();
        settings.print();
        break;
    }
    case 4: {
        HighScoreManager hsManager;
        hsManager.print();
        break;
    }
    case 5:
        printf("Выход из игры.\n");
        break;
    default:
        printf("Неверный выбор!\n");
    }

    return 0;

}