#include <iostream>
#include <mutex>
#include <thread>

std::mutex cout_mtx;

void train_station(char name)
{
    std::string command;
    std::cout << "Train " << name << " has arrived on the station." << std::endl;
    while (command != "depart")
    {
        cout_mtx.lock();
        std::cout << "Input command for train " << name << ": " << std::endl;
        std::cin >> command;
        cout_mtx.unlock();
    }
    cout_mtx.lock();
    std::cout << "Train " << name << " is departing." << std::endl;
    cout_mtx.unlock();
}
std::mutex train_station_access;

void train_track(int timeSec, char name)
{
    std::this_thread::sleep_for(std::chrono::seconds(timeSec));
    cout_mtx.lock();
    std::cout << "Train " << name << " is waiting." << std::endl;
    cout_mtx.unlock();
    train_station_access.lock();
    train_station(name);
    train_station_access.unlock();
}

int main() {
    int trainA, trainB, trainC;
    std::cout << "Input times for trains A, B and C: ";
    std::cin >> trainA >> trainB >> trainC;
    std::thread train_track_A(train_track, trainA, 'A');
    std::thread train_track_B(train_track, trainB, 'B');
    std::thread train_track_C(train_track, trainC, 'C');
    train_track_A.join();
    train_track_B.join();
    train_track_C.join();
    return 0;
}
