#include <cstdlib>
#include <iostream>
using namespace std;

//template <typename T>
class List {
    friend ostream& operator<<(ostream& os, const List& rhs);
    struct Node {
        Node() { data = 0; next = nullptr; prev = nullptr; }
        Node(int val, Node* prev = nullptr, Node* next = nullptr) : data(val), next(next), prev(prev) {}
        int data;
        Node* next;
        Node* prev;
    };
    
public:
    class iterator {
        friend List;
    public:
        iterator(Node* nodeptr) : nodeptr(nodeptr) {}
        iterator& operator++() { // Isn't it better if it crashes ? 
            //if(nodeptr->next) nodeptr = nodeptr->next;
            nodeptr = nodeptr->next;
            return *this;
        }
        iterator& operator--() {// Isn't it better if it crashes ?
            //if(nodeptr->next) nodeptr = nodeptr->prev;
            nodeptr = nodeptr->prev; 
            return *this;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.nodeptr != rhs.nodeptr;
        }
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.nodeptr == rhs.nodeptr;
        }
        int& operator*() { return nodeptr->data; }
    private:
        Node* nodeptr;
    };
    class const_iterator {
        friend List;
    public:
        const_iterator(Node* nodeptr) : nodeptr(nodeptr) {}
        const_iterator& operator++() { // Isn't it better if it crashes ? 
            //if(nodeptr->next) nodeptr = nodeptr->next;
            nodeptr = nodeptr->next;
            return *this;
        }
        const_iterator& operator--() {// Isn't it better if it crashes ?
            //if(nodeptr->next) nodeptr = nodeptr->prev;
            nodeptr = nodeptr->prev;
            return *this;
        }
        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
            return lhs.nodeptr != rhs.nodeptr;
        }
        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
            return lhs.nodeptr == rhs.nodeptr;
        }
        int operator*() { return nodeptr->data; }
    private:
        const Node* nodeptr;
    };
    List() {
        theSize = 0;
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
    }
    /*List(const List& rhs) {
        theSize = 0;
        header = new Node();
        trailer = new Node();
        header->next = trailer;
        trailer->prev = header;
        Node* rhscursor = rhs.header->next;
        while (theSize != rhs.theSize) {
            push_back(rhscursor->data);
            rhscursor = rhscursor->next;
        }
    }*/
    List(const List& rhs){
        trailer = new Node(); header = new Node(); theSize = 0;
        header->next = trailer; trailer->prev = header;
        Node* cursor = rhs.header->next;
        while (cursor != rhs.trailer) {
            addToTail(cursor->data);
            cursor = cursor->next;
        }
    }
    void addToTail(int data) {
        trailer->prev->next = new Node(data, trailer->prev, trailer);
        trailer->prev = trailer->prev->next;
        ++theSize;
    }
    List& operator=(const List& rhs) {
        if (this != &rhs) {
            deleteAll();
            Node* cursor = rhs.header->next;
            while (cursor != rhs.trailer) {
                addToTail(cursor->data);
                cursor = cursor->next;
            }
        }return *this;
    }
    void deleteAll() {
        Node* cursor = header->next;
        while (cursor != trailer) {
            Node* toDelete = cursor;
            cursor = cursor->next; 
            delete toDelete;
        }
        theSize = 0; header->next = trailer; trailer->prev = header;
    }
    ~List() {  deleteAll(); delete header; delete trailer; }
    //List& operator=(const List& rhs) {
    //    while (theSize != 0) {
    //        pop_back();
    //    }
    //    Node* rhscursor = rhs.header->next;
    //    while (theSize != rhs.theSize) {
    //        push_back(rhscursor->data);
    //        rhscursor = rhscursor->next;
    //    } 
    //    return *this;
    //}
    //~List() {
    //    cout << "~List()\n";
    //    while (theSize != 0) pop_back(); //When theSize hits 0, the header and the trailer won't be deleted
    //    delete header; delete trailer; 
    //}
    void push_back(int data) {
        Node* newNode = new Node(data, trailer->prev, trailer); //I will lose access to the orig pointer so it doesn't matter if I create a copy of the pointer
        trailer->prev->next = newNode;
        trailer->prev = newNode;
        ++theSize;
    }
    void pop_back() { //I want it to crash in the case the user calls it on an empty list
        //if (theSize == 0) return; // I think its better if it crashes
        Node* toDelete = trailer->prev;
        trailer->prev->prev->next = trailer;
        trailer->prev = trailer->prev->prev;
        delete toDelete;
        --theSize;
    }
    void push_front(int data) {
        Node* newNode = new Node(data, header->next->prev, header->next);
        header->next->prev = newNode;
        header->next = newNode;
        ++theSize;
    }
    void pop_front() {
        Node* toDelete = header->next; //I will lose access to the orig pointer so it doesn't matter if I create a copy of the pointer
        header->next->next->prev = header;
        header->next = header->next->next;
        delete toDelete;
        --theSize;
    }
    int front() const { return header->next->data; }//It will act in an undefined behaviour when called on a empty list which I think makes more sense than returning 0
    int& front() { return header->next->data; }//It will act in an undefined behaviour when called on a empty list which I think makes more sense than returning 0
    int back() const { return trailer->prev->data; }//It will act in an undefined behaviour when called on a empty list which I think makes more sense than returning 0
    int& back() { return trailer->prev->data; }//It will act in an undefined behaviour when called on a empty list which I think makes more sense than returning 0
    size_t size() const { return theSize; }
    void clear() { 
        while (theSize != 0) {
            pop_back();
            /*Node* toDelete = header->next;
            header->next = header->next->next;
            delete toDelete;*/
        } /*trailer->prev = header; theSize = 0;*/
    }
    int operator[](size_t i) const { //I want it to crash if it goes out of range
        Node* cursor = header->next;
        for (size_t index = 0; index < i; ++index) {
            cursor = cursor->next;
        } return cursor->data;
    }
    int& operator[](size_t i) { //I want it to crash if it goes out of range
        Node* cursor = header->next;
        for (size_t index = 0; index < i; ++index) {
            cursor = cursor->next;
        } return cursor->data;
    }
    iterator begin() { return iterator(header->next); }
    iterator end() { return iterator(trailer); }
    const_iterator begin() const { return const_iterator(header->next); } //const_iterator returns the data by a copy which will lead the compiler to give you an error when you will try to iterate with a refernce to the data, thus if you hold a const pointer to an integer this will moreover ensure you to return a copy on your derefence operator
    const_iterator end() const { return const_iterator(trailer); }
    /*iterator begin() const { return iterator(header->next); } //Uncomment these and comment the const_iterator version you will see that in the printList function it won't disable the user from editing the data. 
    iterator end() const { return iterator(trailer); }*/
    iterator insert(const iterator& iter, int data) {
        Node* origPrev = iter.nodeptr->prev;
        Node* newNode = new Node(data, origPrev, iter.nodeptr);
        iter.nodeptr->prev = newNode;
        origPrev->next = newNode;
        ++theSize;
        return iterator(newNode);
    }
    iterator erase(iterator iter) { //The code is being used as 
        Node* toDelete = iter.nodeptr;
        iter.nodeptr->prev->next = iter.nodeptr->next;
        iter.nodeptr->next->prev = iter.nodeptr->prev;
        delete toDelete;
        --theSize;
        return ++iter;
    }
