/*

imagine i have a restro which sells burger 
burger is made up of burger and patty
cheese , toppings , etc etc are other things which customer can tell us he require or not

so , if i have a constructor which make burger object , so i have to make multiple constructor
with these configuration 

this is called constructor telescoping anti pattern - in this we create multiple
loaded constructor each with one more optional parameter than the last. 

eg - 

class BurgerMeal {
    public BurgerMeal(String bun, String patty) { ... }
    public BurgerMeal(String bun, String patty, boolean cheese) { ... }
    public BurgerMeal(String bun, String patty, boolean cheese, String side) { ... }
    public BurgerMeal(String bun, String patty, boolean cheese, String side, String drink) { ... }
}

or 

if i have one constructor i have to give multiple parameter and set them default ,
imagine there are 100 + customizations
so we have to flood the parameters with all the customization

there for we use builder pattern


below code is not using builder pattern


*/


#include<iostream>
#include<vector>
using namespace std;


class BurgerMeal{
    private:
    //mandatory
    string bun;
    string patty;

    //optional
    vector<string> toppings;
    bool cheese;
    string sides;

    public:

    BurgerMeal(string bun , string patty , vector<string>toppings , bool cheese , string sides){
        this->bun = bun;
        this->patty = patty;
        this->toppings = toppings;
        this->cheese = cheese ;
        this->sides = sides;
    }

    void printBurger(){
        cout<<"bun :"<< this->bun<<endl;
        cout<<"patty :"<< this->patty<<endl;
        cout<<"toppings :";
        for(auto & it : toppings){
            cout<<it<<" ";
        }
        cout<<endl;
        cout<<"cheese :"<< this->cheese<<endl;
        cout<<"sides :"<< this->sides<<endl;
    }


};


int main(){
    BurgerMeal burgerMeal("wheat","veg",{},true,"");
    burgerMeal.printBurger();
    return 0;
}