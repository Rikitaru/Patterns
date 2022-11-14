#include <iostream>
#include <vector>
#include <memory>
#include <random>
//Фабричный метод
//Этот шаблон полезен для каких-то общих обработок в классе, но требуемые подклассы динамически определяются в ходе
// выполнения (runtime). То есть когда клиент не знает, какой именно подкласс может ему понадобиться.
struct baseTank {
    virtual void type() = 0;
    virtual ~baseTank() = default;
};

struct t34USA : baseTank {
    void type() override { std::cout << "I am heavy tank T34(USA)" << std::endl; }
};

struct t34USSR : baseTank {
    void type() override { std::cout << "I am medium tank T-34(USSR)" << std::endl; }
};

struct maintenance {
    virtual baseTank* specialCheckTypeTank() = 0; // Фабричный метод
    void inspectTank() {
        baseTank* tank = specialCheckTypeTank();
        tank->type();
    };
};

struct HeavyMaintenance : maintenance {
    baseTank* specialCheckTypeTank() override {
        std::cout << "A special inspection of heavy tanks was carried out. For the presence of heavy armor." << std::endl;
        return new t34USA();
    }
};

struct MediumMaintenance : maintenance {
    baseTank* specialCheckTypeTank() override {
        std::cout << "A special inspection of the medium tanks was carried out. For the presence of a fast engine." << std::endl;
        return new t34USSR();
    }
};
int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    HeavyMaintenance *f1 = new HeavyMaintenance();
    f1->inspectTank();
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    MediumMaintenance *f2 = new MediumMaintenance();
    f2->inspectTank();
    delete f1;
    return 0;
}