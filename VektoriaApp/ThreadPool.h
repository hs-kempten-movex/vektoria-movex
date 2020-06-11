#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

using namespace std;

class ThreadPool
{
public:
    ThreadPool(size_t threads = thread::hardware_concurrency())
    {
        //Start n threads
        for (size_t i = 0; i < threads; i++)
        {
            m_threads.push_back
            (thread([this]()
                {
                    //Run this loop in every thread
                    while (true)
                    {
                        //check if task queue is empty and sleep if it is
                        m_taskQueueMutex.lock();
                        if (m_taskQueue.empty())
                        {
                            m_taskQueueMutex.unlock();
                            this_thread::sleep_for(chrono::milliseconds(100));
                            continue;
                        }

                        //if task queue is not empty, acquire next task
                        auto workFunc = m_taskQueue.front();
                        m_taskQueue.pop();
                        m_taskQueueMutex.unlock();

                        //exit loop if task is nullptr
                        if (workFunc == nullptr)
                        {
                            m_taskQueue.push(nullptr);
                            break;
                        }

                        //otherwise exit task
                        workFunc();
                    }
                }
            ));
        }
    }

    ~ThreadPool()
    {
        //push nullptr to task queue to signal the threads to exit
        m_taskQueue.push(nullptr);
        //wait until every thread has finished
        for (auto& thread : m_threads)
        {
            thread.join();
        }
    }

    template<typename F, typename... Args>
    void EnqueueTask(F&& f, Args&&... args)
    {
        m_taskQueueMutex.lock();
        m_taskQueue.push([=]() {f(args...);});
        m_taskQueueMutex.unlock();
    }

private:
    vector<thread> m_threads;

    //task queue has to be locked with mutex to avoid race conditions
    mutex m_taskQueueMutex;
    queue<function<void()>> m_taskQueue;
};

