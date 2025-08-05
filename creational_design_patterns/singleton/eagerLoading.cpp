//Eager Loading (Early Initialization)


/*
In Eager Loading, the instance is created at the time of class loading—even if it's not used.
This makes it thread-safe by default and simple to implement in C++.
*/

/*
-- in this we will create a private instance and move our constructor to private
-- delete copy constructor and assignment operator
--create a static method to get instance this will return the same instance to all the calls
--Initialize the eager-loaded singleton instance
*/




#include<iostream>
#include<map>
using namespace std;

class JudgeAnalytics{
    private: 
    int totalSubmissions;
    int acceptedCount;
    int wrongAnswerCount;
    int tleCount;
    unordered_map<string,int>userSubmissionCount;

    //create singleton instance
    static JudgeAnalytics instance;

    //private constructor to prevent external initialisation
    JudgeAnalytics(){
        totalSubmissions = acceptedCount = wrongAnswerCount = tleCount = 0;
    }

    //delete copy constructor and assignment operator
    JudgeAnalytics(const JudgeAnalytics&) = delete;
    JudgeAnalytics& operator=(const JudgeAnalytics&) = delete;

    



    public:

    static JudgeAnalytics& getInstance() {
        return instance;
    }
   

    void recordSubmission(string name , string result){
        totalSubmissions++;
        userSubmissionCount[name]++;
        if( result == "AC" ){
            acceptedCount++;
        }
        else if(result == "WA"){
            wrongAnswerCount++;
        }
        else if(result == "TLE"){
            tleCount++;
        }

    }

    void printStats(){
        cout<<"Total submissions in Judge :"<<totalSubmissions<<endl;
        cout<<"Total accepted submissions in Judge :"<<acceptedCount<<endl;
        cout<<"Total wrong submissions in Judge :"<<wrongAnswerCount<<endl;
        cout<<"Total TLE submissions in Judge :"<<tleCount<<endl;
    }

    int getUsersSubmissionCount(string name){
        auto it = userSubmissionCount.find(name);
        if(it!=userSubmissionCount.end()){
            return it->second;
        }
        return 0;
    }

};

//Initialize the eager-loaded singleton instance
JudgeAnalytics JudgeAnalytics::instance;



class Main{

public:
   static void run(){
        JudgeAnalytics& analytics = JudgeAnalytics::getInstance();

        //inserting data
        analytics.recordSubmission("Ankit", "AC");
        analytics.recordSubmission("Lokesh", "WA");
        analytics.recordSubmission("Rohit", "TLE");
        analytics.recordSubmission("Vibha", "AC");
        analytics.recordSubmission("Deepak", "AC");

        cout<<endl;
        cout << "=== Judge Analytics Report ===" << endl;
        analytics.printStats();

        cout << "\nUser-specific Submission Count:" << endl;
        cout << "Ankit: " << analytics.getUsersSubmissionCount("Ankit") << endl;
        cout << "Lokesh: " << analytics.getUsersSubmissionCount("Lokesh") << endl;
        cout << "Rohit: " << analytics.getUsersSubmissionCount("Rohit") << endl;

    
   }

};


int main(){
    Main::run();
    return 0;
}