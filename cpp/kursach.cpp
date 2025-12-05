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
#include <stdexcept>
#include <sstream>

// ==================== БАЗОВЫЕ КЛАССЫ ДЛЯ НАСЛЕДОВАНИЯ ====================

class Elektropribor {
protected:
    std::string proizvoditel;  // Производитель
    int god_vypuska;           // Год выпуска
    float napryazhenie;        // Напряжение

public:
    Elektropribor(const std::string& prod = "Unknown", int year = 2024, float volt = 220.0f)
        : proizvoditel(prod), god_vypuska(year), napryazhenie(volt) {}

    virtual ~Elektropribor() = default;

    virtual void vkluchit() = 0;

    std::string getProizvoditel() const { return proizvoditel; }
    int getGodVypuska() const { return god_vypuska; }
    float getNapryazhenie() const { return napryazhenie; }

    void setProizvoditel(const std::string& prod) { proizvoditel = prod; }

    virtual void info() const {
        printf("Электроприбор от %s, %d год, %.1fV\n",
            proizvoditel.c_str(), god_vypuska, napryazhenie);
    }
};

class Geografiya {
protected:
    std::string strana;        // Страна
    std::string region;        // Регион
    double shirota;           // Широта
    double dolgota;           // Долгота

public:
    Geografiya(const std::string& country = "Unknown", const std::string& reg = "Unknown",
        double lat = 0.0, double lon = 0.0)
        : strana(country), region(reg), shirota(lat), dolgota(lon) {}

    virtual ~Geografiya() = default;
    virtual void pokazat_mesto() = 0;

    std::string getStrana() const { return strana; }
    std::string getRegion() const { return region; }
    double getShirota() const { return shirota; }
    double getDolgota() const { return dolgota; }

    void peremestit(double newLat, double newLon) {
        shirota = newLat;
        dolgota = newLon;
    }

    virtual std::string opisanie() const {
        return strana + ", " + region + " (" + std::to_string(shirota) + "°, " +
            std::to_string(dolgota) + "°)";
    }
};

class Zavod {
protected:
    std::string nazvanie;      // Название завода
    std::string adres;         // Адрес
    int rabochih;             // Количество рабочих
    float ploshad;            // Площадь в кв.м.

public:
    Zavod(const std::string& name = "Безымянный", const std::string& addr = "Неизвестно",
        int workers = 0, float area = 0.0f)
        : nazvanie(name), adres(addr), rabochih(workers), ploshad(area) {}

    virtual ~Zavod() = default;
    virtual void proizvesti() = 0;

    std::string getNazvanie() const { return nazvanie; }
    std::string getAdres() const { return adres; }
    int getRabochih() const { return rabochih; }
    float getPloshad() const { return ploshad; }

    void nayti_rabotnikov(int count) {
        rabochih += count;
    }

    virtual float proizvoditelnost() const {
        return rabochih > 0 ? ploshad / rabochih : 0;
    }
};

class Schitatel {
protected:
    std::string tip;          // Тип счетчика
    int max_znachenie;        // Максимальное значение
    bool kalibrovka;          // Откалиброван ли

public:
    Schitatel(const std::string& type = "Механический", int max = 9999, bool calib = false)
        : tip(type), max_znachenie(max), kalibrovka(calib) {}

    virtual ~Schitatel() = default;
    virtual void schitat() = 0;

    std::string getTip() const { return tip; }
    int getMaxZnachenie() const { return max_znachenie; }
    bool getKalibrovka() const { return kalibrovka; }

    void otkalibrovat() {
        kalibrovka = true;
    }

    virtual std::string status() const {
        return kalibrovka ? "Откалиброван" : "Требуется калибровка";
    }
};
class Rekordsmen {
protected:
    std::string vid_sporta;   // Вид спорта
    std::string organizaciya; // Организация
    int god_ustanovki;        // Год установки рекорда

public:
    Rekordsmen(const std::string& sport = "Неизвестно", const std::string& org = "Неизвестно", int year = 2024)
        : vid_sporta(sport), organizaciya(org), god_ustanovki(year) {}

    virtual ~Rekordsmen() = default;
    virtual void zafiksirovat_rekord() = 0;

    std::string getVidSporta() const { return vid_sporta; }
    std::string getOrganizaciya() const { return organizaciya; }
    int getGodUstanovki() const { return god_ustanovki; }

    void izmenit_sport(const std::string& new_sport) {
        vid_sporta = new_sport;
    }

    virtual bool mirovoy_rekord() const {
        return organizaciya.find("Миров") != std::string::npos ||
            organizaciya.find("Гиннес") != std::string::npos;
    }
};

// ==================== КЛАСС 1: КООРДИНАТА ====================

class Coordinate : public Geografiya {
private:
    int x;
    int y;
    static int totalCoordinates;

public:
    Coordinate(int xCoord = 0, int yCoord = 0,
        const std::string& country = "Россия", const std::string& reg = "Центральный",
        double lat = 55.7558, double lon = 37.6173)
        : Geografiya(country, reg, lat, lon), x(xCoord), y(yCoord) {
        totalCoordinates++;
    }

    Coordinate(const Coordinate& other)
        : Geografiya(other.strana, other.region, other.shirota, other.dolgota),
        x(other.x), y(other.y) {
        totalCoordinates++;
    }

    ~Coordinate() {
        totalCoordinates--;
    }

    void print() const {
        printf("Координаты: (%d, %d) в %s\n", x, y, opisanie().c_str());
    }

    void pokazat_mesto() override {
        printf("Местоположение: (%d, %d) - %s, %s\n",
            x, y, strana.c_str(), region.c_str());
    }

