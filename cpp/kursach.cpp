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
#include <cmath>


// Электроприбор 
class Elektropribor {
protected:
    std::string tip; 
    float uroven_gromkosti; 
    bool podklyuchen; 
    
public:
    Elektropribor(const std::string& device_type = "Колонки", float volume = 50.0f, bool connected = true)
        : tip(device_type), uroven_gromkosti(volume), podklyuchen(connected) {}
    
    virtual ~Elektropribor() = default;
    
    virtual void izdat_zvuk(const std::string& zvuk) = 0;
    
    void nastroit_gromkost(float novaya_gromkost) {
        if (novaya_gromkost >= 0 && novaya_gromkost <= 100) {
            uroven_gromkosti = novaya_gromkost;
        }
    }
    
    void pereklyuchit_podklyuchenie() {
        podklyuchen = !podklyuchen;
    }
    
    std::string getTip() const { return tip; }
    float getUrovenGromkosti() const { return uroven_gromkosti; }
    bool getPodklyuchen() const { return podklyuchen; }
    
    virtual void info() const {
        printf("Устройство: %s, Громкость: %.1f%%, %s\n", 
               tip.c_str(), uroven_gromkosti, podklyuchen ? "Подключено" : "Отключено");
    }
};

// География  
class Geografiya {
protected:
    std::string nazvanie_regiona; 
    int uroven_opasnosti; 
    bool razvedeno;
    
public:
    Geografiya(const std::string& region = "Неизвестно", int danger = 0, bool explored = false)
        : nazvanie_regiona(region), uroven_opasnosti(danger), razvedeno(explored) {}
    
    virtual ~Geografiya() = default;
    
    virtual void issledovat_territoriyu() = 0;
    
    void izmenit_opasnost(int novaya_opasnost) {
        if (novaya_opasnost >= 0 && novaya_opasnost <= 10) {
            uroven_opasnosti = novaya_opasnost;
        }
    }
    
    void pometit_kak_razvedennuyu() {
        razvedeno = true;
    }
    
    std::string getNazvanieRegiona() const { return nazvanie_regiona; }
    int getUrovenOpasnosti() const { return uroven_opasnosti; }
    bool getRazvedeno() const { return razvedeno; }
    
    bool opasniy_region() const {
        return uroven_opasnosti >= 7;
    }
    
    virtual std::string opisanie() const {
        return nazvanie_regiona + " (опасность: " + std::to_string(uroven_opasnosti) + "/10)";
    }
};

// Завод 
class Zavod {
protected:
    std::string specializaciya; 
    int proizvoditelnost; 
    int kachestvo; 
    
public:
    Zavod(const std::string& spec = "Стандартные", int productivity = 10, int quality = 7)
        : specializaciya(spec), proizvoditelnost(productivity), kachestvo(quality) {}
    
    virtual ~Zavod() = default;
    
    virtual void sozdat_igrovoe_pole() = 0;
    
    void uluchsit_kachestvo(int na_skolko) {
        kachestvo += na_skolko;
        if (kachestvo > 10) kachestvo = 10;
    }
    
    void izmenit_specializaciyu(const std::string& novaya_spec) {
        specializaciya = novaya_spec;
    }
    
    std::string getSpecializaciya() const { return specializaciya; }
    int getProizvoditelnost() const { return proizvoditelnost; }
    int getKachestvo() const { return kachestvo; }
    
    bool vysokoe_kachestvo() const {
        return kachestvo >= 8;
    }
    
    virtual float efektivnost() const {
        return proizvoditelnost * (kachestvo / 10.0f);
    }
};

// Считатель 
class Schitatel {
protected:
    std::string tip_otscheta; 
    int predel_otscheta; 
    bool avtomaticheskiy; 
    
public:
    Schitatel(const std::string& count_type = "Ходы", int limit = 100, bool automatic = true)
        : tip_otscheta(count_type), predel_otscheta(limit), avtomaticheskiy(automatic) {}
    
    virtual ~Schitatel() = default;
    
    virtual void nachat_otschet() = 0;
    
    void ustanovit_predel(int noviy_predel) {
        predel_otscheta = noviy_predel;
    }
    
    void pereklyuchit_rezhim() {
        avtomaticheskiy = !avtomaticheskiy;
    }
    
    std::string getTipOtscheta() const { return tip_otscheta; }
    int getPredelOtscheta() const { return predel_otscheta; }
    bool getAvtomaticheskiy() const { return avtomaticheskiy; }
    
    bool dostignut_predel(int tekushee_znachenie) const {
        return tekushee_znachenie >= predel_otscheta;
    }
    
    virtual std::string status() const {
        return avtomaticheskiy ? "Автоматический" : "Ручной";
    }
};

// Рекордсмен 
class Rekordsmen {
protected:
    std::string kategoriya; 
    std::string uroven_slozhnosti; 
    int god_ustanovki; 
    
public:
    Rekordsmen(const std::string& category = "Время", const std::string& difficulty = "Средний", int year = 2024)
        : kategoriya(category), uroven_slozhnosti(difficulty), god_ustanovki(year) {}
    
    virtual ~Rekordsmen() = default;
    
    virtual void zaregistrirovat_rekord() = 0;
    
    void izmenit_kategoriyu(const std::string& novaya_kategoriya) {
        kategoriya = novaya_kategoriya;
    }
    
    void izmenit_slozhnost(const std::string& novaya_slozhnost) {
        uroven_slozhnosti = novaya_slozhnost;
    }
    
    std::string getKategoriya() const { return kategoriya; }
    std::string getUrovenSlozhnosti() const { return uroven_slozhnosti; }
    int getGodUstanovki() const { return god_ustanovki; }
    
    bool sovremenniy_rekord() const {
        return (2024 - god_ustanovki) <= 2;
    }
    
    virtual bool validniy_rekord() const {
        return !kategoriya.empty() && !uroven_slozhnosti.empty() && god_ustanovki > 2000;
    }
};

class Coordinate : public Geografiya {
private:
    int x;
    int y;
    static int totalCoordinates;

public:
    Coordinate(int xCoord = 0, int yCoord = 0, 
               const std::string& region = "Центральный", int danger = 1, bool explored = false)
        : Geografiya(region, danger, explored), x(xCoord), y(yCoord) {
        totalCoordinates++;
    }
    
