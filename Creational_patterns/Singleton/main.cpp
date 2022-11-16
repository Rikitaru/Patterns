#include <iostream>
//Классическая реализация Singleton https://www.bestprog.net/ru/2020/11/14/patterns-singleton-pattern-overview-features-of-use-implementation-in-c-ru/#contents
class Singleton
{
private:
    static Singleton * _instance;
    int d;
    // Конструкторы и оператор присваивания недоступны клиентам
protected:
    Singleton() { d = 0; };
public:
    static Singleton * getInstance() {
        if(!_instance)
            _instance = new Singleton();
        else{
            return nullptr;
        }
        return _instance;
    }
    void setD(int _d) { d = _d; }
    void Print() { std::cout << "d = " << d << std::endl; }
    ~Singleton() { delete _instance; }
};

/* Клиенты запрашивают единственный объект класса через статическую функцию-член getInstance(),
 * которая при первом запросе динамически выделяет память под этот объект и затем возвращает
 * указатель на этот участок памяти. Впоследcтвии клиенты должны сами позаботиться об освобождении памяти при помощи оператора delete.
*/
// Инициализация внутренней статической переменной _instance,
Singleton* Singleton::_instance = nullptr;
int main()
{
    Singleton* obj1 = Singleton::getInstance();
    if (obj1 != nullptr) {
        obj1->setD(255);
        obj1->Print(); // d = 255
    }

    // Попытка создания другого экземляра класса Singleton
    Singleton* obj2 = Singleton::getInstance(); // obj2 = nullptr
    if (obj2 != nullptr) {
        obj2->setD(300);
        obj2->Print();
    }
    return 0;
}

//Singleton Мэйерса
class Singleton_M
{
private:
    Singleton_M() = default;
    Singleton_M( const Singleton_M&) = delete;
    Singleton_M& operator=( Singleton_M& ) = delete;
public:
    static Singleton_M& getInstance() {
        static Singleton_M  instance;
        return instance;
    }
};

//Есть также Singleton для многопоточного программирования! https://radioprog.ru/post/1470