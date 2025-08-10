/*

for this we will create a brugerBuilder class which is subclass
of burgerMeal class it will have all the configuration we need
and reutrn the object to the constructor of burger meal class by 
which burger meal class will take all the configuration and create the object
without flooding the parameter

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


    class BurgerBuilder{
        private:
        //mandatory
        string bun;
        string patty;

        //optional
        vector<string> toppings;
        bool cheese;
        string sides;

        friend class BurgerMeal;

        public:

        BurgerBuilder(string bun , string patty){
            this->bun = bun;
            this->patty = patty;
        }

        BurgerBuilder& withTopping(vector<string>toppings){
            this->toppings = toppings;
            return *this;
        }

        BurgerBuilder& withCheese(bool cheese){
            this->cheese = cheese;
            return *this;
        }

        BurgerBuilder& withSides(string sides){
            this->sides = sides;
            return *this;
        }

        BurgerMeal build(){
            return BurgerMeal(*this);
        }

    };


    BurgerMeal(const BurgerBuilder& builder){
        this->bun = builder.bun;
        this->patty = builder.patty;
        this->toppings = builder.toppings;
        this->cheese = builder.cheese ;
        this->sides = builder.sides;
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

    //plain burger
    BurgerMeal plainBurger = BurgerMeal::BurgerBuilder("wheat","veg");

    //burger with cheese
    BurgerMeal burgerWithCheese = BurgerMeal::BurgerBuilder("wheat","veg").withCheese(true).build();

    //burger with loaded configuration

    vector<string>toppings = {"berries","chikcken"};
    BurgerMeal loadedBurger = BurgerMeal::BurgerBuilder("wheat","chicken").withCheese(true).withSides("crispy").withTopping(toppings).build();


    //print all burgers

    cout<<"plain burger"<<endl;
    plainBurger.printBurger();
    cout<<endl;

    cout<<"cheese burger"<<endl;
    burgerWithCheese.printBurger();
    cout<<endl;

    cout<<"loaded burger"<<endl;
    loadedBurger.printBurger();
    cout<<endl;
    




    return 0;
}