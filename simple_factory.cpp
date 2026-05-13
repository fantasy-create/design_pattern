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

enum class Type:char{Sheep, Lion, Bat};
//建议使用枚举不使用宏
//因为枚举会进行错误的检查，宏不会
class SmileFactory
{
public:
    AbstractSmile* createSmile(Type type)
    {
        AbstractSmile* ptr = nullptr;
        switch (type)
        {
        case Type::Sheep:
            ptr = new SheepSmile();
            break;
        case Type::Lion:
            ptr = new LionSmile();
            break;
        case Type::Bat:
            ptr = new BatSmile();
            break;
        default:
            break;
        }
        return ptr;
    }
};

int main()
{
    SmileFactory* factory = new SmileFactory();
    AbstractSmile* obj = factory->createSmile(Type::Lion);

    obj->transform();
    obj->ablity();
    return 0;
}