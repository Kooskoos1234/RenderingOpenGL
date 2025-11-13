#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

void updateMean(double value, double& mean, int& counter) {
    mean *= counter;
    mean += value;
    counter++;
    mean /= counter;
}

chrono::steady_clock::time_point curTime() {
    return std::chrono::steady_clock::now();
}
void logTime(int i, string message, double& time, chrono::steady_clock::time_point timeStart, double array[]) {
    time = chrono::duration_cast<chrono::nanoseconds>(curTime() - timeStart).count() / 1e6;
    cout << "Loop #" << i << ": time in cycle " << message << ": " << time << "ms\n";
    array[i] = time;
}
void preciseSleep(double time) {
    chrono::time_point<chrono::steady_clock> start;
    static int counter{ 1 };
    static double estimate{ 5 };
    int loops{ 0 };
    while (time > estimate) {
        start = curTime();
        this_thread::sleep_for(chrono::milliseconds(1));
        double observed = (curTime() - start).count() / 1e6;
        loops++;
        time -= observed;
        updateMean(observed, estimate, counter);
    }
    start = curTime();
    while ((curTime() - start).count() / 1e6 < time);
}