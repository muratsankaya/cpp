/*
    Copy Control with Inheritance
    Sec Base
*/

#include <iostream>
using namespace std;

//class Base {
//public:
//    Base() {
//        cerr << "Base()\n";
//    }
//    Base(const Base& rhs) {
//        cerr << "Base(const Base&)\n";
//    }
//    //~Base() {
//    virtual ~Base() {
//        cerr << "~Base()\n";
//    }
//    Base& operator=(const Base& rhs) {
//        cerr << "Base::operator=(const Base&)\n";
//        return *this;
//    }
//};
//
//class Member {
//public:
//    Member() {
//        cerr << "Member()\n";
//    }
//    ~Member() {
//        cerr << "~Member()\n";
//    }
//    Member(const Member& rhs) {
//        cerr << "Member(const Member&)\n";
//    }
//    Member& operator=(const Member& rhs) {
//        cerr << "Member::operator=(const Member&)\n";
//        return *this;
//    }
//};
//
//class Derived : public Base {
//    Member mem;
//public:
//    //Derived() : Base() {}
//    Derived() { cerr << "Derived()\n"; }
//
//    ~Derived() {
//        cerr << "~Derived()\n";
//    }
//
//    Derived(const Derived& rhs) : Base(rhs), mem(rhs.mem) {
//        cerr << "Derived(const Derived&)\n";
//    }
//
//    Derived& operator=(const Derived& rhs) {
//        //*this Base::= rhs;
//        //(*this).Base::operator=(rhs);
//        //this->Base::operator=(rhs);
//        Base::operator=(rhs);
//
//        mem = rhs.mem;     
//            cerr << "Derived::operator=(const Derived&)\n";
//        return *this;
//    }
//};


//08 Polymorphsm and Constructors

//class Base {
//public:
//    Base() {
//        foo();
//        //this->foo();
//
//    }
//    virtual void foo() const { cout << "Base\n"; }
//    void display() {
//        
//        //this->foo(); 
//        foo();
//        //cout << "this one comes from the the call of base version display->";
//    }
//    void agha() { cout << "Testing for Poly(Base)\n"; }
//};
//
//class Derived : public Base {
//public:
//    Derived(int n) : Base(), x(n) {}
//    void foo() const override { cout << "Derived: x == " << x << endl; }
//    void display() { Base::display(); }
//    void agha() { cout << "Testing for Poly(Derived)\n"; }
//private:
//    int x;
//};

/*
  9.polyNonMember
  22S Sec B
 */

//#include <iostream>
//using namespace std;
//
//class Base {
//public:
//    virtual void display(ostream& os) const {
//        os << "Base";
//    }
//};
//
//ostream& operator<<(ostream& os, const Base& rhs) {
//    //    os << "Base"; 
//    rhs.display(os);
//    return os;
//}
//
//class Derived : public Base {
//public:
//    void display(ostream& os) const override {
//        os << "Derived";
//    }
//};
//
///*
//ostream& operator<<(ostream& os, const Derived& rhs) {
//    //os << "Derived";
//    rhs.display(os);
//    return os;
//}
//*/
//
////=============CLient code===========
//void func(const Base& base) {
//    cout << base << endl;
//    //operator<<(cout, base);
//    //base.operator<<(cout);
//    //    cout.operator<<(base);
//}

/*
  6.hiding.cpp
  22S Sec B
 */

//class Base {
//public:
//    void foo(int n) const { cout << "Base::foo(n)\n"; }
//    void foo() const { cout << "Base::foo()\n"; }
//};
//
//class Derived : public Base {
//public:
//    void foo()  const { cout << "Derived::foo()\n"; }
//    //void foo(int n) const { Base::foo(n); } // Wrapper
//    void foo(int n) const { cout<< "Derived::foo(n)\n"; } // Wrapper
//    using Base::foo;
//};

/*
  6.OverrideVsOverload.cpp
  Demonstrates how the compiler makes the choice for overloading based
  when the paramters are related by inheritance
 */

