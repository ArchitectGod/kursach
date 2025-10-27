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

class GameObject {     // Базовый класс
public:
    virtual ~GameObject() = default;
    virtual void print() const = 0;
};

class Cell : public GameObject {         // Класс клетки
private:
    int isBomb;
    int isOpen;
    int isFlag;
    int countBomb;
    int coordinateX;
    int coordinateY;

public:
    Cell(int x = 0, int y = 0) : isBomb(0), isOpen(0), isFlag(0), countBomb(0), coordinateX(x), coordinateY(y) {}
    
    // Геттеры
    int getIsBomb() const { return isBomb; }
    int getIsOpen() const { return isOpen; }
    int getIsFlag() const { return isFlag; }
    int getCountBomb() const { return countBomb; }
    int getX() const { return coordinateX; }
    int getY() const { return coordinateY; }
    
    // Сеттеры
    void setIsBomb(int value) { isBomb = value; }
    void setIsOpen(int value) { isOpen = value; }
    void setIsFlag(int value) { isFlag = value; }
    void setCountBomb(int value) { countBomb = value; }
    
    void print() const override {
        printf("Клетка [%d,%d]: ", coordinateX, coordinateY);
        if (isOpen) {
            if (isBomb) {
                printf("Бомба");
            } else {
                printf("Бомб вокруг: %d", countBomb);
            }
        } else if (isFlag) {
            printf("Флаг");
        } else {
            printf("Закрыта");
        }
        printf("\n");
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
};



class Board : public GameObject {         // Класс игрового поля
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

    void print() const override {
        printf(" ");
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

    // Геттеры
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTotalBombs() const { return totalBombs; }
    int getSafeCellsLeft() const { return safeCellsLeft; }
};

class Player : public GameObject {         //Класс игрока
private:
    std::string name;
    int timeSpent;
    int openedCells;
    int mistakes;
    int bestTime;

public:
    Player(const std::string& playerName = "") : name(playerName), timeSpent(0), openedCells(0), mistakes(0), bestTime(0) {}

    void print() const override {
        printf("Игрок: %s\n", name.c_str());
        printf("Время: %d сек, Открыто: %d, Ошибок: %d\n", timeSpent, openedCells, mistakes);
    }

    void addMistake() { mistakes++; }
    void addOpenedCell() { openedCells++; }

    void updateBestTime() {
        if (bestTime == 0 || timeSpent < bestTime) {
            bestTime = timeSpent;
        }
    }

    // Геттеры и сеттеры
    std::string getName() const { return name; }
    int getTimeSpent() const { return timeSpent; }
    int getOpenedCells() const { return openedCells; }
    int getMistakes() const { return mistakes; }
    int getBestTime() const { return bestTime; }

    void setTimeSpent(int time) { timeSpent = time; }
    void setName(const std::string& newName) { name = newName; }
};

class Game : public GameObject { // класс игры
private:
    Board* board;
    Player* player;
    int state;
    time_t startTime;
    time_t pauseTime;

public:
    Game(Board* b, Player* p) : board(b), player(p), state(0) {
        startTime = time(NULL);
        pauseTime = 0;
    }

    void print() const override {
        printf("=== ИГРА ===\n");
        printf("Статус: ");
        switch (state) {
        case 0: printf("В процессе\n"); break;
        case 1: printf("ПОБЕДА!\n"); break;
        case 2: printf("ПРОИГРЫШ\n"); break;
        }
        if (board) board->print();
        if (player) player->print();
    }

    void winGame() {
        state = 1;
        if (player) player->updateBestTime();
    }

    void loseGame() {
        state = 2;
    }

    bool isGameRunning() const {
        return state == 0;
    }

    int getGameTime() const {
        return (int)(time(NULL) - startTime);
    }

    // Геттеры
    int getState() const { return state; }
    Board* getBoard() const { return board; }
    Player* getPlayer() const { return player; }
};

class Settings : public GameObject {         //Класс настроек
private:
    int autoBombs;
    int sounds;
    int difficulty;

public:
    Settings() : autoBombs(1), sounds(1), difficulty(0) {}
    
    void print() const override {
        printf("=== НАСТРОЙКИ ===\n");
        printf("Авторасстановка бомб: %s\n", autoBombs ? "Вкл" : "Выкл");
        printf("Сложность: ");
        switch (difficulty) {
            case 0: printf("Легко\n"); break;
            case 1: printf("Средне\n"); break;
            case 2: printf("Сложно\n"); break;
        }
    }
    
    // Геттеры и сеттеры
    int getAutoBombs() const { return autoBombs; }
    int getSounds() const { return sounds; }
    int getDifficulty() const { return difficulty; }
    
    void setAutoBombs(int value) { autoBombs = value; }
    void setSounds(int value) { sounds = value; }
    void setDifficulty(int value) { difficulty = value; }
};


class Logger : public GameObject { // Класс логгера
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

    void print() const override {
        printf("Логгер: файл %s\n", filename.c_str());
    }

