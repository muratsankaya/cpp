#include <string>
#include "Polynomial.h"
using namespace std;

struct Polynomial::Node{
    Node(int coef = 0, Node* next = nullptr) : coef(coef), next(next) {}
	Node* next;
    int coef;
};
Polynomial::Polynomial() { headptr = new Node(); degree = 0; } 
Polynomial::Polynomial(const vector<int>& vectorOfCoefs) {
    if( vectorOfCoefs.size() == 0 ) { headptr = new Node(); degree = 0; } //For the case where the user inputs an empty vector
    else {
        headptr = new Node(vectorOfCoefs[0]); degree = 0;
        Node* cursor = headptr; //creating a copy of the headptr
        for (size_t i = 1; i < vectorOfCoefs.size(); ++i) { // I'm staring the loop from index 1
            cursor->next = new Node(vectorOfCoefs[i]);
            cursor = cursor->next;
            ++degree;
        }
        removeZeros(); //For the case where highest degrees are zeros   
    }
}
Polynomial::Polynomial(const Polynomial& rhs) { //Instead of doing the same opeartions twice in copy const and operator= I created a deepCopy method
    deepCopy(rhs);
}
Polynomial::~Polynomial() { removeAll(); }
Polynomial& Polynomial::operator=(const Polynomial& rhs) { //Instead of doing the same opeartions twice in copy const and operator= I created a deepCopy method
    if (this != &rhs) {
        removeAll();
        deepCopy(rhs);
    } return *this;
}
void Polynomial::deepCopy(const Polynomial& rhs) {
    degree = rhs.degree;
    headptr = new Node(*rhs.headptr);
    Node* cursor = headptr;
    const Node* rhscursor = rhs.headptr->next;
    while (rhscursor) { 
        cursor->next = new Node(*rhscursor);
        cursor = cursor->next; rhscursor = rhscursor->next;
    }
}
void Polynomial::removeAll() {
    while (headptr) { //I don't care here that the headptr is changing I will anyway reset it or won't use it anymore
        Node* toDelete = headptr;
        headptr = headptr->next;
        delete toDelete;
    }
}
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* cursor = headptr;
    const Node* rhscursor = rhs.headptr;
    //First I will have to match degrees to add coefs
    if (degree < rhs.degree) { //I could have created an insert method, which would make the code more readable, but would run in quadratic time, this is a linear time solution
        headptr = new Node(*rhscursor); ++degree; rhscursor = rhscursor->next;
        Node* tempcursor = headptr;
        while (degree != rhs.degree) {
            tempcursor->next = new Node(*rhscursor); ++degree;
            tempcursor = tempcursor->next; rhscursor = rhscursor->next;
        }
        tempcursor->next = cursor; //Here the sequence connects with prev headptr
    }
    else {
        for (int counter = 0; counter != degree - rhs.degree; ++counter) {
            cursor = cursor->next;
        }
    }
    while(cursor){ //After I match the degrees both cursors will go out of range at the same time
        cursor->coef += rhscursor->coef;
        cursor = cursor->next; rhscursor = rhscursor->next;
    }
    removeZeros(); //For the case where the leading degrees has 0 ceof 
    return *this;
}
int Polynomial::evaluate(int input) {
    int result = 0;
    int degreeToEvaluate = degree;
    const Node* cursor = headptr;
    while (cursor) {
        result += power(input, degreeToEvaluate) * (cursor->coef);
        --degreeToEvaluate; 
        cursor = cursor->next;
    }
    return result;
}

void Polynomial::removeZeros() {
    while (degree != 0 && headptr->coef == 0) { //We don't want to remove the case of zero polynomial, therefore I have to check for degree
        Node* toDelete = headptr;
        headptr = headptr->next;
        delete toDelete; 
        --degree; 
    }
}
int Polynomial::power(int val, int degree) {
    int result = 1;
    while (degree != 0) {
        result *= val; --degree;
    } return result;
}

ostream& operator<<(ostream& os, const Polynomial& rhs) {
    const Polynomial::Node* cursor = rhs.headptr;
    int degree = rhs.degree;
    if (cursor->coef == 0) { os << "0"; return os; } //The zero polynomial case
    else {
        if (degree != 0) {
            if (cursor->coef == -1) os << '-'; //I would need to display the negative sign if the highest degree coef is -1
            if (cursor->coef != 1 && cursor->coef != -1) os << cursor->coef;
            (degree != 1 ? os << "x^" << degree : os << "x");
        }
        else os << cursor->coef;
    }
    cursor = cursor->next; --degree;
    while (cursor) {
        if (cursor->coef != 0) {
            (cursor->coef < 0 ? os << " - " : os << " + ");
            if (degree != 0) {
                if (cursor->coef != 1 && cursor->coef != -1) (cursor->coef < 0 ? os << cursor->coef * -1 : os << cursor->coef);
                (degree != 1 ? os << "x^" << degree : os << "x");
            }
            else (cursor->coef < 0 ? os << cursor->coef * -1 : os << cursor->coef);
        }
        cursor = cursor->next; --degree;
    }
    return os;
}
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial res = lhs;
    res += rhs;
    return res;
}
bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree == rhs.degree) {
        const Polynomial::Node* lhscursor = lhs.headptr;
        const Polynomial::Node* rhscursor = rhs.headptr;
        while (lhscursor) { //Again if degrees are equal they will got out of range at the same time
            if (lhscursor->coef != rhscursor->coef) return false;
            lhscursor = lhscursor->next; rhscursor = rhscursor->next;
        }return true;
    } return false;
}
bool operator!=(const Polynomial& lhs, const Polynomial& rhs) { return !(lhs == rhs); }