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
#include <array>
#include <list>
#include <span>
#include <variant>

template<typename T>
concept HasUrovenOpasnosti = requires(T t) {
    { t.getUrovenOpasnosti() } -> std::convertible_to<int>;
};

template<typename T>
concept HasGetTip = requires(T t) {
    { t.getTip() } -> std::convertible_to<std::string>;
};

template<typename T>
concept HasNazvanie = requires(T t) {
    { t.getNazvanie() } -> std::convertible_to<std::string>;
};

template<typename T>
concept HasRezultat = requires(T t) {
    { t.getRezultat() } -> std::convertible_to<int>;
};

template<typename T>
concept HasValue = requires(T t) {
    { t.getValue() } -> std::convertible_to<int>;
};

template<typename T>
double calculateAverageUroven(const std::vector<T>& items) requires HasUrovenOpasnosti<T> {
    if (items.empty()) return 0.0;
    int sum = 0;
    for (const auto& item : items) {
        sum += item.getUrovenOpasnosti();
    }
    return static_cast<double>(sum) / items.size();
}

template<typename T>
std::string findMostCommonTip(const std::vector<T>& items) requires HasGetTip<T> {
    if (items.empty()) return "";
    std::map<std::string, int> tipCount;
    for (const auto& item : items) {
        tipCount[item.getTip()]++;
    }
    auto maxIt = std::max_element(tipCount.begin(), tipCount.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });
    return maxIt != tipCount.end() ? maxIt->first : "";
}

template<typename T>
void sortByNazvanie(std::vector<T>& items) requires HasNazvanie<T> {
    std::sort(items.begin(), items.end(),
        [](const T& a, const T& b) { return a.getNazvanie() < b.getNazvanie(); });
}

template<typename T>
T* findBestRezultat(std::vector<T>& items) requires HasRezultat<T> {
    if (items.empty()) return nullptr;
    auto it = std::max_element(items.begin(), items.end(),
        [](const T& a, const T& b) { return a.getRezultat() < b.getRezultat(); });
    return it != items.end() ? &(*it) : nullptr;
}

template<typename T>
int calculateTotalValue(const std::vector<T>& items) requires HasValue<T> {
    int total = 0;
    for (const auto& item : items) {
        total += item.getValue();
    }
    return total;
}
class AbstractGeografiya {
protected:
    std::string nazvanie_regiona;
    int uroven_opasnosti;

public:
    AbstractGeografiya(const std::string& region = "Неизвестно", int danger = 0)
        : nazvanie_regiona(region), uroven_opasnosti(danger) {}

    virtual ~AbstractGeografiya() = default;

    virtual void issledovat_territoriyu() = 0;
    virtual void pokazat_info() const = 0;

    std::string getNazvanieRegiona() const { return nazvanie_regiona; }
    int getUrovenOpasnosti() const { return uroven_opasnosti; }
    std::string getNazvanie() const { return nazvanie_regiona; }

    void izmenit_opasnost(int novaya_opasnost) {
        if (novaya_opasnost >= 0 && novaya_opasnost <= 10) {
            uroven_opasnosti = novaya_opasnost;
        }
    }
};

class AbstractElektropribor {
protected:
    std::string tip_ustroystva;

public:
    AbstractElektropribor(const std::string& tip = "Устройство")
        : tip_ustroystva(tip) {}

    virtual ~AbstractElektropribor() = default;

    virtual void vkluchit() = 0;
    virtual void izdat_zvuk(const std::string& zvuk) = 0;

    std::string getTipUstroystva() const { return tip_ustroystva; }
    std::string getTip() const { return tip_ustroystva; }
};

class AbstractZavod {
protected:
    std::string nazvanie_zavoda;
public:
    AbstractZavod(const std::string& nazvanie = "Завод")
        : nazvanie_zavoda(nazvanie) {}

    virtual ~AbstractZavod() = default;

    virtual void zapustit_proizvodstvo() = 0;
    virtual void ostanovit_proizvodstvo() = 0;

    std::string getNazvanieZavoda() const { return nazvanie_zavoda; }
    std::string getNazvanie() const { return nazvanie_zavoda; }
};

class AbstractSchitatel {
protected:
    std::string tip_schetchika;

public:
    AbstractSchitatel(const std::string& tip = "Счетчик")
        : tip_schetchika(tip) {}

    virtual ~AbstractSchitatel() = default;

    virtual void sbrosit() = 0;
    virtual void pokazat_tekushee() const = 0;

    std::string getTipSchetchika() const { return tip_schetchika; }
    int getValue() const { return 0; }
};

class AbstractRekordsmen {
protected:
    std::string kategoriya_sorevnovaniya;
    int god_ustanovki_rekorda;

public:
    AbstractRekordsmen(const std::string& kategoriya = "Категория", int god = 2024)
        : kategoriya_sorevnovaniya(kategoriya), god_ustanovki_rekorda(god) {}

    virtual ~AbstractRekordsmen() = default;

    virtual void zaregistrirovat_pobedu() = 0;
    virtual void pokazat_rezultat() const = 0;

    std::string getKategoriyaSorevnovaniya() const { return kategoriya_sorevnovaniya; }
    int getGodUstanovkiRekorda() const { return god_ustanovki_rekorda; }
    int getRezultat() const { return god_ustanovki_rekorda; }
};

class Geografiya : public AbstractGeografiya {
protected:
    bool razvedeno;

public:
    Geografiya(const std::string& region = "Неизвестно", int danger = 0, bool explored = false)
        : AbstractGeografiya(region, danger), razvedeno(explored) {}

    virtual ~Geografiya() = default;

    void issledovat_territoriyu() override {
        if (!razvedeno) {
            razvedeno = true;
        }
    }

