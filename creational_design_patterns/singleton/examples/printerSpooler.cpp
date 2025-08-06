//printer spooler using eager loading

#include<iostream>
#include<queue>
using namespace std;


class Printer{

    private:

    //printer with id and print
    queue<pair<int,string>>q;

    static Printer instance;

    //private constructor
    Printer(){}


    public:

    static Printer&  getInstance(){
        return instance;
    }

    void sendToPrint(int id ,string & text){
        q.push({id,text});
    }

    void print(int size = 1){
        //size tells how much files we want to print
        if(size > q.size()){
            size = q.size();
        } 


        for(int i=0;i<size;i++){
            cout<<"\nid :"<<q.front().first<<" "<<"text :"<<q.front().second;
            q.pop();
        }
    }

    //checks all the current id's inside the spooler
    void checkStatus(){
        int size = q.size();
        if(size == 0){
            cout<<"spooler is empty :("<<endl;
            return ;
        }
        for(int i=0;i<size;i++){
            auto val = q.front();
            cout<<"id :"<<val.first<<endl;
            q.pop();
            q.push(val);
        }
    }


};

Printer Printer::instance;


class Main{

    public:
    static void run(){
        //for user 1
        Printer& obj1 = Printer::getInstance();
        Printer& obj2 = Printer::getInstance();
        Printer& obj3 = Printer::getInstance();
        Printer& obj4 = Printer::getInstance();

        string first = "hii this is first file to print";
        obj1.sendToPrint(1,first);

        string second = "hii this is second file to print";
        obj2.sendToPrint(2,second);

        string third = "hii this is third file to print";
        obj3.sendToPrint(3,third);

        string fourth = "hii this is fourth file to print";
        obj4.sendToPrint(4,fourth);


        obj1.checkStatus();

        obj2.print(3);





    


    }

};

int main(){
    Main::run();
    return 0;
}