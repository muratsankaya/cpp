// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

//Task 9
void printList(const list<int>& rhs) {
    //for(list<int>::iterator start = rhs.begin(); ) I got the error massege
    for (list<int>::const_iterator start = rhs.begin(); start != rhs.end(); ++start) cout << *start << ' ';
    cout << endl;
}

//Task 10
void printList2(const list<int>& rhs) {
    //for(list<int>::iterator start = rhs.begin(); ) I got the error massege
    for (int val : rhs) cout << val << ' ';
    cout << endl;
}

//Task 12
list<int>::const_iterator findListVal(const list<int>& rhs, int val) {
    for (list<int>::const_iterator start = rhs.begin(); start != rhs.end(); ++start) {
        if (*start == val) return start;
    } return rhs.end();

}

//Task 13
auto findListVal2(const list<int>& rhs, int val) {
    for (auto start = rhs.begin(); start != rhs.end(); ++start) {
        if (*start == val) return start;
    } return rhs.end();

}

//Task 15
bool isEven(int n) { return n % 2 == 0; }

//Task 16
struct checkForEven {
    bool operator()(int n) { return n % 2 == 0; }
};

//Task 19
list<int>::iterator myFind(list<int>::iterator start, list<int>::iterator end, int val){
    cout << "we are in myFind\n";
    while (start != end) {
        if (*start == val) return start;
        ++start;
    }return end;
}

//Task 20
template<typename T, typename U>
T myFind(T start, T end, U val) {
    cout << "we are in templated myFind\n";
    while (start != end) {
        if (*start == val) return start;
        ++start;
    }return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vectorOfValues{ 3, 2, 1, 4, 6, 5 };
    for (const int val : vectorOfValues) cout << val << ' ';
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> listOfValues(vectorOfValues.begin(), vectorOfValues.end());
    for (const int val : vectorOfValues) cout << val << ' ';
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vectorOfValues.begin(), vectorOfValues.end()); 
    for (const int val : vectorOfValues) cout << val << ' '; cout << endl;
    for (const int val : listOfValues) cout << val << ' ';
    cout << "\n=======\n";

    // 4. print every other element of the vector. ASSUMING the length is odd.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vectorOfValues.size(); i += 2) cout << vectorOfValues[i] << ' ';
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    //for (size_t i = 0; i < listOfValues.size(); i += 2) cout << listOfValues[i];
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::const_iterator start = vectorOfValues.begin(); start != vectorOfValues.end(); start += 2) cout << *start << ' ';
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    int counter = 0;
    for (list<int>::const_iterator start = listOfValues.begin(); start != listOfValues.end(); ++start, ++counter) {
        if (counter % 2 == 0) cout << *start << ' ';
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    listOfValues.sort();
    for (const int val : listOfValues) cout << val << ' ';
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(listOfValues);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(listOfValues);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    cout << "=======\n";
    counter = 0;
    for (auto start = listOfValues.begin(); start != listOfValues.end(); ++start, ++counter) {
        if (counter % 2 == 0) cout << *start << ' ';
    }
    cout << endl;
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::const_iterator where = findListVal(listOfValues, 4);
    if (where != listOfValues.end()) cout << *where << endl;
    //cout << *findListVal(listOfValues, 15) << endl; //can not dereference an end list iterator
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    where = findListVal2(listOfValues, 5);
    if (where != listOfValues.end()) cout << *where << endl;

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    list<int>::const_iterator whereL = find(listOfValues.begin(), listOfValues.end(), 4);
    if (whereL != listOfValues.end()) cout << *whereL << endl;
    //cout << *find(listOfValues.begin(), listOfValues.end(), 15) << endl; //can not dereference an end list iterator

    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    vector<int>::const_iterator whereV = find_if(vectorOfValues.begin(), vectorOfValues.end(), isEven);
    if (whereV != vectorOfValues.end()) cout << *whereV << endl;

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    checkForEven checkEven; //Functor
    whereV = find_if(vectorOfValues.begin(), vectorOfValues.end(), checkEven);
    if (whereV != vectorOfValues.end()) cout << *whereV << endl;

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    whereV = find_if(vectorOfValues.begin(), vectorOfValues.end(), [](int n) {return n % 2 == 0; });
    if (whereV != vectorOfValues.end()) cout << *whereV << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arrayOnTheHeap = new int[vectorOfValues.size()];
    copy(vectorOfValues.begin(), vectorOfValues.end(), arrayOnTheHeap);
    for (size_t i = 0; i < vectorOfValues.size(); ++i) cout << arrayOnTheHeap[i] << ' '; //I think the compiler gets confused because I'm using vector.size()
    cout << endl;
    int* whereA = find(arrayOnTheHeap, arrayOnTheHeap + vectorOfValues.size(), 5);
    if (whereA != arrayOnTheHeap + vectorOfValues.size() ) cout << *where;
    delete[] arrayOnTheHeap;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    whereL = myFind(listOfValues.begin(), listOfValues.end(), 4);
    if (whereL != listOfValues.end()) cout << *whereL << endl;

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    whereV = myFind(vectorOfValues.begin(), vectorOfValues.end(), 4);
    if (whereV != vectorOfValues.end()) cout << *whereV << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs) {
        cout << "File could not open!" << endl;
        exit(1);
        ifs.close();
    }
    string token;
    vector<string> vectorOftokens;
    while (ifs >> token) {
        vector<string>::iterator where = find(vectorOftokens.begin(), vectorOftokens.end(), token);
        if (where == vectorOftokens.end()) vectorOftokens.push_back(token);
    }
    ifs.close();
    
    cout << vectorOftokens.size() << endl;
    for (const string& word : vectorOftokens) {
        cout << word << ' ';
    }
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set

    cout << "Task 22:\n";
    ifs.open("pooh-nopunc.txt");
    set<string> setOftokens;
    while (ifs >> token) {
        setOftokens.insert(token);
    }
    ifs.close();
    cout << setOftokens.size() << endl;
    for (const string& word : setOftokens) {
        cout << word << ' ';
    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifs.open("pooh-nopunc.txt");
    map <string, vector<int>> wordMap;
    int counterForToken = 0;
    while (ifs >> token) {
        wordMap[token].push_back(counterForToken);
        ++counterForToken;
    }
    ifs.close();
    cout << wordMap.size() << endl;
    for (const pair<string, vector<int>>& elem : wordMap) {
        cout << elem.first << '\t';
        for (int x : elem.second) cout << x << ' ';
    }
    cout << "=======\n";
}
