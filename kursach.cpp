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

class Settings : public GameObject {          //Класс настроек
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

class Timer : public GameObject {          // Класс счетчика времени
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

class Coordinate : public GameObject {      //Класс координат
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