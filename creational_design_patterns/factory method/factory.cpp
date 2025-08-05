/*

Factory Pattern
The Factory Pattern is a creational design pattern that provides an interface 
for creating objects but allows subclasses to alter the type of objects that will be created.

In simpler terms:
Rather than calling a constructor directly to create an object, 
we use a factory method to create that object based on some input or condition.

When Should You Use It?
We can use the Factory Pattern when:
The client code needs to work with multiple types of objects.
The decision of which class to instantiate must be made at runtime.
The instantiation process is complex or needs to be controlled.



Basic Structure of Factory Pattern
The Factory Pattern typically consists of the following components:

Product: It is an interface or abstract class that defines the methods the product must implement.
Concrete Products: The concrete classes that implement the Product interface.
Factory: A class with a method that returns different concrete products based on input.

*/


#include <iostream>
#include <string>
using namespace std;

// Interface 
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
    virtual ~Shape() {}
};

// Class implementing the Shape Interface
class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

// Class implementing the Shape Interface
class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing Square" << endl;
    }
};

// Factory Class
class ShapeFactory {
public:
    /* Method that takes the type of shape as input 
    and returns the corresponding object */
    Shape* getShape(const string& shapeType) {
        if (shapeType == "CIRCLE") {
            return new Circle();
        } else if (shapeType == "SQUARE") {
            return new Square();
        }
        return nullptr;
    }
};

// Driver code
int main() {
    // Object of ShapeFactory is initialized
    ShapeFactory shapeFactory;

    // Get a Circle object and call its draw method
    Shape* shape1 = shapeFactory.getShape("CIRCLE");
    if (shape1) shape1->draw();

    // Get a Square object and call its draw method
    Shape* shape2 = shapeFactory.getShape("SQUARE");
    if (shape2) shape2->draw();

    // Clean up dynamic memory
    delete shape1;
    delete shape2;

    return 0;
}


