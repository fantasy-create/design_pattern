#include <iostream>

using namespace std;

class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ablity() = 0;

    //使用虚析构函数，保证通过父类指针删除子类对象时能正确调用子类的析构函数，避免内存泄漏
    virtual ~AbstractSmile() {} 
};

class SheepSmile : public AbstractSmile
{
public:
    virtual void transform() override
    {
        cout << "变成人兽--山羊人形态..." << endl;
    }
    virtual void ablity() override
    {
        cout << "将手臂变成绵羊角的招式-巨羊角" << endl;
    }
};

class LionSmile : public AbstractSmile
{
public:
    virtual void transform() override
    {
        cout << "变成人兽--狮子人形态..." << endl;
    }
    virtual void ablity() override
    {
        cout << "将手臂变成狮子爪的招式-猛狮爪" << endl;
    }
};

class BatSmile : public AbstractSmile
{
public:
    virtual void transform() override
    {
        cout << "变成人兽--蝙蝠人形态..." << endl;
    }
    virtual void ablity() override
    {
        cout << "将手臂变成蝙蝠翼的招式-狂风翼" << endl;
    }
};

class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;   

    virtual ~AbstractFactory() {}
};

class LionSmileFactory : public AbstractFactory
{   
public:
    virtual AbstractSmile* createSmile() override
    {
        return new LionSmile();
    }

    ~LionSmileFactory() 
    {
        cout << "LionSmileFactory析构函数被调用..." << endl;
    }
};

class SheepSmileFactory : public AbstractFactory
{   
public:
    virtual AbstractSmile* createSmile() override
    {
        return new SheepSmile();
    }

    ~SheepSmileFactory() 
    {
        cout << "SheepSmileFactory析构函数被调用..." << endl;
    }
};

class BatSmileFactory : public AbstractFactory
{   
public:
    virtual AbstractSmile* createSmile() override
    {
        return new BatSmile();
    }

    ~BatSmileFactory() 
    {
        cout << "BatSmileFactory析构函数被调用..." << endl;
    }
};

int main()
{
    AbstractFactory* factory = new LionSmileFactory();
    AbstractSmile* obj = factory->createSmile();

    obj->transform();
    obj->ablity();

    delete obj; //释放对象内存
    delete factory; //释放工厂内存

    return 0;
}