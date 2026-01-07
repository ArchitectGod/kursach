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