    Coordinate(const Coordinate& other) 
        : Geografiya(other.nazvanie_regiona, other.uroven_opasnosti, other.razvedeno),
          x(other.x), y(other.y) {
        totalCoordinates++;
    }
    
    ~Coordinate() {
        totalCoordinates--;
    }
    
    void print() const {
        printf("Координаты: [%d, %d] - %s\n", x, y, opisanie().c_str());
    }
    
    void issledovat_territoriyu() override {
        if (!razvedeno) {
            razvedeno = true;
        }
    }
    
    // Перегрузка операторов
    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }
    
    Coordinate operator+(const Coordinate& other) const {
        return Coordinate(x + other.x, y + other.y, 
                         nazvanie_regiona, 
                         std::max(uroven_opasnosti, other.uroven_opasnosti));
    }
    
    Coordinate operator-(const Coordinate& other) const {
        return Coordinate(x - other.x, y - other.y, nazvanie_regiona);
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
    friend void obmenyat_koordinati(Coordinate& a, Coordinate& b);
    
    static int getTotalCoordinates() {
        return totalCoordinates;
    }
    
    static void sbrosit_schetchik() {
        totalCoordinates = 0;
    }
    
    int getX() const { return this->x; }
    int getY() const { return this->y; }
    
    void setX(int newX) { this->x = newX; }
    void setY(int newY) { this->y = newY; }
    
    bool isValid(int maxX, int maxY) const {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }
    
    double rasstoyanie_do(const Coordinate& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    std::string toString() const {
        return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
    }
    
    void otsenit_opasnost_dlya_sapera() {
        if (opasniy_region()) {
            printf("⚠️ [%d,%d] - Опасная зона!\n", x, y);
        } else if (uroven_opasnosti >= 4) {
            printf("⚠️ [%d,%d] - Требует осторожности\n", x, y);
        }
    }
};

int Coordinate::totalCoordinates = 0;

void obmenyat_koordinati(Coordinate& a, Coordinate& b) {
    std::swap(a.x, b.x);
    std::swap(a.y, b.y);
    std::swap(a.nazvanie_regiona, b.nazvanie_regiona);
    std::swap(a.uroven_opasnosti, b.uroven_opasnosti);
}

std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
    os << "[" << coord.x << "," << coord.y << "]";
    return os;
}

class Cell {
private:
    bool bomba;
    bool otkrita;
    bool flag;
    int bomby_vokrug;
    std::shared_ptr<Coordinate> koordinata;

public:
    Cell(int x = 0, int y = 0) : bomba(false), otkrita(false), flag(false), bomby_vokrug(0) {
        std::string region;
        if (x < 5 && y < 5) region = "Северо-Запад";
        else if (x >= 5 && y < 5) region = "Северо-Восток";
        else if (x < 5 && y >= 5) region = "Юго-Запад";
        else region = "Юго-Восток";
        
        koordinata = std::make_shared<Coordinate>(x, y, region, 1);
    }
    
    Cell(const Cell& other) 
        : bomba(other.bomba), otkrita(other.otkrita), flag(other.flag), 
          bomby_vokrug(other.bomby_vokrug) {
        koordinata = std::make_shared<Coordinate>(*other.koordinata);
    }
    
    void print() const {
        printf("Клетка ");
        koordinata->print();
        printf("Состояние: ");
        if (otkrita) {
            if (bomba) printf("💣 БОМБА");
            else printf("📊 %d бомб вокруг", bomby_vokrug);
        } else if (flag) {
            printf("🚩 ФЛАГ");
        } else {
            printf("⬜ ЗАКРЫТА");
        }
        printf("\n");
    }
    
    void otkrit() {
        if (!otkrita) {
            otkrita = true;
            flag = false;
            koordinata->issledovat_territoriyu();
            
            if (bomba) {
                koordinata->izmenit_opasnost(10);
            } else if (bomby_vokrug > 0) {
                koordinata->izmenit_opasnost(bomby_vokrug + 2);
            }
        }
    }
    
    void pereklyuchit_flag() {
        if (!otkrita) {
            flag = !flag;
        }
    }
    
    void ustanovit_bombu() {
        bomba = true;
        koordinata->izmenit_opasnost(8);
    }
    
    void ustanovit_bomby_vokrug(int count) {
        bomby_vokrug = count;
    }
    
    bool getBomba() const { return bomba; }
    bool getOtkrita() const { return otkrita; }
    bool getFlag() const { return flag; }
    int getBombyVokrug() const { return bomby_vokrug; }
    int getX() const { return koordinata->getX(); }
    int getY() const { return koordinata->getY(); }
    
    std::shared_ptr<Coordinate> getKoordinata() const { return koordinata; }
    
    Cell& operator=(const Cell& other) {
        if (this != &other) {
            bomba = other.bomba;
            otkrita = other.otkrita;
            flag = other.flag;
            bomby_vokrug = other.bomby_vokrug;
            koordinata = std::make_shared<Coordinate>(*other.koordinata);
        }
        return *this;
    }
    
    bool operator==(const Cell& other) const {
        return getX() == other.getX() && getY() == other.getY();
    }
    
    std::string getInfo() const {
        std::string info = "Клетка " + koordinata->toString() + ": ";
        if (otkrita) {
            if (bomba) info += "БОМБА";
            else info += std::to_string(bomby_vokrug) + " бомб вокруг";
        } else if (flag) {
            info += "ФЛАГ";
        } else {
            info += "ЗАКРЫТА";
        }
        return info;
    }
};

class Board {
private:
    int shirina;
    int vysota;
    int vsego_bomb;
    int bezopasnye_kletki;
    std::vector<Cell> kletki;

public:
    Board(int width = 9, int height = 9, int bombs = 10) 
        : shirina(width), vysota(height), vsego_bomb(bombs), bezopasnye_kletki(width * height - bombs) {
        
        for (int y = 0; y < vysota; y++) {
            for (int x = 0; x < shirina; x++) {
                std::string region;
                if (x < shirina/2 && y < vysota/2) region = "Северо-Запад";
                else if (x >= shirina/2 && y < vysota/2) region = "Северо-Восток";
                else if (x < shirina/2 && y >= vysota/2) region = "Юго-Запад";
                else region = "Юго-Восток";
                
                kletki.emplace_back(x, y);
            }
        }
    }
    
