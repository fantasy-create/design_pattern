#include<iostream>
#include<mutex>
#include<queue>
#include<thread>
#include <chrono> 

using namespace std;

//写一个任务队列

class TaskQueue
{
public:
    static TaskQueue* getInstance()
    {
        return m_taskQ;
    }

    void print()
    {
        cout << "This is a task queue." << endl;
    }

    //判断任务队列是否为空
    bool isEmpty()
    {
        lock_guard<mutex> lock(m_mutex);
        return m_data.empty();
    }
    //添加任务
    void addTask(int task)
    {
        lock_guard<mutex> lock(m_mutex);
        m_data.push(task);
    }
    //删除任务
    bool removeTask()
    {
        lock_guard<mutex> lock(m_mutex);
        if(m_data.empty())
        {
            return false;
        }

        m_data.pop();
        return true;
    }

    //获取任务（不删除任务）
    int getTask()
    {
        lock_guard<mutex> lock(m_mutex);
        if(m_data.empty())
        {
            return -1;
        }

        int data = m_data.front();
        return data;
    }


private:
//方法二：
    TaskQueue() = default;
    TaskQueue(const TaskQueue&) = default;
    TaskQueue& operator=(const TaskQueue&) = default;

    //只能通过类名访问静态属性或方法
    static TaskQueue* m_taskQ;
    
    //定义任务队列
    queue<int> m_data;
    mutex m_mutex;

};

TaskQueue* TaskQueue::m_taskQ = new TaskQueue();

int main()
{
    TaskQueue* taskQueue = TaskQueue::getInstance();
    
    //生产者
    thread t1([=](){
        for(int i = 0; i < 10; i++)
        {
            taskQueue->addTask(i + 100);
            cout << "+++ push data:" << i + 100 << ", threadID:"<<
                this_thread::get_id() << endl;

            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });
    
    //消费者
    thread t2([=](){
        this_thread::sleep_for(chrono::milliseconds(100));
        while(!taskQueue->isEmpty())
        {
            int data = taskQueue->getTask();
            cout << "+++ take data:" << data << ", threadID:"<<
                this_thread::get_id() << endl;

            taskQueue->removeTask();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    });
    
    t1.join();
    t2.join();

    return 0;
}