    // Перегрузка операторов
    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }

    Coordinate operator+(const Coordinate& other) const {
        return Coordinate(x + other.x, y + other.y, strana, region);
    }

    Coordinate& operator=(const Coordinate& other) {
        if (this != &other) {
            Geografiya::operator=(other);
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Coordinate& operator+=(const Coordinate& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);
    friend void swapCoordinates(Coordinate& a, Coordinate& b);

    static int getTotalCoordinates() {
        return totalCoordinates;
    }

    static void resetCounter() {
        totalCoordinates = 0;
    }

    int getX() const { return this->x; }
    int getY() const { return this->y; }

    void setX(int newX) { this->x = newX; }
    void setY(int newY) { this->y = newY; }

    bool isValid(int maxX, int maxY) const {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

int Coordinate::totalCoordinates = 0;

void swapCoordinates(Coordinate& a, Coordinate& b) {
    std::swap(a.x, b.x);
    std::swap(a.y, b.y);
    std::swap(a.shirota, b.shirota);
    std::swap(a.dolgota, b.dolgota);
}

std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
    os << "(" << coord.x << ", " << coord.y << ") в " << coord.strana;
    return os;
}

// ==================== КЛАСС 2: КЛЕТКА ====================

class Cell {
private:
    int isBomb;
    int isOpen;
    int isFlag;
    int countBomb;
    std::shared_ptr<Coordinate> coord;
public:
    Cell(int x = 0, int y = 0,
        const std::string& country = "Россия", const std::string& reg = "Игровое поле")
        : isBomb(0), isOpen(0), isFlag(0), countBomb(0) {
        coord = std::make_shared<Coordinate>(x, y, country, reg);
    }

    Cell(const Cell& other)
        : isBomb(other.isBomb), isOpen(other.isOpen), isFlag(other.isFlag),
        countBomb(other.countBomb) {
        coord = std::make_shared<Coordinate>(*other.coord);
    }

    void print() const {
        printf("Клетка [%d,%d]: ", coord->getX(), coord->getY());
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
        printf(" (%s)\n", coord->getStrana().c_str());
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
    int getX() const { return coord->getX(); }
    int getY() const { return coord->getY(); }

    std::shared_ptr<Coordinate> getCoordinate() const { return coord; }

    Cell& operator=(const Cell& other) {
        if (this != &other) {
            isBomb = other.isBomb;
            isOpen = other.isOpen;
            isFlag = other.isFlag;
            countBomb = other.countBomb;
            coord = std::make_shared<Coordinate>(*other.coord);
        }
        return *this;
    }

    bool operator==(const Cell& other) const {
        return getX() == other.getX() && getY() == other.getY();
    }
};

// ==================== КЛАСС 3: ПОЛЕ ====================

class Board {
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
                std::string country = (x < w / 2 && y < h / 2) ? "Россия" :
                    (x >= w / 2 && y < h / 2) ? "США" :
                    (x < w / 2 && y >= h / 2) ? "Германия" : "Япония";
                cells.emplace_back(x, y, country);
            }
        }
    }

    Board(const Board& other)
        : width(other.width), height(other.height), totalBombs(other.totalBombs),
        safeCellsLeft(other.safeCellsLeft), cells(other.cells) {}

    void print() const {
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

    std::shared_ptr<Cell> getCell(int x, int y) {
        try {
            if (x < 0 || x >= width || y < 0 || y >= height) {
                throw std::out_of_range("Неверные координаты клетки: " +
                    std::to_string(x) + "," + std::to_string(y));
            }
            return std::make_shared<Cell>(cells[y * width + x]);
        }
        catch (const std::exception& e) {
            printf("Ошибка: %s\n", e.what());
            return nullptr;
        }
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
                cells[y * width + x].getIsBomb()) {
                continue;
            }

            cells[y * width + x].setBomb();
            bombsPlaced++;
        }
        calculateBombCounts();
    }

    void calculateBombCounts() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                auto cell = getCell(x, y);
                if (cell && !cell->getIsBomb()) {
                    int count = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            auto neighbor = getCell(x + dx, y + dy);
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

    Board& operator=(const Board& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            totalBombs = other.totalBombs;
            safeCellsLeft = other.safeCellsLeft;
            cells = other.cells;
        }
        return *this;
    }
};

// ==================== КЛАСС 4: ИГРОК ====================

class Player {
private:
    std::string name;
    int timeSpent;
    int openedCells;
    int mistakes;
    int bestTime;

public:
    Player(const std::string& playerName = "")
        : name(playerName), timeSpent(0), openedCells(0), mistakes(0), bestTime(0) {}

    Player(const Player& other)
        : name(other.name), timeSpent(other.timeSpent), openedCells(other.openedCells),
        mistakes(other.mistakes), bestTime(other.bestTime) {}

    void print() const {
        printf("Игрок: %s\n", name.c_str());
        printf("Время: %d сек, Открыто: %d, Ошибок: %d, Лучшее время: %d сек\n",
            timeSpent, openedCells, mistakes, bestTime);
    }

    bool operator>(const Player& other) const {
        if (bestTime == 0) return false;
        if (other.bestTime == 0) return true;
        return bestTime < other.bestTime;
    }

    Player& operator+=(int seconds) {
        timeSpent += seconds;
        return *this;
    }

    Player& operator++() {
        mistakes++;
        return *this;
    }

    Player operator++(int) {
        Player temp = *this;
        mistakes++;
        return temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    void addMistake() {
        mistakes++;
    }

    void addOpenedCell() {
        openedCells++;
    }

    void updateBestTime() {
        if (bestTime == 0 || timeSpent < bestTime) {
            bestTime = timeSpent;
        }
    }

    std::string getName() const { return name; }
    int getTimeSpent() const { return timeSpent; }
    int getOpenedCells() const { return openedCells; }
    int getMistakes() const { return mistakes; }
    int getBestTime() const { return bestTime; }

    void setTimeSpent(int time) { timeSpent = time; }
    void setName(const std::string& newName) { name = newName; }

    std::string getInfo() const {
        return name + ": " + std::to_string(bestTime) + " сек (ошибок: " +
            std::to_string(mistakes) + ")";
    }
};

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.name << " - " << player.bestTime << " сек";
    return os;
}

// ==================== КЛАСС 5: ТАЙМЕР ====================

class Timer {
private:
    time_t startTime;
    time_t pausedTime;
    bool isRunning;

public:
    Timer() : startTime(0), pausedTime(0), isRunning(false) {}

