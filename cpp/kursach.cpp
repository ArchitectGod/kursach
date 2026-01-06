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