    Board(const Board& other) 
        : shirina(other.shirina), vysota(other.vysota), vsego_bomb(other.vsego_bomb),
          bezopasnye_kletki(other.bezopasnye_kletki), kletki(other.kletki) {}
    
    void print() const {
        printf(" ");
        for (int x = 0; x < shirina; x++) {
            printf("%2d ", x);
        }
        printf("\n");

        for (int y = 0; y < vysota; y++) {
            printf("%2d ", y);
            for (int x = 0; x < shirina; x++) {
                const Cell& kletka = kletki[y * shirina + x];
                if (kletka.getOtkrita()) {
                    if (kletka.getBomba()) {
                        printf(" * ");
                    } else {
                        printf(" %d ", kletka.getBombyVokrug());
                    }
                } else if (kletka.getFlag()) {
                    printf(" F ");
                } else {
                    printf(" . ");
                }
            }
            printf("\n");
        }
        printf("Бомб: %d, Безопасных клеток осталось: %d\n", vsego_bomb, bezopasnye_kletki);
    }
    
    std::shared_ptr<Cell> getKletka(int x, int y) {
        try {
            if (x < 0 || x >= shirina || y < 0 || y >= vysota) {
                throw std::out_of_range("Неверные координаты: " + 
                                       std::to_string(x) + "," + std::to_string(y));
            }
            return std::make_shared<Cell>(kletki[y * shirina + x]);
        }
        catch (const std::exception& e) {
            printf("Ошибка: %s\n", e.what());
            return nullptr;
        }
    }
    
    void umenshit_bezopasnye_kletki() {
        if (bezopasnye_kletki > 0) {
            bezopasnye_kletki--;
        }
    }
    
    bool pobeda() const {
        return bezopasnye_kletki == 0;
    }
    
    void razmestit_bomby(int startX, int startY) {
        int razmesheno_bomb = 0;
        while (razmesheno_bomb < vsego_bomb) {
            int x = rand() % shirina;
            int y = rand() % vysota;

            if ((abs(x - startX) <= 1 && abs(y - startY) <= 1) ||
                kletki[y * shirina + x].getBomba()) {
                continue;
            }

            kletki[y * shirina + x].ustanovit_bombu();
            razmesheno_bomb++;
        }
        pereschet_bomb_vokrug();
    }
    
    void pereschet_bomb_vokrug() {
        for (int y = 0; y < vysota; y++) {
            for (int x = 0; x < shirina; x++) {
                auto kletka = getKletka(x, y);
                if (kletka && !kletka->getBomba()) {
                    int count = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            auto sosed = getKletka(x + dx, y + dy);
                            if (sosed && sosed->getBomba()) {
                                count++;
                            }
                        }
                    }
                    kletka->ustanovit_bomby_vokrug(count);
                }
            }
        }
    }
    
    int getShirina() const { return shirina; }
    int getVysota() const { return vysota; }
    int getVsegoBomb() const { return vsego_bomb; }
    int getBezopasnyeKletki() const { return bezopasnye_kletki; }
    
    Board& operator=(const Board& other) {
        if (this != &other) {
            shirina = other.shirina;
            vysota = other.vysota;
            vsego_bomb = other.vsego_bomb;
            bezopasnye_kletki = other.bezopasnye_kletki;
            kletki = other.kletki;
        }
        return *this;
    }
    
    void printRegiony() const {
        printf("=== РЕГИОНЫ ПОЛЯ ===\n");
        for (int y = 0; y < vysota; y++) {
            for (int x = 0; x < shirina; x++) {
                const Cell& kletka = kletki[y * shirina + x];
                auto coord = kletka.getKoordinata();
                printf("%c ", coord->getNazvanieRegiona()[0]);
            }
            printf("\n");
        }
    }
};

class Player {
private:
    std::string imya;
    int vremya_igry;
    int otkrytye_kletki;
    int oshibki;
    int luchshee_vremya;

public:
    Player(const std::string& name = "") 
        : imya(name), vremya_igry(0), otkrytye_kletki(0), oshibki(0), luchshee_vremya(0) {}
    
    Player(const Player& other) 
        : imya(other.imya), vremya_igry(other.vremya_igry), 
          otkrytye_kletki(other.otkrytye_kletki), oshibki(other.oshibki),
          luchshee_vremya(other.luchshee_vremya) {}
    
    void print() const {
        printf("Игрок: %s\n", imya.c_str());
        printf("Время: %d сек, Открыто: %d, Ошибок: %d, Лучшее время: %d сек\n", 
               vremya_igry, otkrytye_kletki, oshibki, luchshee_vremya);
    }
    
    bool operator>(const Player& other) const {
        if (luchshee_vremya == 0) return false;
        if (other.luchshee_vremya == 0) return true;
        return luchshee_vremya < other.luchshee_vremya;
    }
    
    Player& operator+=(int seconds) {
        vremya_igry += seconds;
        return *this;
    }
    
    Player& operator++() {
        oshibki++;
        return *this;
    }
    
    Player operator++(int) {
        Player temp = *this;
        oshibki++;
        return temp;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    
    void dobavit_oshibku() { 
        oshibki++; 
    }
    
    void dobavit_otkrytuyu_kletku() { 
        otkrytye_kletki++; 
    }
    
    void obnovit_luchshee_vremya() {
        if (luchshee_vremya == 0 || vremya_igry < luchshee_vremya) {
            luchshee_vremya = vremya_igry;
        }
    }
    
    std::string getImya() const { return imya; }
    int getVremyaIgry() const { return vremya_igry; }
    int getOtkrytyeKletki() const { return otkrytye_kletki; }
    int getOshibki() const { return oshibki; }
    int getLuchsheeVremya() const { return luchshee_vremya; }
    
    void setVremyaIgry(int time) { vremya_igry = time; }
    void setImya(const std::string& newName) { imya = newName; }
    
    std::string getStatistika() const {
        return imya + ": " + std::to_string(luchshee_vremya) + " сек, " + 
               std::to_string(oshibki) + " ошибок";
    }
    
    float effektivnost() const {
        if (otkrytye_kletki == 0) return 0.0f;
        return (float)(otkrytye_kletki - oshibki) / otkrytye_kletki * 100;
    }
};

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.imya << " - " << player.luchshee_vremya << " сек";
    return os;
}

