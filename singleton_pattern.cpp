#include<iostream>

using namespace std;

// 定义一个单例模式的任务队列
class TaskQueue
{
public:
// 方法一：
    //TaskQueue() = delete;
    //TaskQueue(const TaskQueue&) = delete;
    //TaskQueue& operator=(const TaskQueue&) = delete;

    static TaskQueue* getInstance()
    {
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

};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue();

int main()
{
    TaskQueue* taskQueue = TaskQueue::getInstance();
    taskQueue->print();
    return 0;
}