    Timer(const Timer& other)
        : startTime(other.startTime), pausedTime(other.pausedTime), isRunning(other.isRunning) {}

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

    Timer& operator=(const Timer& other) {
        if (this != &other) {
            startTime = other.startTime;
            pausedTime = other.pausedTime;
            isRunning = other.isRunning;
        }
        return *this;
    }
};

// ==================== КЛАСС 6: ИГРА ====================

class Game {
private:
    std::unique_ptr<Board> board;
    std::shared_ptr<Player> player;
    int state;
    std::unique_ptr<Timer> timer;

public:
    Game(std::unique_ptr<Board> b, std::shared_ptr<Player> p)
        : board(std::move(b)), player(p), state(0) {
        timer = std::make_unique<Timer>();
        timer->start();
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
    }

    void loseGame() {
        state = 2;
        if (player) {
            player->addMistake();
        }
    }

    bool isGameRunning() const {
        return state == 0;
    }

    int getGameTime() const {
        return timer->getElapsedTime();
    }

    void pauseGame() {
        timer->pause();
    }

    void resumeGame() {
        timer->resume();
    }

    void makeMove(int x, int y) {
        if (!isGameRunning() || !board) return;

        auto cell = board->getCell(x, y);
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
    Board* getBoard() const { return board.get(); }
    std::shared_ptr<Player> getPlayer() const { return player; }
};

// ==================== КЛАСС 7: НАСТРОЙКИ ====================

class Settings {
private:
    int autoBombs;
    int sounds;
    int difficulty;

public:
    Settings() : autoBombs(1), sounds(1), difficulty(0) {}

    Settings(const Settings& other)
        : autoBombs(other.autoBombs), sounds(other.sounds), difficulty(other.difficulty) {}

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

    std::unique_ptr<Board> createBoardByDifficulty() const {
        switch (difficulty) {
        case 0: return std::make_unique<Board>(9, 9, 10);
        case 1: return std::make_unique<Board>(16, 16, 40);
        case 2: return std::make_unique<Board>(30, 16, 99);
        default: return std::make_unique<Board>(9, 9, 10);
        }
    }

    int getAutoBombs() const { return autoBombs; }
    int getSounds() const { return sounds; }
    int getDifficulty() const { return difficulty; }

    void setDifficulty(int level) { difficulty = level; }

