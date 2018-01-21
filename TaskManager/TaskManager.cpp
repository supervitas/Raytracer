//
// Created by Виталий on 20.01.2018.
//

#include <iostream>
#include "TaskManager.h"

TaskManager::TaskManager() {
    for (int i = 0; i < concurentThreads; i++) {
        threadPool.emplace_back([this,i]() -> void {
            while (true) {
                std::function<void()> task; {
                    std::unique_lock<std::mutex> lock( mutex );
                    condition.wait(lock, [this]() -> bool {
                        return !taskQueue.empty() || stop;
                    });

                    if (stop && taskQueue.empty()) {
                        return;
                    }

                    task = std::move(taskQueue.front());
                    taskQueue.pop();
                }
                task();
                taskCount--;
            }
        });
    }
}
TaskManager::~TaskManager() {
    stop = true;
    condition.notify_all();
    for (auto &w: threadPool) {
        w.join();
    }
}

void TaskManager::AddTask(std::function<void()> job) {
    {
        std::unique_lock<std::mutex> lock(mutex);
        taskQueue.push(job);
    }
    taskCount++;
    condition.notify_one();

}

void TaskManager::waitAll() const {
    while (taskCount != 0u) {
        std::this_thread::yield();
    }
}


