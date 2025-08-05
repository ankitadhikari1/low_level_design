/*
In this code we will se a judge Analytics class which will keep track of all the 
submissions and track accepted , wrong , tle submissions of users 

it does not follow singleton pattern so whenever a new object is initiated
it will create a new instance 
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



    public:
    JudgeAnalytics(){
        totalSubmissions = acceptedCount = wrongAnswerCount = tleCount = 0;
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



class Main{

public:
   static void run(){
        JudgeAnalytics analytics;

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
        cout << "Alice: " << analytics.getUsersSubmissionCount("Ankit") << endl;
        cout << "Bob: " << analytics.getUsersSubmissionCount("Lokesh") << endl;
        cout << "Charlie: " << analytics.getUsersSubmissionCount("Rohit") << endl;

    
   }

};


int main(){
    Main::run();
    return 0;
}