class Timer {
private:
    time_t start_time;
    time_t pause_time;
    bool is_running;

public:
    Timer() : start_time(0), pause_time(0), is_running(false) {}
    
    Timer(const Timer& other) 
        : start_time(other.start_time), pause_time(other.pause_time), is_running(other.is_running) {}
    
    void print() const {
        printf("Таймер: %d секунд, статус: %s\n", getElapsedTime(), is_running ? "работает" : "на паузе");
    }
    
    void start() {
        start_time = time(NULL);
        is_running = true;
    }
    
    void pause() {
        if (is_running) {
            pause_time = time(NULL);
            is_running = false;
        }
    }
    
    void resume() {
        if (!is_running) {
            start_time += (time(NULL) - pause_time);
            is_running = true;
        }
    }
    
    int getElapsedTime() const {
        if (is_running) {
            return (int)(time(NULL) - start_time);
        }
        return (int)(pause_time - start_time);
    }
    
    void reset() {
        start_time = 0;
        pause_time = 0;
        is_running = false;
    }
    
    Timer& operator=(const Timer& other) {
        if (this != &other) {
            start_time = other.start_time;
            pause_time = other.pause_time;
            is_running = other.is_running;
        }
        return *this;
    }
};

class Game {
private:
    std::unique_ptr<Board> pole;
    std::shared_ptr<Player> igrok;
    int sostoyanie;
    std::unique_ptr<Timer> taymer;

public:
    Game(std::unique_ptr<Board> board, std::shared_ptr<Player> player) 
        : pole(std::move(board)), igrok(player), sostoyanie(0) {
        taymer = std::make_unique<Timer>();
        taymer->start();
    }
    
    void print() const {
        printf("=== СОСТОЯНИЕ ИГРЫ ===\n");
        printf("Статус: ");
        switch (sostoyanie) {
            case 0: printf("В процессе\n"); break;
            case 1: printf("ПОБЕДА!\n"); break;
            case 2: printf("ПРОИГРЫШ\n"); break;
        }
        printf("Время игры: %d сек\n", getGameTime());
        if (pole) pole->print();
        if (igrok) igrok->print();
    }
    
    void winGame() {
        sostoyanie = 1;
        if (igrok) {
            igrok->obnovit_luchshee_vremya();
        }
    }
    
    void loseGame() {
        sostoyanie = 2;
        if (igrok) {
            igrok->dobavit_oshibku();
        }
    }
    
    bool isGameRunning() const {
        return sostoyanie == 0;
    }
    
    int getGameTime() const {
        return taymer->getElapsedTime();
    }
    
    void pauseGame() {
        taymer->pause();
    }
    
    void resumeGame() {
        taymer->resume();
    }
    
    void makeMove(int x, int y) {
        if (!isGameRunning() || !pole) return;
        
        auto kletka = pole->getKletka(x, y);
        if (kletka && !kletka->getOtkrita()) {
            kletka->otkrit();
            pole->umenshit_bezopasnye_kletki();
            igrok->dobavit_otkrytuyu_kletku();
            
            if (kletka->getBomba()) {
                loseGame();
            } else if (pole->pobeda()) {
                winGame();
            }
        }
    }
    
    int getSostoyanie() const { return sostoyanie; }
    Board* getPole() const { return pole.get(); }
    std::shared_ptr<Player> getIgrok() const { return igrok; }
};

class Settings {
private:
    int auto_bombs;
    int zvuki;
    int slozhnost;

public:
    Settings() : auto_bombs(1), zvuki(1), slozhnost(0) {}
    
    Settings(const Settings& other) 
        : auto_bombs(other.auto_bombs), zvuki(other.zvuki), slozhnost(other.slozhnost) {}
    
    void print() const {
        printf("=== НАСТРОЙКИ ===\n");
        printf("Авторасстановка бомб: %s\n", auto_bombs ? "Вкл" : "Выкл");
        printf("Звуки: %s\n", zvuki ? "Вкл" : "Выкл");
        printf("Сложность: ");
        switch (slozhnost) {
            case 0: printf("Легко\n"); break;
            case 1: printf("Средне\n"); break;
            case 2: printf("Сложно\n"); break;
        }
    }
    
    std::unique_ptr<Board> sozdatPolePoSlozhnosti() const {
        switch (slozhnost) {
            case 0: return std::make_unique<Board>(9, 9, 10);
            case 1: return std::make_unique<Board>(16, 16, 40);
            case 2: return std::make_unique<Board>(30, 16, 99);
            default: return std::make_unique<Board>(9, 9, 10);
        }
    }
    
    int getAutoBombs() const { return auto_bombs; }
    int getZvuki() const { return zvuki; }
    int getSlozhnost() const { return slozhnost; }
    
    void setSlozhnost(int level) { slozhnost = level; }
    
    Settings& operator=(const Settings& other) {
        if (this != &other) {
            auto_bombs = other.auto_bombs;
            zvuki = other.zvuki;
            slozhnost = other.slozhnost;
        }
        return *this;
    }
};

