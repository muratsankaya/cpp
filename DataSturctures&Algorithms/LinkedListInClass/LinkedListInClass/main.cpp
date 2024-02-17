/*
  linked-list.cpp
  22S Sec B
 */

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

/*
  display
  length/size
  add, remove at front / back / etc.
  clear
  duplicate
 */

Node* listDuplicate(const Node* headPtr) {
    // edge case
    if (headPtr == nullptr) return nullptr;

    // initialization code
    Node* result = new Node(headPtr->data);
    const Node* p = headPtr->next;
    Node* last = result;

    while (p != nullptr) {
        last->next = new Node(p->data);
        last = last->next;
        p = p->next;
    }

    return result;
}


void listAddTail(Node*& headPtr, int data) {
    if (headPtr == nullptr) {
        headPtr = new Node(data);
    }
    else {
        // find last node
        Node* last = headPtr;
        while (last->next != nullptr) {
            last = last->next;
        }
        // Append the data to that last node
        last->next = new Node(data);
    }

}

void listAdd(Node* where, int data) {
    // create a node for the data;
    // Node* tmp = new Node(data);

    // // Make our node point to the one after the "where" node
    // tmp->next = where->next;

    //Node* tmp = new Node(data, where->next);

    // make where node point to the new one
    //where->next = tmp;

    if (where != nullptr) {
        where->next = new Node(data, where->next);
    }

}

void listDisplayR(Node* headPtr) {
    if (headPtr != nullptr) {
        cout << headPtr->data << ' ';
        //	if (headPtr->next != nullptr) {
        listDisplayR(headPtr->next);
        //	}
    }
}

//void listDisplay(Node* headPtr) const {
void listDisplay(const Node* headPtr) {
    while (headPtr != nullptr) {
        cout << headPtr->data << ' ';
        headPtr = headPtr->next;
    }
    cout << endl;
}

void listDisplay2(const Node* headPtr) {
    const Node* p = headPtr;
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

int listLength(const Node* headPtr) {
    const Node* p = headPtr;
    int count = 0;
    while (p != nullptr) {
        ++count;
        p = p->next;
    }
    return count;
}

void shiftToEnd(Node*& cursor) {
    while (cursor->next) cursor = cursor->next;
}

Node* addList(const vector<Node*>& vectorOfNodePtr) {
    if (vectorOfNodePtr.size() == 0) return nullptr;
    Node* headptr = vectorOfNodePtr[0];
    Node* cursor = headptr;
    for (size_t i = 1; i != vectorOfNodePtr.size(); ++i) {
        shiftToEnd(cursor);
        cursor->next = vectorOfNodePtr[i];
    }
    return headptr;
}


void listAddHead(Node*& headPtr, int data) {
    // // create a node for the data
    // Node* tmp = new Node(data);

    // // made that node point to the old head node
    // tmp->next = headPtr;
    // Node* tmp = new Node(data, headPtr);

    // // make the headPtr point to that node
    // headPtr = tmp;
    headPtr = new Node(data, headPtr);
}


void foo(vector<string> const& ptr){}

int main() {
    int* p = new int[4];
    delete p;
    Node* myList = nullptr;
    //listDisplay(myList);
    char* s = "hello";

    listAddHead(myList, 17);
    myList->next = new Node(28);
    //listDisplay(myList);


    listAddHead(myList, 6);
    //listDisplay(myList);
    Node* myListDuplicate =  listDuplicate(myList);
    listDisplay(myList);
    listDisplay(myListDuplicate);
    vector<Node*> v{ myList, myListDuplicate };
    listDisplay(addList(v));
    listDisplay(myList);
    listDisplay(myListDuplicate);
}