private:
    size_t theSize;
    Node* header;
    Node* trailer;
};

ostream& operator<<(ostream& os, const List& rhs) {
    List::Node* start = rhs.header->next; //creating a copy to avoid changing the header
    while (start != rhs.trailer) {
        os << start->data << ' '; start = start->next;
    } return os;
}

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
 //void changeFrontAndBackConst(const List& theList){ //Yes it does not compile
 //    theList.front() = 17;
 //    theList.back() = 42;
 //}

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

//void printList(const List& list) {
//    for (int& val : list) {
//        cout << val;
//    }
//}

int main() {
    //// Task 1
    //cout << "\n------Task One------\n";
    List myList;
    ////myList.pop_back(); It crashes as I expected
    //cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    //for (int i = 0; i < 10; ++i) {
    //    cout << "myList.push_back(" << i*i << ");\n";
    //    myList.push_back(i*i);
    //    printListInfo(myList);
    //}
    //cout << "===================\n";
    //
    //cout << "Modify the first and last items, and display the results\n";
    //changeFrontAndBack(myList);
    //printListInfo(myList);
    //cout << "===================\n";

    //cout << "Remove the items with pop_back\n";
    //while (myList.size()) {
    //    printListInfo(myList);
    //    myList.pop_back();
    //}
    //cout << "===================\n";

    //// Task 2
    //cout << "\n------Task Two------\n";
    //cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    //for (int i = 0; i < 10; ++i) {
    //    cout << "myList2.push_front(" << i*i << ");\n";
    //    myList.push_front(i*i);
    //    printListInfo(myList);
    //}
    //cout << "===================\n";
    //cout << "Remove the items with pop_front\n";
    //while (myList.size()) {
    //    printListInfo(myList);
    //    myList.pop_front();
    //}
    //printListInfo(myList);
    //cout << "===================\n";

    //// Task 3
    //cout << "\n------Task Three------\n";
    //cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    //for (int i = 0; i < 10; ++i) {
    //    myList.push_back(i*i);
    //}
    //printListInfo(myList);
    //cout << "Now clear\n";
    //myList.clear();
    //cout << "Size: " << myList.size() << ", list: " << myList << endl;
    //cout << "===================\n";

    //// Task 4
    //cout << "\n------Task Four------\n";
    //cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    //for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    //cout << "Display elements with op[]\n";
    //for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    //cout << endl;
    //cout << "Add one to each element with op[]\n";
    //for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    //cout << "And print it out again with op[]\n";
    //for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    //cout << endl;
    //cout << "Now calling a function, printListSlow, to do the same thing\n";
    //printListSlow(myList);
    //cout << "Finally, for this task, using the index operator to modify\n"
    //     << "the data in the third item in the list\n"
    //     << "and then using printListSlow to display it again\n";
    //myList[2] = 42;
    //printListSlow(myList);
    //

    //// Task 5
    //cout << "\n------Task Five------\n";
    //cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    //myList.clear();
    //for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    //printListInfo(myList);
    //cout << "Now display the elements in a ranged for\n";
    //for (int x : myList) cout << x << ' ';
    //cout << endl;
    //cout << "And again using the iterator type directly:\n";
    //// Note you can choose to nest the iterator class or not, your choice.
    ////for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    //for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    //    cout << *iter << ' ';
    //}
    //cout << endl;
    //cout << "WOW!!! (I thought it was cool.)\n";
    //
    //// Task 6
    //cout << "\n------Task Six------\n";
    //cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    //myList.clear();
    //for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    //printListInfo(myList);
    //cout << "Filling an empty list with insert at begin(): "
    //     << "i*i for i from 0 to 9\n";
    //myList.clear();
    //for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    //printListInfo(myList);
    //// ***Need test for insert other than begin/end***
    //cout << "===================\n";

    //// Task 7
    //cout << "\n------Task Seven------\n";
    //cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    //myList.clear();
    //for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    //cout << "Erasing the elements in the list, starting from the beginning\n";
    //while (myList.size()) {
    //    printListInfo(myList);
    //    myList.erase(myList.begin());
    //}
    //// ***Need test for erase other than begin/end***
    //cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";

}