//class Parent {};
//class Child : public Parent {};
//class Grandchild : public Child {};
//
//void func(Parent& base) { cout << "func(Parent)\n"; }
//void func(Child& derived) { cout << "func(Child)\n"; }
//
//void otherFunc(Parent& base) {
//    func(base);
//}

/*
  6.OverrideVsOverloadV2.cpp

  Demonstrates that the compiler makes the choice for overloading at
  compile time and overriding at run time.
 */

//class Parent {
//public:
//    virtual void whereami() const = 0; /*{
//        cout << "Parent" << endl;
//    }*/
//    /*virtual void whereami() const {
//        cout << "Parent" << endl;
//    }*/
//    /*void whereami() const {
//        cout << "Parent" << endl;
//    }*/
//};
//
//class Child : public Parent {
//public:
//    /*void whereami() const override {
//        cout << "Child!!!" << endl;
//    }*/
//    /*void whereami() const {
//        cout << "Child!!!" << endl;
//    }*/
//};
//
//class Grandchild : public Child {
//public:
//    /*void whereami() const override {
//        cout << "Grandchild!!!" << endl;
//    }*/
//    /*void whereami() const {
//        cout << "Grandchild!!!" << endl;
//    }*/
//};
//
//void func(const Parent& base) { cout << "func(Parent)\n"; }
//void func(const Child& derived) { cout << "func(Child)\n"; }
//
//void otherFunc(Child& base) {
//    func(base);
//    base.whereami();
//}

int main() {
    //cerr << "Derived der;\n"
    //    << "------------\n";
    //Derived der; 
    //// Base() -> Member() -> Derived()

    //cout << "===\n";

    //cerr << "Derived der2(der);\n"
    //    << "------------------\n";
    //Derived der2(der);
    //cout << "===\n";
    //// Base(const Base&) --> Member(const Member&) --> Derived(const Derived&)

    //cerr << "Derived der3 = der;\n"
    //    << "-------------------\n";
    //Derived der3 = der;
    //cout << "===\n";
    //// Base(const Base&) --> Member(const Member&) --> Derived(const Derived&) // This is just writing the copy constructor at another way

    //cerr << "der = der2;\n"
    //    << "-----------\n";
    //der = der2;
    //// Base::operator(const Base& rhs) --> Member::operator(const Member& rhs) --> Derived::operator(const Derived& rhs)
    //cout << "===\n";

    //cerr << "Derived* p = new Derived();\n"
    //    << "delete p;\n"
    //    << "---------------------------\n";
    //Derived* p = new Derived(); // Base() --> Member() --> Derived()
    //delete p; //~Derived() --> ~Member() 

    //cout << "===\n";
    //cerr << "Base* bp = new Derived();\n"
    //    << "delete bp;\n"
    //    << "---------------------------\n";
    //Base* bp = new Derived();
    //delete bp;
    //cout << "===\n";

    /*Derived der(17);
    der.display();*/
    //Base b = Derived(3); //Here is the slicing problem, you are calling the copy constructor you're creatin a copy here !!!!
    //Derived d(4);
    //Base* b2 = &d; 
    ////b.foo(); // Will print derived 
    //b2->foo();
    ////b.agha(); // Since not virtual, will print for base

    //Derived der;
    //cout << der << endl;
    ////operator<<(cout, der);
    //func(der);

    /*Derived der;
    der.foo();
    der.foo(17);*/
    //der.Base::foo(17);

    //Parent parent;
    //func(parent); //Parent version
    //Child child;
    //func(child);//Child version

    //Grandchild gc;
    //func(gc);//Child version

    //otherFunc(child); //Parent version -- Compiler's decision, based on the type of the parameter that otherFunc takes

    //Parent parent;
    //otherFunc(parent); // obvious, hopefully  //func(parent) --> Parent

    //Child child;
    //otherFunc(child); // less obvious? //func(parent) --> Child

    //Grandchild gc;
    //otherFunc(gc); // ok, by now you know what happens //func(parent) --> Child (Since whereami is not overridden in Child there should not be any polymorphsm between Child and GrandChild

    //08 polymorphsm and constructors
    /*Derived der(17);
    Base bas;
    bas.display();
    der.display();*/

}