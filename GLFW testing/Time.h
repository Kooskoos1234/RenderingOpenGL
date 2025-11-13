#ifndef TIME_H
#define TIME_H
#include <chrono>
#include <iostream>

//returns current time (this is a shortcut). primarily used for performance testing, but also functional in some cases.
std::chrono::steady_clock::time_point curTime();
//Prints out current time with a loop number (*i*), along with a message(*message*). Used for debugging. 
void logTime(int i, std::string message, double& time, std::chrono::steady_clock::time_point timeStart, double array[]);
/*
  sleeps for precisely *time* milliseconds, by using sleep_for until precision isn't high enough, then spinlocks.
  This is more precise than sleep_for, but more demanding on the processor. It is slightly less presice than spinlocking,
  but it is much lighter on the processor. *this may become less accurate if many other programs are running on this
  machine. it still uses sleep_for and shares some of its limitations*.
*/
void preciseSleep(double time);

#endif