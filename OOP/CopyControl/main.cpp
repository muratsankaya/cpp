#include <string>
#include <iostream>
using namespace std;

// 
// Position class
// 
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


// 
// Directory class
// 
class Directory {
    // 
    // nested Entry class
    // 
    class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs) {
	    os << rhs.name << ' ' << rhs.room
	       << ' ' << rhs.phone << ", " << *rhs.pos;
	    return os;
	}
    public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
	    : name(name), room(room), phone(phone), pos(&position) {
	}
	const string& getName() const { return name; }
	unsigned getPhone() const { return phone; }
    private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    // ...
    friend ostream& operator<<(ostream& os, const Directory& directory) {
        os << "Directory: " << directory.company << endl;
        for (size_t i = 0; i < directory.size; ++i) {
            os << *(directory.entries[i]) << endl;
        }
        return os;
    }

public:
    // Of course the first function you need to write for this (or
    // any) class is...
    Directory(const string& name) : size(0), capacity(1), company(name) {
        entries = new Entry * [capacity];
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!
            Entry** oldentries = entries;
            capacity *= 2;
            entries = new Entry * [capacity];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = oldentries[i];
            }
            delete[] oldentries;
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    ~Directory() {
        cout << "Deleting entries!" << endl;
        for (size_t i = 0; i < size; ++i) {
            delete entries[i];
        }
        delete[] entries;
    }

    Directory(const Directory& directory) : size(directory.size), capacity(directory.capacity), company(directory.company) {
        cout << "Initilazing a copy!" << endl;
        entries = new Entry * [capacity];
        for (size_t i = 0; i < size; ++i) {
            entries[i] = new Entry (* directory.entries[i]);
        }
    }

    Directory& operator=(const Directory& directory) {
        cout << "Creating a copy of an already constructed object!" << endl;
        if (this != &directory) {
            for (size_t i = 0; i < size; ++i) {
                delete entries[i];
            }
            delete[] entries;
            capacity = directory.capacity; 
            size = directory.size; 
            company = directory.company;
            entries = new Entry * [capacity];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = new Entry(* directory.entries[i]);
            }
        }
        return *this;
    }

    unsigned operator[](const string& name) const{
        if (searchPerson(name) == size) {
            return 99999999;
        }
        else {
            return entries[searchPerson(name)]->getPhone();
        }
    }


private:	
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;

    size_t searchPerson(const string& name) const {
        for (size_t i = 0; i < size; ++i) {
            if (entries[i]->getName() == name) {
                return i;
            }
        }
        return size;
    }

}; // class Directory

void doNothing(Directory dir) { 
    // You need to overload the Directory output operator before
    // uncommenting the next line.

    cout << dir << endl;
}



int main() {
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    
    // Create a Directory
    Directory d("HAL");
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    
    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;
    
    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    // Should display 1592
    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);
    

    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
    

    cout << "The delete on the next line will come once the main is popped" << endl;
} // main