    void logMessage(const std::string& message) {
        if (file) {
            time_t now = time(NULL);
            fprintf(file, "[%s] %s\n", ctime(&now), message.c_str());
            fflush(file);
        }
    }
};




class Menu : public GameObject {         //Класс меню
private:
    std::string title;
    std::vector<std::string> options;

public:
    Menu(const std::string& menuTitle) : title(menuTitle) {}
    
    void addOption(const std::string& option) {
        options.push_back(option);
    }
    
    void print() const override {
        printf("=== %s ===\n", title.c_str());
        for (size_t i = 0; i < options.size(); i++) {
            printf("%zu. %s\n", i + 1, options[i].c_str());
        }
    }
    
    int getChoice() const {
        int choice;
        printf("Выберите вариант: ");
        scanf("%d", &choice);
        return choice;
    }
};

class Timer : public GameObject {         // Класс счетчика времени
private:
    time_t startTime;
    time_t pausedTime;
    bool isRunning;

public:
    Timer() : startTime(0), pausedTime(0), isRunning(false) {}
    
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
    
    void print() const override {
        printf("Таймер: %d секунд, статус: %s\n", getElapsedTime(), isRunning ? "работает" : "на паузе");
    }
};


class GameStats : public GameObject {         // Класс статистики игры
private:
    int gamesPlayed;
    int gamesWon;
    int totalTime;
    int bestTime;

public:
    GameStats() : gamesPlayed(0), gamesWon(0), totalTime(0), bestTime(0) {}

    void addGame(bool won, int time) {
        gamesPlayed++;
        if (won) gamesWon++;
        totalTime += time;
        if (won && (time < bestTime || bestTime == 0)) {
            bestTime = time;
        }
    }

    void print() const override {
        printf("=== СТАТИСТИКА ===\n");
        printf("Игр сыграно: %d\n", gamesPlayed);
        printf("Побед: %d\n", gamesWon);
        printf("Лучшее время: %d сек\n", bestTime);
        printf("Среднее время: %.1f сек\n", gamesPlayed > 0 ? (float)totalTime / gamesPlayed : 0);
    }
};

class Coordinate : public GameObject {         //Класс координат
private:
    int x;
    int y;

public:
    Coordinate(int xCoord = 0, int yCoord = 0) : x(xCoord), y(yCoord) {}
    
    void print() const override {
        printf("Координаты: (%d, %d)\n", x, y);
    }
    
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};



class Bomb : public GameObject { // Класс бомбы
private:
    Coordinate position;
    bool exploded;

public:
    Bomb(const Coordinate& pos) : position(pos), exploded(false) {}

    void explode() {
        exploded = true;
    }

    void print() const override {
        printf("Бомба в позиции (%d, %d), состояние: %s\n",
            position.getX(), position.getY(), exploded ? "взорвана" : "не взорвана");
    }

    bool isExploded() const { return exploded; }
    Coordinate getPosition() const { return position; }
};


class Flag : public GameObject {         //Класс флага
private:
    Coordinate position;
    bool isPlaced;

public:
    Flag(const Coordinate& pos) : position(pos), isPlaced(false) {}

    void place() { isPlaced = true; }
    void remove() { isPlaced = false; }

    void print() const override {
        printf("Флаг в позиции (%d, %d), состояние: %s\n",
            position.getX(), position.getY(), isPlaced ? "установлен" : "не установлен");
    }

    bool getIsPlaced() const { return isPlaced; }
};

class RandomGenerator : public GameObject {         //Класс генератора случайных чисел
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
    
    int getRandom(int min, int max) {
        return min + rand() % (max - min + 1);
    }
    
    void print() const override {
        printf("Генератор случайных чисел, seed: %d\n", seed);
    }
};

class Renderer : public GameObject {         //Класс отрисовщика
public:
    void print() const override {
        printf("Рендерер для отображения игры\n");
    }

    void renderBoard(const Board& board) {
        board.print();
    }

    void renderPlayer(const Player& player) {
        player.print();
    }
};


class InputHandler : public GameObject {         //Класс ввода пользователя
public:
    void print() const override {
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
};

class GameController : public GameObject { // класс управления игрой
private:
    Game* currentGame;

public:
    GameController() : currentGame(nullptr) {}

    void setGame(Game* game) {
        currentGame = game;
    }

    void print() const override {
        printf("Контроллер игры, игра %s\n", currentGame ? "активна" : "не активна");
    }

    void processMove(const Coordinate& coord) {
        if (!currentGame) return;

        Board* board = currentGame->getBoard();
        Player* player = currentGame->getPlayer();

        if (board && player) {
            Cell* cell = board->getCell(coord.getX(), coord.getY());
            if (cell) {
                if (!cell->getIsOpen()) {
                    cell->open();
                    board->decreaseSafeCells();
                    player->addOpenedCell();

                    if (cell->getIsBomb()) {
                        player->addMistake();
                        currentGame->loseGame();
                    }
                    else if (board->isGameWon()) {
                        currentGame->winGame();
                    }
                }
            }
        }
    }
};

class Validator : public GameObject { // класс валидатора
public:
    void print() const override {
        printf("Валидатор входных данных\n");
    }

