#include <iostream>
#include <vector>
#include <memory>
#include <random>
//Простая фаблика
//Когда создание объекта подразумевает какую-то логику, а не просто несколько присваиваний,
//то имеет смысл делегировать задачу выделенной фабрике, а не повторять повсюду один и тот же код.
//Описываем общий интерфейс Абстрактный класс
struct baseTank {
    virtual void draw() = 0;
    virtual ~baseTank() = default;
};

struct t34USA : baseTank {
    void draw() override { std::cout << "I am heavy tank T34(USA)" << std::endl; }
};

struct t34USSR : baseTank {
    void draw() override { std::cout << "I am T-34(USSR)" << std::endl; }
};

int main() {
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.

    std::vector<std::unique_ptr<baseTank>> tanks;
    int size = 5;
    std::cout <<"Задача создать пару танчиков для игрока по его уровню, навыкам и технологиям. "<<std::endl;
    for(int i = 0; i < size; ++i) {
        int rval = rand() % 2;
        std::cout << "Обработка логики создания танков: проверка способностей, денег, навыков, ресурсов, рандома и прочего" <<std::endl;
        std::cout << "В результате вся логика по созданию танка в одном месте. А описание как создать танк - в другом. Процесс самого создания и правил создания разделены" <<std::endl;
        switch(rval)
        {
            case 0:
                tanks.push_back(std::make_unique<t34USA>());
                break;
            case 1:
                tanks.push_back(std::make_unique<t34USSR>());
                break;
        }
    }

    for(int i = 0; i < size; ++i) {
        auto &obj = tanks[i];
        obj.get()->draw();
    }
    return 0;
}