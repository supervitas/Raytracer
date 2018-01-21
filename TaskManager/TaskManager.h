//
// Created by Виталий on 20.01.2018.
//

#ifndef RAYTRACER_TASKMANAGER_H
#define RAYTRACER_TASKMANAGER_H


#include <thread>
#include <vector>
#include <queue>

class TaskManager {
private:
    std::vector<std::thread> threadPool;
    std::queue<std::function<void()>> taskQueue;
    std::atomic_uint taskCount;
    std::mutex mutex;
    std::condition_variable condition;
    std::atomic_bool stop;

public:
    TaskManager();
    ~TaskManager();
    void AddTask(std::function<void()> job);
    void waitAll() const;

public:
    const int concurentThreads = std::thread::hardware_concurrency();
};


#endif //RAYTRACER_TASKMANAGER_H
