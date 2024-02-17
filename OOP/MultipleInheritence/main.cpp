#include <iostream>
#include <vector>
using namespace std;

//class PrintedMaterial {
//public:
//    //PrintedMaterial(unsigned numberOfPages) : numberOfPages(numberOfPages) {}
//    //void displayNumPages() const { cout << numberOfPages; }
//    /*friend ostream& operator<<(ostream& os, const PrintedMaterial& rhs) {
//        cout << rhs.numberOfPages << endl;
//        return os;
//    }*/
//    unsigned getNumOfPages() const { return numberOfPages; }
//private:
//    unsigned numberOfPages = 0;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//    //Magazine(unsigned num) : PrintedMaterial(num){}
//private:
//};
//
//class Book : public PrintedMaterial {
//public:
//    //Book(unsigned num) : PrintedMaterial(num) {}
//private:
//};
//
//class TextBook : public Book {
//public:
//    //TextBook(unsigned num) : Book(num){}
//private:
//};
//
//class Novel : public Book {
//public:
//    //Novel(unsigned num):  Book(num) {}
//private:
//};
//
//ostream& operator<<(ostream& os, const PrintedMaterial& rhs) {
//    cout << rhs.getNumOfPages() << endl;
//    return os;
//}

//class PrintedMaterial {
//public:
//    PrintedMaterial(unsigned numPages)
//        : numOfPages(numPages)
//    {}
//    virtual void displayNumPages() const =  0;//{ cout << numOfPages << endl; }
//    unsigned getNumberOfPages() const { return numOfPages; }
//private:
//    unsigned numOfPages;
//};
//
//class Magazine : public PrintedMaterial {
//public:
//    Magazine(unsigned numPages)
//        : PrintedMaterial(numPages)
//    {}
//    virtual void displayNumPages() const override { cout << PrintedMaterial::getNumberOfPages << endl; }
//private:
//};
//
//class Book : public PrintedMaterial {
//public:
//    Book(unsigned numPages)
//        : PrintedMaterial(numPages)
//    {}
//    
//private:
//};
//
//class TextBook : public Book {
//public:
//    TextBook(unsigned numPages, unsigned numIndxPgs)
//        : Book(numPages),
//        numOfIndexPages(numIndxPgs)
//    {}
//    void displayNumPages() const {
//        cout << "Pages: ";
//        PrintedMaterial::displayNumPages();
//        cout << "Index pages: ";
//        cout << numOfIndexPages << endl;
//    }
//
//    void toSeeIfWillCall() { cout << "Just to try\n"; }
//
//private:
//    unsigned numOfIndexPages;
//};
//
//class Novel : public Book {
//public:
//    Novel(unsigned numPages)
//        : Book(numPages)
//    {}
//private:
//};
//
//void printMaterial(const PrintedMaterial& rhs) {
//    rhs.displayNumPages();
//    cout << endl;
//}

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
        : numOfPages(numPages)
    {}

    virtual void displayNumPages() const = 0;

private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
        : PrintedMaterial(numPages)
    {}

    // virtual - NOTE even without writing "virtual"
    // again, this overriden method IS virtual
    // viruality cannot be removed once installed
    // Also note that the = 0 has is not there
    void displayNumPages() const {
        cout << "Hi, I'm a Magazine object stored\n"
            << "(but I can't know that I am being\n"
            << "stored (by pointer) in a vector of\n"
            << "PrintedMaterial pointers!\n";
        PrintedMaterial::displayNumPages();
        cout << "(and I'm very glossy!\n";
    }

private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
        : PrintedMaterial(numPages)
    {}

private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs)
        : Book(numPages),
        numOfIndexPages(numIndxPgs)
    {}

    void displayNumPages() const {
        cout << "\nThis is a textbook.\n";
        cout << "It is a very boring textbook.\n";
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
        cout << "Index pages: ";
        cout << numOfIndexPages << endl;
    }

private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
        : Book(numPages)
    {}
    void displayNumPages() const {
        cout << "\nThis is the story of a very\n"
            << " interesting programmer's quest\n"
            << "  to understand inheritance.\n"
            << "   The journey is just beginning\n"
            << "    and already the journeyman\n"
            << "      hacker, no - not a hacker! -\n"
            << "         a programmer who reads, and\n"
            << "             studies and understands code\n"
            << "                 Hackers steal and don't even\n"
            << "                      try to understand what they stole\n"
            << "                           before using it.\n"
            << "\n       ...But I digress.\n"
            << "\nThis novel is quite long, there\n"
            << "being this number of pages:\n"
            << "=====================================\n"
            << "                 ";
        PrintedMaterial::displayNumPages();
        cout << "=====================================\n"
            << "Whew!\n"
            << " but there is an exciting\n"
            << "  programming adventure on every\n"
            << "   single one of them!\n"
            << "    And now, let's let the quest continue..."
            << endl << endl << endl;
    }

private:
};

// note that here, reference to PrintedMaterial is the parameter type
// so now we can use the dot member operator (the .)  if use the ->
// operator, that's not going to work (try it!)
void displayNumberOfPages(const PrintedMaterial& anyPM) {
    anyPM.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);
    //PrintedMaterial material(32);
    /*printMaterial(material);
    printMaterial(text);*/
    text.displayNumPages();
    //novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";
    cout << "\nA PrintedMaterial material object!\n";
    //PrintedMaterial pm(2345); PrintedMaterial class is now a virtual class
    //pm.displayNumPages();
    cout << "\nA PrintedMaterial variable containing a TextBook value\n";
    //pm = text; // like putting a Textbook into a PrintedMaterial
    //pm.displayNumPages();
    cout << "Try using pointer to base type\n";
    PrintedMaterial* pmPtr;
    pmPtr = &text;
    cout << "Now with the virtual mechanism involved\n";
    //pmPtr->displayNumPages(); // this won't work because we did not declare the display method as virtual method
    pmPtr->displayNumPages(); //I called it a virtual now it should work!
    TextBook* txtPtr = &text;
    //txtPtr->toSeeIfWillCall(); This was for me to see if it is the whole derived class(when we use pointers of the type of the base)
    vector<PrintedMaterial*> vectorOfPrintedMaterials;
    vectorOfPrintedMaterials.push_back(&text);
    vectorOfPrintedMaterials.push_back(&novel);
    vectorOfPrintedMaterials.push_back(&mag);
    for (const PrintedMaterial* ptr : vectorOfPrintedMaterials) {
        ptr->displayNumPages();
    }
}


// tester/modeler code
//int main() {
//    /*TextBook text(40);
//    Novel novel(300);
//    Magazine mag(55);*/
//    TextBook text;
//    Novel novel;
//    Magazine mag;
//    cout << novel << endl;
//}
