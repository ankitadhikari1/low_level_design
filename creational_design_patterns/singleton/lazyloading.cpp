//lazy loading (on demand initialization)


/*
In Lazy Loading, the singleton instance is created only when it's first accessed, rather than at program start. This:
Saves memory if the instance is never used
Requires handling for thread safety (though we’ll keep it simple for single-threaded use here)
*/

/*
-- in this we will create a private instance pointer and move our constructor to private
-- delete copy constructor and assignment operator
--create a static method to get instance this will return the same instance to all the calls
--Initialize the eager-loaded singleton instance to null

when object is initialised for the first time it will create a instance and afterwards 
we will just return already created instance
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
    static JudgeAnalytics * instance;

    //private constructor to prevent external initialisation
    JudgeAnalytics(){
        totalSubmissions = acceptedCount = wrongAnswerCount = tleCount = 0;
    }

    //delete copy constructor and assignment operator
    JudgeAnalytics(const JudgeAnalytics&) = delete;
    JudgeAnalytics& operator=(const JudgeAnalytics&) = delete;

    



    public:

    static JudgeAnalytics* getInstance() {
        if(instance == nullptr){
            instance = new JudgeAnalytics();
        }
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
JudgeAnalytics * JudgeAnalytics::instance = nullptr;



class Main{

public:
   static void run(){
        JudgeAnalytics* analytics = JudgeAnalytics::getInstance();

        //inserting data
        analytics->recordSubmission("Ankit", "AC");
        analytics->recordSubmission("Lokesh", "WA");
        analytics->recordSubmission("Rohit", "TLE");
        analytics->recordSubmission("Vibha", "AC");
        analytics->recordSubmission("Deepak", "AC");

        cout<<endl;
        cout << "=== Judge Analytics Report ===" << endl;
        analytics->printStats();

        cout << "\nUser-specific Submission Count:" << endl;
        cout << "Ankit: " << analytics->getUsersSubmissionCount("Ankit") << endl;
        cout << "Lokesh: " << analytics->getUsersSubmissionCount("Lokesh") << endl;
        cout << "Rohit: " << analytics->getUsersSubmissionCount("Rohit") << endl;

    
   }

};


int main(){
    Main::run();
    return 0;
}