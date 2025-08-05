/*
in this we will use synchronization which we will achieve using mutex 
int this we will lock the mutex and then we will create the instance for the first time
*/


#include <iostream>
#include <unordered_map>
#include <mutex>
using namespace std;

class JudgeAnalytics {
private:
    int totalSubmissions;
    int acceptedCount;
    int wrongAnswerCount;
    int tleCount;
    unordered_map<string, int> userSubmissionCount;

    // Singleton pointer and mutex for synchronization
    static JudgeAnalytics* instance;
    static mutex mtx;

    // Private constructor
    JudgeAnalytics() {
        totalSubmissions = acceptedCount = wrongAnswerCount = tleCount = 0;
    }

    // Delete copy constructor and assignment operator
    JudgeAnalytics(const JudgeAnalytics&) = delete;
    JudgeAnalytics& operator=(const JudgeAnalytics&) = delete;

public:
    // Thread-safe getInstance with synchronization
    static JudgeAnalytics* getInstance() {
        
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new JudgeAnalytics();
            }
        
        return instance;
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

// Initialize static members
JudgeAnalytics* JudgeAnalytics::instance = nullptr;
mutex JudgeAnalytics::mtx;

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
