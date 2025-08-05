/*
The Bill Pugh Singleton Design Pattern is one of the best and most efficient
 ways to implement a thread-safe lazy-loaded singleton in C++ or Java
  without using locks or mutexes directly.
*/


/*
This is a highly efficient way to implement the Singleton pattern. 
It uses a static inner helper class to hold the Singleton instance. 
The instance is created only when the inner class is loaded, which happens 
only when getInstance() is called for the first time.
*/


/*
The first time getInstance() is called, the static local variable instance is constructed.

From the second call onward, the same memory address (&instance) is returned – the constructor is not called again.

This is guaranteed by the C++ standard since C++11, and it’s thread-safe.
*/

#include <iostream>
#include <unordered_map>
using namespace std;

class JudgeAnalytics {
private:
    int totalSubmissions;
    int acceptedCount;
    int wrongAnswerCount;
    int tleCount;
    unordered_map<string, int> userSubmissionCount;

    // Private constructor
    JudgeAnalytics() {
        totalSubmissions = acceptedCount = wrongAnswerCount = tleCount = 0;
    }

    // Delete copy constructor and assignment operator
    JudgeAnalytics(const JudgeAnalytics&) = delete;
    JudgeAnalytics& operator=(const JudgeAnalytics&) = delete;

public:
    // Bill Pugh Singleton: thread-safe lazy initialization using function-local static
    static JudgeAnalytics* getInstance() {
        // The static local variable behaves like the Java Holder class:
        // - It's not initialized until this method is called
        // - Initialization is thread-safe (in C++11 and later)
        // - No need for manual synchronization
        static JudgeAnalytics instance;
        return &instance;
    }

    void recordSubmission(string name, string result) {
        totalSubmissions++;
        userSubmissionCount[name]++;
        if (result == "AC") {
            acceptedCount++;
        } else if (result == "WA") {
            wrongAnswerCount++;
        } else if (result == "TLE") {
            tleCount++;
        }
    }

    void printStats() {
        cout << "Total submissions in Judge: " << totalSubmissions << endl;
        cout << "Total accepted submissions in Judge: " << acceptedCount << endl;
        cout << "Total wrong submissions in Judge: " << wrongAnswerCount << endl;
        cout << "Total TLE submissions in Judge: " << tleCount << endl;
    }

    int getUsersSubmissionCount(string name) {
        auto it = userSubmissionCount.find(name);
        return (it != userSubmissionCount.end()) ? it->second : 0;
    }
};

class Main {
public:
    static void run() {
        JudgeAnalytics* analytics = JudgeAnalytics::getInstance();

        analytics->recordSubmission("Ankit", "AC");
        analytics->recordSubmission("Lokesh", "WA");
        analytics->recordSubmission("Rohit", "TLE");
        analytics->recordSubmission("Vibha", "AC");
        analytics->recordSubmission("Deepak", "AC");

        cout << "\n=== Judge Analytics Report ===" << endl;
        analytics->printStats();

        cout << "\nUser-specific Submission Count:" << endl;
        cout << "Ankit: " << analytics->getUsersSubmissionCount("Ankit") << endl;
        cout << "Lokesh: " << analytics->getUsersSubmissionCount("Lokesh") << endl;
        cout << "Rohit: " << analytics->getUsersSubmissionCount("Rohit") << endl;
    }
};

int main() {
    Main::run();
    return 0;
}
