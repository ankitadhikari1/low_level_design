/*

Imagine we're building a Checkout Service for ecommerce platform:

This version of the CheckoutService tightly couples business logic with object creation. 
It works for a simple scenario but quickly becomes problematic as the application scales or
needs to support multiple payment gateways and invoice formats.

Issues with this design

Tight Coupling:

The CheckoutService directly creates instances of RazorpayGateway, 
PayUGateway, and GSTInvoice, making it dependent on specific implementations.

Violation of the Open/Closed Principle:

Any addition of new payment gateways or invoice types will require modifying the CheckoutService class.

Lack of Extensibility:

Hardcoding limits the ability to support other countries or multiple combinations of payment methods and invoice formats.


*/


#include<iostream>
using namespace std;


class PaymentGateway{
public:
    virtual void processpayment(double amount) = 0;
    virtual ~PaymentGateway(){};
};

class RazorpayGateway : public PaymentGateway{
public:
    void processpayment(double amount) override {
        cout<<"Processing inr payement using razor pay of :"<<amount<<endl;
    }
};

class payUGateway : public PaymentGateway{
public:
    void processpayment(double amount) override {
        cout<<"Processing inr payement using payU of :"<<amount<<endl;
    }
};

class Invoice{
public:
    virtual void generateInvoice() = 0;
    virtual ~Invoice(){};
};

class gstInvoice : public Invoice{
public:
    void generateInvoice()override{
        cout << "Generating GST Invoice for India." << endl;
    }
};


class CheckoutService{
private:
    string gatewayType;

public:
    CheckoutService(const string& gatewayType) : gatewayType(gatewayType){}

    void checkOut(double amount){
        PaymentGateway* paymentGateway;
        if(gatewayType == "razorpay"){
            paymentGateway = new RazorpayGateway();
        }
        else{
            paymentGateway = new payUGateway();
        }

        paymentGateway->processpayment(amount);
        delete paymentGateway;

        Invoice * invoice = new gstInvoice();
        invoice->generateInvoice();
        delete invoice;


    }
};


int main(){
    CheckoutService razorpayServices("razorpay");
    razorpayServices.checkOut(1500.00);
    return 0;
}