#include<iostream>

using namespace std;

//shipbody
class ShipBody
{
public:
    virtual string getBody() = 0;
    virtual ~ShipBody() {}
};

class WoodBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("木质船体");
    }
};

class IronBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("铁质船体");
    }
};

class MetalBody : public ShipBody
{
public:
    string getBody() override
    {
        return string("金属船体");
    }
};

//engine
class Engine
{
public:
    virtual string getEngine() = 0;
    virtual ~Engine() {}
};

class Human : public Engine
{
public:
    string getEngine() override
    {
        return string("人力引擎");
    }
};

class Diesel : public Engine
{
public:
    string getEngine() override
    {
        return string("柴油引擎");
    }
};

class Nuclear : public Engine
{
public:
    string getEngine() override
    {
        return string("核能引擎");
    }
};

//weapon
class Weapon
{
public:
    virtual string getWeapon() = 0;
    virtual ~Weapon() {}
};

class Gun : public Weapon
{
public:
    string getWeapon() override
    {
        return string("枪炮武器");
    }
};

class Cannon : public Weapon
{
public:
    string getWeapon() override
    {
        return string("加农炮武器");
    }
};

class Laser : public Weapon
{
public:
    string getWeapon() override
    {
        return string("激光武器");
    }
};

//ship  
class Ship
{
public:
    Ship(ShipBody* body, Engine* engine, Weapon* weapon)
        : m_body(body), m_engine(engine), m_weapon(weapon) {}

    string getProperty()
    {
        return m_body->getBody() + " + " + m_engine->getEngine() + " + " + m_weapon->getWeapon();
    }

    ~Ship()
    {
        cout << "Ship析构函数被调用..." << endl;
        delete m_body;
        delete m_engine;
        delete m_weapon;
    }

private:
    ShipBody* m_body;
    Engine* m_engine;
    Weapon* m_weapon;
};


//工厂类 - 抽象工厂模式
class AbstractFactory
{
public:
    virtual Ship* createShip() = 0;   

    virtual ~AbstractFactory() {}
};

class BasicFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new WoodBody, new Human, new Gun);

        cout << "BasicFactory工厂创建了一个基本的船只..." << endl;

        return ship;
    }
};

class StandardFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new IronBody, new Diesel, new Cannon);

        cout << "StandardFactory工厂创建了一个标准的船只..." << endl;

        return ship;
    }
};

class UltimataFactory : public AbstractFactory
{
public:
    Ship* createShip() override
    {
        Ship* ship = new Ship(new MetalBody, new Nuclear, new Laser);

        cout << "UltimataFactory工厂创建了一个终极的船只..." << endl;

        return ship;
    }
};

int main()
{
    //下单为plus
    AbstractFactory* factory = new UltimataFactory;
    Ship* ship = factory -> createShip();
    cout << ship->getProperty();
    
    delete ship;
    delete factory;
    return 0;
}