    void pokazat_info() const override {
        printf("Регион: %s, Опасность: %d\n", nazvanie_regiona.c_str(), uroven_opasnosti);
    }

    bool getRazvedeno() const { return razvedeno; }
};

class Elektropribor : public AbstractElektropribor {
protected:
    bool vklyuchen;

public:
    Elektropribor(const std::string& tip = "Устройство", bool enabled = false)
        : AbstractElektropribor(tip), vklyuchen(enabled) {}

    virtual ~Elektropribor() = default;

    void vkluchit() override {
        vklyuchen = true;
    }

    void izdat_zvuk(const std::string& zvuk) override {
        if (vklyuchen) {
            printf("[%s] %s\n", tip_ustroystva.c_str(), zvuk.c_str());
        }
    }

    bool getVklyuchen() const { return vklyuchen; }
};

class Zavod : public AbstractZavod {
protected:
    bool rabotaet;

public:
    Zavod(const std::string& nazvanie = "Завод", bool working = false)
        : AbstractZavod(nazvanie), rabotaet(working) {}

    virtual ~Zavod() = default;

    void zapustit_proizvodstvo() override {
        rabotaet = true;
    }

    void ostanovit_proizvodstvo() override {
        rabotaet = false;
    }

    bool getRabotaet() const { return rabotaet; }
};

class Schitatel : public AbstractSchitatel {
protected:
    int tekushee_znachenie;

public:
    Schitatel(const std::string& tip = "Счетчик", int current = 0)
        : AbstractSchitatel(tip), tekushee_znachenie(current) {}

    virtual ~Schitatel() = default;

    void sbrosit() override {
        tekushee_znachenie = 0;
    }

    void pokazat_tekushee() const override {
        printf("Счетчик %s: %d\n", tip_schetchika.c_str(), tekushee_znachenie);
    }

    int getTekusheeZnachenie() const { return tekushee_znachenie; }
    int getValue() const { return tekushee_znachenie; }
};

class Rekordsmen : public AbstractRekordsmen {
protected:
    std::string imya_uchastnika;

public:
    Rekordsmen(const std::string& kategoriya = "Категория", int god = 2024,
        const std::string& imya = "Участник")
        : AbstractRekordsmen(kategoriya, god), imya_uchastnika(imya) {}

    virtual ~Rekordsmen() = default;

    void zaregistrirovat_pobedu() override {
        printf("Победа зарегистрирована для %s\n", imya_uchastnika.c_str());
    }

    void pokazat_rezultat() const override {
        printf("Рекорд: %s, Участник: %s\n", kategoriya_sorevnovaniya.c_str(), imya_uchastnika.c_str());
    }

    std::string getImyaUchastnika() const { return imya_uchastnika; }
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
        printf("Координата [%d,%d]: ", x, y);
        pokazat_info();
    }

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    bool isValid(int maxX, int maxY) const {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }

    static int getTotalCoordinates() {
        return totalCoordinates;
    }
};

int Coordinate::totalCoordinates = 0;

class Cell {
private:
    bool bomba;
    bool otkrita;
    bool flag;
    int bomby_vokrug;
    std::shared_ptr<Coordinate> koordinata;

public:
    Cell(int x = 0, int y = 0) : bomba(false), otkrita(false), flag(false), bomby_vokrug(0) {
        koordinata = std::make_shared<Coordinate>(x, y);
    }

    void print() const {
        printf("Клетка ");
        koordinata->print();
        printf("Состояние: ");
        if (otkrita) {
            if (bomba) printf("💣 БОМБА");
            else printf("📊 %d бомб вокруг", bomby_vokrug);
        }
        else if (flag) {
            printf("🚩 ФЛАГ");
        }
        else {
            printf("⬜ ЗАКРЫТА");
        }
        printf("\n");
    }

    void otkrit() {
        if (!otkrita) {
            otkrita = true;
            flag = false;
        }
    }

    void pereklyuchit_flag() {
        if (!otkrita) {
            flag = !flag;
        }
    }

    void ustanovit_bombu() {
        bomba = true;
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
        : shirina(width), vysota(height), vsego_bomb(bombs), bezopasnye_kletki(width* height - bombs) {
        for (int y = 0; y < vysota; y++) {
            for (int x = 0; x < shirina; x++) {
                kletki.emplace_back(x, y);
            }
        }
    }

    void print() const {
        printf("   ");
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
                    }
                    else {
                        printf(" %d ", kletka.getBombyVokrug());
                    }
                }
                else if (kletka.getFlag()) {
                    printf(" F ");
                }
                else {
                    printf(" . ");
                }
            }
            printf("\n");
        }
    }

    Cell* getKletka(int x, int y) {
        if (x >= 0 && x < shirina && y >= 0 && y < vysota) {
            return &kletki[y * shirina + x];
        }
        return nullptr;
    }

    int getShirina() const { return shirina; }
    int getVysota() const { return vysota; }
    int getVsegoBomb() const { return vsego_bomb; }
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

    void print() const {
        printf("Игрок: %s\n", imya.c_str());
        printf("Время: %d сек, Открыто: %d, Ошибок: %d\n",
            vremya_igry, otkrytye_kletki, oshibki);
    }

    void dobavit_oshibku() { oshibki++; }
    void dobavit_otkrytuyu_kletku() { otkrytye_kletki++; }

    std::string getImya() const { return imya; }
    int getVremyaIgry() const { return vremya_igry; }
    int getOtkrytyeKletki() const { return otkrytye_kletki; }
    int getOshibki() const { return oshibki; }
    int getLuchsheeVremya() const { return luchshee_vremya; }

    void setVremyaIgry(int time) { vremya_igry = time; }
    void setImya(const std::string& newName) { imya = newName; }
};

class Timer {
private:
    time_t start_time;
    time_t pause_time;
    bool is_running;

public:
    Timer() : start_time(0), pause_time(0), is_running(false) {}

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

