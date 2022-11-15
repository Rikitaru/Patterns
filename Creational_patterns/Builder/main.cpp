#include <iostream>
#include <vector>
using namespace std;
/** Строитель
 * Когда у объекта может быть несколько свойств и когда нужно избежать Telescoping constructor.
 * Ключевое отличие от шаблона «Простая фабрика»: он используется в одноэтапном создании,
 * а «Строитель» — в многоэтапном.
 * Пример вреднего Telescoping constructor - __construct($size, $cheese = true, $pepperoni = true, $tomato = false, $lettuce = true) {}
 */
// Классы всех возможных родов войск
class Archer
{
public:
    static void info() {
        cout << "Archer" << endl;
    }
};

class Catapult
{
public:
    static void info() {
        cout << "Catapult" << endl;
    }
};


// Класс "Армия", содержащий все типы боевых единиц
class Army
{
public:
    vector<Archer>      va;
    vector<Catapult>    vc;
    void info() {
        int i;
        for(i=0; i<va.size(); ++i)  va[i].info();
        for(i=0; i<vc.size(); ++i)  vc[i].info();
    }
};


// Базовый класс ArmyBuilder объявляет интерфейс для поэтапного
// построения армии и предусматривает его реализацию по умолчанию
class ArmyBuilder
{
protected:
    Army* p;
public:
    ArmyBuilder(): p(nullptr) {}
    virtual ~ArmyBuilder() = default;
    virtual void createArmy() {}
    virtual void buildArcher() {}
    virtual void buildCatapult() {}
    virtual Army* getArmy() { return p; }
};


// Римская армия может добавлять себе лучников и катапульты
class RomanArmyBuilder: public ArmyBuilder
{
public:
    void createArmy() override { p = new Army; }
    void buildArcher() override { p->va.push_back( Archer()); }
    void buildCatapult() override { p->vc.push_back( Catapult()); }
};


// Армия Карфагена может добавлять себе только лучников
class CarthaginianArmyBuilder: public ArmyBuilder
{
public:
    void createArmy() override { p = new Army; }
    void buildArcher() override { p->va.push_back( Archer()); }
    ///Метод поэтапного создания конкретно этой армии. НО!! можно ее вынести в отдельный класс Director
    // Army* FullCreate() {
    //     createArmy();
    //     buildArcher();
    // }
};


// Класс-распорядитель, поэтапно создающий армию той или иной стороны.
// Именно здесь определен алгоритм построения армии.
class Director
{
public:
    static Army* createArmy( ArmyBuilder & builder )
    {
        builder.createArmy();
        builder.buildArcher();
        builder.buildCatapult();
        return( builder.getArmy());
    }
};


int main()
{
    //auto a = (new CarthaginianArmyBuilder)->FullCreate();  Метод поэтапного создания конкретно этой армии

    RomanArmyBuilder ra_builder;
    CarthaginianArmyBuilder ca_builder;

    Army * ra = Director::createArmy( ra_builder);
    Army * ca = Director::createArmy( ca_builder);
    cout << "Roman army:" << endl;
    ra->info();
    cout << "\nCarthaginian army:" << endl;
    ca->info();
    return 0;
}