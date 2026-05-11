#include<iostream>
#include<mutex>
#include<atomic>

using namespace std;

/*
// 懒汉模式解决多线程并行访问时的线程安全问题
// 1. 双重检查锁定机制
// 存在问题：代码转换为机器指令后运行顺序可能不是顺序的
class TaskQueue
{
public:
// 方法一：
    //TaskQueue() = delete;
    //TaskQueue(const TaskQueue&) = delete;
    //TaskQueue& operator=(const TaskQueue&) = delete;

    static TaskQueue* getInstance()
    {
        if(m_taskQ == nullptr)    //双重检查锁定机制，目的是为了不让每次访问单例对象时都加锁，只有在第一次创建单例对象时才加锁
        {
            m_mutex.lock(); 
            if(m_taskQ == nullptr)
            {
                m_taskQ = new TaskQueue();
            }
            m_mutex.unlock();
        }
        return m_taskQ;
    }

    void print()
    {
        cout << "This is a task queue." << endl;
    }

private:
//方法二：
    TaskQueue() = default;
    TaskQueue(const TaskQueue&) = default;
    TaskQueue& operator=(const TaskQueue&) = default;

    //只能通过类名访问静态属性或方法
    static TaskQueue* m_taskQ;
    static mutex m_mutex;

};

TaskQueue* TaskQueue::m_taskQ = nullptr;
mutex TaskQueue::m_mutex;

int main()
{
    TaskQueue* taskQueue = TaskQueue::getInstance();
    taskQueue->print();
    return 0;
}
*/

/*
// 用原子操作解决双重检查锁定机制存在的问题
class TaskQueue
{
public:
    static TaskQueue* getInstance()
    {
        TaskQueue* task = m_taskQ.load();
        if(task == nullptr)    
        {
            m_mutex.lock();
            task = m_taskQ.load(); 
            if(task == nullptr)
            {
                task = new TaskQueue();
                m_taskQ.store(task);
            }
            m_mutex.unlock();
        }
        return task;
    }

    void print()
    {
        cout << "This is a task queue." << endl;
    }

private:
    TaskQueue() = default;
    TaskQueue(const TaskQueue&) = default;
    TaskQueue& operator=(const TaskQueue&) = default;

    //只能通过类名访问静态属性或方法
    //static TaskQueue* m_taskQ;
    static mutex m_mutex;
    static atomic<TaskQueue*> m_taskQ;

};

atomic<TaskQueue*> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;

int main()
{
    TaskQueue* taskQueue = TaskQueue::getInstance();
    taskQueue->print();
    return 0;
}
*/

//使用局部静态对象解决线程安全问题
//原理：如果指令逻辑进入一个未被初始化的声明变量，所有并发执行应当等待该变量完成初始化
class TaskQueue
{
public:
    static TaskQueue* getInstance()
    {
        //原理：如果指令逻辑进入一个未被初始化的声明变量，所有并发执行应当等待该变量完成初始化
        static TaskQueue task;
        return &task;
    }

    void print()
    {
        cout << "This is a task queue." << endl;
    }

private:
    TaskQueue() = default;
    TaskQueue(const TaskQueue&) = default;
    TaskQueue& operator=(const TaskQueue&) = default;

};

int main()
{
    TaskQueue* taskQueue = TaskQueue::getInstance();
    taskQueue->print();
    return 0;
}