    bool isRunning() const { return is_running; }
};

class Game : public AbstractGeografiya, public AbstractZavod {
private:
    std::unique_ptr<Board> pole;
    std::shared_ptr<Player> igrok;
    int sostoyanie;
    std::unique_ptr<Timer> taymer;

public:
    Game(std::unique_ptr<Board> board, std::shared_ptr<Player> player,
        const std::string& region = "Игровая зона")
        : AbstractGeografiya(region), AbstractZavod("Игровая фабрика"),
        sostoyanie(0) {
        pole = std::move(board);
        igrok = player;
        taymer = std::make_unique<Timer>();
        taymer->start();
    }

    void print() const {
        printf("=== СОСТОЯНИЕ ИГРЫ ===\n");
        printf("Регион: %s\n", nazvanie_regiona.c_str());
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

    void issledovat_territoriyu() override {
        printf("Исследование игровой территории: %s\n", nazvanie_regiona.c_str());
    }

    void pokazat_info() const override {
        printf("Игра в регионе: %s, Опасность: %d\n",
            nazvanie_regiona.c_str(), uroven_opasnosti);
    }

    void zapustit_proizvodstvo() override {
        printf("Запуск производства игр: %s\n", nazvanie_zavoda.c_str());
    }

    void ostanovit_proizvodstvo() override {
        printf("Остановка производства игр: %s\n", nazvanie_zavoda.c_str());
    }

    void winGame() {
        sostoyanie = 1;
        if (igrok) {
            int gameTime = getGameTime();
            igrok->setVremyaIgry(gameTime);
            if (gameTime < igrok->getLuchsheeVremya() || igrok->getLuchsheeVremya() == 0) {
                igrok->setVremyaIgry(gameTime);
            }
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
            igrok->dobavit_otkrytuyu_kletku();

            if (kletka->getBomba()) {
                loseGame();
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
        case 0: return std::unique_ptr<Board>(new Board(9, 9, 10));
        case 1: return std::unique_ptr<Board>(new Board(16, 16, 40));
        case 2: return std::unique_ptr<Board>(new Board(30, 16, 99));
        default: return std::unique_ptr<Board>(new Board(9, 9, 10));
        }
    }

    int getAutoBombs() const { return auto_bombs; }
    int getZvuki() const { return zvuki; }
    int getSlozhnost() const { return slozhnost; }

    void setSlozhnost(int level) { slozhnost = level; }
};

class Logger {
private:
    std::string filename;
    FILE* file;

public:
    Logger(const std::string& fname) : filename(fname) {
        file = fopen(filename.c_str(), "a");
        if (!file) {
            printf("Ошибка открытия файла: %s\n", filename.c_str());
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
            fprintf(file, "%s\n", message.c_str());
            fflush(file);
        }
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

    Game* getCurrentGame() const { return currentGame.get(); }
};

class Validator {
public:
    void print() const {
        printf("Валидатор входных данных\n");
    }

    bool isValidCoordinate(int x, int y, int maxX, int maxY) const {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }

    bool isValidName(const std::string& name) const {
        return !name.empty() && name.length() <= 49;
    }
};

class GameFactory : public AbstractZavod {
private:
    std::map<std::string, std::tuple<int, int, int>> shabloni_poley;

public:
    GameFactory(const std::string& nazvanie = "Фабрика игр")
        : AbstractZavod(nazvanie) {

        shabloni_poley["Легкое"] = std::make_tuple(9, 9, 10);
        shabloni_poley["Среднее"] = std::make_tuple(16, 16, 40);
        shabloni_poley["Сложное"] = std::make_tuple(30, 16, 99);
    }

    void print() const {
        printf("Фабрика игровых полей: %s\n", nazvanie_zavoda.c_str());
    }

    void zapustit_proizvodstvo() override {
        printf("Фабрика '%s' запускает производство...\n", nazvanie_zavoda.c_str());
    }

    void ostanovit_proizvodstvo() override {
        printf("Фабрика '%s' останавливает производство...\n", nazvanie_zavoda.c_str());
    }

    std::unique_ptr<Board> sozdatPole(const std::string& tip) {
        zapustit_proizvodstvo();

        auto it = shabloni_poley.find(tip);
        if (it != shabloni_poley.end()) {
            int width = std::get<0>(it->second);
            int height = std::get<1>(it->second);
            int bombs = std::get<2>(it->second);

            return std::unique_ptr<Board>(new Board(width, height, bombs));
        }
        return std::unique_ptr<Board>(new Board(9, 9, 10));
    }
};

class ScoringSystem : public AbstractSchitatel {
private:
    int base_score;
    int time_bonus;
    int mistake_penalty;

public:
    ScoringSystem()
        : AbstractSchitatel("Система очков"), base_score(1000), time_bonus(50), mistake_penalty(100) {}

    void print() const {
        printf("Система подсчета очков: %s\n", tip_schetchika.c_str());
    }

    void sbrosit() override {
        printf("Сброс системы очков\n");
    }

    void pokazat_tekushee() const override {
        printf("Базовая система очков активирована\n");
    }

    int calculateScore(const Player& player, int gameTime) const {
        int score = base_score;
        score += (3600 - gameTime) / 60 * time_bonus;
        score -= player.getOshibki() * mistake_penalty;
        return score > 0 ? score : 0;
    }
};

class PlayerSession {
private:
    std::shared_ptr<Player> player;
    GameStats stats;

public:
    PlayerSession(std::shared_ptr<Player> p) : player(p) {}

    void print() const {
        printf("Сессия игрока: %s\n", player ? player->getImya().c_str() : "нет игрока");
        stats.print();
    }

    void addGameResult(bool won, int time) {
        stats.addGame(won, time);
    }
};

class Notifier : public AbstractElektropribor {
public:
    Notifier() : AbstractElektropribor("Уведомитель") {}

    void print() const {
        printf("Система уведомлений: %s\n", tip_ustroystva.c_str());
    }

    void vkluchit() override {
        printf("Уведомления включены\n");
    }

    void izdat_zvuk(const std::string& zvuk) override {
        printf("[Уведомление] %s\n", zvuk.c_str());
    }

    void showWinMessage() {
        izdat_zvuk("🎉 ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ! 🎉");
    }

    void showLoseMessage() {
        izdat_zvuk("💥 ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ! 💥");
    }
};

class Difficulty : public AbstractGeografiya {
private:
    int width;
    int height;
    int bombs;

public:
    Difficulty(const std::string& level, int w, int h, int b)
        : AbstractGeografiya("Уровень " + level, b / 10), width(w), height(h), bombs(b) {}

    void print() const {
        printf("Уровень сложности: %s (%dx%d, %d бомб)\n",
            nazvanie_regiona.c_str(), width, height, bombs);
    }

    void issledovat_territoriyu() override {
        printf("Исследование уровня сложности: %s\n", nazvanie_regiona.c_str());
    }

    void pokazat_info() const override {
        printf("Сложность: %s, Бомб: %d, Опасность: %d/10\n",
            nazvanie_regiona.c_str(), bombs, uroven_opasnosti);
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getBombs() const { return bombs; }
};

class PlayerProfile {
private:
    std::shared_ptr<Player> player;
    std::string avatar;
    int level;

public:
    PlayerProfile(std::shared_ptr<Player> p, const std::string& av = "default")
        : player(p), avatar(av), level(1) {}

    void print() const {
        printf("Профиль игрока: %s\n", player ? player->getImya().c_str() : "нет игрока");
        printf("Аватар: %s, Уровень: %d\n", avatar.c_str(), level);
    }

    void levelUp() {
        level++;
        printf("%s повысил уровень до %d!\n", player->getImya().c_str(), level);
    }
};

class Achievement : public AbstractRekordsmen {
private:
    bool unlocked;
    std::string description;

public:
    Achievement(const std::string& category, const std::string& desc, int year = 2024)
        : AbstractRekordsmen(category, year), unlocked(false), description(desc) {}

    void print() const {
        printf("Достижение: %s - %s [%s]\n",
            kategoriya_sorevnovaniya.c_str(), description.c_str(),
            unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }

    void zaregistrirovat_pobedu() override {
        unlocked = true;
        printf("Достижение разблокировано: %s\n", kategoriya_sorevnovaniya.c_str());
    }

    void pokazat_rezultat() const override {
        printf("Рекорд в категории '%s': %s\n",
            kategoriya_sorevnovaniya.c_str(), description.c_str());
    }

    bool isUnlocked() const { return unlocked; }
    std::string getDescription() const { return description; }
};

class AchievementSystem {
private:
    std::vector<Achievement> achievements;

public:
    AchievementSystem() {
        achievements.emplace_back("Новичок", "Сыграйте первую игру");
        achievements.emplace_back("Сапер", "Выиграйте 10 игр");
        achievements.emplace_back("Эксперт", "Выиграйте игру на сложном уровне");
        achievements.emplace_back("Скоростник", "Победить менее чем за 60 секунд");
        achievements.emplace_back("Аккуратный", "Победить без ошибок");
    }

    void print() const {
        printf("=== СИСТЕМА ДОСТИЖЕНИЙ ===\n");
        for (const auto& achievement : achievements) {
            achievement.print();
        }
    }

    void checkAndUnlock(int gamesPlayed, int gamesWon, int bestTime, int difficulty) {
        for (auto& achievement : achievements) {
            if (!achievement.isUnlocked()) {
                if (achievement.getKategoriyaSorevnovaniya() == "Новичок" && gamesPlayed >= 1) {
                    achievement.zaregistrirovat_pobedu();
                }
                else if (achievement.getKategoriyaSorevnovaniya() == "Сапер" && gamesWon >= 10) {
                    achievement.zaregistrirovat_pobedu();
                }
                else if (achievement.getKategoriyaSorevnovaniya() == "Эксперт" && difficulty >= 2) {
                    achievement.zaregistrirovat_pobedu();
                }
            }
        }
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

    void print() const {
        printf("Сохранение: %s, время: %s", save_name.c_str(), ctime(&save_time));
    }

    std::string getName() const { return save_name; }
    time_t getSaveTime() const { return save_time; }
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
        printf("Создано сохранение: %s\n", name.c_str());
    }

    bool loadSave(const std::string& name) {
        for (const auto& save : saves) {
            if (save && save->getName() == name) {
                printf("Загружено сохранение: %s\n", name.c_str());
                return true;
            }
        }
        printf("Сохранение не найдено: %s\n", name.c_str());
        return false;
    }
};

class SoundSystem : public AbstractElektropribor {
private:
    std::string nazvanie_ustroystva;
    std::vector<std::string> zvukovye_effekti;

public:
    SoundSystem(const std::string& device_name = "Игровая звуковая система")
        : AbstractElektropribor("Звуковая система"), nazvanie_ustroystva(device_name) {

        zvukovye_effekti = { "click", "flag", "bomb", "win", "lose" };
    }

    void print() const {
        printf("Звуковая система: %s (%s)\n", nazvanie_ustroystva.c_str(), tip_ustroystva.c_str());
    }

    void vkluchit() override {
        printf("Звуковая система включена\n");
    }

    void izdat_zvuk(const std::string& zvuk) override {
        auto it = std::find(zvukovye_effekti.begin(), zvukovye_effekti.end(), zvuk);
        if (it != zvukovye_effekti.end()) {
            if (zvuk == "click") printf("[ЗВУК] Клик\n");
            else if (zvuk == "flag") printf("[ЗВУК] Флаг\n");
            else if (zvuk == "bomb") printf("[ЗВУК] ВЗРЫВ!\n");
            else if (zvuk == "win") printf("[ЗВУК] ПОБЕДА!\n");
            else if (zvuk == "lose") printf("[ЗВУК] Поражение\n");
        }
        else {
            printf("[ЗВУК] %s\n", zvuk.c_str());
        }
    }

    void playClick() { izdat_zvuk("click"); }
    void playFlag() { izdat_zvuk("flag"); }
    void playBomb() { izdat_zvuk("bomb"); }
    void playWin() { izdat_zvuk("win"); }
    void playLose() { izdat_zvuk("lose"); }
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
        }
        else if (themeName == "modern") {
            cell_closed = "■";
            cell_open = "□";
            bomb = "💣";
        }
        else if (themeName == "simple") {
            cell_closed = "#";
            cell_open = ".";
            bomb = "B";
        }
    }

    void print() const {
        printf("Тема: %s\n", name.c_str());
        printf("Закрытая клетка: %s, Открытая: %s, Бомба: %s\n",
            cell_closed.c_str(), cell_open.c_str(), bomb.c_str());
    }

    std::string getCellClosed() const { return cell_closed; }
    std::string getCellOpen() const { return cell_open; }
    std::string getBomb() const { return bomb; }
    std::string getName() const { return name; }
};

class HelpSystem {
public:
    void print() const {
        printf("Система помощи\n");
    }

    void showTips() {
        printf("=== СОВЕТЫ ДЛЯ САПЁРА ===\n");
        printf("1. Начинайте с углов или центра\n");
        printf("2. Используйте флаги (F) для отметки бомб\n");
        printf("3. Цифра показывает сколько бомб вокруг клетки\n");
        printf("4. Если вокруг клетки уже отмечено достаточно флагов,\n");
        printf("   можно открыть оставшиеся клетки двойным кликом\n");
        printf("5. Не торопитесь, анализируйте поле\n");
    }

    void showRules() {
        printf("=== ПРАВИЛА ИГРЫ ===\n");
        printf("Цель: открыть все клетки без бомб\n");
        printf("1. Клик по клетке - открыть\n");
        printf("2. Правый клик - поставить/убрать флаг\n");
        printf("3. Цифры показывают количество бомб вокруг\n");
        printf("4. Наступили на бомбу - игра проиграна\n");
        printf("5. Открыли все безопасные клетки - победа!\n");
    }
};

class GameAnalyzer : public AbstractSchitatel {
private:
    int analyzed_games;

public:
    GameAnalyzer() : AbstractSchitatel("Анализатор игр"), analyzed_games(0) {}

    void print() const {
        printf("Анализатор игрового процесса: %s\n", tip_schetchika.c_str());
        printf("Проанализировано игр: %d\n", analyzed_games);
    }

    void sbrosit() override {
        analyzed_games = 0;
        printf("Анализатор сброшен\n");
    }

    void pokazat_tekushee() const override {
        printf("Текущее состояние анализатора: %d игр проанализировано\n", analyzed_games);
    }

    void analyzeBoard(const Board& board) {
        analyzed_games++;
        printf("Анализ поля %dx%d:\n", board.getShirina(), board.getVysota());
        printf("Количество бомб: %d\n", board.getVsegoBomb());
        printf("Плотность бомб: %.1f%%\n",
            (float)board.getVsegoBomb() / (board.getShirina() * board.getVysota()) * 100);
    }
};

class HighScore : public AbstractRekordsmen {
private:
    std::string imya_igroka;
    int rezultat;

public:
    HighScore(const std::string& player_name, int result,
        const std::string& category = "Время", int year = 2024)
        : AbstractRekordsmen(category, year),
        imya_igroka(player_name), rezultat(result) {}

    void print() const {
        printf("Рекорд: %s - %d", imya_igroka.c_str(), rezultat);
        if (kategoriya_sorevnovaniya == "Время") printf(" сек");
        printf(", Категория: %s, Год: %d\n",
            kategoriya_sorevnovaniya.c_str(), god_ustanovki_rekorda);
    }

    void zaregistrirovat_pobedu() override {
        printf("Рекорд зарегистрирован: %s - %d\n", imya_igroka.c_str(), rezultat);
    }

    void pokazat_rezultat() const override {
        printf("Рекорд в категории '%s': %s - %d\n",
            kategoriya_sorevnovaniya.c_str(), imya_igroka.c_str(), rezultat);
    }

    int getRezultat() const { return rezultat; }
    std::string getImyaIgroka() const { return imya_igroka; }
};

class HighScoreManager {
private:
    std::vector<std::shared_ptr<HighScore>> high_scores;

public:
    void print() const {
        printf("=== ТАБЛИЦА РЕКОРДОВ ===\n");
        if (high_scores.empty()) {
            printf("Рекордов пока нет\n");
            return;
        }

        for (size_t i = 0; i < high_scores.size() && i < 10; i++) {
            printf("%zu. ", i + 1);
            if (high_scores[i]) high_scores[i]->print();
        }
    }

    void addScore(std::shared_ptr<HighScore> score) {
        high_scores.push_back(score);
        std::sort(high_scores.begin(), high_scores.end(),
            [](const std::shared_ptr<HighScore>& a, const std::shared_ptr<HighScore>& b) {
                return a->getRezultat() < b->getRezultat();
            });

        if (high_scores.size() > 10) {
            high_scores.resize(10);
        }
    }

    void saveToFile(const std::string& filename) {
        FILE* file = fopen(filename.c_str(), "w");
        if (file) {
            for (const auto& score : high_scores) {
                if (score) {
                    fprintf(file, "%s,%d,%s,%d\n",
                        score->getImyaIgroka().c_str(),
                        score->getRezultat(),
                        score->getKategoriyaSorevnovaniya().c_str(),
                        score->getGodUstanovkiRekorda());
                }
            }
            fclose(file);
            printf("Рекорды сохранены в %s\n", filename.c_str());
        }
    }
};

class HintSystem {
private:
    int hints_available;
    int hints_used;
public:
    HintSystem() : hints_available(3), hints_used(0) {}

    void print() const {
        printf("Система подсказок, доступно подсказок: %d, использовано: %d\n",
            hints_available, hints_used);
    }

    bool useHint() {
        if (hints_available > 0) {
            hints_available--;
            hints_used++;
            printf("Использована подсказка! Осталось: %d\n", hints_available);
            return true;
        }
        printf("Подсказки закончились!\n");
        return false;
    }

    void addHints(int count) {
        hints_available += count;
        printf("Добавлено %d подсказок. Всего: %d\n", count, hints_available);
    }

    int getHintsAvailable() const { return hints_available; }
    int getHintsUsed() const { return hints_used; }
};

class GameHistory {
private:
    std::vector<std::string> moves;
    std::string player_name;
    time_t start_time;

public:
    GameHistory(const std::string& player) : player_name(player) {
        start_time = time(NULL);
    }

    void print() const {
        printf("=== ИСТОРИЯ ХОДОВ: %s ===\n", player_name.c_str());
        printf("Начало игры: %s", ctime(&start_time));
        printf("Количество ходов: %zu\n", moves.size());

        for (size_t i = 0; i < moves.size(); i++) {
            printf("Ход %zu: %s\n", i + 1, moves[i].c_str());
        }
    }

    void addMove(const std::string& move) {
        time_t current_time = time(NULL);
        int elapsed = (int)(current_time - start_time);
        std::string timed_move = "[" + std::to_string(elapsed) + "с] " + move;
        moves.push_back(timed_move);
    }

    void saveToFile(const std::string& filename) {
        FILE* file = fopen(filename.c_str(), "w");
        if (file) {
            fprintf(file, "История игры: %s\n", player_name.c_str());
            fprintf(file, "Начало: %s", ctime(&start_time));
            fprintf(file, "Ходов: %zu\n\n", moves.size());

            for (const auto& move : moves) {
                fprintf(file, "%s\n", move.c_str());
            }
            fclose(file);
            printf("История сохранена в %s\n", filename.c_str());
        }
    }
};

class MoveCounter : public AbstractSchitatel {
private:
    int vsego_hodov;
    int bezopasnye_hody;
    int flag_hody;
    int bomb_hody;

public:
    MoveCounter()
        : AbstractSchitatel("Счетчик ходов"),
        vsego_hodov(0), bezopasnye_hody(0), flag_hody(0), bomb_hody(0) {}

    void print() const {
        printf("=== СТАТИСТИКА ХОДОВ ===\n");
        printf("Тип счетчик: %s\n", tip_schetchika.c_str());
        printf("Всего ходов: %d\n", vsego_hodov);
        printf("Безопасные: %d, Флаги: %d, Бомбы: %d\n",
            bezopasnye_hody, flag_hody, bomb_hody);
    }

    void sbrosit() override {
        vsego_hodov = 0;
        bezopasnye_hody = 0;
        flag_hody = 0;
        bomb_hody = 0;
        printf("Счетчик ходов сброшен\n");
    }

    void pokazat_tekushee() const override {
        printf("Текущее состояние счетчика: %d ходов\n", vsego_hodov);
    }

    void dobavit_bezopasniy_hod() {
        vsego_hodov++;
        bezopasnye_hody++;
    }

    void dobavit_flag_hod() {
        vsego_hodov++;
        flag_hody++;
    }

    void dobavit_bomb_hod() {
        vsego_hodov++;
        bomb_hody++;
    }

    int getVsegoHodov() const { return vsego_hodov; }
    int getBezopasnyeHody() const { return bezopasnye_hody; }
    int getFlagHody() const { return flag_hody; }
    int getBombHody() const { return bomb_hody; }

    float getEffectiveness() const {
        if (vsego_hodov == 0) return 0.0f;
        return (float)bezopasnye_hody / vsego_hodov * 100.0f;
    }
};

template<typename T>
class TemplateGeografiya : public AbstractGeografiya {
private:
    T dopolnitelnyiParam;
    std::vector<std::shared_ptr<AbstractGeografiya>> regions;

public:
    TemplateGeografiya(const std::string& region = "Неизвестно", int danger = 0, T param = T())
        : AbstractGeografiya(region, danger), dopolnitelnyiParam(param) {}

    void addRegion(std::shared_ptr<AbstractGeografiya> region) {
        regions.push_back(region);
    }

    void issledovat_territoriyu() override {
        printf("Исследование шаблонной территории: %s\n", nazvanie_regiona.c_str());
        for (auto& region : regions) {
            region->issledovat_territoriyu();
        }
    }

    void pokazat_info() const override {
        printf("Шаблонная география: %s, Опасность: %d, Параметр: ",
            nazvanie_regiona.c_str(), uroven_opasnosti);
        std::cout << dopolnitelnyiParam << std::endl;
    }

    T getParam() const { return dopolnitelnyiParam; }
    void setParam(T param) { dopolnitelnyiParam = param; }

    std::vector<std::shared_ptr<AbstractGeografiya>> getRegions() const { return regions; }

    void sortRegionsByDanger() {
        std::sort(regions.begin(), regions.end(),
            [](const std::shared_ptr<AbstractGeografiya>& a,
                const std::shared_ptr<AbstractGeografiya>& b) {
                    return a->getUrovenOpasnosti() < b->getUrovenOpasnosti();
            });
    }
};

template<typename T>
class TemplateSchitatel : public AbstractSchitatel {
private:
    T currentValue;
    std::map<std::string, T> history;

public:
    TemplateSchitatel(const std::string& tip = "Счетчик", T startValue = T())
        : AbstractSchitatel(tip), currentValue(startValue) {}

    void sbrosit() override {
        history["reset"] = currentValue;
        currentValue = T();
        printf("Счетчик сброшен\n");
    }

    void pokazat_tekushee() const override {
        printf("Текущее значение: ");
        std::cout << currentValue << std::endl;
    }

    void increment(T value) {
        currentValue += value;
        history["increment"] = value;
    }

    T getCurrentValue() const { return currentValue; }

    std::map<std::string, T> getHistory() const { return history; }

    bool containsKey(const std::string& key) const {
        return history.find(key) != history.end();
    }
};

template<typename T>
class TemplateZavod : public AbstractZavod {
private:
    std::array<T, 10> productionQueue;
    int queueIndex;

public:
    TemplateZavod(const std::string& nazvanie = "Завод")
        : AbstractZavod(nazvanie), queueIndex(0) {
        productionQueue.fill(T());
    }

    void zapustit_proizvodstvo() override {
        printf("Шаблонный завод '%s' запускает производство...\n", nazvanie_zavoda.c_str());
        if (queueIndex < 10) {
            productionQueue[queueIndex++] = T();
        }
    }

    void ostanovit_proizvodstvo() override {
        printf("Шаблонный завод '%s' останавливает производство...\n", nazvanie_zavoda.c_str());
        queueIndex = 0;
    }

    void addToQueue(T item) {
        if (queueIndex < 10) {
            productionQueue[queueIndex++] = item;
        }
    }

    std::array<T, 10> getProductionQueue() const { return productionQueue; }
    int getQueueSize() const { return queueIndex; }

    bool isQueueFull() const {
        return queueIndex >= 10;
    }
};

template<typename T>
class TemplateElektropribor : public AbstractElektropribor {
private:
    std::list<T> soundQueue;

public:
    TemplateElektropribor(const std::string& tip = "Устройство")
        : AbstractElektropribor(tip) {}

    void vkluchit() override {
        printf("Шаблонное устройство '%s' включено\n", tip_ustroystva.c_str());
        soundQueue.clear();
    }

    void izdat_zvuk(const std::string& zvuk) override {
        printf("[%s] %s\n", tip_ustroystva.c_str(), zvuk.c_str());
    }

    void queueSound(T sound) {
        soundQueue.push_back(sound);
    }

    void playAllSounds() {
        for (const auto& sound : soundQueue) {
            std::cout << "Проигрывание: " << sound << std::endl;
        }
        soundQueue.clear();
    }

    std::list<T> getSoundQueue() const { return soundQueue; }

    bool isSoundQueueEmpty() const {
        return soundQueue.empty();
    }
};


template<typename T1, typename T2>
class TemplateRekordsmen : public AbstractRekordsmen {
private:
    std::variant<T1, T2> recordData;
    std::vector<std::shared_ptr<AbstractRekordsmen>> competitors;

public:
    TemplateRekordsmen(const std::string& kategoriya = "Категория", int god = 2024)
        : AbstractRekordsmen(kategoriya, god) {}

    void zaregistrirovat_pobedu() override {
        printf("Победа зарегистрирована в категории: %s\n", kategoriya_sorevnovaniya.c_str());
    }

    void pokazat_rezultat() const override {
        printf("Шаблонный рекорд: %s, Год: %d\n",
            kategoriya_sorevnovaniya.c_str(), god_ustanovki_rekorda);
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double> ||
                std::is_same_v<T, float> || std::is_same_v<T, long>)
                std::cout << "Значение рекорда: " << arg << std::endl;
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "Строковый рекорд: " << arg << std::endl;
            }, recordData);
    }

