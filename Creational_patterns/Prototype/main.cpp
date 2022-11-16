#include <iostream>
#include <vector>
#include <map>
//Ptototype
//Когда необходимый объект аналогичен уже существующему или когда создание с нуля дороже клонирования.

// Идентификаторы всех родов войск
enum Warrior_ID {
    Infantryman_ID,
    Archer_ID
};

class Warrior;  // Опережающее объявление
typedef std::map<Warrior_ID, Warrior*> RegistryType;

// Реестр прототипов определен в виде Singleton Мэйерса
RegistryType& getRegistry()
{
    static RegistryType _instance;
    return _instance;
}

// базовый класс c интерфейсом. Здесь также определен статический
// обобщенный конструктор для создания боевых единиц всех родов войск
class Warrior
{
public:
    virtual Warrior* clone() = 0;
    virtual void info() = 0;
    virtual ~Warrior() {}
    // Параметризированный статический метод для создания воинов
    // всех родов войск
    static Warrior* createWarrior( Warrior_ID id ) {
        RegistryType& r = getRegistry();
        if (r.find(id) != r.end())
            /*
             * Возвращаемое значение
             * Итератор, ссылающийся на расположение элемента с указанным ключом,
             * или расположение последнего элемента в map (map::end()),
             * если совпадение для ключа не найдено.
             */
            return r[id]->clone();
        return 0;
    }
protected:
    // Добавление прототипа в множество прототипов
    static void addPrototype( Warrior_ID id, Warrior * prototype ) {
        RegistryType& r = getRegistry();
        r[id] = prototype;
    }
    // Удаление прототипа из множества прототипов
    static void removePrototype( Warrior_ID id ) {
        RegistryType& r = getRegistry();
        r.erase( r.find( id));
    }
};


// В производных классах различных родов войск в виде статических
// членов-данных определяются соответствующие прототипы
class Infantryman: public Warrior
{
public:
    Warrior* clone() {
        return new Infantryman( *this);
    }
    void info() {
        std::cout << "Infantryman" << std::endl;
    }
private:
    Infantryman(int) {
        Warrior::addPrototype( Infantryman_ID, this);
    }
    Infantryman() {}
    static Infantryman prototype;
};

class Archer: public Warrior
{
public:
    Warrior* clone() {
        return new Archer( *this);
    }
    void info() {
        std::cout << "Archer" << std::endl;
    }
private:
    Archer(int) {
        addPrototype( Archer_ID, this);
    }
    Archer() {}
    static Archer prototype;
};

//указание прототипов
Infantryman Infantryman::prototype = Infantryman(0);
Archer Archer::prototype = Archer(0);


int main()
{
    std::vector<Warrior*> v;
    v.push_back( Warrior::createWarrior( Infantryman_ID));
    v.push_back( Warrior::createWarrior( Archer_ID));

    for(int i=0; i<v.size(); i++)
        v[i]->info();
}