class Logger {
private:
    std::string filename;
    FILE* file;

public:
    Logger(const std::string& fname) : filename(fname) {
        file = fopen(filename.c_str(), "a");
        if (!file) {
            throw std::runtime_error("Не удалось открыть файл: " + filename);
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

class Leaderboard {
private:
    std::string imya;
    int vremya;
    int vysota;
    int shirina;
    int bomby;
    int day;
    int month;
    int year;
    int win;

public:
    Leaderboard(const std::string& playerName, int time, int width, int height, int bombs, int victory) 
        : imya(playerName), vremya(time), shirina(width), vysota(height), bomby(bombs), win(victory) {
        
        time_t t_now = ::time(NULL);
        struct tm* tm_info = localtime(&t_now);
        day = tm_info->tm_mday;
        month = tm_info->tm_mon + 1;
        year = tm_info->tm_year + 1900;
    }
    
    Leaderboard(const Leaderboard& other)
        : imya(other.imya), vremya(other.vremya), shirina(other.shirina), vysota(other.vysota),
          bomby(other.bomby), day(other.day), month(other.month), year(other.year), win(other.win) {}
    
    void print() const {
        printf("%s: %d сек, %dx%d, %s\n", imya.c_str(), vremya, shirina, vysota, 
               win ? "ПОБЕДА" : "ПРОИГРЫШ");
    }
    
    void saveToFile(const std::string& filename) {
        FILE* file = fopen(filename.c_str(), "a");
        if (file) {
            fprintf(file, "%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    imya.c_str(), vremya, vysota, shirina, bomby,
                    day, month, year, win);
            fclose(file);
        }
    }
    
    Leaderboard& operator=(const Leaderboard& other) {
        if (this != &other) {
            imya = other.imya;
            vremya = other.vremya;
            shirina = other.shirina;
            vysota = other.vysota;
            bomby = other.bomby;
            day = other.day;
            month = other.month;
            year = other.year;
            win = other.win;
        }
        return *this;
    }
};

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

class GameStats {
private:
    int igr_played;
    int igr_won;
    int total_time;
    int best_time;

public:
    GameStats() : igr_played(0), igr_won(0), total_time(0), best_time(0) {}
    
    GameStats(const GameStats& other)
        : igr_played(other.igr_played), igr_won(other.igr_won),
          total_time(other.total_time), best_time(other.best_time) {}
    
    void print() const {
        printf("=== СТАТИСТИКА ===\n");
        printf("Игр сыграно: %d\n", igr_played);
        printf("Побед: %d\n", igr_won);
        printf("Лучшее время: %d сек\n", best_time);
        printf("Среднее время: %.1f сек\n", igr_played > 0 ? (float)total_time / igr_played : 0);
    }
    
    void addGame(bool won, int time) {
        igr_played++;
        if (won) igr_won++;
        total_time += time;
        if (won && (time < best_time || best_time == 0)) {
            best_time = time;
        }
    }
    
    GameStats& operator=(const GameStats& other) {
        if (this != &other) {
            igr_played = other.igr_played;
            igr_won = other.igr_won;
            total_time = other.total_time;
            best_time = other.best_time;
        }
        return *this;
    }
    
    GameStats operator+(const GameStats& other) const {
        GameStats result;
        result.igr_played = igr_played + other.igr_played;
        result.igr_won = igr_won + other.igr_won;
        result.total_time = total_time + other.total_time;
        result.best_time = std::min(best_time ? best_time : INT_MAX, 
                                  other.best_time ? other.best_time : INT_MAX);
        if (result.best_time == INT_MAX) result.best_time = 0;
        return result;
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

class InputHandler {
public:
    void print() const {
        printf("Обработчик ввода пользователя\n");
    }
    
    std::pair<int, int> getCellCoordinates() {
        int x, y;
        printf("Введите координаты X Y: ");
        scanf("%d %d", &x, &y);
        return {x, y};
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

class Validator {
public:
    void print() const {
        printf("Валидатор входных данных\n");
    }
    
    bool isValidCoordinate(int x, int y, int maxX, int maxY) {
        try {
            if (x < 0 || x >= maxX || y < 0 || y >= maxY) {
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

class GameFactory : public Zavod {
private:
    std::map<std::string, std::tuple<int, int, int>> shabloni_poley;
    
public:
    GameFactory(const std::string& spec = "Стандартные", int productivity = 15, int quality = 8)
        : Zavod(spec, productivity, quality) {
        
        shabloni_poley["Легкое"] = std::make_tuple(9, 9, 10);
        shabloni_poley["Среднее"] = std::make_tuple(16, 16, 40);
        shabloni_poley["Сложное"] = std::make_tuple(30, 16, 99);
    }
    
    GameFactory(const GameFactory& other) 
        : Zavod(other.specializaciya, other.proizvoditelnost, other.kachestvo),
          shabloni_poley(other.shabloni_poley) {}
    
    void print() const {
        printf("Фабрика игровых полей: %s\n", specializaciya.c_str());
        printf("Производительность: %d полей/час, Качество: %d/10\n", 
               proizvoditelnost, kachestvo);
    }
    
    void sozdat_igrovoe_pole() override {
        printf("Фабрика '%s' создает игровое поле...\n", specializaciya.c_str());
    }
    
    std::unique_ptr<Board> sozdatPole(const std::string& tip) {
        sozdat_igrovoe_pole();
        
        auto it = shabloni_poley.find(tip);
        if (it != shabloni_poley.end()) {
            auto [w, h, b] = it->second;
            return std::make_unique<Board>(w, h, b);
        }
        return std::make_unique<Board>(9, 9, 10);
    }
    
    GameFactory& operator=(const GameFactory& other) {
        if (this != &other) {
            Zavod::operator=(other);
            shabloni_poley = other.shabloni_poley;
        }
        return *this;
    }
};

class ScoringSystem {
private:
    int base_score;
    int time_bonus;
    int mistake_penalty;
    static int total_games_scored;

public:
    ScoringSystem() : base_score(1000), time_bonus(50), mistake_penalty(100) {}
    
    ScoringSystem(const ScoringSystem& other)
        : base_score(other.base_score), time_bonus(other.time_bonus), mistake_penalty(other.mistake_penalty) {}
    
    void print() const {
        printf("Система подсчета очков\n");
    }
    
    static void incrementGamesScored() {
        total_games_scored++;
    }
    
    static int getTotalGamesScored() {
        return total_games_scored;
    }
    
    int calculateScore(const Player& player, int gameTime) {
        incrementGamesScored();
        int score = base_score;
        score += (3600 - gameTime) / 60 * time_bonus;
        score -= player.getOshibki() * mistake_penalty;
        return score > 0 ? score : 0;
    }
    
    ScoringSystem& operator=(const ScoringSystem& other) {
        if (this != &other) {
            base_score = other.base_score;
            time_bonus = other.time_bonus;
            mistake_penalty = other.mistake_penalty;
        }
        return *this;
    }
};

int ScoringSystem::total_games_scored = 0;

class PlayerSession {
private:
    std::shared_ptr<Player> player;
    GameStats stats;

public:
    PlayerSession(std::shared_ptr<Player> p) : player(p) {}
    
    PlayerSession(const PlayerSession& other) 
        : player(other.player), stats(other.stats) {}
    
    void print() const {
        printf("Сессия игрока: %s\n", player ? player->getImya().c_str() : "нет игрока");
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
        printf("Профиль игрока: %s\n", player ? player->getImya().c_str() : "нет игрока");
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

class GameSave {
private:
    std::string save_name;
    time_t save_time;

public:
    GameSave(const std::string& name) : save_name(name) {
        save_time = time(NULL);
    }
    
    GameSave(const GameSave& other) 
        : save_name(other.save_name + "_copy"), save_time(other.save_time) {}
    
    void print() const {
        printf("Сохранение: %s, время: %s", save_name.c_str(), ctime(&save_time));
    }
    
    GameSave& operator=(const GameSave& other) {
        if (this != &other) {
            save_name = other.save_name + "_assigned";
            save_time = other.save_time;
        }
        return *this;
    }
};

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

class SoundSystem : public Elektropribor {
private:
    std::string nazvanie_ustroystva;
    std::vector<std::string> zvukovye_effekti;
    
public:
    SoundSystem(const std::string& device_name = "Игровая звуковая система", 
                const std::string& device_type = "Колонки", 
                float volume = 70.0f, bool connected = true)
        : Elektropribor(device_type, volume, connected), 
          nazvanie_ustroystva(device_name) {
        
        zvukovye_effekti = {"click", "flag", "bomb", "win", "lose"};
    }
    
    SoundSystem(const SoundSystem& other)
        : Elektropribor(other.tip, other.uroven_gromkosti, other.podklyuchen),
          nazvanie_ustroystva(other.nazvanie_ustroystva + " (копия)"),
          zvukovye_effekti(other.zvukovye_effekti) {}
    
    void print() const {
        printf("Звуковая система: %s\n", nazvanie_ustroystva.c_str());
        info();
    }
    
    void izdat_zvuk(const std::string& zvuk) override {
        if (!podklyuchen) {
            return;
        }
        
        auto it = std::find(zvukovye_effekti.begin(), zvukovye_effekti.end(), zvuk);
        if (it != zvukovye_effekti.end()) {
            if (zvuk == "click") printf("[ЗВУК] Клик\n");
            else if (zvuk == "flag") printf("[ЗВУК] Флаг\n");
            else if (zvuk == "bomb") printf("[ЗВУК] ВЗРЫВ!\n");
            else if (zvuk == "win") printf("[ЗВУК] ПОБЕДА!\n");
            else if (zvuk == "lose") printf("[ЗВУК] Поражение\n");
        }
    }
    
    SoundSystem& operator=(const SoundSystem& other) {
        if (this != &other) {
            Elektropribor::operator=(other);
            nazvanie_ustroystva = other.nazvanie_ustroystva;
            zvukovye_effekti = other.zvukovye_effekti;
        }
        return *this;
    }
    
    bool operator==(const SoundSystem& other) const {
        return nazvanie_ustroystva == other.nazvanie_ustroystva && 
               tip == other.tip;
    }
};

class Theme {
private:
    std::string name;
    std::string cell_closed;
    std::string cell_open;
    std::string bomb;

public:
    Theme(const std::string& themeName = "classic") : name(themeName) {
        if (themeName == "classic") {
            cell_closed = ".";
            cell_open = " ";
            bomb = "*";
        } else if (themeName == "modern") {
            cell_closed = "■";
            cell_open = "□";
            bomb = "💣";
        }
    }
    
    Theme(const Theme& other)
        : name(other.name), cell_closed(other.cell_closed), 
          cell_open(other.cell_open), bomb(other.bomb) {}
    
    void print() const {
        printf("Тема: %s\n", name.c_str());
    }
    
    std::string getFullInfo() const {
        return "Тема: " + name;
    }
    
    bool contains(const std::string& substr) const {
        return name.find(substr) != std::string::npos;
    }
    
    Theme& operator=(const Theme& other) {
        if (this != &other) {
            name = other.name;
            cell_closed = other.cell_closed;
            cell_open = other.cell_open;
            bomb = other.bomb;
        }
        return *this;
    }
    
    bool operator==(const Theme& other) const {
        return name == other.name;
    }
};

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

class GameAnalyzer {
public:
    void print() const {
        printf("Анализатор игрового процесса\n");
    }
    
    void analyzeBoard(const Board& board) {
        printf("Анализ поля: бомб %d\n", board.getVsegoBomb());
    }
    
    GameAnalyzer& operator=(const GameAnalyzer& other) {
        return *this;
    }
};

class HighScore : public Rekordsmen {
private:
    std::string imya_igroka;
    int rezultat;
    std::string tip_rezultata;
    
public:
    HighScore(const std::string& player_name, int result, 
              const std::string& result_type = "Время",
              const std::string& category = "Время", 
              const std::string& difficulty = "Средний", int year = 2024)
        : Rekordsmen(category, difficulty, year),
          imya_igroka(player_name), rezultat(result), tip_rezultata(result_type) {}
    
    HighScore(const HighScore& other) 
        : Rekordsmen(other.kategoriya, other.uroven_slozhnosti, other.god_ustanovki),
          imya_igroka(other.imya_igroka + " (копия)"),
          rezultat(other.rezultat),
          tip_rezultata(other.tip_rezultata) {}
    
    void print() const {
        printf("Рекорд: %s - %d", imya_igroka.c_str(), rezultat);
        if (tip_rezultata == "Время") printf(" сек");
        printf(", Сложность: %s\n", uroven_slozhnosti.c_str());
    }
    
    void zaregistrirovat_rekord() override {
        printf("Рекорд зарегистрирован: %s\n", imya_igroka.c_str());
    }
    
    friend std::ostream& operator<<(std::ostream& os, const HighScore& hs);
    
    bool operator>(const HighScore& other) const {
        if (tip_rezultata != other.tip_rezultata) return false;
        
        if (tip_rezultata == "Время") {
            return rezultat < other.rezultat;
        } else {
            return rezultat > other.rezultat;
        }
    }
    
    HighScore& operator=(const HighScore& other) {
        if (this != &other) {
            Rekordsmen::operator=(other);
            imya_igroka = other.imya_igroka;
            rezultat = other.rezultat;
            tip_rezultata = other.tip_rezultata;
        }
        return *this;
    }
    
    int getRezultat() const { return rezultat; }
};

std::ostream& operator<<(std::ostream& os, const HighScore& hs) {
    os << hs.imya_igroka << ": " << hs.rezultat;
    if (hs.tip_rezultata == "Время") os << " сек";
    return os;
}

class HighScoreManager {
private:
    std::vector<std::shared_ptr<HighScore>> high_scores;

public:
    void print() const {
        printf("=== ТАБЛИЦА РЕКОРДОВ ===\n");
        for (size_t i = 0; i < high_scores.size(); i++) {
            printf("%zu. ", i + 1);
            if (high_scores[i]) high_scores[i]->print();
        }
    }
    
    void addScore(std::shared_ptr<HighScore> score) {
        high_scores.push_back(score);
        std::sort(high_scores.begin(), high_scores.end(), 
                  [](const std::shared_ptr<HighScore>& a, const std::shared_ptr<HighScore>& b) {
                      return a && b && a->getRezultat() > b->getRezultat();
                  });
    }
    
    HighScoreManager& operator=(const HighScoreManager& other) {
        if (this != &other) {
            high_scores = other.high_scores;
        }
        return *this;
    }
};

class HintSystem {
private:
    int hints_available;

public:
    HintSystem() : hints_available(3) {}
    
    HintSystem(const HintSystem& other) : hints_available(other.hints_available) {}
    
    void print() const {
        printf("Система подсказок, доступно подсказок: %d\n", hints_available);
    }
    
    bool useHint() {
        if (hints_available > 0) {
            hints_available--;
            return true;
        }
        return false;
    }
    
    HintSystem& operator=(const HintSystem& other) {
        if (this != &other) {
            hints_available = other.hints_available;
        }
        return *this;
    }
    
    HintSystem& operator--() {
        if (hints_available > 0) hints_available--;
        return *this;
    }
    
    HintSystem operator--(int) {
        HintSystem temp = *this;
        if (hints_available > 0) hints_available--;
        return temp;
    }
};

class GameHistory {
private:
    std::vector<std::string> moves;

public:
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

class MoveCounter : public Schitatel {
private:
    int vsego_hodov;
    int bezopasnye_hody;
    int flag_hody;
    int bomb_hody;
    time_t vremya_nachala;
    
public:
    MoveCounter(const std::string& count_type = "Ходы сапёра", int limit = 200, bool automatic = true,
                int total = 0, int safe = 0, int flag = 0, int bomb = 0)
        : Schitatel(count_type, limit, automatic),
          vsego_hodov(total), bezopasnye_hody(safe), flag_hody(flag), bomb_hody(bomb) {
        vremya_nachala = time(NULL);
    }
    
    MoveCounter(const MoveCounter& other) 
        : Schitatel(other.tip_otscheta, other.predel_otscheta, other.avtomaticheskiy),
          vsego_hodov(other.vsego_hodov), bezopasnye_hody(other.bezopasnye_hody),
          flag_hody(other.flag_hody), bomb_hody(other.bomb_hody),
          vremya_nachala(other.vremya_nachala) {}
    
    void print() const {
        printf("=== СТАТИСТИКА ХОДОВ ===\n");
        printf("Тип отсчета: %s\n", tip_otscheta.c_str());
        printf("Всего ходов: %d/%d\n", vsego_hodov, predel_otscheta);
        printf("Безопасные: %d, Флаги: %d, Бомбы: %d\n", 
               bezopasnye_hody, flag_hody, bomb_hody);
    }
    
    void nachat_otschet() override {
        vremya_nachala = time(NULL);
    }
    
    void dobavit_bezopasniy_hod() {
        if (!avtomaticheskiy) return;
        
        if (dostignut_predel(vsego_hodov)) return;
        
        vsego_hodov++;
        bezopasnye_hody++;
    }
    
    void dobavit_flag_hod() {
        if (dostignut_predel(vsego_hodov)) return;
        
        vsego_hodov++;
        flag_hody++;
    }
    
    void dobavit_bomb_hod() {
        if (dostignut_predel(vsego_hodov)) return;
        
        vsego_hodov++;
        bomb_hody++;
    }
    
    MoveCounter& operator++() {
        dobavit_bezopasniy_hod();
        return *this;
    }
    
    MoveCounter operator++(int) {
        MoveCounter temp = *this;
        dobavit_bezopasniy_hod();
        return temp;
    }
    
    MoveCounter& operator+=(int hodi) {
        for (int i = 0; i < hodi; i++) {
            dobavit_bezopasniy_hod();
        }
        return *this;
    }
    
    MoveCounter& operator=(const MoveCounter& other) {
        if (this != &other) {
            Schitatel::operator=(other);
            vsego_hodov = other.vsego_hodov;
            bezopasnye_hody = other.bezopasnye_hody;
            flag_hody = other.flag_hody;
            bomb_hody = other.bomb_hody;
            vremya_nachala = other.vremya_nachala;
        }
        return *this;
    }
};

void demonstrateFullGame() {
    printf("=== ПОЛНАЯ ДЕМОНСТРАЦИЯ САПЁРА ===\n\n");
    
    try {
        // 1. Создание игровых объектов
        printf("1. СОЗДАНИЕ ОБЪЕКТОВ:\n");
        auto player = std::make_shared<Player>("Алексей Сапёров");
        auto board = std::make_unique<Board>(8, 8, 10);
        auto game = std::make_unique<Game>(std::move(board), player);
        
        player->print();
        game->print();
        
        // 2. Координаты с географией
        printf("\n2. ГЕОГРАФИЯ КООРДИНАТ:\n");
        Coordinate coord1(2, 3, "Центральный сектор", 3);
        coord1.print();
        coord1.issledovat_territoriyu();
        coord1.otsenit_opasnost_dlya_sapera();
        
        Coordinate coord2(7, 2, "Пограничная зона", 7, true);
        if (coord2.opasniy_region()) {
            printf("⚠️ Опасный регион!\n");
        }
        
        printf("Всего координат: %d\n", Coordinate::getTotalCoordinates());
        
        // 3. Звуковая система
        printf("\n3. ЗВУКОВАЯ СИСТЕМА:\n");
        SoundSystem sound("Сапёр Аудио", "Наушники", 80.0f);
        sound.print();
        sound.izdat_zvuk("click");
        sound.izdat_zvuk("flag");
        sound.izdat_zvuk("bomb");
        
        // 4. Фабрика игр
        printf("\n4. ФАБРИКА ИГРОВЫХ ПОЛЕЙ:\n");
        GameFactory factory("Экспертные поля", 20, 9);
        factory.print();
        factory.sozdat_igrovoe_pole();
        
        auto pole = factory.sozdatPole("Среднее");
        if (pole) {
            printf("Создано поле: %dx%d\n", pole->getShirina(), pole->getVysota());
        }
        
        // 5. Счетчик ходов
        printf("\n5. СТАТИСТИКА ХОДОВ:\n");
        MoveCounter counter("Ходы сапёра", 50);
        counter.nachat_otschet();
        counter.dobavit_bezopasniy_hod();
        counter.dobavit_flag_hod();
        counter.dobavit_bomb_hod();
        counter.print();
        
        // Использование операторов
        ++counter;
        counter += 2;
        counter.print();
        
        // 6. Рекорды
        printf("\n6. РЕКОРДЫ:\n");
        HighScore record1("Алексей", 45, "Время", "Скорость", "Сложный", 2024);
        record1.print();
        record1.zaregistrirovat_rekord();
        
        HighScore record2("Мария", 120, "Время", "Скорость", "Экстремальный", 2023);
        record2.print();
        
        if (record1 > record2) {
            printf("%s показал лучший результат!\n", record1.getKategoriya().c_str());
        }
        
        std::cout << "Рекорд: " << record1 << std::endl;
        
        // 7. Все остальные классы
        printf("\n7. ВСЕ 35 КЛАССОВ:\n");
        
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
        hsManager.addScore(std::make_shared<HighScore>("Игрок", 1000, "Очки"));
        
        HintSystem hints;
        hints.print();
        
        // 8. Копирование объектов
        printf("\n8. КОПИРОВАНИЕ ОБЪЕКТОВ:\n");
        Coordinate coordCopy = coord1;
        coordCopy.print();
        
        Player playerCopy(*player);
        playerCopy.print();
        
        MoveCounter counterCopy(counter);
        counterCopy.print();
        
        // 9. Работа с исключениями
        printf("\n9. ОБРАБОТКА ИСКЛЮЧЕНИЙ:\n");
        try {
            if (!validator.isValidCoordinate(10, 10, 5, 5)) {
                throw std::runtime_error("Тестовое исключение");
            }
        }
        catch (const std::exception& e) {
            printf("Исключение перехвачено: %s\n", e.what());
        }
        
        // 10. Перегрузка операторов
        printf("\n10. ПЕРЕГРУЗКА ОПЕРАТОРОВ:\n");
        Coordinate c1(1, 2);
        Coordinate c2(3, 4);
        Coordinate c3 = c1 + c2;
        std::cout << "c1 + c2 = " << c3 << std::endl;
        
        Player p1("А");
        Player p2("Б");
        p1 += 100;
        ++p1;
        std::cout << "p1: " << p1 << std::endl;
        
        // 11. Дружественные функции
        printf("\n11. ДРУЖЕСТВЕННЫЕ ФУНКЦИИ:\n");
        obmenyat_koordinati(c1, c2);
        std::cout << "После обмена: c1 = " << c1 << ", c2 = " << c2 << std::endl;
        
        // 12. Статические члены
        printf("\n12. СТАТИЧЕСКИЕ ЧЛЕНЫ:\n");
        printf("Всего координат: %d\n", Coordinate::getTotalCoordinates());
        printf("Всего оцененных игр: %d\n", ScoringSystem::getTotalGamesScored());
        
        // 13. Работа со строками
        printf("\n13. РАБОТА СО СТРОКАМИ:\n");
        std::string str = "Игрок: ";
        str += player->getImya();
        str += " имеет ";
        str += std::to_string(player->getOshibki());
        str += " ошибок";
        printf("%s\n", str.c_str());
        
        // 14. Использование this
        printf("\n14. ИСПОЛЬЗОВАНИЕ this:\n");
        player->setImya("Новое имя");
        player->print();
        
        // 15. Интеграция всех систем
        printf("\n15. ИНТЕГРАЦИЯ ВСЕХ СИСТЕМ:\n");
        printf("Игровая сессия сапёра включает:\n");
        printf("- Исследование координат с географическими данными\n");
        printf("- Звуковые эффекты для каждого действия\n");
        printf("- Статистику ходов и эффективности\n");
        printf("- Запись рекордов\n");
        printf("- Все вспомогательные системы\n");
        
        // Симуляция игрового процесса
        printf("\n--- Симуляция игрового процесса ---\n");
        sound.izdat_zvuk("click");
        counter.dobavit_bezopasniy_hod();
        coord1.issledovat_territoriyu();
        
        sound.izdat_zvuk("flag");
        counter.dobavit_flag_hod();
        
        sound.izdat_zvuk("bomb");
        counter.dobavit_bomb_hod();
        
        printf("Итоговая статистика:\n");
        counter.print();
        
        if (counter.dostignut_predel(counter.getPredelOtscheta())) {
            printf("⚠️ Достигнут лимит ходов!\n");
        }
        
    }
    catch (const std::exception& e) {
        printf("Ошибка в демонстрации: %s\n", e.what());
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    printf("=== САПЁР НА C++ ===\n");
    printf("35 классов с тематическим наследованием\n");
    printf("Смарт-указатели, перегрузка операторов, исключения\n\n");
    
    demonstrateFullGame();
    
    printf("\n=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
    
    return 0;
}