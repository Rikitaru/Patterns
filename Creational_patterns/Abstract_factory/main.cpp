#include <iostream>
#include <vector>
//Абстрактная фабрика
//Прокачанная фабрика, Когда у вас есть взаимосвязи с не самой простой логикой создания (creation logic).

/**
 * Каждый отдельный продукт семейства продуктов должен иметь базовый интерфейс.
 * Все вариации продукта должны реализовывать этот интерфейс.
 */
struct baseTank {
    virtual void draw() = 0;
    virtual ~baseTank() = default;
};

/**
 * Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
struct t34USA : baseTank {
    void draw() override { std::cout << "I am heavy tank T34(USA)" << std::endl; }
};

struct t34USSR : baseTank {
    void draw() override { std::cout << "I am T-34(USSR)" << std::endl; }
};
//Эксперты, занимающиеся созданием строго определенных танков
struct Expert {
    virtual void draw() = 0;
    virtual ~Expert() = default;
};

struct USAExpert : Expert {
    void draw() override { std::cout << "I can create only USA tanks" << std::endl; }
};

struct USSRExpert : Expert {
    void draw() override { std::cout << "I can create only USSR tanks" << std::endl; }
};

/**
 * Интерфейс Абстрактной Фабрики объявляет набор методов, которые возвращают
 * различные абстрактные продукты.
 * Мы получили абстрактную фабрику, которая позволяет создавать семейства объектов
 * или взаимосвязанные объекты. То есть фабрика американских танков создаст американского
 * эксперта и танк, фабрика совестких танков — совесткого эксперта и танк
 */
struct TankFactory {
    virtual baseTank*  makeTank() = 0;
    virtual Expert*  makeExpert() = 0;
};

/**
 * Конкретная Фабрика производит семейство продуктов одной вариации. Фабрика
 * гарантирует совместимость полученных продуктов. Внимание! сигнатуры методов
 * Конкретной Фабрики возвращают абстрактный продукт, в то
 * время как внутри метода создается экземпляр конкретного продукта.
 */
struct USATankFactory : TankFactory {
    baseTank* makeTank() override{
        return new t34USA();
    }
    Expert* makeExpert() override{
        return new USAExpert();
    }
};

/**
 * Каждая Конкретная Фабрика имеет соответствующую вариацию продукта.
 */
struct USSRTankFactory : TankFactory {
    baseTank* makeTank() override{
        return new t34USSR();
    }
    Expert* makeExpert() override{
        return new USSRExpert();
    }
};

/**
 * Клиентский код получает на вход конкретную ФАБРИКУ (СССР или США) и создает с ней
 * конкретных специалистов и сами танки через абстрактные типы: Абстрактная Фабрика
 * и Абстрактный Продукт. Это позволяет передавать любой подкласс фабрики или продукта
 * клиентскому коду, не нарушая его.
 */
void ClientCode(TankFactory &factory) {
    baseTank *tank = factory.makeTank();
    Expert *Expert = factory.makeExpert();
    tank->draw();
    Expert->draw();
    delete tank;
    delete Expert;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    USATankFactory *f1 = new USATankFactory();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    USSRTankFactory *f2 = new USSRTankFactory();
    ClientCode(*f2);
    delete f2;
    return 0;
}