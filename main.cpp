#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <mutex>

const int swimmersCount = 6;

std::mutex mut;

void swim(std::vector<int>& speeds, int sequenceNumber, std::vector<std::string>& results) {
    int distance = 70;
    int traveled = 0;

    mut.lock();
    std::cout << "Swimmer #" << sequenceNumber << " has started!\n";
    mut.unlock();

    while (distance > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        traveled += speeds[sequenceNumber-1];
        distance -= speeds[sequenceNumber-1];

        mut.lock();
        std::cout << "Swimmer #" << sequenceNumber << " traveled " << traveled << " metres!\n";
        mut.unlock();
    }

    mut.lock();
    std::cout << "Swimmer #" << sequenceNumber << " has finished!\n";
    mut.unlock();

    mut.lock();
    results.push_back("Swimmer #" + std::to_string(sequenceNumber));
    mut.unlock();
}


int main() {
    std::vector<int> speeds;
    std::vector<std::string> results;
    for (int i = 0; i < swimmersCount; ++i) {
        std::cout << "Enter speed for swimmer #" << i + 1 << ": ";
        int speed;
        std::cin >> speed;
        speeds.push_back(speed);
    }
    std::cout << std::endl;

    std::thread first(swim, std::ref(speeds), 1, std::ref(results));
    std::thread second(swim, std::ref(speeds), 2, std::ref(results));
    std::thread third(swim, std::ref(speeds), 3, std::ref(results));
    std::thread fourth(swim, std::ref(speeds), 4, std::ref(results));
    std::thread fifth(swim, std::ref(speeds), 5, std::ref(results));
    std::thread sixth(swim, std::ref(speeds), 6, std::ref(results));

    first.join();
    second.join();
    third.join();
    fourth.join();
    fifth.join();
    sixth.join();

    for (int i = 0; i < swimmersCount; ++i) {
        std::cout << "Place #" << i + 1 << " – " << results[i] << std::endl;
    }

}