    Settings& operator=(const Settings& other) {
        if (this != &other) {
            autoBombs = other.autoBombs;
            sounds = other.sounds;
            difficulty = other.difficulty;
        }
        return *this;
    }
};

// ==================== КЛАСС 8: ЛОГГЕР ====================

class Logger {
private:
    std::string filename;
    FILE* file;

public:
    Logger(const std::string& fname) : filename(fname) {
        file = fopen(filename.c_str(), "a");
        if (!file) {
            throw std::runtime_error("Не удалось открыть файл лога: " + filename);
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

    void logMessage(const std::string& message) {
        if (file) {
            time_t now = time(NULL);
            std::string timeStr = ctime(&now);
            timeStr.erase(std::remove(timeStr.begin(), timeStr.end(), '\n'), timeStr.end());
            std::string fullMessage = "[" + timeStr + "] " + message;
            fprintf(file, "%s\n", fullMessage.c_str());
            fflush(file);
        }
    }

    Logger(const Logger& other) : filename(other.filename + "_copy") {
        file = fopen(filename.c_str(), "a");
    }

    Logger& operator=(const Logger& other) {
        if (this != &other) {
            if (file) fclose(file);
            filename = other.filename + "_assigned";
            file = fopen(filename.c_str(), "a");
        }
        return *this;
    }
};

// ==================== КЛАСС 9: ТАБЛИЦА ЛИДЕРОВ ====================

class Leaderboard {
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
    Leaderboard(const std::string& playerName, int t, int w, int h, int b, int victory)
        : name(playerName), time(t), width(w), height(h), bombs(b), win(victory) {

        time_t t_now = ::time(NULL);
        struct tm* tm_info = localtime(&t_now);
        day = tm_info->tm_mday;
        month = tm_info->tm_mon + 1;
        age = tm_info->tm_year + 1900;
    }

    Leaderboard(const Leaderboard& other)
        : name(other.name), time(other.time), width(other.width), height(other.height),
        bombs(other.bombs), day(other.day), month(other.month), age(other.age), win(other.win) {}

    void print() const {
        printf("%s: %d сек, %dx%d, %s\n", name.c_str(), time, width, height,
            win ? "ПОБЕДА" : "ПРОИГРЫШ");
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

    Leaderboard& operator=(const Leaderboard& other) {
        if (this != &other) {
            name = other.name;
            time = other.time;
            width = other.width;
            height = other.height;
            bombs = other.bombs;
            day = other.day;
            month = other.month;
            age = other.age;
            win = other.win;
        }
        return *this;
    }
};

// ==================== КЛАСС 10: МЕНЮ ====================

class Menu {
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

// ==================== КЛАСС 11: СТАТИСТИКА ====================

class GameStats {
private:
    int gamesPlayed;
    int gamesWon;
    int totalTime;
    int bestTime;

public:
    GameStats() : gamesPlayed(0), gamesWon(0), totalTime(0), bestTime(0) {}

    GameStats(const GameStats& other)
        : gamesPlayed(other.gamesPlayed), gamesWon(other.gamesWon),
        totalTime(other.totalTime), bestTime(other.bestTime) {}

    void print() const {
        printf("=== СТАТИСТИКА ===\n");
        printf("Игр сыграно: %d\n", gamesPlayed);
        printf("Побед: %d\n", gamesWon);
        printf("Лучшее время: %d сек\n", bestTime);
        printf("Среднее время: %.1f сек\n", gamesPlayed > 0 ? (float)totalTime / gamesPlayed : 0);
    }

    void addGame(bool won, int time) {
        gamesPlayed++;
        if (won) gamesWon++;
        totalTime += time;
        if (won && (time < bestTime || bestTime == 0)) {
            bestTime = time;
        }
    }

    GameStats& operator=(const GameStats& other) {
        if (this != &other) {
            gamesPlayed = other.gamesPlayed;
            gamesWon = other.gamesWon;
            totalTime = other.totalTime;
            bestTime = other.bestTime;
        }
        return *this;
    }

    GameStats operator+(const GameStats& other) const {
        GameStats result;
        result.gamesPlayed = gamesPlayed + other.gamesPlayed;
        result.gamesWon = gamesWon + other.gamesWon;
        result.totalTime = totalTime + other.totalTime;
        result.bestTime = std::min(bestTime ? bestTime : INT_MAX,
            other.bestTime ? other.bestTime : INT_MAX);
        if (result.bestTime == INT_MAX) result.bestTime = 0;
        return result;
    }
};

// ==================== КЛАСС 12: ГЕНЕРАТОР СЛУЧАЙНОСТЕЙ ====================

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

    RandomGenerator(const RandomGenerator& other) : seed(other.seed) {
        srand(seed);
    }

    void print() const {
        printf("Генератор случайных чисел, seed: %d\n", seed);
    }

    int getRandom(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    RandomGenerator& operator=(const RandomGenerator& other) {
        if (this != &other) {
            seed = other.seed;
            srand(seed);
        }
        return *this;
    }
};

// ==================== КЛАСС 13: ОТРИСОВЩИК ====================

class Renderer {
public:
    void print() const {
        printf("Рендерер для отображения игры\n");
    }

    void renderBoard(const Board& board) {
        board.print();
    }

    void renderPlayer(const Player& player) {
        player.print();
    }
};

// ==================== КЛАСС 14: ОБРАБОТЧИК ВВОДА ====================

class InputHandler {
public:
    void print() const {
        printf("Обработчик ввода пользователя\n");
    }

    std::pair<int, int> getCellCoordinates() {
        int x, y;
        printf("Введите координаты X Y: ");
        scanf("%d %d", &x, &y);
        return { x, y };
    }

    std::string getPlayerName() {
        std::string name;
        printf("Введите имя игрока: ");
        char buffer[50];
        scanf("%49s", buffer);
        name = buffer;
        return name;
    }
};

// ==================== КЛАСС 15: КОНТРОЛЛЕР ИГРЫ ====================

class GameController {
private:
    std::unique_ptr<Game> currentGame;

public:
    GameController() {}

    void print() const {
        printf("Контроллер игры, игра %s\n", currentGame ? "активна" : "не активна");
    }

    void setGame(std::unique_ptr<Game> game) {
        currentGame = std::move(game);
    }

    void processMove(int x, int y) {
        if (!currentGame) return;
        currentGame->makeMove(x, y);
    }
};

// ==================== КЛАСС 16: ВАЛИДАТОР ====================

class Validator {
public:
    void print() const {
        printf("Валидатор входных данных\n");
    }

    bool isValidCoordinate(int x, int y, int maxX, int maxY) {
        try {
            if (x < 0 || y < 0 || y >= maxY) {
                throw std::invalid_argument("Координаты вне диапазона: " +
                    std::to_string(x) + "," + std::to_string(y));
            }
            return true;
        }
        catch (const std::exception& e) {
            printf("Ошибка валидации: %s\n", e.what());
            return false;
        }
    }

    bool isValidName(const std::string& name) {
        if (name.empty()) {
            printf("Имя не может быть пустым\n");
            return false;
        }
        if (name.length() > 49) {
            printf("Имя слишком длинное (макс 49 символов)\n");
            return false;
        }
        return true;
    }

    Validator& operator=(const Validator& other) {
        return *this;
    }
};

// ==================== КЛАСС 17: ФАБРИКА ИГР ====================

class GameFactory : public Zavod {
private:
    std::string specializaciya;

public:
    GameFactory(const std::string& name = "Игровая фабрика",
        const std::string& spec = "Стратегии",
        const std::string& addr = "ул. Программистов, 1",
        int workers = 50, float area = 1000.0f)
        : Zavod(name, addr, workers, area), specializaciya(spec) {}

    GameFactory(const GameFactory& other)
        : Zavod(other.nazvanie, other.adres, other.rabochih, other.ploshad),
        specializaciya(other.specializaciya) {}

    void print() const {
        printf("Фабрика игр: %s (специализация: %s)\n", nazvanie.c_str(), specializaciya.c_str());
        printf("Адрес: %s, Рабочих: %d, Площадь: %.0f м²\n", adres.c_str(), rabochih, ploshad);
    }
    void proizvesti() override {
        printf("Фабрика '%s' производит игру...\n", nazvanie.c_str());
        printf("Специализация: %s, Производительность: %.1f м²/чел\n",
            specializaciya.c_str(), proizvoditelnost());
    }

    std::unique_ptr<Game> createEasyGame(const std::string& playerName) {
        proizvesti();
        auto board = std::make_unique<Board>(9, 9, 10);
        auto player = std::make_shared<Player>(playerName);
        return std::make_unique<Game>(std::move(board), player);
    }

    std::unique_ptr<Game> createMediumGame(const std::string& playerName) {
        auto board = std::make_unique<Board>(16, 16, 40);
        auto player = std::make_shared<Player>(playerName);
        return std::make_unique<Game>(std::move(board), player);
    }

    std::unique_ptr<Game> createCustomGame(const std::string& playerName, int width, int height, int bombs) {
        auto board = std::make_unique<Board>(width, height, bombs);
        auto player = std::make_shared<Player>(playerName);
        return std::make_unique<Game>(std::move(board), player);
    }

    GameFactory& operator=(const GameFactory& other) {
        if (this != &other) {
            Zavod::operator=(other);
            specializaciya = other.specializaciya;
        }
        return *this;
    }
};

// ==================== КЛАСС 18: СИСТЕМА ОЧКОВ ====================

class ScoringSystem {
private:
    int baseScore;
    int timeBonus;
    int mistakePenalty;
    static int totalGamesScored;

public:
    ScoringSystem() : baseScore(1000), timeBonus(50), mistakePenalty(100) {}

    ScoringSystem(const ScoringSystem& other)
        : baseScore(other.baseScore), timeBonus(other.timeBonus), mistakePenalty(other.mistakePenalty) {}

    void print() const {
        printf("Система подсчета очков\n");
        printf("Базовые очки: %d, Бонус за время: %d, Штраф за ошибку: %d\n",
            baseScore, timeBonus, mistakePenalty);
    }

    static void incrementGamesScored() {
        totalGamesScored++;
    }

    static int getTotalGamesScored() {
        return totalGamesScored;
    }

    int calculateScore(const Player& player, int gameTime) {
        incrementGamesScored();
        int score = baseScore;
        score += (3600 - gameTime) / 60 * timeBonus;
        score -= player.getMistakes() * mistakePenalty;
        return score > 0 ? score : 0;
    }

    ScoringSystem& operator=(const ScoringSystem& other) {
        if (this != &other) {
            baseScore = other.baseScore;
            timeBonus = other.timeBonus;
            mistakePenalty = other.mistakePenalty;
        }
        return *this;
    }
};

int ScoringSystem::totalGamesScored = 0;

// ==================== КЛАСС 19: СЕССИЯ ИГРОКА ====================

class PlayerSession {
private:
    std::shared_ptr<Player> player;
    GameStats stats;

public:
    PlayerSession(std::shared_ptr<Player> p) : player(p) {}

    PlayerSession(const PlayerSession& other)
        : player(other.player), stats(other.stats) {}

    void print() const {
        printf("Сессия игрока: %s\n", player ? player->getName().c_str() : "нет игрока");
        stats.print();
    }

    void addGameResult(bool won, int time) {
        stats.addGame(won, time);
    }

    PlayerSession& operator=(const PlayerSession& other) {
        if (this != &other) {
            player = other.player;
            stats = other.stats;
        }
        return *this;
    }
};

// ==================== КЛАСС 20: УВЕДОМИТЕЛЬ ====================

class Notifier {
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

    Notifier& operator=(const Notifier& other) {
        return *this;
    }
};
// ==================== КЛАСС 21: СЛОЖНОСТЬ ====================

class Difficulty {
private:
    std::string level;
    int width;
    int height;
    int bombs;

public:
    Difficulty(const std::string& lvl, int w, int h, int b)
        : level(lvl), width(w), height(h), bombs(b) {}

    Difficulty(const Difficulty& other)
        : level(other.level), width(other.width), height(other.height), bombs(other.bombs) {}

    void print() const {
        printf("Уровень сложности: %s (%dx%d, %d бомб)\n", level.c_str(), width, height, bombs);
    }

    Difficulty& operator=(const Difficulty& other) {
        if (this != &other) {
            level = other.level;
            width = other.width;
            height = other.height;
            bombs = other.bombs;
        }
        return *this;
    }

    bool operator==(const Difficulty& other) const {
        return level == other.level && width == other.width &&
            height == other.height && bombs == other.bombs;
    }
};

// ==================== КЛАСС 22: ПРОФИЛЬ ИГРОКА ====================

class PlayerProfile {
private:
    std::shared_ptr<Player> player;
    std::string avatar;
    int level;

public:
    PlayerProfile(std::shared_ptr<Player> p, const std::string& av = "default")
        : player(p), avatar(av), level(1) {}

    PlayerProfile(const PlayerProfile& other)
        : player(other.player), avatar(other.avatar), level(other.level) {}

    void print() const {
        printf("Профиль игрока: %s\n", player ? player->getName().c_str() : "нет игрока");
        printf("Аватар: %s, Уровень: %d\n", avatar.c_str(), level);
    }

    void levelUp() {
        level++;
    }

    PlayerProfile& operator=(const PlayerProfile& other) {
        if (this != &other) {
            player = other.player;
            avatar = other.avatar;
            level = other.level;
        }
        return *this;
    }

    PlayerProfile& operator++() {
        level++;
        return *this;
    }
};

// ==================== КЛАСС 23: ДОСТИЖЕНИЕ ====================

class Achievement {
private:
    std::string title;
    std::string description;
    bool unlocked;

public:
    Achievement(const std::string& t, const std::string& desc)
        : title(t), description(desc), unlocked(false) {}

    Achievement(const Achievement& other)
        : title(other.title), description(other.description), unlocked(other.unlocked) {}

    void print() const {
        printf("Достижение: %s - %s [%s]\n", title.c_str(), description.c_str(),
            unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }

    void unlock() {
        unlocked = true;
    }

    Achievement& operator=(const Achievement& other) {
        if (this != &other) {
            title = other.title;
            description = other.description;
            unlocked = other.unlocked;
        }
        return *this;
    }

    bool operator==(const Achievement& other) const {
        return title == other.title;
    }
};

// ==================== КЛАСС 24: СИСТЕМА ДОСТИЖЕНИЙ ====================

class AchievementSystem {
private:
    std::vector<Achievement> achievements;

public:
    AchievementSystem() {
        achievements.emplace_back("Новичок", "Сыграйте первую игру");
        achievements.emplace_back("Сапер", "Выиграйте 10 игр");
        achievements.emplace_back("Эксперт", "Выиграйте игру на сложном уровне");
    }

    AchievementSystem(const AchievementSystem& other) : achievements(other.achievements) {}

    void print() const {
        printf("=== СИСТЕМА ДОСТИЖЕНИЙ ===\n");
        for (const auto& achievement : achievements) {
            achievement.print();
        }
    }

    AchievementSystem& operator=(const AchievementSystem& other) {
        if (this != &other) {
            achievements = other.achievements;
        }
        return *this;
    }
};

// ==================== КЛАСС 25: СОХРАНЕНИЕ ИГРЫ ====================

class GameSave {
private:
    std::string saveName;
    time_t saveTime;
public:
    GameSave(const std::string& name) : saveName(name) {
        saveTime = time(NULL);
    }

    GameSave(const GameSave& other)
        : saveName(other.saveName + "_copy"), saveTime(other.saveTime) {}

    void print() const {
        printf("Сохранение: %s, время: %s", saveName.c_str(), ctime(&saveTime));
    }

    GameSave& operator=(const GameSave& other) {
        if (this != &other) {
            saveName = other.saveName + "_assigned";
            saveTime = other.saveTime;
        }
        return *this;
    }
};

// ==================== КЛАСС 26: МЕНЕДЖЕР СОХРАНЕНИЙ ====================

class SaveManager {
private:
    std::vector<std::shared_ptr<GameSave>> saves;

public:
    void print() const {
        printf("Менеджер сохранений, сохранений: %zu\n", saves.size());
        for (const auto& save : saves) {
            if (save) save->print();
        }
    }

    void createSave(const std::string& name) {
        saves.push_back(std::make_shared<GameSave>(name));
    }

    SaveManager& operator=(const SaveManager& other) {
        if (this != &other) {
            saves = other.saves;
        }
        return *this;
    }
};

// ==================== КЛАСС 27: ЗВУКОВАЯ СИСТЕМА ====================

class SoundSystem : public Elektropribor {
private:
    bool enabled;
    std::string soundDevice;
    int kanali;

public:
    SoundSystem(const std::string& device = "default", int channels = 2,
        const std::string& prod = "Creative", int year = 2023, float volt = 12.0f)
        : Elektropribor(prod, year, volt),
        enabled(true), soundDevice(device), kanali(channels) {}

    SoundSystem(const SoundSystem& other)
        : Elektropribor(other.proizvoditel, other.god_vypuska, other.napryazhenie),
        enabled(other.enabled), soundDevice(other.soundDevice), kanali(other.kanali) {}

    void print() const {
        printf("Звуковая система: %s, устройство: %s\n", enabled ? "включена" : "выключена", soundDevice.c_str());
        info();
    }

    void vkluchit() override {
        enabled = true;
        printf("Звуковая система '%s' включена\n", soundDevice.c_str());
    }

    void playClickSound() {
        if (enabled) {
            printf("[ЗВУК от %s] Клик!\n", proizvoditel.c_str());
        }
    }

    bool isModern() const {
        return (2024 - god_vypuska) <= 5;
    }

    void setEnabled(bool enable) { enabled = enable; }

    SoundSystem& operator=(const SoundSystem& other) {
        if (this != &other) {
            Elektropribor::operator=(other);
            enabled = other.enabled;
            soundDevice = other.soundDevice;
            kanali = other.kanali;
        }
        return *this;
    }

    bool operator==(const SoundSystem& other) const {
        return soundDevice == other.soundDevice && proizvoditel == other.proizvoditel;
    }
};

// ==================== КЛАСС 28: ТЕМА ОФОРМЛЕНИЯ ====================

class Theme {
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

    Theme(const Theme& other)
        : name(other.name), cellClosed(other.cellClosed),
        cellOpen(other.cellOpen), bomb(other.bomb) {}

    void print() const {
        printf("Тема: %s\n", name.c_str());
    }

    std::string getFullInfo() const {
        return "Тема: " + name + " (закрытая: '" + cellClosed + "', открытая: '" +
            cellOpen + "', бомба: '" + bomb + "')";
    }

    bool contains(const std::string& substr) const {
        return name.find(substr) != std::string::npos ||
            cellClosed.find(substr) != std::string::npos ||
            bomb.find(substr) != std::string::npos;
    }

    Theme& operator=(const Theme& other) {
        if (this != &other) {
            name = other.name;
            cellClosed = other.cellClosed;
            cellOpen = other.cellOpen;
            bomb = other.bomb;
        }
        return *this;
    }

    bool operator==(const Theme& other) const {
        return name == other.name;
    }
};

// ==================== КЛАСС 29: СИСТЕМА ПОМОЩИ ====================

class HelpSystem {
public:
    void print() const {
        printf("Система помощи\n");
    }

    void showTips() {
        printf("=== СОВЕТЫ ===\n");
        printf("1. Начинайте с углов\n");
        printf("2. Используйте флаги для отметки бомб\n");
        printf("3. Анализируйте цифры\n");
    }

    HelpSystem& operator=(const HelpSystem& other) {
        return *this;
    }
};

// ==================== КЛАСС 30: АНАЛИЗАТОР ИГРЫ ====================

class GameAnalyzer {
public:
    void print() const {
        printf("Анализатор игрового процесса\n");
    }

    void analyzeBoard(const Board& board) {
        printf("Анализ поля: бомб %d, клеток %d\n",
            board.getTotalBombs(), board.getWidth() * board.getHeight());
    }

    GameAnalyzer& operator=(const GameAnalyzer& other) {
        return *this;
    }
};

// ==================== КЛАСС 31: РЕКОРД ====================

class HighScore : public Rekordsmen {
private:
    std::string playerName;
    int score;
    int time;
    std::string difficulty;

public:
    HighScore(const std::string& name, int s, int t, const std::string& diff,
        const std::string& sport = "Сапёр", const std::string& org = "Мировые рекорды",
        int year = 2024)
        : Rekordsmen(sport, org, year),
        playerName(name), score(s), time(t), difficulty(diff) {}

    HighScore(const HighScore& other)
        : Rekordsmen(other.vid_sporta, other.organizaciya, other.god_ustanovki),
        playerName(other.playerName), score(other.score),
        time(other.time), difficulty(other.difficulty) {}

    void print() const {
        printf("Рекорд: %s - %d очков, время: %d сек, сложность: %s\n",
            playerName.c_str(), score, time, difficulty.c_str());
        printf("Вид спорта: %s, Организация: %s\n", vid_sporta.c_str(), organizaciya.c_str());
    }

    void zafiksirovat_rekord() override {
        printf("Рекорд зафиксирован! %s: %d очков\n", playerName.c_str(), score);
        if (mirovoy_rekord()) {
            printf("⭐ ЭТО МИРОВОЙ РЕКОРД! ⭐\n");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const HighScore& hs);

    bool operator>(const HighScore& other) const {
        return score > other.score;
    }

    HighScore& operator=(const HighScore& other) {
        if (this != &other) {
            Rekordsmen::operator=(other);
            playerName = other.playerName;
            score = other.score;
            time = other.time;
            difficulty = other.difficulty;
        }
        return *this;
    }

    int getScore() const { return score; }
};

std::ostream& operator<<(std::ostream& os, const HighScore& hs) {
    os << hs.playerName << ": " << hs.score << " очков (" << hs.vid_sporta << ")";
    return os;
}

// ==================== КЛАСС 32: МЕНЕДЖЕР РЕКОРДОВ ====================

class HighScoreManager {
private:
    std::vector<std::shared_ptr<HighScore>> highScores;
public:
    void print() const {
        printf("=== ТАБЛИЦА РЕКОРДОВ ===\n");
        for (size_t i = 0; i < highScores.size(); i++) {
            printf("%zu. ", i + 1);
            if (highScores[i]) highScores[i]->print();
        }
    }

    void addScore(std::shared_ptr<HighScore> score) {
        highScores.push_back(score);
        std::sort(highScores.begin(), highScores.end(),
            [](const std::shared_ptr<HighScore>& a, const std::shared_ptr<HighScore>& b) {
                return a && b && a->getScore() > b->getScore();
            });
    }

    HighScoreManager& operator=(const HighScoreManager& other) {
        if (this != &other) {
            highScores = other.highScores;
        }
        return *this;
    }
};

// ==================== КЛАСС 33: СИСТЕМА ПОДСКАЗОК ====================

class HintSystem {
private:
    int hintsAvailable;

public:
    HintSystem() : hintsAvailable(3) {}

    HintSystem(const HintSystem& other) : hintsAvailable(other.hintsAvailable) {}

    void print() const {
        printf("Система подсказок, доступно подсказок: %d\n", hintsAvailable);
    }

    bool useHint() {
        if (hintsAvailable > 0) {
            hintsAvailable--;
            return true;
        }
        return false;
    }

    HintSystem& operator=(const HintSystem& other) {
        if (this != &other) {
            hintsAvailable = other.hintsAvailable;
        }
        return *this;
    }

    HintSystem& operator--() {
        if (hintsAvailable > 0) hintsAvailable--;
        return *this;
    }

    HintSystem operator--(int) {
        HintSystem temp = *this;
        if (hintsAvailable > 0) hintsAvailable--;
        return temp;
    }
};

// ==================== КЛАСС 34: ИСТОРИЯ ИГРЫ ====================

class GameHistory {
private:
    std::vector<std::string> moves;

public:
    GameHistory() {}
    GameHistory(const GameHistory& other) : moves(other.moves) {}

    void print() const {
        printf("=== ИСТОРИЯ ХОДОВ ===\n");
        for (size_t i = 0; i < moves.size(); i++) {
            printf("Ход %zu: %s\n", i + 1, moves[i].c_str());
        }
    }

    void addMove(const std::string& move) {
        moves.push_back(move);
    }

    GameHistory& operator=(const GameHistory& other) {
        if (this != &other) {
            moves = other.moves;
        }
        return *this;
    }

    GameHistory& operator+=(const std::string& move) {
        moves.push_back(move);
        return *this;
    }
};

// ==================== КЛАСС 35: СЧЕТЧИК ХОДОВ ====================

class MoveCounter : public Schitatel {
private:
    int totalMoves;
    int safeMoves;
    int flagMoves;
    int bombMoves;

public:
    MoveCounter(const std::string& type = "Электронный", int max = 999, bool calib = true,
        int total = 0, int safe = 0, int flag = 0, int bomb = 0)
        : Schitatel(type, max, calib),
        totalMoves(total), safeMoves(safe), flagMoves(flag), bombMoves(bomb) {}

    MoveCounter(const MoveCounter& other)
        : Schitatel(other.tip, other.max_znachenie, other.kalibrovka),
        totalMoves(other.totalMoves), safeMoves(other.safeMoves),
        flagMoves(other.flagMoves), bombMoves(other.bombMoves) {}

    void print() const {
        printf("=== СТАТИСТИКА ХОДОВ ===\n");
        printf("Тип счётчика: %s, Макс: %d, %s\n",
            tip.c_str(), max_znachenie, status().c_str());
        printf("Всего ходов: %d/%d\n", totalMoves, max_znachenie);
        printf("Безопасных: %d, Флагов: %d, Бомб: %d\n", safeMoves, flagMoves, bombMoves);
    }

    void schitat() override {
        printf("Счётчик '%s' подсчитывает... Всего ходов: %d\n", tip.c_str(), totalMoves);
        if (totalMoves >= max_znachenie) {
            printf("⚠️ Достигнут предел счётчика!\n");
        }
    }

    void addSafeMove() {
        if (totalMoves < max_znachenie) {
            totalMoves++;
            safeMoves++;
        }
    }

    void addBombMove() {
        if (totalMoves < max_znachenie) {
            totalMoves++;
            bombMoves++;
        }
    }

    MoveCounter& operator++() {
        addSafeMove();
        return *this;
    }

    MoveCounter operator++(int) {
        MoveCounter temp = *this;
        addSafeMove();
        return temp;
    }

    MoveCounter& operator+=(int moves) {
        for (int i = 0; i < moves && totalMoves < max_znachenie; i++) {
            totalMoves++;
            safeMoves++;
        }
        return *this;
    }

    MoveCounter& operator=(const MoveCounter& other) {
        if (this != &other) {
            Schitatel::operator=(other);
            totalMoves = other.totalMoves;
            safeMoves = other.safeMoves;
            flagMoves = other.flagMoves;
            bombMoves = other.bombMoves;
        }
        return *this;
    }
};

// ==================== ДЕМОНСТРАЦИОННАЯ ФУНКЦИЯ ====================

void demonstrateAllFeatures() {
    printf("=== ДЕМОНСТРАЦИЯ ВСЕХ ВОЗМОЖНОСТЕЙ САПЕРА ===\n\n");

    try {
        // 1. Смарт-указатели
        printf("1. SMART POINTERS:\n");
        auto player = std::make_shared<Player>("Игрок 1");
        auto board = std::make_unique<Board>(5, 5, 3);
        auto game = std::make_unique<Game>(std::move(board), player);

        // 2. Наследование с данными
        printf("\n2. НАСЛЕДОВАНИЕ С ДАННЫМИ:\n");
        Coordinate coord(10, 20, "Россия", "Москва", 55.7558, 37.6173);
        coord.print();
        coord.pokazat_mesto();

        SoundSystem sound("Игровая", 2, "Logitech", 2022);
        sound.print();
        sound.vkluchit();

        GameFactory factory("Blizzard", "RPG", "Калифорния", 5000);
        factory.print();
        factory.proizvesti();

        MoveCounter counter("Точный", 10, true);
        counter.print();
        counter.schitat();

        HighScore record("Алексей", 1500, 45, "Сложный", "Сапёр", "Мировые рекорды");
        record.print();
        record.zafiksirovat_rekord();

        // 3. Перегрузка операторов
        printf("\n3. ПЕРЕГРУЗКА ОПЕРАТОРОВ:\n");
        Coordinate c1(1, 2);
        Coordinate c2(3, 4);
        Coordinate c3 = c1 + c2;
        std::cout << "c1 + c2 = " << c3 << std::endl;

        Player p1("А");
        Player p2("Б");
        p1 += 100;
        ++p1;
        std::cout << "p1: " << p1 << std::endl;

        HighScore hs1("Игрок1", 1000, 60, "Легко");
        HighScore hs2("Игрок2", 1500, 45, "Легко");
        if (hs1 > hs2) std::cout << "hs1 > hs2" << std::endl;
        else std::cout << "hs1 < hs2" << std::endl;

        std::cout << "Рекорд: " << hs1 << std::endl;

        // 4. Дружественные функции
        printf("\n4. ДРУЖЕСТВЕННЫЕ ФУНКЦИИ:\n");
        swapCoordinates(c1, c2);
        std::cout << "После swap: c1 = " << c1 << ", c2 = " << c2 << std::endl;

        // 5. Статические поля и методы
        printf("\n5. СТАТИЧЕСКИЕ ЧЛЕНЫ:\n");
        printf("Всего координат: %d\n", Coordinate::getTotalCoordinates());
        printf("Всего оцененных игр: %d\n", ScoringSystem::getTotalGamesScored());

        // 6. Конструкторы копирования
        printf("\n6. КОНСТРУКТОРЫ КОПИРОВАНИЯ:\n");
        Coordinate coordCopy(coord);
        coordCopy.print();

        Player playerCopy(*player);
        playerCopy.print();

        // 7. Исключения
        printf("\n7. ОБРАБОТКА ИСКЛЮЧЕНИЙ:\n");
        try {
            Validator validator;
            if (!validator.isValidCoordinate(10, 10, 5, 5)) {
                throw std::runtime_error("Тестовое исключение");
            }
        }
        catch (const std::exception& e) {
            printf("Исключение перехвачено: %s\n", e.what());
        }

        // 8. Работа со строками
        printf("\n8. РАБОТА СО СТРОКАМИ:\n");
        std::string str = "Игрок: ";
        str += player->getName();
        str += " имеет ";
        str += std::to_string(player->getMistakes());
        str += " ошибок";
        printf("%s\n", str.c_str());

        Theme theme("modern");
        printf("Информация о теме: %s\n", theme.getFullInfo().c_str());
        printf("Содержит 'mod'? %s\n", theme.contains("mod") ? "Да" : "Нет");

        // 9. Использование this
        printf("\n9. ИСПОЛЬЗОВАНИЕ this:\n");
        player->setName("Новое имя");
        player->print();

        // 10. Все классы в действии
        printf("\n10. ВСЕ 35 КЛАССОВ:\n");

        Settings settings;
        settings.print();

        Logger logger("game.log");
        logger.print();

        Leaderboard lb("Игрок", 120, 9, 9, 10, 1);
        lb.print();

        Menu menu;
        menu.print();

        GameStats stats;
        stats.addGame(true, 100);
        stats.print();

        RandomGenerator randGen;
        printf("Случайное число: %d\n", randGen.getRandom(1, 100));

        Renderer renderer;
        renderer.print();

        InputHandler input;
        input.print();

        GameController controller;
        controller.print();

        Validator validator;
        validator.print();

        ScoringSystem scoring;
        printf("Очки: %d\n", scoring.calculateScore(*player, 100));

        PlayerSession session(player);
        session.print();

        Notifier notifier;
        notifier.showWinMessage();

        Difficulty diff("Легко", 9, 9, 10);
        diff.print();

        PlayerProfile profile(player);
        profile.print();

        Achievement achievement("Первый шаг", "Сыграйте игру");
        achievement.print();

        AchievementSystem achSystem;
        achSystem.print();

        GameSave save("save1");
        save.print();

        SaveManager saveManager;
        saveManager.createSave("autosave");

        HelpSystem help;
        help.showTips();

        GameAnalyzer analyzer;
        analyzer.print();

        HighScoreManager hsManager;
        hsManager.addScore(std::make_shared<HighScore>("Игрок", 1000, 60, "Легко"));

        HintSystem hints;
        hints.print();

        GameHistory history;
        history.addMove("Открытие (1,1)");

        // 11. Операторы присваивания
        printf("\n11. ОПЕРАТОРЫ ПРИСВАИВАНИЯ:\n");
        Settings s1, s2;
        s2 = s1;

        GameStats stats1, stats2;
        stats2 = stats1;

        // 12. Дополнительные операторы
        printf("\n12. ДОПОЛНИТЕЛЬНЫЕ ОПЕРАТОРЫ:\n");
        counter++;
        ++counter;
        counter += 3;
        counter.print();

        hints--;
        --hints;
        hints.print();

        GameStats combined = stats1 + stats2;
        combined.print();

    }
    catch (const std::exception& e) {
        printf("Ошибка в демонстрации: %s\n", e.what());
    }
}

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    printf("=== САПЁР НА C++ С 35 КЛАССАМИ ===\n");
    printf("Реализованы все требования: смарт-указатели, наследование,\n");
    printf("перегрузка операторов, исключения, статические члены и др.\n\n");

    demonstrateAllFeatures();

    printf("\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n");

    return 0;
}