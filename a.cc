#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

namespace {
    struct TheMagicTree {
        void sleep(int sleepFor = -1) {

            static std::default_random_engine generator;

            if (0 > sleepFor) {
                std::uniform_int_distribution<int> distribution(0, 1000);
                sleepFor = distribution(generator);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds{sleepFor});
        }
    };

    TheMagicTree* getTheMagicTree(const bool create = true) {
        static struct {
            std::mutex mutex;
            TheMagicTree* pointer = nullptr;
        } instance;
        std::lock_guard<std::mutex> lock(instance.mutex);
            if (create)
                instance.pointer = new TheMagicTree{};
        return instance.pointer;
    }
}

int main() {
    std::vector<std::thread> threads(10);
    for (auto& thread : threads)
        thread = std::thread([]{
            TheMagicTree* const magicTree = getTheMagicTree();
            magicTree->sleep();
        });

    for (auto& thread : threads)
        thread.join();
    
    return 0;
}