    void setRecordData(const std::variant<T1, T2>& data) {
        recordData = data;
    }

    std::variant<T1, T2> getRecordData() const { return recordData; }

    void addCompetitor(std::shared_ptr<AbstractRekordsmen> competitor) {
        competitors.push_back(competitor);
    }

    std::vector<std::shared_ptr<AbstractRekordsmen>> getCompetitors() const { return competitors; }

    void sortCompetitorsByYear() {
        std::sort(competitors.begin(), competitors.end(),
            [](const std::shared_ptr<AbstractRekordsmen>& a,
                const std::shared_ptr<AbstractRekordsmen>& b) {
                    return a->getGodUstanovkiRekorda() < b->getGodUstanovkiRekorda();
            });
    }
};
void demonstrateSTLFeatures() {
    printf("\n=== ДЕМОНСТРАЦИЯ STL КОНТЕЙНЕРОВ И ШАБЛОНОВ ===\n\n");

    std::vector<std::shared_ptr<AbstractGeografiya>> regions;
    regions.push_back(std::make_shared<Geografiya>("Север", 3));
    regions.push_back(std::make_shared<Geografiya>("Юг", 7));
    regions.push_back(std::make_shared<Geografiya>("Запад", 2));
    regions.push_back(std::make_shared<Geografiya>("Восток", 5));

    printf("1. std::sort - сортировка регионов по опасности:\n");
    std::sort(regions.begin(), regions.end(),
        [](const auto& a, const auto& b) {
            return a->getUrovenOpasnosti() < b->getUrovenOpasnosti();
        });

    for (const auto& region : regions) {
        region->pokazat_info();
    }

    printf("\n2. std::find_if - поиск опасного региона (опасность > 5):\n");
    auto dangerousIt = std::find_if(regions.begin(), regions.end(),
        [](const auto& region) {
            return region->getUrovenOpasnosti() > 5;
        });

    if (dangerousIt != regions.end()) {
        printf("Найден опасный регион: ");
        (*dangerousIt)->pokazat_info();
    }

    std::array<int, 5> dangerLevels = { 3, 7, 2, 5, 9 };
    printf("\n3. std::array и std::max_element:\n");
    auto maxIt = std::max_element(dangerLevels.begin(), dangerLevels.end());
    printf("Максимальный уровень опасности: %d\n", *maxIt);

    std::map<std::string, std::shared_ptr<AbstractZavod>> factories;
    factories["Основной"] = std::make_shared<Zavod>("Главный завод");
    factories["Вспомогательный"] = std::make_shared<Zavod>("Второстепенный завод");

    printf("\n4. std::map - фабрики:\n");
    for (const auto& [key, factory] : factories) {
        printf("Ключ: %s, Завод: %s\n", key.c_str(), factory->getNazvanieZavoda().c_str());
    }

    std::list<std::shared_ptr<AbstractElektropribor>> devices;
    devices.push_back(std::make_shared<Elektropribor>("Колонки"));
    devices.push_back(std::make_shared<Elektropribor>("Наушники"));

    printf("\n5. std::list - электроприборы:\n");
    for (const auto& device : devices) {
        device->izdat_zvuk("тестовый звук");
    }

    printf("\n6. Шаблонные функции:\n");
    std::vector<Geografiya> geoVec;
    geoVec.emplace_back("Регион1", 4);
    geoVec.emplace_back("Регион2", 7);
    geoVec.emplace_back("Регион3", 2);

    auto result1 = calculateAverageUroven(geoVec);
    printf("Средняя опасность регионов: %lf\n", result1);
    std::vector<Elektropribor> elecVec;
    elecVec.emplace_back("Колонки");
    elecVec.emplace_back("Наушники");
    elecVec.emplace_back("Колонки");

    auto result2 = findMostCommonTip(elecVec);
    printf("Самый распространенный тип устройства: %s\n", result2.c_str());

    std::vector<Zavod> zavodVec;
    zavodVec.emplace_back("Завод А");
    zavodVec.emplace_back("Завод С");
    zavodVec.emplace_back("Завод Б");

    sortByNazvanie(zavodVec);
    printf("Отсортированные заводы:\n");
    for (const auto& z : zavodVec) {
        printf("  %s\n", z.getNazvanieZavoda().c_str());
    }

    std::vector<Rekordsmen> rekords;
    rekords.emplace_back("Скорость", 2023, "Игрок1");
    rekords.emplace_back("Точность", 2024, "Игрок2");
    rekords.emplace_back("Выносливость", 2022, "Игрок3");

    auto best = findBestRezultat(rekords);
    if (best) {
        printf("Лучший результат: год %d\n", best->getGodUstanovkiRekorda());
    }

    std::vector<Schitatel> counters;
    counters.emplace_back("Счетчик1", 10);
    counters.emplace_back("Счетчик2", 20);
    counters.emplace_back("Счетчик3", 30);

    int total = calculateTotalValue(counters);
    printf("Общее значение всех счетчиков: %d\n", total);

    printf("\n7. Шаблонные классы:\n");
    TemplateGeografiya<int> tGeo("Шаблонный регион", 5, 100);
    tGeo.addRegion(std::make_shared<Geografiya>("Вложенный регион", 3));
    tGeo.issledovat_territoriyu();
    printf("Параметр шаблонной географии: %d\n", tGeo.getParam());

    TemplateSchitatel<double> tCounter("Шаблонный счетчик", 3.14);
    tCounter.increment(1.5);
    tCounter.pokazat_tekushee();

    TemplateZavod<std::string> tFactory("Шаблонный завод");
    tFactory.addToQueue("Продукт1");
    tFactory.addToQueue("Продукт2");
    printf("Размер очереди производства: %d\n", tFactory.getQueueSize());

    TemplateElektropribor<std::string> tDevice("Шаблонное устройство");
    tDevice.vkluchit();
    tDevice.queueSound("Звук1");
    tDevice.queueSound("Звук2");
    tDevice.playAllSounds();

    TemplateRekordsmen<int, std::string> tRecord("Шаблонный рекорд", 2024);
    tRecord.setRecordData(42);
    tRecord.zaregistrirovat_pobedu();

    printf("\n8. std::variant и std::span:\n");
    std::variant<int, std::string, double> data;
    data = "Рекордная строка";
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>)
            printf("Целочисленный рекорд: %d\n", arg);
        else if constexpr (std::is_same_v<T, std::string>)
            printf("Строковый рекорд: %s\n", arg.c_str());
        else if constexpr (std::is_same_v<T, double>)
            printf("Вещественный рекорд: %.2f\n", arg);
        }, data);

    const char* sounds[] = { "beep", "buzz", "click", "alert" };
    std::span<const char*> soundSpan(sounds);
    printf("Доступные звуки (%zu):\n", soundSpan.size());
    for (const auto& sound : soundSpan) {
        printf("  %s\n", sound);
    }

    printf("\n9. Демонстрация полной игры:\n");
    auto player = std::make_shared<Player>("Тестовый игрок");
    auto board = std::make_unique<Board>(5, 5, 3);
    Game game(std::move(board), player, "Тестовый регион");
    game.print();

    printf("\n10. Все контейнеры STL в одном примере:\n");
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::array<char, 3> arr = { 'a', 'b', 'c' };
    std::list<std::string> lst = { "один", "два", "три" };
    std::map<int, std::string> mp = { {1, "первый"}, {2, "второй"} };

    printf("vector size: %zu\n", vec.size());
    printf("array[1]: %c\n", arr[1]);
    printf("list front: %s\n", lst.front().c_str());
    printf("map[2]: %s\n", mp[2].c_str());
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    demonstrateSTLFeatures();

    printf("\n=== ПРОГРАММА ЗАВЕРШЕНА ===\n");

    return 0;
}