    bool isValidCoordinate(const Coordinate& coord, int maxX, int maxY) {
        return coord.getX() >= 0 && coord.getX() < maxX &&
            coord.getY() >= 0 && coord.getY() < maxY;
    }

    bool isValidName(const std::string& name) {
        return !name.empty() && name.length() <= 49;
    }
};

class GameFactory : public GameObject { // класс фабрики игр
public:
    void print() const override {
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
};

class ScoringSystem : public GameObject { // класс системы очков
private:
    int baseScore;
    int timeBonus;
    int mistakePenalty;

public:
    ScoringSystem() : baseScore(1000), timeBonus(50), mistakePenalty(100) {}

    void print() const override {
        printf("Система подсчета очков\n");
    }

    int calculateScore(const Player& player, int gameTime) {
        int score = baseScore;
        score += (3600 - gameTime) / 60 * timeBonus; // бонус за быстроту
        score -= player.getMistakes() * mistakePenalty; // штраф за ошибки
        return score > 0 ? score : 0;
    }
};

class PlayerSession : public GameObject { // класс сессии игрока
private:
    Player* player;
    GameStats stats;

public:
    PlayerSession(Player* p) : player(p) {}

    void print() const override {
        printf("Сессия игрока: %s\n", player ? player->getName().c_str() : "нет игрока");
        stats.print();
    }

    void addGameResult(bool won, int time) {
        stats.addGame(won, time);
    }
};

class Notifier : public GameObject { // класс уведомлений
public:
    void print() const override {
        printf("Система уведомлений\n");
    }

    void showWinMessage() {
        printf("ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ!\n");
    }

    void showLoseMessage() {
        printf("ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ!\n");
    }

    void showErrorMessage(const std::string& message) {
        printf("ОШИБКА: %s\n", message.c_str());
    }
};

class Difficulty : public GameObject {          //Класс сложности
private:
    std::string level;
    int width;
    int height;
    int bombs;

public:
    Difficulty(const std::string& lvl, int w, int h, int b) : level(lvl), width(w), height(h), bombs(b) {}
    
    void print() const override {
        printf("Уровень сложности: %s (%dx%d, %d бомб)\n", level.c_str(), width, height, bombs);
    }
    
    // Геттеры
    std::string getLevel() const { return level; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getBombs() const { return bombs; }
};


class PlayerProfile : public GameObject { //  Класс профиля игрока
private:
    Player* player;
    std::string avatar;
    int level;

public:
    PlayerProfile(Player* p, const std::string& av = "default") : player(p), avatar(av), level(1) {}

    void print() const override {
        printf("Профиль игрока: %s\n", player ? player->getName().c_str() : "нет игрока");
        printf("Аватар: %s, Уровень: %d\n", avatar.c_str(), level);
    }

    void levelUp() {
        level++;
    }
};


class Achievement : public GameObject { // Класс ачивментов
private:
    std::string title;
    std::string description;
    bool unlocked;

public:
    Achievement(const std::string& t, const std::string& desc) : title(t), description(desc), unlocked(false) {}

    void unlock() {
        unlocked = true;
    }

    void print() const override {
        printf("Достижение: %s - %s [%s]\n", title.c_str(), description.c_str(),
            unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }

    bool isUnlocked() const { return unlocked; }
};



class AchievementSystem : public GameObject { // Класс системы ачивментов
private:
    std::vector<Achievement> achievements;

public:
    AchievementSystem() {
        // Добавляем базовые достижения
        achievements.emplace_back("Новичок", "Сыграйте первую игру");
        achievements.emplace_back("Сапер", "Выиграйте 10 игр");
        achievements.emplace_back("Эксперт", "Выиграйте игру на сложном уровне");
        achievements.emplace_back("Скоростник", "Выиграйте игру менее чем за 60 секунд");
    }

    void print() const override {
        printf("=== СИСТЕМА ДОСТИЖЕНИЙ ===\n");
        for (const auto& achievement : achievements) {
            achievement.print();
        }
    }

    void checkAchievements(const PlayerSession& session) {
        // Здесь будет логика проверки достижений
    }
};



class GameSave : public GameObject { // Класс сохранения игры
private:
    std::string saveName;
    time_t saveTime;

public:
    GameSave(const std::string& name) : saveName(name) {
        saveTime = time(NULL);
    }

    void print() const override {
        printf("Сохранение: %s, время: %s", saveName.c_str(), ctime(&saveTime));
    }

    std::string getName() const { return saveName; }
    time_t getSaveTime() const { return saveTime; }
};



class SaveManager : public GameObject { // Класс менеджера сохранений
private:
    std::vector<GameSave> saves;

public:
    void print() const override {
        printf("Менеджер сохранений, сохранений: %zu\n", saves.size());
        for (const auto& save : saves) {
            save.print();
        }
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
};


class SoundSystem : public GameObject { // Класс звуковой системы
private:
    bool enabled;

public:
    SoundSystem() : enabled(true) {}

    void print() const override {
        printf("Звуковая система: %s\n", enabled ? "включена" : "выключена");
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